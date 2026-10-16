#ifndef PORT_RTLJPEGQUANTIZERS_H
#define PORT_RTLJPEGQUANTIZERS_H

#include "port.h"

/* At 0x4c6c80, libjpeg's jinit_1pass_quantizer: it allocates a 0x58-byte quantizer object through
 * the memory manager, stores it at cinfo+0x1cc and sets its methods to 0x4c6a20, 0x4c6a80 and
 * 0x4c6c70. */
uint32_t vertrix_port_jpeg_one_pass_quantizer_init_4c6c80(PORT_SIGNATURE);

#endif
