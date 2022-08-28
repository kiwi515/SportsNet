#include "matoSceneHookMgr.hpp"

#include "matoAssert.h"

#include <RPGraphics/RPGrpRenderer.h>
#include <RPSystem/RPSysScene.h>
#include <RPSystem/RPSysSceneMgr.h>

namespace mato {

static s32 GetCurrentSceneID() {
    RPSysSceneMgr* mgr = RPSysSceneMgr::getInstance();
    MATO_ASSERT(mgr != NULL);
    return mgr->getCurrentSceneID();
}

static RPSysScene* GetCurrentScene() {
    RPSysSceneMgr* mgr = RPSysSceneMgr::getInstance();
    MATO_ASSERT(mgr != NULL);
    return (RPSysScene*)mgr->getCurrentScene();
}

void SceneHookMgr::ConfigureCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onConfigure != NULL)
        hookMgr.mSceneHooks[scene].onConfigure(GetCurrentScene());
}
kmBranch(0x800a5190, SceneHookMgr::ConfigureCallback);

void SceneHookMgr::LoadResourceCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onLoadResource != NULL)
        hookMgr.mSceneHooks[scene].onLoadResource(GetCurrentScene());
}
kmBranch(0x8018695c, SceneHookMgr::LoadResourceCallback);

void SceneHookMgr::CalculateCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onCalculate != NULL)
        hookMgr.mSceneHooks[scene].onCalculate(GetCurrentScene());
}
kmBranch(0x80185160, SceneHookMgr::CalculateCallback);

void SceneHookMgr::UserDrawCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    RPGrpRenderer::Begin();
    {
        if (hookMgr.mSceneHooks[scene].onUserDraw != NULL)
            hookMgr.mSceneHooks[scene].onUserDraw(GetCurrentScene());
    }
    RPGrpRenderer::End();
}
kmBranch(0x80185090, SceneHookMgr::UserDrawCallback);

void SceneHookMgr::ExitCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onExit != NULL)
        hookMgr.mSceneHooks[scene].onExit(GetCurrentScene());
}
kmBranch(0x80185000, SceneHookMgr::ExitCallback);

void SceneHookMgr::PauseCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onPause != NULL)
        hookMgr.mSceneHooks[scene].onPause(GetCurrentScene(), true);
}
kmBranch(0x801b68ec, SceneHookMgr::PauseCallback);

void SceneHookMgr::UnPauseCallback() {
    s32 scene = GetCurrentSceneID();
    SceneHookMgr& hookMgr = SceneHookMgr::GetInstance();

    if (hookMgr.mSceneHooks[scene].onPause != NULL)
        hookMgr.mSceneHooks[scene].onPause(GetCurrentScene(), false);
}
kmBranch(0x801b6840, SceneHookMgr::UnPauseCallback);

} // namespace mato
