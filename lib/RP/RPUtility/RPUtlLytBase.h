#ifndef RP_UTILITY_LYT_BASE_H
#define RP_UTILITY_LYT_BASE_H
#include "types_RP.h"

class RPUtlLytBase {
public:
    RPUtlLytBase();

    virtual void LoadResource(EGG::Archive* arc);
    virtual void Reset();
    virtual void Calculate();
    virtual void UserDraw();
    virtual void VF_18();
    // virtual ~RPUtlLytBase() = 0;

private:
    RPSysLytResAccessor* mAccessor; // at 0x4
};

#endif