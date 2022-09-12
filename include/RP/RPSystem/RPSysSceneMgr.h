#ifndef RP_SYSTEM_SCENE_MGR_H
#define RP_SYSTEM_SCENE_MGR_H
#include "RPSysSystem.h"
#include "types_RP.h"

#include <egg/core/eggColorFader.h>
#include <egg/core/eggSceneManager.h>

/**
 * @brief RP engine scene manager
 * @details Has another ColorFader, which gets purposed for the current scene.
 * The inherited fader is referred to as the "manager fader"
 * and is used to fade in/out all graphics (transition between scenes)
 * @wfuname
 */
class RPSysSceneMgr : public EGG::SceneManager {
public:
    //! @brief Scene manager states
    enum EState {
        STATE_NORMAL,
        STATE_PAUSED,
        STATE_SOFT_RESET,
        STATE_RETURN_TO_MENU,
        STATE_RETURN_TO_MENU_2
    };

public:
    static RPSysSceneMgr* getInstance() { return sInstance; }

    /**
     * @brief Manager state logic
     * @address 801856d0
     */
    void updateState();
    /**
     * @brief Active scene's logic
     * @address 80185868
     */
    void calcCurrentScene();

    //! @address 8018589c
    void drawMgrFader();
    //! @address 801858b0
    void drawSceneFader();
    //! @address 801858c4
    void calcSceneFader();

    /**
     * @brief Checks if the scene is allowed to change
     * @details The manager fader needs to be done and the NAND must not be busy
     * @address 801858d8
     */
    bool isSceneChangeEnable();
    /**
     * @brief Checks if all of the system threads are idle
     * @address 80185968
     */
    bool isTaskFinished();
    /**
     * @brief Checks if both faders are currently fading in
     * @address 801859dc
     */
    bool isFadeIn();
    /**
     * @brief Checks if the current scene is blank (not displaying)
     * @details The current scene is blank when both faders are preparing to
     * fade in
     * @address 80185a50
     */
    bool isBlank();
    /**
     * @brief Checks if the current scene is displaying
     * @details The current scene is displaying when both faders are done fading
     * in
     * @address 80185ac4
     */
    bool isDisplay();

    //! @address 80185b38
    void startSceneFadeOut();
    //! @address 80185b4c
    void startSceneFadeIn();
    //! @address 80185b60
    void startMgrFadeIn();

    //! @address 80185b64
    void setSceneStatus(EGG::Fader::EStatus status);
    //! @address 80185b78
    EGG::Fader::EStatus getSceneStatus();

    //! @address 80185b8c
    void setSceneFadeColor(nw4r::ut::Color color);
    //! @address 80185bd4
    void setFadeColor(nw4r::ut::Color color);
    //! @address 80185c60
    nw4r::ut::Color getFadeColor();
    /**
     * @brief Reset both faders' colors to white
     * @address 80185c8c
     */
    void resetFadeColor();

    //! @address 80185ce0
    void setFadeFrame(u16 frame);
    //! @address 80185d28
    u16 getFadeFrame();
    /**
     * @brief Reset both faders' frame to 20
     * @address 80185d34
     */
    void resetFadeFrame();

    /**
     * @brief Fade out into new scene
     * @address 80185d74
     * @param scene Scene ID
     * @param reload Optionally reload current scene
     */
    bool changeNextSceneAfterFade(int scene, bool reload);

    // State check functions
    // ? FUN_80185f04()
    // ? FUN_80185f18()
    // ? FUN_80185f38()
    // ? FUN_80185f50()
    // ? FUN_80185f64()

    /**
     * @brief Shutdown system
     * @address 80185f74
     * @param black For VISetBlack
     */
    bool shutdownSystem(bool black);
    /**
     * @brief Shutdown system
     * @address 80185fe4
     * @param black For VISetBlack
     */
    bool returnToMenu(bool black);
    /**
     * @brief Soft reset
     * @address 80186054
     * @param black For VISetBlack
     */
    bool softReset(bool black);

    //! @address 80186100
    EGG::Scene* getCurrentScene() const;

private:
    RPSysSceneMgr() : EGG::SceneManager(NULL) {
        RPSysSystem* sys = RPSysSystem::getInstance();
        mSceneFader = new EGG::ColorFader(
            0.0f, 0.0f, sys->getFBWidth(), sys->getXFBHeight(),
            nw4r::ut::Color(0), EGG::ColorFader::STATUS_PREPARE_IN);
    }

    //! @address 80185678
    virtual ~RPSysSceneMgr();

private:
    //! @brief Heap in which this object was allocated
    EGG::Heap* mParentHeap; // at 0x2C
    //! @brief Manager state
    int mState; // at 0x30
    //! @brief Fader for the current scene
    EGG::ColorFader* mSceneFader; // at 0x34

    static RPSysSceneMgr* sInstance;
};

#endif