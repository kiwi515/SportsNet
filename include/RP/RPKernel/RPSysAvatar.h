#ifndef RP_KERNEL_AVATAR_H
#define RP_KERNEL_AVATAR_H
#include "types_RP.h"

class RPSysAvatar {
public:
    RPSysAvatar(const RPSysKokeshiGenInfo*);
    virtual ~RPSysAvatar();
    virtual void LoadResource(const RPSysKokeshiOverloadInfo*);
    virtual void ApplyLightTexture(u8) = 0;
};

#endif