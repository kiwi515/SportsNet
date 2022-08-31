#include "NetplayMgr.hpp"

namespace spnet {

void NetplayMgr::CreateInstance() {
    if (sInstance == NULL) {
        sInstance = new NetplayMgr();
    }
}

void NetplayMgr::DestroyInstance() { delete sInstance; }

NetplayMgr::NetplayMgr() : mIsOnlinePlay(false) {
    ;
    ;
}

NetplayMgr::NetplayMgr(const NetplayMgr& other) { MATO_ASSERT(false); }

NetplayMgr::~NetplayMgr() {
    ;
    ;
}

} // namespace spnet