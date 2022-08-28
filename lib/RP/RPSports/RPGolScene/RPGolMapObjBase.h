#ifndef RP_SPORTS_GOL_MAP_OBJ_BASE_H
#define RP_SPORTS_GOL_MAP_OBJ_BASE_H
#include "RPSysUnknownBase.h"
#include "types_RP.h"

#include <nw4r/math/math_types.h>

/**
 * @brief Base class for Pack Map objects in the golf scene
 * @todo Document all of the functions
 */
class RPGolMapObjBase : RPSysUnknownBase {
public:
    //! @address 80290a48
    RPGolMapObjBase();
    //! @address 80290ae4
    virtual ~RPGolMapObjBase();

private:
    //! @brief Map object model
    RPGrpModelG3D* mModel; // at 0x4
    //! @brief Binary map object
    RPUtlMapObject* mMapObj; // at 0x8

    //! @brief Map object rotation
    nw4r::math::MTX33 mRotation; // at 0xC
    //! @brief Map object offset
    nw4r::math::VEC3 mOffset; // at 0x30
    //! @brief Map object scale
    nw4r::math::VEC3 mScale; // at 0x3C

    //! @brief Pointer to mRotation
    nw4r::math::MTX33* mpRotation; // at 0x40
    //! @brief Pointer to mOffset
    nw4r::math::VEC3* mpOffset; // at 0x44
};

#endif