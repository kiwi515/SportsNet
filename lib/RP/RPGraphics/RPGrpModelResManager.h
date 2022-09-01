#ifndef RP_GRAPHICS_MODEL_RES_MANAGER_H
#define RP_GRAPHICS_MODEL_RES_MANAGER_H
#include <types_RP.h>

class RPGrpModelResManager {
public:
    static RPGrpModelResManager* GetInstance() { return sInstance; }

    void CreateModelScene(u32, u8, u32, RPGrpLightManager*, RPGrpFogManager*);

private:
    static RPGrpModelResManager* sInstance;
};

#endif