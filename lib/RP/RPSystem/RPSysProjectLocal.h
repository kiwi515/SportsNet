#ifndef RP_SYSTEM_PROJECT_LOCAL_H
#define RP_SYSTEM_PROJECT_LOCAL_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Runtime-access regional localization using compile-time settings.
 * @wfuname
 */
class RPSysProjectLocal {
public:
    //! @brief Measurement system (mostly used for string formatting)
    enum EMeasureSystem {
        RP_SYS_0,
        RP_SYS_IMPERIAL,
        RP_SYS_2,
    };

    //! @brief Pack Project game ID
    enum EPackID {
        RP_SPORTS_PACK,
        RP_PARTY_PACK,
        RP_HEALTH_PACK,
        RP_MUSIC_PACK,
        RP_ALLPACK
    };

    //! @brief Region, used for both locale and language
    enum ERegion {
        RP_ENGLISH_GB,
        RP_FRENCH,
        RP_GERMAN,
        RP_ITALIAN,
        RP_SPANISH,
        RP_ENGLISH_NL,
        RP_JAPANESE,
        RP_ENGLISH_US
    };

    //! @brief Storage of sound archives (NAND suggests RP supports WiiWare?)
    enum EStorage {
        RP_STORAGE_MEM,
        RP_STORAGE_NAND,
        RP_STORAGE_DVD,
    };

public:
    //! @address 801863a4
    static RPSysProjectLocal* CreateInstance(EGG::Heap* heap);
    static RPSysProjectLocal* getInstance() { return sInstance; }

    //! @address 80186234
    void setLanguage(ERegion lang);
    //! @address 8018623c
    void setLocale(ERegion locale);

    /**
     * @brief Concatenate locale directory to input path
     * @address 80186244
     */
    void appendLocalDirectory(char* path, const char* prefix);

private:
    RPSysProjectLocal(EGG::Heap* heap)
        : mParentHeap(heap),
          mMeasureSystem(RP_SYS_IMPERIAL),
          mPackID(RP_SPORTS_PACK),
          mLocale(RP_ENGLISH_US),
          mLanguage(RP_ENGLISH_US),
          WORD_0x18(0),
          mSndStorage(RP_STORAGE_MEM) {}

    //! @address 80186364
    virtual ~RPSysProjectLocal();

    //! @brief Heap in which this object was allocated
    EGG::Heap* mParentHeap; // at 0x4
    //! @brief For formatting decimal numbers, using feet vs meters, etc.
    u32 mMeasureSystem; // at 0x8
    //! @brief Pack Project game ID
    u32 mPackID; // at 0xC
    //! @brief Controls what directory is used for regional files, etc.
    u32 mLocale; // at 0x10
    //! @brief Seems to be unused, set alongside locale
    u32 mLanguage; // at 0x14
    //! @brief Audio related, only used by code leftover from Wii Play
    UNKWORD WORD_0x18;
    //! @brief Where audio archives are stored (DVD, NAND, memory)
    u32 mSndStorage;

    /**
     * Static instance
     * @address 804bf4e0
     */
    static RPSysProjectLocal* sInstance;
};

#endif