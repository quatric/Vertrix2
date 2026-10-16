#ifndef PORT_RTLJPEGDECOMPRESSES_H
#define PORT_RTLJPEGDECOMPRESSES_H

#include "port.h"

/* 0x4b9f70 has the shape of libjpeg's jdcoefct decompress_onepass, which the Delphi JPEG unit links
 * in. */
uint32_t vertrix_port_jpeg_decompress_onepass_4b9f70(PORT_SIGNATURE);

#endif
