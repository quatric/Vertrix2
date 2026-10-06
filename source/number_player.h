#ifndef VERTRIX_NUMBER_PLAYER_H
#define VERTRIX_NUMBER_PLAYER_H
#include "number_text.h"
#include "object_list.h"
typedef struct
{
    uint32_t id, value, mode, width, show_zero, handler;
    int16_t refresh_index;
    uint32_t refresh;
} VertrixNumberPlayer;
/* Original 0x44fa70/0x44faa0/0x44fc00/0x44fc30. Listed objects supply field180;
 * player_values supply field17c for44faa0 or field178 for44fc30 indexed by id.
 * Shared refresh words represent5bb714. Both player handlers clear on completion.
 * This selects/formats text but does not bind its font resource. */
int vertrix_number_player_update(VertrixNumberPlayer *number, const VertrixObjectList *objects,
                                 VertrixObjectState identity, VertrixObjectState value,
                                 void *context, const uint32_t *player_values, size_t player_count,
                                 uint32_t *refresh_words, size_t refresh_count, char *text,
                                 size_t capacity);
#endif
