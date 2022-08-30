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
    //! Socket types
    enum Type {
        SOCK_STREAM = 1,
        SOCK_DGRAM,
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

public:
    static void Initialize();
    static const char* GetErrorString(s32 error);
    static u32 GetHostIP();

    Socket(Type type);
    virtual ~Socket();

    bool IsOpen() const { return mHandle >= 0; }
    bool SetBlocking(bool block);

    Socket* Accept();
    bool Bind(u16 port);
    bool Connect(u32 ip, u16 port);
    bool Disconnect();
    bool Listen(s32 backlog = 5);
    bool GetSocketIP(u32& ip, u16& port);
    bool GetPeerIP(u32& ip, u16& port);
    s32 Recieve(void* buf, size_t len);
    s32 RecieveFrom(void* buf, size_t len, u32 ip, u16 port);
    s32 Send(void* buf, size_t len);
    s32 SendTo(void* buf, size_t len, u32 ip, u16 port);

private:
    Socket(s32 handle);
    s32 RecieveFromImpl(void* buf, size_t len, u32* ip, u16* port);
    s32 SendToImpl(const void* buf, size_t len, u32* ip, u16* port);

private:
    s32 mHandle;

    static bool sInitialized;
    static s32 sTcpStackHandle;
};

} // namespace spnet

#endif