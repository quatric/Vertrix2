#ifndef VERTRIX_PARTICLE_SPAWN_H
#define VERTRIX_PARTICLE_SPAWN_H
#include "actor_chain_visit.h"
#include "board_cells.h"
#include "call_glue.h"
/* Initializers for the short-lived particle actors of the background effects. A child actor is
 * an object handle; every random value comes from the supplied draw (original 0x4826c0). */

/* Supplied boundary for the original random draw: a value below divisor (divisor nonzero). */
typedef uint16_t (*VertrixSpawnDraw)(uint16_t divisor, void *context);

/* Screen dimension words (0x5b9c8e, 0x5b9c90) and the scratch words every spawn routine stores in
 * its own globals: width, height, half width and half height (the second routine stores only the
 * first two). */
typedef struct
{
    uint16_t width;
    uint16_t height;
    uint16_t half_width;
    uint16_t half_height;
} VertrixSpawnScratch;

/* Supplied boundaries shared by the spawn routines. */
typedef struct
{
    VertrixObjectStorage resolve;
    VertrixImageLookup lookup; /* original 0x4877f0 behind the bind call 0x4ac8a0 */
    VertrixSpawnDraw draw;
    void *context;
} VertrixSpawnServices;

/* Original fragment 0x43dea0: spread particle. Attaches resource 0x544c10 with frame 15 (binding
 * the image), period 12 when the scene's dword +0x94c is 1 else 5, position words +0xe/+0x16 = 0
 * and velocity words +0x8/+0xa from draws below the screen width and height minus half of them
 * times 150, then +0x58 = 200, +0x5c = 0 and a lifetime +0x60 from a draw below 2 plus 1 (and word
 * +0x28 = 1 when +0x94c is 1). Returns zero for an unresolvable object. */
int vertrix_spawn_spread(uint32_t scene, uint32_t child, uint16_t width, uint16_t height,
                         VertrixSpawnScratch *scratch, const VertrixSpawnServices *services);

/* Original fragment 0x43e740: burst particle. Same placement and velocity as above with period 12,
 * +0x58 = 200, +0x5c = 0, +0x144 = 0 and a lifetime from a draw below 3 plus 1. */
int vertrix_spawn_burst(uint32_t child, uint16_t width, uint16_t height,
                        VertrixSpawnScratch *scratch, const VertrixSpawnServices *services);

/* Original fragment 0x43e840: drifting particle. Attaches resource 0x544c64, frame 0, period 60,
 * size words +0x8/+0xa = width/height, position +0xe/+0x16 from draws below them, handler 0x4574a0
 * and the timers +0x58 = 0, +0x60 = 1, +0x70 = 200, +0x64 = 100 and +0x5c = 100 plus a draw below
 * 200, byte +0x93 = 1, +0x4e = 0 and +0x44 = 0. scratch receives width and height only. */
int vertrix_spawn_drift(uint32_t child, uint16_t width, uint16_t height,
                        VertrixSpawnScratch *scratch, const VertrixSpawnServices *services);

/* Original fragment 0x43e920: place a sparkle. Byte +0x95 = 5 or 4 (5 when the dword +0xb8 is 1);
 * when +0xb8 is 2 the position is a draw below the size words +0x8/+0xa (the height range starts at
 * 0x136), otherwise a draw below 5 selects the position from the tables at 0x4fb93c and 0x4fb950.
 */
int vertrix_spawn_place(uint32_t child, const VertrixSpawnServices *services);
/* Original 0x43dea0: complete spread initialization using live screen/scratch globals,
 * scene state and actor storage. Calls carry scene in EBX and child in ECX to binding
 * 0x4ac8a0 and draws 0x4826c0. Return EAX is low word of final draw plus one. */
int vertrix_spawn_spread_full(uint32_t scene, uint32_t child, VertrixMemoryRead read,
                              VertrixMemoryWrite write, void *memory_context,
                              const VertrixCalls *calls, uint32_t *result);

/* Original 0x43e920: complete sparkle placement, snapshotting both original position
 * tables before drawing. Free placement rereads height after its first draw and returns
 * full second draw plus 0x136; table placement preserves draw high word with Y low word.
 * Both full APIs report success separately, retaining prior writes/calls and leaving result
 * untouched on late boundary failure. Null required boundaries/result fail before effects. */
int vertrix_spawn_place_full(uint32_t child, uint32_t ebx, VertrixMemoryRead read,
                             VertrixMemoryWrite write, void *memory_context,
                             const VertrixCalls *calls, uint32_t *result);
#endif
