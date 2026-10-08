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

/* Original fragment 0x4ac8d0: bind a resource to an actor, clearing the dword +0xcc and the
 * frame counter +0xb8 and storing the resource token at +0xb0. */
int vertrix_actor_attach_resource(void *actor, size_t size, uint32_t resource);

/* Original fragment 0x4adf20: place an actor: words +8 and +0xe = x, +0xa and +0x16 = y, +0xc and
 * +0x1e = z; dwords +0xb0 = bank, +0xb8 = frame, +0xb4 = image and the handler token +0x154 =
 * handler. */
int vertrix_actor_initialize(void *actor, size_t size, uint16_t x, uint16_t y, uint16_t z,
                             uint32_t bank, uint32_t frame, uint32_t image, uint32_t handler);

/* Original fragment 0x42bb00: construct a block actor: the base fields (0x4abd70), then dword
 * +0x158 = 0x514914, byte +0x15d = 0 and byte +0x15c = 0xff. Returns zero for short storage. */
int vertrix_block_construct(void *storage, size_t size);

/* Original fragment 0x43a080: construct a kind-1 block actor: base fields, dword +0x158
 * = 0x514b14, byte +0x15c = 1 and byte +0x15d = 0, then flag bytes +0x94 = 0
 * and +0x95 = 3. Returns zero for short storage. */
int vertrix_block_construct_kind_one(void *storage, size_t size);

/* Original fragment 0x4b5400: construct a class-0x518174 actor: the base fields
 * (0x4abd70), then dword +0x158 = 0x518174, byte +0x94 = 0 and word +0x15c
 * = 0. Returns zero for short storage. */
int vertrix_actor_construct_518174(void *storage, size_t size);

/* Original fragment 0x42bbd0: allocate and build one block of the given kind (a signed byte):
 * initialise it with handler, set the dword +0xd0 to d0 and the period to steps * 12, attach the
 * resource at 0x544ac0 + kind * 28 and store the kind in byte +0x15c. Returns zero when allocation
 * fails or an object does not resolve; the new handle is stored otherwise. */
int vertrix_block_create(uint8_t kind, uint32_t d0, uint32_t steps, uint32_t handler,
                         const VertrixFactoryServices *services, uint32_t *handle);

/* Original fragment 0x430800: create a block of the kind in the low byte of index on the board. Its
 * steps are one plus a draw below 10; its +0xd0 delay is a draw over the table range lo..hi of the
 * entry of index (the original 0x415470, with the draw divisor hi - lo + 1 truncated to 16 bits)
 * plus lo. The block then receives the board's clip rectangle. Returns zero on failure. */
int vertrix_block_spawn(const void *board, size_t board_size, uint32_t index,
                        const VertrixFactoryServices *services, uint32_t *handle);
/* Full scalar/constructor APIs return original actor EAX through result, separately from
 * storage success. Null output fails before writes; existing raw-storage preflights apply. */
/* Original 0x4ac8d0: attach resource, returning actor unchanged. */
int vertrix_actor_attach_resource_full(void *actor, size_t size, uint32_t token, uint32_t resource,
                                       uint32_t *result);
/* Original 0x4adf20: initialize actor from register coordinates and four stack values,
 * returning actor unchanged (the original also consumes a fifth unused stack argument). */
int vertrix_actor_initialize_full(void *actor, size_t size, uint32_t token, uint16_t x, uint16_t y,
                                  uint16_t z, uint32_t bank, uint32_t frame, uint32_t image,
                                  uint32_t handler, uint32_t *result);
/* Original 0x42bb00: complete block constructor and original actor return. */
int vertrix_block_construct_full(void *storage, size_t size, uint32_t token, uint32_t *result);
/* Original 0x43a080: complete kind-one constructor and original actor return. */
int vertrix_block_construct_kind_one_full(void *storage, size_t size, uint32_t token,
                                          uint32_t *result);
/* Original 0x4b5400: complete class-0x518174 constructor and original actor return. */
int vertrix_actor_construct_518174_full(void *storage, size_t size, uint32_t token,
                                        uint32_t *result);
/* Original 0x42bbd0: exact allocation 0x4ca000 register boundary and native initialization.
 * Allocation result resolves after the callback; a zero token skips the constructor just as
 * original, but still needs supplied backing for later writes. Failed resolution retains
 * allocation effects. Short resolved storage retains completed helper writes; output stays
 * untouched on failure. */
int vertrix_block_create_full(uint32_t kind, uint32_t d0, uint32_t steps, uint32_t handler,
                              VertrixObjectStorage resolve, void *resolve_context,
                              const VertrixCalls *calls, uint32_t *result);
/* Original 0x430800: complete spawn. Range globals are read after the first draw, and low
 * is reread after the second. Board clip fields are read after allocation/initialization.
 * Read/write boundaries retain completed effects on late failure; result stays untouched. */
int vertrix_block_spawn_full(uint32_t board, uint32_t index, uint32_t ebx, VertrixMemoryRead read,
                             VertrixMemoryWrite write, void *memory_context,
                             VertrixObjectStorage resolve, void *resolve_context,
                             const VertrixCalls *calls, uint32_t *result);
#endif
