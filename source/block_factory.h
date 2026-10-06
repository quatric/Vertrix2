#ifndef VERTRIX_BLOCK_FACTORY_H
#define VERTRIX_BLOCK_FACTORY_H
#include "board_cells.h"
#include "particle_spawn.h"
/* Creation of falling-block actors. Object handles are original address tokens; allocation, name
 * resolution and the random draw (original 0x4826c0) are supplied by the caller. */

/* Supplied boundary for the original operator new (0x4ca000): returns the handle of a fresh
 * object of the given size, or zero when memory is exhausted. */
typedef uint32_t (*VertrixAllocate)(uint32_t size, void *context);

/* Supplied boundary for the delay table of the spawn routine: the entry 0x53bcd0 + 8 * index holds
 * the delay range lo..hi of a block kind. Returns zero for an index outside the table. */
typedef int (*VertrixSpawnRange)(uint32_t index, uint32_t *lo, uint32_t *hi, void *context);

typedef struct
{
    VertrixObjectStorage resolve;
    VertrixAllocate allocate;
    VertrixSpawnDraw draw;
    VertrixSpawnRange range;
    void *context;
} VertrixFactoryServices;

/* Original0x4ac8d0: bind a resource to an actor, clearing the dword +0xcc and the
 * frame counter +0xb8 and storing the resource token at +0xb0. */
int vertrix_actor_attach_resource(void *actor, size_t size, uint32_t resource);

/* Original0x4adf20: place an actor: words +8 and +0xe = x, +0xa and +0x16 = y, +0xc and +0x1e = z;
 * dwords +0xb0 = bank, +0xb8 = frame, +0xb4 = image and the handler token +0x154 = handler. */
int vertrix_actor_initialize(void *actor, size_t size, uint16_t x, uint16_t y, uint16_t z,
                             uint32_t bank, uint32_t frame, uint32_t image, uint32_t handler);

/* Original0x42bb00: construct a block actor: the base fields (0x4abd70), then dword +0x158 =
 * 0x514914, byte +0x15d = 0 and byte +0x15c = 0xff. Returns zero for short storage. */
int vertrix_block_construct(void *storage, size_t size);

/* Original0x43a080: construct a kind-1 block actor: base fields, dword +0x158
 * = 0x514b14, byte +0x15c = 1 and byte +0x15d = 0, then flag bytes +0x94 = 0
 * and +0x95 = 3. Returns zero for short storage. */
int vertrix_block_construct_kind_one(void *storage, size_t size);

/* Original0x42bbd0: allocate and build one block of the given kind (a signed byte): initialise it
 * with handler, set the dword +0xd0 to d0 and the period to steps * 12, attach the resource at
 * 0x544ac0 + kind * 28 and store the kind in byte +0x15c. Returns zero when allocation fails or an
 * object does not resolve; the new handle is stored otherwise. */
int vertrix_block_create(uint8_t kind, uint32_t d0, uint32_t steps, uint32_t handler,
                         const VertrixFactoryServices *services, uint32_t *handle);

/* Original0x430800: create a block of the kind in the low byte of index on the board. Its steps
 * are one plus a draw below 10; its +0xd0 delay is a draw over the table range lo..hi of the entry
 * of index (the original 0x415470, with the draw divisor hi - lo + 1 truncated to 16 bits) plus lo.
 * The block then receives the board's clip rectangle. Returns zero on failure. */
int vertrix_block_spawn(const void *board, size_t board_size, uint32_t index,
                        const VertrixFactoryServices *services, uint32_t *handle);
#endif
