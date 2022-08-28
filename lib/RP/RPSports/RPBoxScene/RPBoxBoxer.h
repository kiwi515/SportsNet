#ifndef RP_SPORTS_BOX_BOXER_H
#define RP_SPORTS_BOX_BOXER_H
#include "types_RP.h"

/**
 * @brief Info about a boxer
 * @details This seems to be a member of of a parent "player" class, but this
 * holds all relevant information about a boxer, from health/state to even the
 * time they will get up when knocked down.
 * @customname
 */
class RPBoxBoxer {
public:
    //! @brief Boxer fighting states
    enum BoxerState {
        STATE_FIGHTING,
        STATE_KNOCKDOWN,
        STATE_STAND_UP,
        // Unique to Wii Sports Club
        STATE_AS_IS,
        STATE_FIGHT_STILL,
        STATE_T_POSE
    };

    /**
     * @brief Add damage to combo
     * @note Combo damage capped at 1.0
     */
    void addComboDmg(f32 dmg) {
        // Limited to 0.3 combo dmg per punch
        if (dmg > 0.3f)
            dmg = 0.3f;

        // Overall combo dmg is capped at 1.0
        mComboDmg += dmg;
        if (mComboDmg > 1.0f)
            mComboDmg = 1.0f;
    }

private:
    //! @brief Boxer state
    BoxerState mState; // at 0x0
    //! @brief Times this boxer has been knocked down
    u8 mKnockdownCount; // at 0x4
    u16 SHORT_0x6;
    //! @brief Boxer health
    f32 mHealth; // at 0x8
    //! @brief Boxer visual health (pie chart)
    f32 mHealthPie; // at 0xC
    //! @brief Total outgoing damage in the current round
    f32 mTotalRoundDmgDealt; // at 0x10
    //! @brief Current combo damage
    f32 mComboDmg; // at 0x14
    f32 FLOAT_0x18;
    f32 FLOAT_0x1C;
    //! @brief Strength of last incoming hit
    f32 mLastDamageTaken; // at 0x20
    //! @brief When in the count this boxer will get up
    f32 mGetUpTime; // at 0x24
    //! @brief Total outgoing damage throughout the match
    f32 mTotalMatchDmgDealt; // at 0x28
    f32 FLOAT_0x2C;

public:
    //! @address 80305b7c
    RPBoxBoxer();
    //! @address 80305b8c
    virtual ~RPBoxBoxer();

    /**
     * @brief @address 803057c0
     * @return Whether this boxer was knocked down
     */
    bool onHit(f32 damage, f32 adjustedDmg);
    //! @address 80305900
    void onUpdate();
    //! @address 80305a50
    void onGetUp();
    //! @address 80305a64
    void onRoundStart();
    //! @address 80305aa8
    void onReset();
};

#endif