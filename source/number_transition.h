#ifndef VERTRIX_NUMBER_TRANSITION_H
#define VERTRIX_NUMBER_TRANSITION_H
#include "number_player.h"
#include "timer.h"
typedef struct
{
    uint32_t id, source, handler;
    int16_t effect, target, step;
    VertrixTimer timer;
} VertrixNumberTransition;
/* Original44fad0/44fb40/44fbb0. The caller resolves the first numeric object
 * matching id in list54671c. Its id selects player field17c. Completion of
 *44fb40 schedules44faa0 on that object before advancing the effect handler.
 * No allocation or text/font binding occurs here. */
int vertrix_number_transition_update(VertrixNumberTransition *transition,
                                     VertrixNumberPlayer *linked_number,
                                     const uint32_t *player_values, size_t player_count,
                                     uint32_t elapsed);
/* Also44fc60/44fcf0/44fd60/44fdb0/44fe30. Caller supplies player field178 for
 * these handlers. Config words represent original532bc8 and532b34.
 * The shorter entry point supplies zero for both config words. */
int vertrix_number_transition_configured(VertrixNumberTransition *transition,
                                         VertrixNumberPlayer *linked_number,
                                         const uint32_t *player_values, size_t player_count,
                                         uint32_t elapsed, uint32_t config_mode,
                                         uint32_t config_value);
#endif
