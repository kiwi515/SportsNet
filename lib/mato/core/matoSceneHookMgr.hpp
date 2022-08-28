#ifndef MATO_SCENE_HOOK_MGR_H
#define MATO_SCENE_HOOK_MGR_H
#include "types.h"

#include <RPSystem/RPSysSceneCreator.h>

namespace mato {

typedef void (*SceneCallback)(RPSysScene*);
typedef void (*PauseCallback)(RPSysScene*, bool isPause);

struct SceneHook {
    SceneCallback onConfigure;
    SceneCallback onLoadResource;
    SceneCallback onCalculate;
    SceneCallback onUserDraw;
    SceneCallback onExit;
    PauseCallback onPause;
};

class SceneHookMgr {
public:
    static SceneHookMgr& GetInstance() {
        static SceneHookMgr instance;
        return instance;
    }

    void SetHook(RPSysSceneCreator::ESceneID scene, const SceneHook& hook) {
        mSceneHooks[scene] = hook;
    }

    static void ConfigureCallback();
    static void LoadResourceCallback();
    static void CalculateCallback();
    static void UserDrawCallback();
    static void ExitCallback();
    static void PauseCallback();
    static void UnPauseCallback();

private:
    SceneHookMgr() {}
    virtual ~SceneHookMgr() {}

private:
    SceneHook mSceneHooks[RPSysSceneCreator::SCENE_MAX];
};

} // namespace mato

#endif