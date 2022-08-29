#include "matoMemMgr.hpp"

namespace mato {

/**
 * @brief Initialize Mato main heap
 */
void MemManager::Initialize() {
    MATO_ASSERT_EX(sHeap == NULL, "MemManager already initialized!");

    // Child of sAllocatableHeap
    sHeap = EGG::ExpHeap::create(sHeapSize, NULL, 0);
    MATO_ASSERT_EX(sHeap != NULL, "Main game heap creation failed!!!");
}

EGG::ExpHeap* MemManager::sHeap = NULL;
u32 MemManager::sHeapSize = 64 * 1024; // 64KB

} // namespace mato

void* operator new(size_t size) { return mato::MemManager::Alloc(size, 4); }
void* operator new[](size_t size) { return mato::MemManager::Alloc(size, 4); }

void* operator new(size_t size, s32 align) {
    return mato::MemManager::Alloc(size, align);
}
void* operator new[](size_t size, s32 align) {
    return mato::MemManager::Alloc(size, align);
}

void operator delete(void* block) { mato::MemManager::Free(block); }
void operator delete[](void* block) { mato::MemManager::Free(block); }