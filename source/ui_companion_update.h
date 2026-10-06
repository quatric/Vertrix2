#ifndef VERTRIX_UI_COMPANION_UPDATE_H
#define VERTRIX_UI_COMPANION_UPDATE_H
#include "actor_lookup.h"
#include "actor_storage.h"
#include "linked_movement.h"
/* Original450860..4509d0 on portable actor bytes. Caller supplies original
 * linked values and shared refresh array5bb714. Invalid storage/state/required
 * refresh index preserves actor and refresh storage. */
int vertrix_ui_companion_storage_update(void *storage, size_t size, int linked_present,
                                        uint32_t linked_value, uint32_t linked_state,
                                        int16_t start_y, uint32_t elapsed, uint32_t *refresh_words,
                                        size_t refresh_count);
int vertrix_ui_companion_storage_update_list(void *storage, size_t size,
                                             const VertrixObjectList *list,
                                             VertrixActorStorageResolve resolve, void *context,
                                             int16_t start_y, uint32_t elapsed,
                                             uint32_t *refresh_words, size_t refresh_count);
#endif
