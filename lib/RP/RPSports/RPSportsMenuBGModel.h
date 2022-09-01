#ifndef RP_SPORTS_MENU_BG_MODEL_H
#define RP_SPORTS_MENU_BG_MODEL_H
#include "types_RP.h"

class RPSportsMenuBGModel {
public:
    RPSportsMenuBGModel(u8, u8, u8);
    virtual ~RPSportsMenuBGModel();
    void LoadResource(EGG::Archive* cmnArc);
    void Reset();
    void Calculate();

private:
    char UNK_0x4[0x28 - 0x4];
};

#endif