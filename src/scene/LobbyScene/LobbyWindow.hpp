#ifndef SPORTSNET_LOBBY_WINDOW_H
#define SPORTSNET_LOBBY_WINDOW_H
#include "types.h"

#include <RPSports/RPSportsLytCursorBase.h>

namespace spnet {

class LobbySlot;

/**
 * @brief Main window/layout for lobby
 */
class LobbyWindow : public RPSportsLytCursorBase {
public:
    LobbyWindow();
    virtual ~LobbyWindow();
    void LoadResource();
    void Reset();
    void Calculate();
    void UserDraw();

private:
    static const u32 scMaxPlayers = 4;

    RPSysLayout* mLayout;
    LobbySlot* mSlots[scMaxPlayers];
    RPSportsLytButton* mSettingsBtn;
    RPSportsLytButton* mStartBtn;
};

} // namespace spnet

#endif