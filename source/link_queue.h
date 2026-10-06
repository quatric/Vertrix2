#ifndef VERTRIX_LINK_QUEUE_H
#define VERTRIX_LINK_QUEUE_H
#include "board_cells.h"
#include <stdint.h>

/* Doubly linked queue. The header holds the tail at +0 and the head at +4; a node holds its
 * payload handle at +0, the next node at +0xc and the previous node at +0x10. */
enum
{
    VERTRIX_QUEUE_TAIL = 0,
    VERTRIX_QUEUE_HEAD = 4,
    VERTRIX_QUEUE_TOTAL = 8,
    VERTRIX_NODE_PAYLOAD = 0,
    VERTRIX_NODE_SIZE = 4,
    VERTRIX_NODE_UNUSED = 8,
    VERTRIX_NODE_NEXT = 0xc,
    VERTRIX_NODE_PREVIOUS = 0x10,
    VERTRIX_NODE_BYTES = 0x14
};

/* Supplied boundary for the release 0x4ea190. */
typedef void (*VertrixQueueRelease)(uint32_t handle, void *context);

/* Original0x405ea0: remove the head node. The next node becomes the head with its previous link
 * cleared; with no next node the tail is cleared instead. The payload, then the node, are
 * released. The original faults on an empty queue; here an empty queue, or storage that does
 * not resolve, returns 0 without any change. Returns 1 after popping. */
int vertrix_queue_pop(uint32_t header, VertrixObjectStorage resolve, VertrixQueueRelease release,
                      void *context);

/* Supplied boundaries: the allocator 0x4e7c90 (byte count, returns a handle or 0), and the copy
 * 0x4eb5e0 (destination, source, byte count). Release is 0x4ea190, above. */
typedef uint32_t (*VertrixQueueAllocate)(uint32_t size, void *context);
typedef void (*VertrixQueueCopy)(uint32_t destination, uint32_t source, uint32_t size,
                                 void *context);

/* Original0x405e00: append a copy of `size` bytes from `source`. Allocates a 0x14 byte node, then
 * the payload; a failed node allocation returns 0, a failed payload allocation releases the node
 * and returns 0. The node records payload, size, a zero at +8, no next and the old tail as
 * previous; the old tail's next link (or the head, for an empty queue) and the tail point at it,
 * and the header total grows by size. Returns the node. Storage that does not resolve returns 0
 * after the allocations. */
uint32_t vertrix_queue_push(uint32_t header, uint32_t source, uint32_t size,
                            VertrixObjectStorage resolve, VertrixQueueAllocate allocate,
                            VertrixQueueCopy copy, VertrixQueueRelease release, void *context);
#endif
