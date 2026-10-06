#include "actor_storage.h"

typedef struct
{
    uint16_t offset;
    uint8_t width;
    uint32_t value;
} ActorDefault;

/* Original4abd70..4ac121: instruction-order immediate writes. */
static const ActorDefault defaults[] = {
    {0x158, 4, UINT32_C(0x517af4)},   {0x0, 4, UINT32_C(0x0)},   {0x4, 4, UINT32_C(0x0)},
    {0x8, 2, UINT32_C(0x0)},          {0xa, 2, UINT32_C(0x0)},   {0xc, 2, UINT32_C(0x0)},
    {0xe, 2, UINT32_C(0x0)},          {0x16, 2, UINT32_C(0x0)},  {0x1e, 2, UINT32_C(0x0)},
    {0x10, 2, UINT32_C(0x0)},         {0x18, 2, UINT32_C(0x0)},  {0x20, 2, UINT32_C(0x0)},
    {0x14, 2, UINT32_C(0x0)},         {0x1c, 2, UINT32_C(0x0)},  {0x12, 2, UINT32_C(0x0)},
    {0x1a, 2, UINT32_C(0x0)},         {0x22, 2, UINT32_C(0x0)},  {0x24, 2, UINT32_C(0x0)},
    {0x26, 2, UINT32_C(0x0)},         {0x28, 2, UINT32_C(0x0)},  {0x2a, 2, UINT32_C(0x0)},
    {0x2c, 2, UINT32_C(0x0)},         {0x2e, 2, UINT32_C(0x0)},  {0x30, 2, UINT32_C(0x0)},
    {0x32, 2, UINT32_C(0x0)},         {0x34, 2, UINT32_C(0x0)},  {0x36, 2, UINT32_C(0x0)},
    {0x38, 2, UINT32_C(0x0)},         {0x3a, 2, UINT32_C(0x0)},  {0x3c, 2, UINT32_C(0x0)},
    {0x3e, 2, UINT32_C(0x0)},         {0x40, 2, UINT32_C(0x0)},  {0x42, 2, UINT32_C(0x0)},
    {0x44, 1, UINT32_C(0x10)},        {0x45, 1, UINT32_C(0x10)}, {0x46, 2, UINT32_C(0x0)},
    {0x48, 2, UINT32_C(0x0)},         {0x4a, 2, UINT32_C(0x0)},  {0x4c, 2, UINT32_C(0x0)},
    {0x4e, 1, UINT32_C(0x32)},        {0x4f, 1, UINT32_C(0x32)}, {0x50, 2, UINT32_C(0x0)},
    {0x52, 1, UINT32_C(0xd)},         {0x53, 1, UINT32_C(0xd)},  {0x54, 2, UINT32_C(0x0)},
    {0x80, 4, UINT32_C(0x0)},         {0x84, 4, UINT32_C(0x0)},  {0x88, 4, UINT32_C(0x0)},
    {0x8c, 1, UINT32_C(0x0)},         {0x8d, 1, UINT32_C(0x0)},  {0x8e, 1, UINT32_C(0x1)},
    {0x90, 1, UINT32_C(0x0)},         {0x91, 1, UINT32_C(0x0)},  {0x92, 1, UINT32_C(0x0)},
    {0x93, 1, UINT32_C(0x0)},         {0x8f, 1, UINT32_C(0x0)},  {0x94, 1, UINT32_C(0x2)},
    {0x95, 1, UINT32_C(0x1)},         {0x98, 4, UINT32_C(0x0)},  {0x9c, 4, UINT32_C(0x0)},
    {0xa0, 4, UINT32_C(0x0)},         {0xa4, 4, UINT32_C(0x0)},  {0xa8, 2, UINT32_C(0x0)},
    {0xaa, 2, UINT32_C(0x0)},         {0xac, 2, UINT32_C(0x0)},  {0xae, 2, UINT32_C(0x0)},
    {0xb0, 4, UINT32_C(0x0)},         {0xb4, 4, UINT32_C(0x0)},  {0xb8, 4, UINT32_C(0x0)},
    {0xbc, 4, UINT32_C(0x0)},         {0xc0, 4, UINT32_C(0x0)},  {0xc4, 4, UINT32_C(0x0)},
    {0xc8, 4, UINT32_C(0x0)},         {0xcc, 4, UINT32_C(0x0)},  {0xd0, 4, UINT32_C(0x0)},
    {0xd4, 4, UINT32_C(0x0)},         {0xd8, 4, UINT32_C(0x0)},  {0xdc, 4, UINT32_C(0x0)},
    {0xe0, 4, UINT32_C(0x0)},         {0xe4, 4, UINT32_C(0x0)},  {0xe8, 4, UINT32_C(0x0)},
    {0xec, 4, UINT32_C(0x0)},         {0x154, 4, UINT32_C(0x0)}, {0xf0, 4, UINT32_C(0x0)},
    {0xf4, 4, UINT32_C(0x0)},         {0xf8, 4, UINT32_C(0x0)},  {0xfc, 1, UINT32_C(0x0)},
    {0xfd, 1, UINT32_C(0x0)},         {0xfe, 2, UINT32_C(0x0)},  {0x100, 2, UINT32_C(0x0)},
    {0x104, 4, UINT32_C(0x0)},        {0x108, 4, UINT32_C(0x0)}, {0x10c, 4, UINT32_C(0x0)},
    {0x110, 1, UINT32_C(0x0)},        {0x114, 4, UINT32_C(0x0)}, {0x118, 4, UINT32_C(0xffffff)},
    {0x11c, 4, UINT32_C(0xff000000)}, {0x58, 4, UINT32_C(0x0)},  {0x5c, 4, UINT32_C(0x0)},
    {0x60, 4, UINT32_C(0x0)},         {0x64, 4, UINT32_C(0x0)},  {0x68, 4, UINT32_C(0x0)},
    {0x6c, 4, UINT32_C(0x0)},         {0x70, 4, UINT32_C(0x0)},  {0x74, 4, UINT32_C(0x0)},
    {0x78, 4, UINT32_C(0x0)},         {0x7c, 4, UINT32_C(0x0)},  {0x120, 4, UINT32_C(0x1)},
    {0x124, 4, UINT32_C(0x0)},        {0x138, 4, UINT32_C(0x1)}, {0x128, 2, UINT32_C(0x0)},
    {0x12a, 2, UINT32_C(0x0)},        {0x12c, 4, UINT32_C(0x0)}, {0x130, 4, UINT32_C(0x0)},
    {0x13c, 4, UINT32_C(0x1)},        {0x140, 4, UINT32_C(0x0)}, {0x144, 4, UINT32_C(0x1)},
    {0x14c, 4, UINT32_C(0x0)},        {0x134, 4, UINT32_C(0x1)}, {0x150, 4, UINT32_C(0x0)},
    {0x148, 2, UINT32_C(0xffff)},
};

static int field_valid(const void *storage, size_t size, size_t offset, unsigned width)
{
    return storage && (width == 1 || width == 2 || width == 4) && offset <= size &&
           width <= size - offset;
}

int vertrix_actor_storage_read(const void *storage, size_t size, size_t offset, unsigned width,
                               uint32_t *value)
{
    if (!value || !field_valid(storage, size, offset, width))
    {
        return 0;
    }
    const uint8_t *bytes = storage;
    uint32_t result = 0;
    for (unsigned i = 0; i < width; i++)
    {
        result |= (uint32_t)bytes[offset + i] << (8 * i);
    }
    *value = result;
    return 1;
}

int vertrix_actor_storage_write(void *storage, size_t size, size_t offset, unsigned width,
                                uint32_t value)
{
    if (!field_valid(storage, size, offset, width))
    {
        return 0;
    }
    uint8_t *bytes = storage;
    for (unsigned i = 0; i < width; i++)
    {
        bytes[offset + i] = (uint8_t)(value >> (8 * i));
    }
    return 1;
}

int vertrix_actor_storage_construct(void *storage, size_t size)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof(defaults) / sizeof(defaults[0]); i++)
    {
        vertrix_actor_storage_write(storage, size, defaults[i].offset, defaults[i].width,
                                    defaults[i].value);
    }
    return 1;
}
