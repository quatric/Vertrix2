#ifndef VERTRIX_UI_ACTOR_UPDATE_H
#define VERTRIX_UI_ACTOR_UPDATE_H
#include "actor_lookup.h"
#include "linked_alternating.h"
#include "object_list.h"
/* Original six alternating handlers on portable actor bytes. Map resource
 * tokens546618/546634 to live native resources. Caller supplies the original
 * first matching linked object's values. Unknown tokens/invalid state preserve
 * storage. This dispatch does not perform scene lookup or render pixels. */
int vertrix_ui_actor_storage_update(void *storage, size_t size, int linked_present,
                                    uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                    uint32_t elapsed, const VertrixFrameResource *resource_one,
                                    const VertrixFrameResource *resource_other, size_t budget);
/* Original linked lookup4b5eb0: display field4 selects first matching field0
 * in list order, then reads linked58/64. Missing match uses waiting behavior.
 * Unresolved/short storage fails before the display is mutated. */
int vertrix_ui_actor_storage_update_list(void *storage, size_t size, const VertrixObjectList *list,
                                         VertrixActorStorageResolve resolve, void *context,
                                         int16_t start_y, uint32_t elapsed,
                                         const VertrixFrameResource *resource_one,
                                         const VertrixFrameResource *resource_other, size_t budget);
#endif
