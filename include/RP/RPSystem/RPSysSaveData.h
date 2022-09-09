#ifndef RP_SYSTEM_SAVE_DATA_H
#define RP_SYSTEM_SAVE_DATA_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Generic structure to hold RP engine save data
 * @details While this structure is generic and can support multiple Pack
 * Project games, it seems that some of its behavior is set at compile time
 * rather than using RPSysProjectLocal.
 * @wfuname
 */
class RPSysSaveData {
public:
    //! @brief Potential errors in the save data
    enum ESaveError {
        SAVE_BAD_HI_MAGIC = (1 << 0), //!< Missing 'RPSP'
        SAVE_BAD_LO_MAGIC = (1 << 1), //!< Missing '0000'
        SAVE_BAD_CHECKSUM = (1 << 2)  //!< Checksum mismatch
    };

public:
    /**
     * @brief Size of save file
     * @address 8018bf54
     */
    static u32 getFileSize();

    //! @address 8018ad34
    RPSysSaveData();

    /**
     * @brief Write save to stream
     * @address 8018ad70
     * @param rawSave Binary save, needed to calculate checksum
     */
    void write(EGG::RamStream* stream, const void* rawSave) const;
    /**
     * @brief Read save from stream
     * @address 8018b0e4
     * @param rawSave Binary save, needed to calculate checksum
     */
    void read(EGG::RamStream* stream, const void* rawSave);

    //! @address 8018c32c
    RPPartyCommonData* getPartyCommonData() const;

    //! @address 8018c334
    void setPartyPlayerData(const RPPartyPlayerData* playerData, u32 id);
    //! @address 8018c40c
    RPPartyPlayerData* getPartyPlayerData(u32 id) const;

    //! @address 8018c41c
    void setSportsCommonData(const RPSportsCommonData* cmnData);
    //! @address 8018c684
    RPSportsCommonData* getSportsCommonData() const;

    //! @address 8018c68c
    void setSportsPlayerData(const RPSportsPlayerData* playerData, u32 id);
    //! @address 8018cb6c
    RPSportsPlayerData* getSportsPlayerData(u32 id) const;

    /**
     * @brief Check save data validity
     * @typo
     * @address 8018cb7c
     */
    bool isErrorOccured() const;

private:
    //! @brief Flags regarding the status of the data
    u32 mErrors; // at 0x0
    //! @brief Wii Sports common save data
    RPSportsCommonData* mSportsCmnData; // at 0x4
    //! @brief Wii Sports player list (100 entries)
    RPSportsPlayerData* mSportsPlayerList; // at 0x8
    //! @brief Wii Play common save data
    RPPartyCommonData* mPartyCmnData; // at 0xC
    //! @brief Wii Play player list (100 entries)
    RPPartyPlayerData* mPartyPlayerList; // at 0x10

    UNKWORD WORD_0x14;
    UNKWORD WORD_0x18;
    UNKWORD WORD_0x1C;
    UNKWORD WORD_0x20;
    UNKWORD WORD_0x24;
};

#endif