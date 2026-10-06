#ifndef VERTRIX_REGS_CALL_H
#define VERTRIX_REGS_CALL_H
#include <stdint.h>

#include "actor_build.h"

/* The four argument registers of the original's register calling convention, tracked by the
 * recovered handlers so that every boundary call carries the values the original holds. */
typedef struct VertrixRegs
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
} VertrixRegs;

/* A call of the unrecovered routine target with the current registers; eax takes its result. */
static inline void vertrix_regs_call(const VertrixCalls *calls, VertrixRegs *regs, uint32_t target)
{
    regs->eax = vertrix_call(calls, target, regs->eax, regs->edx, regs->ebx, regs->ecx, 0);
}

/* The same with stdcall stack arguments. */
static inline void vertrix_regs_calln(const VertrixCalls *calls, VertrixRegs *regs, uint32_t target,
                                      const uint32_t *stack, unsigned count)
{
    regs->eax = vertrix_calln(calls, target, regs->eax, regs->edx, regs->ebx, regs->ecx, stack,
                              count, NULL);
}

/* `call [edx + offset]` where edx holds a vtable pointer: the target is the dword read there. */
static inline void vertrix_regs_virtual(const VertrixCalls *calls, const VertrixGlobals *globals,
                                        VertrixRegs *regs, uint32_t offset)
{
    vertrix_regs_call(calls, regs, globals->read(regs->edx + offset, globals->context));
}
#endif
