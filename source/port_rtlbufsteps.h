#ifndef PORT_RTLBUFSTEPS_H
#define PORT_RTLBUFSTEPS_H

#include "port.h"

/* 0x4bd9e0 steps a state machine in the record at [this+0x1a8], with state at +0x44, step counter
 * +0x34 and limit +0x48 (= [this+0x13c]-1, later [this+0x13c]+2). */
uint32_t vertrix_port_staged_buffer_step_wrap_pad_4bd9e0(PORT_SIGNATURE);

#endif
