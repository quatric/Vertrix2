#ifndef MEMORIES_H
#define MEMORIES_H

#include "port.h"

/* Memory manager setup, triple compare, object setter and player release routines. */
uint32_t vertrix_port_memory_manager_make_4c5a40(PORT_SIGNATURE);
uint32_t vertrix_port_triple_below_4e949c(PORT_SIGNATURE);
uint32_t vertrix_port_object_set_pair_4b35b0(PORT_SIGNATURE);
uint32_t vertrix_port_object_make_4b3fb0(PORT_SIGNATURE);
uint32_t vertrix_port_app_player_release_411f50(PORT_SIGNATURE);

#endif
