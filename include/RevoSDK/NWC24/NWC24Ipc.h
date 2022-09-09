#ifndef RVL_SDK_NWC24_IPC_H
#define RVL_SDK_NWC24_IPC_H
#include <IPC/ipcclt.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 NWC24iOpenResourceManager(const char* function, const char* file,
                              s32* result, IPCOpenMode);
s32 NWC24iCloseResourceManager(const char* function, s32 fd);
s32 NWC24iIoctlResourceManager(const char* function, s32, IPCIoctlType, void*,
                               s32, void*, s32);

#ifdef __cplusplus
}
#endif
#endif
