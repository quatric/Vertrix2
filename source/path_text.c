#include "path_text.h"

enum
{
    BACKSLASH = 0x5c
};

size_t vertrix_path_last_separator(const uint8_t *path, size_t first, size_t last)
{
    size_t position = last;
    if (last <= first)
    {
        return last;
    }
    do
    {
        if (path[position] == BACKSLASH)
        {
            return position;
        }
        --position;
    } while (position > first);
    return position;
}

uint32_t vertrix_path_is_network(const uint8_t *path)
{
    return path[0] == BACKSLASH && path[1] == BACKSLASH;
}

int vertrix_string_append(char *destination, size_t size, const char *source, const char *suffix)
{
    size_t first = 0;
    size_t second = 0;
    size_t position;
    if (!destination || !source || !suffix || size == 0)
    {
        return 0;
    }
    while (source[first] != 0)
    {
        first++;
    }
    while (suffix[second] != 0)
    {
        second++;
    }
    if (first + second + 1 > size)
    {
        return 0;
    }
    for (position = 0; position < first; position++)
    {
        destination[position] = source[position];
    }
    for (position = 0; position < second; position++)
    {
        destination[first + position] = suffix[position];
    }
    destination[first + second] = 0;
    return 1;
}
