#ifndef REVOSDK_KPAD_H
#define REVOSDK_KPAD_H
#ifdef __cplusplus
#include <types.h>
extern "C" {
#endif

typedef struct {

} KPADStatus;

void KPADSetPosParam(s32 chan, f32, f32);
void KPADSetHoriParam(s32 chan, f32, f32);
void KPADSetDistParam(s32 chan, f32, f32);
void KPADSetAccParam(s32 chan, f32, f32);

s32 KPADRead(s32 chan, UNKTYPE*, UNKWORD);
void KPADInit(void);

#ifdef __cplusplus
}
#endif
#endif