#ifndef VERTRIX_PIECE_ACTOR_LAYOUT_H
#define VERTRIX_PIECE_ACTOR_LAYOUT_H
#include "ui_scene_frame.h"
/* Original 0x42aab0: complete routine: base constructor, class514774, seven null child
 * handles and zero movement/mode/flag/count178..188. Minimum18c bytes;
 * preserve all untouched bytes and reject short storage before mutation. */
int vertrix_piece_actor_parent_construct(void *parent, size_t parent_size);
/* Original42af30: visit seven parent slots15c..174, skip nulls, copy parent
 * x0e and write parent y16 + slot * row height to actor y16 with word wrapping.
 * Row height represents original4f90ac. Read parent coordinates as each actor
 * is reached. Resolver keeps parent and actors live. Failure retains preceding
 * writes; this helper does not update timers, callbacks or parent position. */
int vertrix_piece_actor_layout(void *parent, size_t parent_size, uint16_t row_height,
                               VertrixActorStorageMutableResolve resolve, void *context);
/* Original 0x42af80: for count188 >=2, rotate active handles left, then set
 * penultimate callback44c370 and final callback44c2b0. Counts0..7 supported;
 * counts0/1 require no resolver. Invalid storage/count/required resolution
 * preserves parent and children. Resolver keeps handles/storage stable. */
int vertrix_piece_actor_cycle(void *parent, size_t parent_size,
                              VertrixActorStorageMutableResolve resolve, void *context);
#endif
