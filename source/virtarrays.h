#ifndef VIRTARRAYS_H
#define VIRTARRAYS_H

#include "port.h"

/* Image decoder virtual arrays. */
uint32_t vertrix_port_virtual_arrays_realize_4c5200(PORT_SIGNATURE);
uint32_t vertrix_port_virtual_sample_access_4c55a0(PORT_SIGNATURE);
uint32_t vertrix_port_virtual_block_access_4c5740(PORT_SIGNATURE);

#endif
