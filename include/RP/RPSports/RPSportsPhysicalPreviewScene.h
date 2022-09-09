#ifndef RP_SPORTS_PHYSICAL_PREVIEW_SCENE_H
#define RP_SPORTS_PHYSICAL_PREVIEW_SCENE_H
#include "RPSysScene.h"
#include "types_RP.h"

/**
 * @brief Wii Fitness game preview scene
 */
class RPSportsPhysicalPreviewScene : public RPSysScene {
public:
    RPSportsPhysicalPreviewScene() {}
    //! @address 801ee2e8
    virtual ~RPSportsPhysicalPreviewScene();
    virtual void Configure();
    virtual void LoadResource();
    virtual void Reset();
    virtual void Calculate();
    virtual void Exit();
    virtual void UserDraw();

private:
    char UNK_0x44[0x60 - 0x44];
};

#endif