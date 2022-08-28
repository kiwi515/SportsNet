#ifndef RP_SPORTS_BOW_RESOURCE_MANAGER_H
#define RP_SPORTS_BOW_RESOURCE_MANAGER_H
#include "IRPSysHostIOSocket.h"
#include "types_RP.h"

/**
 * @brief Bowling scene resource manager
 * @customname
 */
class RPBowResourceManager : public IRPSysHostIOSocket {
public:
    //! @address 80320ea4
    static void CreateInstance();
    //! @address 80320e60
    static void DestroyInstance();
    static RPBowResourceManager* GetInstance() { return sInstance; }

    RPBowResourceManager() : mExcelGlobal(NULL) {}

    //! @address 80320da8
    virtual ~RPBowResourceManager();

    /**
     * @brief Sets up all bowling resources
     * @address 80320e00
     */
    void LoadResource();
    /**
     * @brief Get specified file from the scene common archive
     * @address 80320d9c
     */
    void* GetFileFromCmnArchive(const char* path);

private:
    //! @brief EXBIN globals (`BowExcelGlobal.bin`)
    void* mExcelGlobal; // at 0x0
    //! @brief Scene common archive
    void* mCmnArchive; // at 0x4
    //! @brief Scene local archive
    void* mLocalArchive; // at 0x8

    /**
     * @brief Static instance
     * @address 804bf9a8
     */
    static RPBowResourceManager* sInstance;
};

#endif