#ifndef MATO_KERNEL_MEM_MGR_H
#define MATO_KERNEL_MEM_MGR_H
#include "matoAssert.h"
#include "types.h"

#include <egg/core/eggExpHeap.h>

namespace mato {

/**
 * @brief Mato memory manager
 * @details Manages child of main game heap
 */
class MemManager {
public:
    static void Initialize();

    static void* Alloc(u32 size, s32 align) {
        MATO_ASSERT(sHeap != NULL);
        return sHeap->alloc(size, align);
    }

    static void Free(void* block) {
        MATO_ASSERT(sHeap != NULL);
        sHeap->free(block);
    }

    static u32 GetFreeSize() {
        MATO_ASSERT(sHeap != NULL);
        return sHeap->getAllocatableSize(4);
    }

private:
    MemManager() {}
    ~MemManager() {}

    //! @brief Mato main heap
    static EGG::ExpHeap* sHeap;
    //! @brief Mato main heap size (configurable)
    static u32 sHeapSize;
};

} // namespace mato

inline void* operator new(size_t size) {
    return mato::MemManager::Alloc(size, 4);
}

inline void* operator new[](size_t size) {
    return mato::MemManager::Alloc(size, 4);
}

inline void operator delete(void* block) { mato::MemManager::Free(block); }

inline void operator delete[](void* block) { mato::MemManager::Free(block); }

#endif