#ifndef RP_GRAPHICS_RENDERER_H
#define RP_GRAPHICS_RENDERER_H
#include "types_RP.h"

//! TODO
class RPGrpRenderer {
public:
    enum EDrawPass { DRAWPASS_LYT = 5 };

public:
    static void Begin();
    static void End();

    static RPGrpRenderer* GetInstance() { return sInstance; }

    void AppendDrawObject(IRPGrpDrawObject*);

    void CreateView2D(u8, RPGrpScreen*);
    void CorrectView();

    IRPGrpDrawObject* GetDrawObjectList() const { return mDrawObjects; }

    static EDrawPass GetDrawPass() { return (EDrawPass)sDrawPass; }
    static void SetDrawPass(s32 pass) { sDrawPass = pass; }

    static RPGrpScreen* GetActiveScreen() { return sActiveScreen; }

public:
    static u8 D_804BF615;

private:
    char UNK_0x0[0xC];
    IRPGrpDrawObject* mDrawObjects; // at 0xC

    static s32 sDrawPass;
    static RPGrpRenderer* sInstance;
    static RPGrpScreen* sActiveScreen;
};

#endif