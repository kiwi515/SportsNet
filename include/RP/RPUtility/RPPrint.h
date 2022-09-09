#ifndef RP_UTILITY_PRINT_H
#define RP_UTILITY_PRINT_H
#include "types.h"
#include <string.h>

void RPPrint(f32 x, f32 y, f32 scale, const char *msg, u32 color, bool param_6);

inline void RPPrintOutline(f32 x, f32 y, f32 scale, const char *msg, u32 textColor, u32 outlineColor, bool param_6)
{
    // Outline 
    RPPrint(x - 2.0f, y + 0.0f, scale, msg, outlineColor, param_6);
    RPPrint(x + 2.0f, y + 0.0f, scale, msg, outlineColor, param_6);
    RPPrint(x + 0.0f, y - 2.0f, scale, msg, outlineColor, param_6);
    RPPrint(x + 0.0f, y + 2.0f, scale, msg, outlineColor, param_6);

    // Text
    RPPrint(x, y, scale, msg, textColor, param_6);
}

inline void RPPrintShadow(f32 x, f32 y, f32 scale, const char *msg, u32 textColor, u32 shadowColor, bool param_6)
{
    // Shadow (bottom right)
    RPPrint(x - 2.0f, y - 2.0f, scale, msg, shadowColor, param_6);

    // Text
    RPPrint(x, y, scale, msg, textColor, param_6);
}

#define RPPrintf(x, y, scale, msg, color, param_6, ...) \
{ \
    char __buf__[1024]; \
    sprintf(__buf__, msg, __VA_ARGS__); \
    RPPrint(x, y, scale, __buf__, color, param_6); \
}

#define RPPrintfOutline(x, y, scale, msg, textColor, outlineColor, param_6, ...) \
{ \
    char __buf__[1024]; \
    sprintf(__buf__, msg, __VA_ARGS__); \
    RPPrint(x - 2.0f, y + 0.0f, scale, __buf__, outlineColor, param_6); \
    RPPrint(x + 2.0f, y + 0.0f, scale, __buf__, outlineColor, param_6); \
    RPPrint(x + 0.0f, y - 2.0f, scale, __buf__, outlineColor, param_6); \
    RPPrint(x + 0.0f, y + 2.0f, scale, __buf__, outlineColor, param_6); \
    RPPrint(x, y, scale, __buf__, textColor, param_6); \
}

#define RPPrintfShadow(x, y, scale, msg, textColor, shadowColor, param_6, ...) \
{ \
    char __buf__[1024]; \
    sprintf(__buf__, msg, __VA_ARGS__); \
    RPPrint(x - 2.0f, y - 2.0f, scale, __buf__, shadowColor, param_6); \
    RPPrint(x, y, scale, __buf__, textColor, param_6); \
}

#endif