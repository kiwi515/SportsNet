#ifndef SPORTSNET_NET_NETPLAY_MGR_H
#define SPORTSNET_NET_NETPLAY_MGR_H
#include "types.h"

namespace spnet {

/**
 * @brief P2P netplay manager
 */
class NetplayMgr {
public:
    static void CreateInstance();
    static void DestroyInstance();

    static NetplayMgr& GetInstance() {
        MATO_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    bool IsOnlinePlay() const { return mIsOnlinePlay; }
    void SetOnlinePlay(bool online) { mIsOnlinePlay = online; }

    bool IsServer() const { return mIsServer; }
    bool IsClient() const { return !mIsServer; }

    const char* GetPlayerName(u32 player);
    void SetPlayerName(u32 player, const char* name);

private:
    NetplayMgr();
    NetplayMgr(const NetplayMgr&);
    virtual ~NetplayMgr();

private:
    static const u32 scMaxPlayers = 4;
    static const u32 scPlayerNameLength = 10;

    //! Whether online play is enabled
    bool mIsOnlinePlay;
    //! Whether the console is the room server
    bool mIsServer;
    //! Mii names of other players in the room
    char mPlayerNames[scPlayerNameLength][scMaxPlayers];

    static NetplayMgr* sInstance;
};

} // namespace spnet

#endif