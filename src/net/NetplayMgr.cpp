#include "NetplayMgr.hpp"

#include <TRK/__mem.h>
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

/**
 * @brief Reset netplay settings (for exiting/changing scene)
 */
void NetplayMgr::Exit() {
    mIsOnlinePlay = false;
    mIsServer = false;
    memset(mPlayerNames, 0, sizeof(mPlayerNames));
}

const char* NetplayMgr::GetPlayerName(u32 player) {
    return mPlayerNames[player];
}

void NetplayMgr::SetPlayerName(u32 player, const char* name) {
    strncpy(mPlayerNames[player], name, scPlayerNameLength);
}

} // namespace spnet