#ifndef RP_KERNEL_LYT_DYNAMIC_ANM_H
#define RP_KERNEL_LYT_DYNAMIC_ANM_H
#include "types_RP.h"

#include <egg/math/eggVector.h>
#include <nw4r/lyt/lyt_pane.h>
#include <nw4r/ut/ut_list.h>

/**
 * @brief Dynamic animation in/out of the screen, with configurable direction
 * and length. Reversible at any time.
 * @wfuname
 */
class RPSysLytDynamicAnm {
public:
    /**
     * @brief Animation state
     */
    enum EState {
        STATE_FINISH_OUT,
        STATE_START_IN,
        STATE_FINISH_IN,
        STATE_START_OUT,
        STATE_NONE
    };

    /**
     * @brief Animation direction
     */
    enum EDirection {
        DIRECTION_UP,
        DIRECTION_DOWN,
        DIRECTION_LEFT,
        DIRECTION_RIGHT,
    };

public:
    /**
     * @brief Constructor
     * @param parent Parent pane
     * @param direction Animation direction
     * @param length Animation length (in frames)
     * @address 8019e9b0
     */
    RPSysLytDynamicAnm(nw4r::lyt::Pane* parent, EDirection direction,
                       s16 length);

    /**
     * @brief Run animation logic
     * @address 8019e494
     */
    void calc();

    /**
     * @brief Start animating out
     * @param frame Start frame
     * @address 8019e7ec
     */
    void startAnmOut(s16 frame);

    /**
     * @brief Start animating in
     * @param frame Start frame
     * @address 8019e810
     */
    void startAnmIn(s16 frame);

    /**
     * @brief Flip animation horizontally
     * @param reverse Whether to reverse horizontal direction
     * @address 8019e834
     */
    void reverseAnmHDirection(bool reverse);

    /**
     * @brief Reset animation
     * @address 8019e970
     */
    void reset();

private:
    s16 SHORT_0x0;

    //! @brief Animation state
    s16 mState; // at 0x2

    s16 SHORT_0x4;

    //! @brief Animation length
    s16 mLength; // at 0x6
    //! @brief Current animation frame
    s16 mFrame; // at 0x8
    //! @brief Animation direction
    EDirection mDirection; // at 0xC
    //! @brief Parent pane
    nw4r::lyt::Pane* mParent; // at 0x10
    //! @brief Transparency
    u8 mAlpha; // at 0x14
    //! @brief Animation start position
    EGG::Vector3f mStartPos; // at 0x18
    //! @brief Animation end position
    EGG::Vector3f mDestPos; // at 0x24
    //! @brief Node for linked list
    nw4r::ut::Node mNode; // at 0x30
};

#endif