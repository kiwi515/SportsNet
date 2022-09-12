#ifndef NW4R_EF_DRAWPOINTSTRATEGY_H
#define NW4R_EF_DRAWPOINTSTRATEGY_H
#include "ef_drawstrategyimpl.h"
#include "types_nw4r.h"

namespace nw4r {
namespace ef {
// TODO: Implement the object accurately
struct DrawPointStrategy : DrawStrategyImpl {
    DrawPointStrategy();
    ~DrawPointStrategy();

    UNKTYPE Draw(const DrawInfo&, ParticleManager*);
};
} // namespace ef
} // namespace nw4r

#endif