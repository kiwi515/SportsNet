#ifndef NW4R_UT_LOCK_H
#define NW4R_UT_LOCK_H
#include <OSInterrupt.h>
#include <OSMutex.h>

namespace nw4r {
namespace ut {
namespace detail {
inline void Lock(OSMutex& mutex) { OSLockMutex(&mutex); }

inline void Unlock(OSMutex& mutex) { OSUnlockMutex(&mutex); }

template <typename T> struct AutoLock {
    T& mMutex;

    inline AutoLock(T& rMutex) : mMutex(rMutex) { Lock(mMutex); }

    inline ~AutoLock() { Unlock(mMutex); }
};
} // namespace detail

struct AutoInterruptLock {
    UNKWORD WORD_0x0;

    inline AutoInterruptLock() : WORD_0x0(OSDisableInterrupts()) {}
    inline ~AutoInterruptLock() { OSRestoreInterrupts(WORD_0x0); }
};
} // namespace ut
} // namespace nw4r

#endif