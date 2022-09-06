#ifndef RP_SYSTEM_LYT_BACK_BUTTON_H
#define RP_SYSTEM_LYT_BACK_BUTTON_H
#include "RPUtlLytBase.h"
#include "types_RP.h"

class RPSysLytBackButton : public RPUtlLytBase {
public:
    enum EState {
        STATE_IN_FRAME,

    };

public:
    RPSysLytBackButton(s32 packID);
    ~RPSysLytBackButton() {}

    virtual void LoadResource(EGG::Archive* arc);
    virtual void Reset();
    virtual void Calculate();
    virtual void UserDraw();
    virtual void VF_18();

    bool IsState2() const;
    void StartState1();
    void StartState5();

private:
    char UNK_0x8[0xC - 0x8];
    UNKWORD mCurrentState; // at 0xC
    UNKWORD mNextState;    // at 0x10
    char UNK_0x14[0x30 - 0x14];
};

#endif