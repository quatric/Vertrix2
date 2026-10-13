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

/* Original 0x47c3b0 (eax = surface, edx = x, ebx = y, ecx = width; stack arguments, popped by
 * the routine: rows and colour): fill `rows` rows of `width` pixels from (x, y) with the colour in
 * the surface's format (0x479a40; its address from 0x478eb0, ecx the pixel, kept at 0x558b80).
 * Pixels of 1, 2 or 4 bytes (the surface's +0x0c, kept at the byte 0x558b70) are written; the
 * cursor of 2- and 4-byte pixels lives in 0x558b78 or 0x558b7c, stepped per pixel, and each row
 * skips the pitch less the row (kept at 0x558b68). 0x558b74 and 0x558b64 end as the byte cursor
 * and the pixels left of the last row (the cursor only moves for 1-byte pixels). Returns 0 and
 * the skip (the row width for 1-byte pixels) after rows, the skip and the row bytes (0 for 4-byte
 * pixels) for no rows, and the address with the size in edx's low byte for other sizes. */
uint32_t vertrix_port_surface_fill(PORT_SIGNATURE);

/* Original 0x47c520(eax = surface, edx = pixel format source, ebx = left, ecx = top; stack: right,
 * bottom, the clip's left, top, right and bottom, colour; ret 0x1c): draw a rectangle's outline
 * clipped to the clip rectangle. Nothing is drawn for the colour 0xff000000 or a rectangle
 * outside the clip. The clipped size goes to the words at 0x558b84; the colour is converted
 * through a local pixel format (0x481b20, 0x481bc0, 0x481e10, released by 0x481b30, under a guard
 * record) and each edge the clip leaves whole is drawn by 0x47c3b0. Returns the guard record's
 * saved chain. */
uint32_t vertrix_port_draw_outline(PORT_SIGNATURE);

/* Original 0x483ed0(eax = image, edx = source pixel format): convert a 32-bit image's pixels
 * (byte +0x27 == 4; width +4 by height +8 from +0) in place through a local ARGB pixel format
 * (0x481b20, 0x481bc0) and 0x481e10, released by 0x481b30 under a guard record. Returns the
 * guard record's saved chain. */
uint32_t vertrix_port_image_color_order(PORT_SIGNATURE);

/* Original 0x485550(eax = display): present the back buffer. After the last flip ends, the
 * front (+0x68) and back (+0x6c) surfaces are locked (status at 0x5b99c4), a lost one restored
 * (0x487080) and locked again; the back is then copied to the front over the screen (+0x3e by
 * +0x40) with BltFast, else Blt, and both unlocked once the copy ends. Returns 1, or 0 when a
 * surface stays lost. Keeps edx. */
uint32_t vertrix_port_display_present(PORT_SIGNATURE);

/* Original 0x483060(eax = width, edx = height, ebx, ecx; stack: four dwords and four bytes, the
 * last the bytes per pixel; ret 0x20): a new 0x28-byte image record with its pixels, both from
 * 0x4ec160, holding the arguments. */
uint32_t vertrix_port_image_new(PORT_SIGNATURE);

/* Original 0x482e10(eax = image, edx = target, ebx = x, ecx = y): blit a whole image through a
 * local surface view of it (0x478cd0 with the depth in bits, 0x478da0 with the pitch) by
 * 0x47ce10. */
uint32_t vertrix_port_event_frame_draw_direct(PORT_SIGNATURE);

/* Original 0x482f80(eax = source, edx = x, ebx = y, ecx = width; stack: height, six dwords,
 * three bytes, the bytes per pixel; ret 0x2c): a new image like 0x483060 holding the arguments,
 * its pixels copied from the source at (x, y) by 0x47ce10 through a view of it. */
uint32_t vertrix_port_image_new_drawn(PORT_SIGNATURE);

/* Original 0x480ec0(eax = stream, edx = position): read an image: its 0x80-byte header (through
 * 0x48a930, the stream's position kept by 0x48aad0 and restored by 0x48aaf0) sizes a new surface
 * (0x478d10), whose pixels 0x480d60 reads. Returns the surface. */
uint32_t vertrix_port_image_read(PORT_SIGNATURE);

/* Original 0x482d00(eax = stream): read an image: a 0x30-byte header (0x48a930) whose last 40
 * bytes become the new image record (0x4ec160), then its pixels by depth (+0x27): 8-bit read raw
 * or unpacked by 0x481480, 32-bit read raw then blended with 0x5b9c60 (0x483750) and converted
 * (0x483ed0). Returns the image; keeps edx. */
uint32_t vertrix_port_image_read_tga(PORT_SIGNATURE);

/* Original 0x482e80(eax = image, edx, ebx, ecx; one stack argument, the position): blend the
 * image (0x47c930) from its source record (0x478cd0, 0x478da0). */
uint32_t vertrix_port_event_frame_draw_blend(PORT_SIGNATURE);

/* Original 0x482f00(eax = image, edx, ebx, ecx; five stack arguments): as 0x482e80, scaled
 * (0x47cb40), the position the fifth argument. */
uint32_t vertrix_port_event_frame_draw_scaled(PORT_SIGNATURE);

/* Original 0x483ce0(eax = image): mirror each row of an 8-bit or 32-bit image (+0x27) left to
 * right in place. Keeps edx. */
uint32_t vertrix_port_image_mirror_rows(PORT_SIGNATURE);

#endif
