#include "ui_slide_setup.h"
#include "guest_bytes.h"

enum
{
    CENTER_X = 0xe,
    START_X = 0x10,
    STEP_X = 0x12,
    TARGET_X = 0x14,
    CENTER_Y = 0x16,
    START_Y = 0x18,
    STEP_Y = 0x1a,
    TARGET_Y = 0x1c,
    ANCHOR_X = 8,
    ANCHOR_Y = 0xa,
    ANCHOR_Z = 0xc,
    FALLBACK_WIDTH = 0xf4,
    FALLBACK_HEIGHT = 0xf8,
    OBJECT_MODE = 0x44,
    SCREEN_OVERRIDE = 0x91,
    SLIDE_STEP = 8,
    SLIDE_STEP_VERTICAL = 4,
    BELOW_DISTANCE = 0x140,
    ABOVE_DISTANCE = 0x70,
    EDGE_MARGIN = 4
};

int vertrix_ui_slide_from_below(uint8_t *actor, size_t size)
{
    if (!actor || size < VERTRIX_SLIDE_STORAGE_SIZE)
    {
        return 0;
    }
    vertrix_guest_set16(actor, STEP_X, SLIDE_STEP);
    vertrix_guest_set16(actor, START_X, vertrix_guest_get16(actor, CENTER_X));
    vertrix_guest_set16(actor, STEP_Y, SLIDE_STEP);
    uint16_t y = vertrix_guest_get16(actor, CENTER_Y);
    vertrix_guest_set16(actor, START_Y, y);
    vertrix_guest_set16(actor, CENTER_Y, (uint16_t)(y + BELOW_DISTANCE));
    return 1;
}

int vertrix_ui_slide_sideways(uint8_t *actor, size_t size, uint32_t mode, int32_t distance,
                              int32_t offset, uint16_t screen_width)
{
    if (!actor || size < VERTRIX_SLIDE_STORAGE_SIZE)
    {
        return 0;
    }
    uint16_t y = vertrix_guest_get16(actor, CENTER_Y);
    vertrix_guest_set16(actor, START_Y, y);
    vertrix_guest_set16(actor, TARGET_Y, y);
    vertrix_guest_set16(actor, START_X, vertrix_guest_get16(actor, CENTER_X));
    uint32_t x;
    if (mode == 1)
    {
        x = (uint32_t)(-distance) - EDGE_MARGIN + (uint32_t)offset;
    }
    else
    {
        x = (uint32_t)screen_width + EDGE_MARGIN + (uint32_t)offset;
    }
    vertrix_guest_set16(actor, CENTER_X, (uint16_t)x);
    vertrix_guest_set16(actor, TARGET_X, (uint16_t)x);
    vertrix_guest_set16(actor, STEP_X, SLIDE_STEP);
    vertrix_guest_set16(actor, STEP_Y, SLIDE_STEP);
    return 1;
}

int vertrix_ui_slide_from_above(uint8_t *actor, size_t size)
{
    if (!actor || size < VERTRIX_SLIDE_STORAGE_SIZE)
    {
        return 0;
    }
    vertrix_guest_set16(actor, STEP_X, SLIDE_STEP);
    vertrix_guest_set16(actor, START_X, vertrix_guest_get16(actor, CENTER_X));
    vertrix_guest_set16(actor, STEP_Y, SLIDE_STEP_VERTICAL);
    uint16_t y = vertrix_guest_get16(actor, CENTER_Y);
    vertrix_guest_set16(actor, START_Y, y);
    y = (uint16_t)(y - ABOVE_DISTANCE);
    vertrix_guest_set16(actor, CENTER_Y, y);
    vertrix_guest_set16(actor, ANCHOR_X, vertrix_guest_get16(actor, CENTER_X));
    vertrix_guest_set16(actor, ANCHOR_Y, y);
    return 1;
}

static int16_t signed_word(const uint8_t *actor, size_t offset)
{
    return (int16_t)vertrix_guest_get16(actor, offset);
}

int vertrix_ui_center_on_anchor(uint8_t *actor, size_t size,
                                const VertrixResourceDimensions *descriptor,
                                uint8_t screen_unscaled, uint8_t screen_mode)
{
    if (!actor || size < VERTRIX_CENTER_STORAGE_SIZE)
    {
        return 0;
    }
    VertrixResourceDimensions fallback = {vertrix_guest_get16(actor, FALLBACK_WIDTH),
                                          vertrix_guest_get16(actor, FALLBACK_HEIGHT)};
    int32_t width = 0;
    int32_t height = 0;
    vertrix_resource_measure_state(descriptor, fallback, vertrix_guest_get8(actor, OBJECT_MODE),
                                   vertrix_guest_get8(actor, SCREEN_OVERRIDE), screen_unscaled,
                                   screen_mode, &width, &height);
    int32_t x = signed_word(actor, ANCHOR_X) - (int32_t)((uint32_t)width >> 1);
    vertrix_guest_set16(actor, CENTER_X, (uint16_t)x);
    int32_t y = signed_word(actor, ANCHOR_Y) - (int32_t)((uint32_t)height >> 1);
    vertrix_guest_set16(actor, CENTER_Y, (uint16_t)(y + signed_word(actor, ANCHOR_Z)));
    return 1;
}
