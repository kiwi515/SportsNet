#include "Socket.hpp"
#include "SocketTest.hpp"
#include "types.h"

#include <mato/kernel/matoMapFile.hpp>
#include <mato/kernel/matoMemMgr.hpp>

namespace spnet {

void spnet_main() {
    // Setup heap
    mato::MemManager::Initialize();
    // Open symbol map
    mato::MapFile::GetInstance().LoadFromDVD("modules/SportsNet_NTSC_U.map",
                                             mato::MapFile::LINK_DYNAMIC);

    // Initialize networking
    Socket::Initialize();

#ifndef NDEBUG
    SocketTest::DoTest();
#endif
}
kmBranch(0x80182ee8, spnet_main);

} // namespace spnet