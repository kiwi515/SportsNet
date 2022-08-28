#ifndef RP_SYSTEM_RESOURCE_MANAGER_H
#define RP_SYSTEM_RESOURCE_MANAGER_H
#include "RPSysFile.h"
#include "RPSysSceneCreator.h"
#include "types_rp.h"

#include <egg/core/eggHeap.h>
#include <nw4r/ut/ut_list.h>

/**
 * @brief Engine resource manager
 * @details Responsible for pretty much all file loads from the disc,
 * and also serves as a utility for building scene/pack relative paths to files.
 * @wfuname
 */
class RPSysResourceManager {
public:
    //! @address 80187ae8
    static RPSysResourceManager* CreateInstance();
    static RPSysResourceManager* GetInstance() { return sInstance; }

    /**
     * @brief Open binary message (BMG) file
     * @address 8018783c
     */
    static void* GetMessageResource(const char* path);
    /**
     * @brief Get file from EGG archive
     * @address 80187878
     * @param sizeOut Optional output pointer for file size
     */
    static void* GetFileFromArchive(EGG::Archive* arc, const char* path,
                                    u32* sizeOut);

    /**
     * @brief Load archive from current scene's Stage directory
     * @address 801878c4
     */
    static EGG::Archive* LoadGameStageArchive(const char* path);
    /**
     * @brief Load local archive (`local.carc`) for the specified scene
     * @address 80187964
     */
    static EGG::Archive* LoadGameLocalArchive(int sceneID, EGG::Heap* heap);
    /**
     * @brief Load common archive (`common.carc`) for the specified scene
     * @address 80187a0c
     */
    static EGG::Archive* LoadGameCommonArchive(int sceneID, EGG::Heap* heap);

    /**
     * @brief Load file from DVD
     * @address 80186eb4
     * @param sizeOut Optional output pointer for file size
     */
    void* LoadFromDVD(const char* path, EGG::Heap* heap, int allocDir,
                      int* sizeOut);
    /**
     * @brief Load and decompress file
     * @address 80186fa0
     */
    void* LoadCompressed(const char* path, EGG::Heap* heap);
    /**
     * @brief Load local archive in specified directory
     * @address 801871f4
     */
    EGG::Archive* LoadLocalArchive(const char* dir);

    /**
     * @brief Get local sound path of specified scene
     * @address 80187290
     * @param bufOut Output buffer for path
     * @param bufSize Size of output buffer (unused)
     */
    void GetGameSoundLocalPath(char* bufOut, u32 bufSize, int sceneID);
    /**
     * @brief Get common sound path of specified scene
     * @address 80187300
     * @param bufOut Output buffer for path
     * @param bufSize Size of output buffer (unused)
     */
    void GetGameSoundCommonPath(char* bufOut, u32 bufSize, int sceneID);
    /**
     * @brief Get local sound path of current pack's static directory
     * @address 8018736c
     * @param bufOut Output buffer for path
     * @param bufSize Size of output buffer (unused)
     */
    void GetStaticSoundLocalPath(char* bufOut, u32 bufSize);
    /**
     * @brief Get common sound path of current pack's static directory
     * @address 801873e8
     * @param bufOut Output buffer for path
     * @param bufSize Size of output buffer (unused)
     */
    void GetStaticSoundCommonPath(char* bufOut, u32 bufSize);

    /**
     * @brief Load Mii resources (`kokeshi.carc`)
     * @address 8018744c
     */
    void LoadKokeshiArchive();
    /**
     * @brief Load static common archive
     * @address 801874b4
     */
    void LoadSharedCommonArchive();
    /**
     * @brief Load cached archives (font, BMG, static common)
     * @address 80187604
     */
    void LoadCacheArchives();
    /**
     * @brief Load sound archive
     * @address 801877dc
     */
    bool LoadSoundArchive(const char* path);

    /**
     * @brief Remove file from file list
     * @address 801877d4
     */
    void RemoveFromFileList(RPSysFile* file);

private:
    RPSysResourceManager() {
        nw4r::ut::List_Init(&LIST_0x4, offsetof(RPSysFile, mNode));
        nw4r::ut::List_Init(&mFileList, offsetof(RPSysFile, mNode));
        mPath = new char[128];
    }

    //! @address 80187aa8
    virtual ~RPSysResourceManager();

private:
    nw4r::ut::List LIST_0x4;
    nw4r::ut::List mFileList; // at 0x10
    //! @brief Buffer for constucting path
    char* mPath; // at 0x1C
    //! @brief Kokeshi (Mii) archive
    EGG::Archive* mKokeshiArc; // at 0x20
    //! @brief Message (BMG) archive
    EGG::Archive* mMessageArc; // at 0x24
    //! @brief Font archive
    EGG::Archive* mFontArc; // at 0x28
    //! @brief Pack static common archive
    EGG::Archive* mStaticCmnArc; // at 0x2C
    //! @brief Pack static local archive
    EGG::Archive* mStaticLocalArc; // at 0x30
    UNKWORD WORD_0x34;
    UNKTYPE* PTR_0x38;
    UNKWORD WORD_0x3C;

    /**
     * @brief Pack Project static paths
     * @address 803b9850
     */
    static const char* sPackStaticPaths[4];

    /**
     * @brief Static instance
     * @address 804bf4f0
     */
    static RPSysResourceManager* sInstance;
};

const char* RPSysResourceManager::sPackStaticPaths[4] = {
    "SportsStatic/", // Wii Sports
    "PartyStatic/",  // Wii Play
    "HealthStatic/", // Wii Fit
    "MusicStatic/"   // Wii Music
};

#endif