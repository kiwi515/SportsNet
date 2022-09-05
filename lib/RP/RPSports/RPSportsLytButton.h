#ifndef RP_SPORTS_LYT_BUTTON_H
#define RP_SPORTS_LYT_BUTTON_H
#include "types_RP.h"

#include <egg/types_egg.h>
#include <nw4r/types_nw4r.h>

class RPSportsLytButton {
public:
    struct Arg {
        s32 id;                        // at 0x0
        RPSysLayout* parent;           // at 0x4
        RPSysLytResAccessor* accessor; // at 0x8
        const char* pane;              // at 0xC
        const char* bounding;          // at 0x10
        const char* activeAnim;        // at 0x14
        const char* STR_0x18;
        const char* pushAnim; // at 0x1C
    };

    enum ELink {
        LINK_RIGHT,
        LINK_LEFT,
        LINK_ABOVE,
        LINK_BELOW,
        LINK_MAX,
    };

    enum EState { STATE_HOVER, STATE_IDLE, STATE_PUSH };

public:
    RPSportsLytButton(const Arg&);

    EState GetState() const { return mState; }

    void Link(ELink link, RPSportsLytButton* btn) { mLinks[link] = btn; }

private:
    s32 mId;                             // at 0x0
    RPSysLayout* mParent;                // at 0x4
    nw4r::lyt::Pane* mPane;              // at 0x8
    RPSysLytBounding* mBounding;         // at 0xC
    RPSportsLytButton* mLinks[LINK_MAX]; // at 0x10
    UNKWORD WORD_0x20;
    UNKWORD WORD_0x24;
    char UNK_0x28[0x34 - 0x28];
    EState mState; // at 0x34
    char UNK_0x38[0x44 - 0x38];
};

#endif