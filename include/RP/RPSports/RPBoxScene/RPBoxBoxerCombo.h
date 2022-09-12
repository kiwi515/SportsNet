#ifndef RP_SPORTS_BOX_BOXER_COMBO_H
#define RP_SPORTS_BOX_BOXER_COMBO_H
#include "types_RP.h"

/**
 * @brief Combo for boxer's punches
 * @details The combo system rewards alternating hands when punching, and
 * increases punch strength over time. If the player either waits too long or
 * does not alternate hands, the combo will reset.
 * @customname
 */
class RPBoxBoxerCombo {
public:
    //! @brief Types of punches
    enum PunchType {
        PUNCH_LEFT,  //!< Left-handed punch
        PUNCH_RIGHT, //!< Right-handed punch
        PUNCH_MISS   //!< Missed punch
    };

private:
    //! @brief Combo strength (next hit)
    u16 mStrength; // at 0x0
    //! @brief Time left to continue combo
    f32 mContinueTimer; // at 0x4
    //! @brief Continue timer initial value (in frames)
    u16 mWindowLength; // at 0x8
    //! @brief Fraction of continue timer remaining
    f32 mWindowRemaining; // at 0xC
    //! @brief Combo length (number of punches)
    u16 mPunchCount; // at 0x10
    //! @brief Last punch
    PunchType mLastPunchType; // at 0x14

public:
    //! @address 80306c24
    RPBoxBoxerCombo();
    //! @address 80306c34
    virtual ~RPBoxBoxerCombo();

    //! @address 80306a8c
    void onPunchLand(PunchType);
    //! @address 80306b30
    void onPunchThrow(PunchType);

    //! @address 80306b64
    void calc();

    //! @address 80306bd4
    void onPunchEnd();
    //! @address 80306bfc
    void onRoundStart();

    /**
     * @brief Reset all values
     * @note Called on combo break
     */
    void reset() {
        mStrength = 0;
        mContinueTimer = 0.0f;
        mWindowLength = 0;
        mWindowRemaining = 0.0f;
        mPunchCount = 0;
        mLastPunchType = PUNCH_MISS;
    }
};

#endif