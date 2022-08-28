#ifndef RP_KERNEL_SYSTEM_H
#define RP_KERNEL_SYSTEM_H
#include "types_rp.h"

#include <GX/GXFrameBuf.h>
#include <OS/OSMutex.h>
#include <egg/core/eggHeap.h>
#include <egg/core/eggTaskThread.h>
#include <nw4r/ut/ut_Color.h>

/**
 * @brief Main RP engine class
 *
 * The system class manages the low level components of the RP engine, such as
 * the different heaps, console power/reset callbacks, and setting up the
 * TV/render modes.
 *
 * One thing to note is the existence of the calendar time functions:
 * They are part of the system class in this version of the engine, they were
 * later moved into RPSysCalendar.
 *
 * (Name from Wii Fit U)
 *
 * TODO: A few functions are missing
 */
class RPSysSystem {
public:
    static RPSysSystem* getInstance() { return sInstance; }

    static EGG::Heap* getRootMem1Heap() { return sRootMem1; }
    static EGG::Heap* getRootMem2Heap() { return sRootMem2; }
    static EGG::Heap* getSystemHeap() { return sSystemHeap; }

    void* alloc(EGG::Heap* heap, u32 size, s32 align) {
        return EGG::Heap::alloc(size, align, heap);
    }

    void free(EGG::Heap* heap, void* mem) { return EGG::Heap::free(mem, heap); }

    static void initialize();                   // 80183be4
    static void create();                       // 80183ba0
    void setup0();                              // 80183a64
    void mainLoop();                            // 801838f8
    void loadUpdate(bool showLoadingText);      // 80183778
    static void setupTVMode();                  // 8018370c
    static void setupRenderMode();              // 801835dc
    u8 getTicksPerFrame() const;                // 801835d4
    f32 getModifyRatio() const;                 // 801835c0
    u16 getFBWidth() const;                     // 801835b4
    u16 getXFBHeight() const;                   // 801835a8
    void setDisplayClearColor(nw4r::ut::Color); // 80183534
    u32 getBootSceneId();                       // 8018352c
    u32 getCalendarTime32();                    // 801834bc
    u16 getCalendarTime16();                    // 80183470
    void getCalendarTime(const u32* time32, u32& wday, u32& year, u32& mon,
                         u32& mday, u32& hour); // 801833b4
    void getCalendarTime(const u16* time16, u32& year, u32& mon,
                         u32& mday);      // 80183314
    void startLoadCount();                // 80183308
    bool isLoadCountEnd() const;          // 801832f0
    void createTimeStamp();               // 801832c8
    void systemShutDown();                // 801831f0
    void setDimming(int);                 // 801831e8
    EGG::TaskThread* getNandThread();     // 801831e0
    EGG::TaskThread* getDvdThread();      // 801831d8
    EGG::TaskThread* getWc24Thread();     // 801831d0
    u32* getNandEndMessage() const;       // 801831c8
    u32* getDvdEndMessage() const;        // 801831c0
    const char* getTimeStampString();     // 801831b8
    void createFromSystemHeap();          // 80182eec
    void setupLocalSettings();            // 80182cfc
    void waitRenderModeChange();          // 80182c5c
    void setCallBack();                   // 80182c28
    static void softResetCallBack();      // 80182bb8
    static void shutdownSystemCallBack(); // 80182bac

    EGG::Heap* getResourceHeap() { return mResourceHeap; }
    EGG::Heap* getMem2SmallHeap() { return mMem2Heap500KB; }
    EGG::Heap* getMem1SmallHeap() { return mMem1Heap256B; }

private:
    RPSysSystem();          // 8018309c
    virtual ~RPSysSystem(); // 80183178

    UNKWORD WORD_0x4;
    EGG::Heap* mResourceHeap;  // at 0x8
    EGG::Heap* mMem2Heap500KB; // at 0xC
    EGG::Heap* mMem1Heap256B;  // at 0x10
    EGG::Heap* HEAP_0x14;
    EGG::Heap* HEAP_0x18; // Used to backup Heap::sCurrentHeap when changed
    OSMutex mMutex;       // at 0x1C
    EGG::TaskThread* mNandThread; // at 0x34
    EGG::TaskThread* mDvdThread;  // at 0x38
    EGG::TaskThread* mWc24Thread; // at 0x3C
    u32 mNandEndMessage;          // at 0x40
    u32 mDvdEndMessage;           // at 0x44
    u32 mWc24EndMessage;          // at 0x48
    u8 mTicksPerFrame;            // at 0x4C
    char UNK_0x4D[0x50 - 0x4D];
    f32 mFrameTime;         // 0x50 (mTicksPerFrame / 60.0f)
    u32 mLoadCount;         // at 0x54 (incremented by mTicksPerFrame)
    char* mTimeStampString; // at 0x58

    static RPSysSystem* sInstance; // 804bf4b8

    // TO-DO: Move to RPSysConfigData
    static EGG::Heap* sRootMem1;   // MEM1 arena
    static EGG::Heap* sRootMem2;   // MEM2 arena
    static EGG::Heap* sSystemHeap; // ~6MB, child of sRootMem1
};

#endif