#ifndef RP_KERNEL_KOKESHI_ICON_H
#define RP_KERNEL_KOKESHI_ICON_H
#include "types_RP.h"

class RPSysKokeshiIcon {
public:
    RPSysKokeshiIcon(const RPSysKokeshiGenInfo*);
    virtual ~RPSysKokeshiIcon();
    virtual void LoadResource(const RPSysKokeshiOverloadInfo*);
    virtual void ApplyLightTexture(u8);
};

#endif