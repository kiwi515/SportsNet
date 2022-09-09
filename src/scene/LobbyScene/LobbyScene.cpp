#include "LobbyScene.hpp"

#include "LobbyWindow.hpp"
#include "Lobby_sound.h"
#include "NetplayMgr.hpp"
#include "SceneCreatorEx.hpp"

#include <RPAudio/RPSndAudioMgr.h>

namespace spnet {

LobbyScene::LobbyScene() : mWindow(NULL) {}

LobbyScene::~LobbyScene() {}

void LobbyScene::OnConfigure() {
    mWindow = new LobbyWindow();

    // Prepare audio manager for new archive
    RPSndAudioMgr::getInstance()->changeScene();
}

void LobbyScene::OnLoadResource() {
    // Load sound archive
    MATO_ASSERT(RPSndAudioMgr::getInstance()->attachArchive("Lobby_sound.brsar",
                                                            false, NULL));
    MATO_ASSERT(RPSndAudioMgr::getInstance()->loadGroup(0, NULL, 0));

    // Load layout assets
    mWindow->LoadResource();
}

void LobbyScene::OnReset() {
    // Start BGM
    RPSndAudioMgr::getInstance()->startSound(BGM_Lobby);

    mWindow->Reset();
}

void LobbyScene::OnCalculate() { mWindow->Calculate(); }

void LobbyScene::OnExit() {
    // Reset netplay settings
    NetplayMgr::GetInstance().Reset();

    // Prepare audio manager for new archive
    RPSndAudioMgr::getInstance()->changeScene();
}

void LobbyScene::OnUserDraw() { mWindow->UserDraw(); }

} // namespace spnet