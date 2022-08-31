#ifndef SPORTSNET_SCENE_LOBBYSCENE_H
#define SPORTSNET_SCENE_LOBBYSCENE_H
#include "types.h"

#include <RPSystem/RPSysScene.h>

namespace spnet {

/**
 * @brief Online multiplayer lobby scene
 */
class LobbyScene : public RPSysScene {
public:
    LobbyScene();
    virtual ~LobbyScene();
    virtual void Configure();
    virtual void LoadResource();
    virtual void Reset();
    virtual void Calculate();
    virtual void Exit();
    virtual void UserDraw();

private:
};

} // namespace spnet

#endif