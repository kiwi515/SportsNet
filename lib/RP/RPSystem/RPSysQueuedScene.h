#ifndef RP_SYSTEM_QUEUED_SCENE_H
#define RP_SYSTEM_QUEUED_SCENE_H
#include "types_rp.h"

#include <types_egg.h>

/**
 * @brief Tracks the next scene that will be loaded
 * @details Used commonly by the menu scene to determine whether the player
 * select scene should be in its regular/training/fitness state.
 * @customname
 */
class RPSysQueuedScene {
public:
    //! @address 80187ba0
    static RPSysQueuedScene* CreateInstance(EGG::Heap* heap);
    static RPSysQueuedScene* getInstance() { return sInstance; }

    /**
     * @brief Reset the queued scene to -1
     * @address 80187b94
     */
    void Reset();

private:
    RPSysQueuedScene(EGG::Heap* heap) : mParentHeap(heap), mSceneID(-1) {}

    //! @address 80187b54
    virtual ~RPSysQueuedScene();

private:
    //! @brief Heap in which this object was allocated
    EGG::Heap* mParentHeap; // at 0x4
    //! @brief ID of queued scene (-1 = none)
    s32 mSceneID; // at 0x8

    /**
     * @brief Static instance
     * @address 804bf4f8
     */
    static RPSysQueuedScene* sInstance;
};

#endif