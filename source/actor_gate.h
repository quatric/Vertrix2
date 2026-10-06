#ifndef VERTRIX_ACTOR_GATE_H
#define VERTRIX_ACTOR_GATE_H
#include <stddef.h>
#include <stdint.h>
/* Original render globals 5bb680..5bc01f. Offsets are original address minus base. */
#define VERTRIX_GATE_BASE 0x5bb680u
#define VERTRIX_GATE_SIZE 0x9a0u
/* Supplied read of original memory outside the globals (objects, image data, tables). Original
 * addresses are identity tokens. Returns zero when the address cannot be read. */
typedef int (*VertrixMemoryRead)(uint32_t address, unsigned width, uint32_t *value, void *context);
/* Original4ae3e0: actor clipping and span preparation. mode is actor dword144. Runs the complete
 * routine against the globals and the actor (at least 0x15c bytes), reads original memory through
 * read and reports the original eax in *result. Division by zero, unreadable memory, out-of-range
 * global writes and short storage return zero and preserve globals and actor. */
int vertrix_actor_gate(uint8_t *globals, void *actor, size_t actor_size, uint32_t mode,
                       VertrixMemoryRead read, void *context, uint32_t *result);
#endif
