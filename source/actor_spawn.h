#ifndef VERTRIX_ACTOR_SPAWN_H
#define VERTRIX_ACTOR_SPAWN_H
#include <stdint.h>

#include "actor_fields.h"
#include "actor_storage.h"
#include "call_glue.h"
#include "object_glue.h"

/* The values that distinguish the spawn routines 0x472470, 0x4724f0 and 0x472570. */
typedef struct VertrixSpawnSpec
{
    uint32_t kind;
    uint32_t delay;
    uint32_t field58;
    uint32_t field5c;
    uint32_t field60;
    uint32_t handler;
} VertrixSpawnSpec;

/* Originals 0x472470, 0x4724f0 and 0x472570 (edx, ebx and ecx the caller's): 0x4ca000(0x15c)
 * allocates the actor, which a non-zero result sends through 0x4abd70; 0x4adf20 (five zero stack
 * arguments) initialises it, its kind dword is set, 0x4ac7d0 sets the delay, the dwords +0x58,
 * +0x5c and +0x60 are stored, 0x4ac8f0 sets the handler, 0x4ac910 clears its flag and 0x4b5e70
 * registers it with the list 0x54676c. Returns the eax of 0x4b5e70, or zero when the actor
 * does not resolve. */
uint32_t vertrix_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixSpawnSpec *spec, uint32_t edx, uint32_t ebx,
                             uint32_t ecx);

/* Original 0x430190 (eax = source object, edx/ebx = the caller's pair index scaled by 0x18
 * below, ecx handed through): build the match effect actor. The base position words come from
 * the source dwords +0xc/+0x14 (arithmetic shift right 0x10, plus 0x77/0x137); 0x4ca000(0x15c)
 * allocates the actor, which a non-zero result sends through 0x4abd70, then 0x4adf20 (five
 * zero stack arguments) initialises it, 0x4ac470 sets four steps, 0x4ac7b0 one period step,
 * 0x4ac8d0 binds resource 0x544d28 and 0x4ac710 selects frame zero. The position words
 * +0xe/+0x16 are the scaled pair sums minus three. Returns the actor handle, zero when an
 * object does not resolve. */
uint32_t vertrix_actor_spawn_match_effect(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const void *source, size_t source_size, uint32_t edx,
                                          uint32_t ebx, uint32_t ecx);

/* Boundaries of the match burst 0x4302a0: the actor allocator (original 0x4ca000, called with
 * the size), the random draw (original 0x4826c0, called with the divisor), the frame binding
 * of an actor (original 0x4ac8a0, called with the actor handle and the descriptor; the
 * original preserves edx across it) and the append of an actor to the list (original 0x4b5e70,
 * called with the list address and the item). */
typedef struct VertrixMatchBurstHooks
{
    uint32_t (*allocate)(uint32_t size, void *context);
    VertrixSpawnDraw draw;
    void (*bind_frame)(uint32_t actor, uint16_t descriptor, void *context);
    void (*append)(uint32_t list, uint32_t item, void *context);
    void *context;
} VertrixMatchBurstHooks;

/* Original 0x4302a0 (eax = source object, edx/ebx the caller's pair, ecx handed through):
 * spawn eight burst actors into the list at source +0xcec. One draw below 0x168 gives the
 * shared descriptor and one below two plus three the shared count; every actor takes the
 * position words +0xe/+0x16 (source words plus the scaled pair plus 0xc), resource 0x54651c,
 * handler 0x444700, the unsigned remainder of the descriptor below 0x168 in word +0x24
 * and the count in +0x28, and is appended to the list. Returns zero. */
uint32_t vertrix_actor_spawn_match_burst(const VertrixFactoryServices *services, const void *source,
                                         size_t source_size, uint32_t source_handle, uint32_t edx,
                                         uint32_t ebx, const VertrixMatchBurstHooks *hooks);

#endif
