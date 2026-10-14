#ifndef VERTRIX_PORT_VOICES_H
#define VERTRIX_PORT_VOICES_H
#include "port.h"

/* Clean ports of sound buffer fill, channel buffer and play, swapped word read, option record
 * step, high score name, clock text and game teardown routines (port_voices.c). */
uint32_t vertrix_port_sound_buffer_fill_40bcc0(PORT_SIGNATURE);
uint32_t vertrix_port_sound_channel_buffer_40bdb0(PORT_SIGNATURE);
uint32_t vertrix_port_sound_channel_play_40beb0(PORT_SIGNATURE);
uint32_t vertrix_port_file_read_word_swapped_40c360(PORT_SIGNATURE);
uint32_t vertrix_port_option_record_step_up_412430(PORT_SIGNATURE);
uint32_t vertrix_port_option_record_step_down_412510(PORT_SIGNATURE);
uint32_t vertrix_port_high_score_name_416990(PORT_SIGNATURE);
uint32_t vertrix_port_clock_text_418170(PORT_SIGNATURE);
uint32_t vertrix_port_game_teardown_41fd20(PORT_SIGNATURE);
#endif
