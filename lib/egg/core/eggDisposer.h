#ifndef EGG_CORE_DISPOSER_H
#define EGG_CORE_DISPOSER_H
#include "types_egg.h"

#include <nw4r/ut/ut_list.h>

namespace EGG {
struct Disposer {
    Disposer();
    virtual ~Disposer();

    Heap* mHeap;          // at 0x0
    nw4r::ut::Node mNode; // at 0x4
};
} // namespace EGG

#endif