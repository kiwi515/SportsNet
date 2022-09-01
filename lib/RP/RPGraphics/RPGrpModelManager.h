#ifndef RP_GRAPHICS_MODEL_MANAGER_H
#define RP_GRAPHICS_MODEL_MANAGER_H
#include <types_RP.h>

class RPGrpModelManager {
public:
    static RPGrpModelManager* GetInstance() { return sInstance; }

    void CreateResourceList(u16);

private:
    static RPGrpModelManager* sInstance;
};

#endif