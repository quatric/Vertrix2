#include "number_player.h"

int vertrix_number_player_update(VertrixNumberPlayer *number, const VertrixObjectList *objects,
                                 VertrixObjectState identity, VertrixObjectState value,
                                 void *context, const uint32_t *player_values, size_t player_count,
                                 uint32_t *refresh_words, size_t refresh_count, char *text,
                                 size_t capacity)
{
    if (!number || (number->handler != 0x44fa70 && number->handler != 0x44faa0 &&
                    number->handler != 0x44fc00 && number->handler != 0x44fc30))
    {
        return 0;
    }
    VertrixNumberPlayer next = *number;
    int player = next.handler == 0x44faa0 || next.handler == 0x44fc30;
    if (player)
    {
        if (!player_values || next.id >= player_count || next.refresh_index < -1 ||
            (next.refresh_index != -1 &&
             (!refresh_words || (size_t)next.refresh_index >= refresh_count)))
        {
            return 0;
        }
        next.value = player_values[next.id];
    }
    else
    {
        uint32_t object;
        if (!value || !vertrix_object_list_find(objects, next.id, identity, context, &object) ||
            !object || !value(object, &next.value, context))
        {
            return 0;
        }
    }
    if (!vertrix_number_text(next.value, next.mode, next.width, next.show_zero, text, capacity))
    {
        return 0;
    }
    if (player)
    {
        if (next.refresh_index == -1)
        {
            next.refresh = 1;
        }
        else
        {
            refresh_words[next.refresh_index] = 1;
        }
        next.handler = 0;
    }
    *number = next;
    return 1;
}
