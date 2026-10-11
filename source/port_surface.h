#ifndef VERTRIX_PORT_SURFACE_H
#define VERTRIX_PORT_SURFACE_H
#include "port.h"

/* Clean ports of the surface pixel routines (port.h). A surface is the original's record:
 * +0x00 the first byte of the pixels, +0x04 the width, +0x08 the height, +0x0c the bytes per pixel
 * (a byte) and +0x14 the bytes per row. */

/* Original 0x478eb0 (eax = surface, edx = x, ebx = y): the address of pixel (x, y), the pixels
 * plus y rows plus x pixels, in 32-bit arithmetic. edx is unchanged. */
uint32_t vertrix_port_surface_offset(PORT_SIGNATURE);

/* Original 0x479d70 (eax = target surface, edx = source surface, ebx = x, ecx = y): copy one
 * pixel at (x, y) when x and y are not negative and below the target's width and height (the
 * comparisons unsigned). The source pixel's address goes to the global 0x558a5c, the target's to
 * 0x558a60 and the target's bytes per pixel to the byte 0x558a58; a pixel of 4, 2 or 1 bytes is
 * copied, other sizes copy nothing. Returns the target pixel's address (the source surface when
 * outside), with edx the x (the source surface when outside). */
uint32_t vertrix_port_surface_copy_pixel(PORT_SIGNATURE);

/* Original 0x479df0 (eax, edx as 0x479d70, ebx = x, ecx = y): 0x479d70 at (x, y + 1), (x, y - 1),
 * (x - 1, y + 1) and (x + 1, y - 1), in that order. Returns the last call's eax and edx. */
uint32_t vertrix_port_neighbour_calls(PORT_SIGNATURE);

/* Original 0x478f10 (eax = surface, edx = x, ebx = y): the pixel at (x, y) (0x478eb0, ecx the
 * surface), its address stored at 0x5589f0 and the bytes per pixel at the byte 0x5589ec. Returns
 * the pixel's 4, 2 or 1 bytes (0 for other sizes), with edx the call's edx with its low byte the
 * bytes per pixel. */
uint32_t vertrix_port_surface_read(PORT_SIGNATURE);

#endif
