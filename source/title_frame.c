#include "title_frame.h"

/* Static flags and slots of the original, named by what the frame does with them. */
enum
{
    STARTED = 0x540338,       /* byte: the first frame's setup has run */
    LISTS_STARTED = 0x54033c, /* dword: the scene lists have been started this screen */
    SCREEN_MODE = 0x532b40,   /* dword: 1 while the screen has a transition */
    MODE_FORWARD = 0x532b48,  /* dword: the transition goes to the first target */
    MODE_BACKWARD = 0x532b44, /* dword: the transition goes to the second target */
    CURRENT_SCREEN = 0x532a50,
    REQUESTED_SCREEN = 0x532a98,
    CLOSING = 0x532a38,
    PLAYING = 0x532a84,
    PLAY_READY = 0x532a7c,
    FIRST_SCREEN = 0x4f7bb0,
    SECOND_SCREEN = 0x4f7bb4,
    BACK_BUFFER_OBJECT = 0x558c84,
    BACK_BUFFER_SIZE = 0x558c88,
    FRONT_BUFFER_OBJECT = 0x558c7c,
    DRAW_SURFACE = 0x5b9c50,
    TITLE_NEXT_HANDLER = 0x41c9e0,
    MENU_NEXT_HANDLER = 0x41cbb0
};

static uint32_t read_dword(const VertrixGlobals *globals, uint32_t address)
{
    return globals->read(address, globals->context);
}

static uint32_t call_eax(const VertrixCalls *calls, uint32_t routine, uint32_t eax)
{
    return vertrix_call(calls, routine, eax, 0, 0, 0, 0);
}

static void call_with_edx(const VertrixCalls *calls, uint32_t routine, uint32_t eax, uint32_t edx)
{
    vertrix_call(calls, routine, eax, edx, 0, 0, 0);
}

/* The state transitions after the stages: 0x418840 installs the next idle handler. */
static void install_handler(const VertrixCalls *calls, uint32_t form, uint32_t handler)
{
    vertrix_global_store(calls, STARTED, 1, 0);
    call_with_edx(calls, 0x418840, form, handler);
}

uint32_t vertrix_title_frame(const VertrixCalls *calls, const VertrixGlobals *globals,
                             uint32_t form)
{
    if ((read_dword(globals, STARTED) & 0xff) == 0)
    {
        vertrix_global_store(calls, STARTED, 1, 1);
        call_eax(calls, 0x41d640, form);
        vertrix_global_store(calls, LISTS_STARTED, 4, 0);
    }
    call_eax(calls, 0x4b7d10, 0);
    call_eax(calls, 0x41d670, form);
    call_eax(calls, 0x41dec0, form);
    call_eax(calls, 0x4ac1c0, 0);
    call_eax(calls, 0x419490, form);
    if (read_dword(globals, SCREEN_MODE) == 1)
    {
        call_eax(calls, 0x472d90, 0);
    }
    call_eax(calls, 0x471a70, 0);
    if (read_dword(globals, LISTS_STARTED) == 0)
    {
        call_eax(calls, 0x471a60, 0);
        vertrix_global_store(calls, LISTS_STARTED, 4, 1);
    }
    if (call_eax(calls, 0x4854a0, DRAW_SURFACE) == 1)
    {
        call_with_edx(calls, 0x471a20, read_dword(globals, BACK_BUFFER_OBJECT),
                      read_dword(globals, BACK_BUFFER_SIZE));
        call_eax(calls, 0x471a40, read_dword(globals, BACK_BUFFER_OBJECT));
        call_eax(calls, 0x485520, DRAW_SURFACE);
    }
    call_eax(calls, 0x41aaf0, form);
    call_eax(calls, 0x486d00, DRAW_SURFACE);
    call_eax(calls, 0x471a50, read_dword(globals, FRONT_BUFFER_OBJECT));
    call_eax(calls, 0x4194b0, form);
    if (read_dword(globals, SCREEN_MODE) == 1)
    {
        if (read_dword(globals, MODE_FORWARD) == 1)
        {
            call_eax(calls, 0x415530, 0);
            vertrix_global_store(calls, CURRENT_SCREEN, 4, read_dword(globals, FIRST_SCREEN));
            call_eax(calls, 0x472d50, 0);
        }
        else if (read_dword(globals, MODE_BACKWARD) == 1)
        {
            call_eax(calls, 0x415530, 0);
            vertrix_global_store(calls, CURRENT_SCREEN, 4, read_dword(globals, SECOND_SCREEN));
            call_eax(calls, 0x415550, 0);
            call_eax(calls, 0x472d50, 0);
        }
    }
    call_eax(calls, 0x41d6d0, form);
    call_eax(calls, 0x41dd60, form);
    call_eax(calls, 0x486da0, DRAW_SURFACE);
    call_eax(calls, 0x487020, DRAW_SURFACE);
    call_eax(calls, 0x41d660, form);
    call_eax(calls, 0x41de80, form);
    if (read_dword(globals, CLOSING) == 1)
    {
        call_eax(calls, 0x41aca0, form);
        vertrix_global_store(calls, LISTS_STARTED, 4, 0);
    }
    {
        uint32_t current = read_dword(globals, CURRENT_SCREEN);
        if (current != read_dword(globals, REQUESTED_SCREEN))
        {
            if (current == read_dword(globals, FIRST_SCREEN))
            {
                install_handler(calls, form, TITLE_NEXT_HANDLER);
            }
            else if (current == read_dword(globals, SECOND_SCREEN))
            {
                install_handler(calls, form, MENU_NEXT_HANDLER);
            }
            vertrix_global_store(calls, CURRENT_SCREEN, 4, read_dword(globals, REQUESTED_SCREEN));
        }
    }
    if (read_dword(globals, PLAYING) == 1 && read_dword(globals, PLAY_READY) == 1 &&
        call_eax(calls, 0x418130, 0) == 0)
    {
        install_handler(calls, form, MENU_NEXT_HANDLER);
    }
    return 0;
}
