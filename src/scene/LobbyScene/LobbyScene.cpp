#include "LobbyScene.hpp"

#include <RPAudio/RPSndAudioMgr.h>
#include <RPAudio/rp_Common_Sports.h>
#include <RPSports/RPSportsMenuBGModel.h>

namespace spnet {

LobbyScene::LobbyScene() {}

LobbyScene::~LobbyScene() {}

void LobbyScene::OnConfigure() {}

void LobbyScene::OnLoadResource() {}

void LobbyScene::OnReset() {
    // Play BGM
    RPSndAudioMgr::getInstance()->startSound(STRM_Training_Select);
}

void LobbyScene::OnCalculate() {}

void LobbyScene::OnExit() {
    ;
    ;
}

void LobbyScene::OnUserDraw() {
    ;
    ;
}

} // namespace spnet