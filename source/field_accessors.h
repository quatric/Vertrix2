#ifndef VERTRIX_FIELD_ACCESSORS_H
#define VERTRIX_FIELD_ACCESSORS_H
#include <stddef.h>
#include <stdint.h>
/* One-field accessors of the library, settings and score objects. Storage is raw bytes of the
 * object; short or null storage returns zero and preserves everything. Handles that the original
 * reads from global arrays (0x540f88..0x540f90) are resolved by the caller. */

/* Original0x471e60 and 0x471e80 (the objects at globals 0x540f8c and 0x540f90): dword +0x454
 * becomes 1 - value. */
int vertrix_object_flip_454(void *storage, size_t size);

/* Original0x471ea0 / 0x471eb0 set / get dword +0x464; 0x471ec0 / 0x471ed0 get dword +0x174 /
 * +0x178 of the object picked from the array at 0x540f88. */
int vertrix_object_set_464(void *storage, size_t size, uint32_t value);
int vertrix_object_get_464(const void *storage, size_t size, uint32_t *value);
int vertrix_object_get_174(const void *storage, size_t size, uint32_t *value);
int vertrix_object_get_178(const void *storage, size_t size, uint32_t *value);

/* Original0x45f1e0: store the identity ramp 0..6 in the seven bytes at 0x53bcc8. */
void vertrix_global_index_bytes(uint8_t bytes[7]);

/* Original0x4757b0 / 0x4759d0: byte +0 = 0 / 1. Original0x475800: read it. Original0x475810,
 * 0x475820, 0x475830: read dword +4, +8, +0xc. Original0x475b00: byte +0x5a is zero. */
int vertrix_flags_clear(void *storage, size_t size);
int vertrix_flags_set(void *storage, size_t size);
int vertrix_flags_get(const void *storage, size_t size, uint32_t *value);
int vertrix_flags_dword(const void *storage, size_t size, unsigned index, uint32_t *value);
int vertrix_flags_idle(const void *storage, size_t size, uint32_t *idle);

/* Original0x475dd0 / 0x475e40: store dword +0x40 / +0x3c. Original0x475df0: dword +0x44 is at
 * least dword +0x48 (unsigned). Original0x475e10: dword +0x44 divided by dword +0x48 (1 when that
 * is zero). */
int vertrix_progress_set_40(void *storage, size_t size, uint32_t value);
int vertrix_progress_set_3c(void *storage, size_t size, uint32_t value);
int vertrix_progress_done(const void *storage, size_t size, uint32_t *done);
int vertrix_progress_quotient(const void *storage, size_t size, uint32_t *quotient);

/* Original0x477240: dword +0x14 = 0x516744, byte +4 = 0, dword +0 = 0. Original0x477870: dword
 * +0xc = 0x5167a4. The class tokens are original addresses. */
int vertrix_stream_init(void *storage, size_t size);
int vertrix_stream_set_class(void *storage, size_t size);

/* Original0x477e10: words +0x3c, +0x3e, +0x40, +0x42 = a, b, c, d. Original0x478460: copy words
 * +0x48 and +0x4a to +0x4c and +0x4e. */
int vertrix_rect_set(void *storage, size_t size, uint16_t a, uint16_t b, uint16_t c, uint16_t d);
int vertrix_rect_commit(void *storage, size_t size);

/* Original0x479b30: address of cell (row, column) in a 32-bit surface: base dword +0 plus
 * row * pitch dword +0x14 plus 4 * column, with 32-bit wrap. */
int vertrix_surface_cell_address(const void *storage, size_t size, uint32_t row, uint32_t column,
                                 uint32_t *address);

/* Original0x47e990: the dword at +0 is nonzero. */
int vertrix_dword_set(const void *storage, size_t size, uint32_t *set);
#endif
