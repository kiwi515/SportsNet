#include "NetSelectScene.hpp"

#include "NetplayMgr.hpp"
#include "SceneCreatorEx.hpp"
#include "net_select_message.h"

#include <RPGraphics/RPGrpRenderer.h>
#include <RPKernel/RPSysMessage.h>
#include <RPKernel/RPSysSystemWinMgr.h>
#include <RPSystem/RPSysResourceManager.h>
#include <RPUtility/RPPrint.h>

namespace spnet {

NetSelectScene::NetSelectScene() : mNetworkMsg(NULL) {}

NetSelectScene::~NetSelectScene() { delete mNetworkMsg; }

void NetSelectScene::OnConfigure() {}

void NetSelectScene::OnLoadResource() {
    void* netBmg =
        RPSysResourceManager::GetMessageResource("net_select_message.bmg");
    MATO_ASSERT(netBmg != NULL);
    mNetworkMsg = new RPSysMessage(netBmg, NULL);
    MATO_ASSERT(mNetworkMsg != NULL);
}

void NetSelectScene::OnReset() {}

void NetSelectScene::OnCalculate() {
    switch (RPSysSystemWinMgr::getInstance()->getResult()) {
    case RPSysSystemWinMgr::RESULT_NONE:
        RPSysSystemWinMgr::getInstance()->setSystemWindow(
            RPSysSystemWinMgr::WINDOW_TYPE_MSG,
            MESSAGE_GROUP_ID(MSG_ASK_NET_SELECT), mNetworkMsg, 0);
        return;
    case RPSysSystemWinMgr::RESULT_WAIT:
        return;
    case RPSysSystemWinMgr::RESULT_YES:
        NetplayMgr::GetInstance().SetOnlinePlay(true);
        break;
    case RPSysSystemWinMgr::RESULT_NO:
        NetplayMgr::GetInstance().SetOnlinePlay(false);
        break;
    default:
        return;
    }

    SceneCreatorEx::GetInstance().ChangeSceneAfterFade(
        SceneCreatorEx::RP_PLAYER_SELECT_SCENE, false);
}

void NetSelectScene::OnExit() {}

void NetSelectScene::OnUserDraw() {}

} // namespace spnet