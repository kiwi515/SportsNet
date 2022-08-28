#ifndef RP_SPORTS_BOX_BOXER_STATUS_H
#define RP_SPORTS_BOX_BOXER_STATUS_H
#include "types_RP.h"

/**
 * @brief State of a boxer's energy
 * @details Depletes as you whiff punches and/or get blocked.
 * @note The code that allows the energy to deplete/regen is locked behind
 * global flags, so the entire feature goes unused. It can be seen in some
 * prerelease footage.
 * @customname
 */
class RPBoxBoxerEnergy {
public:
    enum EnergyState {
        ENERGY_NORMAL, //!< Regular state
        ENERGY_STUNNED //!< Stunned
    };

    enum EnergyFlag { FLAG_STUNNED = (1 << 0) };

    EnergyState mState; // at 0x0
    f32 FLOAT_0x4;
    //! @brief Energy remaining
    f32 mEnergy; // at 0x8
    f32 FLOAT_0xC;
    f32 FLOAT_0x10;
    u16 mFlags; // at 0x14

public:
    //! @address 80305e0c
    RPBoxBoxerEnergy();
    //! @address 80305e1c
    virtual ~RPBoxBoxerEnergy();

    /**
     * @brief Check if the energy is low enough to stun
     * @address 80305bcc
     */
    bool shouldStun() const;

    /**
     * @brief Regenerate energy
     * @details Regen differs based on boxer state
     * @address 80305be8
     */
    void calcRegen(f32 baseRegen, u32 boxerState);

    /**
     * @brief Deplete energy
     * @details Energy depletes most on whiffed punches
     * @note Always disabled due to global flags
     * @param flag Effectively toggles option, however a global flag overrides
     * this
     * @param resetEnergy Reset energy to 1.0
     */
    void calcDeplete(u32 flag, bool resetEnergy);
};

#endif