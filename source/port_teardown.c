#include "port_teardown.h"

/* Object teardown and construction, script loading, the options scene exit and the choice grid
 * column pick. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* The guard record (0x4ec1ec, `guard`) of a frame routine at `record`. */
static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

/* Original 0x412130: the object's teardown by the flags dl: with bit 2 0x4ccb9f (0x5132f0) and
 * 0x4ca040; otherwise (guarded, 0x5132a0) its methods 0x5132e4 (+0x7b4), the 0x7a flags from
 * +0x5cc on set and, with bit 1, 0x4ca050. The object. */
uint32_t vertrix_port_object_teardown_412130(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t result;
    uint32_t offset;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x34u, object);
        port_set32(&port, ebp, -0x14u, 1);
        result = port_forward(&port, entry, 0x4ccb9f, object, 0x5132f0, flags, object);
        port_set32(&port, ebp, -0x14u, 0);
        port_forward(&port, entry, 0x4ca040, result, 0, flags, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0x7b4, 0x5132e4);
    guard_record(&port, ebp - 0x20, 0x5132a0);
    for (offset = 4; offset <= 0x1e8; offset += 4)
    {
        port_set32(&port, object + offset, 0x5c8, 1);
    }
    if ((flags & 2) == 0)
    {
        return port_return(&port, object, object + 0x1e8);
    }
    port_call_with(&port, 0x4ca050, object, object + 0x1e8, flags, object, 0x5132a0, 0, ebp);
    return port_return(&port, object, vertrix_lift_edx);
}

/* Original 0x412240 (guarded, 0x5132ac): a reader (0x4ca000 of 0x10 bytes, 0x488b10) that opens
 * (0x489040 gives 1) gives the object eax its data (0x412390) and is closed (its method +0x54);
 * any reader is then deleted (its method +4 with 2). */
uint32_t vertrix_port_object_read_412240(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t guard = 0x5132ac;
    uint32_t reader;
    uint32_t methods;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x28, guard);
    reader = port_call_with(&port, 0x4ca000, 0x10, entry->edx, guard, 0x4ec1ec, object, 0, ebp);
    if (reader != 0)
    {
        port_set32(&port, ebp, -0x14u, reader);
        port_set32(&port, ebp, -0x1cu, 1);
        reader =
            port_call_with(&port, 0x488b10, reader, vertrix_lift_edx, guard, 1, object, 0, ebp);
        port_set32(&port, ebp, -0x1cu, 0);
    }
    if (port_call_with(&port, 0x489040, reader, vertrix_lift_edx, reader, reader, object, 0, ebp) ==
        1)
    {
        port_call_with(&port, 0x412390, object, reader, reader, reader, object, 0, ebp);
        methods = port_u32(&port, reader, 0);
        port_call_with(&port, port_u32(&port, methods, 0x54), reader, methods, reader, reader,
                       object, 0, ebp);
    }
    if (reader != 0)
    {
        methods = port_u32(&port, reader, 0);
        port_call_with(&port, port_u32(&port, methods, 4), reader, 2, reader, methods, object, 0,
                       ebp);
    }
    return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
}

/* Original 0x416a80 (guarded, 0x513b9c): a script name eax other than 0x50d652 (0x4ccfe0) is
 * printed with 0x50d653 (0x4cdfb0) into a frame text (0x4ca070) loaded into 0x5bb254 (0x47faf0)
 * and released (0x4ca210). */
uint32_t vertrix_port_object_load_script_416a80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t name = entry->eax;
    uint32_t guard = 0x513b9c;
    uint32_t pushed[3];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x2c, guard);
    if (port_call_with(&port, 0x4ccfe0, name, 0x50d652, guard, name, 0, entry->edi, ebp) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
    }
    port_call_with(&port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, guard, name, 0, entry->edi, ebp);
    port_set32(&port, ebp, -0x20u, 1);
    pushed[0] = ebp - 0x18;
    pushed[1] = 0x50d653;
    pushed[2] = name;
    call_frame(&port, 0x4cdfb0, ebp - 0x18, vertrix_lift_edx, guard, name, 0, 1, ebp, pushed, 3);
    port_call_with(&port, 0x47faf0, 0x5bb254, port_u32(&port, ebp, -0x18u), guard, name, 0, 1, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    port_call_with(&port, 0x4ca210, ebp - 0x18, 0, guard, name, 0, 1, ebp);
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

/* Original 0x41fc70 (guarded, 0x514128): the options scene closes (0x41ab90, 0x41ac20, 0x41abe0,
 * 0x41ac40, 0x41ac70, 0x41a9e0), its lists and pictures are released (0x471a90, 0x4719e0,
 * 0x45f9f0, 0x45e740), a changed level (0x532bbc against 0x532aa0) sets 0x532b88, and the scene
 * moves to 0x421f10 (0x418840) and 0x41d5b0. */
uint32_t vertrix_port_scene_leave_options_41fc70(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    static const uint32_t closes[6] = {0x41ab90, 0x41ac20, 0x41abe0, 0x41ac40, 0x41ac70, 0x41a9e0};
    static const uint32_t releases[4] = {0x471a90, 0x4719e0, 0x45f9f0, 0x45e740};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t guard = 0x514128;
    uint32_t edx = 0x4ec1ec;
    uint32_t result = 0;
    unsigned k;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x24, guard);
    for (k = 0; k < 6; k++)
    {
        result = port_call_with(&port, closes[k], scene, edx, guard, scene, 0, entry->edi, ebp);
        edx = vertrix_lift_edx;
    }
    for (k = 0; k < 4; k++)
    {
        result = port_call_with(&port, releases[k], result, vertrix_lift_edx, guard, scene, 0,
                                entry->edi, ebp);
    }
    if (port_u32(&port, 0, 0x532bbc) != port_u32(&port, 0, 0x532aa0))
    {
        port_set32(&port, 0, 0x532b88, 1);
    }
    port_call_with(&port, 0x418840, scene, 0x421f10, guard, scene, 0, entry->edi, ebp);
    port_call_with(&port, 0x41d5b0, scene, vertrix_lift_edx, guard, scene, 0, entry->edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

/* Original 0x42a080: the columns of the grid row dl (+0x1cc, 16 bytes a row) marked 1 are
 * gathered, shuffled ten times (0x4826c0 on 0x598d30) and one picked at random into the byte ebx.
 * 1, or 0 when none is marked. */
uint32_t vertrix_port_choice_grid_pick_column_42a080(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t row = entry->edx & 0xff;
    uint32_t count = 0;
    uint32_t column;
    uint32_t pass;
    uint32_t pick;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set8(&port, ebp, -0x10u, row);
    port_set32(&port, ebp, -0x14u, entry->ebx);
    for (column = 0; column < 4; column++)
    {
        uint32_t mark = port_u32(&port, (row << 4) + grid + column * 4, 0x1cc);
        if (mark == 1)
        {
            port_set8(&port, ebp - 0x18 + count, 0, column);
            count += mark;
        }
    }
    if (count == 0)
    {
        return port_return(&port, 0, (row << 4) + grid);
    }
    for (pass = 0; pass < 0xa; pass++)
    {
        for (column = 0; column < count;)
        {
            uint32_t a;
            uint32_t b;
            pick = port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, count, column, pass,
                                  0x598d30, ebp) &
                   0xffff;
            a = port_u8(&port, ebp - 0x18 + pick, 0);
            b = port_u8(&port, ebp - 0x18 + column, 0);
            column++;
            port_set8(&port, ebp - 0x18 + pick, 0, b);
            port_set8(&port, ebp - 0x18 + column, -1u, a);
        }
    }
    pick = port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, count, count, pass, 0x598d30,
                          ebp) &
           0xffff;
    port_set8(&port, port_u32(&port, ebp, -0x14u), 0, port_u8(&port, ebp - 0x18 + pick, 0));
    return port_return(&port, 1, port_u32(&port, ebp, -0x14u));
}

/* Original 0x42a310 (guarded, 0x514660): an actor (0x4abd70) made the choice grid: methods
 * 0x5146f4 (+0x158), two lists of 3 (0x4b2290 at +0x15c and +0x170), +0x168, +0x17c, +0x180 and
 * +0x184 0, then 0x42a940 and 0x42a950. The grid. */
uint32_t vertrix_port_choice_grid_construct_42a310(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t guard = 0x514660;
    uint32_t grid;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x34, guard);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, entry->eax);
    grid = port_call_with(&port, 0x4abd70, entry->eax, 0x4ec1ec, guard, entry->eax, 0, 1, ebp);
    port_set32(&port, ebp, -0x28u, 1);
    port_set32(&port, grid, 0x158, 0x5146f4);
    port_call_with(&port, 0x4b2290, grid + 0x15c, 3, guard, grid, 0, 1, ebp);
    port_call_with(&port, 0x4b2290, grid + 0x170, 3, guard, grid, 0, 1, ebp);
    port_set32(&port, grid, 0x168, 0);
    port_set32(&port, grid, 0x17c, 0);
    port_set32(&port, grid, 0x180, 0);
    port_set32(&port, grid, 0x184, 0);
    port_call_with(&port, 0x42a940, grid, vertrix_lift_edx, guard, grid, 0, 1, ebp);
    port_call_with(&port, 0x42a950, grid, vertrix_lift_edx, guard, grid, 0, 1, ebp);
    return port_return(&port, grid, entry->edx);
}

/* Original 0x42a3c0: the choice grid's teardown by the flags dl: with bit 2 0x4ccb9f (0x514710)
 * and 0x4ca040; otherwise (guarded, 0x51466c) its methods 0x5146f4 (+0x158), 0x42a4a0, 0x42a480,
 * 0x4ac130 with 1 and, with bit 1, 0x4ca050 on what it gives. The grid, or that. */
uint32_t vertrix_port_choice_grid_teardown_42a3c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t grid = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t guard = 0x51466c;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if ((flags & 4) != 0)
    {
        port_set32(&port, ebp, -0x44u, grid);
        port_set32(&port, ebp, -0x24u, 1);
        result = port_call_with(&port, 0x4ccb9f, grid, 0x514710, 1, grid, 0, entry->edi, ebp);
        port_set32(&port, ebp, -0x24u, 0);
        port_call_with(&port, 0x4ca040, result, vertrix_lift_edx, 1, grid, 0, entry->edi, ebp);
        return port_return(&port, grid, vertrix_lift_edx);
    }
    port_set32(&port, grid, 0x158, 0x5146f4);
    port_set32(&port, ebp, -0x1cu, grid);
    port_set8(&port, ebp, -0x18u, flags);
    guard_record(&port, ebp - 0x30, guard);
    port_set32(&port, ebp, -0x24u, 3);
    port_call_with(&port, 0x42a4a0, grid, 0x4ec1ec, flags, grid, guard, 3, ebp);
    port_call_with(&port, 0x42a480, grid, vertrix_lift_edx, flags, grid, guard, 3, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call_with(&port, 0x4ac130, grid, 1, flags, grid, guard, 3, ebp);
    port_set32(&port, ebp, -0x24u, 0);
    if ((flags & 2) == 0)
    {
        return port_return(&port, result, 0);
    }
    port_call_with(&port, 0x4ca050, result, 0, flags, result, guard, 3, ebp);
    return port_return(&port, result, vertrix_lift_edx);
}
