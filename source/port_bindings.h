#ifndef PORT_BINDINGS_H
#define PORT_BINDINGS_H

#include "port.h"

/* Table and buffer release, key binding, event setup and marker reader routines. */
uint32_t vertrix_port_table_release_everything_45e260(PORT_SIGNATURE);
uint32_t vertrix_port_player_keys_release_473490(PORT_SIGNATURE);
uint32_t vertrix_port_key_bind_4737d0(PORT_SIGNATURE);
uint32_t vertrix_port_key_bind_473960(PORT_SIGNATURE);
uint32_t vertrix_port_events_setup_48b7e0(PORT_SIGNATURE);
uint32_t vertrix_port_marker_reader_make_4c09e0(PORT_SIGNATURE);
uint32_t vertrix_port_release_pair_475510(PORT_SIGNATURE);

#endif
