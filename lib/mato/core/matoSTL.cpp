#include "matoSTL.hpp"

#include "matoAssert.h"

namespace mato {

/**
 * @brief Check if character is a decimal digit
 */
bool isdigit(char c) { return c >= '0' && c <= '9'; }

/**
 * @brief Check if character is alphabetic
 */
bool isalpha(char c) { return isupper(c) || islower(c); }

/**
 * @brief Check if character is uppercase
 */
bool isupper(char c) { return c >= 'A' && c <= 'Z'; }

/**
 * @brief Check if character is lowercase
 */
bool islower(char c) { return c >= 'a' && c <= 'z'; }

/**
 * @brief Find occurrence of character in string
 */
char* strchr(const char* str, char c) {
    MATO_ASSERT(str != NULL);

    for (char* p = (char*)str; *p != '\0'; p++) {
        if (*p == c) {
            return p;
        }
    }

    return NULL;
}

/**
 * @brief Convert string to signed long
 * @note Logic from UC implementation
 * @copyright Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. [rescinded 22 July 1999]
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
s32 strtol(const char* str, char** endptr, int base) {
    MATO_ASSERT(str != NULL);

    // Trim leading whitespace
    while (*str == ' ') {
        if (*str == '\0') {
            return 0;
        }
        str++;
    }

    // Sign (positive by default)
    bool positive = true;
    if (*str == '-') {
        positive = false;
        str++;
    } else if (*str == '+') {
        str++;
    }

    // Check prefix
    const char c0 = *str;
    const char c1 = *str + 1;

    // Auto-detect base
    // If base is octal/hex, just check for optional prefix
    if (base == 0 || base == 16) {
        // Valid hex prefix
        if (c0 == '0' && (c1 == 'x' || c1 == 'X')) {
            base = 16;
            str += sizeof('0x');
        }
    } else if (base == 0 || base == 8) {
        // Valid octal prefix
        if (c0 == '0') {
            base = 8;
            str += sizeof('0');
        }
    }

    MATO_ASSERT_EX(base != 0, "Failed to auto-detect base");
    MATO_ASSERT_EX(2 <= base <= 36, "Invalid base");

    // Parse digits
    s32 ret = 0;
    for (; *str != '\0'; str++) {
        const char digit = *str;

        if (isdigit(digit)) {
            ret *= base;
            ret += digit - '0';
        } else if (isalpha(digit)) {
            // Uppercase
            if (isupper(digit)) {
                ret *= base;
                ret += 0xA + digit - 'A';
            }
            // Lowercase
            else if (islower(digit)) {
                ret *= base;
                ret += 0xA + digit - 'a';
            }
        }
        // Conversion end
        else {
            if (endptr != NULL) {
                *endptr = (char*)str;
            }
            break;
        }
    }

    return ret;
}

/**
 * @brief Convert string to unsigned long
 */
u32 strtoul(const char* str, char** endptr, int base) {
    return (u32)strtol(str, endptr, base);
}

/**
 * @brief Get string length (at most maxlen)
 */
size_t strnlen(const char* s, size_t maxlen) {
    const u8* p = (const u8*)s;
    while (*p && maxlen-- > 0) {
        p++;
    }
    return (u32)p - (u32)s;
}

} // namespace mato