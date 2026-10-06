#ifndef VERTRIX_NODE_POOL_H
#define VERTRIX_NODE_POOL_H
#include <stddef.h>
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Free list node pools of the Delphi runtime. A pool holds the free list head at +0x10, the used
 * count at +0xc, the nodes per block at +0x18 and the block list at +0x14. An empty free list is
 * refilled with a block of nodes from 0x4e23e0 (stack: block list, nodes per block, node size),
 * linked from the last node to the first, the block starting four bytes before its first node. */

/* Original 0x4d8490 (eax = pool, ebx = key, edx = value; nodes of 12 bytes): takes the head node,
 * stores key at +0 and value at +4, counts it and clears +8. `ecx` is the caller's register.
 * Returns the node. Fails with zero when the pool or a node cannot be read. */
int vertrix_node_pool_take_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t pool, uint32_t key, uint32_t value, uint32_t ecx,
                                uint32_t *node);
/* Original 0x4d8c20 (the same taking): then 0x4ca060 (on the next node) and 0x4eb5e0 (on node +
 * 8, ebx 4) initialise the node's field at +8. */
int vertrix_node_pool_take_initialised(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t pool,
                                       uint32_t key, uint32_t value, uint32_t ecx, uint32_t *node);
/* Original 0x4df070 (eax = pool; nodes of 16 bytes): takes the head node, counts it and clears
 * +8 and +0xc. `edx` and `ecx` are the caller's registers. */
int vertrix_node_pool_take_quad(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t pool, uint32_t edx, uint32_t ecx, uint32_t *node,
                                uint32_t *block);

/* Stores a dword at `field` of a node taken from a refilled block (`block` as given by
 * vertrix_node_pool_take_quad, zero for a node of an earlier block). */
int vertrix_node_pool_store(const VertrixFactoryServices *services, uint32_t block, uint32_t node,
                            size_t field, uint32_t value);

/* Original 0x4df160 (eax = map, edx = key; `local` is the address of the hash local, esp - 16 of
 * the entry): 0x4df0f0 looks the key up (storing the bucket in the local); a found node's value
 * address (node + 0xc) is returned. Otherwise an empty bucket array (+4) is first sized by 0x4def50
 * (the bucket count at +8, ebx 1), a node is taken (vertrix_node_pool_take_quad), given the bucket,
 * key and the previous bucket head, and linked as the bucket's head. Returns the value address. */
int vertrix_map_find_or_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t local, uint32_t map, uint32_t key, uint32_t *value);

/* Original 0x4df220 (eax = map, edx = cursor cell, ebx = key out, ecx = value out): advances a
 * hash map iterator. The cell holds the current node, or 0xffffffff before the first, which
 * starts at the first occupied bucket (+4, with the bucket count at +8). The node's key (+8) and
 * value (+0xc) are stored through the outputs and the cell receives the node's successor: its
 * chain link (+0), else the head of the next occupied bucket after the node's bucket (+4), else
 * zero. Returns zero when a cell cannot be read, or when the first node does not exist (the
 * original reads address zero). */
int vertrix_map_iterate(const VertrixFactoryServices *services, uint32_t map, uint32_t cursor,
                        uint32_t key_out, uint32_t value_out);

#endif
