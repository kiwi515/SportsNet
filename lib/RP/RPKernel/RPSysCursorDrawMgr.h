#ifndef RP_KERNEL_CURSOR_DRAW_MGR_H
#define RP_KERNEL_CURSOR_DRAW_MGR_H
#include "IRPSysHostIOSocket.h"
#include "types_RP.h"

#include <egg/math/eggVector.h>
#include <egg/types_egg.h>

/**
 * @brief Cursor manager and renderer
 */
class RPSysCursorDrawMgr : public IRPSysHostIOSocket {
public:
    /**
     * @brief Player ID
     */
    enum EPlayer {
        PLAYER_1,
        PLAYER_2,
        PLAYER_3,
        PLAYER_4,

        PLAYER_MAX
    };

    /**
     * @brief Cursor state
     */
    enum ECursorType { CURSOR_DISABLED, CURSOR_1, CURSOR_ACTIVE };

public:
    //! @address 801a0230
    static RPSysCursorDrawMgr* CreateInstance(EGG::Heap* heap);

    static RPSysCursorDrawMgr* GetInstance() { return sInstance; }

    //! @address 8019ede8
    RPSysCursorDrawMgr(EGG::Heap* heap);
    //! @address 8019ed74
    virtual ~RPSysCursorDrawMgr(); // at 0x8

    void startDpdCheck();
    void createActiveCursor();

private:
    //! @brief Parent heap
    EGG::Heap* mHeap; // at 0x4
    u32 mFlags;       // at 0x8

    u32 WORD_0xC;
    u32 WORDS_0x10[PLAYER_MAX];
    s32 WORDS_0x20[PLAYER_MAX];

    //! @brief Cursor state
    ECursorType mCursorTypes[PLAYER_MAX]; // at 0x30
    //! @brief Cursor rotation (in radians)
    f32 mCursorRotation[PLAYER_MAX]; // at 0x40
    //! @brief Current cursor wait time
    u32 mCursorWaitTimes[PLAYER_MAX]; // at 0x50
    //! @brief Wait time required before the cursor is re-enabled after using
    //! the D-Pad
    u32 mCursorMinWaitTime; // at 0x60
    //! @brief Disabled cursor transparency
    u8 mDisabledCursorAlpha; // at 0x64
    //! @brief Cursor position
    EGG::Vector2f mCursorPosition[PLAYER_MAX]; // at 0x68
    //! @brief Cursor effect
    RPSysEffect* mCursorEff[PLAYER_MAX]; // at 0x88
    //! @brief Cursor trail effect
    RPSysEffect* mCursorBlurEff[PLAYER_MAX]; // at 0x98
    //! @brief Cursor shadow
    RPSysEffect* mCursorShadowEff[PLAYER_MAX]; // at 0xA8

    /**
     * @brief Default cursor position
     * @address 804bf590
     */
    static EGG::Vector2f sDefaultCursorPosition;

    /**
     * @brief Static instance
     * @address 804bf598
     */
    static RPSysCursorDrawMgr* sInstance;
};

#endif