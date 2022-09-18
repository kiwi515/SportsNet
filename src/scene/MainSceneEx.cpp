#include "MainSceneEx.hpp"

#include "SceneCreatorEx.hpp"

#include <RPSystem/RPSysQueuedScene.h>

namespace spnet {

/**
 * @brief Sport selection callback
 */
void MainSceneEx::Dispatch() {
    // Queued menu scene
    const SceneCreatorEx::ESceneIDEx next =
        static_cast<SceneCreatorEx::ESceneIDEx>(
            RPSysQueuedScene::GetInstance()->GetSceneID());

    // Training mode/Wii Fitness not supported yet
    if (next == SceneCreatorEx::RP_TRAIN_MENU_SCENE ||
        next == SceneCreatorEx::RP_PHYSICAL_MENU_SCENE) {
        SceneCreatorEx::GetInstance().ChangeSceneAfterFade(
            SceneCreatorEx::RP_PLAYER_SELECT_SCENE, false);
    }

    // Change to network select scene
    SceneCreatorEx::GetInstance().ChangeSceneAfterFade(
        SceneCreatorEx::SPNET_LYT_TEST_SCENE, false);
}
kmCallMF(0x801f6b3c, MainSceneEx, Dispatch);

} // namespace spnet