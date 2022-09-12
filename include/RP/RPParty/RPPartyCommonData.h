#ifndef RP_PARTY_COMMON_DATA_H
#define RP_PARTY_COMMON_DATA_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Wii Play save file common data
 * @details Includes everything that isn't tied to a specific player
 * @note Not a packed structure, this is an abstraction of the binary format
 * @customname
 */
class RPPartyCommonData {
public:
    /**
     * @brief Structure used to allow players' Miis to be automatically
     * selected.
     * @details The Mii's player list index is kept alongside information
     * identifying the remote used, so that Mii can be chosen automatically when
     * applicable.
     */
    struct MiiHistory {
        //! @brief Previously selected Mii (Index into player list)
        //! @note -1 if unused
        s8 mPrevMiiIdx; // at 0x0

        //! @brief Set by WPADGetRadioSensitivity
        //! @details Used to identify the remote previously used
        u8 mRadioSensitivity[6]; // at 0x1
    };

    //! @brief Bit indices for the game unlock bitfield
    enum EGameUnlock {
        GAME_DUC, //!< Shooting Range
        GAME_WLY, //!< Find Mii
        GAME_PNP, //!< Table Tennis
        GAME_BOM, //!< Pose Mii
        GAME_HKY, //!< Laser Hockey
        GAME_BIL, //!< Billiards
        GAME_FSH, //!< Fishing
        GAME_COW, //!< Charge!
        GAME_TNK  //!< Tanks!
    };

    //! @brief Bit indices for the dialog seen bitfield
    enum EDialogSeen {
        DIALOG_WELCOME,          //!< Game is played for first time
        DIALOG_STAGE_TWO,        //!< Stage two is unlocked
        DIALOG_STAGE_THREE,      //!< Stage three is unlocked
        DIALOG_STAGE_FOUR,       //!< Stage four is unlocked
        DIALOG_STAGE_FIVE,       //!< Stage five is unlocked
        DIALOG_STAGE_SIX,        //!< Stage six is unlocked
        DIALOG_STAGE_SEVEN,      //!< Stage seven is unlocked
        DIALOG_STAGE_EIGHT,      //!< Stage eight is unlocked
        DIALOG_FINAL_STAGE,      //!< Stage nine (final stage) is unlocked
        DIALOG_WII_REMOTE_MASTER //!< All stages are completed
    };

public:
    /**
     * @brief Check if a game has been unlocked
     * @address 8018d6ac
     */
    bool isGameUnlock(u32 id) const;

private:
    //! @brief Mii History for every possible amount of players
    MiiHistory mHistory[1 + 2]; // at 0x0
    //! @brief Number of players added to the player list on the current date
    //! @todo Why is this counted?
    u8 mPlayersAddedToday; // at 0x15
    //! @brief Date last player was added to player list
    //! @details Used to increment mAddedPlayersToday.
    RPTime16 mLastDatePlayerAdded; // at 0x16
    //! @brief Bitfield marking games as unlocked
    u32 mGameUnlockBitfield; // at 0x18
    //! @brief Bitfield marking dialog windows as seen
    u32 mDialogSeenBitfield; // at 0x1C
};

#endif