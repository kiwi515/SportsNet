#ifndef RP_GRAPHICS_MODEL_RES_MANAGER_H
#define RP_GRAPHICS_MODEL_RES_MANAGER_H
#include <types_RP.h>

class RPGrpModelResManager {
public:
    static RPGrpModelResManager* GetInstance() { return sInstance; }

    void CreateResourceList(u16);

private:
    static RPGrpModelResManager* sInstance;
};

#endif