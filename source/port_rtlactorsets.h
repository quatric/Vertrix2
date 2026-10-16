#ifndef PORT_RTLACTORSETS_H
#define PORT_RTLACTORSETS_H

#include "port.h"

/* Copies six 7-dword tables (0x4fd560..0x4fd5ec) to the stack, draws seven values with
 * random_in_range (0x415470), then runs four 7-pass loops. */
uint32_t vertrix_port_spawn_random_actor_set_46a410(PORT_SIGNATURE);

#endif
