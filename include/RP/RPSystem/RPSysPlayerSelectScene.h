#ifndef RP_SYSTEM_PLAYER_SELECT_SCENE_H
#define RP_SYSTEM_PLAYER_SELECT_SCENE_H
#include "RPSysScene.h"
#include "types_RP.h"

/**
 * @brief Pack Project player select scene
 * @note Stub class for SceneCreatorEx
 */
class RPSysPlayerSelectScene : public RPSysScene {
public:
    RPSysPlayerSelectScene() {}
    //! @address 803c1fe0
    virtual ~RPSysPlayerSelectScene();
    virtual void Configure();
    virtual void LoadResource();
    virtual void Reset();
    virtual void Calculate();
    virtual void Exit();
    virtual void UserDraw();

private:
    char UNK_0x44[0x8C - 0x44];
};

#endif