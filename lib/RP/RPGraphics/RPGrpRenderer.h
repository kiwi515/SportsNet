#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include "types_RP.h"

//! TODO
class RPGrpRenderer {
public:
    static void Begin();
    static void End();

    void AppendDrawObject(IRPGrpDrawObject*);

    IRPGrpDrawObject* GetDrawObjectList() const { return mDrawObjects; }
    static void SetDrawPass(s32 pass) { sDrawPass = pass; }

private:
    char UNK_0x0[0xC];
    IRPGrpDrawObject* mDrawObjects; // at 0xC

    static s32 sDrawPass;
};

#endif