#ifndef RTLBOARDMATCHES_H
#define RTLBOARDMATCHES_H

#include "port.h"

/* Resolves the matches on a player's board after a piece locks: the figure and line passes, then
 * clears the matched cells and starts their effects. */
uint32_t vertrix_port_board_match_resolve_432480(PORT_SIGNATURE);

#endif
