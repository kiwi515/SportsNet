#ifndef RP_SPORTS_MAIN_SCENE_H
#define RP_SPORTS_MAIN_SCENE_H
#include "RPSysScene.h"
#include "types_RP.h"

/**
 * @brief Sports Pack menu scene
 * @note Stub class for SceneCreatorEx
 */
class RPSportsMainScene : public RPSysScene {
public:
    RPSportsMainScene() {}
    //! @address 801f6e50
    virtual ~RPSportsMainScene();
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