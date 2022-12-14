#ifndef NW4R_G3D_INIT_H
#define NW4R_G3D_INIT_H
#include "types_nw4r.h"

#include <RevoSDK/OS/OS.h>

namespace nw4r {
namespace g3d {
void InitFastCast() {
    OSInitFastCast();
    OSSetGQR6(7, 5);
    OSSetGQR7(7, 8);
}

void G3dInit(bool);
void G3dReset();
} // namespace g3d
} // namespace nw4r

#endif