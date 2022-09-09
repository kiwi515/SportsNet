#ifndef RP_SPORTS_MENU_LOGO_MODEL_H
#define RP_SPORTS_MENU_LOGO_MODEL_H
#include "types_RP.h"

#include <egg/math/eggVector.h>

class RPSportsMenuLogoModel {
public:
    RPSportsMenuLogoModel(u8, u8);
    virtual ~RPSportsMenuLogoModel();
    void LoadResource();
    void Reset();
    void Calculate();
    void SetPosition(const EGG::Vector2f& pos);

private:
    char UNK_0x4[0x28 - 0x4];
};

#endif