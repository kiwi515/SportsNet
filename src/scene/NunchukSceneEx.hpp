#ifndef SPORTSNET_SCENE_NUNCHUK_SCENE_EX_H
#define SPORTSNET_SCENE_NUNCHUK_SCENE_EX_H
#include <RPSystem/RPSysNunchukScene.h>

namespace spnet {

/**
 * @brief System nunchuk scene extension to set up P2P/lobby
 */

class NunchukSceneEx : public RPSysNunchukScene {
public:
    void Dispatch();

private:
    // NunchukSceneEx should not be constructed
    NunchukSceneEx();
    NunchukSceneEx(const NunchukSceneEx&);
    ~NunchukSceneEx();
};

} // namespace spnet

#endif