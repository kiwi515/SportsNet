#ifndef EGG_CORE_VIDEO_H
#define EGG_CORE_VIDEO_H
#include "eggBitFlag.h"
#include "types_egg.h"

#include <RevoSDK/GX/GXFrameBuf.h>
#include <RevoSDK/VI/vi.h>

#define FRAMERATE_50HZ 50.0f
#define FRAMERATE_60HZ 59.94f

namespace EGG {
struct Video {
    inline Video(GXRenderModeObj* obj)
        : mRenderMode(NULL), mFlags(), mOSTick(0) {
        (void)initialize(obj);
    }

    GXRenderModeObj* initialize(GXRenderModeObj*);
    GXRenderModeObj* configure(GXRenderModeObj*);
    static u32 getTickPerVRetrace(u32);
    static u32 getTickPerVRetrace();
    static GXRenderModeObj* getStandardRenderModeObj();

    GXRenderModeObj* mRenderMode; // at 0x0
    TBitFlag<u8> mFlags;
    s32 mOSTick; // at 0x8
};
} // namespace EGG

#endif