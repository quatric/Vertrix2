#ifndef VERTRIX_UI_INDICATOR_UPDATE_H
#define VERTRIX_UI_INDICATOR_UPDATE_H
#include "actor_lookup.h"
/* Original variants 0x44ff90, 0x44fff0, 0x450040, 0x4500b0, 0x450100: Update serialized actor
 * storage. Resolve the first matching player object using the original list ordering. Invalid input
 * or unsupported handler preserves storage. */
int vertrix_ui_indicator_storage_update(void *storage, size_t size, int linked_present,
                                        uint32_t linked_value, uint32_t linked_state,
                                        uint32_t elapsed);
int vertrix_ui_indicator_storage_update_list(void *storage, size_t size,
                                             const VertrixObjectList *list,
                                             VertrixActorStorageResolve resolve, void *context,
                                             uint32_t elapsed);
#endif
