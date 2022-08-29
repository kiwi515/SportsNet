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