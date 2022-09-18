#include "LobbyScene.hpp"

#include "LobbyLytPlayerList.hpp"
#include "Lobby_sound.h"
#include "NetplayMgr.hpp"
#include "SceneCreatorEx.hpp"

#include <RPAudio/RPSndAudioMgr.h>
#include <RPKernel/RPSysMessage.h>
#include <RPSystem/RPSysResourceManager.h>

namespace spnet {

LobbyScene::LobbyScene()
    : mSequence(SEQ_ASK_HOST), mLobbyMessage(NULL), mPlayerListLyt(NULL) {}

LobbyScene::~LobbyScene() {
    delete mLobbyMessage;
    delete mPlayerListLyt;
}

void LobbyScene::OnConfigure() {
    mPlayerListLyt = new LobbyLytPlayerList();

    // Prepare audio manager for new archive
    RPSndAudioMgr::getInstance()->changeScene();
}

void LobbyScene::OnLoadResource() {
    // Load sound archive
    MATO_ASSERT(RPSndAudioMgr::getInstance()->attachArchive("Lobby_sound.brsar",
                                                            false, NULL));
    MATO_ASSERT(RPSndAudioMgr::getInstance()->loadGroup(0, NULL, 0));

    // Load text
    void* mesgBmg =
        RPSysResourceManager::GetMessageResource("lobby_message.bmg");
    MATO_ASSERT(mesgBmg != NULL);
    mLobbyMessage = new RPSysMessage(mesgBmg, NULL);
    MATO_ASSERT(mLobbyMessage != NULL);

    // Load layout assets
    mPlayerListLyt->LoadResource();
}

void LobbyScene::OnReset() {
    // Start BGM
    RPSndAudioMgr::getInstance()->startSound(BGM_Lobby);

    mPlayerListLyt->Reset();
}

void LobbyScene::OnCalculate() {
    MATO_ASSERT(mSequence < SEQ_MAX);
    (this->*sSequenceCalcProc[mSequence])();
}

void LobbyScene::OnExit() {
    // Reset netplay settings
    NetplayMgr::GetInstance().Reset();

    // Prepare audio manager for new archive
    RPSndAudioMgr::getInstance()->changeScene();
}

void LobbyScene::OnUserDraw() {
    MATO_ASSERT(mSequence < SEQ_MAX);
    (this->*sSequenceDrawProc[mSequence])();
}

/**
 * @brief Lobby player connect callback
 *
 * @param arg Lobby scene
 * @param player Player slot ID
 */
void LobbyScene::OnPlayerConnect(void* arg, u32 player) {
    MATO_ASSERT(arg != NULL);
    LobbyScene* thisx = static_cast<LobbyScene*>(arg);
    thisx->mPlayerListLyt->UpdatePlayer(player);
}

/**
 * @brief Lobby player disconnect callback
 *
 * @param arg Lobby scene
 * @param player Player slot ID
 */
void LobbyScene::OnPlayerDisconnect(void* arg, u32 player) {
    MATO_ASSERT(arg != NULL);
    LobbyScene* thisx = static_cast<LobbyScene*>(arg);
    thisx->mPlayerListLyt->UpdatePlayer(player);
}

const LobbyScene::SequenceProc
    LobbyScene::sSequenceCalcProc[LobbyScene::SEQ_MAX] = {
        &LobbyScene::CalcSeqAskHost,
        &LobbyScene::CalcSeqJoinServer,
        &LobbyScene::CalcSeqWaitLobby,
};

const LobbyScene::SequenceProc
    LobbyScene::sSequenceDrawProc[LobbyScene::SEQ_MAX] = {
        &LobbyScene::DrawSeqAskHost,
        &LobbyScene::DrawSeqJoinServer,
        &LobbyScene::DrawSeqWaitLobby,
};

} // namespace spnet