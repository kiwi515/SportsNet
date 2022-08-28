#ifndef RVL_SDK_OS_FATAL_H
#define RVL_SDK_OS_FATAL_H
#include <GX/GX.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void OSFatal(GXColor fg, GXColor bg, const char* msg);

#ifdef __cplusplus
}
#endif
#endif
