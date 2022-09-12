#ifndef RP_SYSTEM_COMMON_OBJECT_H
#define RP_SYSTEM_COMMON_OBJECT_H
#include "IRPGrpDrawObject.h"
#include "types_RP.h"

/**
 * @brief Provides common draw functionality to derived objects,
 * and automatically adds them to the renderer's queue.
 * @wfuname
 */
class RPSysCommonObject : public IRPGrpDrawObject {
public:
    //! @address 80187dbc
    RPSysCommonObject();

    //! @address 80187f24
    virtual ~RPSysCommonObject();

    /**
     * @brief Draws scene fader, pause mgr, etc.
     * @address 80187c10
     */
    virtual void UserDraw();
};

#endif