#ifndef VERTRIX_EVENT_FRAME_DRAW_H
#define VERTRIX_EVENT_FRAME_DRAW_H

#include <stddef.h>
#include <stdint.h>

/* Callbacks for draw boundaries */
typedef void (*VertrixDrawDirectCallback)(const void *event, uint32_t edx, uint32_t ebx,
                                          uint32_t ecx, const uint32_t stack[4], void *context);

typedef void (*VertrixDrawBlendCallback)(const void *event, uint32_t edx, uint32_t ebx,
                                         uint32_t ecx, const uint32_t stack[5], void *context);

typedef void (*VertrixDrawScaledCallback)(const void *event, uint32_t edx, uint32_t ebx,
                                          uint32_t ecx, const uint32_t stack[5], void *context);

/* Original 0x482e10: prepares an event record from item descriptor (+0, +4, +8, +0x27),
 * maps key index via 0x478cd0 and scales fields via 0x478da0, then dispatches to 0x47ce10. */
int vertrix_event_frame_draw_direct(const void *item, size_t size, uint32_t edx, uint32_t ebx,
                                    uint32_t ecx, VertrixDrawDirectCallback draw, void *context);

/* Original 0x482e80: prepares an event record from item descriptor, maps key and scales,
 * then dispatches to 0x47c930 with an extra blend stack parameter. */
int vertrix_event_frame_draw_blend(const void *item, size_t size, uint32_t edx, uint32_t ebx,
                                   uint32_t ecx, uint32_t extra, VertrixDrawBlendCallback blend,
                                   void *context);

/* Original 0x482f00: prepares an event record from item descriptor, maps key and scales,
 * then dispatches to 0x47cb40 with five scaled parameters. */
int vertrix_event_frame_draw_scaled(const void *item, size_t size, uint32_t edx, uint32_t ebx,
                                    uint32_t ecx, const uint32_t args[5],
                                    VertrixDrawScaledCallback draw_scaled, void *context);

#endif
