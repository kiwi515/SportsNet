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
        IPPROTO_AUTO,

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
    static const u32 scAddrInfoMaxResults = 35;
    static const u32 scAddrInfoNameSize = 28;

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
        IOCTL_14H,
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

    // https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/IOS/Network/Socket.h
    enum Error {
        SUCCESS,
        E2BIG,
        EACCES,
        EADDRINUSE,
        EADDRNOTAVAIL,
        EAFNOSUPPORT,
        EAGAIN,
        EALREADY,
        EBADF,
        EBADMSG,
        EBUSY,
        ECANCELED,
        ECHILD,
        ECONNABORTED,
        ECONNREFUSED,
        ECONNRESET,
        EDEADLK,
        EDESTADDRREQ,
        EDOM,
        EDQUOT,
        EEXIST,
        EFAULT,
        EFBIG,
        EHOSTUNREACH,
        EIDRM,
        EILSEQ,
        EINPROGRESS,
        EINTR,
        EINVAL,
        EIO,
        EISCONN,
        EISDIR,
        ELOOP,
        EMFILE,
        EMLINK,
        EMSGSIZE,
        EMULTIHOP,
        ENAMETOOLONG,
        ENETDOWN,
        ENETRESET,
        ENETUNREACH,
        ENFILE,
        ENOBUFS,
        ENODATA,
        ENODEV,
        ENOENT,
        ENOEXEC,
        ENOLCK,
        ENOLINK,
        ENOMEM,
        ENOMSG,
        ENOPROTOOPT,
        ENOSPC,
        ENOSR,
        ENOSTR,
        ENOSYS,
        ENOTCONN,
        ENOTDIR,
        ENOTEMPTY,
        ENOTSOCK,
        ENOTSUP,
        ENOTTY,
        ENXIO,
        EOPNOTSUPP,
        EOVERFLOW,
        EPERM,
        EPIPE,
        EPROTO,
        EPROTONOSUPPORT,
        EPROTOTYPE,
        ERANGE,
        EROFS,
        ESPIPE,
        ESRCH,
        ESTALE,
        ETIME,
        ETIMEDOUT,
        ETXTBSY,
        EXDEV,

        ERROR_MAX
    };

    //! Structure for get/free addr info
    struct GetAddrInfoData {
        AddrInfo results[scAddrInfoMaxResults];
        char names[scAddrInfoMaxResults * scAddrInfoNameSize];
    };

public:
    static void Initialize();
    static const char* GetErrorString(s32 error);
    static void GetHostID(InAddr& addr);
    static bool GetAddrInfo(const char* node, const char* service,
                            const AddrInfo* hints, AddrInfo** res);
    static void FreeAddrInfo(AddrInfo* addr);
    static const char* INetNtoA(const InAddr& addr, char* dst = NULL,
                                size_t len = 0);
    static bool INetAtoN(const char* addr, InAddr& dst);

    Socket(Family domain, SocketType type, Protocol protocol);
    virtual ~Socket();

    bool IsOpen() const { return mHandle >= 0; }

    bool Close();
    bool Listen(s32 backlog);
    Socket* Accept(SockAddrIn* remote);
    bool Bind(SockAddrIn& local);
    bool Connect(SockAddrIn& remote);
    bool Disconnect();
    // bool SetBlocking(bool);
    // bool SetAsync(bool);
    bool GetPeerName(SockAddrIn& peer);
    bool GetSocketName(SockAddrIn& peer);
    s32 Recieve(void* buf, size_t len, u32 flags);
    s32 RecieveFrom(void* buf, size_t len, u32 flags, SockAddrIn* from);
    s32 Send(const void* buf, size_t len, u32 flags);
    s32 SendTo(const void* buf, size_t len, u32 flags, const SockAddrIn* to);
    bool Shutdown(ShutdownType type);

private:
    Socket(s32 handle);

private:
    s32 mHandle;

    static bool sInitialized;
    static s32 sTcpStackHandle;
};

} // namespace spnet

#endif