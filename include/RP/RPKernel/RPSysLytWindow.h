#ifndef RP_KERNEL_LYT_WINDOW_H
#define RP_KERNEL_LYT_WINDOW_H
#include "types_RP.h"

#include <nw4r/lyt/lyt_window.h>

/**
 * @brief NW4R layout window extension
 */
class RPSysLytWindow : public nw4r::lyt::Window {
public:
    /**
     * @brief Set the picture TEV color to the CPU color
     * @address 801a59ec
     */
    void applyCpuColor();

    /**
     * @brief Set the picture TEV color to the specified player color
     * @param player Player ID
     * @param setContent Set content material color
     * @address 801a5a98
     */
    void applyPlayerColor(u32 player, bool setContent);
};

#endif