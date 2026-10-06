#include "render_pixel.h"
#include "palette_map.h"

static uint32_t color_index(uint32_t value)
{
    return ((value & 0xfc0000u) >> 6) | ((value & 0xfc00u) >> 4) | ((value & 0xfcu) >> 2);
}

static int palette_blend(uint32_t source, uint32_t destination, uint32_t kernel,
                         const VertrixRenderPreparation *prepared,
                         const VertrixPaletteTables *tables, uint32_t *output)
{
    if (!prepared || !tables || !tables->lookup)
    {
        return 0;
    }
    uint32_t entry = tables->lookup[color_index(source)];
    uint32_t other = tables->lookup[color_index(destination)];
    uint8_t row = (uint8_t)entry;
    if (kernel == 0x48da80 || kernel == 0x48e5f0)
    {
        row = (uint8_t)(((entry & 255u) + (other & 255u)) / 2u);
    }
    else if (kernel == 0x48df10 || kernel == 0x48f800)
    {
        row = (uint8_t)other;
    }
    int32_t selected_row = row;
    if (kernel == 0x4901a0 || kernel == 0x4907d0)
    {
        if (!prepared->source_words || !prepared->destination_words)
        {
            return 0;
        }
        uint16_t weighted =
            (uint16_t)(prepared->source_words[row] + prepared->destination_words[other & 255u]);
        selected_row = weighted < 32768u ? weighted : (int32_t)weighted - 65536;
    }
    if ((kernel == 0x490340 || kernel == 0x490980) &&
        (!prepared->source_weights || !prepared->destination_weights))
    {
        return 0;
    }
    VertrixPaletteMap map;
    if (!vertrix_palette_map(tables, prepared->map_shift, selected_row, &map))
    {
        return 0;
    }
    uint32_t result = 0;
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t shift = 24 - i * 8;
        uint32_t channel = (entry >> shift) & 255u;
        uint32_t other_channel = (other >> shift) & 255u;
        if (kernel == 0x48e5f0 || kernel == 0x4907d0)
        {
            channel = prepared->color.indices[i];
        }
        if (kernel == 0x48de30 || kernel == 0x48f520)
        {
            channel = other_channel;
        }
        if (kernel == 0x48dba0)
        {
            channel = (channel + other_channel) / 2u;
        }
        else if (kernel == 0x490340 || kernel == 0x490980)
        {
            channel = (uint32_t)prepared->source_weights[channel] +
                      prepared->destination_weights[other_channel];
            if (kernel == 0x490980)
            {
                channel = (channel + prepared->color.indices[i]) / 2u;
            }
        }
        else if (kernel == 0x48e700)
        {
            channel = ((channel + other_channel) / 2u + prepared->color.indices[i]) / 2u;
        }
        if (kernel == 0x48d8c0 || kernel == 0x48ea30 || kernel == 0x48ec70 || kernel == 0x48eeb0 ||
            kernel == 0x48f0a0 || kernel == 0x48f260 || kernel == 0x48f800)
        {
            channel = (channel + prepared->color.indices[i]) / 2u;
        }
        if (kernel == 0x48f520)
        {
            channel = (channel + prepared->color.indices[i]) / 2u;
        }
        if (channel >= map.size)
        {
            return 0;
        }
        result |= (uint32_t)map.data[channel] << (16 - i * 8);
    }
    *output = result;
    return 1;
}

int vertrix_render_pixel32(uint32_t flags, uint32_t source, uint32_t destination,
                           const VertrixRenderPreparation *prepared,
                           const VertrixPaletteTables *tables, uint32_t *output)
{
    if (!output)
    {
        return 0;
    }
    uint32_t kernel = vertrix_render_kernel_address(flags, 4);
    switch (kernel)
    {
        case 0x48d720:
            *output = source;
            return 1;
        case 0x490dc0:
        case 0x490e90:
        case 0x490f60:
        case 0x491050:
        case 0x4911d0:
        case 0x4912e0:
        case 0x4913e0:
        case 0x491530:
        case 0x491620:
        case 0x491720:
        case 0x491820:
        case 0x491920:
        case 0x491a00:
        case 0x491af0:
        case 0x491be0:
        case 0x491ce0:
        case 0x491e10:
        case 0x491f70:
        case 0x492120:
        {
            if (!prepared || !tables || !tables->lookup || !tables->hue)
            {
                return 0;
            }
            uint32_t input = kernel == 0x490f60
                                 ? ((source >> 1) & 0x7f7f7fu) + prepared->color.half_color
                                 : source;
            if (kernel == 0x491a00)
            {
                input = destination;
            }
            if (kernel == 0x4912e0)
            {
                input = ((source >> 1) & 0x7f7f7fu) + ((destination >> 1) & 0x7f7f7fu);
            }
            if (kernel == 0x491e10)
            {
                if (!prepared->source_weights || !prepared->destination_weights)
                {
                    return 0;
                }
                input = 0;
                for (uint32_t shift = 0; shift < 24; shift += 8)
                {
                    uint32_t channel =
                        (uint32_t)prepared->source_weights[(source >> shift) & 255u] +
                        prepared->destination_weights[(destination >> shift) & 255u];
                    input |= channel << shift;
                }
            }
            if (kernel == 0x491050 &&
                !palette_blend(source, destination, 0x48ea30, prepared, tables, &input))
            {
                return 0;
            }
            uint32_t index = color_index(input);
            uint32_t entry;
            uint32_t tail = (uint32_t)(0x54bb90 + (int32_t)prepared->map_shift * 4);
            uint8_t hue = kernel == 0x490e90 ? prepared->color.hue : tables->hue[index];
            if (kernel == 0x491af0)
            {
                hue = tables->hue[color_index(destination)];
            }
            if (!vertrix_palette_tables_cycle(tables, hue, prepared->cycle, tail, &entry))
            {
                return 0;
            }
            VertrixPaletteMap map;
            uint32_t row_index = kernel == 0x491050 ? color_index(source) : index;
            if (kernel == 0x491be0)
            {
                row_index = color_index(destination);
            }
            int16_t row = (uint8_t)tables->lookup[row_index];
            if (kernel == 0x491ce0)
            {
                if (!prepared->source_words || !prepared->destination_words)
                {
                    return 0;
                }
                uint8_t other = (uint8_t)tables->lookup[color_index(destination)];
                uint16_t sum =
                    (uint16_t)(prepared->source_words[row] + prepared->destination_words[other]);
                row = (int16_t)(sum <= 0x7fffu ? (int32_t)sum : (int32_t)sum - 65536);
            }
            if (kernel == 0x4911d0)
            {
                row = (uint8_t)((row + (tables->lookup[color_index(destination)] & 255u)) / 2u);
            }
            if (!vertrix_palette_map(tables, prepared->map_shift, row, &map))
            {
                return 0;
            }
            uint32_t result = 0;
            for (uint32_t i = 0; i < 3; ++i)
            {
                uint32_t channel = (entry >> (24 - i * 8)) & 255u;
                if (kernel == 0x4913e0)
                {
                    uint32_t other = tables->lookup[color_index(destination)];
                    channel = (channel + ((other >> (24 - i * 8)) & 255u)) / 2u;
                }
                if (kernel == 0x491f70)
                {
                    if (!prepared->source_weights || !prepared->destination_weights)
                    {
                        return 0;
                    }
                    uint32_t other = tables->lookup[color_index(destination)];
                    uint32_t other_channel = (other >> (24 - i * 8)) & 255u;
                    channel = (uint32_t)prepared->source_weights[channel] +
                              prepared->destination_weights[other_channel];
                }
                if (channel >= map.size)
                {
                    return 0;
                }
                result |= (uint32_t)map.data[channel] << (16 - i * 8);
            }
            if (kernel == 0x491530 || kernel == 0x491620 || kernel == 0x491720 ||
                kernel == 0x491820)
            {
                return vertrix_render_effect_pixel(result, destination,
                                                   kernel == 0x491530   ? 1
                                                   : kernel == 0x491620 ? 4
                                                   : kernel == 0x491720 ? 5
                                                                        : 6,
                                                   output);
            }
            if (kernel == 0x491920 || kernel == 0x491a00)
            {
                result = ~result & 0xffffffu;
            }
            if (kernel == 0x492120)
            {
                if (!prepared->source_weights || !prepared->destination_weights)
                {
                    return 0;
                }
                uint32_t blended = 0;
                for (uint32_t shift = 0; shift < 24; shift += 8)
                {
                    uint32_t channel =
                        (uint32_t)prepared->source_weights[(result >> shift) & 255u] +
                        prepared->destination_weights[(destination >> shift) & 255u];
                    blended |= channel << shift;
                }
                result = blended;
            }
            *output = result;
            return 1;
        }
        case 0x48fcd0:
        case 0x48fdb0:
        {
            if (!prepared)
            {
                return 0;
            }
            uint32_t input = kernel == 0x48fcd0 ? source : destination;
            uint32_t blended = ((~input >> 1) & 0x7f7f7fu) + prepared->color.half_color;
            return vertrix_palette_map_pixel(tables, prepared->map_shift, blended, 0,
                                             prepared->color.indices, output);
        }
        case 0x48efc0:
        case 0x48f190:
            return prepared &&
                   vertrix_palette_map_pixel(tables, prepared->map_shift,
                                             ~(kernel == 0x48efc0 ? source : destination), 1,
                                             prepared->color.indices, output);
        case 0x48f0a0:
            return palette_blend(~source, destination, kernel, prepared, tables, output);
        case 0x48f260:
            return palette_blend(~destination, source, kernel, prepared, tables, output);
        case 0x48f070:
        case 0x48f230:
            if (!prepared)
            {
                return 0;
            }
            *output = ((~(kernel == 0x48f070 ? source : destination) >> 1) & 0x7f7f7fu) +
                      prepared->color.half_color;
            return 1;
        case 0x48d740:
        case 0x48d7f0:
        case 0x48f360:
            return prepared &&
                   vertrix_palette_map_pixel(tables, prepared->map_shift, source,
                                             kernel != 0x48d740, prepared->color.indices, output);
        case 0x48f430:
        case 0x48f6f0:
        case 0x48fe90:
        case 0x490010:
        {
            uint32_t mapped;
            if (!palette_blend(source, destination,
                               kernel == 0x48f6f0 || kernel == 0x490010 ? 0x48df10 : 0x48de30,
                               prepared, tables, &mapped))
            {
                return 0;
            }
            uint32_t blended = ((mapped >> 1) & 0x7f7f7fu) + prepared->color.half_color;
            if (kernel == 0x48fe90 || kernel == 0x490010)
            {
                return vertrix_palette_map_pixel(tables, prepared->map_shift, blended, 0,
                                                 prepared->color.indices, output);
            }
            *output = blended;
            return 1;
        }
        case 0x48f620:
            return prepared && vertrix_palette_map_pixel(tables, prepared->map_shift, destination,
                                                         1, prepared->color.indices, output);
        case 0x48d890:
        case 0x48d9a0:
        case 0x48f9f0:
        case 0x48faf0:
        case 0x48fbe0:
        {
            if (!prepared)
            {
                return 0;
            }
            uint32_t result = ((source >> 1) & 0x7f7f7fu) + prepared->color.half_color;
            if (kernel == 0x48f9f0 || kernel == 0x48faf0 || kernel == 0x48fbe0)
            {
                uint32_t mapped;
                if (!vertrix_palette_map_pixel(tables, prepared->map_shift, result, 0,
                                               prepared->color.indices, &mapped))
                {
                    return 0;
                }
                return vertrix_render_effect_pixel(mapped, destination,
                                                   kernel == 0x48f9f0   ? 4
                                                   : kernel == 0x48faf0 ? 5
                                                                        : 6,
                                                   output);
            }
            if (kernel == 0x48d9a0)
            {
                return vertrix_palette_map_pixel(tables, prepared->map_shift, result, 0,
                                                 prepared->color.indices, output);
            }
            *output = result;
            return 1;
        }
        case 0x48da80:
        case 0x48dba0:
        case 0x48de30:
        case 0x48f520:
        case 0x48df10:
        case 0x48f800:
        case 0x48e5f0:
        case 0x48e700:
        case 0x490340:
        case 0x490980:
        case 0x4901a0:
        case 0x48d8c0:
        case 0x4907d0:
            return palette_blend(source, destination, kernel, prepared, tables, output);
        case 0x48ea30:
        case 0x48ec70:
        case 0x48eeb0:
        {
            uint32_t mapped;
            if (!palette_blend(source, destination, kernel, prepared, tables, &mapped))
            {
                return 0;
            }
            return vertrix_render_effect_pixel(mapped, destination,
                                               kernel == 0x48ea30   ? 4
                                               : kernel == 0x48ec70 ? 5
                                                                    : 6,
                                               output);
        }
        case 0x48e9d0:
        case 0x48ec10:
        case 0x48ee50:
            if (!prepared)
            {
                return 0;
            }
            return vertrix_render_effect_pixel(
                ((source >> 1) & 0x7f7f7fu) + prepared->color.half_color, destination,
                kernel == 0x48e9d0   ? 4
                : kernel == 0x48ec10 ? 5
                                     : 6,
                output);
        case 0x48e6c0:
        case 0x48f910:
            if (!prepared)
            {
                return 0;
            }
            {
                uint32_t blended = ((source >> 2) & 0x3f3f3fu) + ((destination >> 2) & 0x3f3f3fu) +
                                   prepared->color.half_color;
                if (kernel == 0x48f910)
                {
                    return vertrix_palette_map_pixel(tables, prepared->map_shift, blended, 0,
                                                     prepared->color.indices, output);
                }
                *output = blended;
                return 1;
            }
        case 0x48db70:
        case 0x48dcd0:
            return vertrix_render_effect_pixel(source, destination, 1, output);
        case 0x48dd00:
            return vertrix_render_effect_pixel(source, destination, 4, output);
        case 0x48dd50:
            return vertrix_render_effect_pixel(source, destination, 5, output);
        case 0x48dda0:
            return vertrix_render_effect_pixel(source, destination, 6, output);
        case 0x48ddf0:
            return vertrix_render_effect_pixel(source, destination, 7, output);
        case 0x48de10:
            return vertrix_render_effect_pixel(source, destination, 8, output);
        case 0x48e0c0:
        case 0x48e190:
        case 0x48e280:
        case 0x48e370:
        case 0x48e460:
        case 0x48e520:
        case 0x48e850:
        case 0x48e900:
        case 0x48eb40:
        case 0x48ed80:
        {
            if (!prepared)
            {
                return 0;
            }
            uint32_t mapped;
            uint32_t input = kernel == 0x48e520 ? destination : source;
            if (!vertrix_palette_map_pixel(tables, prepared->map_shift, input,
                                           kernel == 0x48e850 || kernel == 0x48e900 ||
                                               kernel == 0x48eb40 || kernel == 0x48ed80,
                                           prepared->color.indices, &mapped))
            {
                return 0;
            }
            uint8_t effect = kernel == 0x48e0c0 || kernel == 0x48e850   ? 1
                             : kernel == 0x48e190 || kernel == 0x48e900 ? 4
                             : kernel == 0x48e280 || kernel == 0x48eb40 ? 5
                             : kernel == 0x48e370 || kernel == 0x48ed80 ? 6
                             : kernel == 0x48e460                       ? 7
                                                                        : 8;
            return vertrix_render_effect_pixel(mapped, kernel == 0x48e520 ? mapped : destination,
                                               effect, output);
        }
        case 0x48dff0:
        {
            if (!prepared)
            {
                return 0;
            }
            uint32_t blended;
            vertrix_render_effect_pixel(source, destination, 1, &blended);
            return vertrix_palette_map_pixel(tables, prepared->map_shift, blended, 0,
                                             prepared->color.indices, output);
        }
        case 0x4902a0:
        case 0x4904c0:
        case 0x490560:
        case 0x4906a0:
        case 0x490b30:
        case 0x4908c0:
        case 0x490c60:
        {
            if (!prepared || !prepared->source_weights || !prepared->destination_weights)
            {
                return 0;
            }
            if (kernel == 0x4906a0 || kernel == 0x490b30)
            {
                uint32_t mapped;
                if (!vertrix_palette_map_pixel(tables, prepared->map_shift, source,
                                               kernel == 0x490b30, prepared->color.indices,
                                               &mapped))
                {
                    return 0;
                }
                source = mapped;
            }
            uint32_t result = 0;
            for (uint32_t shift = 0; shift < 24; shift += 8)
            {
                uint32_t channel = (uint32_t)prepared->source_weights[(source >> shift) & 255u] +
                                   prepared->destination_weights[(destination >> shift) & 255u];
                if (kernel == 0x4908c0 || kernel == 0x490c60)
                {
                    channel = (channel + prepared->color.channels[2 - shift / 8]) / 2u;
                }
                result |= channel << shift;
            }
            if (kernel == 0x490560 || kernel == 0x490c60)
            {
                return vertrix_palette_map_pixel(tables, prepared->map_shift, result, 0,
                                                 prepared->color.indices, output);
            }
            *output = result;
            return 1;
        }
        default:
            return 0;
    }
}
