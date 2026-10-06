#include "render_dispatch.h"
#include "render_dispatch_tables.h"

uint32_t vertrix_render_rule(uint32_t flags)
{
    for (uint32_t i = 0; i < 92; ++i)
    {
        uint32_t required = render_rules[i][0];
        uint32_t allowed = render_rules[i][1];
        if ((flags & required) == required && !(flags & ~(required | allowed)))
        {
            return i;
        }
    }
    return 92;
}

uint32_t vertrix_render_kernel_address(uint32_t flags, uint8_t target_format)
{
    uint32_t rule = vertrix_render_rule(flags);
    if (rule == 92)
    {
        return 0;
    }
    uint32_t row = 0;
    if (target_format == 2)
    {
        row = 1;
    }
    else if (target_format == 1)
    {
        row = 2;
    }
    else if (target_format == 0)
    {
        row = 3;
    }
    return render_addresses[row][rule];
}

uint32_t vertrix_render_flags(VertrixRenderFlagState state, uint32_t mode)
{
    uint32_t flags = state.flag_73a == 1 ? 0x80000u : 0;
    int direct = 0;
    if (mode == 1)
    {
        flags += 0x100000u;
        direct = 1;
    }
    else if (!state.flag_739)
    {
        flags += 1;
        direct = 1;
    }
    else
    {
        flags += state.amount_00e == 50 ? 8 : 16;
        if (state.effect_00d == 0)
        {
            flags += 0x100;
        }
        else if (state.effect_00d <= 10)
        {
            flags += 1u << (state.effect_00d + 8);
            if (state.effect_00d >= 4)
            {
                if (state.amount_00e != 50)
                {
                    flags -= 8;
                }
                direct = 1;
            }
        }
    }
    if (state.format_000 != state.format_730)
    {
        flags += 4;
        if (direct && state.transform_00c <= 2)
        {
            flags += 0x20u << state.transform_00c;
        }
    }
    if (state.word_002)
    {
        flags += 2;
    }
    return flags;
}

uint32_t vertrix_render_direct_pixel(uint32_t source, uint8_t target_format)
{
    if (target_format == 2)
    {
        return ((source & 0xf80000u) >> 8) | ((source & 0xfc00u) >> 5) | ((source & 0xf8u) >> 3);
    }
    if (target_format == 1)
    {
        return ((source & 0xf80000u) >> 9) | ((source & 0xf800u) >> 6) | ((source & 0xf8u) >> 3);
    }
    if (target_format == 0)
    {
        return ((source & 0xe00000u) >> 16) | ((source & 0xe000u) >> 11) | ((source & 0xc0u) >> 6);
    }
    return source;
}

int vertrix_render_direct_write(VertrixSurface *target, uint8_t target_format, uint32_t x,
                                uint32_t y, uint32_t source)
{
    uint8_t bytes = target_format == 0 ? 1 : (target_format == 1 || target_format == 2) ? 2 : 4;
    if (!target || target->bytes_per_pixel != bytes)
    {
        return 0;
    }
    return vertrix_surface_write(target, x, y, vertrix_render_direct_pixel(source, target_format));
}

int vertrix_render_effect_pixel(uint32_t source, uint32_t destination, uint8_t effect,
                                uint32_t *output)
{
    if (!output)
    {
        return 0;
    }
    uint32_t result;
    if (effect == 1 || effect == 3)
    {
        result = ((source >> 1) & 0x7f7f7fu) + ((destination >> 1) & 0x7f7f7fu);
    }
    else if (effect == 4)
    {
        uint32_t sum = (source & 0xfefeffu) + (destination & 0xfefeffu);
        result = (sum | (0x1010100u - ((sum & 0x1010100u) >> 7))) & 0xffffffu;
    }
    else if (effect == 5 || effect == 6)
    {
        uint32_t difference = effect == 5 ? (destination & 0xfefeffu) - (source & 0xfefeffu)
                                          : (source & 0xfefeffu) - (destination & 0xfefeffu);
        result = (difference & (((difference & 0x1010100u) >> 7) - 0x1010101u)) & 0xffffffu;
    }
    else if (effect == 7 || effect == 8)
    {
        result = ~(effect == 7 ? source : destination) & 0xffffffu;
    }
    else
    {
        return 0;
    }
    *output = result;
    return 1;
}

uint32_t vertrix_render_traversal_flags(uint8_t flag_fff, uint8_t scale_738, uint8_t flag_ff0)
{
    uint32_t flags = flag_fff == 1 ? 1 : 2;
    if (scale_738 != 16)
    {
        flags += 4;
    }
    if (flag_ff0 == 1)
    {
        flags += 8;
    }
    return flags;
}

uint32_t vertrix_render_traversal_index(uint32_t flags)
{
    static const uint32_t modes[8] = {2, 1, 6, 5, 10, 9, 14, 13};
    for (uint32_t i = 0; i < 8; ++i)
    {
        if (flags == modes[i])
        {
            return i;
        }
    }
    return 8;
}

uint32_t vertrix_render_traversal_group(uint32_t flags)
{
    static const uint32_t modes[4] = {0, 8, 4, 12};
    for (uint32_t i = 0; i < 4; ++i)
    {
        if (flags == modes[i])
        {
            return i;
        }
    }
    return 4;
}

int vertrix_render_pixels_enabled(uint32_t pixel_resource, uint8_t scale,
                                  VertrixRenderFlagState state)
{
    if (!pixel_resource || !scale)
    {
        return 0;
    }
    if (!state.amount_00e && state.flag_739 == 1 && !state.word_002 &&
        state.format_000 == state.format_730)
    {
        return 0;
    }
    return 1;
}

int vertrix_render_traversal(uint8_t flag_fff, uint8_t scale_738, uint8_t flag_ff0,
                             uint8_t target_format, VertrixRenderTraversal *output)
{
    static const uint32_t rows[4][8] = {
        {0x492400, 0x492280, 0x492710, 0x492550, 0x492460, 0x4922f0, 0x492770, 0x4925d0},
        {0x4a21e0, 0x4a2070, 0x4a24e0, 0x4a2330, 0x4a2240, 0x4a20e0, 0x4a2540, 0x4a23b0},
        {0x49a120, 0x499fb0, 0x49a420, 0x49a270, 0x49a180, 0x49a020, 0x49a480, 0x49a2f0},
        {0x4a9ee0, 0x4a9d70, 0x4aa1e0, 0x4aa030, 0x4a9f40, 0x4a9de0, 0x4aa240, 0x4aa0b0}};
    static const uint32_t images[4][4] = {{0x492880, 0x492980, 0x4928f0, 0x492a70},
                                          {0x4a2650, 0x4a2750, 0x4a26c0, 0x4a2840},
                                          {0x49a590, 0x49a690, 0x49a600, 0x49a780},
                                          {0x4aa350, 0x4aa450, 0x4aa3c0, 0x4aa540}};
    uint32_t format = target_format == 4   ? 0
                      : target_format == 2 ? 1
                      : target_format == 1 ? 2
                      : target_format == 0 ? 3
                                           : 4;
    if (!output || format == 4)
    {
        return 0;
    }
    uint32_t flags = vertrix_render_traversal_flags(flag_fff, scale_738, flag_ff0);
    uint32_t row = vertrix_render_traversal_index(flags);
    uint32_t image = vertrix_render_traversal_group(flags & 12u);
    if (row >= 8 || image >= 4)
    {
        return 0;
    }
    output->row_address = rows[format][row];
    output->image_address = images[format][image];
    return 1;
}

int vertrix_render_operation(uint32_t rule, uint32_t traversal_index, uint32_t traversal_group,
                             uint8_t target_format, uint32_t alpha_override,
                             VertrixRenderOperation *output)
{
    static const uint32_t fast[4][2] = {
        {0x4ab310, 0x4ab2a0}, {0x4ab830, 0x4ab790}, {0x4ab540, 0x4ab4a0}, {0x4abb30, 0x4aba80}};
    static const uint32_t alpha[4][8] = {{0x4ab380, 0x4ab380, 0, 0, 0x4930c0, 0x4930c0, 0, 0},
                                         {0x4ab8d0, 0x4ab8d0, 0, 0, 0x4a30a0, 0x4a30a0, 0, 0},
                                         {0x4ab5e0, 0x4ab5e0, 0, 0, 0x49b000, 0x49b000, 0, 0},
                                         {0x4abbd0, 0x4abbd0, 0, 0, 0x4aad90, 0x4aad90, 0, 0}};
    uint32_t format = target_format == 4   ? 0
                      : target_format == 2 ? 1
                      : target_format == 1 ? 2
                      : target_format == 0 ? 3
                                           : 4;
    if (!output || format == 4 || rule >= 92 || traversal_index >= 8 || traversal_group >= 4)
    {
        return 0;
    }
    VertrixRenderTraversal binding;
    uint8_t scale = traversal_group >= 2 ? 1 : 16;
    uint8_t transformed = traversal_group & 1u;
    if (!vertrix_render_traversal(traversal_index & 1u, scale, transformed, target_format,
                                  &binding))
    {
        return 0;
    }
    VertrixRenderOperation result = {binding.image_address, 1};
    if (alpha_override && rule == 0 && traversal_group < 2 && alpha[format][traversal_index])
    {
        result.operation_address = alpha[format][traversal_index];
        result.prepare = 0;
    }
    else if (!alpha_override && rule == 0 && traversal_group == 0 && traversal_index < 2)
    {
        result.operation_address = fast[format][traversal_index];
        result.prepare = 0;
    }
    *output = result;
    return 1;
}

int vertrix_render_weighted_pixel(uint32_t source, uint32_t destination, uint8_t amount,
                                  uint32_t *output)
{
    if (amount > 100 || !output)
    {
        return 0;
    }
    uint32_t result = 0;
    for (uint32_t shift = 0; shift < 24; shift += 8)
    {
        uint32_t channel = ((source >> shift) & 255) * amount / 100 +
                           ((destination >> shift) & 255) * (100 - amount) / 100;
        result |= channel << shift;
    }
    *output = result;
    return 1;
}
