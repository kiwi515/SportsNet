#ifndef SPORTSNET_SCENE_LOBBY_SLOT_H
#define SPORTSNET_SCENE_LOBBY_SLOT_H
#include "types.h"

#include <RP/types_RP.h>
#include <nw4r/math/math_types.h>

namespace spnet {

/**
 * @brief Lobby player slot
 */
class LobbySlot {
public:
    LobbySlot(u32 player);
    ~LobbySlot();
    void LoadResource();
    void Reset();
    void Calculate();
    void UserDraw();

    void UpdatePlayer();

    void SetName(const wchar_t* name);
    void SetKokeshiIcon(RPSysKokeshiIcon* icon);

private:
    static const u32 scMaxPlayers = 4;
    static const u32 scPlayerNameLength = 10;

    //! Player slot ID
    u32 mPlayer;
    //! Player slot layout
    RPSysLayout* mLayout;
    //! Player Mii icon (non-owning)
    RPSysKokeshiIcon* mIcon;

    static const nw4r::math::VEC2 sSlotRootTrans[scMaxPlayers];
};

} // namespace spnet

#endif