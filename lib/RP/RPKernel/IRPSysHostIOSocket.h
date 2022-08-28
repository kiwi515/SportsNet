#ifndef RP_KERNEL_I_HOSTIO_SOCKET_H
#define RP_KERNEL_I_HOSTIO_SOCKET_H
#include "types_RP.h"

/**
 * @brief Host I/O for debugging
 * @details All functions have been stubbed out
 */
class IRPSysHostIOSocket {
public:
    /**
     * @brief Construct socket with formattable name
     * @address 801907e4
     */
    IRPSysHostIOSocket(const char* name, ...);
    //! @address 801907d4
    IRPSysHostIOSocket();

    //! @address 80190794
    virtual ~IRPSysHostIOSocket();

    //! @address 8018a904
    virtual UNKTYPE FUN_8018a904(UNKTYPE) {}
    //! @address 8018a908
    virtual UNKTYPE FUN_8018a908(UNKTYPE) {}
};

#endif