#ifndef RP_SPORTS_COMMON_DATA_H
#define RP_SPORTS_COMMON_DATA_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Wii Sports save file common data
 * @details Includes everything that isn't tied to a specific player
 * @note Not a packed structure, this is an abstraction of the binary format
 * @customname
 */
class RPSportsCommonData {
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

    /**
     * @brief Indices for the common save data bitfield
     * @note Must be used with getTrainingUnlock, or getBitFlag(15 + bit)
     */
    enum ETrainingGames {
        BIT_BOX_MITUCHI,  //!< Throwing Punches
        BIT_BOX_TAMAYOKE, //!< Dodging
        BIT_BOX_SANDBAG,  //!< Working the Bag

        BIT_GOL_TARGET,  //!< Target Practice
        BIT_GOL_NEARPIN, //!< Hitting the Green
        BIT_GOL_ONEPAT,  //!< Putting

        BIT_BOW_GATETOSHI,  //!< Spin Control
        BIT_BOW_NAGITAOSHI, //!< Power Throws
        BIT_BOW_SPAREGET,   //!< Picking Up Spares

        BIT_BSB_RENZOKU,  //!< Batting Practice
        BIT_BSB_UCHIWAKE, //!< Swing Control
        BIT_BSB_HOMERUN,  //!< Hitting Home Runs

        BIT_TNS_KABEUCHI,  //!< Target Practice
        BIT_TNS_NERAUCHII, //!< Timing Your Swing
        BIT_TNS_RENZOKU,   //!< Returning Balls
    };

public:
    RPSportsCommonData(); // 8018ad34

    /**
     * @brief Write data
     * @address 8018a90c
     */
    void write(EGG::RamStream* stream) const;
    /**
     * @brief Read data
     * @address 8018a9d0
     */
    void read(EGG::RamStream* stream);

    /**
     * @brief Get Mii history fields
     * @address 8018abe0
     * @param[out] miiIdxOut For storing mii index
     * @param[out] radioSensOut For storing radio sensitivity
     * @param[in] numPlayers Player count
     * @param[in] playerIdx Index into history
     */
    void getMiiHistory(s8* miiIdxOut, u8* radioSensOut, u32 numPlayers,
                       u32 playerIdx) const;
    /**
     * @brief Set Mii history fields
     * @address 8018ab60
     * @param[in] miiIdx Mii index
     * @param[in] radioSens Radio sensitivity
     * @param[in] numPlayers Player count
     * @param[in] playerIdx Index into history
     */
    void setMiiHistory(const s8* miiIdx, const u8* radioSens, u32 numPlayers,
                       u32 playerIdx);

    /**
     * @brief Check training unlock
     * @note Training game bits start at 15, so this is equivalent to
     * getBitFlag(15 + i)
     * @see ETrainingGame
     * @address 8018aa90
     * @param i Training game
     */
    bool getTrainingUnlock(u8 i) const;
    /**
     * @brief Check training unlock
     * @note Training game bits start at 15, so this is equivalent to
     * setBitFlag(15 + i, val)
     * @see ETrainingGame
     * @address 8018aab8
     * @param i Training game
     * @param val New value
     */
    bool setTrainingUnlock(u8 i, bool val);

    //! @address 8018aaf0
    bool getBitFlag(u8 i) const;
    //! @address 8018ab10
    bool setBitFlag(u8 i, bool val);

    //! @address 8018ab40
    u16 getLastFitnessTestTime() const;
    //! @address 8018ab40
    void setLastFitnessTestTime(u16 time);

    //! @address 8018ab50
    u8 getTotalFitnessTests() const;
    //! @address 8018ab58c
    void setTotalFitnessTests(u8 num);

    /**
     * @brief Reset all data
     * @address 8018ac64
     */
    void reset();

private:
    //! @brief Mii History for every possible amount of players
    MiiHistory mHistory[1 + 2 + 3 + 4]; // at 0x0

    //! @brief Total fitness tests across all Miis
    u8 mTotalFitnessTests; // at 0x46
    //! @brief Last fitness test by any Mii
    u16 mLastFitnessTestTime; // at 0x48

    u16 SHORT_0x4A;
    u8 BYTE_0x4C;

    //! @brief Common save data bitfield, used primarily for training games
    u32 mBitfield;

    u32 WORD_0x54;
};

#endif