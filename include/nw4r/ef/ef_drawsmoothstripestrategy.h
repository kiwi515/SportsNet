#ifndef NW4R_EF_DRAWSMOOTHSTRIPESTRATEGY_H
#define NW4R_EF_DRAWSMOOTHSTRIPESTRATEGY_H
#include "ef_drawstrategyimpl.h"
#include "types_nw4r.h"

namespace nw4r {
namespace ef {
// TODO: Implement the object accurately
struct DrawSmoothStripeStrategy : DrawStrategyImpl {
    DrawSmoothStripeStrategy();
    ~DrawSmoothStripeStrategy();

    UNKTYPE Draw(const DrawInfo&, ParticleManager*);
    virtual UNKTYPE GetCalcAheadFunc(ParticleManager*);
};
} // namespace ef
} // namespace nw4r

#endif