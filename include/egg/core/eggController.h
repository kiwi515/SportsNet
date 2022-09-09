#ifndef EGG_CORE_CONTROLLER_H
#define EGG_CORE_CONTROLLER_H
#include "eggBitFlag.h"
#include "eggBuffer.h"
#include "eggDisposer.h"
#include "eggMatrix.h"
#include "eggVector.h"
#include "types_egg.h"
#include "ut_list.h"

#include <RevoSDK/KPAD/KPAD.h>
#include <RevoSDK/PAD/Pad.h>

namespace EGG {
enum eCoreDevType { cDEV_0xFD = -3 };

enum eButtonType {
    cCORE_FSSTICK_NONE = 0x0000,
    cCORE_FSSTICK_LEFT = 0x0001,
    cCORE_FSSTICK_RIGHT = 0x0002,
    cCORE_FSSTICK_DOWN = 0x0004,
    cCORE_FSSTICK_UP = 0x0008,
    cCORE_FSSTICK_PLUS = 0x0010,
    cCORE_FSSTICK_2 = 0x0100,
    cCORE_FSSTICK_1 = 0x0200,
    cCORE_FSSTICK_B = 0x0400,
    cCORE_FSSTICK_A = 0x0800,
    cCORE_FSSTICK_MINUS = 0x1000,
    cCORE_FSSTICK_HOME = 0x8000,
    cCORE_FSSTICK_BUTTONS = 0xF0000
};

struct CoreStatus {
    CoreStatus() {}
    ~CoreStatus() {}

    f32 getFSStickX() const { return mFSStickX; }
    f32 getFSStickY() const { return mFSStickY; }
    bool isFreestyle() const { return CHAR_0x5C == 1; }

    Vector3f getAccel() const { return mAccel; }

    u32 getFSStickButton();

    u32 hold;        // at 0x0
    u32 trig;        // at 0x4
    u32 release;     // at 0x8
    Vector3f mAccel; // at 0xC
    char UNK_0x18[0x5C - 0x18];
    s8 CHAR_0x5C;
    f32 mFSStickX; // at 0x60
    f32 mFSStickY; // at 0x64
    char UNK_0x68[0x84 - 0x68];
};

class CoreController {
public:
    virtual void setPosParam(f32 f1, f32 f2) {
        KPADSetPosParam(mChannel, f1, f2);
    } // at 0x8
    virtual void setHoriParam(f32 f1, f32 f2) {
        KPADSetHoriParam(mChannel, f1, f2);
    } // at 0xC
    virtual void setDistParam(f32 f1, f32 f2) {
        KPADSetDistParam(mChannel, f1, f2);
    } // at 0x10
    virtual void setAccParam(f32 f1, f32 f2) {
        KPADSetAccParam(mChannel, f1, f2);
    }                                    // at 0x14
    virtual void beginFrame(PADStatus*); // at 0x18
    virtual void endFrame();             // at 0x1C

    CoreController();
    ~CoreController() {}

    Vector3f getAccel() const { return STATUS_0x14.getAccel(); }
    void setChannel(s32 chan) { mChannel = chan; }
    s32 getChannel() const { return mChannel; }
    bool isStable(u8 c) const { return ((mFlags & c) == c); }

    void sceneReset() {
        VEC3_0x858.mCoords.x = 0.0f;
        VEC3_0x858.mCoords.y = 0.0f;
        VEC3_0x858.mCoords.z = 0.0f;

        mPostureMtx.makeIdentity();
        M34_0x8A8.makeIdentity();

        WORD_0x8DC = 10;
        FLOAT_0x8EC = 0.13f;

        FLOATS_0x8F0[0] = 0.0f;
        FLOATS_0x8F0[1] = 0.0f;
        FLOATS_0x8F0[2] = 0.0f;

        mFlags = 0;
        WORDS_0x8E0[0] = 0;
        WORDS_0x8E0[1] = 0;
        WORDS_0x8E0[2] = 0;
        WORD_0x864 = 0;
        WORD_0x86C = 0;
        BYTE_0x868 = 0;
        BYTE_0x870 = 0x20;
        BYTE_0x871 = 0x1F;

        stopRumbleMgr();
    }

    u32 getButtonHold() const { return mButtonHold; }
    u32 getButtonTrigger() const { return mButtonTrigger; }
    u32 getButtonRelease() const { return mButtonRelease; }

    void createRumbleMgr(u8);
    void startPatternRumble(const char*, int, bool);
    void startPowerFrameRumble(f32, int, bool);
    void stopRumbleMgr();
    CoreStatus* getCoreStatus(int);

    void calc_posture_matrix(Matrix34f&, bool);
    void stopMotor();

public:
    s32 mChannel;       // at 0x4
    u32 mButtonHold;    // at 0x8
    u32 mButtonTrigger; // at 0xC
    u32 mButtonRelease; // at 0x10
    CoreStatus STATUS_0x14;
    CoreStatus STATUS_0x98;
    CoreStatus STATUS_0x11C;
    CoreStatus STATUS_0x1A0;
    CoreStatus STATUS_0x224;
    CoreStatus STATUS_0x2A8;
    CoreStatus STATUS_0x32C;
    CoreStatus STATUS_0x3B0;
    CoreStatus STATUS_0x434;
    CoreStatus STATUS_0x4B8;
    CoreStatus STATUS_0x53C;
    CoreStatus STATUS_0x5C0;
    CoreStatus STATUS_0x644;
    CoreStatus STATUS_0x6C8;
    CoreStatus STATUS_0x74C;
    CoreStatus STATUS_0x7D0;
    int mKPADReadLength; // at 0x854
    Vector3f VEC3_0x858;
    UNKWORD WORD_0x864;
    u8 BYTE_0x868;
    UNKWORD WORD_0x86C;
    u8 BYTE_0x870;
    u8 BYTE_0x871;
    struct ControllerRumbleMgr* mRumbleMgr; // at 0x874
    Matrix34f mPostureMtx;                  // at 0x878
    Matrix34f M34_0x8A8;
    u8 mFlags; // at 0x8D8
    UNKWORD WORD_0x8DC;
    UNKWORD WORDS_0x8E0[3];
    f32 FLOAT_0x8EC;
    f32 FLOATS_0x8F0[3];
};

class NullController : CoreController {
public:
    NullController() {}
    ~NullController() {}

private:
};

struct ControllerRumbleUnit {
    ControllerRumbleUnit() : PTR_0x4(NULL), PTR_0x8(NULL), WORD_0xC(0) {
        FLOAT_0x14 = 0.0f;
        FLOAT_0x10 = 0.0f;

        mFlags.makeAllZero();
    }

    virtual ~ControllerRumbleUnit() {} // at 0x8

    void startPattern(const char*, int);
    void startPowerFrame(f32, int);
    f32 calc();

    void setFlags(u8 mask) { mFlags.set(mask); }
    void clrFlags(u8 mask) { mFlags.reset(mask); }
    bool tstFlags(u8 mask) { return mFlags.on(mask); }

    const char* PTR_0x4;
    const char* PTR_0x8;
    UNKWORD WORD_0xC;
    f32 FLOAT_0x10;
    f32 FLOAT_0x14;
    TBitFlag<u8> mFlags;  // at 0x18
    nw4r::ut::Node mNode; // at 0x1C
    char UNK_0x24[0x28 - 0x24];
};

class ControllerRumbleMgr {
public:
    ControllerRumbleMgr() : mController(NULL) {
        nw4r::ut::List_Init(&LIST_0x4, offsetof(ControllerRumbleUnit, mNode));
        nw4r::ut::List_Init(&LIST_0x10, offsetof(ControllerRumbleUnit, mNode));
    }

    virtual ~ControllerRumbleMgr() {} // at 0x8

    void createUnit(u8, CoreController*);
    void startPattern(const char*, int, bool);
    void startPowerFrame(f32, int, bool);
    void stop();
    void calc();

    ControllerRumbleUnit* getUnitFromList(bool);

private:
    nw4r::ut::List LIST_0x4;
    nw4r::ut::List LIST_0x10;
    CoreController* mController; // at 0x1C
};

class CoreControllerMgr {
public:
    // From Wii Fit U
    struct CoreControllerConnectArg {
        s32 LONG_0x0;
        s32 LONG_0x4;
    };
    typedef void (*ConnectCallback)(CoreControllerConnectArg*);

    typedef CoreController* (*CoreControllerFactory)();

    class T__Disposer : Disposer {
    public:
        T__Disposer() {}
        virtual ~T__Disposer(); // at 0x8
    };

private:
    T__Disposer mDisposer; // at 0x0

public:
    static CoreControllerMgr* getInstance() { return sInstance; }

    virtual void beginFrame(); // at 0x8
    virtual void endFrame();   // at 0xC

    static void deleteInstance();
    CoreController* getNthController(int i);
    static void connectCallback(s32, s32);

private:
    CoreControllerMgr();

private:
    TBuffer<CoreController*> mControllers; // at 0x14
    struct UnkInterface {
        virtual UNKTYPE VF08(UNKTYPE*) = 0;
    } * PTR_0x20;
    TBuffer<eCoreDevType> mDevTypes; // at 0x24

    static CoreControllerMgr* sInstance;
    static CoreControllerFactory sCoreControllerFactory;
    static ConnectCallback sConnectCallback;
    static int sWPADWorkSize;
};
} // namespace EGG

#endif