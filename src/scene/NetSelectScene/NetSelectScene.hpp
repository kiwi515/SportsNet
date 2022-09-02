#ifndef SPORTSNET_NET_SELECT_SCENE_H
#define SPORTSNET_NET_SELECT_SCENE_H
#include "SportsNetBaseScene.hpp"
#include "types.h"

#include <RPSystem/RPSysScene.h>

namespace spnet {

/**
 * @brief Online/local play section
 */
class NetSelectScene : public SportsNetBaseScene {
public:
    NetSelectScene();
    virtual ~NetSelectScene();
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

private:
    //! @brief Network BMG
    RPSysMessage* mNetworkMsg;
};

} // namespace spnet

#endif