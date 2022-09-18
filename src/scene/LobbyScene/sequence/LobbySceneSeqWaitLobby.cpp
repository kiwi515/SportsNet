#include "LobbyLytPlayerList.hpp"
#include "LobbyScene.hpp"

namespace spnet {

void LobbyScene::CalcSeqWaitLobby() { mPlayerListLyt->Calculate(); }

void LobbyScene::DrawSeqWaitLobby() { mPlayerListLyt->UserDraw(); }

} // namespace spnet