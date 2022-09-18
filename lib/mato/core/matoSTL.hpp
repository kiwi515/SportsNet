#ifndef MATO_KERNEL_STL_H
#define MATO_KERNEL_STL_H
#include "types.h"

#include <stdio.h>
#include <string.h>

namespace mato {

bool isdigit(char c);
bool isalpha(char c);
bool isupper(char c);
bool islower(char c);

char* strchr(const char* str, char c);
s32 strtol(const char* str, char** endptr, int base);
u32 strtoul(const char* str, char** endptr, int base);

size_t strnlen(const char* s, size_t maxlen);

} // namespace mato

#endif