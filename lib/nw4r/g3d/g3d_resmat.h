#ifndef NW4R_G3D_RESMAT_H
#define NW4R_G3D_RESMAT_H
#include "g3d_rescommon.h"
#include "math_types.h"
#include "types_nw4r.h"

namespace nw4r {
namespace g3d {
struct ResTexPlttInfoData {
    u32 mNumOffsets; // at 0x0

    struct InfoOffset {
        u32 mResOffset; // at 0x0
        u32 mTexOffset; // at 0x4
    } mOffsets[];       // at 0x4
};

struct ResTexPlttInfo {
    ResCommon<ResTexPlttInfoData> mInfo;

    inline ResTexPlttInfo(void* vptr) : mInfo(vptr) {}
};

struct ResMatData {
    // . . .
};

struct ResMat {
    ResCommon<ResMatData> mMat;

    inline ResMat(void* vptr) : mMat(vptr) {}
    bool Bind(ResFile);
    UNKTYPE Release();
    UNKTYPE Init();
};
} // namespace g3d
} // namespace nw4r

#endif