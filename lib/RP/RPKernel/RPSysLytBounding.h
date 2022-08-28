#ifndef RP_KERNEL_LYT_BOUNDING_H
#define RP_KERNEL_LYT_BOUNDING_H
#include "types_RP.h"

#include <nw4r/lyt/lyt_bounding.h>

/**
 * @brief NW4R layout bounding extension
 */
class RPSysLytBounding : public nw4r::lyt::Bounding {
public:
    /**
     * @brief Check if a specified position is inside the bounding
     * @param drawInfo Parent draw info
     * @param pos Position to check
     * @address 801993f4
     */
    bool isInsideBounding(nw4r::lyt::DrawInfo* drawInfo,
                          const nw4r::math::VEC2& pos);
};

#endif