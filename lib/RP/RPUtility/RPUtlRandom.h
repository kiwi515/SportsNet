#ifndef RP_UTILITY_RANDOM_H
#define RP_UTILITY_RANDOM_H
#include "types_RP.h"

class RPUtlRandom
{
public:
    static void initialize();
    static u32 getU32() { return calc() >> 16; }
    static u32 getU32(u32 max) { return getU32() % max; }
    static u32 getU32(u32 min, u32 max) { return getU32() % (max - min + 1) + min; }
    static f32 getF32() { return (f32)getU32() / 0x10000; }

private:
    RPUtlRandom() {}
    static void setSeed(u32 s) { sSeed = s; }
    static u32 calc() { return (sSeed = sSeed * sSeedStep + 1); }
    
    static const u32 sSeedStep = 69069;
    static u32 sSeed;
};

#endif