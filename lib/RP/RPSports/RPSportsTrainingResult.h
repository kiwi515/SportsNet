#ifndef RP_SPORTS_TRAINING_RESULT_H
#define RP_SPORTS_TRAINING_RESULT_H
#include "types_RP.h"

class RPSportsTrainingResult {
public:
    RPSportsTrainingResult();
    virtual ~RPSportsTrainingResult();

    void LoadResource(EGG::Archive* arc, RPSysMessage* msg);
    void Reset();
    void Calculate();
    void UserDraw();

public:
    char UNK_0x4[0x6C - 0x4];
    u16 mFlags; // at 0x6C
    char UNK_0x6E[0x88 - 0x6E];
};

#endif