#ifndef NW4R_EF_DRAWORDER
#define NW4R_EF_DRAWORDER
#include "ef_draworderbase.h"
#include "ef_particlemanager.h"
#include "types_nw4r.h"

namespace nw4r {
namespace ef {
struct DrawOrder : DrawOrderBase {
    void Draw(Effect*, const DrawInfo&);
    void Add(Effect*, ParticleManager*);
    void Remove(Effect*, ParticleManager*);
};
} // namespace ef
} // namespace nw4r

#endif