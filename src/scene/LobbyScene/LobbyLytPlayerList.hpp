#ifndef SPORTSNET_LOBBY_LYT_PLAYER_LIST_H
#define SPORTSNET_LOBBY_LYT_PLAYER_LIST_H
#include "types.h"

#include <RPSports/RPSportsLytCursorBase.h>

namespace spnet {

class LobbyLytPlayerSlot;

/**
 * @brief Main window/layout for lobby
 */
class LobbyLytPlayerList : public RPSportsLytCursorBase {
public:
    LobbyLytPlayerList();
    virtual ~LobbyLytPlayerList();
    void LoadResource();
    void Reset();
    void Calculate();
    void UserDraw();

    void UpdatePlayer(u32 player);

private:
    static const u32 scMaxPlayers = 4;

    RPSysLayout* mLayout;
    LobbyLytPlayerSlot* mSlots[scMaxPlayers];
    RPSportsLytButton* mSettingsBtn;
    RPSportsLytButton* mStartBtn;
};

} // namespace spnet

#endif