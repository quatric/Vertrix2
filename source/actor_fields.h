#ifndef VERTRIX_ACTOR_FIELDS_H
#define VERTRIX_ACTOR_FIELDS_H
#include "actor_storage.h"
/* One-field base actor setters. Short or null storage is preserved and reports zero. */

/* Original0x4ac510: clear the timer counter at +0xbc. */
int vertrix_actor_clear_counter(void *actor, size_t size);

/* Original0x4ac7b0: set the timer period at +0xc0 to twelve times the given count. */
int vertrix_actor_set_period_steps(void *actor, size_t size, uint32_t steps);

/* Original0x4ac7d0: set the timer period at +0xc0. */
int vertrix_actor_set_period(void *actor, size_t size, uint32_t period);

/* Original0x4ac8f0: set the handler token at +0x154 (an original address, never a native
 * pointer). */
int vertrix_actor_set_handler(void *actor, size_t size, uint32_t handler);

/* Original0x4ac380: clear the dword at +0xcc. */
int vertrix_actor_clear_cc(void *actor, size_t size);

/* Original0x4ac490: set the dword at +0xd0. */
int vertrix_actor_set_d0(void *actor, size_t size, uint32_t value);

/* Original0x4ac710: set the frame index at +0xb8 (looked up with the bank at +0xb0). */
int vertrix_actor_set_frame_index(void *actor, size_t size, uint32_t index);
/* Original0x4ac470: set the dword at +0xd0 to twelve times the given count. */
int vertrix_actor_set_d0_steps(void *actor, size_t size, uint32_t steps);

/* Original0x4ac900: read the handler token at +0x154. */
int vertrix_actor_get_handler(const void *actor, size_t size, uint32_t *handler);

/* Original0x4ac370: add delta (the frame step held in the global at 0x5bd834, read at the
 * boundary) to the dword +0xcc. Original0x4ac390: +0xcc has reached +0xd0 (unsigned). */
int vertrix_actor_add_cc(void *actor, size_t size, uint32_t delta);
/* Original 0x4ac390: Counter +0xcc has reached +0xd0 (unsigned). */
int vertrix_actor_cc_reached(const void *actor, size_t size, uint32_t *reached);

/* Original 0x4ac520: the counter +0xbc has reached the period +0xc0 (unsigned). */
int vertrix_actor_counter_reached(const void *actor, size_t size, uint32_t *reached);
/* Original 0x4ac540: +0xbc divided by +0xc0 (1 when zero). */
int vertrix_actor_counter_quotient(const void *actor, size_t size, uint32_t *quotient);
/* Original 0x4ac640: +0xdc divided by +0xe0 (1 when zero). */
int vertrix_actor_progress_quotient(const void *actor, size_t size, uint32_t *quotient);

/* Original0x4ac700 (+0xb8 = 0), 0x4ac740 (increment), 0x4ac750 (decrement) and 0x4ac7a0 (+0xb8 is
 * zero): the frame index counter. */
int vertrix_actor_reset_frame_counter(void *actor, size_t size);
/* Original 0x4ac740: Increment frame index +0xb8. */
int vertrix_actor_next_frame_counter(void *actor, size_t size);
/* Original 0x4ac750: Decrement frame index +0xb8. */
int vertrix_actor_previous_frame_counter(void *actor, size_t size);
/* Original 0x4ac7a0: Frame index +0xb8 is zero. */
int vertrix_actor_frame_counter_is_zero(const void *actor, size_t size, uint32_t *zero);

/* Original0x4ac840 (+0xe0 = steps * 12), 0x4ac860 (+0xe0 = value), 0x4ac910 (+0xec), 0x4ac930
 * (+0xf0) and 0x4ac950 (+0xb4) setters, 0x4ac960 (+0xb4) getter. */
int vertrix_actor_set_e0_steps(void *actor, size_t size, uint32_t steps);
/* Original 0x4ac860: Store the value at +0xe0. */
int vertrix_actor_set_e0(void *actor, size_t size, uint32_t value);
/* Original 0x4ac910: Store the value at +0xec. */
int vertrix_actor_set_ec(void *actor, size_t size, uint32_t value);
/* Original 0x4ac930: Store the value at +0xf0. */
int vertrix_actor_set_f0(void *actor, size_t size, uint32_t value);
/* Original 0x4ac950: Store the value at +0xb4. */
int vertrix_actor_set_b4(void *actor, size_t size, uint32_t value);
/* Original 0x4ac960: Read the value at +0xb4. */
int vertrix_actor_get_b4(const void *actor, size_t size, uint32_t *value);

/* Original0x4ac920 and 0x4ac940: copy the dword +0xec / +0xf0 to the handler token +0x154. */
int vertrix_actor_handler_from_ec(void *actor, size_t size);
/* Original 0x4ac940: Copy +0xf0 to handler +0x154. */
int vertrix_actor_handler_from_f0(void *actor, size_t size);

/* Original0x4ac4e0 (+0x114 = first, +0x118 = second) and 0x4ac4f0 (+0x11c = value). */
int vertrix_actor_set_114(void *actor, size_t size, uint32_t first, uint32_t second);
/* Original 0x4ac4f0: Store the value at +0x11c. */
int vertrix_actor_set_11c(void *actor, size_t size, uint32_t value);

/* Original0x4ad510 (words +0x2a, +0x2c, +0x2e) and 0x4ad520 (words +0x3a, +0x3c, +0x3e). */
int vertrix_actor_set_words_2a(void *actor, size_t size, uint16_t a, uint16_t b, uint16_t c);
/* Original 0x4ad520: Store words at +0x3a, +0x3c and +0x3e. */
int vertrix_actor_set_words_3a(void *actor, size_t size, uint16_t a, uint16_t b, uint16_t c);

/* Original0x4b54d0: words +0xe = x, +0x16 = y; dwords +0xf4 = width and +0xf8 = height (zero
 * extended words). */
int vertrix_actor_set_box(void *actor, size_t size, uint16_t x, uint16_t y, uint16_t width,
                          uint16_t height);

/* Original0x4ac5b0 (counter +0xbc, period +0xc0) and 0x4ac6b0 (progress +0xdc, total +0xe0):
 * keep the remainder of the dword by the divisor (a zero divisor counts as one): the dword is
 * replaced by itself minus the quotient times the divisor, or by zero when that product reaches
 * it. */
int vertrix_actor_counter_wrap(void *actor, size_t size);
/* Original 0x4ac6b0: Wrap progress +0xdc by total +0xe0; zero divisor counts as one. */
int vertrix_actor_progress_wrap(void *actor, size_t size);
#endif
