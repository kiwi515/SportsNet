#ifndef SPORTSNET_LOBBY_SCENE_H
#define SPORTSNET_LOBBY_SCENE_H
#include "SportsNetBaseScene.hpp"
#include "types.h"

#include <RPSystem/RPSysScene.h>

namespace spnet {

class LobbyWindow;

/**
 * @brief Online multiplayer lobby scene
 */
class LobbyScene : public SportsNetBaseScene {
public:
    LobbyScene();
    virtual ~LobbyScene();
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

private:
    LobbyWindow* mWindow;
};

} // namespace spnet

#endif