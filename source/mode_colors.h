#ifndef VERTRIX_MODE_COLORS_H
#define VERTRIX_MODE_COLORS_H
#include <stdint.h>
/* Original palette words read by 0x43bd90: 0x4f81cc is the default, 0x4f8198 and 0x4f81a4 the
 * two main colors and 0x4f818c, 0x4f81ac two accents. */
typedef struct
{
    uint32_t base;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t fourth;
} VertrixModeColors;

/* Original0x43bd90: choose the primary and secondary color of an effect mode. Both start as the
 * default; a mode selects the first/second/accent color for the primary and, for many modes
 * when flag is 1, the second color for the secondary. A primary left at the default becomes the
 * second color. sub is the effect sub-mode that modes 0x12 and 0x19 consult. The routine
 * writes the two palette globals back unchanged. */
void vertrix_mode_colors(const VertrixModeColors *colors, uint8_t mode, uint8_t sub, uint32_t flag,
                         uint32_t *primary, uint32_t *secondary);
#endif
