#include "RSPE.h"

#include "kamekLoader.h"

#include <RPKernel/RPSysSystem.h>
#include <STL/stdio.h>
#include <egg/core/eggHeap.h>

// Entrypoint is after system is initialized,
// but before its main loop is called
#ifdef SPNET_REGION_NTSC_U
const u32 RSPE_Entrypoint = 0x80183098;
#endif

void* allocAdapter(u32 size, bool isForCode, const loaderFunctions* funcs) {
#pragma unused(funcs)

    RPSysSystem* sys = RPSysSystem::getInstance();
    // Code goes in MEM1 while resources go in MEM2
    EGG::Heap* heap =
        (isForCode) ? sys->getSystemHeap() : sys->getResourceHeap();

    return sys->alloc(heap, size, 32);
}

void freeAdapter(void* buffer, bool isForCode, const loaderFunctions* funcs) {
#pragma unused(funcs)

    RPSysSystem* sys = RPSysSystem::getInstance();
    // Code goes in MEM1 while resources go in MEM2
    EGG::Heap* heap =
        (isForCode) ? sys->getSystemHeap() : sys->getResourceHeap();

    return sys->free(heap, buffer);
}

// Patch stubbed OSReport
// TO-DO: Make this work in C++
void OSReport(const char* msg, ...) {
    va_list list;
    va_start(msg, list);
    vprintf(msg, list);
    va_end(list);
}
#ifdef SPNET_REGION_NTSC_U
kmBranch(0x80183f18, OSReport);
#endif

void RSPE_Setup() {
    loadKamekBinaryFromDisc(&functions_us_rev1.base,
                            "/modules/SportsNet_NTSC_U.bin");
}

kmBranch(RSPE_Entrypoint, RSPE_Setup);
