#ifndef RP_KERNEL_LYT_ALLOCATOR_H
#define RP_KERNEL_LYT_ALLOCATOR_H
#include "types_RP.h"

#include <egg/core/eggAllocator.h>

/**
 * @brief Memory allocator for layouts
 * @details Wrapper for EGG::Allocator with custom free func
 * @wfuname
 */
class RPSysLytAllocator : public EGG::Allocator {
public:
    //! @address 8019e434
    RPSysLytAllocator(EGG::Heap* heap, s32 r5);

    //! @address 8019e3dc
    virtual ~RPSysLytAllocator();

private:
    /**
     * @brief Alloc/free funcs
     * @note Base class's funcs point here
     */
    MEMAllocatorFuncs mFuncs; // at 0x14
};

/**
 * @brief Layout allocator free func
 * @note Alloc func is carried over from base class
 * @address 8019e490
 */
static void FreeMemory(MEMAllocator* allocator, void* mem);

#endif