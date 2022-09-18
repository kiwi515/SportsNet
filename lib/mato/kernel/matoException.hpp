#ifndef MATO_KERNEL_EXCEPTION_H
#define MATO_KERNEL_EXCEPTION_H
#include "types.h"

#include <OS/OSContext.h>
#include <OS/OSError.h>

namespace mato {

/**
 * @brief Exception handler debugging utility
 */
class Exception {
public:
    static void Initialize();
    static void DumpException(u8 err, OSContext* ctx, u32 dsisr, u32 dar, ...);

private:
    static void Printf(const char* fmt, ...);
    static void PrintSymbol(const void* addr);
    static void FillFPUContext(OSContext* ctx);

private:
    //! Maximum stack trace depth during exception handling
    static const int scStackTraceMaxDepth = 5;

    //! Exception text buffer
    static char sTextBuffer[2048];
    static int sTextBufferPos;

    //! Exception name table
    static const char* sExceptionNames[OS_ERR_MAX];
};

} // namespace mato

#endif