#include "LobbyScene.hpp"
#include "lobby_message.h"

#include <RPKernel/RPSysSystemWinMgr.h>

/**
 * @brief Lobby scene host/client select sequence
 */

namespace spnet {

void LobbyScene::CalcSeqAskHost() {
    switch (RPSysSystemWinMgr::getInstance()->getResult()) {
    case RPSysSystemWinMgr::RESULT_NONE:
        RPSysSystemWinMgr::getInstance()->setSystemWindow(
            RPSysSystemWinMgr::WINDOW_TYPE_MSG, MESSAGE_GROUP_ID(MSG_ASK_HOST),
            mLobbyMessage, 0);
        return;
    case RPSysSystemWinMgr::RESULT_WAIT:
        return;
    case RPSysSystemWinMgr::RESULT_YES:
        mSequence = SEQ_WAIT_LOBBY;
        break;
    case RPSysSystemWinMgr::RESULT_NO:
        mSequence = SEQ_JOIN_SERVER;
        break;
    default:
        return;
    }
}

void LobbyScene::DrawSeqAskHost() {}

} // namespace spnet