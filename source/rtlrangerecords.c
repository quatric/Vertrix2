#include "rtlrangerecords.h"

/* The range dispatcher's call (0x4cb820): stores a record, or calls a method by its kind. */

enum
{
    /* The frame below the return slot. The original copies its first three stack arguments and
     * the object to 0x24 below the return slot; the getter it calls first gets their address. */
    BELOW = 0x40,
    ARGUMENTS = 6,
    COPY = 0x24,
    COPY_OBJECT = 0x10,

    /* The stack arguments: the getter, the object's offset, a third dword, the operand, the kind
     * and the record. */
    GETTER = 0,
    OFFSET = 1,
    THIRD = 2,
    OPERAND = 3,
    KIND = 4,
    RECORD = 5,

    /* The operand's flag the boolean kinds test and clear. */
    OPERAND_FLAG = 0x18
};

typedef struct
{
    Port *port;
    uint32_t object;
    uint32_t copy;
    uint32_t getter;
    uint32_t operand;
    uint32_t edx;
} Call;

/* The getter (the first stack argument) with eax = the object, edx = the copy's address, ebx 0 or
 * the caller's edx, and ecx; esi, edi and ebp as the original holds them. Returns the method. */
static uint32_t method_of(Call *c, uint32_t ebx, uint32_t ecx)
{
    return port_call_with(c->port, c->getter, c->object, c->copy, ebx, ecx, c->object, c->edx, 1);
}

static uint32_t call_method(Call *c, uint32_t method, uint32_t edx, uint32_t ebx, uint32_t ecx,
                            uint32_t esi, uint32_t edi, uint32_t ebp)
{
    return port_call_with(c->port, method, c->object, edx, ebx, ecx, esi, edi, ebp);
}

/* The operand's flag at +0x18 as a boolean of it being clear, then set to `value`. */
static uint32_t take_flag(Call *c, uint32_t value)
{
    const uint32_t clear = port_u32(c->port, c->operand, OPERAND_FLAG) == 0;
    port_set32(c->port, c->operand, OPERAND_FLAG, value);
    return clear;
}

/* Original 0x4cb5a0 (eax = an object, edx = a value, then six stack arguments: a getter, an
 * offset, a dword, an operand, a kind and a record). With a record, stores the object and the
 * first three arguments in it and returns 1. Otherwise calls the getter for a method and calls
 * the method on the object + offset, the registers set by the kind (the operand's two dwords, the
 * operand itself, the value); kinds outside 2, 0xc, 0xd, 0x23, 0x26..0x29 and 0x2c..0x2f return 0.
 * Returns 1, the method's result, or (0x2c, 0x2d) whether the operand's +0x18 was clear, which
 * they then set to 0. No caller reads a result. */
uint32_t vertrix_port_rtl_range_record_store_4cb5a0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    uint32_t argument[ARGUMENTS];
    for (unsigned i = 0; i < ARGUMENTS; i++)
    {
        argument[i] = port_u32(&port, entry->esp + 4 + 4 * i, 0);
    }
    const uint32_t copy = entry->esp - COPY;
    port_set32(&port, copy, COPY_OBJECT, entry->eax);
    port_set32(&port, copy, 0, argument[GETTER]);
    port_set32(&port, copy, 4, argument[OFFSET]);
    port_set32(&port, copy, 8, argument[THIRD]);

    const uint32_t record = argument[RECORD];
    if (record != 0)
    {
        port_set32(&port, record, 0, entry->eax);
        port_set32(&port, record, 4, argument[GETTER]);
        port_set32(&port, record, 8, argument[OFFSET]);
        port_set32(&port, record, 0xc, argument[THIRD]);
        return port_return(&port, 1, 0);
    }

    const uint32_t target = entry->eax + argument[OFFSET];
    const uint32_t operand = argument[OPERAND];
    Call c = {&port, target, copy, argument[GETTER], operand, entry->edx};
    const uint32_t value = entry->edx;
    uint32_t result = 1;
    uint32_t method;
    switch (argument[KIND])
    {
        case 0x2:
            method = method_of(&c, 0, target);
            result = call_method(&c, method, value, 0, target, method, value, 1);
            break;
        case 0xc:
            /* This kind hands the getter the object in edx, not the copy. */
            method = port_call_with(&port, c.getter, target, target, 0, copy, target, value, 1);
            call_method(&c, method, vertrix_lift_edx, 0, method, target, value, 1);
            break;
        case 0xd:
            method = method_of(&c, 0, operand);
            call_method(&c, method, value, 0, method, target, value, 1);
            break;
        case 0x23:
            method = method_of(&c, 0, operand);
            result = call_method(&c, method, method, 0, operand, target, value, 1);
            break;
        case 0x26:
        case 0x27:
            method = method_of(&c, 0, operand);
            result = call_method(&c, method, port_u32(&port, operand, 4),
                                 port_u32(&port, operand, 0), operand, target, method, 1);
            if (argument[KIND] == 0x26)
            {
                result = 1;
            }
            break;
        case 0x28:
            method = method_of(&c, 0, operand);
            call_method(&c, method, value, port_u32(&port, operand, 4), port_u32(&port, operand, 0),
                        target, value, 1);
            break;
        case 0x29:
            method = method_of(&c, 0, operand);
            result = call_method(&c, method, value, port_u32(&port, operand, 4),
                                 port_u32(&port, operand, 0), target, value, method);
            break;
        case 0x2c:
            method = method_of(&c, 0, operand);
            call_method(&c, method, operand, 0, operand, target, method, 1);
            result = take_flag(&c, 0);
            break;
        case 0x2d:
            method = method_of(&c, value, operand);
            call_method(&c, method, operand, value, operand, target, value, method);
            result = take_flag(&c, 0);
            break;
        case 0x2e:
        case 0x2f:
            method = method_of(&c, 0, operand);
            result = call_method(&c, method, operand, method, operand, target, value, 1);
            if (argument[KIND] == 0x2e)
            {
                result = 1;
            }
            break;
        default:
            result = 0;
            break;
    }
    return port_return(&port, result, 0);
}
