#ifndef SPORTSNET_NET_NETPLAY_MGR_H
#define SPORTSNET_NET_NETPLAY_MGR_H
#include "types.h"

#include <RP/types_RP.h>
#include <wstring.h>

namespace spnet {

/**
 * @brief P2P netplay manager
 */
class NetplayMgr {
public:
    typedef void (*PlayerStateCallback)(void* arg, u32 player);

public:
    static void CreateInstance();
    static void DestroyInstance();

    static NetplayMgr& GetInstance() {
        MATO_ASSERT(sInstance != NULL);
        return *sInstance;
    }

    u32 GetNumPlayers() const { return mNumPlayers; }

    const wchar_t* GetPlayerName(u32 player) { return mPlayerNames[player]; }
    void SetPlayerName(u32 player, const wchar_t* name) {
        wcsncpy(mPlayerNames[player], name, scPlayerNameLength);
    }

    RPSysKokeshiIcon* GetKokeshiIcon(u32 player) {
        return mPlayerIcons[player];
    }
    void SetKokeshiIcon(u32 player, RPSysKokeshiIcon* icon) {
        mPlayerIcons[player] = icon;
    }

    bool IsOnlinePlay() const { return mIsOnlinePlay; }
    void SetOnlinePlay(bool online) { mIsOnlinePlay = online; }

    bool IsServer() const { return mIsServer; }
    bool IsClient() const { return !IsServer(); }

    void SetPlayerConnectCallback(PlayerStateCallback callback) {
        mOnConnect = callback;
    }

    void SetPlayerDisconnectCallback(PlayerStateCallback callback) {
        mOnDisconnect = callback;
    }

    void Reset();

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
    //! Room player count
    u32 mNumPlayers;
    //! Mii names of players in room
    wchar_t mPlayerNames[scPlayerNameLength][scMaxPlayers];
    //! Mii icons of players in room
    RPSysKokeshiIcon* mPlayerIcons[scMaxPlayers];

    //! Player connect callback
    PlayerStateCallback mOnConnect;
    //! Player disconnect callback
    PlayerStateCallback mOnDisconnect;

    static NetplayMgr* sInstance;
};

} // namespace spnet

#endif