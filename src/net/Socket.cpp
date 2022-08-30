#include "Socket.hpp"

#include <IPC/ipcclt.h>
#include <TRK/__mem.h>
#include <mato/math/matoAlgorithm.hpp>
#include <stdio.h>
#include <string.h>

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
 * @brief Get IP address of the local machine
 *
 * @param[out] addr Address structure
 */
void Socket::GetHostID(InAddr& addr) {
    if (!sInitialized) {
        Initialize();
    }

    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_GET_HOST_ID, NULL, 0, NULL, 0);
    addr.addr = static_cast<u32>(result);
}

/**
 * @brief Get address info structure from internet host/service
 *
 * @param node Internet host
 * @param service Service
 * @param hints Search criteria
 * @param[out] res Result output (owned by caller)
 * @returns Success
 */
bool Socket::GetAddrInfo(const char* node, const char* service,
                         const AddrInfo* hints, AddrInfo** res) {
    if (!sInitialized) {
        Initialize();
    }

    if (res == NULL) {
        return false;
    }

    // Only IPv4 is supported
    if (hints != NULL && hints->family != PF_INET) {
        *res = NULL;
        return false;
    }

    // Setup data for ioctl
    enum GetAddrVectors {
        V_NODE,
        V_SERVICE,
        V_HINTS,
        V_RES,
        V_MAX,

        V_INPUT = 3,
        V_OUTPUT = 1
    };
    IPCIOVector* vectors = new (32) IPCIOVector[V_MAX];

    // Node
    if (node != NULL) {
        const size_t nodeLength = strlen(node);
        vectors[V_NODE].base = new char[nodeLength];
        strncpy(static_cast<char*>(vectors[V_NODE].base), node, nodeLength);
        vectors[V_NODE].length = nodeLength;
    }

    // Service
    if (service != NULL) {
        const size_t serviceLength = strlen(service);
        vectors[V_SERVICE].base = new char[serviceLength];
        strncpy(static_cast<char*>(vectors[V_SERVICE].base), service,
                serviceLength);
        vectors[V_SERVICE].length = serviceLength;
    }

    // Hints
    AddrInfo* addr = new (32) AddrInfo();
    if (hints != NULL) {
        memcpy(addr, hints, sizeof(AddrInfo));
    }
    if (addr->family == 0) {
        addr->family = PF_INET;
    }
    vectors[V_HINTS].base = addr;
    vectors[V_HINTS].length = sizeof(AddrInfo);

    // Result buffer
    GetAddrInfoData* data = new (32) GetAddrInfoData();
    vectors[V_RES].base = data;
    vectors[V_RES].length = sizeof(GetAddrInfoData);

    s32 result = IOS_Ioctlv(sTcpStackHandle, IOCTL_GET_ADDR_INFO, V_INPUT,
                            V_OUTPUT, vectors);
    if (result >= 0) {
        // Output results
        *res = data->results;

        // Fix pointers in address info
        char* name = data->names;
        for (AddrInfo* it = data->results; it != NULL; it = it->next) {
            it->canonName = name;
            // Results are contiguous in buffer
            if (it->next != NULL) {
                it->next = reinterpret_cast<AddrInfo*>(
                    mato::AddToPtr(it, sizeof(AddrInfo)));
            }

            name += scAddrInfoNameSize;
        }
    } else {
        *res = NULL;
        // Free results because they will not be used
        delete data;
    }

    // Cleanup memory
    // (NOTE: Results (V_RES.base) are NOT destroyed, they are freed using
    // FreeAddrInfo)
    delete vectors[V_NODE].base;
    delete vectors[V_SERVICE].base;
    delete vectors[V_HINTS].base;
    delete[] vectors;

    MATO_WARN_EX(result < 0, "GetAddrInfo returned [%s]",
                 GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Free address info obtained using GetAddrInfo
 *
 * @param addr Address info
 */
void Socket::FreeAddrInfo(AddrInfo* addr) {
    if (addr != NULL) {
        // We assume the address info is actually the results structure
        GetAddrInfoData* results = reinterpret_cast<GetAddrInfoData*>(addr);
        delete results;
    }
}

/**
 * @brief Convert network address to ASCII string
 * @note Provide your own buffer if you don't want to use temp mem
 *
 * @param addr Network address
 * @param[out] dst Destination buffer (optional)
 * @param len Destination buffer length
 * @returns ASCII string
 */
const char* Socket::INetNtoA(const InAddr& addr, char* dst, size_t len) {
    static char sTempMem[32];

    char* buffer = (dst != NULL) ? dst : sTempMem;
    const size_t bufferLength = (dst != NULL) ? len : sizeof(sTempMem);

    snprintf(buffer, bufferLength, "%d.%d.%d.%d", addr.octets[0],
             addr.octets[1], addr.octets[2], addr.octets[3]);
    return buffer;
}

/**
 * @brief Convert ASCII string to network address
 *
 * @param addr ASCII string
 * @param[out] dst Network address
 * @returns Success
 */
bool Socket::INetAtoN(const char* addr, InAddr& dst) {
    if (!sInitialized) {
        Initialize();
    }

    if (addr == NULL) {
        return false;
    }

    // Setup data for ioctl
    struct AtoNData {
        union {
            InAddr addr;
            u8 data[32];
        };              // at 0x0
        char ascii[32]; // at 0x20
    };
    AtoNData* data = new (32) AtoNData();

    const size_t len = mato::Min<size_t>(strlen(addr), sizeof(data->ascii) - 1);
    strncpy(data->ascii, addr, sizeof(data->ascii));
    data->ascii[len] = '\0';

    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_INET_ATON, data->ascii, len,
                           &data->addr, sizeof(InAddr));

    if (result >= 0) {
        memcpy(&dst, &data->addr, sizeof(InAddr));
    }

    delete data;
    MATO_WARN_EX(result < 0, "INetAtoN returned [%s]", GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Create a new socket
 *
 * @param domain Socket domain
 * @param type Socket type
 * @param protocol Transfer protocol
 */
Socket::Socket(Family domain, SocketType type, Protocol protocol) {
    if (!sInitialized) {
        Initialize();
    }

    // Setup data for ioctl
    struct CreateData {
        s32 domain;   // at 0x0
        s32 type;     // at 0x4
        s32 protocol; // at 0x8
    };
    CreateData* data = new (32) CreateData();
    data->domain = domain;
    data->type = type;
    data->protocol = protocol;

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
Socket::Socket(s32 handle) : mHandle(handle) {
    if (!sInitialized) {
        Initialize();
    }
}

/**
 * @brief Destroy socket
 */
Socket::~Socket() {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");
    Disconnect();
}

/**
 * @brief Close socket
 *
 * @returns Success
 */
bool Socket::Close() {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Setup data for ioctl
    struct CloseData {
        s32 handle; // at 0x0
    };
    CloseData* data = new (32) CloseData();
    data->handle = mHandle;

    // Request close
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_CLOSE, data,
                           sizeof(CloseData), NULL, 0);
    delete data;
    MATO_WARN_EX(result < 0, "Close returned [%s]", GetErrorString(result));
    return result >= 0;
}

/**
 * @brief
 *
 * @param backlog
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
    delete data;
    MATO_WARN_EX(result < 0, "Listen returned [%s]", GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Accept remote connection
 *
 * @param[out] remote Remote address
 */
Socket* Socket::Accept(SockAddrIn* remote) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Child socket
    Socket* child = NULL;
    // Output buffer for ioctl
    SockAddrIn* outData = NULL;
    s32 outSize = 0;

    // Only IPv4 is supported
    if (remote != NULL && remote->len != 8) {
        return NULL;
    }

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

    // Caller wants remote address
    if (remote != NULL) {
        // Fill in fields
        memcpy(&data->addr, remote, remote->len);
        // Update output buffer
        outData = &data->addr;
        outSize = data->addr.len;
    }

    // Request new socket
    s32 handle = IOS_Ioctl(sTcpStackHandle, IOCTL_ACCEPT, &data->handle,
                           sizeof(s32), outData, outSize);
    if (handle >= 0) {
        // Copy output addr
        if (remote != NULL) {
            memcpy(remote, &data->addr, 8);
        }

        // Construct new socket
        child = new Socket(handle);
    }

    delete data;
    return child;
}

/**
 * @brief Bind socket to IP/port
 *
 * @param local Socket address
 * @returns Success
 */
bool Socket::Bind(SockAddrIn& local) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (local.len != 8) {
        return false;
    }

    // Setup data for ioctl
    struct BindData {
        s32 handle; // at 0x0
        s32 WORD_0x4;
        SockAddrIn addr; // at 0x8
        char UNK_0x10[0x24 - 0x10];
    };
    BindData* data = new (32) BindData();
    data->handle = mHandle;
    data->WORD_0x4 = 1;
    memcpy(&data->addr, &local, local.len);

    // Request bind
    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_BIND, data, sizeof(BindData), NULL, 0);
    delete data;
    MATO_WARN_EX(result < 0, "Bind returned [%s]", GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Connect to server
 *
 * @param remote Server address
 * @returns Success
 */
bool Socket::Connect(SockAddrIn& remote) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (remote.len != 8) {
        return false;
    }

    // Setup data for ioctl
    struct ConnectData {
        s32 handle; // at 0x0
        s32 WORD_0x4;
        SockAddrIn addr; // at 0x8
        char UNK_0x10[0x24 - 0x10];
    };
    ConnectData* data = new (32) ConnectData();
    data->handle = mHandle;
    data->WORD_0x4 = 1;
    memcpy(&data->addr, &remote, remote.len);

    // Request connect
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_CONNECT, data,
                           sizeof(ConnectData), NULL, 0);
    delete data;
    MATO_WARN_EX(result < 0, "Connect returned [%s]", GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Shutdown and close socket
 *
 * @returns Success
 */
bool Socket::Disconnect() {
    bool success = true;

    if (mHandle >= 0) {
        // Both operations must be successful
        success = success && Shutdown(SHUT_RDWR);
        success = success && Close();
        mHandle = -1;
    }

    return success;
}

/**
 * @brief Get address info of remote connection
 *
 * @param[out] peer Remote address info
 * @returns Success
 */
bool Socket::GetPeerName(SockAddrIn& peer) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (peer.len != 8) {
        return false;
    }

    // Setup data for ioctl
    struct PeerNameData {
        union {
            s32 handle;
            u8 data[32];
        };               // at 0x0
        SockAddrIn addr; // at 0x20
    };
    PeerNameData* data = new (32) PeerNameData();
    data->handle = mHandle;
    memcpy(&data->addr, &peer, peer.len);

    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_GET_PEER_NAME, &data->handle,
                           sizeof(s32), &data->addr, data->addr.len);
    if (result >= 0) {
        memcpy(&peer, &data->addr, data->addr.len);
    }

    delete data;
    MATO_WARN_EX(result < 0, "GetPeerName returned [%s]",
                 GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Get address info of socket
 *
 * @param[out] socket Socket address info
 * @returns Success
 */
bool Socket::GetSocketName(SockAddrIn& socket) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (socket.len != 8) {
        return false;
    }

    // Setup data for ioctl
    struct SocketNameData {
        union {
            s32 handle;
            u8 data[32];
        };               // at 0x0
        SockAddrIn addr; // at 0x20
    };
    SocketNameData* data = new (32) SocketNameData();
    data->handle = mHandle;
    memcpy(&data->addr, &socket, socket.len);

    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_GET_SOCKET_NAME, &data->handle,
                  sizeof(s32), &data->addr, data->addr.len);
    if (result >= 0) {
        memcpy(&socket, &data->addr, data->addr.len);
    }

    delete data;
    MATO_WARN_EX(result < 0, "GetSocketName returned [%s]",
                 GetErrorString(result));
    return result >= 0;
}

/**
 * @brief Receive data from bound connection
 *
 * @param buf Destination buffer
 * @param len Buffer size
 * @param flags Flags
 * @returns Total data received
 */
s32 Socket::Recieve(void* buf, size_t len, u32 flags) {
    return RecieveFrom(buf, len, flags, NULL);
}

/**
 * @brief Receive data from specified source
 *
 * @param buf Destination buffer
 * @param len Buffer size
 * @param flags Flags
 * @param from Data source
 * @returns Total data received (< 0 if failure)
 */
s32 Socket::RecieveFrom(void* buf, size_t len, u32 flags, SockAddrIn* from) {
    // Only IPv4 is supported
    if (from != NULL && from->len != 8) {
        return -1;
    }

    if (len == 0) {
        return 0;
    }

    if (buf == NULL) {
        return -1;
    }
}

/**
 * @brief Send data to bound connection
 *
 * @param buf Source buffer
 * @param len Buffer size
 * @param flags Flags
 * @returns Total data sent (< 0 if failure)
 */
s32 Socket::Send(const void* buf, size_t len, u32 flags) {
    return SendTo(buf, len, flags, NULL);
}

/**
 * @brief Send data to bound connection
 *
 * @param buf Source buffer
 * @param len Buffer size
 * @param flags Flags
 * @param to Data destination
 * @returns Total data sent (< 0 if failure)
 */
s32 Socket::SendTo(const void* buf, size_t len, u32 flags,
                   const SockAddrIn* to) {
    MATO_ASSERT_EX(false, "Not yet implemented.");
}

/**
 * @brief Close socket in a specific way
 *
 * @param type Shutdown type
 * @returns Success
 */
bool Socket::Shutdown(ShutdownType type) {
    // Setup data for ioctl
    struct ShutdownData {
        s32 handle; // at 0x0
        s32 type;   // at 0x4
    };
    ShutdownData* data = new (32) ShutdownData();
    data->handle = mHandle;
    data->type = type;

    // Request shutdown
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_SO_SHUTDOWN, data,
                           sizeof(ShutdownData), NULL, 0);
    delete data;
    MATO_WARN_EX(result < 0, "Shutdown returned [%s]", GetErrorString(result));
    return result >= 0;
}

} // namespace spnet