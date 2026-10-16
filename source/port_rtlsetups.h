#ifndef PORT_RTLSETUPS_H
#define PORT_RTLSETUPS_H

#include "port.h"

/* Case folds, game step checks, item toggles, decoder table set-up and digit runs */
uint32_t vertrix_port_rtl_char_fold_4eab80(PORT_SIGNATURE);
uint32_t vertrix_port_game_step_check_443ab0(PORT_SIGNATURE);
uint32_t vertrix_port_item_toggle_452370(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_quantizer_init_4c31a0(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_six_digits_4ecf33(PORT_SIGNATURE);

#endif
