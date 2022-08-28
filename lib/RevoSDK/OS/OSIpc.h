#ifndef RVL_SDK_OS_IPC_H
#define RVL_SDK_OS_IPC_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void* OS_IPC_BUFFER_LO : 0x80003130;
void* OS_IPC_BUFFER_HI : 0x80003134;

void* __OSGetIPCBufferHi(void);
void* __OSGetIPCBufferLo(void);
void __OSInitIPCBuffer(void);

#ifdef __cplusplus
}
#endif
#endif
