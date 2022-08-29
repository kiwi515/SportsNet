#ifndef MATO_KERNEL_ASSERT_H
#define MATO_KERNEL_ASSERT_H

#ifndef NDEBUG
//! @brief Log a message to the console
#define MATO_LOG(msg) mato_log(msg)

//! @brief Log a variadic message to the console
#define MATO_LOG_EX(msg, ...) mato_log(msg, __VA_ARGS__)

//! @brief Log a message to the console when a condition is met
#define MATO_WARN(exp, msg)                                                    \
    if ((exp))                                                                 \
    MATO_LOG(msg)

//! @brief Log a variadic message to the console when a condition is met
#define MATO_WARN_EX(exp, msg, ...)                                            \
    if ((exp))                                                                 \
    MATO_LOG_EX(msg, __VA_ARGS__)

//! @brief Assert a condition and halt execution when it fails to hold
#define MATO_ASSERT(exp)                                                       \
    if (!(exp))                                                                \
    mato_fail_assert(__FILE__, __LINE__, #exp "\n")

//! @brief Assert a condition and halt execution when it fails to hold,
//! displaying a custom error message
#define MATO_ASSERT_EX(exp, ...)                                               \
    if (!(exp))                                                                \
    mato_fail_assert(__FILE__, __LINE__, __VA_ARGS__)
#else
#define MATO_LOG(msg)
#define MATO_LOG_EX(msg, ...)
#define MATO_WARN(exp, msg)
#define MATO_WARN_EX(exp, msg, ...)
#define MATO_ASSERT(exp, ...)
#define MATO_ASSERT_EX(exp, ...)
#endif

#ifdef __cplusplus
extern "C" {
#endif

void mato_log(const char* msg, ...);
void mato_fail_assert(const char* file, int line, const char* msg, ...);

#ifdef __cplusplus
}
#endif

#endif