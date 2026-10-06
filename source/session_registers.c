#include "session_registers.h"

static void clear_group(VertrixSessionRegisters *registers)
{
    for (int i = 0; i < VERTRIX_CLEARED_REGISTERS; ++i)
    {
        registers->cleared[i] = 0;
    }
}

void vertrix_session_latch_release(VertrixSessionLatch *latch)
{
    if (latch->state != VERTRIX_LATCH_ARMED)
    {
        return;
    }
    latch->state = 0;
    latch->second = 0;
    latch->first = 0;
}

uint32_t vertrix_session_registers_reset(VertrixSessionRegisters *registers, uint32_t source)
{
    registers->primary = source;
    registers->secondary = source;
    registers->tertiary = source;
    clear_group(registers);
    return source;
}

uint32_t vertrix_session_registers_reset_open(VertrixSessionRegisters *registers, uint32_t source)
{
    registers->primary = source;
    registers->secondary = 0xffffffffu;
    registers->tertiary = source;
    clear_group(registers);
    return source;
}

uint32_t vertrix_session_registers_reset_secondary(VertrixSessionRegisters *registers,
                                                   uint32_t source)
{
    registers->secondary = source;
    clear_group(registers);
    return source;
}
