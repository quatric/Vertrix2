#ifndef TEARDOWNS_H
#define TEARDOWNS_H

#include "port.h"

/* Board destruction and construction, slot object construction, and music loading. */
uint32_t vertrix_port_board_destroy_42ea00(PORT_SIGNATURE);
uint32_t vertrix_port_board_construct_42e870(PORT_SIGNATURE);
uint32_t vertrix_port_slot_object_construct_43d6a0(PORT_SIGNATURE);
uint32_t vertrix_port_music_load_45f3f0(PORT_SIGNATURE);

#endif
