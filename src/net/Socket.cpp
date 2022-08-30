#include "Socket.hpp"

#include <IPC/ipcclt.h>
#include <OS/OSTime.h>
#include <TRK/__mem.h>
#include <mato/math/matoAlgorithm.hpp>
#include <stdio.h>
#include <string.h>

#define PF_INET 2
#define SHUT_RDWR 2

#define F_GETFL 3
#define F_SETFL 4

#define O_NONBLOCK 0x4

namespace spnet {

bool Socket::sInitialized = false;
s32 Socket::sTcpStackHandle = -1;

/**
 * @brief Initalize socket system
 */
void Socket::Initialize() {
    // Prevent double initialization
    if (sInitialized) {
        return;
    }

    // Handle should not be valid yet
    MATO_ASSERT(sTcpStackHandle == -1);

    sTcpStackHandle = IOS_Open("/dev/net/ip/top", IPC_OPEN_NONE);
    MATO_ASSERT_EX(sTcpStackHandle >= 0,
                   "Could not get handle to TCP/IP stack");

    sInitialized = true;
    MATO_LOG("<< Socket Initialized >>");
}

/**
 * @brief Convert error code to string
 *
 * @param error Error code
 * @returns Error message
 */
const char* Socket::GetErrorString(s32 error) {
    u32 index = (error < 0) ? -error : error;

    if (index > ERROR_MAX) {
        return "SUCCESS";
    }

    static const char* sErrorsStr[] = {
        "SUCCESS",         "E2BIG",        "EACCES",       "EADDRINUSE",
        "EADDRNOTAVAIL",   "EAFNOSUPPORT", "EAGAIN",       "EALREADY",
        "EBADF",           "EBADMSG",      "EBUSY",        "ECANCELED",
        "ECHILD",          "ECONNABORTED", "ECONNREFUSED", "ECONNRESET",
        "EDEADLK",         "EDESTADDRREQ", "EDOM",         "EDQUOT",
        "EEXIST",          "EFAULT",       "EFBIG",        "EHOSTUNREACH",
        "EIDRM",           "EILSEQ",       "EINPROGRESS",  "EINTR",
        "EINVAL",          "EIO",          "EISCONN",      "EISDIR",
        "ELOOP",           "EMFILE",       "EMLINK",       "EMSGSIZE",
        "EMULTIHOP",       "ENAMETOOLONG", "ENETDOWN",     "ENETRESET",
        "ENETUNREACH",     "ENFILE",       "ENOBUFS",      "ENODATA",
        "ENODEV",          "ENOENT",       "ENOEXEC",      "ENOLCK",
        "ENOLINK",         "ENOMEM",       "ENOMSG",       "ENOPROTOOPT",
        "ENOSPC",          "ENOSR",        "ENOSTR",       "ENOSYS",
        "ENOTCONN",        "ENOTDIR",      "ENOTEMPTY",    "ENOTSOCK",
        "ENOTSUP",         "ENOTTY",       "ENXIO",        "EOPNOTSUPP",
        "EOVERFLOW",       "EPERM",        "EPIPE",        "EPROTO",
        "EPROTONOSUPPORT", "EPROTOTYPE",   "ERANGE",       "EROFS",
        "ESPIPE",          "ESRCH",        "ESTALE",       "ETIME",
        "ETIMEDOUT",       "ETXTBSY",      "EXDEV"};
    return sErrorsStr[index];
}

/**
 * @brief Get the IP address of the host machine
 */
u32 Socket::GetHostIP() {
    Initialize();
    return static_cast<u32>(
        IOS_Ioctl(sTcpStackHandle, IOCTL_GET_HOST_ID, NULL, 0, NULL, 0));
}

/**
 * @brief Monitor sockets for events
 *
 * @param fds Poll information
 * @param numfds Descriptor array length
 * @param timeout Timeout (OS time)
 * @returns Success
 */
bool Socket::Poll(PollFD* fds, size_t numfds, s64 timeout) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    if (fds == NULL) {
        return false;
    }

    // Setup data for ioctl
    s64* ioctlTimeout = new (32) s64();
    *ioctlTimeout = OS_TIME_TO_MILLI_SEC(timeout);
    PollFD* ioctlFds = new (32) PollFD[numfds];
    memcpy(ioctlFds, fds, numfds * sizeof(PollFD));

    // Request poll
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_POLL, ioctlTimeout,
                           sizeof(s64), ioctlFds, numfds * sizeof(PollFD));
    if (result >= 0) {
        memcpy(fds, ioctlFds, numfds * sizeof(PollFD));
    }

    MATO_WARN_EX(result < 0, "Poll returned [%s]", GetErrorString(result));
    delete ioctlTimeout;
    delete ioctlFds;
    return result >= 0;
}

/**
 * @brief Create a new socket
 *
 * @param type Socket type
 */
Socket::Socket(Type type) {
    Initialize();

    // Setup data for ioctl
    struct CreateData {
        s32 domain;   // at 0x0
        s32 type;     // at 0x4
        s32 protocol; // at 0x8
    };
    CreateData* data = new (32) CreateData();
    data->domain = PF_INET;
    data->type = type;
    data->protocol = 0;

    // Request socket
    mHandle = IOS_Ioctl(sTcpStackHandle, IOCTL_CREATE_SOCKET, data,
                        sizeof(CreateData), NULL, 0);
    MATO_ASSERT_EX(mHandle >= 0, "Failed to create socket");
    delete data;
}

/**
 * @brief Initialize socket with existing handle
 *
 * @param handle Socket handle
 */
Socket::Socket(s32 handle) : mHandle(handle) {}

/**
 * @brief Destroy socket
 */
Socket::~Socket() {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");
    Disconnect();
}

/**
 * @brief Control socket
 *
 * @param cmd Command
 * @param ... Command arguments
 * @returns Result
 */
s32 Socket::Fcntl(s32 cmd, ...) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Get argument
    va_list list;
    va_start(cmd, list);
    s32 arg = *reinterpret_cast<s32*>(__va_arg(list, 1));
    va_end(list);

    // Setup data for ioctl
    struct FcntlData {
        s32 handle; // at 0x0
        s32 cmd;    // at 0x4
        s32 arg;    // at 0x8
    };
    FcntlData* data = new (32) FcntlData();
    data->handle = mHandle;
    data->cmd = cmd;
    data->arg = arg;

    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_FCNTL, data,
                           sizeof(FcntlData), NULL, 0);
    MATO_WARN_EX(result < 0, "Fcntl returned [%s]", GetErrorString(result));
    return result;
}

/**
 * @brief Toggle socket blocking
 *
 * @param block Whether to enable blocking
 * @returns Success
 */
bool Socket::SetBlocking(bool block) {
    s32 flags = Fcntl(F_GETFL, 0);

    if (block) {
        flags &= ~O_NONBLOCK;
    } else {
        flags |= O_NONBLOCK;
    }

    return Fcntl(F_SETFL, flags) >= 0;
}

/**
 * @brief Accept remote connection
 *
 * @returns New socket
 */
Socket* Socket::Accept() {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Child socket
    Socket* child = NULL;

    // Setup data for ioctl
    struct AcceptData {
        union {
            s32 handle;
            u8 data[32];
        };               // at 0x0
        SockAddrIn addr; // at 0x20
    };
    AcceptData* data = new (32) AcceptData();
    data->handle = mHandle;
    data->addr.len = 8;

    // Request new socket
    s32 handle = IOS_Ioctl(sTcpStackHandle, IOCTL_ACCEPT, &data->handle,
                           sizeof(s32), &data->addr, data->addr.len);
    if (handle >= 0) {
        // Construct new socket
        child = new Socket(handle);
    }

    MATO_WARN_EX(handle < 0, "Accept returned [%s]", GetErrorString(handle));
    delete data;
    return child;
}

/**
 * @brief Bind socket to port
 *
 * @param port Socket port
 * @returns Success
 */
bool Socket::Bind(u16 port) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Setup data for ioctl
    struct BindData {
        s32 handle; // at 0x0
        s32 WORD_0x4;
        SockAddrIn dest; // at 0x8
        char UNK_0x10[0x24 - 0x10];
    };
    BindData* data = new (32) BindData();
    data->handle = mHandle;
    data->WORD_0x4 = 1;
    data->dest.len = 8;
    data->dest.family = PF_INET;
    data->dest.port = port;
    data->dest.addr.addr = 0;

    // Request bind
    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_BIND, data, sizeof(BindData), NULL, 0);
    MATO_WARN_EX(result < 0, "Bind returned [%s]", GetErrorString(result));
    delete data;
    return result >= 0;
}

/**
 * @brief Connect to server
 *
 * @param ip IP address
 * @param port Port
 * @returns Success
 */
bool Socket::Connect(u32 ip, u16 port) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Setup data for ioctl
    struct ConnectData {
        s32 handle; // at 0x0
        s32 WORD_0x4;
        SockAddrIn dest; // at 0x8
        char UNK_0x10[0x24 - 0x10];
    };
    ConnectData* data = new (32) ConnectData();
    data->handle = mHandle;
    data->WORD_0x4 = 1;
    data->dest.len = 8;
    data->dest.family = PF_INET;
    data->dest.port = port;
    data->dest.addr.addr = ip;

    // Request connect
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_CONNECT, data,
                           sizeof(ConnectData), NULL, 0);
    MATO_WARN_EX(result < 0, "Connect returned [%s]", GetErrorString(result));
    delete data;
    return result >= 0;
}

/**
 * @brief Shutdown + close socket
 *
 * @returns Success
 */
bool Socket::Disconnect() {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    s32 result;
    bool success = true;

    if (mHandle >= 0) {
        // Setup data for shutdown ioctl
        struct ShutdownData {
            s32 handle; // at 0x0
            s32 type;   // at 0x4
        };
        ShutdownData* sdData = new (32) ShutdownData();
        sdData->handle = mHandle;
        sdData->type = SHUT_RDWR;

        // Request shutdown
        result = IOS_Ioctl(sTcpStackHandle, IOCTL_SO_SHUTDOWN, sdData,
                           sizeof(ShutdownData), NULL, 0);
        MATO_WARN_EX(result < 0, "Shutdown returned [%s]",
                     GetErrorString(result));
        success = success && result >= 0;
        delete sdData;

        // Setup data for close ioctl
        struct CloseData {
            s32 handle; // at 0x0
        };
        CloseData* clData = new (32) CloseData();
        clData->handle = mHandle;

        // Request close
        result = IOS_Ioctl(sTcpStackHandle, IOCTL_CLOSE, clData,
                           sizeof(CloseData), NULL, 0);
        MATO_WARN_EX(result < 0, "Close returned [%s]", GetErrorString(result));
        success = success && result >= 0;
        delete clData;
    }

    mHandle = -1;
    return success;
}

/**
 * @brief Listen for incoming connections
 *
 * @param backlog Maximum pending connections
 * @returns Success
 */
bool Socket::Listen(s32 backlog) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Setup data for ioctl
    struct ListenData {
        s32 handle;  // at 0x0
        s32 backlog; // at 0x4
    };
    ListenData* data = new (32) ListenData();
    data->handle = mHandle;
    data->backlog = backlog;

    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_LISTEN, data,
                           sizeof(ListenData), NULL, 0);
    MATO_WARN_EX(result < 0, "Listen returned [%s]", GetErrorString(result));
    delete data;
    return result >= 0;
}

/**
 * @brief Get address info of socket
 *
 * @param[out] ip IP address
 * @param[out] port port
 * @returns Success
 */
bool Socket::GetSocketIP(u32& ip, u16& port) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Setup data for ioctl
    struct SocketNameData {
        union {
            s32 handle;
            u8 data[32];
        };               // at 0x0
        SockAddrIn self; // at 0x20
    };
    SocketNameData* data = new (32) SocketNameData();
    data->handle = mHandle;
    data->self.len = 8;

    // Request peer info
    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_GET_SOCKET_NAME, &data->handle,
                  sizeof(s32), &data->self, data->self.len);
    if (result >= 0) {
        ip = data->self.addr.addr;
        port = data->self.port;
    }

    MATO_WARN_EX(result < 0, "GetSocketIP returned [%s]",
                 GetErrorString(result));
    delete data;
    return result >= 0;
}

/**
 * @brief Get address info of remote connection
 *
 * @param[out] ip Peer IP address
 * @param[out] port Peer port
 * @returns Success
 */
bool Socket::GetPeerIP(u32& ip, u16& port) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Setup data for ioctl
    struct PeerNameData {
        union {
            s32 handle;
            u8 data[32];
        };               // at 0x0
        SockAddrIn peer; // at 0x20
    };
    PeerNameData* data = new (32) PeerNameData();
    data->handle = mHandle;
    data->peer.len = 8;

    // Request peer info
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_GET_PEER_NAME, &data->handle,
                           sizeof(s32), &data->peer, data->peer.len);
    if (result >= 0) {
        ip = data->peer.addr.addr;
        port = data->peer.port;
    }

    MATO_WARN_EX(result < 0, "GetPeerIP returned [%s]", GetErrorString(result));
    delete data;
    return result >= 0;
}

/**
 * @brief Check if there is a pending response
 */
bool Socket::CanReceive() {
    PollFD fd;
    fd.fd = mHandle;
    fd.events = 1;
    fd.revents = 0;

    bool success = Poll(&fd, 1, 0);
    return success && fd.events == fd.revents;
}

/**
 * @brief Check if the socket can send data
 */
bool Socket::CanSend() {
    PollFD fd;
    fd.fd = mHandle;
    fd.events = 8;
    fd.revents = 0;

    bool success = Poll(&fd, 1, 0);
    return success && fd.events == fd.revents;
}

/**
 * @brief Receive data from bound connection
 *
 * @param buf Destination buffer
 * @param len Buffer size
 * @returns Bytes received (< 0 if failure)
 */
s32 Socket::Recieve(void* buf, size_t len) {
    return RecieveFromImpl(buf, len, NULL, NULL);
}

/**
 * @brief Receive data from specified connection
 *
 * @param buf Destination buffer
 * @param len Buffer size
 * @param ip Source IP address
 * @param port Source port
 * @returns Bytes received (< 0 if failure)
 */
s32 Socket::RecieveFrom(void* buf, size_t len, u32 ip, u16 port) {
    return RecieveFromImpl(buf, len, &ip, &port);
}

/**
 * @brief Send data to bound connection
 *
 * @param buf Source buffer
 * @param len Buffer size
 * @returns Bytes sent (< 0 if failure)
 */
s32 Socket::Send(void* buf, size_t len) {
    return SendToImpl(buf, len, NULL, NULL);
}

/**
 * @brief Send data to specified connection
 *
 * @param buf Source buffer
 * @param len Buffer size
 * @param ip Destination IP address
 * @param port Destination port
 * @returns Bytes sent (< 0 if failure)
 */
s32 Socket::SendTo(void* buf, size_t len, u32 ip, u16 port) {
    return SendToImpl(buf, len, &ip, &port);
}

/**
 * @brief Receive data from specified connection
 *
 * @param buf Destination buffer
 * @param len Buffer size
 * @param ip Source IP address
 * @param port Source port
 * @returns Bytes received (< 0 if failure)
 */
s32 Socket::RecieveFromImpl(void* buf, size_t len, u32* ip, u16* port) {
    MATO_ASSERT_EX(false, "Not yet implemented.");
}

/**
 * @brief Send data to specified connection
 *
 * @param buf Source buffer
 * @param len Buffer size
 * @param ip Destination IP address
 * @param port Destination port
 * @returns Bytes sent (< 0 if failure)
 */
s32 Socket::SendToImpl(const void* buf, size_t len, u32* ip, u16* port) {
    MATO_ASSERT_EX(false, "Not yet implemented.");
}

} // namespace spnet