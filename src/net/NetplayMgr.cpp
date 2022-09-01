#include "NetplayMgr.hpp"

#include <string.h>

namespace spnet {

void NetplayMgr::CreateInstance() {
    if (sInstance == NULL) {
        sInstance = new NetplayMgr();
    }
}

void NetplayMgr::DestroyInstance() { delete sInstance; }

NetplayMgr::NetplayMgr() : mIsOnlinePlay(false), mIsServer(false) {
    ;
    ;
}

NetplayMgr::NetplayMgr(const NetplayMgr& other) { MATO_ASSERT(false); }

NetplayMgr::~NetplayMgr() {
    ;
    ;
}

const char* NetplayMgr::GetPlayerName(u32 player) {
    return mPlayerNames[player];
}

void NetplayMgr::SetPlayerName(u32 player, const char* name) {
    strncpy(mPlayerNames[player], name, scPlayerNameLength);
}

} // namespace spnet