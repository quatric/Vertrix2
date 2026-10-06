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
/* Original4b5e70 append within reserved storage. Caller owns allocation and
 * reserves capacity before registration. Retains order and duplicate handles.
 * Invalid/full storage rejects before mutation; growth is external. */
int vertrix_object_list_append(VertrixObjectList *list, uint32_t object);
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
