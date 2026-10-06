#ifndef VERTRIX_BOARD_BURST_H
#define VERTRIX_BOARD_BURST_H
#include "block_factory.h"

/* Boundaries of the burst routine: the frame binding of an actor (original 0x4ac8a0, called with
 * the actor handle) and the append of an item to the list object embedded in the board at +0xcec
 * (original 0x4b5e70, called with the list address and the item). The list address is the board
 * handle plus the offset. */
typedef struct
{
    void (*bind_frame)(uint32_t actor, void *context);
    void (*append)(uint32_t list, uint32_t item, void *context);
    void *context;
} VertrixBurstHooks;

enum
{
    VERTRIX_BURST_COUNT = 10,
    VERTRIX_BURST_LIST_OFFSET = 0xcec
};

/* Original0x430660: spawn ten sparks at the board cell (cells_x, cells_y), whose centre is the
 * board origin (words +0xe, +0x16) plus 24 * cell + 12. One draw below 360 gives the shared heading
 * and one below 9 plus 2 the shared speed; every spark draws its frame below 32, takes resource
 * 0x54651c, handler 0x444a80, the heading in word +0x24 and the speed in +0x28, and is appended
 * to the board list. Returns zero when an allocation or an object fails. */
int vertrix_board_burst(void *board, size_t board_size, uint32_t board_handle, int32_t cells_x,
                        int32_t cells_y, const VertrixFactoryServices *services,
                        const VertrixBurstHooks *hooks);

/* Original0x430440: three rings of 18 sparks at the cell (cells_x, cells_y), built as the burst
 * does. Ring r draws its first heading below 360 (each spark adds 20 degrees), puts 12 - 4 * r in
 * word +0x30 and 5 - r in word +0x32, clears word +0x28 and takes handler 0x444970. The first and
 * third ring draw a frame below 32 for every spark and use resource 0x54651c; the second ring
 * uses frame 0 and resource 0x546500. Returns zero when an allocation or an object fails. */
int vertrix_board_rings(void *board, size_t board_size, uint32_t board_handle, int32_t cells_x,
                        int32_t cells_y, const VertrixFactoryServices *services,
                        const VertrixBurstHooks *hooks);
#endif
