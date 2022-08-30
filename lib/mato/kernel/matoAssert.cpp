#include "matoAssert.h"

#include "types.h"

#include <GX/GX.h>
#include <OS/OSError.h>
#include <OS/OSFatal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static const GXColor scFatalBG = {0, 142, 161, 255};
static const GXColor scFatalFG = {255, 255, 255, 0};

/**
 * @brief Log message to the console
 * @note Newline is automatically appended
 */
void mato_log(const char* msg, ...) {
    // Format message
    char msg_buf[0x800];
    va_list list;
    va_start(msg, list);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);

    OSReport("%s\n", msg_buf);
}

/**
 * @brief Halt execution and display assertion error to screen.
 * @note Newline is automatically appended
 */
void mato_fail_assert(const char* file, int line, const char* msg, ...) {
    mato_log("------------- HALT -------------");

    // Format message
    char msg_buf[0x800];
    va_list list;
    va_start(msg, list);
    vsnprintf(msg_buf, sizeof(msg_buf), msg, list);
    va_end(list);

    // Format full string
    char assert_buf[0x1000];
    snprintf(assert_buf, sizeof(assert_buf),
             "Assertion Failed: %s\nFile: %s(%d)", msg_buf, file, line);

    // Print to console
    mato_log("Program Halt");

    // Print to screen + console
    OSFatal(scFatalFG, scFatalBG, assert_buf);
}
kmBranch(0x800a1f08, mato_fail_assert);