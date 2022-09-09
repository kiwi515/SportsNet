#ifndef MSL_WPRINTF_H
#define MSL_WPRINTF_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int swprintf(wchar_t* ws, size_t len, const wchar_t* format, ...);

#ifdef __cplusplus
}
#endif
#endif