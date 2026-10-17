#ifndef PORT_RTLBOARDMATCHES_H
#define PORT_RTLBOARDMATCHES_H

#include "port.h"

/* Resolves matches after a piece locks: takes a kind snapshot, runs the line pass (0x4346b0) and
 * the figure pass (0x434ee0), clears the matched cells and spawns the match effects and bursts. */
uint32_t vertrix_port_board_match_resolve_432480(PORT_SIGNATURE);

#endif
