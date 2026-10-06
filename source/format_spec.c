#include "format_spec.h"

#include "actor_storage.h"
#include "rtl_glue.h"

enum
{
    DWORD_WIDTH = 4,
    BYTE_WIDTH = 1,
    FIELD_WIDTH = 4,
    FIELD_PRECISION = 8,
    FIELD_PAD = 0x16,
    FIELD_FLAGS = 0x1e,
    FIELD_FLAGS_HIGH = 0x1f,
    FLAG_LEFT = 8,
    FLAG_SHORT = 0x10,
    FLAG_LONG = 0x20,
    FLAG_NEAR = 0x40,
    FLAG_FAR = 0x80,
    FLAG_INT64 = 1,
    NO_PRECISION = 0xffffffffu
};

typedef struct Spec
{
    const VertrixFactoryServices *services;
    uint32_t argument_base;
    int ok;
} Spec;

static uint32_t get(Spec *s, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!s->services->resolve(handle, &storage, &size, s->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        s->ok = 0;
    }
    return value;
}

static void put(Spec *s, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!s->services->resolve(handle, &storage, &size, s->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        s->ok = 0;
    }
}

static uint32_t next_argument(Spec *s, uint32_t cell)
{
    uint32_t pointer = get(s, cell, 0, DWORD_WIDTH);
    if (s->argument_base == 0)
    {
        s->argument_base = pointer;
    }
    put(s, cell, 0, DWORD_WIDTH, pointer + DWORD_WIDTH);
    return get(s, s->argument_base, pointer - s->argument_base, DWORD_WIDTH);
}

static void set_flag(Spec *s, uint32_t spec, uint32_t offset, uint32_t flag)
{
    put(s, spec, offset, BYTE_WIDTH, get(s, spec, offset, BYTE_WIDTH) | flag);
}

/* 0x4df81c: the flag characters, through the recovered vertrix_rtl_parse_format_flags. */
static uint32_t parse_flags(Spec *s, uint32_t text, uint32_t spec)
{
    void *text_storage, *spec_storage;
    size_t text_size, spec_size;
    if (!s->services->resolve(text, &text_storage, &text_size, s->services->context) ||
        !s->services->resolve(spec, &spec_storage, &spec_size, s->services->context))
    {
        s->ok = 0;
        return 0;
    }
    return vertrix_rtl_parse_format_flags(text_storage, text, spec_storage, spec_size) - text;
}

int vertrix_format_spec(const VertrixFactoryServices *services, uint32_t text,
                        uint32_t argument_cell, uint32_t spec, uint32_t *result)
{
    Spec state = {services, 0, 1};
    Spec *s = &state;
    uint32_t i, c;
    put(s, spec, FIELD_PAD, BYTE_WIDTH, ' ');
    i = parse_flags(s, text, spec);
    put(s, spec, FIELD_WIDTH, DWORD_WIDTH, 0);
    if (get(s, text, i, BYTE_WIDTH) == '*')
    {
        uint32_t width = next_argument(s, argument_cell);
        put(s, spec, FIELD_WIDTH, DWORD_WIDTH, width);
        if ((int32_t)width < 0)
        {
            put(s, spec, FIELD_WIDTH, DWORD_WIDTH, 0u - width);
            set_flag(s, spec, FIELD_FLAGS, FLAG_LEFT);
        }
        i++;
    }
    else
    {
        while (s->ok && (c = get(s, text, i, BYTE_WIDTH)) >= '0' && c <= '9')
        {
            put(s, spec, FIELD_WIDTH, DWORD_WIDTH,
                get(s, spec, FIELD_WIDTH, DWORD_WIDTH) * 10 + (c - '0'));
            i++;
        }
    }
    put(s, spec, FIELD_PRECISION, DWORD_WIDTH, NO_PRECISION);
    if (get(s, text, i, BYTE_WIDTH) == '.')
    {
        uint32_t next = get(s, text, i + 1, BYTE_WIDTH);
        put(s, spec, FIELD_PRECISION, DWORD_WIDTH, 0);
        i++;
        if (next == '*')
        {
            uint32_t precision = next_argument(s, argument_cell);
            put(s, spec, FIELD_PRECISION, DWORD_WIDTH, precision);
            if ((int32_t)precision < 0)
            {
                put(s, spec, FIELD_PRECISION, DWORD_WIDTH, NO_PRECISION);
            }
            i++;
        }
        else
        {
            while (s->ok && (c = get(s, text, i, BYTE_WIDTH)) >= '0' && c <= '9')
            {
                put(s, spec, FIELD_PRECISION, DWORD_WIDTH,
                    get(s, spec, FIELD_PRECISION, DWORD_WIDTH) * 10 + (c - '0'));
                i++;
            }
        }
        if (get(s, spec, FIELD_PRECISION, DWORD_WIDTH) != NO_PRECISION)
        {
            put(s, spec, FIELD_PAD, BYTE_WIDTH, ' ');
        }
    }
    c = get(s, text, i, BYTE_WIDTH);
    if (c == 'F')
    {
        set_flag(s, spec, FIELD_FLAGS, FLAG_FAR);
        i++;
    }
    else if (c == 'N')
    {
        set_flag(s, spec, FIELD_FLAGS, FLAG_NEAR);
        i++;
    }
    else if (c == 'h')
    {
        set_flag(s, spec, FIELD_FLAGS, FLAG_SHORT);
        i++;
    }
    else if (c == 'l' || c == 'w')
    {
        set_flag(s, spec, FIELD_FLAGS, FLAG_LONG);
        i++;
    }
    else if (c == 'L')
    {
        set_flag(s, spec, FIELD_FLAGS_HIGH, FLAG_INT64);
        i++;
    }
    else if (c == 'I' && get(s, text, i + 1, BYTE_WIDTH) == '6' &&
             get(s, text, i + 2, BYTE_WIDTH) == '4')
    {
        set_flag(s, spec, FIELD_FLAGS_HIGH, FLAG_INT64);
        i += 3;
    }
    *result = text + i;
    return s->ok;
}
