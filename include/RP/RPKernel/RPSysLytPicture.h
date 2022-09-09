#ifndef RP_KERNEL_LYT_PICTURE_H
#define RP_KERNEL_LYT_PICTURE_H
#include "types_RP.h"

#include <nw4r/lyt/lyt_picture.h>

/**
 * @brief NW4R layout picture extension
 */
class RPSysLytPicture : public nw4r::lyt::Picture {
public:
    /**
     * @brief Set the picture TEV color to the CPU color
     * @address 8019a6b8
     */
    void applyCpuColor();

    /**
     * @brief Set the picture TEV color to the specified player color
     * @param player Player ID
     * @address 8019a714
     */
    void applyPlayerColor(u32 player);
};

#endif