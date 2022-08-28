#ifndef REVOSDK_TRK___VA_ARG
#define REVOSDK_TRK___VA_ARG
#ifdef __cplusplus
extern "C" {
#endif

typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char* input_arg_area;
    char* reg_save_area;
} va_list[1];

void* __va_arg(va_list, int);

#ifdef __cplusplus
}
#endif
#endif