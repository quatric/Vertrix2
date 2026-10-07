#ifndef VERTRIX_ACTOR_FIELDS_H
#define VERTRIX_ACTOR_FIELDS_H
#include "actor_storage.h"
/* One-field base actor setters. Short or null storage is preserved and reports zero. */

/* Original fragment 0x4ac510: clear the timer counter at +0xbc. */
int vertrix_actor_clear_counter(void *actor, size_t size);

/* Original fragment 0x4ac7b0: set the timer period at +0xc0 to twelve times the given count. */
int vertrix_actor_set_period_steps(void *actor, size_t size, uint32_t steps);

/* Original fragment 0x4ac7d0: set the timer period at +0xc0. */
int vertrix_actor_set_period(void *actor, size_t size, uint32_t period);

/* Original fragment 0x4ac8f0: set the handler token at +0x154 (an original address, never a native
 * pointer). */
int vertrix_actor_set_handler(void *actor, size_t size, uint32_t handler);

/* Original fragment 0x4ac380: clear the dword at +0xcc. */
int vertrix_actor_clear_cc(void *actor, size_t size);

/* Original fragment 0x4ac490: set the dword at +0xd0. */
int vertrix_actor_set_d0(void *actor, size_t size, uint32_t value);

/* Original fragment 0x4ac710: set the frame index at +0xb8 (looked up with the bank at +0xb0). */
int vertrix_actor_set_frame_index(void *actor, size_t size, uint32_t index);
/* Original fragment 0x4ac470: set the dword at +0xd0 to twelve times the given count. */
int vertrix_actor_set_d0_steps(void *actor, size_t size, uint32_t steps);

/* Original fragment 0x4ac900: read the handler token at +0x154. */
int vertrix_actor_get_handler(const void *actor, size_t size, uint32_t *handler);

/* Original fragment 0x4ac370: add delta (the frame step held in the global at 0x5bd834, read at the
 * boundary) to the dword +0xcc. Original fragment 0x4ac390: +0xcc has reached +0xd0 (unsigned). */
int vertrix_actor_add_cc(void *actor, size_t size, uint32_t delta);
/* Original fragment 0x4ac390: Counter +0xcc has reached +0xd0 (unsigned). */
int vertrix_actor_cc_reached(const void *actor, size_t size, uint32_t *reached);

/* Original fragment 0x4ac520: the counter +0xbc has reached the period +0xc0 (unsigned). */
int vertrix_actor_counter_reached(const void *actor, size_t size, uint32_t *reached);
/* Original fragment 0x4ac540: +0xbc divided by +0xc0 (1 when zero). */
int vertrix_actor_counter_quotient(const void *actor, size_t size, uint32_t *quotient);
/* Original fragment 0x4ac640: +0xdc divided by +0xe0 (1 when zero). */
int vertrix_actor_progress_quotient(const void *actor, size_t size, uint32_t *quotient);

/* Original fragment 0x4ac700 (+0xb8 = 0), 0x4ac740 (increment), 0x4ac750 (decrement) and 0x4ac7a0
 * (+0xb8 is zero): the frame index counter. */
int vertrix_actor_reset_frame_counter(void *actor, size_t size);
/* Original fragment 0x4ac740: Increment frame index +0xb8. */
int vertrix_actor_next_frame_counter(void *actor, size_t size);
/* Original fragment 0x4ac750: Decrement frame index +0xb8. */
int vertrix_actor_previous_frame_counter(void *actor, size_t size);
/* Original fragment 0x4ac7a0: Frame index +0xb8 is zero. */
int vertrix_actor_frame_counter_is_zero(const void *actor, size_t size, uint32_t *zero);

/* Original fragment 0x4ac840 (+0xe0 = steps * 12), 0x4ac860 (+0xe0 = value), 0x4ac910 (+0xec),
 * 0x4ac930
 * (+0xf0) and 0x4ac950 (+0xb4) setters, 0x4ac960 (+0xb4) getter. */
int vertrix_actor_set_e0_steps(void *actor, size_t size, uint32_t steps);
/* Original fragment 0x4ac860: Store the value at +0xe0. */
int vertrix_actor_set_e0(void *actor, size_t size, uint32_t value);
/* Original fragment 0x4ac910: Store the value at +0xec. */
int vertrix_actor_set_ec(void *actor, size_t size, uint32_t value);
/* Original fragment 0x4ac930: Store the value at +0xf0. */
int vertrix_actor_set_f0(void *actor, size_t size, uint32_t value);
/* Original fragment 0x4ac950: Store the value at +0xb4. */
int vertrix_actor_set_b4(void *actor, size_t size, uint32_t value);
/* Original fragment 0x4ac960: Read the value at +0xb4. */
int vertrix_actor_get_b4(const void *actor, size_t size, uint32_t *value);

/* Original fragment 0x4ac920 and 0x4ac940: copy the dword +0xec / +0xf0 to the handler token
 * +0x154. */
int vertrix_actor_handler_from_ec(void *actor, size_t size);
/* Original fragment 0x4ac940: Copy +0xf0 to handler +0x154. */
int vertrix_actor_handler_from_f0(void *actor, size_t size);

/* Original fragment 0x4ac4e0 (+0x114 = first, +0x118 = second) and 0x4ac4f0 (+0x11c = value). */
int vertrix_actor_set_114(void *actor, size_t size, uint32_t first, uint32_t second);
/* Original fragment 0x4ac4f0: Store the value at +0x11c. */
int vertrix_actor_set_11c(void *actor, size_t size, uint32_t value);

/* Original fragment 0x4ad510 (words +0x2a, +0x2c, +0x2e) and 0x4ad520 (words +0x3a, +0x3c, +0x3e).
 */
int vertrix_actor_set_words_2a(void *actor, size_t size, uint16_t a, uint16_t b, uint16_t c);
/* Original fragment 0x4ad520: Store words at +0x3a, +0x3c and +0x3e. */
int vertrix_actor_set_words_3a(void *actor, size_t size, uint16_t a, uint16_t b, uint16_t c);

/* Original fragment 0x4b54d0: words +0xe = x, +0x16 = y; dwords +0xf4 = width and +0xf8 = height
 * (zero extended words). */
int vertrix_actor_set_box(void *actor, size_t size, uint16_t x, uint16_t y, uint16_t width,
                          uint16_t height);

/* Original fragment 0x4ac5b0 (counter +0xbc, period +0xc0) and 0x4ac6b0 (progress +0xdc, total
 * +0xe0): keep the remainder of the dword by the divisor (a zero divisor counts as one): the dword
 * is replaced by itself minus the quotient times the divisor, or by zero when that product reaches
 * it. */
int vertrix_actor_counter_wrap(void *actor, size_t size);
/* Original fragment 0x4ac6b0: Wrap progress +0xdc by total +0xe0; zero divisor counts as one. */
int vertrix_actor_progress_wrap(void *actor, size_t size);
/* Original 0x4ac5b0: consume whole periods from counter +0xbc, leaving its remainder. Returns
 * the original eax, the consumed quotient-times-period product. A zero period counts as one.
 * Short/null storage returns zero without changes. */
uint32_t vertrix_actor_counter_consume(void *actor, size_t size);
/* Original 0x4ac6b0: the same operation and original eax for progress +0xdc and total +0xe0. */
uint32_t vertrix_actor_progress_consume(void *actor, size_t size);

/* Complete normal-return APIs below preserve the original eax. Object is the guest object
 * token, independently of native storage. Short/null storage returns zero without writes. */

/* Shared operation for entrypoints 0x4ac510, 0x4ac380, 0x4ac700: clear dword +0xbc, +0xcc or +0xb8,
 * respectively, and return the object token. */
uint32_t vertrix_actor_clear_field(void *actor, size_t size, uint32_t object, uint32_t offset);

/* Shared operation for entrypoints 0x4ac7d0, 0x4ac8f0, 0x4ac490, 0x4ac710, 0x4ac860, 0x4ac910,
 * 0x4ac930, 0x4ac950, 0x4ac4f0: write edx to +0xc0, +0x154, +0xd0, +0xb8, +0xe0,
 * +0xec, +0xf0, +0xb4 or +0x11c, respectively, and return the object token. */
uint32_t vertrix_actor_store_field(void *actor, size_t size, uint32_t object, uint32_t offset,
                                   uint32_t value);

/* Shared operation for entrypoints 0x4ac740, 0x4ac750: increment (delta=1) or decrement
 * (delta=UINT32_MAX) frame counter +0xb8, wrapping in 32 bits, and return the object token. */
uint32_t vertrix_actor_step_frame(void *actor, size_t size, uint32_t object, uint32_t delta);

/* Shared operation for entrypoints 0x4ac900, 0x4ac960: return the dword at +0x154 or +0xb4. */
uint32_t vertrix_actor_read_field(const void *actor, size_t size, uint32_t offset);

/* Shared operation for entrypoints 0x4ac540, 0x4ac640: return +0xbc / +0xc0 or +0xdc / +0xe0,
 * respectively. Unsigned division uses one when the divisor is zero. */
uint32_t vertrix_actor_divide_counter(const void *actor, size_t size, uint32_t dividend_offset,
                                      uint32_t divisor_offset);

/* Shared operation for entrypoint 0x4ac7a0: return one when frame counter +0xb8 is zero, otherwise
 * zero. */
uint32_t vertrix_actor_test_frame_zero(const void *actor, size_t size);

/* Shared operation for entrypoint 0x4ac4e0: write ebx to +0x114 and edx to +0x118; return the
 * object token. */
uint32_t vertrix_actor_store_pair_114(void *actor, size_t size, uint32_t object, uint32_t first,
                                      uint32_t second);

/* Shared operation for entrypoints 0x4ad510, 0x4ad520: store the low words of edx, ebx and ecx at
 * +0x2a/+0x2c/+0x2e or +0x3a/+0x3c/+0x3e, respectively; return the object token. */
uint32_t vertrix_actor_store_word_triple(void *actor, size_t size, uint32_t object, uint32_t offset,
                                         uint32_t first, uint32_t second, uint32_t third);

/* Shared operation for entrypoint 0x4b54d0: write low words of edx/ebx to +0xe/+0x16, zero-extended
 * ecx low word to +0xf4 and zero-extended stack height low word to +0xf8. Return the zero-extended
 * height. */
uint32_t vertrix_actor_store_box(void *actor, size_t size, uint32_t x, uint32_t y, uint32_t width,
                                 uint32_t height);
/* Individually named complete entrypoints. Short/null storage returns zero without changes. */

/* Original 0x4ac510: clear dword +0xbc; return the original object token. */
uint32_t vertrix_actor_clear_counter_full(void *actor, size_t size, uint32_t object);

/* Original 0x4ac380: clear dword +0xcc; return the original object token. */
uint32_t vertrix_actor_clear_cc_full(void *actor, size_t size, uint32_t object);

/* Original 0x4ac700: clear dword +0xb8; return the original object token. */
uint32_t vertrix_actor_reset_frame_counter_full(void *actor, size_t size, uint32_t object);

/* Original 0x4ac7d0: write value to +0xc0; return the original object token. */
uint32_t vertrix_actor_set_period_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac8f0: write value to +0x154; return the original object token. */
uint32_t vertrix_actor_set_handler_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac490: write value to +0xd0; return the original object token. */
uint32_t vertrix_actor_set_d0_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac710: write value to +0xb8; return the original object token. */
uint32_t vertrix_actor_set_frame_index_full(void *actor, size_t size, uint32_t object,
                                            uint32_t value);

/* Original 0x4ac860: write value to +0xe0; return the original object token. */
uint32_t vertrix_actor_set_e0_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac910: write value to +0xec; return the original object token. */
uint32_t vertrix_actor_set_ec_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac930: write value to +0xf0; return the original object token. */
uint32_t vertrix_actor_set_f0_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac950: write value to +0xb4; return the original object token. */
uint32_t vertrix_actor_set_b4_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac4f0: write value to +0x11c; return the original object token. */
uint32_t vertrix_actor_set_11c_full(void *actor, size_t size, uint32_t object, uint32_t value);

/* Original 0x4ac740: increment frame counter +0xb8 with 32-bit wrap; return the object token. */
uint32_t vertrix_actor_next_frame_counter_full(void *actor, size_t size, uint32_t object);

/* Original 0x4ac750: decrement frame counter +0xb8 with 32-bit wrap; return the object token. */
uint32_t vertrix_actor_previous_frame_counter_full(void *actor, size_t size, uint32_t object);

/* Original 0x4ac900: return dword +0x154 as the original eax. */
uint32_t vertrix_actor_get_handler_full(const void *actor, size_t size);

/* Original 0x4ac960: return dword +0xb4 as the original eax. */
uint32_t vertrix_actor_get_b4_full(const void *actor, size_t size);

/* Original 0x4ac540: return unsigned +0xbc / +0xc0, treating a zero divisor as one. */
uint32_t vertrix_actor_counter_quotient_full(const void *actor, size_t size);

/* Original 0x4ac640: return unsigned +0xdc / +0xe0, treating a zero divisor as one. */
uint32_t vertrix_actor_progress_quotient_full(const void *actor, size_t size);

/* Original 0x4ac7a0: return one when frame counter +0xb8 is zero, otherwise zero. */
uint32_t vertrix_actor_frame_counter_is_zero_full(const void *actor, size_t size);

/* Original 0x4ac4e0: write first/second to +0x114/+0x118; return the object token. */
uint32_t vertrix_actor_set_114_full(void *actor, size_t size, uint32_t object, uint32_t first,
                                    uint32_t second);

/* Original 0x4ad510: write low words to +0x2a/+0x2c/+0x2e; return the object token. */
uint32_t vertrix_actor_set_words_2a_full(void *actor, size_t size, uint32_t object, uint32_t first,
                                         uint32_t second, uint32_t third);

/* Original 0x4ad520: write low words to +0x3a/+0x3c/+0x3e; return the object token. */
uint32_t vertrix_actor_set_words_3a_full(void *actor, size_t size, uint32_t object, uint32_t first,
                                         uint32_t second, uint32_t third);

/* Original 0x4b54d0: write low-word position and zero-extended low-word dimensions; return the
 * zero-extended height. */
uint32_t vertrix_actor_set_box_full(void *actor, size_t size, uint32_t x, uint32_t y,
                                    uint32_t width, uint32_t height);
#endif
