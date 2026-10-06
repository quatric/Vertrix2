#include "bitmap_load.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    PREPARE = 0x48a8a0,
    POSITION = 0x48aad0,
    READ = 0x48a930,
    CREATE = 0x478d10,
    SEEK = 0x48aaf0,
    SKIP = 0x48aa90,
    FINISH = 0x479b50,
    FILE_HEADER = 0x4c,
    FILE_HEADER_SIZE = 0xe,
    FILE_DATA_OFFSET = 0xa,
    INFO_HEADER = 0x78,
    INFO_HEADER_SIZE = 0x2c,
    INFO_SIZE = 0x78,
    INFO_WIDTH = 0x74,
    INFO_HEIGHT = 0x70,
    INFO_PLANES = 0x6c,
    INFO_BITS = 0x6a,
    INFO_COMPRESSION = 0x68,
    EXPECTED_SIZE = 0x28,
    EXPECTED_PLANES = 1,
    EXPECTED_BITS = 0x18,
    CHANNEL_B = 0x1c,
    CHANNEL_G = 0x24,
    CHANNEL_R = 0x18,
    CREATE_EBX = 4,
    ONE = 1,
    PIXEL_BYTES = 4
};

typedef struct Frame
{
    const VertrixFactoryServices *services;
    uint32_t base;
    int ok;
} Frame;

static uint32_t local(Frame *f, uint32_t depth, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!f->services->resolve(f->base, &storage, &size, f->services->context) ||
        !vertrix_actor_storage_read(storage, size, VERTRIX_BITMAP_FRAME_SIZE - depth, width,
                                    &value))
    {
        f->ok = 0;
    }
    return value;
}

int vertrix_bitmap_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t stream, uint32_t edx, uint32_t ebx, uint32_t ecx,
                        uint32_t *result)
{
    Frame f = {services, frame - VERTRIX_BITMAP_FRAME_SIZE, 1};
    uint32_t file_header = frame - FILE_HEADER, info = frame - INFO_HEADER;
    uint32_t position, data_offset, width, height, rows, padding, surface, pixels, out;
    void *surface_storage, *pixel_storage;
    size_t surface_size, pixel_size;
    vertrix_call(calls, PREPARE, stream, edx, ebx, ecx, 0);
    position = vertrix_call(calls, POSITION, stream, file_header, ONE, FILE_HEADER_SIZE, 0);
    vertrix_call(calls, READ, stream, file_header, ONE, FILE_HEADER_SIZE, 0);
    data_offset = local(&f, FILE_HEADER - FILE_DATA_OFFSET, DWORD_WIDTH) + position;
    vertrix_call(calls, READ, stream, info, ONE, INFO_HEADER_SIZE, 0);
    if (!f.ok)
    {
        return 0;
    }
    if (local(&f, INFO_SIZE, DWORD_WIDTH) != EXPECTED_SIZE ||
        (local(&f, INFO_PLANES, WORD_WIDTH) & 0xffff) != EXPECTED_PLANES ||
        (local(&f, INFO_BITS, WORD_WIDTH) & 0xffff) != EXPECTED_BITS ||
        local(&f, INFO_COMPRESSION, DWORD_WIDTH) != 0)
    {
        *result = 0;
        return f.ok;
    }
    width = local(&f, INFO_WIDTH, DWORD_WIDTH);
    height = local(&f, INFO_HEIGHT, DWORD_WIDTH);
    rows = (int32_t)height < 0 ? 0u - height : height;
    surface = vertrix_call(calls, CREATE, width, rows, CREATE_EBX, 0, 0);
    padding = PIXEL_BYTES - ((3 * width) & 3);
    if (padding == PIXEL_BYTES)
    {
        padding = 0;
    }
    if (!services->resolve(surface, &surface_storage, &surface_size, services->context) ||
        !vertrix_actor_storage_read(surface_storage, surface_size, 0, DWORD_WIDTH, &pixels) ||
        !services->resolve(pixels, &pixel_storage, &pixel_size, services->context))
    {
        return 0;
    }
    out = 0;
    vertrix_call(calls, SEEK, stream, data_offset, CREATE_EBX, rows, 0);
    if (rows != 0)
    {
        for (uint32_t row = 0; row < rows; row++)
        {
            for (uint32_t column = 0; column < width; column++)
            {
                uint32_t blue, green, red;
                vertrix_call(calls, READ, stream, frame - CHANNEL_B, ONE, ONE, 0);
                vertrix_call(calls, READ, stream, frame - CHANNEL_G, ONE, ONE, 0);
                vertrix_call(calls, READ, stream, frame - CHANNEL_R, ONE, ONE, 0);
                blue = local(&f, CHANNEL_B, BYTE_WIDTH);
                green = local(&f, CHANNEL_G, BYTE_WIDTH);
                red = local(&f, CHANNEL_R, BYTE_WIDTH);
                if (!f.ok ||
                    !vertrix_actor_storage_write(pixel_storage, pixel_size, out, BYTE_WIDTH,
                                                 blue) ||
                    !vertrix_actor_storage_write(pixel_storage, pixel_size, out + 1, BYTE_WIDTH,
                                                 green) ||
                    !vertrix_actor_storage_write(pixel_storage, pixel_size, out + 2, BYTE_WIDTH,
                                                 red) ||
                    !vertrix_actor_storage_write(pixel_storage, pixel_size, out + 3, BYTE_WIDTH, 0))
                {
                    return 0;
                }
                out += PIXEL_BYTES;
            }
            vertrix_call(calls, SKIP, stream, padding & 0xff, row, width != 0 ? ONE : 0, 0);
        }
        vertrix_call(calls, FINISH, surface, rows, rows, width != 0 ? ONE : 0, 0);
    }
    else
    {
        vertrix_call(calls, FINISH, surface, data_offset, CREATE_EBX, 0, 0);
    }
    *result = surface;
    return f.ok;
}
