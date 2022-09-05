#ifndef RP_SPORTS_LYT_CURSOR_BASE_H
#define RP_SPORTS_LYT_CURSOR_BASE_H
#include "types_RP.h"

#include <egg/types_egg.h>

class RPSportsLytCursorBase {
public:
    RPSportsLytCursorBase();

    virtual UNKTYPE VF_0x8(UNKTYPE);

    void Bind(RPSportsLytButton*);
    void LoadCursorResource(EGG::Archive* staticLocalArc);

    void Calculate(const EGG::Vector2f& cursorPos, bool forceBind);
    void UserDraw();
    void Reset();

private:
    RPSportsLytButton* mHeadBtn;       // at 0x4
    RPSportsLytButton* mHoveredBtn;    // at 0x8
    BOOL mIsHoveringBtn;               // at 0xC
    int mLastHoveredBtnId;             // at 0x10
    RPUtlLytFrameCursor* mFrameCursor; // at 0x14
    UNKWORD WORD_0x18;
    UNKWORD WORD_0x1C;
};

#endif