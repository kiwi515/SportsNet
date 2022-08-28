#ifndef NW4R_EF_DRAWFREESTRATEGY_H
#define NW4R_EF_DRAWFREESTRATEGY_H
#include "ef_drawstrategyimpl.h"
#include "types_nw4r.h"

namespace nw4r {
namespace ef {
// TODO: Implement the object accurately
struct DrawFreeStrategy : DrawStrategyImpl {
    DrawFreeStrategy();
    ~DrawFreeStrategy();

    UNKTYPE Draw(const DrawInfo&, ParticleManager*);
};
} // namespace ef
} // namespace nw4r

#endif