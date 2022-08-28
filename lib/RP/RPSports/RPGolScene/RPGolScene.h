#ifndef RP_SPORTS_GOL_SCENE_H
#define RP_SPORTS_GOL_SCENE_H
#include "RPSportsBaseScene.h"
#include "types_RP.h"

/**
 * @brief Golf scene
 * @wscname
 */
class RPGolScene : public RPSportsBaseScene {
public:
    RPGolScene() {}
    //! @address 8028e030
    virtual ~RPGolScene() {}

    //! @address 8028dff0
    virtual void OnConfigure();
    //! @address 8028dfe8
    virtual void OnLoadResource();
    //! @address 8028dfb0
    virtual void OnReset();
    //! @address 8028dfa8
    virtual void OnCalculate();
    //! @address 8028df78
    virtual void OnUserDraw();
    //! @address 8028df74
    virtual void OnDebugDraw();
    //! @address 8028df80
    virtual void OnExit();

private:
    //! @brief Main golf object
    RPGolMain* mGolMain; // at 0x9C
};

#endif