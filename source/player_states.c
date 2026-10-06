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

enum
{
    CHOICE_GRID = 0x3b8,
    CHOICE_ROW = 0x194,
    CHOICE_COLUMN = 0x198,
    CHOICE_CHECK = 0x42a1b0,
    CHOICE_HANDLER = 0x451e20,
    CHOICE_ASK = 0x42a190,
    CHOICE_WAIT = 0x43acd0,
    CHOICE_BUSY = 0x43ccb0,
    CHOICE_CELL = 0x42a170,
    CHOICE_PLACE = 0x43c140,
    CHOICE_FINISH = 0x43bbf0,
    CHOICE_LOCAL_FIRST = 0x1c,
    CHOICE_LOCAL_SECOND = 0x18
};

uint32_t vertrix_state_choice_check(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx)
{
    VertrixRegs regs = {player, edx, 0, player};
    uint32_t board;
    uint32_t grid;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, player, CHOICE_GRID, DWORD_WIDTH, &grid))
    {
        return 0;
    }
    regs.ebx = board;
    regs.eax = grid;
    vertrix_regs_call(calls, &regs, CHOICE_CHECK);
    if (regs.eax == 0)
    {
        regs.edx = CHOICE_HANDLER;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    }
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.ecx))
    {
        return 0;
    }
    regs.eax = board;
    vertrix_regs_virtual_at(calls, globals, &regs, regs.ecx, STATE_VIRTUAL_SLOT);
    return regs.eax;
}

uint32_t vertrix_state_choice_apply(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t frame, uint32_t player,
                                    uint32_t ecx)
{
    VertrixRegs regs;
    uint32_t grid;
    uint32_t board;
    uint32_t row;
    uint32_t column;
    uint32_t flag = 0;
    if (!read_value(services, player, CHOICE_GRID, DWORD_WIDTH, &grid) ||
        !read_value(services, player, CHOICE_COLUMN, DWORD_WIDTH, &column) ||
        !read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, player, CHOICE_ROW, DWORD_WIDTH, &row))
    {
        return 0;
    }
    regs.eax = grid;
    regs.edx = row;
    regs.ebx = column;
    regs.ecx = ecx;
    vertrix_regs_call(calls, &regs, CHOICE_ASK);
    if (regs.eax != 1)
    {
        regs.eax = player;
        regs.ecx = 1;
        vertrix_regs_call(calls, &regs, CHOICE_WAIT);
        flag = regs.ecx;
    }
    else
    {
        regs.eax = player;
        vertrix_regs_call(calls, &regs, CHOICE_BUSY);
        if (regs.eax == 0)
        {
            VertrixCallSite site;
            uint32_t pointer = frame - CHOICE_LOCAL_FIRST;
            if (!read_value(services, player, CHOICE_COLUMN, DWORD_WIDTH, &regs.ebx) ||
                !read_value(services, player, CHOICE_ROW, DWORD_WIDTH, &regs.edx))
            {
                return 0;
            }
            regs.eax = grid;
            regs.ecx = frame - CHOICE_LOCAL_SECOND;
            site = (VertrixCallSite){CHOICE_CELL, regs.eax, regs.edx, regs.ebx, regs.ecx, pointer,
                                     0,           0,        0,        0,        {0},      0};
            calls->call(&site, calls->context);
            regs.eax = player;
            regs.ebx = site.out_value & 0xff;
            regs.edx = site.out_ecx & 0xff;
            vertrix_regs_call(calls, &regs, CHOICE_PLACE);
            if (regs.eax == 0)
            {
                regs.eax = player;
                regs.ebx = 1;
                vertrix_regs_call(calls, &regs, CHOICE_WAIT);
                flag = regs.ebx;
            }
        }
    }
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.edx))
    {
        return 0;
    }
    regs.eax = board;
    vertrix_regs_virtual(calls, globals, &regs, STATE_VIRTUAL_SLOT);
    if (flag == 1)
    {
        regs.eax = player;
        vertrix_regs_call(calls, &regs, CHOICE_FINISH);
    }
    return regs.eax;
}

enum
{
    TAKE_OPPONENT = 0x3b0,
    TAKE_CELL = 0x42a140,
    TAKE_HANDLER = 0x451dd0,
    TAKE_FIRST = 0x43bae0,
    TAKE_SOUNDS = 0x43bd90,
    TAKE_LOCAL_FIRST = 0x18,
    TAKE_LOCAL_SECOND = 0x1c,
    TAKE_LOCAL_THIRD = 0x34,
    TAKE_LOCAL_FOURTH = 0x30,
    MATCH_BOARD = 0x4328a0,
    MATCH_FLAG = 0x44c,
    MATCH_PROGRESS = 0x452250,
    MATCH_QUERY = 0x43ba70,
    MATCH_CLEAR = 0x43ba80,
    MATCH_BONUS_HANDLER = 0x451a60,
    MATCH_FALLBACK_HANDLER = 0x450ff0,
    MATCH_PERIOD = 0x4ac7d0,
    MATCH_PERIOD_TABLE = 0x4f7bf4,
    MATCH_WORD_TABLE = 0x4f7c00,
    MATCH_NEW_HANDLER = 0x452770,
    MATCH_TIMER = 0x4ac510,
    MATCH_WORD_FIELD = 0x1a,
    MATCH_COUNTER = 0x58,
    ATTACK_AMOUNT = 0x3f0,
    ATTACK_CHECK = 0x4316c0,
    ATTACK_STATE = 0x428,
    ATTACK_PERIOD_TABLE = 0x4f7c24,
    ATTACK_WORD_TABLE = 0x4f7c30,
    ATTACK_HANDLER = 0x452520,
    ATTACK_SOUND = 0x4f8188
};

uint32_t vertrix_state_choice_take(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t frame, uint32_t player,
                                   uint32_t ecx)
{
    VertrixRegs regs;
    uint32_t grid;
    uint32_t opponent;
    uint32_t board;
    uint32_t row;
    uint32_t column;
    uint32_t flag = 0;
    if (!read_value(services, player, CHOICE_GRID, DWORD_WIDTH, &grid) ||
        !read_value(services, player, CHOICE_COLUMN, DWORD_WIDTH, &column) ||
        !read_value(services, player, TAKE_OPPONENT, DWORD_WIDTH, &opponent) ||
        !read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, player, CHOICE_ROW, DWORD_WIDTH, &row))
    {
        return 0;
    }
    regs.eax = grid;
    regs.edx = row;
    regs.ebx = column;
    regs.ecx = ecx;
    vertrix_regs_call(calls, &regs, CHOICE_ASK);
    if (regs.eax != 1)
    {
        flag = 1;
    }
    else
    {
        VertrixCallSite site;
        uint32_t first;
        uint32_t second;
        uint32_t third;
        uint32_t fourth;
        regs.eax = grid;
        if (!read_value(services, player, CHOICE_COLUMN, DWORD_WIDTH, &regs.ebx) ||
            !read_value(services, player, CHOICE_ROW, DWORD_WIDTH, &regs.edx))
        {
            return 0;
        }
        vertrix_regs_call(calls, &regs, TAKE_CELL);
        regs.edx = TAKE_HANDLER;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        regs.edx = 4;
        regs.eax = player;
        regs.ecx = frame - TAKE_LOCAL_FIRST;
        site = (VertrixCallSite){TAKE_FIRST, regs.eax, regs.edx, regs.ebx, regs.ecx, 0,
                                 0,          0,        0,        0,        {0},      0};
        calls->call(&site, calls->context);
        first = site.out_ecx;
        if (!read_value(services, player, CHOICE_COLUMN, DWORD_WIDTH, &regs.ebx) ||
            !read_value(services, player, CHOICE_ROW, DWORD_WIDTH, &regs.edx))
        {
            return 0;
        }
        regs.eax = grid;
        site = (VertrixCallSite){
            CHOICE_CELL, regs.eax, regs.edx, regs.ebx, regs.ecx, frame - TAKE_LOCAL_SECOND,
            0,           0,        0,        0,        {0},      0};
        calls->call(&site, calls->context);
        second = site.out_value;
        regs.ebx = second & 0xff;
        regs.edx = first & 0xff;
        regs.eax = player;
        regs.ecx = frame - TAKE_LOCAL_THIRD;
        site = (VertrixCallSite){
            TAKE_SOUNDS, regs.eax, regs.edx, regs.ebx, regs.ecx, frame - TAKE_LOCAL_FOURTH,
            0,           0,        0,        0,        {0},      0};
        calls->call(&site, calls->context);
        third = site.out_ecx;
        fourth = site.out_value;
        regs.edx = third;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SOUND);
        regs.edx = fourth;
        regs.eax = opponent;
        vertrix_regs_call(calls, &regs, STATE_SOUND);
    }
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.edx))
    {
        return 0;
    }
    regs.eax = board;
    regs.ebx = flag;
    vertrix_regs_virtual(calls, globals, &regs, STATE_VIRTUAL_SLOT);
    if (flag == 1)
    {
        regs.eax = player;
        vertrix_regs_call(calls, &regs, CHOICE_FINISH);
    }
    return regs.eax;
}

uint32_t vertrix_state_match_452160(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx)
{
    VertrixRegs regs = {0, edx, 0, player};
    uint32_t board;
    uint32_t flag;
    uint32_t index;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ebx = board;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, MATCH_BOARD);
    if (regs.eax == 1)
    {
        index = globals->read(STATE_SPEED_INDEX, globals->context);
        regs.edx = globals->read(MATCH_PERIOD_TABLE + index * 4, globals->context);
        regs.eax = board;
        vertrix_regs_call(calls, &regs, MATCH_PERIOD);
        index = globals->read(STATE_SPEED_INDEX, globals->context);
        if (!vertrix_build_store(services, board, MATCH_WORD_FIELD, 2,
                                 globals->read(MATCH_WORD_TABLE + index * 4, globals->context)) ||
            !vertrix_build_store(services, board, MATCH_COUNTER, DWORD_WIDTH, 0))
        {
            return 0;
        }
        regs.edx = MATCH_NEW_HANDLER;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, MATCH_TIMER);
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        return finish_edx(calls, services, globals, &regs, board);
    }
    if (!read_value(services, player, MATCH_FLAG, DWORD_WIDTH, &flag))
    {
        return 0;
    }
    if (flag == 1)
    {
        regs.eax = player;
        vertrix_regs_call(calls, &regs, MATCH_PROGRESS);
        return finish_edx(calls, services, globals, &regs, board);
    }
    regs.eax = player;
    vertrix_regs_call(calls, &regs, MATCH_QUERY);
    if (regs.eax == 1)
    {
        regs.edx = MATCH_BONUS_HANDLER;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        regs.edx = 2;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, TAKE_FIRST);
        regs.eax = player;
        vertrix_regs_call(calls, &regs, MATCH_CLEAR);
    }
    else
    {
        regs.edx = MATCH_FALLBACK_HANDLER;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        regs.eax = player;
        regs.edx = 0;
        vertrix_regs_call(calls, &regs, TAKE_FIRST);
    }
    return finish_edx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_attack_452440(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, uint32_t player)
{
    VertrixRegs regs;
    uint32_t opponent;
    uint32_t board;
    uint32_t amount;
    uint32_t opponent_board;
    uint32_t state;
    uint32_t flag = 0;
    uint32_t index;
    if (!read_value(services, player, TAKE_OPPONENT, DWORD_WIDTH, &opponent) ||
        !read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, player, ATTACK_AMOUNT, DWORD_WIDTH, &amount) ||
        !read_value(services, opponent, STATE_BOARD, DWORD_WIDTH, &opponent_board) ||
        !read_value(services, opponent, ATTACK_STATE, DWORD_WIDTH, &state))
    {
        return 0;
    }
    regs.eax = opponent_board;
    regs.edx = state;
    regs.ebx = amount;
    regs.ecx = board;
    vertrix_regs_call(calls, &regs, ATTACK_CHECK);
    if (regs.eax == 1)
    {
        index = globals->read(STATE_SPEED_INDEX, globals->context);
        regs.edx = globals->read(ATTACK_PERIOD_TABLE + index * 4, globals->context);
        regs.eax = board;
        vertrix_regs_call(calls, &regs, STATE_START_PERIOD);
        index = globals->read(STATE_SPEED_INDEX, globals->context);
        if (!vertrix_build_store(services, board, MATCH_WORD_FIELD, 2,
                                 globals->read(ATTACK_WORD_TABLE + index * 4, globals->context)) ||
            !vertrix_build_store(services, board, MATCH_COUNTER, DWORD_WIDTH, 0))
        {
            return 0;
        }
        regs.edx = ATTACK_HANDLER;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, MATCH_TIMER);
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        regs.edx = globals->read(ATTACK_SOUND, globals->context);
        regs.eax = opponent;
        vertrix_regs_call(calls, &regs, STATE_SOUND);
    }
    else
    {
        flag = 1;
    }
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.edx))
    {
        return 0;
    }
    regs.eax = board;
    vertrix_regs_virtual(calls, globals, &regs, STATE_VIRTUAL_SLOT);
    if (!read_value(services, opponent_board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.edx))
    {
        return 0;
    }
    regs.eax = opponent_board;
    vertrix_regs_virtual(calls, globals, &regs, STATE_VIRTUAL_SLOT);
    if (flag == 1)
    {
        regs.eax = player;
        vertrix_regs_call(calls, &regs, CHOICE_FINISH);
        regs.eax = opponent;
        vertrix_regs_call(calls, &regs, CHOICE_FINISH);
    }
    return regs.eax;
}

enum
{
    ADVANCE_FALLBACK_HANDLER = 0x451920,
    ADVANCE_PREPARE = 0x4ac500,
    ADVANCE_STEP = 0x4ac590,
    ADVANCE_STEPS_FIELD = 0x18,
    ADVANCE_WRAP = 0x432a30,
    ADVANCE_NO_WRAP = 0x432b10,
    ADVANCE_LIMIT = 0x18
};

uint32_t vertrix_state_advance_452770(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, uint32_t player, uint32_t edx)
{
    VertrixRegs regs = {player, edx, player, 0};
    uint32_t board;
    uint32_t steps;
    uint32_t counter;
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    regs.ecx = board;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, MATCH_BOARD);
    if (regs.eax != 1)
    {
        regs.edx = ADVANCE_FALLBACK_HANDLER;
        regs.eax = player;
        vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
        return finish_edx(calls, services, globals, &regs, board);
    }
    regs.eax = board;
    vertrix_regs_call(calls, &regs, ADVANCE_PREPARE);
    if (!read_value(services, board, ADVANCE_STEPS_FIELD, DWORD_WIDTH, &steps))
    {
        return 0;
    }
    regs.edx = (uint32_t)((int32_t)steps >> 16);
    regs.eax = board;
    vertrix_regs_call(calls, &regs, ADVANCE_STEP);
    regs.ebx = regs.eax;
    if (regs.eax != 0)
    {
        regs.eax = board;
        vertrix_regs_call(calls, &regs, MATCH_TIMER);
        if (!read_value(services, board, MATCH_COUNTER, DWORD_WIDTH, &counter) ||
            !vertrix_build_store(services, board, MATCH_COUNTER, DWORD_WIDTH, counter + regs.ebx))
        {
            return 0;
        }
    }
    if (!read_value(services, board, MATCH_COUNTER, DWORD_WIDTH, &counter))
    {
        return 0;
    }
    if ((int32_t)counter < ADVANCE_LIMIT)
    {
        regs.eax = board;
        vertrix_regs_call(calls, &regs, ADVANCE_NO_WRAP);
        return finish_edx(calls, services, globals, &regs, board);
    }
    regs.eax = board;
    vertrix_regs_call(calls, &regs, ADVANCE_WRAP);
    if (!read_value(services, board, MATCH_COUNTER, DWORD_WIDTH, &counter))
    {
        return 0;
    }
    while ((int32_t)counter >= ADVANCE_LIMIT)
    {
        counter -= ADVANCE_LIMIT;
        if (!vertrix_build_store(services, board, MATCH_COUNTER, DWORD_WIDTH, counter))
        {
            return 0;
        }
    }
    return finish_edx(calls, services, globals, &regs, board);
}

enum
{
    PAIR_MARK = 0x44c860,
    PAIR_SECOND_MARK = 0x44c940,
    PAIR_ASK_FIRST = 0x42eca0,
    PAIR_ASK_SECOND = 0x42ecc0,
    PAIR_ASK_THIRD = 0x42edf0,
    PAIR_REMOVE = 0x42eb60,
    PAIR_DONE = 0x42ebe0,
    PAIR_CLEAR_FIELD = 0xb8c
};

uint32_t vertrix_state_pair_453050(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t player)
{
    VertrixRegs regs;
    uint32_t opponent;
    uint32_t board;
    uint32_t other;
    uint32_t flag = 0;
    if (!read_value(services, player, TAKE_OPPONENT, DWORD_WIDTH, &opponent) ||
        !read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, opponent, STATE_BOARD, DWORD_WIDTH, &other))
    {
        return 0;
    }
    regs.ebx = board;
    regs.ecx = other;
    regs.edx = PAIR_MARK;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, PAIR_ASK_FIRST);
    if (regs.eax != 0)
    {
        regs.edx = PAIR_MARK;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, PAIR_ASK_SECOND);
    }
    if (regs.eax != 0)
    {
        regs.edx = PAIR_MARK;
        regs.eax = other;
        vertrix_regs_call(calls, &regs, PAIR_ASK_FIRST);
    }
    if (regs.eax != 0)
    {
        regs.edx = PAIR_MARK;
        regs.eax = other;
        vertrix_regs_call(calls, &regs, PAIR_ASK_SECOND);
    }
    if (regs.eax != 0)
    {
        int ready;
        regs.edx = PAIR_MARK;
        regs.eax = other;
        vertrix_regs_call(calls, &regs, PAIR_ASK_THIRD);
        ready = regs.eax != 0;
        if (!ready)
        {
            regs.edx = PAIR_SECOND_MARK;
            regs.eax = other;
            vertrix_regs_call(calls, &regs, PAIR_ASK_THIRD);
            ready = regs.eax != 0;
        }
        if (ready)
        {
            regs.edx = PAIR_SECOND_MARK;
            regs.eax = other;
            vertrix_regs_call(calls, &regs, PAIR_ASK_THIRD);
            if (regs.eax != 0)
            {
                regs.eax = other;
                vertrix_regs_call(calls, &regs, PAIR_REMOVE);
            }
            regs.eax = board;
            vertrix_regs_call(calls, &regs, PAIR_DONE);
            regs.eax = other;
            vertrix_regs_call(calls, &regs, PAIR_DONE);
            flag = 1;
        }
    }
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.edx))
    {
        return 0;
    }
    regs.eax = board;
    vertrix_regs_virtual(calls, globals, &regs, STATE_VIRTUAL_SLOT);
    if (flag != 1)
    {
        return regs.eax;
    }
    regs.eax = player;
    vertrix_regs_call(calls, &regs, CHOICE_FINISH);
    regs.eax = opponent;
    vertrix_regs_call(calls, &regs, CHOICE_FINISH);
    if (!vertrix_build_store(services, board, PAIR_CLEAR_FIELD, DWORD_WIDTH, 0) ||
        !vertrix_build_store(services, other, PAIR_CLEAR_FIELD, DWORD_WIDTH, 0))
    {
        return 0;
    }
    return regs.eax;
}

enum
{
    COMBINE_SOUND = 0x4f81ac,
    COMBINE_VALUE = 0x3dc,
    COMBINE_COUNT = 0x43c,
    COMBINE_LAST = 0x440,
    COMBINE_TAKE = 0x436aa0,
    COMBINE_JOIN = 0x436d80,
    COMBINE_HANDLER = 0x4533b0
};

uint32_t vertrix_state_combine_453320(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, uint32_t player, uint32_t ebx,
                                      uint32_t ecx)
{
    VertrixRegs regs = {player, 0, ebx, ecx};
    uint32_t opponent;
    uint32_t other;
    uint32_t board;
    uint32_t value;
    uint32_t last;
    if (!read_value(services, player, TAKE_OPPONENT, DWORD_WIDTH, &opponent) ||
        !read_value(services, opponent, STATE_BOARD, DWORD_WIDTH, &other))
    {
        return 0;
    }
    regs.eax = opponent;
    regs.edx = globals->read(COMBINE_SOUND, globals->context);
    if (!read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    vertrix_regs_call(calls, &regs, STATE_SOUND);
    if (!read_value(services, player, COMBINE_VALUE, DWORD_WIDTH, &value))
    {
        return 0;
    }
    regs.eax = board;
    regs.edx = value;
    vertrix_regs_call(calls, &regs, COMBINE_TAKE);
    regs.eax = other;
    regs.edx = value;
    vertrix_regs_call(calls, &regs, COMBINE_TAKE);
    if (!read_value(services, player, COMBINE_LAST, DWORD_WIDTH, &last) ||
        !read_value(services, player, COMBINE_COUNT, DWORD_WIDTH, &regs.ecx) ||
        !read_value(services, player, COMBINE_VALUE, DWORD_WIDTH, &regs.ebx))
    {
        return 0;
    }
    regs.eax = board;
    regs.edx = other;
    vertrix_regs_calln(calls, &regs, COMBINE_JOIN, &last, 1);
    regs.edx = COMBINE_HANDLER;
    regs.eax = player;
    vertrix_regs_call(calls, &regs, STATE_SET_HANDLER);
    return finish_edx(calls, services, globals, &regs, board);
}

uint32_t vertrix_state_pair_4533b0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t player)
{
    VertrixRegs regs;
    uint32_t opponent;
    uint32_t board;
    uint32_t other;
    uint32_t flag = 0;
    if (!read_value(services, player, TAKE_OPPONENT, DWORD_WIDTH, &opponent) ||
        !read_value(services, player, STATE_BOARD, DWORD_WIDTH, &board) ||
        !read_value(services, opponent, STATE_BOARD, DWORD_WIDTH, &other))
    {
        return 0;
    }
    regs.ecx = board;
    regs.ebx = other;
    regs.edx = PAIR_MARK;
    regs.eax = board;
    vertrix_regs_call(calls, &regs, PAIR_ASK_FIRST);
    if (regs.eax != 0)
    {
        regs.edx = PAIR_MARK;
        regs.eax = board;
        vertrix_regs_call(calls, &regs, PAIR_ASK_SECOND);
    }
    if (regs.eax != 0)
    {
        regs.edx = PAIR_MARK;
        regs.eax = other;
        vertrix_regs_call(calls, &regs, PAIR_ASK_FIRST);
    }
    if (regs.eax != 0)
    {
        regs.edx = PAIR_MARK;
        regs.eax = other;
        vertrix_regs_call(calls, &regs, PAIR_ASK_SECOND);
    }
    if (regs.eax != 0)
    {
        regs.eax = board;
        vertrix_regs_call(calls, &regs, PAIR_DONE);
        regs.eax = other;
        regs.ebx = 1;
        vertrix_regs_call(calls, &regs, PAIR_DONE);
        flag = 1;
    }
    if (!read_value(services, board, STATE_BOARD_TABLE, DWORD_WIDTH, &regs.ebx))
    {
        return 0;
    }
    regs.eax = board;
    vertrix_regs_virtual_at(calls, globals, &regs, regs.ebx, STATE_VIRTUAL_SLOT);
    if (flag == 1)
    {
        regs.eax = player;
        vertrix_regs_call(calls, &regs, CHOICE_FINISH);
        regs.eax = opponent;
        vertrix_regs_call(calls, &regs, CHOICE_FINISH);
    }
    return regs.eax;
}
