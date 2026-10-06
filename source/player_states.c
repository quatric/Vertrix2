#include "player_states.h"

enum
{
    BYTE_WIDTH = 1,
    DWORD_WIDTH = 4,
    STATE_BOARD = 0x15c,
    STATE_BOARD_TABLE = 0x158,
    STATE_VIRTUAL_SLOT = 4,
    STATE_TIMER_STEP = 0x4ac500,
    STATE_TIMER_DUE = 0x4ac520,
    STATE_TIMER_COUNT = 0x4ac540,
    STATE_TIMER_RESET = 0x4ac5b0,
    STATE_STEP = 0x4342f0,
    STATE_BUSY = 0x433e20,
    STATE_ARM = 0x4323d0,
    STATE_SET_HANDLER = 0x4ac8f0,
    STATE_SOUND = 0x43c0e0,
    STATE_GATE = 0x4334b0,
    STATE_BYTE_SOURCE = 0x433550,
    STATE_BYTE = 0x838,
    STATE_DRAIN_STEP = 0x433840,
    STATE_SOUND_GLOBAL = 0x4f81ac,
    STATE_ARM_AGAIN = 0x42eee0,
    STATE_CHECK_FIRST = 0x42eca0,
    STATE_CHECK_SECOND = 0x42ecc0,
    STATE_MARK = 0x42ebe0,
    STATE_START_BYTE = 0x4cd,
    STATE_START_BUSY = 0xbd8,
    STATE_START_SOUND_IDLE = 0x4f819c,
    STATE_START_SOUND_FIRE = 0x4f8184,
    STATE_START_QUERY = 0x4322f0,
    STATE_START_PIECE = 0x4334a0,
    STATE_START_REGISTER = 0x43bad0,
    STATE_START_PERIOD = 0x4ac7b0,
    STATE_SPEED_INDEX = 0x532bbc,
    STATE_SPEED_TABLE = 0x4f7be8,
    HANDLER_451520 = 0x451520,
    HANDLER_451580 = 0x451580,
    HANDLER_451630 = 0x451630,
    HANDLER_451730 = 0x451730,
    HANDLER_4517C0 = 0x4517c0,
    HANDLER_451920 = 0x451920,
    HANDLER_44C860 = 0x44c860
};

static int read_value(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                      unsigned width, uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, width, value);
}

/* The board's virtual call [[board + 0x158] + 4] with the table pointer in edx. */
static uint32_t finish_edx(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, VertrixRegs *regs, uint32_t board)
{
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs->edx))
    {
        return 0;
    }
    regs->eax = board;
    vertrix_regs_virtual(calls, globals, regs, STATE_VIRTUAL_SLOT);
    return regs->eax;
}

/* The same with the table pointer in ebx. */
static uint32_t finish_ebx(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, VertrixRegs *regs, uint32_t board)
{
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs->ebx))
    {
        return 0;
    }
    regs->eax = board;
    regs->eax = vertrix_call(calls, globals->read(regs->ebx + STATE_VIRTUAL_SLOT, globals->context),
                             regs->eax, regs->edx, regs->ebx, regs->ecx, 0);
    return regs->eax;
}

static void run_steps(const VertrixCalls *calls, VertrixRegs *regs, uint32_t board)
{
    regs->eax = board;
    vertrix_regs_call(calls, regs, STATE_TIMER_STEP);
    regs->eax = board;
    vertrix_regs_call(calls, regs, STATE_TIMER_DUE);
    if (regs->eax == 1)
    {
        regs->eax = board;
        vertrix_regs_call(calls, regs, STATE_TIMER_COUNT);
        regs->ebx = regs->eax;
        regs->edx = regs->eax;
        regs->eax = board;
        vertrix_regs_call(calls, regs, STATE_TIMER_RESET);
        if (regs->ebx != 0)
        {
            do
            {
                regs->eax = board;
                --regs->edx;
                vertrix_regs_call(calls, regs, STATE_STEP);
            } while (regs->edx != 0);
        }
    }
}

uint32_t vertrix_state_steps_451490(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx,
                                    uint32_t ebx)
{
    VertrixRegs regs = {player, edx, ebx, 0};
    uint32_t board;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ecx = board;
    run_steps(calls, &regs, board);
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_BUSY);
    if (regs.eax == 0)
    {
        regs.eax = board;
        regs.edx = HANDLER_451520;
        vertrix_regs_call(calls, &regs, STATE_ARM);
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    }
    return finish_edx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_steps_451730(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx,
                                    uint32_t ebx)
{
    VertrixRegs regs = {player, edx, ebx, 0};
    uint32_t board;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ecx = board;
    run_steps(calls, &regs, board);
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_BUSY);
    if (regs.eax == 0)
    {
        regs.edx = HANDLER_4517C0;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    }
    return finish_edx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_gate_451520(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t player, uint32_t edx)
{
    VertrixRegs regs = {player, edx, player, 0};
    uint32_t board;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ecx = board;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_GATE);
    if (regs.eax == 0)
    {
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_BYTE_SOURCE);
        if (!vertrix_build_store(services, board, STATE_BYTE, BYTE_WIDTH, regs.eax))
        {
            return 0;
        }
        regs.eax = board;
        regs.edx = HANDLER_451580;
        vertrix_regs_call(calls, &regs, STATE_BUSY);
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    }
    return finish_ebx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_drain_451580(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx)
{
    VertrixRegs regs = {player, edx, player, 0};
    uint32_t board;
    uint32_t count;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ecx = board;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_TIMER_STEP);
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_TIMER_DUE);
    if (regs.eax == 1)
    {
        uint32_t steps;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_TIMER_COUNT);
        steps = regs.eax;
        regs.edx = regs.eax;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_TIMER_RESET);
        while (steps != 0)
        {
            if (!read_value(services, board, STATE_BYTE, BYTE_WIDTH, &count))
            {
                return 0;
            }
            regs.eax = count;
            if (count != 0)
            {
                regs.eax = board;
                vertrix_regs_call(calls, &regs, STATE_DRAIN_STEP);
                if (!vertrix_build_store(services, board, STATE_BYTE, BYTE_WIDTH, count - 1))
                {
                    return 0;
                }
            }
            --regs.edx;
            if (regs.edx == 0)
            {
                break;
            }
        }
    }
    if (!read_value(services, board, STATE_BYTE, BYTE_WIDTH, &count))
    {
        return 0;
    }
    if (count != 0)
    {
        return finish_edx(calls, services, globals, &regs, board);
    }
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_DRAIN_STEP);
    regs.eax = board;
    regs.edx = HANDLER_451630;
    vertrix_regs_call(calls, &regs, STATE_ARM_AGAIN);
    regs.eax = player;
    vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    regs.edx = globals->read(STATE_SOUND_GLOBAL, globals->context);
    regs.eax = player;
    vertrix_regs_call(calls, &regs, STATE_SOUND);
    return finish_edx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_check_451630(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player)
{
    VertrixRegs regs = {player, HANDLER_44C860, player, 0};
    uint32_t board;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ecx = board;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, STATE_CHECK_FIRST);
    if (regs.eax != 0)
    {
        regs.edx = HANDLER_44C860;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_CHECK_SECOND);
        if (regs.eax != 0)
        {
            regs.eax = board;
            regs.edx = HANDLER_4517C0;
            vertrix_regs_call(calls, &regs, STATE_MARK);
            regs.eax = player;
            vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        }
    }
    return finish_ebx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_start_451690(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx)
{
    VertrixRegs regs = {player, edx, player, 0};
    uint32_t board;
    uint32_t flag;
    uint32_t busy;
    uint32_t index;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, player, STATE_START_BYTE, BYTE_WIDTH, &flag))
    {
        return 0;
    }
    regs.ecx = board;
    regs.eax = flag;
    if (flag != 0)
    {
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_START_QUERY);
    }
    if (flag != 0 && regs.eax == 1)
    {
        uint32_t byte;
        regs.edx = globals->read(STATE_START_SOUND_FIRE, globals->context);
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SOUND);
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_ARM_AGAIN);
        if (!read_value(services, player, STATE_START_BYTE, BYTE_WIDTH, &byte))
        {
            return 0;
        }
        regs.edx = vertrix_build_sign8(byte);
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_START_PIECE);
        regs.eax = player;
        regs.edx = 0;
        vertrix_regs_call(calls, &regs, STATE_START_REGISTER);
        index = globals->read(STATE_SPEED_INDEX, globals->context);
        regs.edx = globals->read(STATE_SPEED_TABLE + index * 4, globals->context);
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_START_PERIOD);
        regs.edx = HANDLER_451730;
        regs.eax = player;
    }
    else
    {
        if (!read_value(services, board, STATE_START_BUSY, DWORD_WIDTH, &busy))
        {
            return 0;
        }
        if (busy == 0)
        {
            regs.edx = globals->read(STATE_START_SOUND_IDLE, globals->context);
            regs.eax = player;
            vertrix_regs_call(calls, &regs, STATE_SOUND);
        }
        regs.edx = HANDLER_451920;
        regs.eax = player;
    }
    vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    return finish_edx(calls, services, globals, &regs, board);
}
