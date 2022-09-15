#ifndef SPORTSNET_LYT_TEST_SCENE_H
#define SPORTSNET_LYT_TEST_SCENE_H
#include "Socket.hpp"
#include "SportsNetBaseScene.hpp"
#include "types.h"

namespace spnet {

class LytTestScene : public SportsNetBaseScene {
public:
    LytTestScene();
    virtual ~LytTestScene();
    virtual void OnConfigure();
    virtual void OnLoadResource();
    virtual void OnReset();
    virtual void OnCalculate();
    virtual void OnExit();
    virtual void OnUserDraw();

private:
    //! Server socket
    Socket mSocket;
    //! Server port
    u16 mPort;
    //! Socket with client
    Socket* mClient;

    //! Active layout
    RPSysLayout* mLayout;
};

} // namespace spnet

#endif