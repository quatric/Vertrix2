#include "game_frame.h"

/* Static flags and slots of the original. */
enum
{
    STARTED = 0x540330,       /* byte: the first frame's setup has run */
    LISTS_STARTED = 0x540334, /* dword: the scene lists have been started */
    PLAY_PHASE = 0x532a0c,    /* dword: 1 once the screen has started, 0 after it handed over */
    SCREEN_MODE = 0x532b40,   /* dword: 1 while the screen has a transition */
    MODE_FORWARD = 0x532b48,
    MODE_BACKWARD = 0x532b44,
    CURRENT_SCREEN = 0x532a4c,
    REQUESTED_SCREEN = 0x532a98,
    CLOSING = 0x532a38,
    FRONT_BUFFER_OBJECT = 0x558c7c,
    BACK_BUFFER_OBJECT = 0x558c84,
    BACK_BUFFER_SIZE = 0x558c88,
    DRAW_SURFACE = 0x5b9c50,
    DIALOG_OBJECT = 0x5bb254,
    CONFIRM_FLAG = 0x532a34, /* byte */
    PROFILE_COUNT = 0x532bcc,
    /* The play state cleared and set by the level screens. */
    STATE_74 = 0x532a74,
    STATE_78 = 0x532a78,
    STATE_7C = 0x532a7c,
    STATE_80 = 0x532a80,
    STATE_84 = 0x532a84,
    LEVEL_MODE = 0x532a8c,
    /* The four level settings and their copies. */
    SETTING_0 = 0x532b54,
    COPY_0 = 0x532bbc,
    /* Screen numbers of the original, held in a table of dwords. */
    EXIT_TO_FIRST = 0x4f7ba8,
    EXIT_TO_SECOND = 0x4f7bac,
    /* The handlers 0x418840 installs. */
    HANDLER_C0C0 = 0x41c0c0,
    HANDLER_C0F0 = 0x41c0f0,
    HANDLER_C080 = 0x41c080,
    HANDLER_C160 = 0x41c160,
    HANDLER_C1D0 = 0x41c1d0,
    HANDLER_C240 = 0x41c240,
    HANDLER_C2B0 = 0x41c2b0
};

/* The screens of the transition table, by the address of the dword that holds their number. */
enum
{
    SCREEN_B44 = 0x4f7b44,
    SCREEN_B48 = 0x4f7b48,
    SCREEN_B4C = 0x4f7b4c,
    SCREEN_B50 = 0x4f7b50,
    SCREEN_B54 = 0x4f7b54,
    SCREEN_B58 = 0x4f7b58,
    SCREEN_B5C = 0x4f7b5c,
    SCREEN_B60 = 0x4f7b60,
    SCREEN_B64 = 0x4f7b64,
    SCREEN_B68 = 0x4f7b68,
    SCREEN_B6C = 0x4f7b6c,
    SCREEN_B70 = 0x4f7b70,
    SCREEN_B74 = 0x4f7b74,
    SCREEN_B78 = 0x4f7b78,
    SCREEN_B7C = 0x4f7b7c,
    SCREEN_B80 = 0x4f7b80,
    SCREEN_B84 = 0x4f7b84,
    SCREEN_B88 = 0x4f7b88,
    SCREEN_B8C = 0x4f7b8c,
    SCREEN_B90 = 0x4f7b90,
    SCREEN_B94 = 0x4f7b94,
    SCREEN_B98 = 0x4f7b98,
    SCREEN_B9C = 0x4f7b9c,
    SCREEN_BA4 = 0x4f7ba4,
    SCREEN_BA8 = 0x4f7ba8,
    SCREEN_BAC = 0x4f7bac
};

static uint32_t read_dword(const VertrixGlobals *globals, uint32_t address)
{
    return globals->read(address, globals->context);
}

static void call_eax(const VertrixCalls *calls, uint32_t routine, uint32_t eax)
{
    vertrix_call(calls, routine, eax, 0, 0, 0, 0);
}

static void call_pair(const VertrixCalls *calls, uint32_t routine, uint32_t eax, uint32_t edx)
{
    vertrix_call(calls, routine, eax, edx, 0, 0, 0);
}

static void store_dword(const VertrixCalls *calls, uint32_t address, uint32_t value)
{
    vertrix_global_store(calls, address, 4, value);
}

static void install_handler(const VertrixCalls *calls, uint32_t form, uint32_t handler)
{
    call_pair(calls, 0x418840, form, handler);
}

/* The screens that clear the scene list and hand over to one screen routine. */
static void run_screen(const VertrixCalls *calls, uint32_t routine, uint32_t eax)
{
    call_eax(calls, 0x4719e0, 0);
    call_eax(calls, routine, eax);
}

/* A level screen: copy the four settings, set the play state, run the resets and install the
 * handler of the level. `with_profile_reset` also runs 0x415c60 first. */
static void begin_level(const VertrixCalls *calls, const VertrixGlobals *globals, uint32_t form,
                        uint32_t state74, uint32_t state78, uint32_t mode, uint32_t handler,
                        int with_profile_reset)
{
    unsigned i;

    for (i = 0; i < 4; i++)
    {
        store_dword(calls, COPY_0 + 4 * i, read_dword(globals, SETTING_0 + 4 * i));
    }
    store_dword(calls, STATE_74, state74);
    store_dword(calls, STATE_78, state78);
    store_dword(calls, LEVEL_MODE, mode);
    if (with_profile_reset)
    {
        call_eax(calls, 0x415c60, 0);
    }
    call_eax(calls, 0x415b50, 0);
    call_eax(calls, 0x415b10, 0);
    store_dword(calls, STATE_84, 0);
    store_dword(calls, STATE_7C, 0);
    store_dword(calls, STATE_80, 0);
    vertrix_global_store(calls, STARTED, 1, 0);
    install_handler(calls, form, handler);
}

/* Leaving the screen with a menu return: stop, then install the handler. */
static void leave_with(const VertrixCalls *calls, uint32_t form, uint32_t handler)
{
    vertrix_global_store(calls, STARTED, 1, 0);
    install_handler(calls, form, handler);
}

/* The level screens with their own start (0x4f7b70 and 0x4f7b74): reset the play state to
 * "running", then choose the handler from the profile count. */
static void finish_start(const VertrixCalls *calls, const VertrixGlobals *globals, uint32_t form)
{
    if (read_dword(globals, PROFILE_COUNT) == 0)
    {
        store_dword(calls, LEVEL_MODE, 2);
        install_handler(calls, form, HANDLER_C240);
    }
    else
    {
        store_dword(calls, LEVEL_MODE, 3);
        install_handler(calls, form, HANDLER_C2B0);
    }
}

/* The transition out of the screen whose number is `current`, in the order the original tests the
 * numbers (the same number may sit in several slots of the table). */
static void leave_screen(const VertrixCalls *calls, const VertrixGlobals *globals, uint32_t form,
                         uint32_t current)
{
    if (current == read_dword(globals, SCREEN_B48))
    {
        run_screen(calls, 0x461610, 0);
    }
    else if (current == read_dword(globals, SCREEN_B4C))
    {
        run_screen(calls, 0x461790, 0);
    }
    else if (current == read_dword(globals, SCREEN_B50))
    {
        leave_with(calls, form, HANDLER_C0C0);
    }
    else if (current == read_dword(globals, SCREEN_BA4))
    {
        leave_with(calls, form, HANDLER_C080);
    }
    else if (current == read_dword(globals, SCREEN_B54))
    {
        begin_level(calls, globals, form, 1, 0, 0, HANDLER_C160, 1);
    }
    else if (current == read_dword(globals, SCREEN_B58))
    {
        begin_level(calls, globals, form, 1, 0, 1, HANDLER_C1D0, 0);
    }
    else if (current == read_dword(globals, SCREEN_B5C) ||
             current == read_dword(globals, SCREEN_B6C))
    {
        run_screen(calls, 0x461360, 0);
    }
    else if (current == read_dword(globals, SCREEN_B60))
    {
        begin_level(calls, globals, form, 1, 1, 2, HANDLER_C240, 0);
    }
    else if (current == read_dword(globals, SCREEN_B64))
    {
        begin_level(calls, globals, form, 1, 1, 3, HANDLER_C2B0, 0);
    }
    else if (current == read_dword(globals, SCREEN_B68))
    {
        run_screen(calls, 0x4633b0, 0);
    }
    else if (current == read_dword(globals, SCREEN_B70))
    {
        store_dword(calls, STATE_74, 1);
        store_dword(calls, STATE_78, 1);
        call_eax(calls, 0x415b90, 0);
        call_eax(calls, 0x415b10, 0);
        store_dword(calls, STATE_84, 1);
        store_dword(calls, STATE_80, 1);
        store_dword(calls, STATE_7C, 0);
        call_eax(calls, 0x48c6c0, DIALOG_OBJECT);
        vertrix_global_store(calls, STARTED, 1, 0);
        finish_start(calls, globals, form);
    }
    else if (current == read_dword(globals, SCREEN_B74))
    {
        store_dword(calls, STATE_74, 1);
        store_dword(calls, STATE_78, 1);
        call_eax(calls, 0x415bd0, 0);
        call_eax(calls, 0x415b10, 0);
        store_dword(calls, STATE_84, 1);
        store_dword(calls, STATE_7C, 1);
        store_dword(calls, STATE_80, 0);
        call_eax(calls, 0x48c6c0, DIALOG_OBJECT);
        call_eax(calls, 0x48c2b0, DIALOG_OBJECT);
        vertrix_global_store(calls, STARTED, 1, 0);
        finish_start(calls, globals, form);
    }
    else if (current == read_dword(globals, SCREEN_B78))
    {
        if ((read_dword(globals, CONFIRM_FLAG) & 0xff) == 1)
        {
            leave_with(calls, form, HANDLER_C0C0);
        }
        else
        {
            run_screen(calls, 0x461610, 0);
        }
        call_eax(calls, 0x48b770, DIALOG_OBJECT);
    }
    else if (current == read_dword(globals, SCREEN_B7C))
    {
        run_screen(calls, 0x461930, 0);
    }
    else if (current == read_dword(globals, SCREEN_B80))
    {
        run_screen(calls, 0x461fc0, 0);
    }
    else if (current == read_dword(globals, SCREEN_B98))
    {
        run_screen(calls, 0x4627a0, 0);
    }
    else if (current == read_dword(globals, SCREEN_B84))
    {
        run_screen(calls, 0x4651b0, 0xffffffff);
    }
    else if (current == read_dword(globals, SCREEN_B88))
    {
        run_screen(calls, 0x461360, 0);
    }
    else if (current == read_dword(globals, SCREEN_B8C) ||
             current == read_dword(globals, SCREEN_B90) ||
             current == read_dword(globals, SCREEN_B94) ||
             current == read_dword(globals, SCREEN_B9C))
    {
        run_screen(calls, 0x461790, 0);
    }
    else if (current == read_dword(globals, SCREEN_BA8))
    {
        begin_level(calls, globals, form, 0, 0, 2, HANDLER_C240, 0);
    }
    else if (current == read_dword(globals, SCREEN_BAC))
    {
        leave_with(calls, form, HANDLER_C0F0);
    }
}

uint32_t vertrix_game_frame(const VertrixCalls *calls, const VertrixGlobals *globals, uint32_t form)
{
    if ((read_dword(globals, STARTED) & 0xff) == 0)
    {
        vertrix_global_store(calls, STARTED, 1, 1);
        call_eax(calls, 0x41d640, form);
        call_eax(calls, 0x4b7cd0, 0);
        store_dword(calls, LISTS_STARTED, 0);
        store_dword(calls, PLAY_PHASE, 1);
    }
    call_eax(calls, 0x4b7d10, 0);
    call_eax(calls, 0x41d670, form);
    call_eax(calls, 0x41dec0, form);
    call_eax(calls, 0x419490, form);
    if (read_dword(globals, SCREEN_MODE) == 1)
    {
        call_eax(calls, 0x472d90, 0);
    }
    call_eax(calls, 0x471a70, 0);
    call_eax(calls, 0x471a80, 0);
    call_eax(calls, 0x471b00, 0);
    if (read_dword(globals, LISTS_STARTED) == 0)
    {
        call_eax(calls, 0x471a60, 0);
        call_eax(calls, 0x471b70, 0);
        call_eax(calls, 0x471af0, 0);
        store_dword(calls, LISTS_STARTED, 1);
    }
    if (vertrix_call(calls, 0x4854a0, DRAW_SURFACE, 0, 0, 0, 0) == 1)
    {
        call_pair(calls, 0x471ab0, read_dword(globals, BACK_BUFFER_OBJECT),
                  read_dword(globals, BACK_BUFFER_SIZE));
        call_pair(calls, 0x471b30, read_dword(globals, BACK_BUFFER_OBJECT),
                  read_dword(globals, BACK_BUFFER_SIZE));
        call_pair(calls, 0x471a20, read_dword(globals, BACK_BUFFER_OBJECT),
                  read_dword(globals, BACK_BUFFER_SIZE));
        call_eax(calls, 0x471ad0, read_dword(globals, BACK_BUFFER_OBJECT));
        call_eax(calls, 0x471b50, read_dword(globals, BACK_BUFFER_OBJECT));
        call_eax(calls, 0x471a40, read_dword(globals, BACK_BUFFER_OBJECT));
        call_eax(calls, 0x485520, DRAW_SURFACE);
    }
    call_eax(calls, 0x41aaf0, form);
    call_eax(calls, 0x486d00, DRAW_SURFACE);
    call_eax(calls, 0x471ae0, read_dword(globals, FRONT_BUFFER_OBJECT));
    call_eax(calls, 0x471b60, read_dword(globals, FRONT_BUFFER_OBJECT));
    call_eax(calls, 0x471a50, read_dword(globals, FRONT_BUFFER_OBJECT));
    call_eax(calls, 0x4194b0, form);
    call_eax(calls, 0x41d6d0, form);
    call_eax(calls, 0x41dd60, form);
    call_eax(calls, 0x486da0, DRAW_SURFACE);
    call_eax(calls, 0x487020, DRAW_SURFACE);
    call_eax(calls, 0x41d660, form);
    call_eax(calls, 0x4154b0, 0);
    call_eax(calls, 0x41de80, form);
    if (read_dword(globals, SCREEN_MODE) == 1)
    {
        if (read_dword(globals, MODE_FORWARD) == 1)
        {
            call_eax(calls, 0x415530, 0);
            store_dword(calls, CURRENT_SCREEN, read_dword(globals, SCREEN_BA8));
            call_eax(calls, 0x472d50, 0);
        }
        else if (read_dword(globals, MODE_BACKWARD) == 1)
        {
            call_eax(calls, 0x415530, 0);
            call_eax(calls, 0x415550, 0);
            call_eax(calls, 0x472d50, 0);
            store_dword(calls, CURRENT_SCREEN, read_dword(globals, SCREEN_BAC));
        }
    }
    if (read_dword(globals, CLOSING) == 1)
    {
        call_eax(calls, 0x41aca0, form);
        store_dword(calls, LISTS_STARTED, 0);
    }
    {
        uint32_t current = read_dword(globals, CURRENT_SCREEN);

        if (current != read_dword(globals, REQUESTED_SCREEN))
        {
            if (current == read_dword(globals, SCREEN_B44))
            {
                run_screen(calls, 0x4614c0, 0);
            }
            else
            {
                leave_screen(calls, globals, form, current);
            }
            store_dword(calls, CURRENT_SCREEN, read_dword(globals, REQUESTED_SCREEN));
        }
    }
    if ((read_dword(globals, STARTED) & 0xff) == 0)
    {
        store_dword(calls, PLAY_PHASE, 0);
    }
    return 0;
}
