#ifndef NW4R_SND_PLAYER_HEAP_H
#define NW4R_SND_PLAYER_HEAP_H
#include "snd_SoundHeap.h"
#include "types_nw4r.h"

namespace nw4r {
namespace snd {
namespace detail {
struct PlayerHeap : SoundHeap {
    ~PlayerHeap();
    UNKTYPE* Alloc(u32);
};
} // namespace detail
} // namespace snd
} // namespace nw4r

#endif