#ifndef PORT_RTLEXTENDEDEFFECTS_H
#define PORT_RTLEXTENDEDEFFECTS_H

#include "port.h"

/* Applies a module row's extended (Exx) effect: the high nibble of the effect byte at +4 picks the
 * case through the table at 0x40d500, for example a fine volume or period slide that is skipped
 * while [0x531b4c] is set. */
uint32_t vertrix_port_sequence_extended_effect_40d540(PORT_SIGNATURE);

#endif
