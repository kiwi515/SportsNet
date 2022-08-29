#ifndef SPORTSNET_NET_SOCKET_H
#define SPORTSNET_NET_SOCKET_H
#include <types.h>

namespace spnet {

/**
 * @brief TCP/IP socket wrapper
 * @note IPv4 only
 */
class Socket {
public:
    //! Socket Address/protocol family
    enum Family {
        PF_INET = 2,
    };

    //! Socket types
    enum SocketType {
        SOCK_STREAM = 1,
        SOCK_DGRAM,
    };

    //! Socket transfer protocol
    enum Protocol {
        IPPROTO_TCP = 6,
        IPPROTO_UDP = 21,
    };

    //! Socket shutdown type
    enum ShutdownType { SHUT_RD, SHUT_WR, SHUT_RDWR };

    struct InAddr {
        union {
            u32 addr;
            u8 octets[4];
        };
    };

    struct SockAddrIn {
        u8 len;
        u8 family;
        u16 port;
        InAddr addr;
    };

    struct AddrInfo {
        s32 flags;
        s32 family;
        s32 sockType;
        s32 protocol;
        s32 addrLen;
        SockAddrIn* sockAddr;
        char* canonName;
        AddrInfo* next;
    };

private:
    //! I/O control commands for internal socket operation
    enum Ioctl {
        NONE,
        IOCTL_ACCEPT,
        IOCTL_BIND,
        IOCTL_CLOSE,
        IOCTL_CONNECT,
        IOCTL_FCNTL,
        IOCTL_GET_PEER_NAME,
        IOCTL_GET_SOCKET_NAME,
        IOCTL_GET_OPTION,
        IOCTL_SET_OPTION,
        IOCTL_LISTEN,
        IOCTL_POLL,
        IOCTL_RECV_FROM,
        IOCTL_SEND_TO,
        IOCTL_SO_SHUTDOWN,
        IOCTL_CREATE_SOCKET,
        IOCTL_GET_HOST_ID,
        IOCTL_GET_HOST_BY_NAME,
        IOCTL_GET_HOST_BY_ADDR,
        IOCTL_GET_NAME_INFO,
        IOCTL_INET_ATON,
        IOCTL_INET_PTON,
        IOCTL_INET_NTOP,
        IOCTL_GET_ADDR_INFO,
        IOCTL_SOCK_AT_MARK,
        IOCTL_GET_INTERFACE_OPTION,
        IOCTL_SET_INTERFACE_OPTION,
        IOCTL_SET_INTERFACE,
        IOCTL_SO_STARTUP
    };

public:
    static void Initialize();
    static bool GetAddrInfo(const char* node, const char* service,
                            const AddrInfo* hints, AddrInfo** res);
    static bool INetNtoA(const InAddr* addr, char* dst);
    static bool INetAtoN(const char* addr, InAddr* dst);

    Socket(Family domain, SocketType type, Protocol protocol);
    virtual ~Socket();

    bool IsOpen() const { return mHandle >= 0; }

    bool Close();
    bool Listen(s32 backlog);
    Socket* Accept(SockAddrIn* remote);
    bool Bind(SockAddrIn* local);
    bool Connect(SockAddrIn* remote);
    bool Disconnect();
    // bool SetBlocking(bool);
    // bool SetAsync(bool);
    bool GetPeerName(SockAddrIn* peer);
    bool GetSocketName(SockAddrIn* peer);
    size_t Recieve(void* buf, size_t len, u32 flags);
    size_t RecieveFrom(void* buf, size_t len, u32 flags, SockAddrIn* from);
    size_t Send(const void* buf, size_t len, u32 flags);
    size_t SendTo(const void* buf, size_t len, u32 flags, const SockAddrIn* to);
    bool Shutdown(ShutdownType type);

private:
    Socket(s32 handle);

    s32 mHandle;

    static bool sInitialized;
    static s32 sTcpStackHandle;
};

} // namespace spnet

#endif