#include "assets.h"

#include <stdlib.h>
#include <string.h>

static int block_filename(const unsigned char **cursor, const unsigned char *end, char output[128])
{
    const unsigned char *start = *cursor;
    while (*cursor < end && **cursor != '\\')
    {
        if (**cursor < 32 || **cursor == '/' || **cursor == ':')
        {
            return 0;
        }
        ++*cursor;
    }
    size_t length = (size_t)(*cursor - start);
    const char prefix[] = "image/Blocs/";
    if (*cursor == end || !length || length + sizeof(prefix) > 128)
    {
        return 0;
    }
    memcpy(output, prefix, sizeof(prefix) - 1);
    memcpy(output + sizeof(prefix) - 1, start, length);
    output[sizeof(prefix) - 1 + length] = 0;
    ++*cursor;
    return 1;
}

int vertrix_asset_block_files(VertrixVf *archive, uint32_t character, VertrixBlockFiles *files)
{
    uint32_t index, size;
    if (!files || character >= 20 || !vertrix_vf_find(archive, "texte/BlocsFileName.ini", &index) ||
        !vertrix_vf_size(archive, index, &size) || !size || size > 65536)
    {
        return 0;
    }
    unsigned char *text = malloc(size);
    if (!text)
    {
        return 0;
    }
    int success = 0;
    uint32_t row = 0;
    VertrixBlockFiles selected = {0};
    if (!vertrix_vf_read(archive, index, 0, text, size))
    {
        goto done;
    }
    const unsigned char *cursor = text;
    const unsigned char *end = text + size;
    while (cursor < end)
    {
        const unsigned char *line = cursor;
        while (cursor < end && *cursor != '\r' && *cursor != '\n')
        {
            ++cursor;
        }
        const unsigned char *line_end = cursor;
        while (cursor < end && (*cursor == '\r' || *cursor == '\n'))
        {
            ++cursor;
        }
        while (line < line_end && (*line == ' ' || *line == '\t'))
        {
            ++line;
        }
        if (line == line_end || *line == '/')
        {
            continue;
        }
        VertrixBlockFiles current = {0};
        if (row >= 20 || !block_filename(&line, line_end, current.artwork) ||
            !block_filename(&line, line_end, current.mask) || line == line_end || *line++ != '\\')
        {
            goto done;
        }
        while (line < line_end && (*line == ' ' || *line == '\t'))
        {
            ++line;
        }
        if (line < line_end && *line != '/')
        {
            goto done;
        }
        if (row == character)
        {
            selected = current;
        }
        ++row;
    }
    if (row == 20)
    {
        *files = selected;
        success = 1;
    }
done:
    free(text);
    return success;
}

static int horizontal_space(unsigned char byte)
{
    return byte == ' ' || byte == '\t';
}

void vertrix_block_set_free(VertrixBlockSet *set)
{
    if (!set)
    {
        return;
    }
    for (unsigned color = 0; color < 7; ++color)
    {
        for (unsigned frame = 0; frame < 8; ++frame)
        {
            vertrix_image_free(&set->frames[color][frame]);
        }
    }
    memset(set, 0, sizeof(*set));
}

int vertrix_asset_block_set(VertrixVf *archive, uint32_t character, const uint32_t masks[3],
                            VertrixBlockSet *output)
{
    if (!output || !masks)
    {
        return 0;
    }
    for (unsigned color = 0; color < 7; ++color)
    {
        for (unsigned frame = 0; frame < 8; ++frame)
        {
            const VertrixImage *image = &output->frames[color][frame];
            if (image->rgba || image->width || image->height)
            {
                return 0;
            }
        }
    }
    VertrixBlockFiles files;
    VertrixBlockSet loaded = {0};
    VertrixImage sheet = {0};
    int success = 0;
    if (!vertrix_asset_block_files(archive, character, &files) ||
        !vertrix_asset_animation_ranges(archive, character, loaded.delays) ||
        !vertrix_image_bmp_masked(archive, files.artwork, files.mask, &sheet))
    {
        goto done;
    }
    for (unsigned color = 0; color < 7; ++color)
    {
        for (unsigned frame = 0; frame < 8; ++frame)
        {
            VertrixImage *image = &loaded.frames[color][frame];
            if (!vertrix_image_block_frame(&sheet, color, frame, image) ||
                !vertrix_image_color_order(image, masks))
            {
                goto done;
            }
        }
    }
    *output = loaded;
    memset(&loaded, 0, sizeof(loaded));
    success = 1;
done:
    vertrix_image_free(&sheet);
    vertrix_block_set_free(&loaded);
    return success;
}

static int delay_row(const unsigned char *line, const unsigned char *end, uint32_t values[14])
{
    for (unsigned column = 0; column < 14; column++)
    {
        while (line < end && horizontal_space(*line))
        {
            line++;
        }
        if (line == end || *line < '0' || *line > '9')
        {
            return 0;
        }
        uint32_t number = 0;
        while (line < end && *line >= '0' && *line <= '9')
        {
            uint32_t digit = *line++ - '0';
            if (number > (UINT32_MAX - digit) / 10)
            {
                return 0;
            }
            number = number * 10 + digit;
        }
        while (line < end && horizontal_space(*line))
        {
            line++;
        }
        if (line == end || *line++ != '\\')
        {
            return 0;
        }
        values[column] = number;
    }
    while (line < end && horizontal_space(*line))
    {
        line++;
    }
    return line == end || *line == '/';
}

int vertrix_asset_animation_ranges(VertrixVf *archive, uint32_t character,
                                   VertrixAnimationRange ranges[7])
{
    uint32_t index, size;
    if (character >= 20 || !ranges || !vertrix_vf_find(archive, "texte/BlocsSpeed.ini", &index) ||
        !vertrix_vf_size(archive, index, &size) || size == 0 || size > 65536)
    {
        return 0;
    }
    unsigned char *text = malloc(size);
    if (!text)
    {
        return 0;
    }
    int success = 0;
    uint32_t row = 0;
    VertrixAnimationRange selected[7];
    if (!vertrix_vf_read(archive, index, 0, text, size))
    {
        goto done;
    }
    const unsigned char *cursor = text;
    const unsigned char *end = text + size;
    while (cursor < end)
    {
        const unsigned char *line = cursor;
        while (cursor < end && *cursor != '\r' && *cursor != '\n')
        {
            cursor++;
        }
        const unsigned char *line_end = cursor;
        while (cursor < end && (*cursor == '\r' || *cursor == '\n'))
        {
            cursor++;
        }
        while (line < line_end && horizontal_space(*line))
        {
            line++;
        }
        if (line == line_end || *line == '/')
        {
            continue;
        }
        uint32_t values[14];
        if (row >= 20 || !delay_row(line, line_end, values))
        {
            goto done;
        }
        if (row == character)
        {
            for (unsigned color = 0; color < 7; color++)
            {
                unsigned column = color == 5 ? 12 : color == 6 ? 10 : color * 2;
                selected[color].first = values[column];
                selected[color].last = values[column + 1];
                if (selected[color].last < selected[color].first ||
                    selected[color].last - selected[color].first >= 65535)
                {
                    goto done;
                }
            }
        }
        row++;
    }
    if (row == 20)
    {
        for (unsigned color = 0; color < 7; color++)
        {
            ranges[color] = selected[color];
        }
        success = 1;
    }

done:
    free(text);
    return success;
}
