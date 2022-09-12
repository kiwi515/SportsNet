#ifndef REVOSDK_AX_VPB_H
#define REVOSDK_AX_VPB_H
#include "AX.h"

#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

UNKTYPE AXSetMaxDspCycles(UNKWORD);
UNKWORD AXGetMaxVoices(void);

#ifdef __cplusplus
}
#endif
#endif