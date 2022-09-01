#include "MainSceneEx.hpp"

#include "SceneCreatorEx.hpp"

namespace spnet {

/**
 * @brief Sport selection callback
 */
void MainSceneEx::OnSportSelect() {
    SceneCreatorEx::GetInstance().ChangeSceneAfterFade(
        SceneCreatorEx::SPNET_NET_SELECT_SCENE, false);
}
kmCallMF(0x801f6b3c, MainSceneEx, OnSportSelect);

} // namespace spnet