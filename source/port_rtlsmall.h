#ifndef PORT_RTLSMALL_H
#define PORT_RTLSMALL_H

#include "port.h"

/* Small routines: mixer output, string copies, piece spans, centring and a guarded call */
uint32_t vertrix_port_mixer_output_401010(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_string_copy_pair_4ca240(PORT_SIGNATURE);
uint32_t vertrix_port_board_piece_span_431b20(PORT_SIGNATURE);
uint32_t vertrix_port_ui_center_on_anchor_457890(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_zero_call3_4da66e(PORT_SIGNATURE);

#endif
