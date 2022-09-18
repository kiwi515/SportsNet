#include "NetplayMgr.hpp"
#include "Socket.hpp"
#include "types.h"

#include <mato/kernel/matoException.hpp>
#include <mato/kernel/matoMapFile.hpp>
#include <mato/kernel/matoMemMgr.hpp>

namespace spnet {

void spnet_main() {
    // Initialize heap
    mato::MemManager::Initialize();

    // Initialize exceptions
    mato::Exception::Initialize();
    // Open symbol map
    mato::MapFile::GetInstance().LoadFromDVD("modules/SportsNet_NTSC_U.map",
                                             mato::MapFile::LINK_DYNAMIC);

    // Initialize networking
    Socket::Initialize();
    NetplayMgr::CreateInstance();
}
kmBranch(0x80182ee8, spnet_main);

} // namespace spnet