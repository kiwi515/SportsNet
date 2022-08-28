#ifndef NW4R_EF_POINT_H
#define NW4R_EF_POINT_H
#include "ef_emitterform.h"

namespace nw4r {
namespace ef {
struct EmitterFormPoint : EmitterForm {
    virtual UNKTYPE Emission(Emitter*, ParticleManager*, int, u32, float*, u16,
                             float, const math::MTX34*);
};
} // namespace ef
} // namespace nw4r

#endif