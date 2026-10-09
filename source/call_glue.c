#include "call_glue.h"
#include "actor_storage.h"

/* Debugging: an address whose stores lift_store (lift_runtime.h) and the lifted host report.
 * Defined here so that every build of lifted routines, which always links the call glue, has it. */
uint32_t vertrix_debug_watch;

enum
{
    STEP_COUNT = 7,
    SLOT_COUNT = 256,
    SLOT_SIZE = 0x60,
    GRID_ROW_STRIDE = 280,
    GRID_COLUMN_STRIDE = 28,
    BYTE_MASK = 0xff
};

uint32_t vertrix_call(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                      uint32_t ebx, uint32_t ecx, uint32_t stack)
{
    VertrixCallSite site = {target, eax, edx, ebx, ecx, stack, 0, 0, 0, 0, {0}, 0};
    return calls->call(&site, calls->context);
}

uint32_t vertrix_call_out(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                          uint32_t ebx, uint32_t ecx, uint32_t *out_ebx, uint32_t *out_ecx)
{
    VertrixCallSite site = {target, eax, edx, ebx, ecx, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t result = calls->call(&site, calls->context);
    *out_ebx = site.out_ebx;
    *out_ecx = site.out_ecx;
    return result;
}

uint32_t vertrix_calln(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t *stack, unsigned count,
                       uint32_t *out_value)
{
    VertrixCallSite site = {target, eax, edx, ebx, ecx, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t result;
    for (unsigned i = 0; i < count; ++i)
    {
        if (i == 0)
        {
            site.stack = stack[i];
        }
        else if (i == 1)
        {
            site.stack_next = stack[i];
        }
        else if (i == 2)
        {
            site.stack_third = stack[i];
        }
        else if (i - 3 < sizeof site.stack_rest / sizeof site.stack_rest[0])
        {
            site.stack_rest[i - 3] = stack[i];
        }
    }
    result = calls->call(&site, calls->context);
    if (out_value)
    {
        *out_value = site.out_value;
    }
    return result;
}

uint32_t vertrix_call3(const VertrixCalls *calls, uint32_t target, uint32_t eax, uint32_t edx,
                       uint32_t ebx, uint32_t ecx, const uint32_t stack[3])
{
    VertrixCallSite site = {target, eax, edx, ebx, ecx, stack[0], stack[1], stack[2], 0, 0, {0}, 0};
    return calls->call(&site, calls->context);
}

uint32_t vertrix_resource_entry_call(const VertrixCalls *calls, uint32_t eax, uint32_t index)
{
    return vertrix_call(calls, 0x4cea15, eax, index, VERTRIX_CALL_RESOURCE_TABLE, 0, 0);
}

void vertrix_global_store(const VertrixCalls *calls, uint32_t address, unsigned size,
                          uint32_t value)
{
    const uint32_t width[1] = {size};
    vertrix_calln(calls, VERTRIX_GLOBAL_STORE, address, value, 0, 0, width, 1, NULL);
}

uint32_t vertrix_point_list_add(const VertrixCalls *calls, uint32_t object, uint16_t value)
{
    vertrix_call(calls, 0x476160, VERTRIX_CALL_POINT_LIST, object, value, object, 0);
    return object;
}

uint32_t vertrix_point_list_conditional(const VertrixCalls *calls, uint16_t first, uint32_t second)
{
    uint32_t result = vertrix_call(calls, 0x476480, VERTRIX_CALL_POINT_LIST, first, second, 0, 0);
    if (result != 1)
    {
        return result;
    }
    return vertrix_call(calls, 0x476720, VERTRIX_CALL_POINT_LIST, (uint16_t)second, second, 0, 0);
}

uint32_t vertrix_point_list_when_one(const VertrixCalls *calls, uint32_t eax, uint32_t flag)
{
    if (flag != 1)
    {
        return eax;
    }
    return vertrix_call(calls, 0x476720, VERTRIX_CALL_POINT_LIST, (uint16_t)eax, 0, 0, 0);
}

uint32_t vertrix_resource_one_frame(const VertrixCalls *calls, uint32_t resource, uint32_t count)
{
    return vertrix_call(calls, 0x487640, resource, count, 0, 0, 0);
}

uint32_t vertrix_grid_cell_call(const VertrixCalls *calls, uint32_t row, uint32_t column,
                                uint32_t third, uint32_t fourth, uint32_t first, uint32_t second)
{
    uint32_t cell = VERTRIX_CALL_GRID_BASE + GRID_ROW_STRIDE * row + GRID_COLUMN_STRIDE * column;
    return vertrix_call(calls, 0x487750, cell, third, fourth, first, second);
}

uint32_t vertrix_seven_steps(const VertrixCalls *calls, uint32_t eax)
{
    uint32_t result = eax;
    for (uint32_t i = 0; i < STEP_COUNT; ++i)
    {
        result = vertrix_call(calls, 0x45f0c0, eax, i, eax, i + 1, 0);
    }
    return vertrix_call(calls, 0x45f1e0, result, STEP_COUNT - 1, eax, STEP_COUNT, 0);
}

uint32_t vertrix_object_set_table(const VertrixCalls *calls, void *storage, size_t size,
                                  uint32_t object)
{
    if (!vertrix_actor_storage_write(storage, size, VERTRIX_CALL_VTABLE_FIELD, 4,
                                     VERTRIX_CALL_VTABLE_VALUE))
    {
        return 0;
    }
    vertrix_call(calls, 0x425de0, object, object, 0, 0, 0);
    return object;
}

uint32_t vertrix_glyph_present(const VertrixCalls *calls, uint32_t eax, uint32_t edx)
{
    uint32_t low = (uint32_t)(int32_t)(int8_t)(eax & BYTE_MASK);
    return vertrix_call(calls, 0x43f420, low, edx & BYTE_MASK, 0, 0, 0) != 0;
}

uint32_t vertrix_forward_4ea190(const VertrixCalls *calls)
{
    return vertrix_call(calls, 0x4ea190, 0, 0, 0, 0, 0);
}

uint32_t vertrix_list_clear_call(const VertrixCalls *calls, uint32_t list)
{
    return vertrix_call(calls, VERTRIX_CALL_LIST_CLEAR, list, 0, 0, 0, 0);
}

uint32_t vertrix_offset_call(const VertrixCalls *calls, uint32_t target, uint32_t eax,
                             uint32_t offset)
{
    return vertrix_call(calls, target, eax + offset, 0, 0, 0, 0);
}

uint32_t vertrix_slot_call(const VertrixCalls *calls, uint32_t table, uint32_t index)
{
    uint32_t slot = index & 0xffff;
    return vertrix_call(calls, 0x4759e0, table + ((slot * 3) << VERTRIX_CALL_SLOT_STRIDE_SHIFT),
                        slot, 0, table, 0);
}

uint32_t vertrix_list_find_call(const VertrixCalls *calls, uint32_t edx)
{
    VertrixCallSite site = {0x475b80, 0x55364c, 0, edx, 0, 0, 0, 0, 0, 0, {0}, 0};
    return calls->call(&site, calls->context);
}

uint32_t vertrix_when_flag_call(const VertrixCalls *calls, uint32_t flag, uint32_t eax)
{
    if (flag != 1)
    {
        return eax;
    }
    return vertrix_call(calls, 0x40eea0, 0, 0, 0, 0, 0);
}

uint32_t vertrix_forward_first_dword(const VertrixCalls *calls, const void *storage, size_t size)
{
    uint32_t first;
    if (!vertrix_actor_storage_read(storage, size, 0, 4, &first))
    {
        return 0;
    }
    return vertrix_call(calls, 0x4ea190, first, 0, 0, 0, 0);
}

uint32_t vertrix_table_entry_call(const VertrixCalls *calls, const uint32_t *table, uint32_t eax)
{
    return vertrix_call(calls, 0x40adc0, table[eax & BYTE_MASK], 0, 0, 0, 0);
}

void vertrix_copy_dword(uint32_t *destination, const uint32_t *source)
{
    *destination = *source;
}

uint32_t vertrix_copy_dword_full(uint32_t *destination, const uint32_t *source)
{
    if (!destination || !source)
    {
        return 0;
    }
    uint32_t value = *source;
    *destination = value;
    return value;
}

uint32_t vertrix_forward_call(const VertrixCalls *calls, uint32_t target)
{
    return vertrix_call(calls, target, 0, 0, 0, 0, 0);
}

uint32_t vertrix_forward_registers(const VertrixCalls *calls, uint32_t target, uint32_t eax,
                                   uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return vertrix_call(calls, target, eax, edx, ebx, ecx, 0);
}

uint32_t vertrix_list_reset_calls(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                  uint32_t ebx, uint32_t ecx)
{
    vertrix_call(calls, 0x475af0, eax, edx, ebx, ecx, 0);
    vertrix_call(calls, 0x475790, eax + 4, 0, 0, 0, 0);
    return vertrix_call(calls, 0x4759e0, eax, 0, 0, 0, 0);
}

uint32_t vertrix_list_push_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t stack)
{
    return vertrix_call(calls, 0x475790, eax + 4, (uint32_t)(int32_t)(int8_t)(edx & BYTE_MASK), 0,
                        0, stack);
}

uint32_t vertrix_slot_store_call(const VertrixCalls *calls, uint32_t table, uint32_t index,
                                 uint32_t second, uint32_t third, uint32_t stack)
{
    uint32_t slot = index & 0xffff;
    return vertrix_call(calls, 0x475da0, table + ((slot * 3) << VERTRIX_CALL_SLOT_STRIDE_SHIFT),
                        second, third, stack, 0);
}

uint32_t vertrix_two_codes_call(const VertrixCalls *calls, uint32_t eax)
{
    vertrix_call(calls, 0x476140, eax, 0x7a, 0, eax, 0);
    return vertrix_call(calls, 0x476140, eax, 0x7b, 0, eax, 0);
}

uint32_t vertrix_flagged_call(const VertrixCalls *calls, uint32_t first_flag, uint32_t second_flag,
                              uint32_t eax)
{
    if (first_flag != 1)
    {
        return eax;
    }
    return vertrix_call(calls, 0x40ee60, second_flag == 1 ? eax : 0, first_flag, 0, 0, 0);
}

uint32_t vertrix_checked_calls(const VertrixCalls *calls, uint32_t eax)
{
    if (vertrix_call(calls, 0x47e7d0, eax, 0, 0, eax, 0) != 1)
    {
        return 0;
    }
    return vertrix_call(calls, 0x47fd70, eax, 0x51698c, 0, eax, 0) == 1;
}

uint32_t vertrix_flag_pair_call(const VertrixCalls *calls, uint32_t eax)
{
    return vertrix_call(calls, 0x48a930, eax, 0, 1, 2, 0);
}

uint32_t vertrix_string_append_calls(const VertrixCalls *calls, uint32_t eax, const char *string,
                                     uint32_t ebx)
{
    uint32_t length = 0;
    while (string[length] != 0)
    {
        ++length;
    }
    vertrix_call(calls, 0x4ca370, eax, 0x5109ce, ebx, length, 0);
    vertrix_call(calls, 0x4ca600, eax, ebx + length, ebx, length, 0);
    return 1;
}

void vertrix_copy_global16(uint8_t *destination, const uint8_t *source)
{
    for (size_t i = 0; i < 16; ++i)
    {
        destination[i] = source[i];
    }
}

uint32_t vertrix_global_discard_call(const VertrixCalls *calls, uint32_t global)
{
    vertrix_call(calls, 0x4e7eb0, global, 0, 0, 0, 0);
    return 0;
}

uint32_t vertrix_global_pair_call(const VertrixCalls *calls, uint32_t global, uint32_t eax,
                                  uint32_t edx)
{
    vertrix_call(calls, 0x4ebce8, global, eax, edx, global, 0);
    return 0;
}

uint32_t vertrix_global_call(const VertrixCalls *calls, uint32_t global)
{
    return vertrix_call(calls, 0x4ebe60, global, 0, 0, 0, 0);
}

uint32_t vertrix_module_reset_calls(const VertrixCalls *calls, uint32_t marker)
{
    if (marker != 0xffff)
    {
        return 3;
    }
    vertrix_call(calls, 0x40a890, 0x4f76d8, 0, 0, 0, 0);
    vertrix_call(calls, 0x40a890, 0x4f76f8, 0, 0, 0, 0);
    vertrix_call(calls, 0x40a890, 0x4f6514, 0, 0, 0, 0);
    vertrix_call(calls, 0x40a890, 0x4f6468, 0, 0, 0, 0);
    return vertrix_call(calls, 0x40a800, 0, 0, 0, 0, 0);
}

uint32_t vertrix_edx_to_eax_call(const VertrixCalls *calls, uint32_t target, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx)
{
    return vertrix_call(calls, target, edx, edx, ebx, ecx, 0);
}

uint32_t vertrix_return_ebx(uint32_t ebx)
{
    return ebx;
}

uint32_t vertrix_return_zero(void)
{
    return 0;
}

uint32_t vertrix_indexed_resource_call(const VertrixCalls *calls, uint32_t base, uint32_t eax,
                                       uint32_t edx, uint32_t ebx)
{
    if (edx == 0)
    {
        return eax;
    }
    return vertrix_call(calls, 0x487640, base + GRID_COLUMN_STRIDE * eax, edx, ebx, 4 * eax, 0);
}

uint32_t vertrix_grid_array_call(const VertrixCalls *calls, uint32_t row, uint32_t column,
                                 uint32_t ebx)
{
    uint32_t cell = VERTRIX_CALL_GRID_BASE + GRID_ROW_STRIDE * row + GRID_COLUMN_STRIDE * column;
    return vertrix_call(calls, 0x487710, cell, ebx, ebx, column, 0);
}

uint32_t vertrix_slot_table_reset(const VertrixCalls *calls, uint32_t table)
{
    for (uint32_t i = 0; i < SLOT_COUNT; ++i)
    {
        vertrix_list_reset_calls(calls, table + SLOT_SIZE * i, i + 1, 0, table);
    }
    return SLOT_COUNT;
}

uint32_t vertrix_two_step_call(const VertrixCalls *calls, uint32_t eax)
{
    uint32_t result = vertrix_call(calls, 0x40aca0, eax, eax, 0, 0, 0);
    vertrix_call(calls, 0x4ea190, eax, eax, 0, result, 0);
    return result;
}

uint32_t vertrix_read_global(const uint32_t *global)
{
    return *global;
}

uint32_t vertrix_index_sweep_call(const VertrixCalls *calls, uint32_t target, uint32_t object)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < SLOT_COUNT; ++i)
    {
        result = vertrix_call(calls, target, object, i, i, object, 0);
    }
    return result;
}

uint32_t vertrix_neighbour_calls(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                 uint32_t ebx, uint32_t ecx)
{
    vertrix_call(calls, 0x479d70, eax, edx, ebx, ecx + 1, 0);
    vertrix_call(calls, 0x479d70, eax, edx, ebx, ecx - 1, 0);
    vertrix_call(calls, 0x479d70, eax, edx, ebx - 1, ecx + 1, 0);
    return vertrix_call(calls, 0x479d70, eax, edx, ebx + 1, ecx - 1, 0);
}

uint32_t vertrix_fixed_codes_call(const VertrixCalls *calls, uint32_t object)
{
    static const uint8_t first[] = {0x74, 0x75, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3};
    static const uint8_t second[] = {0x70, 0x71, 0x72, 0x73};
    uint32_t result = 0;
    for (size_t i = 0; i < sizeof first; ++i)
    {
        result = vertrix_call(calls, 0x476120, object, first[i], 0, object, 0);
    }
    for (size_t i = 0; i < sizeof second; ++i)
    {
        result = vertrix_call(calls, 0x476140, object, second[i], 0, object, 0);
    }
    return result;
}

uint32_t vertrix_slot_table_switch(const VertrixCalls *calls, uint32_t table, uint32_t mode,
                                   uint32_t *current)
{
    if (mode == *current)
    {
        return table;
    }
    *current = mode;
    vertrix_call(calls, 0x4759e0, 0x55364c, mode, 0, table, 0);
    return vertrix_slot_table_reset(calls, table);
}

uint32_t vertrix_clear_each_call(const VertrixCalls *calls, uint32_t items[76], uint32_t ebx)
{
    uint32_t result = 0;
    for (uint32_t i = 0; i < 76; ++i)
    {
        result = vertrix_call(calls, 0x482b30, items[i], 4 * (i + 1), ebx, 0, 0);
        items[i] = 0;
    }
    return result;
}

uint32_t vertrix_guarded_call(const VertrixCalls *calls, uint32_t flag, uint32_t guard,
                              uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                              uint32_t ecx)
{
    if (flag != 0)
    {
        return eax;
    }
    if (guard != 0)
    {
        return guard;
    }
    return vertrix_call(calls, target, eax, edx, ebx, ecx, 0);
}

uint32_t vertrix_resource_pair_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                    uint32_t ecx, uint32_t first_dword)
{
    uint32_t entry = vertrix_call(calls, 0x4877f0, 0x544a6c, eax, 4, ecx, 0);
    vertrix_call(calls, 0x47cd60, edx, first_dword, 4, entry, 0);
    return vertrix_call(calls, 0x483ed0, entry, 0x5b9c60, 4, entry, 0);
}

uint32_t vertrix_mode_switch_call(const VertrixCalls *calls, uint32_t frame, uint32_t *current,
                                  uint32_t mode, uint32_t ebx, uint32_t ecx)
{
    uint32_t local;
    uint32_t result;
    if (mode == *current)
    {
        return mode;
    }
    result = vertrix_calln(calls, 0x40ef40, frame - 8, mode, ebx, ecx, NULL, 0, &local);
    *current = mode;
    if (mode == 1 && local == 0)
    {
        return vertrix_call(calls, 0x40ede0, result, mode, ebx, ecx, 0);
    }
    if (mode != 1 && local == 1)
    {
        return vertrix_call(calls, 0x40ee30, result, mode, ebx, ecx, 0);
    }
    return result;
}

enum
{
    FIND_CALL = 0x4d9060,
    FIND_LOCAL = 0x120,
    FIND_LOCAL_SIZE = 0x124,
    FIND_ATTRIBUTES_OFFSET = 0x10,
    FIND_FIELD_OFFSET = 0xc
};

static uint32_t find_call(const VertrixCalls *calls, uint32_t frame, uint32_t local, uint32_t path,
                          uint32_t *stored)
{
    uint32_t stack[2] = {path, frame - local};
    return vertrix_calln(calls, FIND_CALL, path, frame - local, 0, 0, stack, 2, stored);
}

uint32_t vertrix_find_attribute_flag(const VertrixCalls *calls, uint32_t frame, uint32_t path)
{
    uint32_t attributes;
    find_call(calls, frame, FIND_LOCAL, path, &attributes);
    return attributes & 1;
}

uint32_t vertrix_find_succeeded(const VertrixCalls *calls, uint32_t frame, uint32_t path)
{
    return find_call(calls, frame, FIND_LOCAL, path, NULL) == 1;
}

uint32_t vertrix_find_size_field(const VertrixCalls *calls, uint32_t frame, uint32_t path)
{
    uint32_t field;
    if (find_call(calls, frame, FIND_LOCAL_SIZE, path, &field) == 0)
    {
        return 0;
    }
    return field;
}

uint32_t vertrix_scratch_pair_call(const VertrixCalls *calls, uint32_t frame, uint32_t eax,
                                   uint32_t edx, uint32_t ebx)
{
    uint32_t scratch = vertrix_call(calls, 0x4ec1a0, frame - 0xc, edx, ebx, eax, 0);
    return vertrix_call(calls, 0x482640, eax, scratch, ebx, eax, 0);
}

uint32_t vertrix_offset_pair_call(const VertrixCalls *calls, uint32_t frame, uint32_t flag,
                                  uint32_t eax, uint32_t edx)
{
    VertrixCallSite site = {0x40ef00, frame - 0x10, frame - 0xc, eax, edx, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t result;
    if (flag != 1)
    {
        return eax;
    }
    result = calls->call(&site, calls->context);
    if (result != 0)
    {
        return result;
    }
    return vertrix_call(calls, 0x40eea0, site.out_ebx + eax, site.out_ecx + edx, eax, edx, 0);
}

uint32_t vertrix_offset_pair_clamp_call(const VertrixCalls *calls, uint32_t frame, uint32_t flag,
                                        uint32_t eax, uint32_t edx)
{
    VertrixCallSite site = {0x40ef00, frame - 0x10, frame - 0xc, edx, eax, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t result;
    int32_t first, second;
    if (flag != 1)
    {
        return eax;
    }
    result = calls->call(&site, calls->context);
    if (result != 0)
    {
        return result;
    }
    first = (int32_t)(site.out_ebx - eax);
    second = (int32_t)(site.out_ecx - edx);
    if (second < 0)
    {
        first--;
        second = 0;
    }
    if (first < 0)
    {
        first = 0;
    }
    return vertrix_call(calls, 0x40eea0, (uint32_t)first, (uint32_t)second, edx, eax, 0);
}

uint32_t vertrix_slot_create_call(const VertrixCalls *calls, uint32_t mode, uint32_t ebx,
                                  uint32_t ecx, uint32_t *slot)
{
    uint32_t created;
    vertrix_call(calls, 0x472d50, mode, mode, ebx, ecx, 0);
    created = vertrix_call(calls, 0x4ca000, 0x15c, mode, ebx, ecx, 0);
    if (created != 0)
    {
        created = vertrix_call(calls, 0x4abd70, created, mode, ebx, ecx, 0);
    }
    *slot = created;
    if (mode != 1)
    {
        return vertrix_call(calls, 0x4ac8f0, created, 0x45c2b0, ebx, ecx, 0);
    }
    vertrix_call(calls, 0x4ac8f0, created, 0x45c250, ebx, ecx, 0);
    return vertrix_call(calls, 0x4ac7d0, *slot, 0x1f40, ebx, ecx, 0);
}

uint32_t vertrix_slot_search_call(const VertrixCalls *calls, uint32_t flag, uint32_t object,
                                  uint32_t edx, uint32_t ebx, uint32_t *cleared)
{
    if (edx != 0)
    {
        *cleared = 0;
    }
    if (flag == 1)
    {
        return vertrix_call(calls, 0x475c80, 0x55364c, edx, ebx, object, 0);
    }
    for (uint32_t index = 0; index < 0x100; ++index)
    {
        if (vertrix_call(calls, 0x476480, object, index, index, object, 0) == 1)
        {
            return index;
        }
    }
    return 0;
}

uint32_t vertrix_text_append_call(const VertrixCalls *calls, uint32_t edx, uint32_t ecx,
                                  char *destination, const char *appended)
{
    uint32_t result = vertrix_call(calls, 0x4776a0, edx, 0x5560b0, 0xc, ecx, 0);
    size_t length = 0;
    while (destination[length] != 0)
    {
        ++length;
    }
    do
    {
        destination[length] = *appended;
        ++length;
    } while (*appended++ != 0);
    return result & ~0xffu;
}

uint32_t vertrix_flagged_table_call(const VertrixCalls *calls, uint32_t flags, int32_t count,
                                    const uint32_t *handles, uint32_t ecx)
{
    if ((flags & 0x80) == 0)
    {
        return 3;
    }
    for (int32_t i = 0; i < count; ++i)
    {
        vertrix_call(calls, 0x40add0, handles[i], (uint32_t)i, 4 * (uint32_t)i, ecx, 0);
        vertrix_call(calls, 0x40ad50, handles[i], (uint32_t)i, 4 * (uint32_t)i, ecx, 0);
    }
    vertrix_call(calls, 0x4eb5c0, 0x53043c, 0, 0x1744, ecx, 0);
    vertrix_call(calls, 0x40ac10, 0, 0, 0x1744, ecx, 0);
    vertrix_call(calls, 0x40ac20, 0x7d, 0, 0x1744, ecx, 0);
    return 0;
}

void vertrix_matcher_reset(VertrixMatcher *matcher)
{
    matcher->index = 0;
}

uint32_t vertrix_matcher_reset_full(VertrixMatcher *matcher, uint32_t eax)
{
    if (!matcher)
    {
        return 0;
    }
    vertrix_matcher_reset(matcher);
    return eax;
}

uint32_t vertrix_matcher_feed(const VertrixCalls *calls, VertrixMatcher *matcher, uint32_t handle,
                              uint8_t first, uint32_t ebx, uint32_t ecx)
{
    vertrix_call(calls, 0x4ca710, handle, handle, ebx, ecx, 0);
    if (first == matcher->pattern[matcher->index])
    {
        ++matcher->index;
    }
    else
    {
        vertrix_matcher_reset(matcher);
        if (first == matcher->pattern[matcher->index])
        {
            ++matcher->index;
        }
    }
    if (matcher->index != matcher->length)
    {
        return 0;
    }
    vertrix_matcher_reset(matcher);
    return 1;
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(uint16_t)value;
}

void vertrix_corner_transform_call(const VertrixCalls *calls, uint32_t frame, uint32_t al,
                                   uint32_t edi, uint32_t bx, uint32_t esi,
                                   const uint32_t arguments[3], VertrixTransformOut *out)
{
    VertrixCallSite first = {0x440610,
                             (uint32_t)(int32_t)(int8_t)al,
                             arguments[1],
                             arguments[2] & BYTE_MASK,
                             frame - 0x20,
                             frame - 0x1c,
                             0,
                             0,
                             0,
                             0,
                             {0},
                             0};
    VertrixCallSite second = {0x440990, frame - 0x18, frame - 0x14, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
    calls->call(&first, calls->context);
    second.ebx = first.out_ecx;
    second.ecx = first.out_value;
    second.stack = sign16(edi);
    second.stack_next = sign16(bx);
    second.stack_third = sign16(esi);
    second.stack_rest[0] = sign16(arguments[0]);
    calls->call(&second, calls->context);
    out->first_word = second.out_ebx & 0xffff;
    out->second_word = second.out_ecx & 0xffff;
    out->first_dword = first.out_ecx;
    out->second_dword = first.out_value;
}

uint32_t vertrix_object_scale_call(const VertrixCalls *calls, uint32_t object, uint32_t scale_c0,
                                   uint32_t scale_bc, uint32_t edx, uint32_t ebx)
{
    uint32_t first = vertrix_call(calls, 0x4d74a6, scale_c0, edx, ebx, object, 0);
    edx = first == 0 ? 0x3f800000 : first;
    first = vertrix_call(calls, 0x4d74a6, scale_bc, edx, ebx, object, 0);
    return vertrix_call(calls, 0x4d81fe, first, edx, ebx, object, 0);
}

uint32_t vertrix_step_toward_call(const VertrixCalls *calls, uint32_t ebx, uint32_t ecx,
                                  uint32_t edx, uint32_t argument)
{
    uint32_t scaled;
    uint32_t amount;
    if ((int32_t)ebx == (int32_t)ecx)
    {
        return ebx;
    }
    scaled = vertrix_call(calls, 0x4d74d1, argument, edx, ebx, ecx, 0);
    amount = vertrix_call(calls, 0x4d8177, edx, scaled, ebx, ecx, 0);
    amount = vertrix_call(calls, 0x4d67a8, amount, scaled, ebx, ecx, 0);
    if ((int32_t)ebx > (int32_t)ecx)
    {
        ebx -= amount;
        return (int32_t)ebx < (int32_t)ecx ? ecx : ebx;
    }
    ebx += amount;
    return (int32_t)ebx > (int32_t)ecx ? ecx : ebx;
}

uint32_t vertrix_curve_table_build(const VertrixCalls *calls, uint32_t mode, uint32_t step,
                                   uint32_t ebx, uint32_t ecx,
                                   uint32_t table[VERTRIX_CURVE_ENTRIES])
{
    uint32_t edx = 0x3f700000;
    uint32_t eax;
    uint32_t base;
    uint32_t value = step;
    if (mode < 1 || mode > 5)
    {
        return 2;
    }
    if (mode != 1 || step > 0x100)
    {
        return 0;
    }
    table[0] = 0xffffd8f0;
    base = vertrix_call(calls, 0x4c9e2f, 0, edx, ebx, ecx, 0);
    for (uint32_t i = 1; i < VERTRIX_CURVE_ENTRIES; ++i)
    {
        eax = value >> 6;
        if (eax != 0)
        {
            eax = vertrix_call(calls, 0x4d6768, eax, edx, ebx, ecx, 0);
            eax = vertrix_call(calls, 0x4db507, eax, edx, 0, 0x3f700000, 0);
            eax = vertrix_call(calls, 0x4c9e2f, eax, edx, 0, 0x3f700000, 0);
            eax = vertrix_call(calls, 0x4db507, eax, edx, 0, 0xc09f4000, 0);
            eax = vertrix_call(calls, 0x4eb652, eax, edx, base, 0x3f700000, 0);
            ebx = base;
            ecx = 0x3f700000;
        }
        else
        {
            edx = 0xc0c38800;
        }
        table[i] = vertrix_call(calls, 0x4eb892, eax, edx, ebx, ecx, 0);
        value += step;
    }
    return 0;
}

enum
{
    DISPATCH_FIRST = 0x418820,
    DISPATCH_PROBE = 0x4177b0,
    DISPATCH_EDX_FIRST = 0x41b5e0,
    DISPATCH_EDX_SECOND = 0x41acc0,
    DISPATCH_EBX = 0x514088,
    DISPATCH_NONE = 0xff
};

uint32_t vertrix_gate_dispatch_call(const VertrixCalls *calls, uint32_t object, uint32_t gate,
                                    uint32_t value, uint32_t *stored)
{
    uint32_t probe;
    vertrix_call(calls, DISPATCH_FIRST, object, DISPATCH_EDX_FIRST, DISPATCH_EBX, object, 0);
    if (gate != 0)
    {
        return 0;
    }
    probe = vertrix_call(calls, DISPATCH_PROBE, value, DISPATCH_EDX_FIRST, DISPATCH_EBX, object, 0);
    if ((probe & 0xff) == DISPATCH_NONE)
    {
        return 0;
    }
    *stored = (uint32_t)(int32_t)(int8_t)(probe & 0xff);
    return vertrix_call(calls, DISPATCH_FIRST, object, DISPATCH_EDX_SECOND, DISPATCH_EBX, object,
                        0);
}

uint32_t vertrix_gate_dispatch_call_full(const VertrixCalls *calls, uint32_t object,
                                         uint32_t previous_exception, VertrixMemoryRead read,
                                         VertrixMemoryWrite write, void *context)
{
    if (!calls || !calls->call || !read || !write)
    {
        return 0;
    }
    vertrix_call(calls, DISPATCH_FIRST, object, DISPATCH_EDX_FIRST, DISPATCH_EBX, object, 0);
    uint32_t gate, value;
    if (!read(0x532a8c, 4, &gate, context))
    {
        return 0;
    }
    if (gate)
    {
        return previous_exception;
    }
    if (!read(0x532aa4, 4, &value, context))
    {
        return 0;
    }
    uint32_t probe =
        vertrix_call(calls, DISPATCH_PROBE, value, DISPATCH_EDX_FIRST, DISPATCH_EBX, object, 0);
    uint32_t byte = probe & 0xffu;
    if (byte == DISPATCH_NONE)
    {
        return previous_exception;
    }
    uint32_t stored = byte < 0x80u ? byte : byte | 0xffffff00u;
    if (!write(0x532ab4, 4, stored, context))
    {
        return 0;
    }
    vertrix_call(calls, DISPATCH_FIRST, object, DISPATCH_EDX_SECOND, DISPATCH_EBX, object, 0);
    return previous_exception;
}

enum
{
    NOTICE_PROBE = 0x47f9b0,
    NOTICE_TABLE = 0x5bb254,
    NOTICE_EDX = 0x4ec1ec,
    NOTICE_ECX = 0x513a2c,
    NOTICE_ASSIGN = 0x4ca280,
    NOTICE_APPLY = 0x4b76d0,
    NOTICE_RELEASE = 0x4ca210,
    NOTICE_LIST = 0x532c24,
    NOTICE_TEXT_SINGLE = 0x50d3c9,
    NOTICE_TEXT_FIRST = 0x50d3f4,
    NOTICE_TEXT_SECOND = 0x50d40d,
    NOTICE_LOCAL_SINGLE = 0x20,
    NOTICE_LOCAL_FIRST = 0x1c,
    NOTICE_LOCAL_SECOND = 0x18
};

static void notice_apply(const VertrixCalls *calls, uint32_t local, uint32_t text)
{
    uint32_t assigned = vertrix_call(calls, NOTICE_ASSIGN, local, text, 0, NOTICE_ECX, 0);
    vertrix_call(calls, NOTICE_APPLY, NOTICE_LIST, assigned, 0, NOTICE_ECX, 0);
    vertrix_call(calls, NOTICE_RELEASE, local, 0, 0, NOTICE_ECX, 0);
}

uint32_t vertrix_notice_call(const VertrixCalls *calls, uint32_t frame, uint32_t current,
                             uint32_t expected, uint32_t *flag)
{
    *flag = 1;
    if (current != expected)
    {
        return 0;
    }
    if (vertrix_call(calls, NOTICE_PROBE, NOTICE_TABLE, NOTICE_EDX, 0, NOTICE_ECX, 0) == 1)
    {
        notice_apply(calls, frame - NOTICE_LOCAL_SINGLE, NOTICE_TEXT_SINGLE);
        *flag = 1;
        return 0;
    }
    notice_apply(calls, frame - NOTICE_LOCAL_FIRST, NOTICE_TEXT_FIRST);
    notice_apply(calls, frame - NOTICE_LOCAL_SECOND, NOTICE_TEXT_SECOND);
    return 0;
}

uint32_t vertrix_notice_call_full(const VertrixCalls *calls, uint32_t frame,
                                  uint32_t previous_exception, VertrixMemoryRead read,
                                  VertrixMemoryWrite write, void *context)
{
    if (!calls || !calls->call || !read || !write)
    {
        return 0;
    }
    uint32_t current, expected;
    if (!read(0x532bf8, 4, &current, context) || !read(0x4f8160, 4, &expected, context) ||
        !write(0x532c40, 4, 1, context))
    {
        return 0;
    }
    if (current != expected)
    {
        return previous_exception;
    }
    if (vertrix_call(calls, NOTICE_PROBE, NOTICE_TABLE, NOTICE_EDX, 0, NOTICE_ECX, 0) == 1)
    {
        notice_apply(calls, frame - NOTICE_LOCAL_SINGLE, NOTICE_TEXT_SINGLE);
        if (!write(0x532c40, 4, 1, context))
        {
            return 0;
        }
        return previous_exception;
    }
    notice_apply(calls, frame - NOTICE_LOCAL_FIRST, NOTICE_TEXT_FIRST);
    notice_apply(calls, frame - NOTICE_LOCAL_SECOND, NOTICE_TEXT_SECOND);
    return previous_exception;
}
