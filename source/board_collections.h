#ifndef VERTRIX_BOARD_COLLECTIONS_H
#define VERTRIX_BOARD_COLLECTIONS_H
#include "board_cells.h"
/* Original board object lists (see scene.h), named by their board offset. */
typedef enum
{
    VERTRIX_BOARD_AT_220,
    VERTRIX_BOARD_AT_87C,
    VERTRIX_BOARD_AT_988,
    VERTRIX_BOARD_AT_9E8,
    VERTRIX_BOARD_AT_A2C,
    VERTRIX_BOARD_AT_BDC,
    VERTRIX_BOARD_AT_324
} VertrixBoardCollection;

/* Original0x4b22c0 through its wrappers 0x42ebc0 (+0x220), 0x42ebe0 (+0x87c), 0x42ec00 (+0x988),
 * 0x42ec20 (+0x9e8), 0x42ec40 (+0xa2c), 0x42ec60 (+0xbdc) and 0x42eee0 (+0x324, 260 entries):
 * destroy (flag 2) and clear every set entry in order. Returns zero for an unknown collection. */
int vertrix_board_clear_collection(VertrixScene *scene, VertrixBoardCollection collection,
                                   VertrixBoardDestroy destroy, void *context);

/* Original0x4b2300 through 0x42ec80, 0x42eca0, 0x42ecc0, 0x42ece0, 0x42ed00 and 0x42ed20:
 * *all is 1 when every set entry's object has handler token +0x154 equal to handler, else 0
 * (stopping at the first mismatch). Returns zero for an unresolvable object reached. */
int vertrix_board_collection_all_handler(const VertrixScene *scene,
                                         VertrixBoardCollection collection, uint32_t handler,
                                         VertrixObjectStorage resolve, void *context,
                                         uint32_t *all);

/* Original0x4b2340 through 0x42eda0 (+0x220): set the handler token of every set entry. */
int vertrix_board_collection_set_handler(const VertrixScene *scene,
                                         VertrixBoardCollection collection, uint32_t handler,
                                         VertrixObjectStorage resolve, void *context);

/* Original0x42ed40 / 0x42edf0 (list 0, piece +0x15c) and 0x42ed70 (list 1, piece +0x170): the
 * same check over the active piece's three child handles; *all is 1 without an active piece. */
int vertrix_board_piece_all_handler(const VertrixScene *scene, int list, uint32_t handler,
                                    VertrixObjectStorage resolve, void *context, uint32_t *all);

/* Original0x42edc0: set the handler token of the active piece's list 0 children (nothing when no
 * piece is active). */
int vertrix_board_piece_set_handler(const VertrixScene *scene, uint32_t handler,
                                    VertrixObjectStorage resolve, void *context);
/* Original0x4387b0: for every set slot of the grid at +0x220, in column order: objects whose byte
 * +0x44 is not 0x10 get handler token 0x44eaf0; objects with +0x44 equal to 0x10 and kind byte
 * +0x15c equal to 5 get byte +0x93 = 0, +0x4e = 0x32 and +0x95 = 1. Returns zero for an
 * unresolvable object, preserving earlier changes as the original performs them in order. */
int vertrix_board_prepare_slots(const VertrixScene *scene, VertrixObjectStorage resolve,
                                void *context);
/* Original0x438c60: for every set slot of the grid at +0x220 whose entry in the pattern is 1,
 * set the word at object +0x48 to 0x64. The pattern is one 65-byte row of the table at 0x4f7e40
 * (row-major: row * 5 + column) selected by the dl argument. Returns zero for an unresolvable
 * object. */
int vertrix_board_apply_pattern(const VertrixScene *scene, const uint8_t pattern[65],
                                VertrixObjectStorage resolve, void *context);
/* Original0x4398c0: destroy and clear every object of the collection at +0xbdc whose cell in the
 * 65-byte marker grid is 2. */
void vertrix_board_clear_marked_extra(VertrixScene *scene, const uint8_t markers[65],
                                      VertrixBoardDestroy destroy, void *context);

/* Original0x439190: for every cell whose marker is 2, destroy and clear the grid object at +0x220
 * and then the collection object at +0xbdc. Returns 1. */
int vertrix_board_destroy_marked(VertrixScene *scene, const uint8_t markers[65],
                                 VertrixBoardDestroy destroy, void *context);

/* Original0x438b90: for every set slot of the grid at +0x220 in row order, assign the effect
 * handler selected by mode (byte): 0 -> 0x44f1e0 with word +0x4c = 10, 1 -> 0x44f320 with
 * +0x4c = 10, 2 -> 0x44f430 with dword +0x88 = 10, 3 -> 0x44f560, 4 -> 0x44f690; other modes change
 * nothing. Returns zero for an unresolvable object. */
int vertrix_board_assign_effect(const VertrixScene *scene, uint8_t mode,
                                VertrixObjectStorage resolve, void *context);
#endif
