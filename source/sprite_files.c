#include "sprite_files.h"
#include <stdlib.h>
#include <string.h>

int vertrix_sprite_file(VertrixVf *archive, uint32_t slot, char *output, size_t capacity)
{
    uint32_t index, size;
    if (!output || slot >= 23 || !vertrix_vf_find(archive, "texte/SpriteFileName.ini", &index) ||
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
    const unsigned char *selected = NULL;
    size_t selected_length = 0;
    unsigned row = 0;
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
        while (line < line_end && *line == ' ')
        {
            ++line;
        }
        if (line == line_end || *line == '/')
        {
            continue;
        }
        const unsigned char *name = line;
        while (line < line_end && *line != '\\')
        {
            if (*line < 32 || *line == '/' || *line == ':')
            {
                goto done;
            }
            ++line;
        }
        size_t length = (size_t)(line - name);
        if (line == line_end || !length || row >= 23)
        {
            goto done;
        }
        if (row == slot)
        {
            selected = name;
            selected_length = length;
        }
        ++row;
        ++line;
        while (line < line_end && *line == ' ')
        {
            ++line;
        }
        if (line < line_end && *line != '/')
        {
            goto done;
        }
    }
    const char prefix[] = ".\\SPRITE\\";
    if (selected_length > SIZE_MAX - sizeof(prefix) || selected_length + sizeof(prefix) > capacity)
    {
        goto done;
    }
    memcpy(output, prefix, sizeof(prefix) - 1);
    if (selected_length)
    {
        memcpy(output + sizeof(prefix) - 1, selected, selected_length);
    }
    output[sizeof(prefix) - 1 + selected_length] = 0;
    success = 1;
done:
    free(text);
    return success;
}
