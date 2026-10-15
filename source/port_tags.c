#include "port_tags.h"

/* The menu tags' steps: each keeps its text +0x15c in step with a setting. */

static void guard_record(Port *port, uint32_t record, uint32_t guard)
{
    port_set32(port, record, 0, port->env.chain);
    port_set32(port, record, 4, 0x4ec1ec);
    port_set32(port, record, 8, guard);
    port_set32(port, record, 0xc, 0);
}

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

enum
{
    /* The tag's text +0x15c is copied out after the changed text: the actor ends its bob
     * (0x4adfe0) first, then the copy and the bob height 80. */
    TAG_ENDS_FIRST,
    /* The copy, then the bob height 80 unless the text is `blank`, then the bob's end. */
    TAG_UNLESS_BLANK,
    /* The copy, the bob height 80, then the bob's end. */
    TAG_ENDS_LAST
};

/* The tag step: under a guard record the actor eax bobs when due (0x4ac500, 0x4ac520, 0x4ac540,
 * 0x4ac5b0; with +0x48 set +0x4a 0, +0x4c 5, 0x4ad530, 0x4adfe0); its text +0x15c (0x4ca280) is
 * compared (0x4ccfe0) with the setting's text: the entry of `table` for the setting word
 * `setting` (0x4ca310) or `none` when it is -1 (0x4ca370), or with a `table` of 0 the setting
 * plus 1 printed (0x4cdfb0) by 0x50e1ad with 19 (0x50e1b9 with 0x50e1b6 when -1), or, with a
 * `count` word, by 0x50e1dc with the count (0x50e1e8 with 0x50e1e5 when -1); a change is taken
 * in (`order`). The temporaries are released (0x4cda10); the guard record's chain. */
static uint32_t tag_step(PORT_SIGNATURE, uint32_t guard, uint32_t setting, uint32_t table,
                         uint32_t none, int order, uint32_t blank, uint32_t count)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t esi = 0;
    uint32_t edi = 1;
    uint32_t eax;
    uint32_t index;
    uint32_t args[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    guard_record(&port, ebp - 0x30, guard);
    port_call_with(&port, 0x4ac500, actor, 0x4ec1ec, guard, actor, 0, entry->edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                       ebp) == 1)
    {
        eax = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                             ebp);
        port_call_with(&port, 0x4ac5b0, actor, eax, actor, actor, 0, entry->edi, ebp);
        if (port_u16(&port, actor, 0x48) != 0)
        {
            port_set16(&port, actor, 0x4a, 0);
            port_set16(&port, actor, 0x4c, 5);
            port_call_with(&port, 0x4ad530, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                           ebp);
            port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, 0, entry->edi,
                           ebp);
        }
    }
    port_call_with(&port, 0x4ca280, ebp - 0x1c, port_u32(&port, actor, 0x15c), actor, actor, esi,
                   edi, ebp);
    port_set32(&port, ebp, -0x24u, 1);
    port_call_with(&port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, actor, actor, esi, edi, ebp);
    index = port_u32(&port, 0, setting);
    port_set32(&port, ebp, -0x24u, 2);
    if (count != 0)
    {
        args[0] = ebp - 0x18;
        args[1] = index == 0xffffffffu ? 0x50e1e8 : 0x50e1dc;
        args[2] = index == 0xffffffffu ? 0x50e1e5 : index + 1;
        args[3] = port_u32(&port, 0, count);
        if (index == 0xffffffffu)
        {
            esi = args[3];
        }
        else
        {
            edi = args[3];
        }
        call_frame(&port, 0x4cdfb0, ebp - 0x18, index, actor, actor, esi, edi, ebp, args, 4);
    }
    else if (table == 0)
    {
        args[0] = ebp - 0x18;
        args[1] = index == 0xffffffffu ? 0x50e1b9 : 0x50e1ad;
        args[2] = index == 0xffffffffu ? 0x50e1b6 : index + 1;
        args[3] = 0x13;
        call_frame(&port, 0x4cdfb0, ebp - 0x18, index, actor, actor, esi, edi, ebp, args, 4);
    }
    else if (index == 0xffffffffu)
    {
        port_call_with(&port, 0x4ca370, ebp - 0x18, none, actor, actor, esi, edi, ebp);
    }
    else
    {
        port_call_with(&port, 0x4ca310, ebp - 0x18, table + index * 4, actor, actor, esi, edi, ebp);
    }
    eax = port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x1cu),
                         port_u32(&port, ebp, -0x18u), actor, actor, esi, edi, ebp);
    if (eax != 0)
    {
        if (order == TAG_ENDS_FIRST)
        {
            port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, esi, edi, ebp);
            eax = port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u),
                                 actor, actor, esi, edi, ebp);
            port_set16(&port, actor, 0x48, 0x50);
        }
        else
        {
            port_call_with(&port, 0x4ca370, actor + 0x15c, port_u32(&port, ebp, -0x18u), actor,
                           actor, esi, edi, ebp);
            if (order == TAG_ENDS_LAST ||
                port_call_with(&port, 0x4ccfe0, port_u32(&port, ebp, -0x18u), blank, actor, actor,
                               esi, edi, ebp) != 0)
            {
                port_set16(&port, actor, 0x48, 0x50);
            }
            eax = port_call_with(&port, 0x4adfe0, actor, vertrix_lift_edx, actor, actor, esi, edi,
                                 ebp);
        }
    }
    port_call_with(&port, 0x4cda10, eax, vertrix_lift_edx, actor, actor, esi, edi, ebp);
    return port_return(&port, port_u32(&port, ebp, -0x30u), entry->edx);
}

/* Original 0x44b050: the tag of the setting 0x532a68 (texts 0x534588, none 0x50e19f). */
uint32_t vertrix_port_tag_step_44b050(PORT_SIGNATURE)
{
    return tag_step(calls, services, globals, entry, 0x5152a0, 0x532a68, 0x534588, 0x50e19f,
                    TAG_ENDS_FIRST, 0, 0);
}

/* Original 0x44b4a0: the tag of the setting 0x532a70 (texts 0x533d7c, none 0x50e1a7), not
 * bobbing for the text 0x50e1a9. */
uint32_t vertrix_port_tag_step_44b4a0(PORT_SIGNATURE)
{
    return tag_step(calls, services, globals, entry, 0x5152dc, 0x532a70, 0x533d7c, 0x50e1a7,
                    TAG_UNLESS_BLANK, 0x50e1a9, 0);
}

/* Original 0x44b5d0: the tag of the setting 0x532a70 (texts 0x533dcc, none 0x50e1ab). */
uint32_t vertrix_port_tag_step_44b5d0(PORT_SIGNATURE)
{
    return tag_step(calls, services, globals, entry, 0x5152f0, 0x532a70, 0x533dcc, 0x50e1ab,
                    TAG_ENDS_LAST, 0, 0);
}

/* Original 0x44b6f0: the tag of the setting 0x532a68 printed as its number. */
uint32_t vertrix_port_tag_step_44b6f0(PORT_SIGNATURE)
{
    return tag_step(calls, services, globals, entry, 0x515304, 0x532a68, 0, 0, TAG_ENDS_LAST, 0, 0);
}

/* Original 0x44b980: the tag of the setting 0x532a70 printed as its number with the count
 * 0x532a88. */
uint32_t vertrix_port_tag_step_44b980(PORT_SIGNATURE)
{
    return tag_step(calls, services, globals, entry, 0x51532c, 0x532a70, 0, 0, TAG_ENDS_LAST, 0,
                    0x532a88);
}
