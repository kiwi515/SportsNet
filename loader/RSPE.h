#ifndef LOADER_RSPE_H
#define LOADER_RSPE_H
#include "kamekLoader.h"

void* allocAdapter(u32 size, bool isForCode, const loaderFunctions* funcs);
void freeAdapter(void* buffer, bool isForCode, const loaderFunctions* funcs);

typedef void* (*EGG_Heap_Alloc_t)(u32 size, s32 align, void* heap);
typedef void (*EGG_Heap_Free_t)(void* buffer, void* heap);

struct loaderFunctionsEx {
    loaderFunctions base;
    EGG_Heap_Alloc_t eggAlloc;
    EGG_Heap_Free_t eggFree;
};

const loaderFunctionsEx functions_us_rev1 = {
    {(OSReport_t)0x80183f18, (OSFatal_t)0x800efd3c,
     (DVDConvertPathToEntrynum_t)0x80139650, (DVDFastOpen_t)0x80139958,
     (DVDReadPrio_t)0x80139f38, (DVDClose_t)0x80139c6c, (sprintf_t)0x800b75d8,
     allocAdapter, freeAdapter},
    (EGG_Heap_Alloc_t)0x800a2e38,
    (EGG_Heap_Free_t)0x800a30a0,
};

#endif