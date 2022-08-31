#include "NunchukSceneEx.hpp"

#include "NetplayMgr.hpp"
#include "SceneCreatorEx.hpp"

#include <RPSports/RPSportsSequenceMgr.h>
#include <RPSystem/RPSysProjectLocal.h>
#include <RPSystem/RPSysQueuedScene.h>
#include <RPSystem/RPSysSceneCreator.h>

namespace spnet {

NetplayMgr* NetplayMgr::sInstance = NULL;

/**
 * @brief Dispatch the correct scene when the Nunchuk check is successful
 */
void NunchukSceneEx::Dispatch() {
    SceneCreatorEx::ESceneIDEx scene;

    // If online play is enabled, launch the lobby instead
    if (NetplayMgr::GetInstance().IsOnlinePlay()) {
        SceneCreatorEx::GetInstance().ChangeSceneAfterFade(
            SceneCreatorEx::SPNET_LOBBY_SCENE, false);
    }

    // Sports Pack
    if (RPSysProjectLocal::getInstance()->getPackID() ==
        RPSysSceneCreator::RP_SPORTS_PACK) {
        switch (RPSportsSequenceMgr::GetInstance()->GetSequence()) {
        case 0:
        case 1:
            // Load sport scene
            scene = static_cast<SceneCreatorEx::ESceneIDEx>(
                RPSysSceneCreator::getInstance()->getSceneID(
                    RPSportsSequenceMgr::GetInstance()->GetSport()));
            SceneCreatorEx::GetInstance().ChangeSceneAfterFade(scene, false);
            break;
        case 2:
            // Load queued scene
            scene = static_cast<SceneCreatorEx::ESceneIDEx>(
                RPSysQueuedScene::GetInstance()->GetSceneID());
            SceneCreatorEx::GetInstance().ChangeSceneAfterFade(scene, false);
            break;
        }
    } else {
        // Load queued scene
        scene = static_cast<SceneCreatorEx::ESceneIDEx>(
            RPSysQueuedScene::GetInstance()->GetSceneID());
        SceneCreatorEx::GetInstance().ChangeSceneAfterFade(scene, false);
    }
}
kmBranchMF(0x801e34b4, NunchukSceneEx, Dispatch);

} // namespace spnet