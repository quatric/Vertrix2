#ifndef VERTRIX_UI_BORDER_UPDATE_H
#define VERTRIX_UI_BORDER_UPDATE_H
#include "actor_lookup.h"
#include "random.h"
/* Original variants 0x450130, 0x4501a0, 0x450200, 0x450270, 0x450300: Update serialized actor
 * storage. The random state is shared with other actors, in original update order. Invalid storage,
 * random state or handler preserves both actor and random state. */
int vertrix_ui_border_storage_update(void *storage, size_t size, int linked_present,
                                     uint32_t linked_value, uint32_t elapsed,
                                     VertrixRandom *random);
int vertrix_ui_border_storage_update_list(void *storage, size_t size, const VertrixObjectList *list,
                                          VertrixActorStorageResolve resolve, void *context,
                                          uint32_t elapsed, VertrixRandom *random);
#endif
