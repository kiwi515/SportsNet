#ifndef NW4R_EF_DRAWBILLBOARDSTRATEGY_H
#define NW4R_EF_DRAWBILLBOARDSTRATEGY_H
#include "ef_drawstrategyimpl.h"
#include "types_nw4r.h"

namespace nw4r {
namespace ef {
// TODO: Implement the object accurately
struct DrawBillboardStrategy : DrawStrategyImpl {
    DrawBillboardStrategy();
    ~DrawBillboardStrategy();

    UNKTYPE Draw(const DrawInfo&, ParticleManager*);
    virtual UNKTYPE GetCalcAheadFunc(ParticleManager*);
};
} // namespace ef
} // namespace nw4r

#endif