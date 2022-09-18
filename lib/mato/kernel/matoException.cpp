#include "matoException.hpp"

#include "matoAlgorithm.hpp"
#include "matoMapFile.hpp"
#include "matoRuntime.h"
#include "matoSTL.hpp"

#include <GX/GX.h>
#include <OS/OSFatal.h>
#include <TRK/__mem.h>
#include <stdio.h>
#include <string.h>

namespace mato {

static const GXColor scFatalBG = {0, 142, 161, 255};
static const GXColor scFatalFG = {255, 255, 255, 0};

/**
 * @brief Register exception handler
 */
void Exception::Initialize() {
    OSSetErrorHandler(OS_ERR_DSI, Exception::DumpException);
    OSSetErrorHandler(OS_ERR_ISI, Exception::DumpException);
    OSSetErrorHandler(OS_ERR_ALIGNMENT, Exception::DumpException);
    OSSetErrorHandler(OS_ERR_PROTECTION, Exception::DumpException);
    OSSetErrorHandler(OS_ERR_FP_EXCEPTION, NULL);
}

/**
 * @brief Dump exception contents to the screen
 *
 * @param err Error type
 * @param ctx Exception context
 * @param dsisr Exception DSISR value
 * @param dar Exception DAR value
 * @param ...
 */
void Exception::DumpException(u8 err, OSContext* ctx, u32 dsisr, u32 dar, ...) {
    MATO_ASSERT(ctx != NULL);

    // Get floating point registers
    FillFPUContext(ctx);

    // Setup text buffer
    memset(sTextBuffer, 0, sizeof(sTextBuffer));
    sTextBufferPos = 0;

    // Exception type
    Printf("%s exception\n", sExceptionNames[err]);

    // Last instruction
    Printf("SRR0: ");
    // Attempt to get symbol
    PrintSymbol(reinterpret_cast<void*>(ctx->srr0));
    Printf("\n\n");

    // Show stack trace
    Printf("Stack trace (at most last %d):\n", scStackTraceMaxDepth);
    u32* sp = reinterpret_cast<u32*>(ctx->gprs[1]);
    for (int i = 0; i < scStackTraceMaxDepth && (u32)sp != 0xFFFFFFFF; i++) {
        // LR save
        Printf("- ");
        PrintSymbol(reinterpret_cast<void*>(sp[1]));
        Printf("\n");
        // Back chain
        sp = (u32*)*sp;
    }

    // Show information on screen
    OSFatal(scFatalFG, scFatalBG, sTextBuffer);
}

/**
 * @brief Append to exception text buffer
 */
void Exception::Printf(const char* fmt, ...) {
    char buf[sizeof(sTextBuffer)];

    // Make sure buffer is not full
    if (sTextBufferPos >= sizeof(sTextBuffer)) {
        MATO_LOG("Exception text buffer full!");
        return;
    }

    // Format text
    va_list list;
    va_start(fmt, list);
    vsnprintf(buf, sizeof(buf), fmt, list);
    va_end(list);

    // Append to buffer
    strncat(sTextBuffer, buf, sizeof(sTextBuffer) - sTextBufferPos);
    sTextBufferPos += strnlen(buf, sizeof(buf));
}

/**
 * @brief Attempt to resolve address to a symbol and print it
 *
 * @param addr Address (expected to be in code)
 */
void Exception::PrintSymbol(const void* addr) {
    // Query symbol map
    const MapFile::Symbol* sym = MapFile::GetInstance().QueryTextSymbol(addr);

    if (sym != NULL) {
        // Offset into function where exception occurred
        const u32 offset =
            (sym->type == MapFile::LINK_DYNAMIC)
                ? PtrDistance(AddToPtr(GetTextStart(), sym->offset), addr)
                : PtrDistance(sym->addr, addr);
        Printf("%s(+0x%04X)", sym->name, offset);
    } else {
        Printf("%08X", addr);
    }
}

/**
 * @brief Fill in floating point registers
 * @note Implementation from OSFillFPUContext (deadstripped from OGWS)
 *
 * @param ctx Exception context
 */
void Exception::FillFPUContext(register OSContext* ctx) {
    asm {
        // clang-format off
        mfmsr r5
        ori r5, r5, 0x2000
        mtmsr r5
        isync

        stfd f0, 0x90(ctx)
        stfd f1, 0x98(ctx)
        stfd f2, 0xa0(ctx)
        stfd f3, 0xa8(ctx)
        stfd f4, 0xb0(ctx)
        stfd f5, 0xb8(ctx)
        stfd f6, 0xc0(ctx)
        stfd f7, 0xc8(ctx)
        stfd f8, 0xd0(ctx)
        stfd f9, 0xd8(ctx)
        stfd f10, 0xe0(ctx)
        stfd f11, 0xe8(ctx)
        stfd f12, 0xf0(ctx)
        stfd f13, 0xf8(ctx)
        stfd f14, 0x100(ctx)
        stfd f15, 0x108(ctx)
        stfd f16, 0x110(ctx)
        stfd f17, 0x118(ctx)
        stfd f18, 0x120(ctx)
        stfd f19, 0x128(ctx)
        stfd f20, 0x130(ctx)
        stfd f21, 0x138(ctx)
        stfd f22, 0x140(ctx)
        stfd f23, 0x148(ctx)
        stfd f24, 0x150(ctx)
        stfd f25, 0x158(ctx)
        stfd f26, 0x160(ctx)
        stfd f27, 0x168(ctx)
        stfd f28, 0x170(ctx)
        stfd f29, 0x178(ctx)
        stfd f30, 0x180(ctx)
        stfd f31, 0x188(ctx)

        mffs f0
        stfd f0, 0x190(ctx)
        lfd f0, 0x90(ctx)
        mfspr r5, 0x398
        rlwinm. r5, r5, 3, 0x1f, 0x1f
        beq no_ps

        psq_st f0, 456(ctx), 0, 0
        psq_st f1, 464(ctx), 0, 0
        psq_st f2, 472(ctx), 0, 0
        psq_st f3, 480(ctx), 0, 0
        psq_st f4, 488(ctx), 0, 0
        psq_st f5, 496(ctx), 0, 0
        psq_st f6, 504(ctx), 0, 0
        psq_st f7, 512(ctx), 0, 0
        psq_st f8, 520(ctx), 0, 0
        psq_st f9, 528(ctx), 0, 0
        psq_st f10, 536(ctx), 0, 0
        psq_st f11, 544(ctx), 0, 0
        psq_st f12, 552(ctx), 0, 0
        psq_st f13, 560(ctx), 0, 0
        psq_st f14, 568(ctx), 0, 0
        psq_st f15, 576(ctx), 0, 0
        psq_st f16, 584(ctx), 0, 0
        psq_st f17, 592(ctx), 0, 0
        psq_st f18, 600(ctx), 0, 0
        psq_st f19, 608(ctx), 0, 0
        psq_st f20, 616(ctx), 0, 0
        psq_st f21, 624(ctx), 0, 0
        psq_st f22, 632(ctx), 0, 0
        psq_st f23, 640(ctx), 0, 0
        psq_st f24, 648(ctx), 0, 0
        psq_st f25, 656(ctx), 0, 0
        psq_st f26, 664(ctx), 0, 0
        psq_st f27, 672(ctx), 0, 0
        psq_st f28, 680(ctx), 0, 0
        psq_st f29, 688(ctx), 0, 0
        psq_st f30, 696(ctx), 0, 0
        psq_st f31, 704(ctx), 0, 0

    no_ps:
        blr
        // clang-format on
    }
}

char Exception::sTextBuffer[2048];
int Exception::sTextBufferPos = 0;

/**
 * @brief Table of exception names
 */
const char* Exception::sExceptionNames[OS_ERR_MAX] = {"System Reset",
                                                      "Machine Check",
                                                      "DSI",
                                                      "ISI",
                                                      "External Interrupt",
                                                      "Alignment",
                                                      "Program",
                                                      "Floating Point",
                                                      "Decrementer",
                                                      "System Call",
                                                      "Trace",
                                                      "Performance Monitor",
                                                      "Break Point",
                                                      "System Interrupt",
                                                      "Thermal Interrupt",
                                                      "Protection",
                                                      "Floating Point"};

} // namespace mato