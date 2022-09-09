#ifndef RP_SYSTEM_SAVE_DATA_MGR_H
#define RP_SYSTEM_SAVE_DATA_MGR_H
#include "IRPSysHostIOSocket.h"
#include "RPPartyCommonData.h"
#include "RPPartyPlayerData.h"
#include "RPSportsCommonData.h"
#include "RPSportsPlayerData.h"
#include "types_RP.h"

#include <types_egg.h>

/**
 * @brief RP engine save data manager
 * @details Alongside the main save data class, the manager also seems to
 * have some behavior set at compile-time based on the pack ID.
 * Due to runtime localization in the player select scene, some code
 * for handling Wii Play save data still exists in the binary.
 * @wfuname
 */
class RPSysSaveDataMgr : public IRPSysHostIOSocket {
public:
    //! @brief Banner files
    enum EBannerType {
        BANNER_REAL, //!< banner.bin
        BANNER_TEMP  //!< /tmp/banner.bin
    };

    //! @brief Status flags
    enum EStatusFlag {
        NAND_MEMORY_EXIST = (1 << 0),
        BANNER_EXIST = (1 << 1),
        SAVE_EXIST = (1 << 2),
        DISABLE_SAVING = (1 << 4),
        NAND_ACCESS_ONGOING = (1 << 8),
        WRITE_TASK_ONGOING = (1 << 9)
    };

public:
    //! @address 8018a8a4
    static RPSysSaveDataMgr* CreateInstance(EGG::Heap* heap);
    static RPSysSaveDataMgr* getInstance() { return sInstance; }

    /**
     * @brief Write both save and banner files
     * @details Used asynchronously through task threads
     * @address 801884f0
     */
    static void saveDataFunc();
    /**
     * @brief Read save file
     * @details Used asynchronously through task threads
     * @address 80188520
     */
    static void loadDataFunc();
    /**
     * @brief Create NAND entries for both save/banner
     * @details Used asynchronously through task threads
     * @address 80188528
     */
    static void createPackFileFunc();
    /**
     * @brief Check if the NAND has enough free space
     * @details Used asynchronously through task threads
     * @address 801885c0
     */
    static void existNandMemoryFunc();
    /**
     * @brief Validate that both the save/banner exist by checking their
     * filetype
     * @details Used asynchronously through task threads
     * @address 801885c8
     */
    static void existPackFileFunc();

    /**
     * @brief Write banner file to NAND (temp/real)
     * @address 801886ac
     */
    void saveBanner(EBannerType bannerType);

    /**
     * @brief Read NAND save data into raw save, then construct RP save file
     * @address 8018877c
     */
    void loadSync();
    /**
     * @brief Save RP save file into raw save, then write raw save to NAND
     * @address 80188868
     */
    void saveSync();

    /**
     * @brief Create temp banner file on NAND (`/tmp/banner.bin`)
     * @address 8018895c
     */
    void createBannerFile();
    /**
     * @brief Check if the NAND has enough free space
     * @address 80188a60
     */
    void existNandMemorySync();
    /**
     * @brief Try to display "Continue without saving?" message
     * @address 80188b04
     */
    void continueNoSaveProc();
    /**
     * @brief Build banner.bin file
     * @details TPL exists on disc, text in BMG
     * @address 80188bd4
     */
    void buildBannerBin();
    /**
     * @brief Try to display "Unable to save" message
     * @details Calls continueNoSaveProc
     * @address 80188d60
     */
    void unableToSaveProc();
    /**
     * @brief Finishes NAND access by clearing the flag
     * @address 80188e54
     */
    void finishNandAccess();

    /**
     * @brief Empty NAND block count the game requires to store save data
     * @details Compile-time constant set to 2 (250kb)
     * @address 80188e64
     */
    u32 getUserBlockSize() const;
    /**
     * @brief Empty NAND block count the game requires to store save data
     * @details Calculated dynamically from the save file size,
     * but still yields same result (2 blocks)
     * @address 80188e6c
     */
    u32 calcUserBlockSize() const;

    //! @address 80188e8c
    s32 getErrorCode() const;
    //! @address 80188e94
    u32 getNandCheckAnswer() const;

    /**
     * @brief Toggle ability to save
     * @address 80188e9c
     */
    void setSaveDisable(bool disable);

    /**
     * @brief Check manager status flags for save-related errors
     * @address 80188ec4
     */
    bool isSaveFileBroken() const;
    /**
     * @brief Check save data for errors
     * @typo
     * @address 80188efc
     */
    bool isErrorOccured() const;
    /**
     * @brief Check for free space on NAND to store save data
     * @address 80188f04
     */
    bool isNandMemoryExist() const;
    /**
     * @brief Check for existence of banner/save files
     * @address 80188f10
     */
    bool isPackFileExist() const;
    //! @brief Is the manager currently done with the NAND?
    bool isNandAccessDone() const; // 80188f30
    //! @brief Check for NAND access/write task
    bool isIdle() const; // 80188f44

    //! @brief Requests saveDataFunc on the NAND thread
    //! @return Whether the task request was successful
    bool saveAsync(); // 80188f64
    //! @brief Requests loadDataFunc on the NAND thread
    //! @return Whether the task request was successful
    bool loadAsync(); // 80189040

    //! @brief Attempts to write save/banner files if the scene is idle
    bool writePackFileSync(); // 801890e0
    //! @brief Attempts to delete save/banner files if the scene is idle
    bool deletePackFileSync(); // 8018915c

    //! @brief Tries to create the banner/save files asynchronously, by using
    //! the NAND thread
    //! @return Whether the task request was successful
    bool createPackFileAsync(); // 80189234
    //! @brief Asynchronously checks if the NAND has enough space for the save
    //! file, by using the NAND thread
    //! @return Whether the task request was successful
    bool existNandMemoryAsync(); // 801892d4
    //! @brief Asynchronously checks if the banner/save files exist on the NAND
    //! @return whether the task request was successful
    bool existPackFileAsync(); // 80189374
    //! @brief Checks if the banner/save files exist on the NAND
    bool existPackFileSync(); // 80189414

    //! @address 80189534
    RPPartyCommonData getPartyCommonData() const;

    //! @address 8018962c
    void setPartyPlayerData(const RPPartyPlayerData* playerData, u32 id);
    //! @address 80189720
    RPPartyPlayerData getPartyPlayerData(u32 id) const;

    //! @address 80189820
    void setSportsCommonData(const RPSportsCommonData* cmnData);
    //! @address 80189c10
    RPSportsCommonData getSportsCommonData() const;

    //! @address 80189ea0
    void setSportsPlayerData(const RPSportsPlayerData* playerData, u32 id);
    //! @address 8018a39c
    RPSportsPlayerData getSportsPlayerData(u32 id) const;

private:
    //! @address 801883c0
    RPSysSaveDataMgr(EGG::Heap* heap);
    //! @address 80188368
    virtual ~RPSysSaveDataMgr();

private:
    //! @brief Heap in which this object was allocated
    EGG::Heap* mParentHeap; // at 0x4
    //! @brief Flags regarding the manager's status
    u32 mStatus; // at 0x8
    //! @brief NAND error code
    s32 mNandErrorCode; // at 0xC
    UNKWORD WORD_0x10;
    //! @brief NAND check answer
    u32 mNandCheckAnswer; // at 0x14
    //! @brief Size of the raw save file (`RPSports.dat`)
    u32 mSaveFileSize; // at 0x18
    //! @brief Banner.bin size
    u32 mBannerBinSize; // at 0x1C
    //! @brief Save file size aligned some way
    //! @details Used to calculate no. of empty blocks needed (WiiWare support?)
    UNKWORD INT_0x20;
    //! @brief Buffer containing banner.bin
    void* mBannerBin; // at 0x24
    //! @brief Raw save file data (RPSports.dat)
    void* mRawSaveFile; // at 0x28
    //! @brief RP save file class
    RPSysSaveData* mRPSaveFile; // at 0x2C

    /**
     * @brief Static instance
     * @address 804bf508
     */
    static RPSysSaveDataMgr* sInstance;
};

#endif