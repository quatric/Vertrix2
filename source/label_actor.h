#ifndef VERTRIX_LABEL_ACTOR_H
#define VERTRIX_LABEL_ACTOR_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Originals 0x45fb00 (variant 0) and 0x45fc80 (variant 1; eax = p, edx = dw, ebx = bx, ecx = cx
 * the caller's registers, ret 0x14 with arguments[0..4] at ebp + 8..0x18). Both build a framed
 * label from two actors. 0x4ca000(0x170) allocates the frame, a non-zero result going through
 * 0x4b3100 (edx zero, ebx = bx - 4, ecx = cx - 4); 0x4adf20 (five zero stack arguments)
 * initialises it, 0x4b54d0 sets the box (x = word p + 2, y = word dw + 2, width = word bx - 4,
 * height = word cx - 4), 0x4ac7b0 sets the period to two. Its byte +0x94 is set; +0x110 is zero
 * for variant 0, while variant 1 sets +0x110, +0x52 = 9 and +0x95 and calls 0x4ac4e0 (0x7f, 0).
 * 0x4ca000(0x180) allocates the text actor (a non-zero result going through 0x4b6350 with ecx =
 * 3), 0x4adf20 initialises it, 0x4b65d0 (three zero stack arguments) gives it the text and glyph
 * of the arguments, 0x4ac7b0 sets its period, its byte +0x44 is stored and 0x4b3210 links it to
 * the frame. The arguments differ by variant: variant 0 uses text = arguments[2], glyph =
 * arguments[3], offset = arguments[0], flag = arguments[1], style = arguments[4]; variant 1 uses
 * text = arguments[0], glyph = arguments[1], offset = arguments[3], flag = arguments[4], style =
 * arguments[2]. Returns the frame actor, zero when an actor does not resolve. */
uint32_t vertrix_label_frame(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             unsigned variant, uint32_t p, uint32_t dw, uint32_t bx, uint32_t cx,
                             const uint32_t arguments[5]);

/* Originals 0x45fe10 (variant 0) and 0x45fee0 (variant 1; the registers as above, no stack
 * arguments). 0x4ca000(0x160) allocates the actor, a non-zero result going through 0x4b5400;
 * the original adds 2 to the dword made of the word dw and the stale halfword above it on its
 * stack (`stale`), which reaches the allocator as ebx. 0x4adf20, 0x4b54d0 (x = word p + 2, y =
 * word dw + 2), 0x4ac7b0 set the box, the bytes +0x94, +0x95 and +0x110 are set and 0x4ac4f0 and
 * 0x4ac4e0 receive 0x450080 and 0x3003e (variant 0) or 0x7f and 0x3f (variant 1). Returns the
 * actor, zero when it does not resolve. */
uint32_t vertrix_label_box(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           unsigned variant, uint32_t p, uint32_t dw, uint32_t bx, uint32_t cx,
                           uint32_t stale);
#endif
