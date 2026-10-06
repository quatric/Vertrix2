#include "head_anim.h"

#include <string.h>

enum
{
    IDLE_BASE = 2000,
    IDLE_SPAN = 10000
};

static int line_at(const char *text, size_t size, size_t *position, const char **line,
                   size_t *length)
{
    while (*position < size)
    {
        size_t start = *position;
        size_t end = start;
        while (end < size && text[end] != '\n')
        {
            end++;
        }
        *position = end + 1;
        while (end > start && text[end - 1] == '\r')
        {
            end--;
        }
        if (end > start && text[start] != '/')
        {
            *line = text + start;
            *length = end - start;
            return 1;
        }
    }
    return 0;
}

/* The backslash-terminated fields of a line. */
static uint32_t fields(const char *line, size_t length, const char *field[], size_t size[],
                       uint32_t capacity)
{
    uint32_t count = 0;
    size_t start = 0;
    for (size_t i = 0; i < length && count < capacity; i++)
    {
        if (line[i] == '\\')
        {
            field[count] = line + start;
            size[count++] = i - start;
            start = i + 1;
        }
    }
    return count;
}

static int32_t number(const char *text, size_t length)
{
    int32_t value = 0;
    for (size_t i = 0; i < length && text[i] >= '0' && text[i] <= '9'; i++)
    {
        value = value * 10 + (text[i] - '0');
    }
    return value;
}

static void copy_name(char *target, const char *source, size_t length, int strip_extension)
{
    if (strip_extension)
    {
        for (size_t i = length; i > 0; i--)
        {
            if (source[i - 1] == '.')
            {
                length = i - 1;
                break;
            }
        }
    }
    if (length > 63)
    {
        length = 63;
    }
    memcpy(target, source, length);
    target[length] = 0;
}

uint32_t vertrix_head_parse_rows(const char *text, size_t size, VertrixHeadScript *script,
                                 char names[][64])
{
    size_t position = 0;
    const char *line;
    size_t length;
    uint32_t rows = 0;
    while (rows < VERTRIX_HEAD_ROWS && line_at(text, size, &position, &line, &length))
    {
        const char *field[4];
        size_t field_size[4];
        if (fields(line, length, field, field_size, 4) < 4)
        {
            continue;
        }
        if (names)
        {
            copy_name(names[rows], field[0], field_size[0], 1);
        }
        script->offset_x[rows] = number(field[2], field_size[2]);
        script->offset_y[rows] = number(field[3], field_size[3]);
        rows++;
    }
    script->rows = rows;
    return rows;
}

uint32_t vertrix_head_parse_list(const char *text, size_t size, uint32_t row,
                                 char names[VERTRIX_HEAD_ANIMATIONS][64],
                                 uint8_t types[VERTRIX_HEAD_ANIMATIONS])
{
    size_t position = 0;
    const char *line;
    size_t length;
    uint32_t seen = 0;
    while (line_at(text, size, &position, &line, &length))
    {
        if (seen++ == row)
        {
            const char *field[2 * VERTRIX_HEAD_ANIMATIONS];
            size_t field_size[2 * VERTRIX_HEAD_ANIMATIONS];
            uint32_t count = fields(line, length, field, field_size, 2 * VERTRIX_HEAD_ANIMATIONS);
            uint32_t animations = 0;
            for (uint32_t i = 0; i + 1 < count; i += 2)
            {
                if (!field_size[i])
                {
                    break;
                }
                copy_name(names[animations], field[i], field_size[i], 0);
                types[animations++] = (uint8_t)number(field[i + 1], field_size[i + 1]);
            }
            return animations;
        }
    }
    return 0;
}

uint32_t vertrix_head_parse_animation(const char *text, size_t size, VertrixHeadAnim *animation)
{
    size_t position = 0;
    const char *line;
    size_t length;
    animation->count = 0;
    while (animation->count < VERTRIX_HEAD_STEPS && line_at(text, size, &position, &line, &length))
    {
        const char *field[2];
        size_t field_size[2];
        if (fields(line, length, field, field_size, 2) < 2)
        {
            continue;
        }
        animation->steps[animation->count].frame = (uint16_t)number(field[0], field_size[0]);
        animation->steps[animation->count].delay = (uint16_t)number(field[1], field_size[1]);
        animation->count++;
    }
    return animation->count;
}

static void arm(VertrixHeadScript *script, VertrixHeadRandom random, void *context)
{
    script->wait = IDLE_BASE + random(context, IDLE_SPAN);
    script->counter = 0;
}

void vertrix_head_start(VertrixHeadScript *script, VertrixHeadRandom random, void *context)
{
    script->playing = 0;
    arm(script, random, context);
}

static uint32_t of_type(const VertrixHeadScript *script, uint32_t type)
{
    uint32_t count = 0;
    for (uint32_t i = 0; i < script->animations; i++)
    {
        count += script->animation[i].type == type;
    }
    return count;
}

static uint32_t nth_of_type(const VertrixHeadScript *script, uint32_t type, uint32_t n)
{
    for (uint32_t i = 0; i < script->animations; i++)
    {
        if (script->animation[i].type == type && n-- == 0)
        {
            return i;
        }
    }
    return 0;
}

void vertrix_head_update(VertrixHeadScript *script, uint32_t mood, uint32_t elapsed,
                         VertrixHeadRandom random, void *context)
{
    if (script->playing)
    {
        const VertrixHeadAnim *animation = &script->animation[script->current];
        script->step_time += elapsed;
        while (script->playing && script->step_time >= animation->steps[script->step].delay)
        {
            script->step_time -= animation->steps[script->step].delay;
            if (++script->step >= animation->count)
            {
                script->playing = 0;
            }
        }
    }
    script->counter += elapsed;
    if (script->counter < script->wait)
    {
        return;
    }
    script->counter = 0;
    if (script->playing)
    {
        return;
    }
    uint32_t type = mood;
    uint32_t count = of_type(script, type);
    if (!count)
    {
        type = VERTRIX_HEAD_MOOD_RANDOM;
        count = of_type(script, type);
    }
    if (!count)
    {
        return;
    }
    script->current = nth_of_type(script, type, random(context, (uint16_t)count));
    script->step = 0;
    script->step_time = 0;
    script->playing = script->animation[script->current].count > 0;
    arm(script, random, context);
}

uint32_t vertrix_head_row(const VertrixHeadScript *script)
{
    if (!script->playing)
    {
        return 0;
    }
    return script->animation[script->current].steps[script->step].frame + 1u;
}
