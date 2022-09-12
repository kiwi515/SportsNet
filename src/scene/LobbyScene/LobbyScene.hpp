#ifndef SPORTSNET_LOBBY_SCENE_H
#define SPORTSNET_LOBBY_SCENE_H
#include "SportsNetBaseScene.hpp"
#include "types.h"

#include <RPSystem/RPSysScene.h>

namespace spnet {

class LobbyLytPlayerList;

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

    static void OnPlayerConnect(void* arg, u32 player);
    static void OnPlayerDisconnect(void* arg, u32 player);

private:
    LobbyLytPlayerList* mWindow;
};

} // namespace spnet

#endif