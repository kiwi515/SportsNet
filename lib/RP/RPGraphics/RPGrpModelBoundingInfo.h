#ifndef RP_GRAPHICS_MODEL_BOUNDING_INFO_H
#define RP_GRAPHICS_MODEL_BOUNDING_INFO_H
#include "types_RP.h"

#include <egg/gfx/eggModelBoundingInfo.h>

/**
 * @brief Wrapper for EGG's ModelBoundingInfo
 * @wfuname
 */
class RPGrpModelBoundingInfo : public EGG::ModelBoundingInfo {
public:
    //! @address 801b25f8
    RPGrpModelBoundingInfo(u32, RPGrpModel*);
    //! @address 801b2638
    virtual ~RPGrpModelBoundingInfo();
};

#endif