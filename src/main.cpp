#include "types.h"

#include <mato/kernel/matoMapFile.hpp>
#include <mato/kernel/matoMemMgr.hpp>

void spnet_main() {
    // Setup heap
    mato::MemManager::Initialize();
    // Open symbol map
    mato::MapFile::GetInstance().LoadFromDVD("modules/SportsNet_NTSC_U.map",
                                             mato::MapFile::LINK_DYNAMIC);
}
kmBranch(0x80183b9c, spnet_main);