#include "rotation_tables.h"
#include <limits.h>

static int32_t table_signed(uint32_t bits)
{
    return bits <= INT32_MAX ? (int32_t)bits : -(int32_t)(UINT32_MAX - bits) - 1;
}

static int read_table(VertrixVf *archive, const char *name, int32_t output[360])
{
    uint32_t index, size;
    unsigned char data[1440];
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, &size) ||
        size != sizeof(data) || !vertrix_vf_read(archive, index, 0, data, sizeof(data)))
    {
        return 0;
    }
    for (unsigned i = 0; i < 360; ++i)
    {
        const unsigned char *p = data + i * 4;
        uint32_t value = (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
                         ((uint32_t)p[3] << 24);
        output[i] = table_signed(value);
    }
    return 1;
}

int vertrix_rotation_tables_load(VertrixVf *archive, VertrixRotationTables *tables)
{
    if (!archive || !tables || tables->ready)
    {
        return 0;
    }
    VertrixRotationTables next = {0};
    if (!read_table(archive, "table/Sin.tab", next.sine) ||
        !read_table(archive, "table/Cos.tab", next.cosine))
    {
        return 0;
    }
    next.ready = 1;
    *tables = next;
    return 1;
}

static int32_t coordinate(int32_t coefficient, int32_t radius)
{
    int32_t shifted = table_signed((uint32_t)radius << 16);
    int64_t product = (int64_t)coefficient * shifted;
    uint32_t word = (uint16_t)((uint64_t)product >> 32);
    return word < 32768 ? (int32_t)word : (int32_t)word - 65536;
}

int vertrix_rotation_coordinates(const VertrixRotationTables *tables, int16_t angle,
                                 int32_t radius_x, int32_t radius_y, int32_t *x, int32_t *y)
{
    if (!tables || !tables->ready || angle < 0 || angle >= 360 || !x || !y)
    {
        return 0;
    }
    int32_t next_x = coordinate(tables->cosine[angle], radius_x);
    int32_t next_y = coordinate(tables->sine[angle], radius_y);
    *x = next_x;
    *y = next_y;
    return 1;
}
