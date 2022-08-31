#ifndef RP_SYSTEM_SCENE_H
#define RP_SYSTEM_SCENE_H
#include "IRPGrpDrawObject.h"
#include "types_rp.h"

#include <egg/core/eggScene.h>
#include <egg/math/eggVector.h>
#include <nw4r/ut/ut_Color.h>

/**
 * @brief Base class for all RP engine scenes
 * @details Inherits from EGG::Scene for compatability,
 * and inherits from a renderable interface to simplify the renderer's job.
 * @wfuname
 */
class RPSysScene : public EGG::Scene, public IRPGrpDrawObject {
public:
    //! @address 80185404
    RPSysScene();
    //! @address 80183fa8
    virtual ~RPSysScene() {}

    //! @address 80185094
    virtual void calc();
    //! @address 80185048
    virtual void draw();
    //! @address 80185304
    virtual void enter();
    //! @address 80184f90
    virtual void exit();
    //! @address 8018522c
    virtual void reinit();
    //! @address 80185168
    virtual void incoming_childDestroy();
    //! @address 80185008
    virtual void outgoing_childCreate();

    /**
     * @brief Access debug heap
     * @address 8018558c
     */
    virtual EGG::Heap* getDebugHeap();

    /**
     * @brief Callback for pause/unpause
     * @address 80185594
     * @param pauseOn True = enter, false = exit
     */
    virtual void pauseCallBack(bool pauseOn);

    /**
     * @brief Setup scene members
     * @address 80185400
     */
    virtual void Configure();
    /**
     * @brief Load required scene resources
     * @address 80185598
     */
    virtual void LoadResource();
    //! @address 80185228
    virtual void Reset();
    //! @address 80185164
    virtual void Calculate();
    //! @address 80185004
    virtual void Exit();

    /**
     * @brief Async task
     * @details Called by taskAsyncFunc
     * @address 8018559c
     */
    virtual void taskAsync();

    /**
     * @brief Disable scene fade-in on enter/reset
     * @address 80184e80
     */
    void disableFadeIn();

    //! @address 80184e90
    int getCreatorSceneID() const;
    //! @address 80184e98
    void setCreatorSceneID(int scene);

    /**
     * @brief Initialize base RP scene members
     * @address 80184ea0
     */
    void init();

    /**
     * @brief Toggle VI dimming
     * @address 8018546c
     */
    void setDimming(bool dim);

    /**
     * @details Bool goes used in WFU, but OGWS just tells the manager
     * rather than accessing the fader directly
     */
    /**@{*/
    //! @address 80185474
    void startFadeOut(bool);
    //! @address 8018547c
    void startFadeIn(bool);
    /**@}*/

    /**
     * @brief Set manager's scene fade color
     * @address 80185484
     */
    void setSceneFadeColor(nw4r::ut::Color color);
    /**
     * @brief Fade color of both of manager's faders
     * @details Manager has a scene fader and a manager fader
     */
    /**@{*/
    //! @address 801854cc
    void setFadeColor(nw4r::ut::Color color);
    //! @address 80185514
    nw4r::ut::Color getFadeColor() const;
    /**@}*/

    /**
     * @brief Set fade frame of both of manager's faders
     * @address 8018551c
     */
    void setFadeFrame(u16 frame);

    /**
     * @brief Check if the scene manager is allowing NAND access
     * @details The scene manager must not be fading in or be busy
     * @address 80185524
     */
    bool isNandAccessEnable() const;
    /**
     * @brief Check if the scene manager is allowing the scene to change
     * @details The scene manager must be ready to fade out and not be busy
     * @address 80185574
     */
    bool isSceneChangeEnable() const;

    /**
     * @brief Check if the scene is currently blank (not visible)
     * @details This happens when both faders are preparing to fade in
     * @address 8018557c
     */
    bool isSceneBlank() const;
    /**
     * @brief Check if the scene is currently fully visible
     * @details This happens when both faders are done and ready to fade back
     * out
     * @address 80185584
     */
    bool isSceneDisplay() const;

    /**
     * @name Defined in RPSysLoadScene.cpp
     */
    /**@{*/
    /**
     * @brief Calls virtual task function asynchronously
     * @details Set up on thread by initTaskAsync
     * @address 80186878
     * @param scene Scene required to call taskAsync
     */
    static void taskAsyncFunc(void* scene);
    /**
     * @brief Loads scene resources asynchronously
     * @details calls LoadResource when done
     * @address 80186888
     * @param scene Scene required to call taskAsync
     */
    static void loadResourceFunc(void* scene);

    UNKTYPE FUN_80186960(UNKTYPE);
    UNKTYPE FUN_80186a1c(UNKTYPE);

    /**
     * @brief Request DVD thread to run taskAsyncFunc
     * @address 80186aa8
     */
    void initTaskAsync();

    UNKTYPE FUN_80186b20(UNKTYPE);
    UNKTYPE FUN_80186c34(UNKTYPE);

    /**
     * @brief Enable the "Now Loading" scene text
     * @details Set automatically if the scene attributes allow it
     * @address 80186cec
     */
    void setShowLoadingText();
    /**
     * @brief Check if the scene is waiting on an async task
     * @address 80186cfc
     */
    bool isTaskAsyncFinish() const;
    /**
     * @brief Set waiting on async flag
     * @address 80186d1c
     */
    void setTaskAsync();

    UNKTYPE FUN_80186d2c(UNKTYPE);

    /**
     * @brief Print time stamp string in specified color
     * @address 80186d30
     */
    void printTimeStamp(nw4r::ut::Color color);
    /**@}*/

private:
    //! @brief Scene renderer (becomes global on scene enter)
    RPGrpRenderer* mRenderer; // at 0x2C
    //! @brief Common draw functionality
    RPSysCommonObject* mCmnObject; // at 0x30
    //! @brief TODO, constructor at 801988d8
    //! @details Some particle related structure
    UNKTYPE* PTR_0x34;
    //! @brief Scene heap (unused)
    EGG::Heap* mHeap; // at 0x38
    //! @brief Scene flags
    u32 mFlags; // at 0x3C
    //! @brief Scene ID set by scene creator
    int mCreatorSceneId; // at 0x40

    //! @brief Debug heap (unused)
    static EGG::Heap* sDebugHeap; // 804bf4d0

    //! @brief Defined in RPSysLoadScene.cpp
    static EGG::Vector3f DAT_804a3db0[3]; // 804a3db0
};

#endif