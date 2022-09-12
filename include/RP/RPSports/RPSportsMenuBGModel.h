#ifndef RP_SPORTS_MENU_BG_MODEL_H
#define RP_SPORTS_MENU_BG_MODEL_H
#include "types_RP.h"

#include <egg/types_egg.h>

class RPSportsMenuBGModel {
public:
    RPSportsMenuBGModel(u8 view, u8 lightMgr, u8 color);
    virtual ~RPSportsMenuBGModel();
    void LoadResource(EGG::Archive* cmnArc);
    void Reset();
    void Calculate();

private:
    char UNK_0x4[0x28 - 0x4];
};

#endif