#ifndef RVL_SDK_GX_TRANSFORM_H
#define RVL_SDK_GX_TRANSFORM_H
#include "GX.h"
#include "GXTev.h"

#include <MTX/mtx.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

void __GXSetProjection(void);
void GXSetProjection(const Mtx44, GXProjectionType);
void GXSetProjectionv(const f32*);
void GXGetProjectionv(f32*);
void GXLoadPosMtxImm(const Mtx, u32);
void GXLoadPosMtxIndx(u16, u32);
void GXLoadNrmMtxImm(const Mtx, u32);
void GXLoadNrmMtxIndx3x3(u16, u32);
void GXSetCurrentMtx(u32);
void GXLoadTexMtxImm(const Mtx, u32, UNKWORD);
void __GXSetViewport(void);
void GXSetViewportJitter(f32, f32, f32, f32, f32, f32, u8);
void GXSetViewport(f32, f32, f32, f32, f32, f32);
void GXGetViewportv(f32*);
void GXSetZScaleOffset(f32, f32);
void GXSetScissor(u32, u32, u32, u32);
void GXGetScissor(u32*, u32*, u32*, u32*);
void GXSetScissorBoxOffset(u32, u32);
void GXSetClipMode(UNKWORD);
void __GXSetMatrixIndex(UNKWORD);

#ifdef __cplusplus
}
#endif
#endif
