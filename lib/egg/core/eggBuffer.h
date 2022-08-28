#ifndef EGG_CORE_BUFFER_H
#define EGG_CORE_BUFFER_H
#include "eggAssert.h"
#include "eggHeap.h"
#include "types_egg.h"

namespace EGG {
template <typename T> class TBuffer {
public:
    TBuffer() : mSize(0), mBuffer(NULL) {}

    virtual ~TBuffer() // at 0x8
    {
        if (mBuffer != NULL) {
            delete[] mBuffer;
            mBuffer = NULL;
        }
    }

    virtual void allocate(int n, int) // at 0xC
    {
        mSize = n;
        mBuffer = new T[n];
        onAllocate(NULL);
    }

    virtual void allocate(int n, Heap* heap, int) // at 0x10
    {
        mSize = n;
        if (heap == NULL)
            heap = Heap::sCurrentHeap;
        mBuffer = new (heap, 4) T[mSize];
        onAllocate(heap);
    }

    virtual void onAllocate(Heap*) {}    // at 0x14
    virtual void errRangeOver() const {} // at 0x18

    int getSize() const { return mSize; }

    T& operator()(int i) {
        checkRange(i);
        return mBuffer[i];
    }

private:
    void checkRange(int i) const {
        if (!isRangeValid(i)) {
            errRangeOver();
            EGG_ASSERT_MSG(false, "TBuffer::checkRange %d (0<=x<%d)\n", i,
                           mSize);
        }
    }

    bool isRangeValid(int i) const { return (i >= 0 && i < mSize); }

private:
    int mSize;  // at 0x4
    T* mBuffer; // at 0x8
};
} // namespace EGG

#endif