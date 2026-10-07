#ifndef VERTRIX_DWORD_TRANSITION_H
#define VERTRIX_DWORD_TRANSITION_H
#include <stddef.h>
#include <stdint.h>
/* Original variants 0x4ad6e0, 0x4acc70: wrapped 32-bit distance and signed clamps.
 * Returns one while moving, zero on arrival, minus one for NULL storage. */
int vertrix_dword_transition(int32_t *current, int32_t target, int32_t step, uint32_t cycles);

enum
{
    VERTRIX_TRANSITION_FIRST = 0x58,
    VERTRIX_TRANSITION_SECOND = 0x70
};

/* Original variants 0x4ad6e0, 0x4ad790: 0x4ad6e0 (first = 0x58: current +0x58, target +0x5c, step
 * +0x60) and 0x4ad790 (first = 0x70: current +0x70, target +0x74, step +0x78): step the dword at
 * first towards the dword at first + 4 by cycles times the dword at first + 8, through
 * vertrix_dword_transition. *moving is its result (1 while moving, 0 on arrival). Returns zero for
 * storage too short for the three dwords. */
int vertrix_actor_dword_transition(void *actor, size_t size, size_t first, uint32_t cycles,
                                   uint32_t *moving);
#endif
