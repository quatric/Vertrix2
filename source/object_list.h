#ifndef VERTRIX_OBJECT_LIST_H
#define VERTRIX_OBJECT_LIST_H
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint32_t *items;
    size_t count;
    size_t capacity;
} VertrixObjectList;
/* Original fragment 0x4b5e70: append within reserved storage. Caller owns allocation and
 * reserves capacity before registration. Retains order and duplicate handles.
 * Invalid/full storage rejects before mutation; growth is external. */
int vertrix_object_list_append(VertrixObjectList *list, uint32_t object);
/* A virtual method of one object, reached through the table at object +0x158. `slot` is the byte
 * offset of the method in that table; `edx` and `ebx` are the two register arguments. */
typedef void (*VertrixObjectCall)(uint32_t object, unsigned slot, uint32_t edx, uint32_t ebx,
                                  void *context);
/* Original 0x4b60c0 (slot 0xc, with EDX and EBX), 0x4b6120 (slot 0x10), 0x4b6170 (slot 0x14) and
 * 0x4b61c0 (slot 0x18): call the same virtual method of every object in the list, in order.
 * 0x4b6200 is the same loop on slot 0x4 (vertrix_object_list_update). The count is read once and
 * each handle as it is reached, so a method may change later handles. Rejects null handles and
 * invalid storage before calling anything.
 * The scene's three global lists (0x54671c, 0x546744 and 0x546730) forward their register
 * arguments to these through the wrappers 0x471a20, 0x471a40, 0x471a50, 0x471a60 and 0x471a70
 * (first list; slots 0xc, 0x10, 0x14, 0x18 and 0x4), 0x471a80, 0x471ab0, 0x471ad0, 0x471ae0 and
 * 0x471af0 (second list) and 0x471b00, 0x471b30, 0x471b50, 0x471b60 and 0x471b70 (third list). */
int vertrix_object_list_broadcast(VertrixObjectList *list, unsigned slot, uint32_t edx,
                                  uint32_t ebx, VertrixObjectCall call, void *context);
/* destroy=0 updates virtual +4; destroy=2 invokes virtual destructor +0.
 * Callbacks must preserve list allocation/count. They may change object state
 * or later nonzero handles. The caller owns objects and list storage. */
typedef void (*VertrixObjectVisit)(uint32_t object, unsigned destroy, void *context);
/* Read original object +0x154. Return 0 for an unresolved handle. */
typedef int (*VertrixObjectState)(uint32_t object, uint32_t *state, void *context);
/* Original 0x4b6200: snapshots the initial count, reads each handle as reached.
 * Rejects null handles/invalid storage before updating anything. */
int vertrix_object_list_update(VertrixObjectList *list, VertrixObjectVisit visit, void *context);
/* Original 0x4b5f50, 0x4b5ee0 and 0x4d8950: destroy matching objects, shift
 * later handles left, retain stale unused tail storage, recheck same index.
 * An unresolved object returns 0 after any preceding removals. */
int vertrix_object_list_prune(VertrixObjectList *list, uint32_t matching_state,
                              VertrixObjectState state, VertrixObjectVisit visit, void *context);
/* Original 0x4b5eb0: return the first object whose field0 matches the requested ID.
 * Reuses the scalar resolver signature; this resolver reads field0, not state154.
 * Success with no match writes handle0. Invalid storage/resolution preserves output. */
int vertrix_object_list_find(const VertrixObjectList *list, uint32_t id,
                             VertrixObjectState identity, void *context, uint32_t *object);
#endif
