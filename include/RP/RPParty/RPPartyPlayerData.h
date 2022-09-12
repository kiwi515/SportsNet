#ifndef RP_PARTY_PLAYER_DATA_H
#define RP_PARTY_PLAYER_DATA_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Wii Play save file player list entry
 * @note Not a packed structure, this is an abstraction of the binary format
 * @customname
 */
class RPPartyPlayerData {
public:
    //! @brief For mFlags
    enum EPlayerFlag { FLAG_ON_PLAYER_LIST = (1 << 1) };

    //! @brief Bit indices for the game unlock bitfield
    enum EGameID {
        GAME_DUC, //!< Shooting Range
        GAME_WLY, //!< Find Mii
        GAME_PNP, //!< Table Tennis
        GAME_BOM, //!< Pose Mii
        GAME_HKY, //!< Laser Hockey
        GAME_BIL, //!< Billiards
        GAME_FSH, //!< Fishing
        GAME_COW, //!< Charge!
        GAME_TNK, //!< Tanks!

        GAME_MAX
    };

    //! @brief Cutscene IDs for mCutscenesSeen
    enum ECutsceneID {
        CUTSCENE_0,           //!< Unused
        CUTSCENE_ALL_BRONZE,  //!< All bronze medals
        CUTSCENE_ALL_SILVER,  //!< All silver medals
        CUTSCENE_ALL_GOLD,    //!< All gold medals
        CUTSCENE_ALL_PLATINUM //!< All platinum medals
    };

public:
    //! @address 8018d6d0
    void setDebutTime(RPTime32 time);
    //! @address 8018d6d8
    RPTime32 getDebutTime() const;

    //! @address 8018d6e0
    void setUniqueID(const u8* id);
    //! @address 8018d724
    void getUniqueID(u8* idOut) const;

    //! @address 8018d768
    void setOnPlayerList(bool onList);
    //! @address 8018d790
    bool isOnPlayerList() const;

    /**
     * @brief Reset all data
     * @address 8018d79c
     */
    void reset();

private:
    //! @brief Length of high score list
    static const u32 NUM_SCORES = 5;

    //! @brief Player list entry flags
    u32 mFlags; // at 0x0
    //! @brief Mii unique ID
    u8 mUniqueID[8]; // at 0x4
    //! @brief Time player was added to the player list
    //! @note Referred to as the player's "debut" on the message board
    RPTime32 mDebutTime; // at 0xC
    //! @brief Top 5 scores in each game
    s32 mTopScores[GAME_MAX][NUM_SCORES]; // at 0x10
    //! @brief Player's medal in every game
    u8 mMedals[GAME_MAX]; // at 0xC4
    //! @brief Bitfield marking medal cutscenes as seen
    u8 mCutscenesSeen; // at 0xCD
};

#endif