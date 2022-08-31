#ifndef __TYPES_H__
#define __TYPES_H__
#include "matoAssert.h"

#include <kamek.h>
#include <stdarg.h>
#include <stddef.h>

#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))
#define ROUND_UP_PTR(x, align)                                                 \
    ((void*)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void*)(((u32)(x)) & (~((align)-1))))

#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))

//! @brief Create dummy function to call a member function
#define kmInjectMF(cls, func)                                                  \
    static UNKWORD KM_HOOK_MF_##cls##_##func(void* arg, ...) {                 \
        typedef UNKWORD (cls::*##cls##_fun_t)(...);                            \
        const cls##_fun_t mem_fun = (cls##_fun_t)(cls::func);                  \
        cls* self = reinterpret_cast<cls*>(arg);                               \
        return (self->*mem_fun)();                                             \
    }

//! @brief Call hook a member/thiscall function
#define kmCallMF(addr, cls, func)                                              \
    kmInjectMF(cls, func);                                                     \
    kmCall(addr, KM_HOOK_MF_##cls##_##func);

//! @brief Branch hook a member/thiscall function
#define kmBranchMF(addr, cls, func)                                            \
    kmInjectMF(cls, func);                                                     \
    kmBranch(addr, KM_HOOK_MF_##cls##_##func);

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;

typedef int UNKWORD;
typedef void UNKTYPE;

typedef enum { FALSE, TRUE } BOOL;

void* operator new(size_t size);
void* operator new[](size_t size);

void* operator new(size_t size, s32 align);
void* operator new[](size_t size, s32 align);

void operator delete(void* block);
void operator delete[](void* block);

#endif