#ifndef MATO_KERNEL_RUNTIME_H
#define MATO_KERNEL_RUNTIME_H
#include "matoAlgorithm.hpp"

namespace mato {

#ifdef __cplusplus
extern "C" {
#endif

//! @brief C++ static initializer function pointer
typedef void (*StaticCtor)(void);
extern StaticCtor __ctor_loc;
extern StaticCtor __ctor_end;

extern void* _f_init;
extern void* _e_init;

extern void* _f_text;
extern void* _e_text;

extern void* _f_ctors;
extern void* _e_ctors;

extern void* _f_dtors;
extern void* _e_dtors;

extern void* _f_rodata;
extern void* _e_rodata;

extern void* _f_data;
extern void* _e_data;

// .init section layout
static inline const void* GetInitStart() { return &_f_init; }
static inline const void* GetInitEnd() { return &_e_init; }
static inline u32 GetInitSize() {
    return PtrDistance(GetInitStart(), GetInitEnd());
}

// .text section layout
static inline const void* GetTextStart() { return &_f_text; }
static inline const void* GetTextEnd() { return &_e_text; }
static inline u32 GetTextSize() {
    return PtrDistance(GetTextStart(), GetTextEnd());
}

// .ctors section layout
static inline const void* GetCtorsStart() { return &_f_ctors; }
static inline const void* GetCtorsEnd() { return &_e_ctors; }
static inline u32 GetCtorsSize() {
    return PtrDistance(GetCtorsStart(), GetCtorsEnd());
}

// .dtors section layout
static inline const void* GetDtorsStart() { return &_f_dtors; }
static inline const void* GetDtorsEnd() { return &_e_dtors; }
static inline u32 GetDtorsSize() {
    return PtrDistance(GetDtorsStart(), GetDtorsEnd());
}

// .rodata section layout
static inline const void* GetRodataStart() { return &_f_rodata; }
static inline const void* GetRodataEnd() { return &_e_rodata; }
static inline u32 GetRodataSize() {
    return PtrDistance(GetRodataStart(), GetRodataEnd());
}

// .data section layout
static inline const void* GetDataStart() { return &_f_data; }
static inline const void* GetDataEnd() { return &_e_data; }
static inline u32 GetDataSize() {
    return PtrDistance(GetDataStart(), GetDataEnd());
}

#ifdef __cplusplus
}
#endif

//! @brief Begin ASM block
#define MATO_ASM_BEGIN asm volatile {
//! @brief End ASM block
#define MATO_ASM_END }

//! @brief Copy GPR to variable
#define MATO_GET_GPR(r, var)                                                   \
    asm volatile { mr var, r; }
//! @brief Copy variable to GPR
#define MATO_SET_GPR(r, var)                                                   \
    asm volatile { mr r, var; }

//! @brief Backup GPRs to stack frame
#define MATO_SAVE_GPRS                                                         \
    asm volatile {                                                             \
        stwu r1, -0x90(r1);                                                    \
        stmw r3, 0xC(r1);                                                      \
        mflr r12;                                                              \
        stw r12, 0x8(r1);                                                      \
    }

//! @brief Restore GPRs from stack frame
#define MATO_REST_GPRS                                                         \
    asm volatile {                                                             \
        lwz r12, 0x8(r1);                                                      \
        mtlr r12;                                                              \
        lmw r3, 0xC(r1);                                                       \
        addi r1, r1, 0x90;                                                     \
    }

} // namespace mato

#endif