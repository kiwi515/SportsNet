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

private:
    NetplayMgr();
    NetplayMgr(const NetplayMgr&);
    virtual ~NetplayMgr();

private:
    bool mIsOnlinePlay;

    static NetplayMgr* sInstance;
};

} // namespace spnet

#endif