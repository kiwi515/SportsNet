#include "Socket.hpp"

#include <IPC/ipcclt.h>
#include <TRK/__mem.h>

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
}

/**
 * @brief Get address info structure from internet host/service
 *
 * @param node
 * @param service
 * @param hints
 * @param res
 * @return Success
 */
bool Socket::GetAddrInfo(const char* node, const char* service,
                         const AddrInfo* hints, AddrInfo** res) {
    ;
    MATO_ASSERT_EX(false, "Not yet implemented.");
}

/**
 * @brief
 *
 * @param addr
 * @param dst
 * @return true
 * @return false
 */
bool Socket::INetNtoP(const InAddr* addr, char* dst) {
    ;
    MATO_ASSERT_EX(false, "Not yet implemented.");
}

/**
 * @brief
 *
 * @param addr
 * @param dst
 * @return true
 * @return false
 */
bool Socket::INetPtoN(const char* addr, InAddr* dst) {
    ;
    MATO_ASSERT_EX(false, "Not yet implemented.");
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

    struct CloseData {
        s32 handle; // at 0x0
    };
    CloseData* data = new (32) CloseData();
    data->handle = mHandle;

    // Request close
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_CLOSE, data,
                           sizeof(CloseData), NULL, 0);
    delete data;
    return result >= 0;
}

/**
 * @brief
 *
 * @param backlog
 * @returns Success
 */
bool Socket::Listen(s32 backlog) {
    ;
    MATO_ASSERT_EX(false, "Not yet implemented.");
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
bool Socket::Bind(SockAddrIn* local) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (local == NULL || (local != NULL && local->len != 8)) {
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
    memcpy(&data->addr, local, local->len);

    // Request bind
    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_BIND, data, sizeof(BindData), NULL, 0);
    delete data;
    return result >= 0;
}

/**
 * @brief Connect to server
 *
 * @param remote Server address
 * @returns Success
 */
bool Socket::Connect(SockAddrIn* remote) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (remote == NULL || (remote != NULL && remote->len != 8)) {
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
    memcpy(&data->addr, remote, remote->len);

    // Request connect
    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_CONNECT, data,
                           sizeof(ConnectData), NULL, 0);
    delete data;
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
bool Socket::GetPeerName(SockAddrIn* peer) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (peer == NULL || (peer != NULL && peer->len != 8)) {
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
    memcpy(&data->addr, peer, peer->len);

    s32 result = IOS_Ioctl(sTcpStackHandle, IOCTL_GET_PEER_NAME, &data->handle,
                           sizeof(s32), &data->addr, data->addr.len);
    if (result >= 0) {
        memcpy(peer, &data->addr, data->addr.len);
    }

    delete data;
    return result >= 0;
}

/**
 * @brief Get address info of socket
 *
 * @param[out] socket Socket address info
 * @returns Success
 */
bool Socket::GetSocketName(SockAddrIn* socket) {
    MATO_ASSERT_EX(sInitialized, "Please call Socket::initialize");

    // Only IPv4 is supported
    if (socket == NULL || (socket != NULL && socket->len != 8)) {
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
    memcpy(&data->addr, socket, socket->len);

    s32 result =
        IOS_Ioctl(sTcpStackHandle, IOCTL_GET_SOCKET_NAME, &data->handle,
                  sizeof(s32), &data->addr, data->addr.len);
    if (result >= 0) {
        memcpy(socket, &data->addr, data->addr.len);
    }

    delete data;
    return result >= 0;
}

/**
 * @brief
 *
 * @param buf
 * @param len
 * @param flags
 * @return size_t
 */
size_t Socket::Recieve(void* buf, size_t len, u32 flags) {
    return RecieveFrom(buf, len, flags, NULL);
}

/**
 * @brief
 *
 * @param buf
 * @param len
 * @param flags
 * @param from
 * @return size_t
 */
size_t Socket::RecieveFrom(void* buf, size_t len, u32 flags, SockAddrIn* from) {
    ;
    MATO_ASSERT_EX(false, "Not yet implemented.");
}

/**
 * @brief
 *
 * @param buf
 * @param len
 * @param flags
 * @return size_t
 */
size_t Socket::Send(const void* buf, size_t len, u32 flags) {
    return SendTo(buf, len, flags, NULL);
}

/**
 * @brief
 *
 * @param buf
 * @param len
 * @param flags
 * @param to
 * @return size_t
 */
size_t Socket::SendTo(const void* buf, size_t len, u32 flags,
                      const SockAddrIn* to) {
    ;
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
    return result >= 0;
}

} // namespace spnet