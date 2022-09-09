#ifndef RP_SYSTEM_NUNCHUK_SCENE_H
#define RP_SYSTEM_NUNCHUK_SCENE_H
#include "IRPSysHostIOSocket.h"
#include "RPSysScene.h"
#include "types_RP.h"

/**
 * @brief Pack Project nunchuk scene
 * @note Stub class for SceneCreatorEx
 */
class RPSysNunchukScene : public RPSysScene, public IRPSysHostIOSocket {
public:
    RPSysNunchukScene() {}
    //! @address 803c1fe0
    virtual ~RPSysNunchukScene();

private:
    char UNK_0x48[0x98 - 0x48];
};

#endif