#ifndef RVL_SDK_OS_UTF_H
#define RVL_SDK_OS_UTF_H
#include "OS.h"

#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

const u8* OSUTF8to32(const u8*, u32*);
const wchar_t* OSUTF16to32(const wchar_t*, u32*);
u8 OSUTF32toANSI(u32);
wchar_t OSUTF32toSJIS(u32);

#ifdef __cplusplus
}
#endif
#endif
