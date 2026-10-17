#ifndef PORT_RTLAIBOARDCOMPARES_H
#define PORT_RTLAIBOARDCOMPARES_H

#include "port.h"

/* Prepares the AI board comparison for a player: copies the 0x41-byte boards (+0x1de) of the player
 * and its opponent into the frame, stores the choice grid values (0x429e80), sets the mode flags
 * (0x427e10), compares the two boards (0x428110) and passes the players' speeds and positions on.
 */
uint32_t vertrix_port_ai_compare_player_boards_427850(PORT_SIGNATURE);

#endif
