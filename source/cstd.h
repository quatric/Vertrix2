#ifndef CSTD_H
#define CSTD_H

#include "port.h"

/* C runtime release, colour, handle table, map walk, exit, type record and write routines. */
uint32_t vertrix_port_heap_pointer_release_4dc190(PORT_SIGNATURE);
uint32_t vertrix_port_system_colours_load_4de810(PORT_SIGNATURE);
uint32_t vertrix_port_handle_table_slot_4ded70(PORT_SIGNATURE);
uint32_t vertrix_port_map_iterate_4df220(PORT_SIGNATURE);
uint32_t vertrix_port_runtime_fatal_exit_4e0738(PORT_SIGNATURE);
uint32_t vertrix_port_type_record_base_4e37fe(PORT_SIGNATURE);
uint32_t vertrix_port_file_write_raw_4e3bf0(PORT_SIGNATURE);

#endif
