#include "NetplayMgr.hpp"

#include <TRK/__mem.h>

namespace spnet {

void NetplayMgr::CreateInstance() {
    if (sInstance == NULL) {
        sInstance = new NetplayMgr();
    }
}

void NetplayMgr::DestroyInstance() { delete sInstance; }

NetplayMgr::NetplayMgr() { Reset(); }

NetplayMgr::NetplayMgr(const NetplayMgr& other) { MATO_ASSERT(false); }

NetplayMgr::~NetplayMgr() { Reset(); }

/**
 * @brief Reset netplay settings (for exiting/changing scene)
 */
void NetplayMgr::Reset() {
    mIsOnlinePlay = false;
    mIsServer = false;
    mNumPlayers = 1;
    memset(mPlayerNames, 0, sizeof(mPlayerNames));
    for (int i = 0; i < scMaxPlayers; i++) {
        delete mPlayerIcons[i];
        mPlayerIcons[i] = NULL;
    }
}

NetplayMgr* NetplayMgr::sInstance = NULL;

} // namespace spnet