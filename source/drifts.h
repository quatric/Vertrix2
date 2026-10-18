#ifndef DRIFTS_H
#define DRIFTS_H

#include "port.h"

/* Block drift, fall and spin step routines. */
uint32_t vertrix_port_block_drift_step_44dcf0(PORT_SIGNATURE);
uint32_t vertrix_port_block_fall_step_44e120(PORT_SIGNATURE);
uint32_t vertrix_port_block_spin_update_44ece0(PORT_SIGNATURE);

#endif
