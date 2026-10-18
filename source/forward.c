#include "forward.h"

/* Small routines that forward to others: tail calls, calls with fixed arguments and the
 * method calls of objects. */

/* A call handing the callee the caller's esi, edi and ebp unchanged. */
static uint32_t forward(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                        uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return port_call_with(port, target, eax, edx, ebx, ecx, entry->esi, entry->edi, entry->ebp);
}

/* The same with stack arguments, the nearest to the stack pointer first. */
static uint32_t forward_stack(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                              uint32_t edx, uint32_t ebx, uint32_t ecx, const uint32_t *stack,
                              unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, entry->esi, entry->edi, entry->ebp,
                               stack, count);
}

/* Original 0x40add0: Call the routine at [0x52f068] with eax less 1. */
uint32_t vertrix_port_call_global_52f068_40add0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x52f068), entry->eax - 1, entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x40ade0: Call the routine at [0x52f06c] with eax less 1. */
uint32_t vertrix_port_call_global_52f06c_40ade0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x52f06c), entry->eax - 1, entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x40ae60: Call the routine at [0x52f08c] with eax less 1. */
uint32_t vertrix_port_call_global_52f08c_40ae60(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x52f08c), entry->eax - 1, entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x40b080: Call method +8 of the object (this pushed), then the import 0x4f1768; the
 * method's result. */
uint32_t vertrix_port_object_method_8_import_40b080(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t self[1];
    port_open(&port, calls, services, globals, entry);
    self[0] = entry->eax;
    r = forward_stack(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 8), entry->eax,
                      entry->edx, port_u32(&port, entry->eax, 0), entry->ecx, self, 1);
    forward(&port, entry, 0x4f1768, r, vertrix_lift_edx, r, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x40b660: Call method +8 of the object (this pushed), then the import 0x4f1768; the
 * method's result. */
uint32_t vertrix_port_object_method_8_import_40b660(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t self[1];
    port_open(&port, calls, services, globals, entry);
    self[0] = entry->eax;
    r = forward_stack(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 8), entry->eax,
                      entry->edx, port_u32(&port, entry->eax, 0), entry->ecx, self, 1);
    forward(&port, entry, 0x4f1768, r, vertrix_lift_edx, r, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x40b680: Call 0x4eb5e0 with edx 0x4f6470 and ebx 0x24; zero. */
uint32_t vertrix_port_call_4eb5e0_40b680(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4eb5e0, entry->eax, 0x4f6470, 0x24, entry->ecx);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x40c1e0: Call 0x4e7eb0 on the object at [0x52f90c]; zero. */
uint32_t vertrix_port_global_discard_call_40c1e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4e7eb0, port_u32(&port, 0, 0x52f90c), entry->edx, entry->ebx,
            entry->ecx);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x40c1f0: Call 0x4ebce8 on the object at [0x52f90c] with eax and edx in edx and ebx;
 * zero. */
uint32_t vertrix_port_global_pair_call_40c1f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4ebce8, port_u32(&port, 0, 0x52f90c), entry->eax, entry->edx,
            port_u32(&port, 0, 0x52f90c));
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x40c210: Tail call of 0x4ebe60 on the object at [0x52f90c]. */
uint32_t vertrix_port_global_call_40c210(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ebe60, port_u32(&port, 0, 0x52f90c), entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x415ef0: The matching value of 0x415eb0 for eax over the 3 entries at 0x532afc (names
 * at 0x4f8128), kept at 0x532b50. */
uint32_t vertrix_port_table_value_532b50_415ef0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532afc, 0x4f8128, 3);
    port_set32(&port, 0, 0x532b50, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x415f10: The matching value of 0x415eb0 for eax over the 3 entries at 0x532c44 (names
 * at 0x4f80e4), kept at 0x532bd4. */
uint32_t vertrix_port_table_value_532bd4_415f10(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532c44, 0x4f80e4, 3);
    port_set32(&port, 0, 0x532bd4, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x415f30: The matching value of 0x415eb0 for eax over the 10 entries at 0x532c50 (names
 * at 0x4f80f0), kept at 0x532bd8. */
uint32_t vertrix_port_table_value_532bd8_415f30(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532c50, 0x4f80f0, 10);
    port_set32(&port, 0, 0x532bd8, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x415f50: The matching value of 0x415eb0 for eax over the 2 entries at 0x532c78 (names
 * at 0x4f8118), kept at 0x532bdc. */
uint32_t vertrix_port_table_value_532bdc_415f50(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532c78, 0x4f8118, 2);
    port_set32(&port, 0, 0x532bdc, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x415f70: The matching value of 0x415eb0 for eax over the 2 entries at 0x532c80 (names
 * at 0x4f8120), kept at 0x532be0. */
uint32_t vertrix_port_table_value_532be0_415f70(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532c80, 0x4f8120, 2);
    port_set32(&port, 0, 0x532be0, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x415f90: The matching value of 0x415eb0 for eax over the 2 entries at 0x532c88 (names
 * at 0x4f8168), kept at 0x532be4. */
uint32_t vertrix_port_table_value_532be4_415f90(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532c88, 0x4f8168, 2);
    port_set32(&port, 0, 0x532be4, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416b30: The matching value of 0x415eb0 for eax over the 3 entries at 0x532ab8 (names
 * at 0x4f80e4), kept at 0x532b54. */
uint32_t vertrix_port_table_value_532b54_416b30(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532ab8, 0x4f80e4, 3);
    port_set32(&port, 0, 0x532b54, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416b50: The matching value of 0x415eb0 for eax over the 10 entries at 0x532ac4 (names
 * at 0x4f80f0), kept at 0x532b58. */
uint32_t vertrix_port_table_value_532b58_416b50(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532ac4, 0x4f80f0, 10);
    port_set32(&port, 0, 0x532b58, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416b70: The matching value of 0x415eb0 for eax over the 2 entries at 0x532aec (names
 * at 0x4f8118), kept at 0x532b5c. */
uint32_t vertrix_port_table_value_532b5c_416b70(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532aec, 0x4f8118, 2);
    port_set32(&port, 0, 0x532b5c, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416b90: The matching value of 0x415eb0 for eax over the 2 entries at 0x532af4 (names
 * at 0x4f8120), kept at 0x532b60. */
uint32_t vertrix_port_table_value_532b60_416b90(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532af4, 0x4f8120, 2);
    port_set32(&port, 0, 0x532b60, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416bb0: The matching value of 0x415eb0 for eax over the 5 entries at 0x532b20 (names
 * at 0x4f8134), kept at 0x532b68. */
uint32_t vertrix_port_table_value_532b68_416bb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532b20, 0x4f8134, 5);
    port_set32(&port, 0, 0x532b68, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416bd0: The matching value of 0x415eb0 for eax over the 6 entries at 0x532b08 (names
 * at 0x4f8148), kept at 0x532b80. */
uint32_t vertrix_port_table_value_532b80_416bd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532b08, 0x4f8148, 6);
    port_set32(&port, 0, 0x532b80, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416bf0: The matching value of 0x415eb0 for eax over the 6 entries at 0x532b08 (names
 * at 0x4f8148), kept at 0x532b84. */
uint32_t vertrix_port_table_value_532b84_416bf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532b08, 0x4f8148, 6);
    port_set32(&port, 0, 0x532b84, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x417130: The matching value of 0x415eb0 for eax over the 76 entries at 0x532d8c (names
 * at 0x4f81d0), kept at 0x532bac. */
uint32_t vertrix_port_table_value_532bac_417130(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415eb0, entry->eax, 0x532d8c, 0x4f81d0, 76);
    port_set32(&port, 0, 0x532bac, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x416970: Copy [0x4f7bb4] to 0x532a50, then 0x417260 and 0x417290 on the object at
 * [0x4f819c]. */
uint32_t vertrix_port_settings_refresh_416970(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, 0x532a50, port_u32(&port, 0, 0x4f7bb4));
    forward(&port, entry, 0x417260, port_u32(&port, 0, 0x4f819c), entry->edx, entry->ebx,
            entry->ecx);
    r = forward(&port, entry, 0x417290, port_u32(&port, 0, 0x4f819c), vertrix_lift_edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x418100: Keep the result of 0x4ce080 at 0x532bfc. */
uint32_t vertrix_port_keep_4ce080_418100(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ce080, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x532bfc, r);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x418110: Whether the import 0x4f1cfc fails (returns zero) for the handle at [0x5bb490]
 * and 0. */
uint32_t vertrix_port_import_failed_5bb490_418110(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, 0, 0x5bb490);
    pushed[1] = 0;
    r = forward_stack(&port, entry, 0x4f1cfc, entry->eax, pushed[0], entry->ebx, entry->ecx, pushed,
                      2) == 0;
    return port_return(&port, r, entry->edx);
}

/* Original 0x418130: Whether the import 0x4f1cfc fails (returns zero) for the handle at [0x5bb498]
 * and 0. */
uint32_t vertrix_port_import_failed_5bb498_418130(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, 0, 0x5bb498);
    pushed[1] = 0;
    r = forward_stack(&port, entry, 0x4f1cfc, entry->eax, pushed[0], entry->ebx, entry->ecx, pushed,
                      2) == 0;
    return port_return(&port, r, entry->edx);
}

/* Original 0x418ae0: Call 0x415e10, 0x4788f0 and 0x475510 in turn. */
uint32_t vertrix_port_call_three_418ae0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x415e10, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4788f0, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x475510, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x419f60: Tail call of 0x4d4d10. */
uint32_t vertrix_port_forward_4d4d10_419f60(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4d4d10, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x41c400: Tail call of 0x41a010. */
uint32_t vertrix_port_forward_41a010_41c400(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x41a010, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x42b300: Tail call of 0x42b290. */
uint32_t vertrix_port_forward_42b290_42b300(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42b290, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43bd80: Tail call of 0x43bbf0. */
uint32_t vertrix_port_forward_43bbf0_43bd80(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43bbf0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43d4b0: Tail call of 0x4b6800. */
uint32_t vertrix_port_forward_4b6800_43d4b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b6800, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43d4c0: Tail call of 0x4b6890. */
uint32_t vertrix_port_forward_4b6890_43d4c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b6890, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x44c2a0: Tail call of 0x4ac8a0. */
uint32_t vertrix_port_forward_4ac8a0_44c2a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ac8a0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x44c3d0: Tail call of 0x44c2a0. */
uint32_t vertrix_port_forward_44c2a0_44c3d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x44c2a0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4872b0: Tail call of 0x4ea190. */
uint32_t vertrix_port_forward_4ea190_4872b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ea190, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x48d6b0: Tail call of 0x4d8950. */
uint32_t vertrix_port_forward_4d8950_48d6b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4d8950, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b5a50: Tail call of 0x4b6890. */
uint32_t vertrix_port_forward_4b6890_4b5a50(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b6890, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b9310: Tail call of 0x4b91b0. */
uint32_t vertrix_port_forward_4b91b0_4b9310(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b91b0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x41abe0: Call 0x4b7cd0 and 0x471a80, then 0x471aa0 on the object at [0x558c80]. */
uint32_t vertrix_port_call_471aa0_41abe0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b7cd0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x471a80, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x471aa0, port_u32(&port, 0, 0x558c80), vertrix_lift_edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x41ac00: Call 0x4b7cd0 and 0x471b00, then 0x471b20 on the object at [0x558c80]. */
uint32_t vertrix_port_call_471b20_41ac00(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b7cd0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x471b00, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x471b20, port_u32(&port, 0, 0x558c80), vertrix_lift_edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x41ac20: Call 0x4b7cd0 and 0x471a70, then 0x4719f0 on the object at [0x558c80]. */
uint32_t vertrix_port_call_4719f0_41ac20(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b7cd0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x471a70, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4719f0, port_u32(&port, 0, 0x558c80), vertrix_lift_edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x41ac70: Call 0x478f50 on the surface at [0x558c88] with edx 0. */
uint32_t vertrix_port_surface_clear_second_41ac70(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x478f50, port_u32(&port, 0, 0x558c88), 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x41aca0: Call 0x41aa20 and 0x41aaa0 on eax, then 0x4b7cd0 with edx 0, whose edx goes to
 * 0x532a38. */
uint32_t vertrix_port_call_41aa20_41aaa0_41aca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x41aa20, entry->eax, entry->eax, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    r = forward(&port, entry, 0x41aaa0, edx, edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4b7cd0, r, 0, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x532a38, vertrix_lift_edx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x424160: Tail call of 0x477610 on 0x55608c. */
uint32_t vertrix_port_forward_477610_424160(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x477610, 0x55608c, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x425e20: Construct by 0x4abd70, then class 0x5144d4 at +0x158 and +0x178 clear. */
uint32_t vertrix_port_player_piece_initialize_425e20(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4abd70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, r, 0x158, 0x5144d4);
    port_set32(&port, r, 0x178, 0);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4290a0: The rotation 0x429000 chooses (ebx +0x210), kept at +0x16c. */
uint32_t vertrix_port_ai_choose_piece_rotation_4290a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x429000, entry->eax, entry->edx, entry->eax + 0x210, entry->eax);
    port_set32(&port, entry->eax, 0x16c, r);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x42a480: Release the 3 slots at +0x15c (0x4b22c0). */
uint32_t vertrix_port_release_slots_15c_42a480(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x15c, 3, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42a4a0: Release the 3 slots at +0x170 (0x4b22c0). */
uint32_t vertrix_port_release_slots_170_42a4a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x170, 3, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ebc0: Release the 65 slots at +0x220 (0x4b22c0). */
uint32_t vertrix_port_release_slots_220_42ebc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x220, 65, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ebe0: Release the 65 slots at +0x87c (0x4b22c0). */
uint32_t vertrix_port_release_slots_87c_42ebe0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x87c, 65, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ec00: Release the 5 slots at +0x988 (0x4b22c0). */
uint32_t vertrix_port_release_slots_988_42ec00(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x988, 5, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ec20: Release the 13 slots at +0x9e8 (0x4b22c0). */
uint32_t vertrix_port_release_slots_9e8_42ec20(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x9e8, 13, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ec40: Release the 13 slots at +0xa2c (0x4b22c0). */
uint32_t vertrix_port_release_slots_a2c_42ec40(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0xa2c, 13, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ec60: Release the 65 slots at +0xbdc (0x4b22c0). */
uint32_t vertrix_port_release_slots_bdc_42ec60(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0xbdc, 65, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42eee0: Release the 260 slots at +0x324 (0x4b22c0). */
uint32_t vertrix_port_release_slots_324_42eee0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b22c0, entry->eax + 0x324, 260, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ec80: Call 0x4b2300 over the 0x41 slots at +0xbdc with the handler in edx. */
uint32_t vertrix_port_slots_each_bdc_42ec80(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b2300, entry->eax + 0xbdc, 0x41, entry->edx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x42eca0: Call 0x4b2300 over the 0x41 slots at +0x220 with the handler in edx. */
uint32_t vertrix_port_slots_each_220_42eca0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b2300, entry->eax + 0x220, 0x41, entry->edx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x42ef00: Call 0x42ef60 with edx 0. */
uint32_t vertrix_port_with_zero_42ef60_42ef00(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42ef60, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ef10: Call 0x42ef80 with edx 0. */
uint32_t vertrix_port_with_zero_42ef80_42ef10(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42ef80, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ef20: Call 0x42f7d0 with edx 0. */
uint32_t vertrix_port_with_zero_42f7d0_42ef20(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f7d0, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ef30: Call 0x42f7f0 with edx 0. */
uint32_t vertrix_port_with_zero_42f7f0_42ef30(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f7f0, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ef40: Call 0x42f810 with edx 0. */
uint32_t vertrix_port_with_zero_42f810_42ef40(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f810, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42ef50: Call 0x42f830 with edx 0. */
uint32_t vertrix_port_with_zero_42f830_42ef50(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f830, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42f850: Call 0x42f8b0 with edx 0. */
uint32_t vertrix_port_with_zero_42f8b0_42f850(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f8b0, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42f860: Call 0x42f8e0 with edx 0. */
uint32_t vertrix_port_with_zero_42f8e0_42f860(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f8e0, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42f870: Call 0x42f890 with edx 0. */
uint32_t vertrix_port_with_zero_42f890_42f870(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f890, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x42f880: Call 0x42f8a0 with edx 0. */
uint32_t vertrix_port_with_zero_42f8a0_42f880(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42f8a0, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x487a10: Call 0x487a20 with edx 0. */
uint32_t vertrix_port_with_zero_487a20_487a10(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x487a20, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48d620: Call 0x48d630 with edx 0. */
uint32_t vertrix_port_with_zero_48d630_48d620(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x48d630, entry->eax, 0, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x430090: Whether 0x4ac900 of the object +0xce0 is the handler 0x44c860. */
uint32_t vertrix_port_board_extra_is_idle_430090(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ac900, port_u32(&port, entry->eax, 0xce0), entry->edx, entry->ebx,
                entry->ecx) == 0x44c860;
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x431fa0: Tail call of 0x42a980 on the object +0xa60. */
uint32_t vertrix_port_board_piece_child_kinds_431fa0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x42a980, port_u32(&port, entry->eax, 0xa60), entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x432820: Call 0x4327e0 over the 0x41 slots at +0x220 with the bytes at +0x1de. */
uint32_t vertrix_port_board_slots_4327e0_432820(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4327e0, entry->eax + 0x220, entry->eax + 0x1de, 0x41, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x43a510: Tail call of 0x43a410 with dl, bl and cl sign-extended. */
uint32_t vertrix_port_piece_children_setup_registers_43a510(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43a410, entry->eax, (uint32_t)(int8_t)entry->edx,
                (uint32_t)(int8_t)entry->ebx, (uint32_t)(int8_t)entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43ab60: Call 0x4279b0 on the object +0x450 with the player in edx. */
uint32_t vertrix_port_player_call_4279b0_43ab60(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4279b0, port_u32(&port, entry->eax, 0x450), entry->eax, entry->ebx,
                port_u32(&port, entry->eax, 0x450));
    return port_return(&port, r, entry->edx);
}

/* Original 0x43b590: Call 0x43b5b0, 0x43b660 and 0x43b680 on the player. */
uint32_t vertrix_port_player_draw_all_delays_43b590(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x43b5b0, entry->eax, entry->eax, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    forward(&port, entry, 0x43b660, edx, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    r = forward(&port, entry, 0x43b680, edx, edx, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x43b660: The delay 0x43b6a0 draws between 2 and 3, kept at +0x45c. */
uint32_t vertrix_port_player_draw_delay_1_43b660(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43b6a0, entry->eax, 2, 3, entry->eax);
    port_set32(&port, entry->eax, 0x45c, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x43b680: The delay 0x43b6a0 draws between 4 and 5, kept at +0x460. */
uint32_t vertrix_port_player_draw_delay_2_43b680(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43b6a0, entry->eax, 4, 5, entry->eax);
    port_set32(&port, entry->eax, 0x460, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x43b800: Tail call of 0x43b810 with edx plus +0x17c. */
uint32_t vertrix_port_player_bump_level_43b800(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43b810, entry->eax, entry->edx + port_u32(&port, entry->eax, 0x17c),
                entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43b880: Method +8 of the object +0x15c (class +0x158). */
uint32_t vertrix_port_object_method_8_43b880(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x15c);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0x158), 8), object,
                entry->edx, entry->ebx, port_u32(&port, object, 0x158));
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43baf0: Store dl at +0x4c4, then 0x4726d0. */
uint32_t vertrix_port_player_set_c4_and_refresh_43baf0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x4c4, entry->edx);
    r = forward(&port, entry, 0x4726d0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43bb40: Store edx at +0x4c8, then 0x4726d0. */
uint32_t vertrix_port_player_set_mode_and_refresh_43bb40(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x4c8, entry->edx);
    r = forward(&port, entry, 0x4726d0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43bce0: Call 0x43bb60, set the byte +0x4cc to 5 and enter the handler 0x452370
 * (0x4ac8f0). */
uint32_t vertrix_port_player_enter_452370_43bce0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x43bb60, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set8(&port, entry->eax, 0x4cc, 5);
    r = forward(&port, entry, 0x4ac8f0, entry->eax, 0x452370, entry->ebx, entry->eax);
    return port_return(&port, r, entry->edx);
}

/* Original 0x43d300: Whether the list +0x468 is not empty (0x4879e0). */
uint32_t vertrix_port_object_list_filled_43d300(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4879e0, port_u32(&port, entry->eax, 0x468), entry->edx, entry->ebx,
                entry->ecx) != 1;
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43d320: Method +0x18 of the object +0x468. */
uint32_t vertrix_port_object_virtual_slot6_43d320(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x468);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0), 0x18), object,
                port_u32(&port, object, 0), entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x43d3f0: Construct by 0x4b5580 with class 0x514d54 at +0x158. */
uint32_t vertrix_port_construct_514d54_43d3f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b5580, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, r, 0x158, 0x514d54);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x43f460: Whether 0x43f420 finds the glyph dl for the signed font al. */
uint32_t vertrix_port_glyph_present_43f460(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43f420, (uint32_t)(int8_t)entry->eax, entry->edx & 0xff, entry->ebx,
                entry->ecx) != 0;
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x448140: Call 0x416010, then enter the handler 0x448160 (0x4ac8f0). */
uint32_t vertrix_port_enter_448160_448140(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x416010, entry->eax, entry->edx, entry->ebx, entry->eax);
    r = forward(&port, entry, 0x4ac8f0, entry->eax, 0x448160, entry->ebx, entry->eax);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4486d0: Tail call of 0x417150 on the object +0x15c of the object +0x160. */
uint32_t vertrix_port_call_417150_4486d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x417150, port_u32(&port, port_u32(&port, entry->eax, 0x160), 0x15c),
                entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4513d0: Method +4 of the object +0x15c (class +0x158). */
uint32_t vertrix_port_object_method_4_4513d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x15c);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0x158), 4), object,
                port_u32(&port, object, 0x158), entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x452050: Method +4 of the object +0x15c (class +0x158). */
uint32_t vertrix_port_object_method_4_452050(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t object;
    port_open(&port, calls, services, globals, entry);
    object = port_u32(&port, entry->eax, 0x15c);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, object, 0x158), 4), object,
                port_u32(&port, object, 0x158), entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x45e740: Tail call of 0x4874f0 on 0x5464e4. */
uint32_t vertrix_port_call_4874f0_5464e4_45e740(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4874f0, 0x5464e4, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x45e810: Tail call of 0x4874f0 on 0x544a34. */
uint32_t vertrix_port_call_4874f0_544a34_45e810(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4874f0, 0x544a34, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x45e820: Tail call of 0x4874f0 on 0x544a50. */
uint32_t vertrix_port_call_4874f0_544a50_45e820(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4874f0, 0x544a50, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x471a90: Tail call of 0x4b5fc0 on 0x546744. */
uint32_t vertrix_port_call_4b5fc0_546744_471a90(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b5fc0, 0x546744, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x471b10: Tail call of 0x4b5fc0 on 0x546730. */
uint32_t vertrix_port_call_4b5fc0_546730_471b10(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b5fc0, 0x546730, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x471b80: Tail call of 0x4b6200 on 0x546758. */
uint32_t vertrix_port_call_4b6200_546758_471b80(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b6200, 0x546758, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x471b90: Tail call of 0x4b5fc0 on 0x546758. */
uint32_t vertrix_port_call_4b5fc0_546758_471b90(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b5fc0, 0x546758, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x46b800: Call 0x46b810 with edx -1. */
uint32_t vertrix_port_forward_registers_46b800_46b800(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x46b810, entry->eax, 0xffffffff, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x471920: Make the object of 0x4718a0, enter the handler 0x544c9c (0x4ac8d0) and start
 * it (0x4ac8a0); the object. */
uint32_t vertrix_port_spawn_544c9c_471920(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4718a0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    forward(&port, entry, 0x4ac8d0, r, 0x544c9c, entry->ebx, r);
    forward(&port, entry, 0x4ac8a0, r, vertrix_lift_edx, entry->ebx, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x471940: Make the object of 0x4718a0, enter the handler 0x544cb8 (0x4ac8d0) and start
 * it (0x4ac8a0); the object. */
uint32_t vertrix_port_spawn_544cb8_471940(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4718a0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    forward(&port, entry, 0x4ac8d0, r, 0x544cb8, entry->ebx, r);
    forward(&port, entry, 0x4ac8a0, r, vertrix_lift_edx, entry->ebx, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x471960: Make the object of 0x4718a0, enter the handler 0x544cd4 (0x4ac8d0) and start
 * it (0x4ac8a0); the object. */
uint32_t vertrix_port_spawn_544cd4_471960(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4718a0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    forward(&port, entry, 0x4ac8d0, r, 0x544cd4, entry->ebx, r);
    forward(&port, entry, 0x4ac8a0, r, vertrix_lift_edx, entry->ebx, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x471980: Make the object of 0x4718a0, enter the handler 0x544cf0 (0x4ac8d0) and start
 * it (0x4ac8a0); the object. */
uint32_t vertrix_port_spawn_544cf0_471980(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4718a0, entry->eax, entry->edx, entry->ebx, entry->ecx);
    forward(&port, entry, 0x4ac8d0, r, 0x544cf0, entry->ebx, r);
    forward(&port, entry, 0x4ac8a0, r, vertrix_lift_edx, entry->ebx, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x475d90: Tail call of 0x475800 on eax plus 0x4. */
uint32_t vertrix_port_offset_call_4_475d90(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x475800, entry->eax + 0x4, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x47ed50: Tail call of 0x4ca370 on eax plus 0x1c. */
uint32_t vertrix_port_offset_call_1c_47ed50(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ca370, entry->eax + 0x1c, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x47f8d0: Tail call of 0x4ca370 on eax plus 0x3c. */
uint32_t vertrix_port_offset_call_3c_47f8d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ca370, entry->eax + 0x3c, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x476260: Call 0x475b80 on 0x55364c with ebx edx and the stack arguments 0 and ebx. */
uint32_t vertrix_port_list_find_call_476260(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = 0;
    pushed[1] = entry->ebx;
    r = forward_stack(&port, entry, 0x475b80, 0x55364c, 0, entry->edx, 0, pushed, 2);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x47ed10: Method +0x14 of the object +0x1c8 with edx the dword +0xc of edx; zero. */
uint32_t vertrix_port_object_handler_14_47ed10(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0x1c8), 0x14), entry->eax,
            port_u32(&port, entry->edx, 0xc), entry->ebx, port_u32(&port, entry->eax, 0x1c8));
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x47f750: Call 0x47f5f0 with edx and esi eax plus 4, ebx 0 and ecx edx. */
uint32_t vertrix_port_object_list_47f5f0_47f750(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = port_call_with(&port, 0x47f5f0, entry->eax, entry->eax + 4, 0, entry->edx, entry->eax + 4,
                       entry->edi, entry->ebp);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x47f770: Call 0x47f5f0 with edx and esi eax plus 8, ebx edx and ecx ebx. */
uint32_t vertrix_port_object_list_47f5f0_8_47f770(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = port_call_with(&port, 0x47f5f0, entry->eax, entry->eax + 8, entry->edx, entry->ebx,
                       entry->eax + 8, entry->edi, entry->ebp);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x47fa20: Call 0x47ea20, then 0x47f750 on eax. */
uint32_t vertrix_port_call_47ea20_47f750_47fa20(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x47ea20, entry->eax, entry->edx, entry->ebx, entry->eax);
    r = forward(&port, entry, 0x47f750, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x482740: Tail call of 0x4ea190 on the dword at eax. */
uint32_t vertrix_port_forward_first_dword_482740(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ea190, port_u32(&port, entry->eax, 0), entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x484500: The import 0x4f1730 on the handle at [0x598db0]. */
uint32_t vertrix_port_import_4f1730_484500(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, 0, 0x598db0);
    r = forward_stack(&port, entry, 0x4f1730, entry->eax, pushed[0], entry->ebx, entry->ecx, pushed,
                      1);
    return port_return(&port, r, entry->edx);
}

/* Original 0x487920: Construct by 0x4d8650 with class 0x516e34 at +0. */
uint32_t vertrix_port_construct_516e34_487920(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4d8650, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, r, 0, 0x516e34);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x489b20: Method +0x30 of the object with ebx 0. */
uint32_t vertrix_port_object_method_30_489b20(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 0x30), entry->eax,
                entry->edx, 0, port_u32(&port, entry->eax, 0));
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x48c260: Notify the field +0x1cc (0x48c9b0 with ebx 1). */
uint32_t vertrix_port_object_notify_field_1cc_48c260(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x48c9b0, entry->eax, entry->eax + 0x1cc, 1, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48c310: Notify the field +0x1e4 (0x48c9b0 with ebx 1). */
uint32_t vertrix_port_object_notify_field_1e4_48c310(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x48c9b0, entry->eax, entry->eax + 0x1e4, 1, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48c390: Append [0x532bec] at +0x3c (0x47f8d0), then 0x47f790. */
uint32_t vertrix_port_append_then_47f790_48c390(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x47f8d0, entry->eax, port_u32(&port, 0, 0x532bec), entry->ebx,
            entry->eax);
    r = forward(&port, entry, 0x47f790, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48c3b0: Append [0x532bec] at +0x3c (0x47f8d0), then 0x47f830. */
uint32_t vertrix_port_append_then_47f830_48c3b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x47f8d0, entry->eax, port_u32(&port, 0, 0x532bec), entry->ebx,
            entry->eax);
    r = forward(&port, entry, 0x47f830, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48c460: Append [0x532bec] at +0x3c (0x47f8d0), then 0x47f4b0. */
uint32_t vertrix_port_append_then_47f4b0_48c460(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x47f8d0, entry->eax, port_u32(&port, 0, 0x532bec), entry->ebx,
            entry->eax);
    r = forward(&port, entry, 0x47f4b0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48c480: Call 0x4b7020 on 0x532c04 with eax in edx, then 0x47f430 on it. */
uint32_t vertrix_port_call_4b7020_47f430_48c480(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4b7020, 0x532c04, entry->eax, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    r = forward(&port, entry, 0x47f430, edx, edx, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x48d500: Clear by 0x48d480 and set the dwords +0x20 and +0x2c. */
uint32_t vertrix_port_object_clear_with_ones_48d500(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x48d480, entry->eax, entry->eax, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, edx, 0x20, 1);
    port_set32(&port, edx, 0x2c, 1);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b45f0: Call 0x4b46e0 with the cursor +0x170. */
uint32_t vertrix_port_object_cursor_row_4b45f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b46e0, entry->eax, port_u32(&port, entry->eax, 0x170), entry->ebx,
                entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b4600: Set the cursor +0x170 to one less, then 0x4b4690. */
uint32_t vertrix_port_object_step_text_length_4b4600(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x170, port_u32(&port, entry->eax, 0x170) - 1);
    r = forward(&port, entry, 0x4b4690, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b4610: Set the cursor +0x170 to one more, then 0x4b4690. */
uint32_t vertrix_port_object_step_text_length_4b4610(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x170, port_u32(&port, entry->eax, 0x170) + 1);
    r = forward(&port, entry, 0x4b4690, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b4620: Set the cursor +0x170 to -1, then 0x4b4690. */
uint32_t vertrix_port_object_step_text_length_4b4620(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x170, 0xffffffff);
    r = forward(&port, entry, 0x4b4690, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b4780: Keep the position of 0x4b4700 at +0x170. */
uint32_t vertrix_port_object_text_seek_4b4780(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b4700, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set32(&port, entry->eax, 0x170, r);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b4c90: Append the dword +0x188 to the list +0x15c of the parent +0x160 (0x4ca370). */
uint32_t vertrix_port_object_parent_append_4b4c90(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ca370, port_u32(&port, entry->eax, 0x160) + 0x15c,
                port_u32(&port, entry->eax, 0x188), entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b4cd0: Append the dword +0x18c to the list +0x15c of the parent +0x160 (0x4ca370). */
uint32_t vertrix_port_object_parent_append_4b4cd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ca370, port_u32(&port, entry->eax, 0x160) + 0x15c,
                port_u32(&port, entry->eax, 0x18c), entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b4cb0: Tail call of 0x4b6a10 on the parent +0x160 with dl. */
uint32_t vertrix_port_object_parent_glyph_4b4cb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4b6a10, port_u32(&port, entry->eax, 0x160), entry->edx & 0xff,
                entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b69f0: Lay out the glyph (0x440610) of the font in the top byte of +0x160 with the
 * table 0x5110b8, bl the byte +0x44 and the caller's ebx pushed. */
uint32_t vertrix_port_object_glyph_layout_4b69f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[1];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = entry->ebx;
    r = forward_stack(&port, entry, 0x440610,
                      (uint32_t)((int32_t)port_u32(&port, entry->eax, 0x15d) >> 24), 0x5110b8,
                      port_u8(&port, entry->eax, 0x44), entry->edx, pushed, 1);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b6a10: Tail call of 0x43f460 for the font in the top byte of +0x160 and dl. */
uint32_t vertrix_port_object_glyph_present_4b6a10(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x43f460,
                (uint32_t)((int32_t)port_u32(&port, entry->eax, 0x15d) >> 24), entry->edx & 0xff,
                entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4b7db0: The import 0x4f1cfc on the handle at [0x5bd840] and eax. */
uint32_t vertrix_port_import_4f1cfc_4b7db0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[2];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, 0, 0x5bd840);
    pushed[1] = entry->eax;
    r = forward_stack(&port, entry, 0x4f1cfc, entry->eax, pushed[0], entry->ebx, entry->ecx, pushed,
                      2);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b8170: The result of 0x40aca0, after 0x4ea190 on its edx. */
uint32_t vertrix_port_two_step_call_4b8170(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x40aca0, entry->eax, entry->eax, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    forward(&port, entry, 0x4ea190, edx, edx, entry->ebx, r);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b91e0: Allocate 0x84 bytes by the allocator at +4 (its method +0) and clear +0x80 of
 * the block. */
uint32_t vertrix_port_allocate_0x84_4b91e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 4), 0), entry->eax, 0,
                0x84, port_u32(&port, entry->eax, 4));
    port_set32(&port, r, 0x80, 0);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b9200: Allocate 0x118 bytes by the allocator at +4 (its method +0) and clear +0x114
 * of the block. */
uint32_t vertrix_port_allocate_0x118_4b9200(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 4), 0), entry->eax, 0,
                0x118, port_u32(&port, entry->eax, 4));
    port_set32(&port, r, 0x114, 0);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4b9dd0: Clear +0x94, then 0x4b9d70. */
uint32_t vertrix_port_clear_94_call_4b9dd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x94, 0);
    r = forward(&port, entry, 0x4b9d70, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c3e40: Method +8 of the object, then 0x4b91b0 on it and 0x4eb4d4 with 0xff. */
uint32_t vertrix_port_object_close_4c3e40(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 8), entry->eax,
            entry->eax, entry->ebx, port_u32(&port, entry->eax, 0));
    edx = vertrix_lift_edx;
    forward(&port, entry, 0x4b91b0, edx, edx, entry->ebx, port_u32(&port, entry->eax, 0));
    r = forward(&port, entry, 0x4eb4d4, 0xff, vertrix_lift_edx, entry->ebx,
                port_u32(&port, entry->eax, 0));
    return port_return(&port, r, entry->edx);
}

/* Original 0x4c4d00: Store the code 0x36 and edx at +0x14 and +0x18 of the record at [eax] and call
 * its handler +0. */
uint32_t vertrix_port_object_error_36_4c4d00(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, entry->eax, 0), 0x14, 0x36);
    port_set32(&port, port_u32(&port, entry->eax, 0), 0x18, entry->edx);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 0), entry->eax,
                port_u32(&port, entry->eax, 0), entry->ebx, port_u32(&port, entry->eax, 0));
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c5bb0: Tail call of 0x4e7c90 on edx. */
uint32_t vertrix_port_edx_to_eax_4e7c90_4c5bb0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e7c90, entry->edx, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c5bc0: Tail call of 0x4ea190 on edx. */
uint32_t vertrix_port_edx_to_eax_4ea190_4c5bc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ea190, entry->edx, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c5bd0: Tail call of 0x4e7c90 on edx. */
uint32_t vertrix_port_edx_to_eax_4e7c90_4c5bd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e7c90, entry->edx, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c5be0: Tail call of 0x4ea190 on edx. */
uint32_t vertrix_port_edx_to_eax_4ea190_4c5be0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ea190, entry->edx, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c5c00: Store the code 0x31 at +0x14 of the record at [eax] and call its handler +0.
 */
uint32_t vertrix_port_object_error_31_4c5c00(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, entry->eax, 0), 0x14, 0x31);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 0), entry->eax,
                port_u32(&port, entry->eax, 0), entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4c6c70: Store the code 0x2e at +0x14 of the record at [eax] and call its handler +0.
 */
uint32_t vertrix_port_object_error_2e_4c6c70(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, entry->eax, 0), 0x14, 0x2e);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 0), entry->eax,
                port_u32(&port, entry->eax, 0), entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4c9fe0: Call 0x4d9510; zero. */
uint32_t vertrix_port_call_4d9510_4c9fe0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4d9510, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x4ca650: Call 0x4ca5a0 with the string at [edx] and its length (the dword 8 bytes
 * before it); eax. */
uint32_t vertrix_port_string_assign_length_4ca650(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4ca5a0, entry->eax,
            port_u32(&port, port_u32(&port, entry->edx, 0), -8u), port_u32(&port, entry->edx, 0),
            entry->eax);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

/* Original 0x4ca6f0: Make room (0x4ca670), then set the string's length to edx and terminate it;
 * the string. */
uint32_t vertrix_port_rtl_string_set_length_4ca6f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t text;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4ca670, entry->eax, entry->edx, entry->edx, entry->eax);
    port_set32(&port, port_u32(&port, entry->eax, 0), -8u, entry->edx);
    text = port_u32(&port, entry->eax, 0);
    port_set8(&port, entry->edx, text, 0);
    r = port_u32(&port, entry->eax, 0);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4cba60: Field +0xc8 of the result of 0x4ce220. */
uint32_t vertrix_port_class_field_c8_4cba60(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = port_u32(&port,
                 forward(&port, entry, 0x4ce220, entry->eax, entry->edx, entry->ebx, entry->ecx),
                 0xc8);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4cd836: Call 0x4e0eaf, then 0x4e0ec7 on its result with eax in edx. */
uint32_t vertrix_port_call_4e0eaf_4e0ec7_4cd836(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e0eaf, entry->eax, entry->edx, entry->ebx, entry->eax);
    r = forward(&port, entry, 0x4e0ec7, r, entry->eax, entry->ebx, entry->eax);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4d3010: Method +0 of the object, then 0x4d3120. */
uint32_t vertrix_port_object_method_0_check_4d3010(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, port_u32(&port, entry->eax, 0), 0), entry->eax,
                entry->edx, entry->ebx, port_u32(&port, entry->eax, 0));
    r = forward(&port, entry, 0x4d3120, r, vertrix_lift_edx, entry->ebx,
                port_u32(&port, entry->eax, 0));
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4d4040: Call 0x4dba10 on the record of 0x4ce780 plus 8 with eax in edx and ebx. */
uint32_t vertrix_port_record_call_4dba10_4d4040(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ce780, entry->eax, entry->edx, entry->eax, entry->ecx);
    r = forward(&port, entry, 0x4dba10, r + 8, entry->eax, entry->eax, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4d4990: Tail call of 0x4d49a0 with ebx the dword at edx. */
uint32_t vertrix_port_forward_4d49a0_4d4990(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4d49a0, entry->eax, entry->edx, port_u32(&port, entry->edx, 0),
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4d5330: The import 0x4f1a60 with edx, 0x3e1, the handle +0x1c and ebx; zero. */
uint32_t vertrix_port_import_4f1a60_4d5330(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = entry->edx;
    pushed[1] = 0x3e1;
    pushed[2] = port_u32(&port, entry->eax, 0x1c);
    pushed[3] = entry->ebx;
    forward_stack(&port, entry, 0x4f1a60, entry->eax, entry->edx, entry->ebx, entry->ecx, pushed,
                  4);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4d5910: The import 0x4f1a94 with the handle +0x1c, 0x362, edx and 0. */
uint32_t vertrix_port_import_4f1a94_362_4d5910(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, entry->eax, 0x1c);
    pushed[1] = 0x362;
    pushed[2] = entry->edx;
    pushed[3] = 0;
    r = forward_stack(&port, entry, 0x4f1a94, entry->eax, entry->edx, entry->ebx, entry->ecx,
                      pushed, 4);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4ee730: The import 0x4f1a94 with the handle +0x1c, 0x401, 0 and 0; zero. */
uint32_t vertrix_port_import_4f1a94_401_4ee730(PORT_SIGNATURE)
{
    Port port;
    uint32_t pushed[4];
    port_open(&port, calls, services, globals, entry);
    pushed[0] = port_u32(&port, entry->eax, 0x1c);
    pushed[1] = 0x401;
    pushed[2] = 0;
    pushed[3] = 0;
    forward_stack(&port, entry, 0x4f1a94, entry->eax, entry->edx, entry->ebx, entry->ecx, pushed,
                  4);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4dad2e: Tail call of 0x4dad38 with edx in ebx. */
uint32_t vertrix_port_rtl_ebx_from_edx_call_4dad2e(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4dad38, entry->eax, entry->edx, entry->edx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4dae70: Store the code in the record of [0x507c9c] at +4. */
uint32_t vertrix_port_thread_record_4_4dae70(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x507c9c), entry->eax, entry->eax, entry->ebx,
                entry->ecx);
    port_set32(&port, r, 4, vertrix_lift_edx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4dae80: Store the code in the record of [0x507c9c] at +4. */
uint32_t vertrix_port_thread_record_4_4dae80(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x507c9c), 0xd, 0xd, entry->ebx, entry->ecx);
    port_set32(&port, r, 4, vertrix_lift_edx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4daeb8: Store the code in the record of [0x507c9c] at +8. */
uint32_t vertrix_port_thread_record_8_4daeb8(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x507c9c), entry->eax, entry->eax, entry->ebx,
                entry->ecx);
    port_set32(&port, r, 8, vertrix_lift_edx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4dd170: Store the stack argument at +0x30 of the record of 0x4ce740. */
uint32_t vertrix_port_rtl_record_set_argument_4dd170(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * 1];
    uint32_t argument;
    uint32_t r;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    argument = port_u32(&port, entry->esp, 4);
    r = forward(&port, entry, 0x4ce740, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, r, 0x30, argument);
    return port_return(&port, r, argument);
}

/* Original 0x4dd440: Call 0x4dd3e0 with 1 and the stack argument, then 0x4ded70. */
uint32_t vertrix_port_rtl_pair_4dd3e0_4dd440(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * 1];
    uint32_t argument;
    uint32_t r;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    argument = port_u32(&port, entry->esp, 4);
    r = forward(&port, entry, 0x4dd3e0, 1, argument, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4ded70, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4ddc40: Call 0x4ddbe0 with 1 and the stack argument, then 0x4ded70. */
uint32_t vertrix_port_rtl_pair_4ddbe0_4ddc40(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * 1];
    uint32_t argument;
    uint32_t r;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    argument = port_u32(&port, entry->esp, 4);
    r = forward(&port, entry, 0x4ddbe0, 1, argument, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4ded70, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4e1210: Call 0x4e11b0 with 1 and the stack argument, then 0x4ded70. */
uint32_t vertrix_port_rtl_pair_4e11b0_4e1210(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * 1];
    uint32_t argument;
    uint32_t r;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    argument = port_u32(&port, entry->esp, 4);
    r = forward(&port, entry, 0x4e11b0, 1, argument, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4ded70, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4dec60: Count up the dword +0x10 of the record of 0x4ce780. */
uint32_t vertrix_port_rtl_record_increment_4dec60(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ce780, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, r, 0x10, port_u32(&port, r, 0x10) + 1);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4dfa74: Call the routine at [0x509794]. */
uint32_t vertrix_port_call_global_509794_4dfa74(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x509794), entry->eax, entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4e7280: Call the routine at [0x509743]. */
uint32_t vertrix_port_call_global_509743_4e7280(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, port_u32(&port, 0, 0x509743), entry->eax, entry->edx, entry->ebx,
                entry->ecx);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4e0884: The import 0x4f1bbc, then 0x4e081c. */
uint32_t vertrix_port_import_4f1bbc_call_4e0884(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4f1bbc, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4e081c, r, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4e0bed: Call 0x4e0ae5 with the dword +4 in edx. */
uint32_t vertrix_port_call_4e0ae5_4e0bed(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e0ae5, entry->eax, port_u32(&port, entry->eax, 4), entry->ebx,
                entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4e0bf8: Call 0x4e0c0c on 0x5127dc with the result of 0x4e0f8b. */
uint32_t vertrix_port_call_4e0c0c_4e0bf8(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e0f8b, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = forward(&port, entry, 0x4e0c0c, 0x5127dc, r, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4e14a3: Call the routine at [0x509750]; eax. */
uint32_t vertrix_port_call_global_509750_4e14a3(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, port_u32(&port, 0, 0x509750), entry->eax, entry->edx, entry->ebx,
            entry->eax);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

/* Original 0x4e2420: Call 0x4e3e00 on edx with the dword at eax, then count up +0x10. */
uint32_t vertrix_port_record_call_4e3e00_4e2420(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e3e00, entry->edx, port_u32(&port, entry->eax, 0), entry->eax,
                entry->ecx);
    port_set32(&port, entry->eax, 0x10, port_u32(&port, entry->eax, 0x10) + 1);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4e36d2: Call 0x4e3698 with cl sign-extended and store the stack argument at +0x10 of
 * its record. */
uint32_t vertrix_port_record_store_argument_4e36d2(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 4 * 1];
    uint32_t argument;
    uint32_t r;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    argument = port_u32(&port, entry->esp, 4);
    r = forward(&port, entry, 0x4e3698, entry->eax, entry->edx, entry->ebx,
                (uint32_t)(int8_t)entry->ecx);
    port_set32(&port, r, 0x10, argument);
    return port_return(&port, r, argument);
}

/* Original 0x4e5750: Clear the 16-byte slot of the low four bits of eax at 0x5c8200 (0x4e5700),
 * then 0x4e03fc. */
uint32_t vertrix_port_clear_slot_call_4e5750(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4e5700, ((entry->eax & 0xf) << 4) + 0x5c8200, entry->eax, entry->ebx,
            entry->ecx);
    edx = vertrix_lift_edx;
    r = forward(&port, entry, 0x4e03fc, edx, edx, entry->ebx, entry->ecx);
    return port_return(&port, r, entry->edx);
}

/* Original 0x4e7ef4: Call 0x4e7fc4, then 0x4e7e44 with its result in edx; the edx left. */
uint32_t vertrix_port_call_4e7fc4_4e7e44_4e7ef4(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4e7fc4, entry->eax, entry->edx, entry->eax, entry->ecx);
    forward(&port, entry, 0x4e7e44, entry->eax, r, entry->eax, entry->ecx);
    r = vertrix_lift_edx;
    return port_return(&port, r, r);
}

/* Original 0x4e89e8: Call 0x4e8978; the dword at 0x50af14. */
uint32_t vertrix_port_read_after_4e8978_4e89e8(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4e8978, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = port_u32(&port, 0, 0x50af14);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4e89f4: Call 0x4e8978; the dword at 0x50af18. */
uint32_t vertrix_port_read_after_4e8978_4e89f4(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    forward(&port, entry, 0x4e8978, entry->eax, entry->edx, entry->ebx, entry->ecx);
    r = port_u32(&port, 0, 0x50af18);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4ea6a0: Call 0x4ea540 with ecx 1. */
uint32_t vertrix_port_call_4ea540_4ea6a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ea540, entry->eax, entry->edx, entry->ebx, 1);
    return port_return(&port, r, vertrix_lift_edx);
}

/* Original 0x4eca85: Store the 64-bit result of 0x4ed79f (edx 0) at edx. */
uint32_t vertrix_port_store_pair_4ed79f_4eca85(PORT_SIGNATURE)
{
    Port port;
    uint32_t r;
    port_open(&port, calls, services, globals, entry);
    r = forward(&port, entry, 0x4ed79f, entry->eax, 0, entry->edx, entry->ecx);
    port_set32(&port, entry->edx, 0, r);
    port_set32(&port, entry->edx, 4, vertrix_lift_edx);
    return port_return(&port, r, vertrix_lift_edx);
}
