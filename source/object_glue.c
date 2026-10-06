#include "object_glue.h"
#include "actor_gate.h"
#include "actor_storage.h"
#include "engine_helpers.h"
#include "table_queries.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    VIRTUAL_SIDE = 0x468,
    VIRTUAL_SLOT = 0x18,
    CALLBACK_SLOT = 0xbc,
    OBJECT_FIELD_8 = 8,
    OBJECT_STATE = 0x474,
    GLYPH_UNALIGNED = 0x15d,
    GLYPH_SHIFT = 24,
    VERTRIX_CHAIN_CELLS = 0x544f90
};

static int get(const void *storage, size_t size, size_t offset, unsigned width, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, offset, width, value);
}

static int16_t signed_word(uint32_t bits)
{
    return (int16_t)(uint16_t)bits;
}

static int parent_dword(const VertrixFactoryServices *services, const void *storage, size_t size,
                        size_t field, uint32_t *handle, uint32_t *value)
{
    void *parent;
    size_t parent_size;
    if (!get(storage, size, VERTRIX_OBJECT_PARENT, DWORD_WIDTH, handle))
    {
        return 0;
    }
    if (!services->resolve(*handle, &parent, &parent_size, services->context))
    {
        return 0;
    }
    return get(parent, parent_size, field, DWORD_WIDTH, value);
}

uint32_t vertrix_object_set_mode(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, void *storage, size_t size, uint32_t value)
{
    uint32_t handle;
    uint32_t list;
    if (!vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_MODE, DWORD_WIDTH, value))
    {
        return 0;
    }
    if (value != 1)
    {
        return object;
    }
    if (!parent_dword(services, storage, size, VERTRIX_OBJECT_PARENT_LIST, &handle, &list))
    {
        return 0;
    }
    return vertrix_call(calls, 0x4ca370, object + VERTRIX_OBJECT_HEAD, list, 0, 0, 0);
}

uint32_t vertrix_object_parent_append(const VertrixCalls *calls, uint32_t object,
                                      const void *storage, size_t size, size_t field)
{
    uint32_t handle;
    uint32_t value;
    (void)object;
    if (!get(storage, size, field, DWORD_WIDTH, &value) ||
        !get(storage, size, VERTRIX_OBJECT_PARENT, DWORD_WIDTH, &handle))
    {
        return 0;
    }
    return vertrix_call(calls, 0x4ca370, handle + VERTRIX_OBJECT_PARENT_LIST, value, 0, 0, 0);
}

uint32_t vertrix_object_start_5182c4(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx)
{
    uint32_t object = vertrix_call(calls, 0x4abd70, eax, edx, 0, 0, 0);
    void *storage;
    size_t size;
    if (!services->resolve(object, &storage, &size, services->context))
    {
        return 0;
    }
    if (!vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_TABLE_FIELD, DWORD_WIDTH,
                                     VERTRIX_OBJECT_TABLE_5182C4) ||
        !vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_WORD_15C, WORD_WIDTH, 0) ||
        !vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_PARENT, DWORD_WIDTH, 0))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_contains(const void *storage, size_t size, int16_t x, int16_t y,
                                 uint32_t *hit)
{
    uint32_t left;
    uint32_t right;
    uint32_t top;
    uint32_t bottom;
    if (!get(storage, size, VERTRIX_OBJECT_BOX_LEFT, WORD_WIDTH, &left) ||
        !get(storage, size, VERTRIX_OBJECT_BOX_RIGHT, WORD_WIDTH, &right) ||
        !get(storage, size, VERTRIX_OBJECT_BOX_TOP, WORD_WIDTH, &top) ||
        !get(storage, size, VERTRIX_OBJECT_BOX_BOTTOM, WORD_WIDTH, &bottom))
    {
        return 0;
    }
    uint32_t inside = x >= signed_word(left) && y >= signed_word(top) && x <= signed_word(right) &&
                      y <= signed_word(bottom);
    *hit = inside;
    return inside;
}

static int glyph(const void *storage, size_t size, uint32_t *value)
{
    uint32_t dword;
    if (!get(storage, size, GLYPH_UNALIGNED, DWORD_WIDTH, &dword))
    {
        return 0;
    }
    *value = (uint32_t)((int32_t)dword >> GLYPH_SHIFT);
    return 1;
}

uint32_t vertrix_object_glyph_layout(const VertrixCalls *calls, const void *storage, size_t size,
                                     uint32_t edx, uint32_t caller_ebx)
{
    uint32_t style;
    uint32_t value;
    if (!glyph(storage, size, &value) ||
        !get(storage, size, VERTRIX_OBJECT_STYLE_BYTE, BYTE_WIDTH, &style))
    {
        return 0;
    }
    return vertrix_call(calls, 0x440610, value, 0x5110b8, style, edx, caller_ebx);
}

uint32_t vertrix_object_glyph_present(const VertrixCalls *calls, const void *storage, size_t size,
                                      uint32_t edx)
{
    uint32_t value;
    if (!glyph(storage, size, &value))
    {
        return 0;
    }
    return vertrix_call(calls, 0x43f460, value, edx & 0xff, 0, 0, 0);
}

uint32_t vertrix_object_release_call(const VertrixCalls *calls, uint32_t object,
                                     const void *storage, size_t size, uint32_t edx)
{
    uint32_t field;
    if (!get(storage, size, OBJECT_FIELD_8, DWORD_WIDTH, &field))
    {
        return 0;
    }
    vertrix_call(calls, 0x4d88a0, object, field, edx, 1, 0);
    return 0;
}

uint32_t vertrix_object_table_store(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, const void *storage,
                                    size_t size, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t table;
    void *table_storage;
    size_t table_size;
    uint32_t target;
    void *target_storage;
    size_t target_size;
    table = services->allocate(0x10, services->context);
    if (table == 0)
    {
        return 0;
    }
    if (!services->resolve(table, &table_storage, &table_size, services->context) ||
        !vertrix_actor_storage_write(table_storage, table_size, 0, 4, edx) ||
        !vertrix_actor_storage_write(table_storage, table_size, 4, 4, ebx) ||
        !vertrix_actor_storage_write(table_storage, table_size, 8, 4, ecx) ||
        !get(storage, size, VIRTUAL_SIDE, DWORD_WIDTH, &target) ||
        !services->resolve(target, &target_storage, &target_size, services->context))
    {
        return 0;
    }
    return vertrix_object_release_call(calls, target, target_storage, target_size, table);
}
static uint32_t chain_select_run(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 void *storage, size_t size, uint32_t chain, uint32_t fallback,
                                 const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                 int store_empty)
{
    uint32_t rows;
    uint32_t row;
    uint32_t address;
    rows = vertrix_table_column_count(grid, counts, column, chain);
    if (rows == 0)
    {
        if (!store_empty)
        {
            return 0;
        }
        return vertrix_object_table_store(calls, services, storage, size, 0, fallback, 0);
    }
    row = vertrix_table_column_nth(grid, counts, column, chain, 0);
    address = VERTRIX_CHAIN_CELLS + 0x118 * column + 0x1c * row;
    return vertrix_object_table_store(calls, services, storage, size, address, fallback, 0);
}

uint32_t vertrix_object_chain_select(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, VertrixMemoryRead read,
                                     void *read_context, void *storage, size_t size,
                                     uint32_t global_default, const uint32_t *state_defaults,
                                     const uint32_t *grid, const uint32_t *counts, uint32_t column,
                                     uint32_t state, uint32_t ebx, uint32_t ecx)
{
    uint32_t chain;
    uint32_t fallback;
    int store_empty;
    if (!vertrix_actor_storage_write(storage, size, OBJECT_STATE, DWORD_WIDTH, 1))
    {
        return 0;
    }
    vertrix_object_virtual_slot6(calls, read, read_context, storage, size, ebx, ecx);
    if (state != 1)
    {
        chain = 5;
        fallback = global_default;
        store_empty = 0;
        if (!vertrix_actor_storage_write(storage, size, OBJECT_STATE, DWORD_WIDTH, 1))
        {
            return 0;
        }
    }
    else
    {
        chain = 1;
        fallback = state_defaults[column];
        store_empty = 1;
        if (!vertrix_actor_storage_write(storage, size, OBJECT_STATE, DWORD_WIDTH, 0))
        {
            return 0;
        }
    }
    return chain_select_run(calls, services, storage, size, chain, fallback, grid, counts, column,
                            store_empty);
}

uint32_t vertrix_object_chain_select_pair(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          VertrixMemoryRead read, void *read_context, void *storage,
                                          size_t size, const uint32_t *pair_defaults,
                                          const uint32_t *grid, const uint32_t *counts,
                                          uint32_t column, uint32_t ebx, uint32_t ecx)
{
    vertrix_object_virtual_slot6(calls, read, read_context, storage, size, ebx, ecx);
    return chain_select_run(calls, services, storage, size, 2, pair_defaults[column], grid, counts,
                            column, 1);
}

uint32_t vertrix_object_match_append(const VertrixCalls *calls, uint32_t object,
                                     const void *storage, size_t size, const void *other,
                                     size_t other_size)
{
    uint32_t mine;
    uint32_t theirs;
    if (!get(other, other_size, VERTRIX_OBJECT_COMPARE_VALUE, DWORD_WIDTH, &theirs) ||
        !get(storage, size, VERTRIX_OBJECT_COMPARE_FIELD, DWORD_WIDTH, &mine) || mine != theirs)
    {
        return 0;
    }
    vertrix_call(calls, 0x4ca370, object + VERTRIX_OBJECT_COMPARE_LIST,
                 VERTRIX_OBJECT_COMPARE_TABLE, 0, 0, 0);
    return 0;
}

uint32_t vertrix_object_chain_at(const VertrixFactoryServices *services, const void *storage,
                                 size_t size, uint32_t index)
{
    uint32_t handle;
    if (!get(storage, size, VERTRIX_OBJECT_CHAIN_HEAD, DWORD_WIDTH, &handle))
    {
        return 0;
    }
    for (uint32_t position = 0; handle != 0; ++position)
    {
        void *node;
        size_t node_size;
        if (position == index)
        {
            return handle;
        }
        if (!services->resolve(handle, &node, &node_size, services->context) ||
            !get(node, node_size, VERTRIX_OBJECT_CHAIN_NEXT, DWORD_WIDTH, &handle))
        {
            return 0;
        }
    }
    return 0;
}

uint32_t vertrix_object_alloc_pair(const VertrixCalls *calls, uint32_t object, void *storage,
                                   size_t size)
{
    uint32_t result = vertrix_call(calls, 0x4ec160, 0x1001, 2, 0, object, 0);
    if (!vertrix_actor_storage_write(storage, size, 4, BYTE_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, 0, DWORD_WIDTH, result))
    {
        return 0;
    }
    return result;
}

uint32_t vertrix_object_record_new(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t eax,
                                   uint32_t edx, uint32_t ebx, uint8_t global_byte)
{
    void *storage;
    size_t size;
    uint32_t result = vertrix_call(calls, 0x4ec160, 1, 0x1c, ebx, eax, 0);
    if (!services->resolve(result, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, 0, DWORD_WIDTH, eax) ||
        !vertrix_actor_storage_write(storage, size, 4, DWORD_WIDTH, edx) ||
        !vertrix_actor_storage_write(storage, size, OBJECT_FIELD_8, DWORD_WIDTH, ebx) ||
        !vertrix_actor_storage_write(storage, size, 0xc, BYTE_WIDTH, global_byte))
    {
        return 0;
    }
    return result;
}

uint32_t vertrix_object_alloc_arrays(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t count)
{
    static const size_t fields[3] = {OBJECT_FIELD_8, 0xc, 0x10};
    uint32_t result = 0;
    if (!vertrix_actor_storage_write(storage, size, 4, DWORD_WIDTH, count))
    {
        return 0;
    }
    for (int i = 0; i < 3; ++i)
    {
        result = vertrix_call(calls, 0x4ec160, count, 4, 0, object, 0);
        if (i == 2 && !vertrix_actor_storage_write(storage, size, 0x14, DWORD_WIDTH, 1))
        {
            return 0;
        }
        if (!vertrix_actor_storage_write(storage, size, fields[i], DWORD_WIDTH, result))
        {
            return 0;
        }
    }
    return result;
}

uint32_t vertrix_object_surface_format(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       const void *storage, size_t size)
{
    uint32_t height;
    uint32_t width;
    uint32_t flag;
    uint32_t format;
    uint32_t surface;
    void *surface_storage;
    size_t surface_size;
    if (!get(storage, size, 0x10, BYTE_WIDTH, &flag) ||
        !get(storage, size, 0x40, WORD_WIDTH, &height) ||
        !get(storage, size, 0x3e, WORD_WIDTH, &width) ||
        !get(storage, size, 0x24, BYTE_WIDTH, &format))
    {
        return 0;
    }
    surface = vertrix_call(calls, 0x478d10, width, height, flag, object, 0);
    if (!services->resolve(surface, &surface_storage, &surface_size, services->context) ||
        !vertrix_actor_storage_write(surface_storage, surface_size, 0xd, BYTE_WIDTH, format))
    {
        return 0;
    }
    return surface;
}

uint32_t vertrix_object_delegate(const VertrixCalls *calls, uint32_t object, uint32_t edx,
                                 uint32_t ebx, const void *storage, size_t size)
{
    uint32_t field;
    if (!get(storage, size, VERTRIX_OBJECT_COMPARE_FIELD, DWORD_WIDTH, &field) || field == 0)
    {
        return 0;
    }
    return vertrix_call(calls, 0x47fa40, object, edx, field, ebx, 0);
}

uint32_t vertrix_object_notify_field(const VertrixCalls *calls, uint32_t object,
                                     const void *storage, size_t size, uint32_t offset)
{
    return vertrix_object_delegate(calls, object, object + offset, 1, storage, size);
}

static int object_enabled(const void *storage, size_t size, uint32_t *enabled)
{
    return get(storage, size, VERTRIX_OBJECT_ENABLED, DWORD_WIDTH, enabled);
}

uint32_t vertrix_object_notify_global(const VertrixCalls *calls, uint32_t object, void *storage,
                                      size_t size, uint32_t global)
{
    uint32_t enabled;
    if (!object_enabled(storage, size, &enabled) || enabled != 1 ||
        !vertrix_actor_storage_write(storage, size, 0x1d4, DWORD_WIDTH, global))
    {
        return 0;
    }
    return vertrix_object_delegate(calls, object, object + 0x1d0, OBJECT_FIELD_8, storage, size);
}

uint32_t vertrix_object_notify_choice(const VertrixCalls *calls, uint32_t object, void *storage,
                                      size_t size, uint8_t enabled_value, uint8_t disabled_value)
{
    uint32_t enabled;
    if (!object_enabled(storage, size, &enabled) ||
        !vertrix_actor_storage_write(storage, size, 0x1e1, BYTE_WIDTH,
                                     enabled == 1 ? enabled_value : disabled_value))
    {
        return 0;
    }
    return vertrix_object_delegate(calls, object, object + 0x1e0, 2, storage, size);
}

uint32_t vertrix_object_notify_byte(const VertrixCalls *calls, uint32_t object, void *storage,
                                    size_t size, uint8_t value)
{
    uint32_t enabled;
    if (!vertrix_actor_storage_write(storage, size, 0x1e3, BYTE_WIDTH, value) ||
        !object_enabled(storage, size, &enabled) || enabled != 1)
    {
        return 0;
    }
    return vertrix_object_delegate(calls, object, object + 0x1e2, 2, storage, size);
}

uint32_t vertrix_object_parent_glyph(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, const void *storage,
                                     size_t size, uint32_t edx)
{
    uint32_t handle;
    void *parent;
    size_t parent_size;
    if (!get(storage, size, VERTRIX_OBJECT_PARENT, DWORD_WIDTH, &handle) ||
        !services->resolve(handle, &parent, &parent_size, services->context))
    {
        return 0;
    }
    return vertrix_object_glyph_present(calls, parent, parent_size, edx);
}

uint32_t vertrix_object_table_new(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t eax, uint32_t edx, uint32_t table)
{
    void *storage;
    size_t size;
    uint32_t object = vertrix_call(calls, 0x4d8650, eax, edx, 0, 0, 0);
    if (!services->resolve(object, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, 0, DWORD_WIDTH, table))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_first_field8(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx)
{
    void *storage;
    size_t size;
    uint32_t value;
    uint32_t object = vertrix_call(calls, 0x4b79c0, eax, edx, 0, 0, 0);
    if (object == 0)
    {
        return 0;
    }
    if (!services->resolve(object, &storage, &size, services->context) ||
        !get(storage, size, OBJECT_FIELD_8, DWORD_WIDTH, &value))
    {
        return 0;
    }
    return value;
}

int vertrix_object_text_length(const VertrixFactoryServices *services, const void *storage,
                               size_t size, uint32_t *length)
{
    uint32_t handle;
    uint32_t pointer;
    void *text;
    size_t text_size;
    if (!parent_dword(services, storage, size, VERTRIX_OBJECT_PARENT_LIST, &handle, &pointer) ||
        !services->resolve(pointer, &text, &text_size, services->context))
    {
        return 0;
    }
    for (size_t i = 0; i < text_size; ++i)
    {
        if (((const uint8_t *)text)[i] == 0)
        {
            *length = (uint32_t)i;
            return 1;
        }
    }
    return 0;
}

uint32_t vertrix_object_text_length_matches(const VertrixFactoryServices *services,
                                            const void *storage, size_t size)
{
    uint32_t length;
    uint32_t expected;
    if (!vertrix_object_text_length(services, storage, size, &length) ||
        !get(storage, size, VERTRIX_OBJECT_TEXT_LENGTH, DWORD_WIDTH, &expected))
    {
        return 0;
    }
    return length - 1 == expected;
}

uint32_t vertrix_object_clamp_text_length(const VertrixFactoryServices *services, void *storage,
                                          size_t size)
{
    uint32_t length;
    uint32_t current;
    if (!vertrix_object_text_length(services, storage, size, &length) ||
        !get(storage, size, VERTRIX_OBJECT_TEXT_LENGTH, DWORD_WIDTH, &current))
    {
        return 0;
    }
    if ((int32_t)current < -1)
    {
        vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_TEXT_LENGTH, DWORD_WIDTH,
                                    UINT32_MAX);
    }
    else if ((int32_t)length <= (int32_t)current)
    {
        vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_TEXT_LENGTH, DWORD_WIDTH,
                                    length - 1);
    }
    return 0;
}

int vertrix_object_init_4c3fa0(void *storage, size_t size)
{
    static const struct
    {
        uint8_t offset;
        uint32_t value;
    } fields[] = {{0x00, 0x4c3e40}, {0x04, 0x4c3ea0}, {0x08, 0x4c3e60}, {0x0c, 0x4c3ed0},
                  {0x10, 0x4c3f80}, {0x68, 0},        {0x6c, 0},        {0x14, 0},
                  {0x70, 0x4ffdbc}, {0x74, 0x7b},     {0x78, 0},        {0x7c, 0},
                  {0x80, 0}};
    for (size_t i = 0; i < sizeof fields / sizeof fields[0]; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, fields[i].offset, DWORD_WIDTH,
                                         fields[i].value))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_object_reset_block(void *storage, size_t size, const uint8_t *source)
{
    if (!vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_CHAIN_HEAD, DWORD_WIDTH, 0))
    {
        return 0;
    }
    for (size_t i = 0; i < 16; i += DWORD_WIDTH)
    {
        uint32_t word = (uint32_t)source[i] | (uint32_t)source[i + 1] << 8 |
                        (uint32_t)source[i + 2] << 16 | (uint32_t)source[i + 3] << 24;
        if (!vertrix_actor_storage_write(storage, size, VERTRIX_OBJECT_BLOCK_COPY + i, DWORD_WIDTH,
                                         word))
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_object_chain_member(const VertrixCalls *calls, uint32_t eax, uint32_t edx)
{
    uint32_t entry = vertrix_call(calls, 0x47f190, eax, edx, 0, 0, 0);
    return entry == 0 ? 0 : entry + 0x50;
}

uint32_t vertrix_object_list_init(const VertrixCalls *calls, uint32_t object, void *storage,
                                  size_t size, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    static const uint8_t cleared[] = {0x44, 0x40, 0x3c, 0x48, 0x4c, 0x50, 0x54};
    vertrix_call(calls, 0x475af0, object, edx, ebx, ecx, 0);
    for (size_t i = 0; i < sizeof cleared; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, cleared[i], DWORD_WIDTH, 0))
        {
            return 0;
        }
    }
    vertrix_call(calls, 0x475790, object + 4, 0, 0, 0, 0);
    return vertrix_call(calls, 0x4759e0, object, 0, 0, 0, 0);
}

uint32_t vertrix_slot_select(const VertrixCalls *calls, uint32_t table, const void *storage,
                             size_t size, uint32_t index, uint32_t *selected)
{
    uint32_t offset = (index & 0xffff) * 0x60;
    uint32_t first;
    uint32_t slot = table + offset;
    *selected = slot;
    if (!get(storage, size, offset, BYTE_WIDTH, &first))
    {
        return 0;
    }
    if (first != 1)
    {
        return slot;
    }
    return vertrix_call(calls, 0x475790, slot + 4, 0, 0, 0, 0);
}

uint32_t vertrix_literal_copy_call(const VertrixCalls *calls, uint32_t eax, uint8_t *buffer,
                                   size_t buffer_size, const uint8_t *text, size_t text_size)
{
    size_t i = 0;
    do
    {
        if (i >= buffer_size || i >= text_size)
        {
            return 0;
        }
        buffer[i] = text[i];
    } while (text[i++] != 0);
    return vertrix_call(calls, 0x40a860, eax, 0x558970, 0x64, eax, 0);
}

enum
{
    STEP_STATE = 0x64,
    STEP_BACK = 0xfffffff6
};

uint32_t vertrix_object_step_toggle(const VertrixCalls *calls, uint32_t object, void *storage,
                                    size_t size, uint32_t edx, uint32_t ebx)
{
    uint32_t state, step, first, second, result;
    uint32_t stack = 1;
    if (edx == 0)
    {
        return object;
    }
    if (!get(storage, size, STEP_STATE, DWORD_WIDTH, &state))
    {
        return 0;
    }
    step = state == 1 ? 0 : STEP_BACK;
    first = (uint32_t)(int32_t)signed_word(
        vertrix_calln(calls, 0x4b65a0, object, edx, ebx, step, &stack, 1, NULL));
    second = vertrix_call(calls, 0x4ac980, object, edx, first, step, 0);
    result = vertrix_call(calls, 0x4b6540, object, (uint32_t)(int32_t)signed_word(second), first,
                          second, 0);
    if (second != step)
    {
        return result;
    }
    if (!vertrix_actor_storage_write(storage, size, STEP_STATE, DWORD_WIDTH, 1 - state))
    {
        return 0;
    }
    return 1 - state;
}

enum
{
    DESTROY_CLASS = 0x158,
    DESTROY_CLASS_VALUE = 0x518174,
    DESTROY_FLAG_SKIP = 4,
    DESTROY_FLAG_FREE = 2,
    DESTROY_SKIP_TABLE = 0x518190
};

uint32_t vertrix_object_destroy_call(const VertrixCalls *calls, uint32_t object, void *storage,
                                     size_t size, uint32_t flags)
{
    uint32_t result;
    if ((flags & DESTROY_FLAG_SKIP) != 0)
    {
        uint32_t cleared = vertrix_call(calls, 0x4ccb9f, object, DESTROY_SKIP_TABLE, 1, object, 0);
        vertrix_call(calls, 0x4ca040, cleared, DESTROY_SKIP_TABLE, 1, object, 0);
        return object;
    }
    if (!vertrix_actor_storage_write(storage, size, DESTROY_CLASS, DWORD_WIDTH,
                                     DESTROY_CLASS_VALUE))
    {
        return 0;
    }
    result = vertrix_call(calls, 0x4ac130, object, 1, flags, object, 0);
    if ((flags & DESTROY_FLAG_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, result, 1, flags, result, 0);
    }
    return result;
}

enum
{
    UNKNOWN_CLASS = 0x110,
    UNKNOWN_CLASS_VALUE = 0x517684,
    UNKNOWN_TEXT = 0xc,
    UNKNOWN_OWNER_CALL = 0x478d80,
    STREAM_AT_END = 0x48a910,
    STREAM_PEEK = 0x48aa80,
    STREAM_ADVANCE = 0x48aa90,
    SLASH = 0x2f,
    CENTER_STATE = 0x60,
    CENTER_LEFT = 0x50,
    CENTER_TOP = 0x52,
    DESTROY_D_LITERAL = 0x518420,
    DESTROY_D_FIELD = 0x158,
    DESTROY_D_CLASS = 0x518404,
    DESTROY_D_NAME = 0x15c,
    DESTROY_E_LITERAL = 0x514ef0,
    DESTROY_E_CLASS = 0x5174b4,
    CONSTRUCT_E_CLASS = 0x5174b4,
    CONSTRUCT_E_EBX = 0x517008,
    CONSTRUCT_E_ECX = 0x4ec1ec,
    CONSTRUCT_E_LOCAL = 0x30,
    CONSTRUCT_F_EBX = 0x516650,
    CONSTRUCT_F_COUNT = 0x100,
    CONSTRUCT_F_CLASS_FIELD = 0x6000,
    CONSTRUCT_F_CLASS = 0x5165e4,
    CONSTRUCT_F_ROW_WORD = 0x58,
    CONSTRUCT_F_ROW_SIZE = 0x60,
    CONSTRUCT_G_CLASS = 0x516f04,
    CONSTRUCT_G_FIRST = 0x10,
    CONSTRUCT_G_LAST = 0x20,
    CONSTRUCT_G_FRAME_SHIFT = 4,
    TEXT_FIELD = 0xb9,
    TEXT_LIMIT = 0x100,
    TEXT_FIELD_BASE = 0xb8,
    TEXT_SOURCE = 0x38,
    TEXT_ECX = 0x102,
    TEXT_CALL = 0x47fa40,
    PICK_HEAD = 0xc,
    PICK_NEXT = 0x60,
    PICK_NODE_DATA = 8,
    PICK_TARGET = 0xa4,
    PICK_BYTES = 16,
    PICK_CALL = 0x47fbb0,
    DESTROY_H_LITERAL = 0x513310,
    DESTROY_H_CLASS = 0x517684,
    DESTROY_H_FIELD = 0x110,
    DESTROY_H_EBX = 0x4ec1ec,
    DESTROY_G_LITERAL = 0x516f80,
    DESTROY_G_CLASS = 0x51a1b4,
    DESTROY_G_FINAL_CLASS = 0x517454,
    DESTROY_F_LITERAL = 0x5199f0,
    DESTROY_F_CLASS = 0x5198f4,
    DESTROY_F_NAME = 0xac,
    DESTROY_F_FIRST_BASE = 0x40,
    DESTROY_F_SECOND_BASE = 0x6c,
    DESTROY_A_LITERAL = 0x516390,
    DESTROY_A_CLASS = 0x518344,
    DESTROY_B_LITERAL = 0x516bc0,
    DESTROY_B_FIELD = 0x20c,
    DESTROY_B_CLASS = 0x516b84,
    DESTROY_C_LITERAL = 0x513f30,
    DESTROY_C_FIELD = 0x228,
    DESTROY_C_CLASS = 0x514554,
    DESTROY_C_EBX = 0x4ec1ec,
    LABELED_NAME = 0x15c,
    LABELED_CLASS_FIELD = 0x158,
    LABELED_CLASS = 0x517bd4,
    LABELED_TEXT = 0x160,
    LABELED_MODE = 3,
    LABELED_EDX = 0x4ec1ec,
    LABELED_EBX = 0x517b30,
    LABELED_LITERAL = 0x511082,
    BOX_CLASS = 0x518404,
    BOX_EBX = 0x518360,
    BOX_LITERAL = 0x5110b7,
    BOX_UNSET = 0xff9c,
    WORD_MASK = 0xffff,
    CENTER_SOURCE_LEFT = 0x48,
    CENTER_SOURCE_TOP = 0x4a,
    CENTER_HALF_WIDTH = 0x5c,
    CENTER_HALF_HEIGHT = 0x5e,
    CENTER_SAVED_EBX = 0x54,
    CENTER_SAVED_ECX = 0x58,
    CENTER_BOUNDS = 0x477e10,
    TITLED_CENTER_OBJECT = 0x5588f8,
    TITLED_CENTER_EBX = 0x3c,
    TITLED_CENTER_ECX = 0xc8,
    TITLED_CENTER_NEXT = 0x418840,
    TITLED_CENTER_EDX = 0x424990,
    CENTER_CLEAR_FIRST = 0x64,
    CENTER_CLEAR_LAST = 0x70,
    LINE_FEED = 0xa,
    CARRIAGE_RETURN = 0xd
};

static int unknown_fields(void *storage, size_t size)
{
    static const char text[] = "UNKNOWN";
    for (size_t offset = 0; offset <= 8; offset += 4)
    {
        if (!vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, 0))
        {
            return 0;
        }
    }
    for (size_t i = 0; i < sizeof text; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, UNKNOWN_TEXT + i, BYTE_WIDTH,
                                         (uint8_t)text[i]))
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_object_unknown_init(void *storage, size_t size, uint32_t object)
{
    if (!vertrix_actor_storage_write(storage, size, UNKNOWN_CLASS, DWORD_WIDTH,
                                     UNKNOWN_CLASS_VALUE) ||
        !unknown_fields(storage, size))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_unknown_reset(const VertrixCalls *calls, void *storage, size_t size,
                                      uint32_t object, uint32_t ebx)
{
    uint32_t owner;
    uint32_t eax = object;
    if (!get(storage, size, 0, DWORD_WIDTH, &owner))
    {
        return 0;
    }
    if (owner != 0)
    {
        eax = vertrix_call(calls, UNKNOWN_OWNER_CALL, owner, object, ebx, owner, 0);
    }
    if (!unknown_fields(storage, size))
    {
        return 0;
    }
    return eax & ~0xffu;
}

uint32_t vertrix_stream_skip_line(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t stream, uint32_t ebx)
{
    uint32_t eax = vertrix_call(calls, STREAM_AT_END, stream, stream, ebx, stream, 0);
    while (eax == 0)
    {
        void *storage;
        size_t size;
        uint32_t byte;
        uint32_t handle = vertrix_call(calls, STREAM_PEEK, stream, 1, ebx, stream, 0);
        if (!services->resolve(handle, &storage, &size, services->context) ||
            !get(storage, size, 0, BYTE_WIDTH, &byte))
        {
            return 0;
        }
        ebx = (ebx & ~0xffu) | byte;
        eax = vertrix_call(calls, STREAM_ADVANCE, stream, 1, ebx, stream, 0);
        if (byte == LINE_FEED || byte == CARRIAGE_RETURN)
        {
            return eax;
        }
        eax = vertrix_call(calls, STREAM_AT_END, stream, 1, ebx, stream, 0);
    }
    return eax;
}

enum
{
    STEP_FIELD_VALUE = 0x58,
    STEP_FIELD_TARGET = 0x5c,
    STEP_FIELD_AMOUNT = 0x60,
    CREATE_CALL = 0x4ccf3b,
    CREATE_INIT = 0x482050,
    CREATE_ARGUMENT = 0xa,
    CREATE_RECORD = 0x516ba0,
    CREATE_CLASS = 0x20c,
    CREATE_CLASS_VALUE = 0x516b84
};

uint32_t vertrix_object_step_field(const VertrixCalls *calls, void *storage, size_t size,
                                   uint32_t edx)
{
    uint32_t value, target, amount, moved;
    if (!get(storage, size, STEP_FIELD_AMOUNT, DWORD_WIDTH, &amount) ||
        !get(storage, size, STEP_FIELD_VALUE, DWORD_WIDTH, &value) ||
        !get(storage, size, STEP_FIELD_TARGET, DWORD_WIDTH, &target))
    {
        return 0;
    }
    moved = vertrix_step_toward_call(calls, value, target, edx, amount);
    if (!vertrix_actor_storage_write(storage, size, STEP_FIELD_VALUE, DWORD_WIDTH, moved) ||
        !get(storage, size, STEP_FIELD_TARGET, DWORD_WIDTH, &target))
    {
        return 0;
    }
    return moved != target;
}

uint32_t vertrix_object_create_with_class(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t eax)
{
    void *storage;
    size_t size;
    uint32_t object = vertrix_call(calls, CREATE_CALL, eax, CREATE_ARGUMENT, CREATE_RECORD, eax, 0);
    if (!services->resolve(object, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, CREATE_CLASS, DWORD_WIDTH, CREATE_CLASS_VALUE))
    {
        return 0;
    }
    vertrix_call(calls, CREATE_INIT, object, object, CREATE_RECORD, eax, 0);
    return object;
}
uint32_t vertrix_object_virtual_slot6(const VertrixCalls *calls, VertrixMemoryRead read,
                                      void *read_context, const void *storage, size_t size,
                                      uint32_t ebx, uint32_t ecx)
{
    uint32_t object;
    uint32_t vtable;
    uint32_t method;
    if (!get(storage, size, VIRTUAL_SIDE, DWORD_WIDTH, &object) ||
        !read(object, 4, &vtable, read_context) ||
        !read(vtable + VIRTUAL_SLOT, 4, &method, read_context))
    {
        return 0;
    }
    return vertrix_call(calls, method, object, vtable, ebx, ecx, 0);
}

uint32_t vertrix_object_invoke_callback(const VertrixCalls *calls, uint32_t object,
                                        const void *storage, size_t size, uint32_t ebx,
                                        uint32_t ecx)
{
    uint32_t target;
    if (!get(storage, size, CALLBACK_SLOT, DWORD_WIDTH, &target))
    {
        return 0;
    }
    if (target == 0)
    {
        return object;
    }
    return vertrix_call(calls, target, object, object, ebx, ecx, 0);
}

typedef struct PeekTracker
{
    const VertrixCalls *inner;
    int peeked;
} PeekTracker;

static uint32_t track_peek(VertrixCallSite *site, void *context)
{
    PeekTracker *tracker = context;
    if (site->target == STREAM_PEEK)
    {
        tracker->peeked = 1;
    }
    return tracker->inner->call(site, tracker->inner->context);
}

uint32_t vertrix_stream_skip_blank(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t stream,
                                   uint32_t object, uint32_t edx)
{
    uint32_t eax = vertrix_call(calls, STREAM_AT_END, stream, edx, object, stream, 0);
    while (eax == 0)
    {
        void *storage;
        size_t size;
        uint32_t byte;
        uint32_t handle = vertrix_call(calls, STREAM_PEEK, stream, edx, object, stream, 0);
        if (!services->resolve(handle, &storage, &size, services->context) ||
            !get(storage, size, 0, BYTE_WIDTH, &byte))
        {
            return 0;
        }
        if (byte == SLASH)
        {
            PeekTracker tracker = {calls, 0};
            VertrixCalls tracked = {track_peek, &tracker};
            vertrix_call(calls, STREAM_ADVANCE, stream, 1, object, stream, 0);
            vertrix_stream_skip_line(&tracked, services, stream, object);
            edx = tracker.peeked ? 1 : stream;
        }
        else if (byte == ' ' || byte == LINE_FEED || byte == CARRIAGE_RETURN)
        {
            vertrix_call(calls, STREAM_ADVANCE, stream, 1, object, stream, 0);
            edx = 1;
        }
        else
        {
            return (handle & ~0xffu) | byte;
        }
        eax = vertrix_call(calls, STREAM_AT_END, stream, edx, object, stream, 0);
    }
    return eax;
}

uint32_t vertrix_object_center_setup(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t width, uint32_t height)
{
    uint32_t last_row = (height - 1) & WORD_MASK;
    uint32_t last_column = (width - 1) & WORD_MASK;
    uint32_t stack[1] = {last_row};
    vertrix_calln(calls, 0x477e10, object, 0, 0, last_column, stack, 1, NULL);
    uint32_t result = vertrix_call(calls, 0x478480, object, width >> 1, (height >> 1) & WORD_MASK,
                                   last_column, 0);
    for (size_t offset = CENTER_CLEAR_FIRST; offset <= CENTER_CLEAR_LAST; offset += DWORD_WIDTH)
    {
        if (!vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, 0))
        {
            return 0;
        }
    }
    return result;
}

typedef struct LabeledField
{
    size_t offset;
    unsigned width;
    uint32_t value;
} LabeledField;

typedef struct LabeledSpec
{
    uint32_t ebx;
    uint32_t literal;
    const LabeledField *fields;
    size_t count;
} LabeledSpec;

static uint32_t construct_labeled(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t eax, const LabeledSpec *spec)
{
    void *storage;
    size_t size;
    uint32_t base = vertrix_call(calls, 0x4abd70, eax, LABELED_EDX, spec->ebx, eax, 0);
    base = vertrix_call(calls, 0x4ca070, base + LABELED_NAME, LABELED_EDX, spec->ebx, eax, 0) -
           LABELED_NAME;
    vertrix_call(calls, 0x4ca370, base + LABELED_NAME, spec->literal, spec->ebx, base, 0);
    if (!services->resolve(base, &storage, &size, services->context))
    {
        return 0;
    }
    for (size_t i = 0; i < spec->count; i++)
    {
        if (!vertrix_actor_storage_write(storage, size, spec->fields[i].offset,
                                         spec->fields[i].width, spec->fields[i].value))
        {
            return 0;
        }
    }
    return base;
}

uint32_t vertrix_object_construct_labeled(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t eax)
{
    static const LabeledField fields[] = {{LABELED_CLASS_FIELD, DWORD_WIDTH, LABELED_CLASS},
                                          {LABELED_TEXT, BYTE_WIDTH, 0},
                                          {0x2f2, WORD_WIDTH, 0},
                                          {0x2f4, WORD_WIDTH, 0},
                                          {0x2f6, WORD_WIDTH, 0},
                                          {0x2f8, WORD_WIDTH, 0},
                                          {0x94, BYTE_WIDTH, 0},
                                          {0x95, BYTE_WIDTH, LABELED_MODE},
                                          {0x2fc, DWORD_WIDTH, 0},
                                          {0x300, DWORD_WIDTH, 0},
                                          {0x304, DWORD_WIDTH, 0}};
    static const LabeledSpec spec = {LABELED_EBX, LABELED_LITERAL, fields,
                                     sizeof fields / sizeof fields[0]};
    return construct_labeled(calls, services, eax, &spec);
}

uint32_t vertrix_object_construct_labeled_box(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services, uint32_t eax)
{
    static const LabeledField fields[] = {{LABELED_CLASS_FIELD, DWORD_WIDTH, BOX_CLASS},
                                          {LABELED_TEXT, BYTE_WIDTH, 0},
                                          {0x162, WORD_WIDTH, 0},
                                          {0x164, WORD_WIDTH, 0},
                                          {0x166, WORD_WIDTH, 0},
                                          {0x168, WORD_WIDTH, 0},
                                          {0x16a, WORD_WIDTH, 0},
                                          {0x16c, WORD_WIDTH, 0},
                                          {0x16e, WORD_WIDTH, 0},
                                          {0x170, WORD_WIDTH, 0},
                                          {0x94, BYTE_WIDTH, 0},
                                          {0x95, BYTE_WIDTH, LABELED_MODE},
                                          {0x172, WORD_WIDTH, 0},
                                          {0x17a, WORD_WIDTH, BOX_UNSET},
                                          {0x17c, WORD_WIDTH, BOX_UNSET},
                                          {0x174, DWORD_WIDTH, 0}};
    static const LabeledSpec spec = {BOX_EBX, BOX_LITERAL, fields,
                                     sizeof fields / sizeof fields[0]};
    return construct_labeled(calls, services, eax, &spec);
}

enum
{
    DESTROY_NO_CALL = 4,
    DESTROY_FREE = 2
};

static uint32_t destroy_skipped(const VertrixCalls *calls, uint32_t object, uint32_t literal,
                                uint32_t ebx, uint32_t second_edx)
{
    uint32_t result = vertrix_call(calls, 0x4ccb9f, object, literal, ebx, object, 0);
    vertrix_call(calls, 0x4ca040, result, second_edx, ebx, object, 0);
    return object;
}

static int store_class(const VertrixFactoryServices *services, uint32_t object, size_t offset,
                       uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value);
}

uint32_t vertrix_object_destroy_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags)
{
    uint32_t result;
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_A_LITERAL, 1, DESTROY_A_LITERAL);
    }
    if (!store_class(services, object, 0, DESTROY_A_CLASS))
    {
        return 0;
    }
    result = vertrix_call(calls, 0x4d86d0, object, 1, flags, object, 0);
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, result, 1, flags, result, 0);
    }
    return result;
}

uint32_t vertrix_object_destroy_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags)
{
    uint32_t result;
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_B_LITERAL, 1, DESTROY_B_LITERAL);
    }
    if (!store_class(services, object, DESTROY_B_FIELD, DESTROY_B_CLASS))
    {
        return 0;
    }
    result = vertrix_call(calls, 0x4823b0, object, 0, flags, object, 0);
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, result, 0, flags, result, 0);
    }
    return result;
}

uint32_t vertrix_object_destroy_c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags, uint32_t ebx)
{
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_C_LITERAL, ebx, 0);
    }
    if (!store_class(services, object, DESTROY_C_FIELD, DESTROY_C_CLASS))
    {
        return 0;
    }
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, object, flags, DESTROY_C_EBX, object, 0);
    }
    return object;
}

uint32_t vertrix_object_destroy_d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags)
{
    uint32_t result;
    uint32_t base;
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_D_LITERAL, 1, DESTROY_D_LITERAL);
    }
    if (!store_class(services, object, DESTROY_D_FIELD, DESTROY_D_CLASS))
    {
        return 0;
    }
    base = vertrix_call(calls, 0x4ca210, object + DESTROY_D_NAME, 0, flags, object, 0) -
           DESTROY_D_NAME;
    result = vertrix_call(calls, 0x4ac130, base, 1, flags, base, 0);
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, result, 0, flags, result, 0);
    }
    return result;
}

uint32_t vertrix_object_destroy_e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags)
{
    uint32_t result;
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_E_LITERAL, 1, DESTROY_E_LITERAL);
    }
    if (!store_class(services, object, 0, DESTROY_E_CLASS))
    {
        return 0;
    }
    vertrix_call(calls, 0x4d7630, object, 0, flags, object, 0);
    result = vertrix_call(calls, 0x4d7630, object, 1, flags, object, 0);
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, result, 0, flags, result, 0);
    }
    return result;
}

uint32_t vertrix_object_destroy_f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags)
{
    uint32_t result;
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_F_LITERAL, flags, DESTROY_F_LITERAL);
    }
    if (!store_class(services, object, 0, DESTROY_F_CLASS))
    {
        return 0;
    }
    vertrix_call(calls, 0x4d4060, object, 0, flags, object, 0);
    result = vertrix_call(calls, 0x4ca210, object + DESTROY_F_NAME, 0, flags, object, 0);
    result = vertrix_call(calls, 0x4d83f0, result - DESTROY_F_FIRST_BASE, 0, flags, object, 0);
    result = vertrix_call(calls, 0x4d01a0, result - DESTROY_F_SECOND_BASE, 1, flags, object, 0);
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, result, 1, flags, result, 0);
    }
    return result;
}

static uint32_t center_place(const VertrixCalls *calls, void *storage, size_t size, uint32_t object,
                             uint32_t ebx, uint32_t ecx, uint32_t width, uint32_t height,
                             uint32_t *ebx_out)
{
    uint32_t state, left, top, half_width, half_height, p, q;
    uint32_t stack[1];
    if (!vertrix_actor_storage_read(storage, size, CENTER_STATE, DWORD_WIDTH, &state))
    {
        return 0;
    }
    *ebx_out = ebx;
    if (state != 0)
    {
        return object;
    }
    if (!vertrix_actor_storage_read(storage, size, CENTER_SOURCE_LEFT, WORD_WIDTH, &left) ||
        !vertrix_actor_storage_write(storage, size, CENTER_LEFT, WORD_WIDTH, left) ||
        !vertrix_actor_storage_read(storage, size, CENTER_SOURCE_TOP, WORD_WIDTH, &top) ||
        !vertrix_actor_storage_write(storage, size, CENTER_TOP, WORD_WIDTH, top))
    {
        return 0;
    }
    half_width = (width & WORD_MASK) >> 1;
    half_height = (height & WORD_MASK) >> 1;
    if (!vertrix_actor_storage_write(storage, size, CENTER_HALF_WIDTH, WORD_WIDTH, half_width) ||
        !vertrix_actor_storage_write(storage, size, CENTER_STATE, DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, CENTER_SAVED_EBX, DWORD_WIDTH, ebx) ||
        !vertrix_actor_storage_write(storage, size, CENTER_HALF_HEIGHT, WORD_WIDTH, half_height) ||
        !vertrix_actor_storage_write(storage, size, CENTER_SAVED_ECX, DWORD_WIDTH, ecx))
    {
        return 0;
    }
    vertrix_object_center_setup(calls, storage, size, object, width, height);
    if (!vertrix_actor_storage_read(storage, size, CENTER_HALF_WIDTH, WORD_WIDTH, &half_width) ||
        !vertrix_actor_storage_read(storage, size, CENTER_HALF_HEIGHT, WORD_WIDTH, &half_height))
    {
        return 0;
    }
    p = half_width - ecx;
    q = half_height - ecx;
    stack[0] = (q + 2 * ecx - 1) & WORD_MASK;
    *ebx_out = q & WORD_MASK;
    return vertrix_calln(calls, CENTER_BOUNDS, object, p & WORD_MASK, q & WORD_MASK,
                         (p + 2 * ecx - 1) & WORD_MASK, stack, 1, NULL);
}

uint32_t vertrix_object_center_place(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t ebx, uint32_t ecx, uint32_t width,
                                     uint32_t height)
{
    uint32_t ebx_out;
    return center_place(calls, storage, size, object, ebx, ecx, width, height, &ebx_out);
}

uint32_t vertrix_object_center_titled(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t object,
                                      uint32_t width, uint32_t height)
{
    void *storage;
    size_t size;
    uint32_t ebx;
    if (!services->resolve(TITLED_CENTER_OBJECT, &storage, &size, services->context))
    {
        return 0;
    }
    center_place(calls, storage, size, TITLED_CENTER_OBJECT, TITLED_CENTER_EBX, TITLED_CENTER_ECX,
                 width, height, &ebx);
    return vertrix_call(calls, TITLED_CENTER_NEXT, object, TITLED_CENTER_EDX, ebx, object, 0);
}

uint32_t vertrix_object_construct_e(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t frame,
                                    uint32_t object)
{
    uint32_t created =
        vertrix_call(calls, 0x4d7510, object, object, CONSTRUCT_E_EBX, CONSTRUCT_E_ECX, 0);
    uint32_t local = frame - CONSTRUCT_E_LOCAL;
    if (!store_class(services, created, 0, CONSTRUCT_E_CLASS))
    {
        return 0;
    }
    vertrix_call(calls, 0x4d7510, local, 0, CONSTRUCT_E_EBX, created, 0);
    vertrix_call(calls, 0x4d7630, local, 0, CONSTRUCT_E_EBX, created, 0);
    return created;
}

uint32_t vertrix_object_construct_f(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t object,
                                    uint32_t *flag)
{
    uint32_t created =
        vertrix_call(calls, CREATE_CALL, object, CONSTRUCT_F_COUNT, CONSTRUCT_F_EBX, object, 0);
    if (!store_class(services, created, CONSTRUCT_F_CLASS_FIELD, CONSTRUCT_F_CLASS))
    {
        return 0;
    }
    for (uint32_t index = 0; index < CONSTRUCT_F_COUNT; index++)
    {
        void *storage;
        size_t size;
        if (!services->resolve(created, &storage, &size, services->context) ||
            !vertrix_actor_storage_write(storage, size,
                                         CONSTRUCT_F_ROW_WORD + CONSTRUCT_F_ROW_SIZE * index,
                                         WORD_WIDTH, index))
        {
            return 0;
        }
    }
    vertrix_call(calls, 0x476090, created, CONSTRUCT_F_COUNT, CONSTRUCT_F_EBX, created, 0);
    vertrix_call(calls, 0x4760f0, created, 0, CONSTRUCT_F_EBX, created, 0);
    *flag = 1;
    vertrix_call(calls, 0x4766b0, created, 0, CONSTRUCT_F_EBX, created, 0);
    return created;
}

uint32_t vertrix_object_construct_g(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t frame,
                                    uint32_t object)
{
    uint32_t created =
        vertrix_object_construct_e(calls, services, frame - CONSTRUCT_G_FRAME_SHIFT, object);
    if (!store_class(services, created, 0, CONSTRUCT_G_CLASS))
    {
        return 0;
    }
    for (size_t offset = CONSTRUCT_G_FIRST; offset <= CONSTRUCT_G_LAST; offset += DWORD_WIDTH)
    {
        if (!store_class(services, created, offset, 0))
        {
            return 0;
        }
    }
    return created;
}

uint32_t vertrix_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, const uint8_t *text)
{
    void *storage;
    size_t size;
    uint32_t length = 0, source;
    while (text[length] != 0)
    {
        length++;
    }
    if (length == 0)
    {
        return 0;
    }
    if (length > TEXT_LIMIT)
    {
        length = TEXT_LIMIT;
    }
    if (!services->resolve(object, &storage, &size, services->context))
    {
        return 0;
    }
    for (uint32_t index = 0; index < length; index++)
    {
        if (!vertrix_actor_storage_write(storage, size, TEXT_FIELD + index, 1, text[index]))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_write(storage, size, TEXT_FIELD + length, 1, 0) ||
        !vertrix_actor_storage_read(storage, size, TEXT_SOURCE, DWORD_WIDTH, &source))
    {
        return 0;
    }
    return vertrix_call(calls, TEXT_CALL, object, object + TEXT_FIELD_BASE, source, TEXT_ECX, 0);
}

uint32_t vertrix_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags, uint32_t ebx)
{
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        return destroy_skipped(calls, object, DESTROY_G_LITERAL, ebx, DESTROY_G_LITERAL);
    }
    if (!store_class(services, object, 0, DESTROY_G_CLASS))
    {
        return 0;
    }
    vertrix_call(calls, 0x4d8b30, object, flags, ebx, object, 0);
    if (!store_class(services, object, 0, DESTROY_G_FINAL_CLASS))
    {
        return 0;
    }
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, object, flags, ebx, object, 0);
    }
    return object;
}

uint32_t vertrix_object_destroy_h(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t flags, uint32_t ebx)
{
    void *storage;
    size_t size;
    if ((flags & DESTROY_NO_CALL) != 0)
    {
        uint32_t result = vertrix_call(calls, 0x4ccb9f, object, DESTROY_H_LITERAL, ebx, object, 0);
        vertrix_call(calls, 0x4ca040, result, 0, ebx, object, 0);
        return object;
    }
    if (!store_class(services, object, DESTROY_H_FIELD, DESTROY_H_CLASS) ||
        !services->resolve(object, &storage, &size, services->context))
    {
        return 0;
    }
    vertrix_object_unknown_reset(calls, storage, size, object, DESTROY_H_EBX);
    if ((flags & DESTROY_FREE) != 0)
    {
        vertrix_call(calls, 0x4ca050, object, flags, DESTROY_H_EBX, object, 0);
    }
    return object;
}

static int read_dword_of(const VertrixFactoryServices *services, uint32_t object, size_t offset,
                         uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

static int copy_to_target(const VertrixFactoryServices *services, uint32_t object,
                          const uint8_t *bytes)
{
    for (size_t offset = 0; offset < PICK_BYTES; offset += DWORD_WIDTH)
    {
        uint32_t value = (uint32_t)bytes[offset] | (uint32_t)bytes[offset + 1] << 8 |
                         (uint32_t)bytes[offset + 2] << 16 | (uint32_t)bytes[offset + 3] << 24;
        if (!store_class(services, object, PICK_TARGET + offset, value))
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_object_pick_entry(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   uint32_t index, uint32_t ecx, const uint8_t scratch[16])
{
    uint32_t node, count = 0;
    uint8_t entry[PICK_BYTES];
    if (!read_dword_of(services, object, PICK_HEAD, &node))
    {
        return 0;
    }
    vertrix_call(calls, PICK_CALL, object, node, index, ecx, 0);
    if (!copy_to_target(services, object, scratch))
    {
        return 0;
    }
    while (node != 0 && count != index)
    {
        if (!read_dword_of(services, node, PICK_NEXT, &node))
        {
            return 0;
        }
        count++;
    }
    if (node == 0)
    {
        return 0;
    }
    for (size_t offset = 0; offset < PICK_BYTES; offset += DWORD_WIDTH)
    {
        uint32_t value;
        if (!read_dword_of(services, node, PICK_NODE_DATA + offset, &value))
        {
            return 0;
        }
        entry[offset] = (uint8_t)value;
        entry[offset + 1] = (uint8_t)(value >> 8);
        entry[offset + 2] = (uint8_t)(value >> 16);
        entry[offset + 3] = (uint8_t)(value >> 24);
    }
    return copy_to_target(services, object, entry) ? 1 : 0;
}

uint32_t vertrix_object_reset_center(const VertrixCalls *calls, void *storage, size_t size,
                                     uint32_t object, uint32_t width, uint32_t height)
{
    uint32_t state, left, top;
    if (!vertrix_actor_storage_read(storage, size, CENTER_STATE, DWORD_WIDTH, &state))
    {
        return 0;
    }
    if (state != 1)
    {
        return object;
    }
    if (!vertrix_actor_storage_write(storage, size, CENTER_STATE, DWORD_WIDTH, 0))
    {
        return 0;
    }
    vertrix_object_center_setup(calls, storage, size, object, width, height);
    if (!vertrix_actor_storage_read(storage, size, CENTER_LEFT, WORD_WIDTH, &left) ||
        !vertrix_actor_storage_read(storage, size, CENTER_TOP, WORD_WIDTH, &top))
    {
        return 0;
    }
    vertrix_call(calls, 0x478480, object, left, top, object, 0);
    return vertrix_call(calls, 0x478460, object, left, top, object, 0);
}

typedef struct IdleCheck
{
    size_t offset;
    uint32_t value;
} IdleCheck;

enum
{
    IDLE_LINK = 0xd8,
    IDLE_REFERENCE = 0x13c,
    IDLE_COUNT_LIMIT = 2
};

static const IdleCheck IDLE_OWN[] = {{0x4c, 0}, {0x12c, 0}, {0x28, 3},
                                     {0x24, 3}, {0x2c, 2},  {0x78, 3}};
static const IdleCheck IDLE_LINKED[] = {{0x8, 2}, {0x5c, 1}, {0xb0, 1}};
static const IdleCheck IDLE_LINKED_LAST[] = {{0x60, 1}, {0xb4, 1}};
static const size_t IDLE_MATCH[] = {0x24, 0x78, 0xcc};

static int idle_matches(const VertrixFactoryServices *services, uint32_t object,
                        const IdleCheck *checks, size_t count)
{
    for (size_t index = 0; index < count; index++)
    {
        uint32_t value;
        if (!read_dword_of(services, object, checks[index].offset, &value) ||
            value != checks[index].value)
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_object_is_idle(const VertrixFactoryServices *services, uint32_t object)
{
    uint32_t link, count, reference;
    if (!idle_matches(services, object, IDLE_OWN, sizeof IDLE_OWN / sizeof IDLE_OWN[0]) ||
        !read_dword_of(services, object, IDLE_LINK, &link) ||
        !idle_matches(services, link, IDLE_LINKED, sizeof IDLE_LINKED / sizeof IDLE_LINKED[0]) ||
        !read_dword_of(services, link, 0xc, &count) || (int32_t)count > IDLE_COUNT_LIMIT ||
        !idle_matches(services, link, IDLE_LINKED_LAST,
                      sizeof IDLE_LINKED_LAST / sizeof IDLE_LINKED_LAST[0]) ||
        !read_dword_of(services, object, IDLE_REFERENCE, &reference))
    {
        return 0;
    }
    for (size_t index = 0; index < sizeof IDLE_MATCH / sizeof IDLE_MATCH[0]; index++)
    {
        uint32_t value;
        if (!read_dword_of(services, link, IDLE_MATCH[index], &value) || value != reference)
        {
            return 0;
        }
    }
    return 1;
}

enum
{
    REGION_FIRST = 0x432820,
    REGION_COPY = 0x428110,
    REGION_MEASURE = 0x427c10,
    REGION_CLASS = 0x428610,
    REGION_ECX = 0x41,
    REGION_ECX_CLASS = 0x4fb500,
    REGION_LOCAL_FIRST = 0xa4,
    REGION_LOCAL_SECOND = 0x60,
    REGION_TEXT = 0x15c,
    REGION_LINK = 0x3b0,
    REGION_SCRATCH = 0x1c5,
    REGION_AREA = 0x1de,
    REGION_ARGUMENTS = 5,
    REGION_COPY_BYTES = 0x41
};

static int copy_area(const VertrixFactoryServices *services, uint32_t object, uint8_t *bytes)
{
    void *storage;
    size_t size;
    if (!services->resolve(object, &storage, &size, services->context))
    {
        return 0;
    }
    for (size_t index = 0; index < REGION_COPY_BYTES; index++)
    {
        uint32_t value;
        if (!vertrix_actor_storage_read(storage, size, REGION_AREA + index, 1, &value))
        {
            return 0;
        }
        bytes[index] = (uint8_t)value;
    }
    return 1;
}

uint32_t vertrix_object_compare_regions(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t frame,
                                        uint32_t object, uint32_t second, uint32_t ebx,
                                        uint8_t first_copy[REGION_COPY_BYTES],
                                        uint8_t second_copy[REGION_COPY_BYTES])
{
    uint32_t link, second_text, link_text, object_angle, link_c180, second_c180;
    uint32_t link_178, link_17c, second_178, second_17c, object_160, scratch, result;
    uint32_t arguments[REGION_ARGUMENTS];
    if (!read_dword_of(services, second, REGION_LINK, &link) ||
        !read_dword_of(services, second, REGION_TEXT, &second_text) ||
        !read_dword_of(services, link, REGION_TEXT, &link_text))
    {
        return 0;
    }
    vertrix_call(calls, REGION_FIRST, second_text, link_text, ebx, REGION_ECX, 0);
    vertrix_call(calls, REGION_FIRST, link_text, link_text, ebx, REGION_ECX, 0);
    if (!copy_area(services, second_text, first_copy) ||
        !copy_area(services, link_text, second_copy))
    {
        return 0;
    }
    scratch = object + REGION_SCRATCH;
    vertrix_call(calls, REGION_COPY, object, frame - REGION_LOCAL_FIRST,
                 frame - REGION_LOCAL_SECOND, scratch, 0);
    if (!read_dword_of(services, object, 0x164, &object_angle) ||
        !read_dword_of(services, link, 0x180, &link_c180) ||
        !read_dword_of(services, second, 0x180, &second_c180) ||
        !read_dword_of(services, link, 0x178, &link_178) ||
        !read_dword_of(services, second, 0x17c, &second_17c) ||
        !read_dword_of(services, link, 0x17c, &link_17c) ||
        !read_dword_of(services, second, 0x178, &second_178) ||
        !read_dword_of(services, object, 0x160, &object_160))
    {
        return 0;
    }
    arguments[0] = link_178;
    arguments[1] = second_c180 - 0xc;
    arguments[2] = link_c180 - 0xc;
    arguments[3] = object_angle;
    arguments[4] = scratch;
    vertrix_calln(calls, REGION_MEASURE, object, second_17c, link_17c, second_178, arguments,
                  REGION_ARGUMENTS, NULL);
    result =
        vertrix_call(calls, REGION_CLASS, object, scratch, object_160, REGION_ECX_CLASS, 0) & 0xff;
    if (result < 3)
    {
        return 1;
    }
    return result <= 5 ? 0 : 0xffffffffu;
}

enum
{
    TREE_RELEASE = 0x4ea190,
    TREE_ITEM_RELEASE = 0x40aca0,
    TREE_RECORDS = 0x150,
    TREE_BLOCKS = 0x154,
    TREE_RECORD_COUNT = 0x28,
    TREE_BLOCK_COUNT = 0x2a,
    TREE_RECORD_SIZE = 0xc,
    TREE_RECORD_FIELD = 8,
    TREE_BLOCK_SIZE = 0xfc,
    TREE_BLOCK_ITEMS = 0xf8,
    TREE_BLOCK_ITEM_COUNT = 0x80,
    TREE_ITEM_FIRST = 0x24,
    TREE_ITEM_SIZE = 0x3c,
    TREE_FAILURE = 2
};

static int read_at(const VertrixFactoryServices *services, uint32_t base, size_t offset,
                   unsigned width, uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(base, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, width, value);
}

uint32_t vertrix_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t records, blocks, count, block_count, field, items, item_count;
    if (object == 0)
    {
        return TREE_FAILURE;
    }
    if (!read_dword_of(services, object, TREE_RECORDS, &records))
    {
        return 0;
    }
    edx = records;
    if (edx != 0)
    {
        for (ecx = 0;; ecx++, edx += TREE_RECORD_SIZE)
        {
            ebx = object;
            if (!read_at(services, object, TREE_RECORD_COUNT, 2, &count))
            {
                return 0;
            }
            if (ecx >= count)
            {
                break;
            }
            if (!read_at(services, records, TREE_RECORD_SIZE * ecx + TREE_RECORD_FIELD, 4, &field))
            {
                return 0;
            }
            ebx = field;
            if (ebx != 0)
            {
                vertrix_call(calls, TREE_RELEASE, ebx, edx, ebx, ecx, 0);
            }
        }
        vertrix_call(calls, TREE_RELEASE, records, edx, ebx, ecx, 0);
    }
    if (!read_dword_of(services, object, TREE_BLOCKS, &blocks))
    {
        return 0;
    }
    if (blocks != 0)
    {
        for (uint32_t index = 0;; index++)
        {
            edx = object;
            if (!read_at(services, object, TREE_BLOCK_COUNT, 2, &block_count))
            {
                return 0;
            }
            if (index >= block_count)
            {
                break;
            }
            if (!read_at(services, blocks, TREE_BLOCK_SIZE * index + TREE_BLOCK_ITEMS, 4, &items))
            {
                return 0;
            }
            ebx = items;
            ecx = 0;
            edx = ebx + TREE_ITEM_FIRST;
            for (;; ecx++, edx += TREE_ITEM_SIZE, ebx += TREE_ITEM_SIZE)
            {
                if (!read_at(services, blocks, TREE_BLOCK_SIZE * index + TREE_BLOCK_ITEM_COUNT, 2,
                             &item_count))
                {
                    return 0;
                }
                if (ecx >= item_count)
                {
                    break;
                }
                vertrix_call(calls, TREE_ITEM_RELEASE, edx, edx, ebx, ecx, 0);
            }
            vertrix_call(calls, TREE_RELEASE, items, edx, ebx, ecx, 0);
        }
        vertrix_call(calls, TREE_RELEASE, blocks, edx, ebx, ecx, 0);
    }
    vertrix_call(calls, TREE_RELEASE, object, edx, ebx, ecx, 0);
    return 0;
}

enum
{
    ITEM_PREPARE = 0x4eb860,
    ITEM_PREPARE_EBX = 0x16,
    ITEM_ALLOCATE = 0x4ec160,
    ITEM_ALLOCATE_EDX = 0x3c,
    ITEM_ATTACH = 0x40ac50,
    ITEM_FILL = 0x40c220,
    ITEM_FINISH = 0x40acd0,
    ITEM_OUT_OF_MEMORY = 8,
    ITEM_SOURCE_SIZE = 0x18,
    ITEM_SOURCE_LOW = 0x1c,
    ITEM_SOURCE_HIGH = 0x20,
    ITEM_SOURCE_BYTE_A = 0x24,
    ITEM_SOURCE_BYTE_B = 0x25,
    ITEM_COUNT_WORD = 0x80,
    ITEM_SLOT = 0xf8,
    ITEM_FLAGS = 0x3a,
    ITEM_FLAG_RANGE = 0x10,
    ITEM_SIZE = 0x2c,
    ITEM_BYTE_A = 0x20,
    ITEM_MARK = 0x21,
    ITEM_MARK_VALUE = 0x80,
    ITEM_BYTE_B = 0x23,
    ITEM_RANGE_LOW = 0x30,
    ITEM_RANGE_HIGH = 0x34,
    ITEM_BUFFER = 0x24,
    ITEM_FLIP = 0x80
};

static int write_at(const VertrixFactoryServices *services, uint32_t base, size_t offset,
                    unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(base, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, width, value);
}

uint32_t vertrix_object_attach_item(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t object,
                                    uint32_t source)
{
    uint32_t item, size, low, high, byte_a, byte_b, edx, result, buffer;
    void *storage;
    size_t storage_size;
    vertrix_call(calls, ITEM_PREPARE, object, source, ITEM_PREPARE_EBX, source, 0);
    if (!read_at(services, source, ITEM_SOURCE_SIZE, 4, &size))
    {
        return 0;
    }
    if (size == 0)
    {
        return 0;
    }
    item = vertrix_call(calls, ITEM_ALLOCATE, 1, ITEM_ALLOCATE_EDX, ITEM_PREPARE_EBX, source, 0);
    if (item == 0)
    {
        return ITEM_OUT_OF_MEMORY;
    }
    if (!write_at(services, object, ITEM_COUNT_WORD, 2, 1) ||
        !write_at(services, object, ITEM_SLOT, 4, item) ||
        !write_at(services, item, ITEM_FLAGS, 2, 0) ||
        !write_at(services, item, ITEM_SIZE, 4, size) ||
        !read_at(services, source, ITEM_SOURCE_BYTE_B, 1, &byte_b) ||
        !write_at(services, item, ITEM_BYTE_A, 1, byte_b) ||
        !read_at(services, source, ITEM_SOURCE_BYTE_A, 1, &byte_a) ||
        !write_at(services, item, ITEM_BYTE_B, 1, byte_a) ||
        !write_at(services, item, ITEM_MARK, 1, ITEM_MARK_VALUE) ||
        !read_at(services, source, ITEM_SOURCE_LOW, 4, &low) ||
        !read_at(services, source, ITEM_SOURCE_HIGH, 4, &high))
    {
        return 0;
    }
    edx = low + 2;
    if (edx < high && high <= size)
    {
        edx = high;
        if (!write_at(services, item, ITEM_FLAGS, 1, ITEM_FLAG_RANGE) ||
            !write_at(services, item, ITEM_RANGE_LOW, 4, low) ||
            !write_at(services, item, ITEM_RANGE_HIGH, 4, high))
        {
            return 0;
        }
    }
    result =
        vertrix_calln(calls, ITEM_ATTACH, item + ITEM_BUFFER, edx, high, source, NULL, 0, &buffer);
    if (result != 0)
    {
        return result;
    }
    if (!write_at(services, item, ITEM_BUFFER, 4, buffer) ||
        !read_at(services, item, ITEM_SIZE, 4, &size))
    {
        return 0;
    }
    vertrix_call(calls, ITEM_FILL, buffer, size, high, source, 0);
    if (!services->resolve(buffer, &storage, &storage_size, services->context))
    {
        return 0;
    }
    for (uint32_t index = 0; index < size; index++)
    {
        uint32_t value;
        if (!vertrix_actor_storage_read(storage, storage_size, index, 1, &value) ||
            !vertrix_actor_storage_write(storage, storage_size, index, 1, value ^ ITEM_FLIP))
        {
            return 0;
        }
    }
    vertrix_call(calls, ITEM_FINISH, item + ITEM_BUFFER, 0, size, source, 0);
    return 0;
}

enum
{
    VERDICT_FLAG = 0x4c5,
    VERDICT_LINK = 0x3b0,
    VERDICT_OTHER = 0x450,
    VERDICT_NONE = 3,
    VERDICT_FIRST = 4,
    VERDICT_LATER = 5,
    VERDICT_FRAME_SHIFT = 12
};

uint32_t vertrix_object_region_verdict(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t frame,
                                       uint32_t object, uint32_t ebx,
                                       uint8_t first_copy[REGION_COPY_BYTES],
                                       uint8_t second_copy[REGION_COPY_BYTES])
{
    uint32_t flag, link, other, result;
    if (!read_at(services, object, VERDICT_FLAG, 1, &flag))
    {
        return 0;
    }
    if ((flag & 0xff) == 0)
    {
        return VERDICT_NONE;
    }
    if (!read_dword_of(services, object, VERDICT_LINK, &link) ||
        !read_at(services, link, VERDICT_FLAG, 1, &flag))
    {
        return 0;
    }
    if ((flag & 0xff) == 0)
    {
        return VERDICT_LATER;
    }
    if (!read_dword_of(services, object, VERDICT_OTHER, &other))
    {
        return 0;
    }
    result = vertrix_object_compare_regions(calls, services, frame - VERDICT_FRAME_SHIFT, other,
                                            object, ebx, first_copy, second_copy);
    if (result == 0xffffffffu)
    {
        return VERDICT_NONE;
    }
    return result == 0 ? VERDICT_FIRST : VERDICT_LATER;
}

enum
{
    CORNER_FIRST = 0x4408e0,
    CORNER_SECOND = 0x440a20,
    CORNER_OBJECT_BYTE = 0x44,
    CORNER_FIRST_ARGUMENTS = 7,
    CORNER_LOCAL_A = 0x1c,
    CORNER_LOCAL_B = 0x18,
    CORNER_LOCAL_X = 0xc,
    CORNER_LOCAL_Y = 0x10
};

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(value & WORD_MASK);
}

uint32_t vertrix_object_corner_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t frame,
                                    uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                    const uint32_t arguments[4])
{
    uint32_t style, x, y;
    VertrixCallSite site = {CORNER_FIRST,
                            (uint32_t)(int32_t)(int8_t)edx,
                            sign16(ebx),
                            sign16(ecx),
                            sign16(arguments[0]),
                            0,
                            0,
                            0,
                            0,
                            0,
                            {0},
                            0};
    if (!read_at(services, arguments[3], CORNER_OBJECT_BYTE, 1, &style))
    {
        return 0;
    }
    site.stack = sign16(arguments[1]);
    site.stack_next = arguments[2];
    site.stack_third = style & 0xff;
    site.stack_rest[0] = frame - CORNER_LOCAL_A;
    site.stack_rest[1] = frame - CORNER_LOCAL_B;
    site.stack_rest[2] = frame - CORNER_LOCAL_X;
    site.stack_rest[3] = frame - CORNER_LOCAL_Y;
    calls->call(&site, calls->context);
    y = site.out_ebx;
    x = site.out_ecx;
    {
        uint32_t stack[2] = {arguments[2], arguments[3]};
        return vertrix_calln(calls, CORNER_SECOND, object, (uint32_t)(int32_t)(int8_t)edx,
                             sign16(x), sign16(y), stack, 2, NULL);
    }
}

enum
{
    POPULATE_ALLOCATE = 0x4ca000,
    POPULATE_WRAP = 0x4abd70,
    POPULATE_INIT = 0x4adf20,
    POPULATE_FIRST = 0x43dea0,
    POPULATE_SECOND = 0x43dc80,
    POPULATE_DRAW = 0x4826c0,
    POPULATE_DRAW_TABLE = 0x598d30,
    POPULATE_DRAW_LIMIT = 0xc8,
    POPULATE_ITEM_SIZE = 0x15c,
    POPULATE_FIRST_SPAN = 0x7d0,
    POPULATE_SECOND_SPAN = 0x20,
    POPULATE_FLAG = 0x17c,
    POPULATE_FIRST_SLOTS = 0x15c,
    POPULATE_SECOND_SLOTS = 0x92c,
    POPULATE_ITEM_DELAY = 0x58,
    POPULATE_ITEM_FLAG = 0x94,
    POPULATE_INIT_ARGUMENTS = 5
};

static uint32_t populate_item(const VertrixCalls *calls, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t item = vertrix_call(calls, POPULATE_ALLOCATE, POPULATE_ITEM_SIZE, edx, ebx, ecx, 0);
    uint32_t zeros[POPULATE_INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    if (item != 0)
    {
        item = vertrix_call(calls, POPULATE_WRAP, item, edx, ebx, ecx, 0);
    }
    vertrix_calln(calls, POPULATE_INIT, item, 0, 0, 0, zeros, POPULATE_INIT_ARGUMENTS, NULL);
    return item;
}

uint32_t vertrix_object_populate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t end = object + POPULATE_FIRST_SPAN;
    uint32_t cursor = object, draw, item;
    if (!write_at(services, object, POPULATE_FIRST_SPAN + POPULATE_FLAG, 4, 1))
    {
        return 0;
    }
    do
    {
        item = populate_item(calls, edx, ebx, ecx);
        vertrix_call(calls, POPULATE_FIRST, object, item, 0, 0, 0);
        draw =
            vertrix_call(calls, POPULATE_DRAW, POPULATE_DRAW_TABLE, POPULATE_DRAW_LIMIT, 0, 0, 0);
        if (!write_at(services, item, POPULATE_ITEM_DELAY, 4, draw & WORD_MASK) ||
            !write_at(services, object, (cursor - object) + POPULATE_FIRST_SLOTS, 4, item))
        {
            return 0;
        }
        cursor += 4;
        edx = cursor;
        ebx = 0;
        ecx = end;
    } while (cursor != end);
    cursor = object;
    do
    {
        item = populate_item(calls, edx, ebx, ecx);
        if (!write_at(services, item, POPULATE_ITEM_FLAG, 1, 1))
        {
            return 0;
        }
        vertrix_call(calls, POPULATE_SECOND, object, item, 0, 0, 0);
        draw =
            vertrix_call(calls, POPULATE_DRAW, POPULATE_DRAW_TABLE, POPULATE_DRAW_LIMIT, 0, 0, 0);
        if (!write_at(services, item, POPULATE_ITEM_DELAY, 4, draw & WORD_MASK) ||
            !write_at(services, object, (cursor - object) + POPULATE_SECOND_SLOTS, 4, item))
        {
            return 0;
        }
        cursor += 4;
        edx = POPULATE_DRAW_LIMIT;
        ebx = cursor;
        ecx = 0;
    } while (cursor != object + POPULATE_SECOND_SPAN);
    return object + POPULATE_SECOND_SPAN - 4;
}

enum
{
    TOKEN_ASSIGN = 0x4ca370,
    TOKEN_TEXT = 0x510a59,
    TOKEN_APPEND = 0x4ca630,
    TOKEN_FINISH_FIRST = 0x4ce030,
    TOKEN_FINISH_SECOND = 0x4cdfe0,
    TOKEN_BACKSLASH = 0x5c,
    SKIP_LINE = 0x48a380,
    ADVANCE_ONE = 1
};

static int peek_byte(const VertrixCalls *calls, const VertrixFactoryServices *services,
                     uint32_t stream, uint32_t edx, uint32_t ebx, uint32_t *byte)
{
    void *storage;
    size_t size;
    uint32_t handle = vertrix_call(calls, STREAM_PEEK, stream, edx, ebx, stream, 0);
    return services->resolve(handle, &storage, &size, services->context) &&
           get(storage, size, 0, BYTE_WIDTH, byte);
}

uint32_t vertrix_stream_read_token(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t stream,
                                   uint32_t object)
{
    uint32_t ebx = object;
    uint32_t edx = TOKEN_TEXT;
    vertrix_call(calls, TOKEN_ASSIGN, object, edx, ebx, stream, 0);
    while (vertrix_call(calls, STREAM_AT_END, stream, edx, ebx, stream, 0) == 0)
    {
        uint32_t byte;
        if (!peek_byte(calls, services, stream, ADVANCE_ONE, ebx, &byte))
        {
            return 0;
        }
        ebx = (ebx & ~0xffu) | byte;
        vertrix_call(calls, STREAM_ADVANCE, stream, ADVANCE_ONE, ebx, stream, 0);
        edx = ADVANCE_ONE;
        if (byte == TOKEN_BACKSLASH || byte == LINE_FEED || byte == CARRIAGE_RETURN)
        {
            break;
        }
        edx = byte;
        vertrix_call(calls, TOKEN_APPEND, object, edx, ebx, stream, 0);
    }
    vertrix_call(calls, TOKEN_FINISH_FIRST, object, edx, ebx, stream, 0);
    return vertrix_call(calls, TOKEN_FINISH_SECOND, object, edx, ebx, stream, 0);
}

uint32_t vertrix_stream_next_directive(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       uint32_t stream)
{
    uint32_t edx = stream;
    while (vertrix_call(calls, STREAM_AT_END, stream, edx, object, stream, 0) == 0)
    {
        uint32_t byte;
        if (!peek_byte(calls, services, stream, edx, object, &byte))
        {
            return 0;
        }
        if (byte == SLASH)
        {
            vertrix_call(calls, STREAM_ADVANCE, stream, ADVANCE_ONE, object, stream, 0);
            vertrix_call(calls, SKIP_LINE, object, stream, object, stream, 0);
            return 0;
        }
        if (byte == LINE_FEED || byte == CARRIAGE_RETURN)
        {
            vertrix_call(calls, STREAM_ADVANCE, stream, ADVANCE_ONE, object, stream, 0);
            return 0;
        }
        if (byte != ' ')
        {
            return 1;
        }
        vertrix_call(calls, STREAM_ADVANCE, stream, ADVANCE_ONE, object, stream, 0);
        edx = ADVANCE_ONE;
    }
    return 0;
}
