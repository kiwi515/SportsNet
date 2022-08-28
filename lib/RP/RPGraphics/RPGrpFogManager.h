#ifndef RP_GRAPHICS_FOG_MANAGER_H
#define RP_GRAPHICS_FOG_MANAGER_H
#include "types_RP.h"

#include <egg/gfx/eggFogManager.h>

/**
 * @brief RP engine fog manager
 * @wfuname
 */
class RPGrpFogManager : public EGG::FogManager {
public:
    RPGrpFogManager() {}
    //! @address 801b2424
    virtual ~RPGrpFogManager() {}
};

#endif