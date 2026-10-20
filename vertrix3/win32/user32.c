#include "process.h"
#include "win32.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/* Windows without a desktop: one top-level window whose procedure receives the messages the
 * game expects (creation, activation, input it does not take from DirectInput, close), a
 * message queue fed by the platform's input, and modal dialogs answered with their defaults. */

enum
{
    WM_CREATE = 0x0001,
    WM_DESTROY = 0x0002,
    WM_SIZE = 0x0005,
    WM_ACTIVATE = 0x0006,
    WM_SETFOCUS = 0x0007,
    WM_CLOSE = 0x0010,
    WM_QUIT = 0x0012,
    WM_SHOWWINDOW = 0x0018,
    WM_ACTIVATEAPP = 0x001c,
    WM_SETCURSOR = 0x0020,
    WM_NCCREATE = 0x0081,
    WM_INITDIALOG = 0x0110,
    WM_COMMAND = 0x0111,
    CLASSES = 16,
    WINDOWS = 16,
    QUEUE = 256,
    CONTROLS = 64,
    ITEMS = 32
};

static struct
{
    char name[64];
    uint32_t procedure;
} classes[CLASSES];
static unsigned class_count;

typedef struct
{
    uint32_t handle;
    uint32_t procedure;
    int dialog;
    int32_t x, y, width, height;
    uint32_t style;
} Window;

static Window windows[WINDOWS];
static unsigned window_count;
static uint32_t main_window;

static struct
{
    uint32_t hwnd, message, wparam, lparam, time;
} queue[QUEUE];
static unsigned queue_head, queue_count;
static int quit_posted;

static Window *window(uint32_t hwnd)
{
    for (unsigned i = 0; i < window_count; ++i)
    {
        if (windows[i].handle == hwnd)
        {
            return &windows[i];
        }
    }
    return NULL;
}

uint32_t v3_main_window(void)
{
    return main_window;
}

void v3_post_message(uint32_t hwnd, uint32_t message, uint32_t wparam, uint32_t lparam)
{
    v3_lock();
    if (queue_count < QUEUE)
    {
        const unsigned slot = (queue_head + queue_count) % QUEUE;
        queue[slot].hwnd = hwnd;
        queue[slot].message = message;
        queue[slot].wparam = wparam;
        queue[slot].lparam = lparam;
        queue[slot].time = (uint32_t)(v3_microseconds() / 1000u);
        ++queue_count;
    }
    v3_unlock();
}

static uint32_t send(Cpu *c, uint32_t hwnd, uint32_t message, uint32_t wparam, uint32_t lparam)
{
    Window *w = window(hwnd);
    if (!w || !w->procedure)
    {
        return 0;
    }
    const uint32_t arguments[4] = {hwnd, message, wparam, lparam};
    return v3_call_guest(c, w->procedure, 4, arguments, 0);
}

/* --- classes and windows ------------------------------------------------------------------ */

static void RegisterClassA(Cpu *c)
{
    const uint32_t wc = ARG(0);
    if (class_count == CLASSES)
    {
        STDCALL_RETURN(1, 0);
    }
    v3_read_string(v3_r32(wc + 36), classes[class_count].name, sizeof classes[0].name);
    classes[class_count].procedure = v3_r32(wc + 4);
    v3_log("RegisterClassA(%s, procedure %08x)", classes[class_count].name,
           classes[class_count].procedure);
    ++class_count;
    STDCALL_RETURN(1, 0xc000u + class_count);
}

static void UnregisterClassA(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void CreateWindowExA(Cpu *c)
{
    char name[64], title[128];
    v3_read_string(ARG(1), name, sizeof name);
    v3_read_string(ARG(2), title, sizeof title);
    uint32_t procedure = 0;
    for (unsigned i = 0; i < class_count; ++i)
    {
        if (strcasecmp(classes[i].name, name) == 0)
        {
            procedure = classes[i].procedure;
        }
    }
    if (window_count == WINDOWS)
    {
        STDCALL_RETURN(12, 0);
    }
    Window *w = &windows[window_count++];
    memset(w, 0, sizeof *w);
    w->handle = 0x00010020u + 4u * window_count;
    w->procedure = procedure;
    w->style = ARG(3);
    w->x = (int32_t)ARG(4);
    w->y = (int32_t)ARG(5);
    w->width = (int32_t)ARG(6);
    w->height = (int32_t)ARG(7);
    if (!main_window)
    {
        main_window = w->handle;
    }
    v3_log("CreateWindowExA(%s, \"%s\", %dx%d) -> %08x", name, title, w->width, w->height,
           w->handle);
    /* The creation messages, with a CREATESTRUCTA describing the window. */
    const uint32_t cs = v3_alloc(48);
    v3_w32(cs + 0, ARG(11));
    v3_w32(cs + 4, ARG(10));
    v3_w32(cs + 8, ARG(9));
    v3_w32(cs + 12, ARG(8));
    v3_w32(cs + 16, ARG(7));
    v3_w32(cs + 20, ARG(6));
    v3_w32(cs + 24, ARG(5));
    v3_w32(cs + 28, ARG(4));
    v3_w32(cs + 32, ARG(3));
    v3_w32(cs + 36, ARG(2));
    v3_w32(cs + 40, ARG(1));
    v3_w32(cs + 44, ARG(0));
    const uint32_t hwnd = w->handle;
    send(c, hwnd, WM_NCCREATE, 0, cs);
    const uint32_t created = send(c, hwnd, WM_CREATE, 0, cs);
    v3_free(cs);
    if (created == 0xffffffffu)
    {
        STDCALL_RETURN(12, 0);
    }
    STDCALL_RETURN(12, hwnd);
}

static void DestroyWindow(Cpu *c)
{
    send(c, ARG(0), WM_DESTROY, 0, 0);
    STDCALL_RETURN(1, 1);
}

static void ShowWindow(Cpu *c)
{
    const uint32_t hwnd = ARG(0);
    static int shown;
    if (!shown && hwnd == main_window)
    {
        shown = 1;
        send(c, hwnd, WM_SHOWWINDOW, 1, 0);
        send(c, hwnd, WM_ACTIVATEAPP, 1, 0);
        send(c, hwnd, WM_ACTIVATE, 1, 0);
        send(c, hwnd, WM_SETFOCUS, 0, 0);
    }
    STDCALL_RETURN(2, 0);
}

static void DefWindowProcA(Cpu *c)
{
    const uint32_t hwnd = ARG(0);
    const uint32_t message = ARG(1);
    if (message == WM_CLOSE)
    {
        send(c, hwnd, WM_DESTROY, 0, 0);
    }
    STDCALL_RETURN(4, message == WM_NCCREATE ? 1 : 0);
}

static void SetWindowPos(Cpu *c)
{
    STDCALL_RETURN(7, 1);
}

static void MoveWindow(Cpu *c)
{
    Window *w = window(ARG(0));
    if (w)
    {
        w->x = (int32_t)ARG(1);
        w->y = (int32_t)ARG(2);
        w->width = (int32_t)ARG(3);
        w->height = (int32_t)ARG(4);
    }
    STDCALL_RETURN(6, 1);
}

static void GetWindowRect(Cpu *c)
{
    Window *w = window(ARG(0));
    const uint32_t r = ARG(1);
    const int32_t x = w ? w->x : 0, y = w ? w->y : 0;
    const int32_t width = w ? w->width : 640, height = w ? w->height : 480;
    v3_w32(r, (uint32_t)(x < 0 ? 0 : x));
    v3_w32(r + 4, (uint32_t)(y < 0 ? 0 : y));
    v3_w32(r + 8, (uint32_t)((x < 0 ? 0 : x) + width));
    v3_w32(r + 12, (uint32_t)((y < 0 ? 0 : y) + height));
    STDCALL_RETURN(2, 1);
}

static void AdjustWindowRect(Cpu *c)
{
    STDCALL_RETURN(3, 1);
}

static void SetRect(Cpu *c)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        v3_w32(ARG(0) + 4 * i, ARG(1 + i));
    }
    STDCALL_RETURN(5, 1);
}

static void MapWindowPoints(Cpu *c)
{
    STDCALL_RETURN(4, 0);
}

static void GetWindowPlacement(Cpu *c)
{
    const uint32_t p = ARG(1);
    memset(MEM(p + 4), 0, 40);
    v3_w32(p, 44);
    v3_w32(p + 8, 1); /* SW_SHOWNORMAL */
    v3_w32(p + 36, 640);
    v3_w32(p + 40, 480);
    STDCALL_RETURN(2, 1);
}

static void GetDesktopWindow(Cpu *c)
{
    STDCALL_RETURN(0, 0x00010010u);
}

static void GetForegroundWindow(Cpu *c)
{
    STDCALL_RETURN(0, main_window);
}

static void SetForegroundWindow(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void SetFocus(Cpu *c)
{
    STDCALL_RETURN(1, main_window);
}

static void GetSystemMetrics(Cpu *c)
{
    switch (ARG(0))
    {
    case 0: /* SM_CXSCREEN */
        STDCALL_RETURN(1, 640);
    case 1: /* SM_CYSCREEN */
        STDCALL_RETURN(1, 480);
    case 4: /* SM_CYCAPTION */
        STDCALL_RETURN(1, 0);
    default:
        STDCALL_RETURN(1, 0);
    }
}

static void LoadIconA(Cpu *c)
{
    STDCALL_RETURN(2, 0x00020001u);
}

static void LoadCursorA(Cpu *c)
{
    STDCALL_RETURN(2, 0x00020002u);
}

static void SetCursor(Cpu *c)
{
    STDCALL_RETURN(1, 0x00020002u);
}

static void ShowCursor(Cpu *c)
{
    static int32_t count;
    count += ARG(0) ? 1 : -1;
    STDCALL_RETURN(1, (uint32_t)count);
}

static void MessageBoxA(Cpu *c)
{
    char text[512], caption[128];
    v3_read_string(ARG(1), text, sizeof text);
    v3_read_string(ARG(2), caption, sizeof caption);
    v3_log("MessageBoxA(\"%s\": \"%s\") -> OK", caption, text);
    if (getenv("V3_HISTORY_ON_MESSAGE"))
    {
        v3_history_dump(400);
    }
    STDCALL_RETURN(4, 1);
}

/* --- display modes ------------------------------------------------------------------------- */

static const uint32_t MODES[][2] = {{640, 480}, {800, 600}, {1024, 768}};

static void EnumDisplaySettingsA(Cpu *c)
{
    uint32_t index = ARG(1);
    const uint32_t mode = ARG(2);
    if (index == 0xffffffffu || index == 0xfffffffeu) /* current, registry */
    {
        index = 0;
    }
    if (index >= sizeof MODES / sizeof MODES[0])
    {
        STDCALL_RETURN(3, 0);
    }
    memset(MEM(mode), 0, 124);
    v3_write_string(mode, "\\\\.\\DISPLAY1", 32);
    v3_w16(mode + 36, 124);
    v3_w32(mode + 40, 0x5c0000u); /* bits per pixel, width, height, frequency */
    v3_w32(mode + 104, 32);
    v3_w32(mode + 108, MODES[index][0]);
    v3_w32(mode + 112, MODES[index][1]);
    v3_w32(mode + 120, 60);
    STDCALL_RETURN(3, 1);
}

static void EnumDisplayDevicesA(Cpu *c)
{
    const uint32_t device = ARG(2);
    if (ARG(1) != 0)
    {
        STDCALL_RETURN(4, 0);
    }
    const uint32_t size = v3_r32(device);
    memset(MEM(device + 4), 0, size > 4 && size < 424 ? size - 4 : 420);
    v3_write_string(device + 4, "\\\\.\\DISPLAY1", 32);
    v3_write_string(device + 36, "Wii GX", 128);
    v3_w32(device + 164, 1u | 4u); /* attached to the desktop, primary */
    STDCALL_RETURN(4, 1);
}

/* --- messages ---------------------------------------------------------------------------- */

static int take(uint32_t msg, int remove)
{
    v3_lock();
    if (!queue_count)
    {
        v3_unlock();
        return 0;
    }
    v3_w32(msg, queue[queue_head].hwnd);
    v3_w32(msg + 4, queue[queue_head].message);
    v3_w32(msg + 8, queue[queue_head].wparam);
    v3_w32(msg + 12, queue[queue_head].lparam);
    v3_w32(msg + 16, queue[queue_head].time);
    v3_w32(msg + 20, 0);
    v3_w32(msg + 24, 0);
    if (remove)
    {
        queue_head = (queue_head + 1) % QUEUE;
        --queue_count;
    }
    v3_unlock();
    return 1;
}

/* A quit from the platform closes the window, as Alt+F4 would, so the game leaves through its
 * own exit (which saves its settings); if it is still running five seconds later, it ends. */
static void pump_platform(void)
{
    static uint64_t asked;
    if (v3_platform->poll && v3_platform->poll())
    {
        if (!asked)
        {
            asked = v3_microseconds();
            v3_log("the platform asked to quit");
            if (main_window)
            {
                v3_post_message(main_window, WM_CLOSE, 0, 0);
            }
        }
        if (!main_window || v3_microseconds() - asked > 5000000u)
        {
            v3_process_exit(0);
        }
    }
}

static void PeekMessageA(Cpu *c)
{
    pump_platform();
    STDCALL_RETURN(5, take(ARG(0), ARG(4) & 1));
}

static void GetMessageA(Cpu *c)
{
    while (!take(ARG(0), 1))
    {
        pump_platform();
        v3_sleep_ms(5);
    }
    STDCALL_RETURN(4, v3_r32(ARG(0) + 4) != WM_QUIT);
}

static void TranslateMessage(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void DispatchMessageA(Cpu *c)
{
    const uint32_t msg = ARG(0);
    const uint32_t result =
        send(c, v3_r32(msg), v3_r32(msg + 4), v3_r32(msg + 8), v3_r32(msg + 12));
    STDCALL_RETURN(1, result);
}

static void PostMessageA(Cpu *c)
{
    v3_post_message(ARG(0), ARG(1), ARG(2), ARG(3));
    STDCALL_RETURN(4, 1);
}

static void PostQuitMessage(Cpu *c)
{
    if (!quit_posted)
    {
        quit_posted = 1;
        v3_post_message(0, WM_QUIT, ARG(0), 0);
    }
    STDCALL_RETURN(1, 0);
}

/* --- dialogs and their controls ---------------------------------------------------------- */

static struct
{
    uint32_t dialog, id;
    char items[ITEMS][64];
    uint32_t count;
    int32_t selection;
    uint32_t check;
    char text[128];
} controls[CONTROLS];
static unsigned control_count;
static uint32_t dialog_result;
static int dialog_ended;

static int control_of(uint32_t handle)
{
    const uint32_t index = (handle - 0x00030000u) / 4u;
    return handle >= 0x00030000u && index < control_count ? (int)index : -1;
}

static void GetDlgItem(Cpu *c)
{
    for (unsigned i = 0; i < control_count; ++i)
    {
        if (controls[i].dialog == ARG(0) && controls[i].id == ARG(1))
        {
            STDCALL_RETURN(2, 0x00030000u + 4u * i);
        }
    }
    if (control_count == CONTROLS)
    {
        STDCALL_RETURN(2, 0);
    }
    memset(&controls[control_count], 0, sizeof controls[0]);
    controls[control_count].dialog = ARG(0);
    controls[control_count].id = ARG(1);
    controls[control_count].selection = -1;
    ++control_count;
    STDCALL_RETURN(2, 0x00030000u + 4u * (control_count - 1));
}

static void SendMessageA(Cpu *c)
{
    const uint32_t hwnd = ARG(0);
    const uint32_t message = ARG(1);
    const uint32_t wparam = ARG(2);
    const uint32_t lparam = ARG(3);
    const int k = control_of(hwnd);
    if (k < 0)
    {
        STDCALL_RETURN(4, send(c, hwnd, message, wparam, lparam));
    }
    uint32_t result = 0;
    switch (message)
    {
    case 0x143: /* CB_ADDSTRING */
    case 0x180: /* LB_ADDSTRING */
        if (controls[k].count < ITEMS)
        {
            v3_read_string(lparam, controls[k].items[controls[k].count], 64);
            result = controls[k].count++;
        }
        break;
    case 0x14b: /* CB_RESETCONTENT */
        controls[k].count = 0;
        controls[k].selection = -1;
        break;
    case 0x14e: /* CB_SETCURSEL */
        controls[k].selection = (int32_t)wparam;
        result = wparam;
        break;
    case 0x147: /* CB_GETCURSEL */
        result = (uint32_t)controls[k].selection;
        break;
    case 0x146: /* CB_GETCOUNT */
        result = controls[k].count;
        break;
    case 0x148: /* CB_GETLBTEXT */
        if (wparam < controls[k].count)
        {
            v3_write_string(lparam, controls[k].items[wparam], 64);
            result = (uint32_t)strlen(controls[k].items[wparam]);
        }
        else
        {
            result = 0xffffffffu;
        }
        break;
    case 0xf0: /* BM_GETCHECK */
        result = controls[k].check;
        break;
    case 0xf1: /* BM_SETCHECK */
        controls[k].check = wparam;
        break;
    case 0x0c: /* WM_SETTEXT */
        v3_read_string(lparam, controls[k].text, sizeof controls[k].text);
        result = 1;
        break;
    case 0x0d: /* WM_GETTEXT */
        v3_write_string(lparam, controls[k].text, wparam);
        result = (uint32_t)strlen(controls[k].text);
        break;
    default:
        break;
    }
    STDCALL_RETURN(4, result);
}

static void DialogBoxParamA(Cpu *c)
{
    /* The settings dialog: initialized, then confirmed with its defaults (IDOK). */
    const uint32_t procedure = ARG(3);
    if (window_count == WINDOWS)
    {
        STDCALL_RETURN(5, 0xffffffffu);
    }
    Window *w = &windows[window_count++];
    memset(w, 0, sizeof *w);
    w->handle = 0x00010020u + 4u * window_count;
    w->procedure = procedure;
    w->dialog = 1;
    const uint32_t hwnd = w->handle;
    v3_log("DialogBoxParamA(template %08x) -> accepting its defaults", ARG(1));
    dialog_ended = 0;
    dialog_result = 0;
    uint32_t arguments[4] = {hwnd, WM_INITDIALOG, 0, ARG(4)};
    v3_call_guest(c, procedure, 4, arguments, 0);
    for (unsigned i = 0; i < control_count; ++i)
    {
        if (controls[i].dialog == hwnd)
        {
            v3_log("  control %u: %u items, selection %d, check %u", controls[i].id,
                   controls[i].count, controls[i].selection, controls[i].check);
        }
    }
    if (!dialog_ended)
    {
        arguments[1] = WM_COMMAND;
        arguments[2] = 1; /* IDOK */
        arguments[3] = 0;
        v3_call_guest(c, procedure, 4, arguments, 0);
    }
    w->procedure = 0;
    STDCALL_RETURN(5, dialog_result);
}

static void EndDialog(Cpu *c)
{
    dialog_ended = 1;
    dialog_result = ARG(1);
    STDCALL_RETURN(2, 1);
}

const V3Export v3_user32[] = {
#define E(name) {#name, name}
    E(MessageBoxA), E(UnregisterClassA), E(DestroyWindow), E(PostQuitMessage), E(DefWindowProcA),
    E(PeekMessageA), E(GetMessageA), E(TranslateMessage), E(DispatchMessageA), E(ShowCursor),
    E(SetWindowPos), E(LoadIconA), E(LoadCursorA), E(GetForegroundWindow), E(MapWindowPoints),
    E(GetDesktopWindow), E(GetWindowPlacement), E(DialogBoxParamA), E(EndDialog),
    E(SendMessageA), E(GetDlgItem), E(MoveWindow), E(GetSystemMetrics), E(GetWindowRect),
    E(EnumDisplaySettingsA), E(EnumDisplayDevicesA), E(SetForegroundWindow), E(RegisterClassA),
    E(SetCursor), E(SetRect), E(AdjustWindowRect), E(SetFocus), E(ShowWindow), E(PostMessageA),
    E(CreateWindowExA),
#undef E
    {NULL, NULL}};
