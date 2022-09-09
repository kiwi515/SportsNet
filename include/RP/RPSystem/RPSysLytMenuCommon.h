#ifndef RP_SYSTEM_LYT_MENU_COMMON_H
#define RP_SYSTEM_LYT_MENU_COMMON_H
#include "RPUtlLytBase.h"
#include "types_RP.h"

class RPSysLytMenuCommon : public RPUtlLytBase {
public:
    RPSysLytMenuCommon(s32 packID);
    ~RPSysLytMenuCommon() {}

    virtual void LoadResource(EGG::Archive* arc);
    virtual void Reset();
    virtual void Calculate();
    virtual void UserDraw();
    virtual void VF_18();

private:
    char UNK_0x8[0x288 - 0x8];
};

#endif