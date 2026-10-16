#ifndef PORT_RTLJPEGUPSAMPLERS_H
#define PORT_RTLJPEGUPSAMPLERS_H

#include "port.h"

/* 0x4c3be0 allocates a 0xa0-byte upsampler through the memory manager ([[cinfo+4]], pool 1) and
 * stores it at cinfo+0x1c4 with start_pass 0x4c35f0, upsample 0x4c3610 and need_context_rows 0. */
uint32_t vertrix_port_jpeg_init_upsampler_4c3be0(PORT_SIGNATURE);

#endif
