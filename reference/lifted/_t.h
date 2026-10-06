#ifndef VERTRIX_BONUS_LIFTED_H
#define VERTRIX_BONUS_LIFTED_H
#include "../../source/lifted_runtime.h"

typedef uint32_t (*VertrixLiftFunction)(LiftContext *, uint32_t, uint32_t, uint32_t,
                                       uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);

/* Number of lifted routines and the lifted routine for an original address (NULL when there
 * is none). Arguments: context, eax, edx, ebx, ecx, esi, edi, ebp, esp. */
uint32_t vertrix_lift_count(void);
VertrixLiftFunction vertrix_lift_find(uint32_t address);

uint32_t vertrix_lift_412650(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
uint32_t vertrix_lift_412690(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);
#endif
