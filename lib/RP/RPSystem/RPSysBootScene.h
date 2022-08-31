#ifndef RP_SYSTEM_BOOT_SCENE_H
#define RP_SYSTEM_BOOT_SCENE_H
#include "RPSysScene.h"
#include "types_RP.h"

/**
 * @brief Pack Project boot scene
 * @note Stub class for SceneCreatorEx
 */
class RPSysBootScene : public RPSysScene {
public:
    RPSysBootScene() {}
    //! @address 803c1fe0
    virtual ~RPSysBootScene();

private:
    char UNK_0x44[0x58 - 0x44];
};

#endif