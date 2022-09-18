#ifndef REVOSDK_VI_H
#define REVOSDK_VI_H
#ifdef __cplusplus
#include <GX/GXFrameBuf.h>
#include <types.h>
extern "C" {
#endif

typedef void (*VIRetraceCallback)(void);

enum VITvFormat {
    VI_NTSC,
    VI_PAL,
    VI_MPAL,
    VI_TV_FORMAT_3,
    VI_TV_FORMAT_4,
    VI_EURGB60
};

void VIInit(void);
void VISetBlack(UNKWORD);
void VIConfigure(GXRenderModeObj*);
void VIWaitForRetrace(void);

void VISetPreRetraceCallback(VIRetraceCallback);
void VISetPostRetraceCallback(VIRetraceCallback);

void VIFlush(void);

UNKTYPE* VIGetCurrentFrameBuffer(void);

UNKTYPE VISetNextFrameBuffer(UNKTYPE*);

UNKWORD VIGetRetraceCount(void);
enum VITvFormat VIGetTvFormat(void);

#ifdef __cplusplus
}
#endif
#endif