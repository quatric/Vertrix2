#include "process.h"
#include "win32.h"

#include <ctype.h>
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
    uint32_t style, ex_style, id, parent, user_data;
} Window;

/* MFC attaches its window objects through a WH_CBT hook during CreateWindowEx (Vertrix 2 v1.2). */
static uint32_t cbt_hook;

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

/* The class a name or atom (0xc001.., as RegisterClassA returns) names; -1 for none. */
static int class_of(uint32_t name_or_atom, char *name, size_t size)
{
    if (name_or_atom < 0x10000u)
    {
        snprintf(name, size, "#%u", name_or_atom);
        const unsigned i = name_or_atom - 0xc001u;
        return name_or_atom >= 0xc001u && i < class_count ? (int)i : -1;
    }
    v3_read_string(name_or_atom, name, size);
    for (unsigned i = 0; i < class_count; ++i)
    {
        if (strcasecmp(classes[i].name, name) == 0)
        {
            return (int)i;
        }
    }
    return -1;
}

static void CreateWindowExA(Cpu *c)
{
    char name[64], title[128];
    const int cls = class_of(ARG(1), name, sizeof name);
    v3_read_string(ARG(2), title, sizeof title);
    const uint32_t procedure = cls >= 0 ? classes[cls].procedure : 0;
    if (window_count == WINDOWS)
    {
        STDCALL_RETURN(12, 0);
    }
    Window *w = &windows[window_count++];
    memset(w, 0, sizeof *w);
    w->handle = 0x00010020u + 4u * window_count;
    w->procedure = procedure;
    w->style = ARG(3);
    w->ex_style = ARG(0);
    w->parent = ARG(8);
    w->id = ARG(9);
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
    if (cbt_hook)
    {
        /* HCBT_CREATEWND with a CBT_CREATEWNDA: MFC subclasses the window here. */
        const uint32_t cbt = v3_alloc(8);
        v3_w32(cbt, cs);
        v3_w32(cbt + 4, 0);
        const uint32_t arguments[3] = {3, hwnd, cbt};
        v3_call_guest(c, cbt_hook, 3, arguments, 0);
        v3_free(cbt);
    }
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

/* --- what Vertrix 2 v1.2's MFC framework calls ----------------------------------------------- */

enum
{
    GWL_WNDPROC = -4,
    GWL_HWNDPARENT = -8,
    GWL_ID = -12,
    GWL_STYLE = -16,
    GWL_EXSTYLE = -20,
    GWL_USERDATA = -21,
    PROPS = 64
};

static uint32_t *window_long(Window *w, int32_t index)
{
    switch (index)
    {
    case GWL_WNDPROC:
        return &w->procedure;
    case GWL_HWNDPARENT:
        return &w->parent;
    case GWL_ID:
        return &w->id;
    case GWL_STYLE:
        return &w->style;
    case GWL_EXSTYLE:
        return &w->ex_style;
    case GWL_USERDATA:
        return &w->user_data;
    default:
        return NULL;
    }
}

static void GetWindowLongA(Cpu *c)
{
    Window *w = window(ARG(0));
    const uint32_t *slot = w ? window_long(w, (int32_t)ARG(1)) : NULL;
    STDCALL_RETURN(2, slot ? *slot : 0);
}

static void SetWindowLongA(Cpu *c)
{
    Window *w = window(ARG(0));
    uint32_t *slot = w ? window_long(w, (int32_t)ARG(1)) : NULL;
    if (!slot)
    {
        STDCALL_RETURN(3, 0);
    }
    const uint32_t old = *slot;
    *slot = ARG(2);
    STDCALL_RETURN(3, old);
}

/* (procedure, hwnd, message, wparam, lparam) */
static void CallWindowProcA(Cpu *c)
{
    const uint32_t procedure = ARG(0);
    if (!procedure)
    {
        STDCALL_RETURN(5, 0);
    }
    const uint32_t arguments[4] = {ARG(1), ARG(2), ARG(3), ARG(4)};
    const uint32_t result = v3_call_guest(c, procedure, 4, arguments, 0);
    STDCALL_RETURN(5, result);
}

/* Only WH_CBT (5) is honoured; the others are accepted and never called. */
static void SetWindowsHookExA(Cpu *c)
{
    if (ARG(0) == 5)
    {
        cbt_hook = ARG(1);
    }
    STDCALL_RETURN(4, 0x00ab0000u + ARG(0));
}

static void UnhookWindowsHookEx(Cpu *c)
{
    if (ARG(0) == 0x00ab0005u)
    {
        cbt_hook = 0;
    }
    STDCALL_RETURN(1, 1);
}

static void CallNextHookEx(Cpu *c)
{
    STDCALL_RETURN(4, 0);
}

/* Window properties, by name or atom. */
static struct
{
    uint32_t hwnd;
    char name[48];
    uint32_t value;
} props[PROPS];

static int prop_find(uint32_t hwnd, uint32_t key, char *name, size_t size)
{
    if (key < 0x10000u)
    {
        snprintf(name, size, "#%u", key);
    }
    else
    {
        v3_read_string(key, name, size);
    }
    for (int i = 0; i < PROPS; ++i)
    {
        if (props[i].hwnd == hwnd && strcmp(props[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

static void SetPropA(Cpu *c)
{
    char name[48];
    int i = prop_find(ARG(0), ARG(1), name, sizeof name);
    for (int k = 0; i < 0 && k < PROPS; ++k)
    {
        if (!props[k].hwnd)
        {
            i = k;
        }
    }
    if (i < 0)
    {
        STDCALL_RETURN(3, 0);
    }
    props[i].hwnd = ARG(0);
    snprintf(props[i].name, sizeof props[i].name, "%s", name);
    props[i].value = ARG(2);
    STDCALL_RETURN(3, 1);
}

static void GetPropA(Cpu *c)
{
    char name[48];
    const int i = prop_find(ARG(0), ARG(1), name, sizeof name);
    STDCALL_RETURN(2, i >= 0 ? props[i].value : 0);
}

static void RemovePropA(Cpu *c)
{
    char name[48];
    const int i = prop_find(ARG(0), ARG(1), name, sizeof name);
    uint32_t value = 0;
    if (i >= 0)
    {
        value = props[i].value;
        props[i].hwnd = 0;
    }
    STDCALL_RETURN(2, value);
}

/* (instance, class, WNDCLASSA out) */
static void GetClassInfoA(Cpu *c)
{
    char name[64];
    const int cls = class_of(ARG(1), name, sizeof name);
    if (cls < 0)
    {
        STDCALL_RETURN(3, 0);
    }
    const uint32_t wc = ARG(2);
    memset(MEM(wc), 0, 40);
    v3_w32(wc + 4, classes[cls].procedure);
    v3_w32(wc + 16, ARG(0));
    STDCALL_RETURN(3, 1);
}

static void GetClassNameA(Cpu *c)
{
    v3_write_string(ARG(1), "Vertrix", ARG(2));
    STDCALL_RETURN(3, ARG(2) > 7 ? 7 : (ARG(2) ? ARG(2) - 1 : 0));
}

static void IsWindow(Cpu *c)
{
    STDCALL_RETURN(1, window(ARG(0)) != NULL);
}

static void GetParent(Cpu *c)
{
    Window *w = window(ARG(0));
    STDCALL_RETURN(1, w ? w->parent : 0);
}

static void GetDlgCtrlID(Cpu *c)
{
    Window *w = window(ARG(0));
    STDCALL_RETURN(1, w ? w->id : 0);
}

static void GetActiveWindow(Cpu *c)
{
    STDCALL_RETURN(0, main_window);
}

static void GetFocus(Cpu *c)
{
    STDCALL_RETURN(0, main_window);
}

static void GetClientRect(Cpu *c)
{
    Window *w = window(ARG(0));
    const uint32_t r = ARG(1);
    v3_w32(r, 0);
    v3_w32(r + 4, 0);
    v3_w32(r + 8, (uint32_t)(w && w->width > 0 ? w->width : 640));
    v3_w32(r + 12, (uint32_t)(w && w->height > 0 ? w->height : 480));
    STDCALL_RETURN(2, 1);
}

/* The window sits at the screen's origin. */
static void ClientToScreen(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void ScreenToClient(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void GetCursorPos(Cpu *c)
{
    v3_w32(ARG(0), 320);
    v3_w32(ARG(0) + 4, 240);
    STDCALL_RETURN(1, 1);
}

static void GetMessageTime(Cpu *c)
{
    STDCALL_RETURN(0, (uint32_t)(v3_microseconds() / 1000u));
}

static void RegisterWindowMessageA(Cpu *c)
{
    static uint32_t next = 0xc100u;
    STDCALL_RETURN(1, next++);
}

static void GetSysColor(Cpu *c)
{
    STDCALL_RETURN(1, 0x00c0c0c0u);
}

/* One device context for the window: GDI drawing goes nowhere (the game draws through DirectDraw). */
static void GetDC(Cpu *c)
{
    STDCALL_RETURN(1, 0x00dc0001u);
}

static void GetWindowDC(Cpu *c)
{
    STDCALL_RETURN(1, 0x00dc0001u);
}

static void ReleaseDC(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void BeginPaint(Cpu *c)
{
    memset(MEM(ARG(1)), 0, 64);
    v3_w32(ARG(1), 0x00dc0001u);
    STDCALL_RETURN(2, 0x00dc0001u);
}

/* --- characters and rectangles --- */

static void CharUpperA(Cpu *c)
{
    const uint32_t s = ARG(0);
    if (s < 0x10000u)
    {
        STDCALL_RETURN(1, (uint32_t)toupper((int)(s & 0xff)));
    }
    for (uint32_t a = s; v3_r8(a); ++a)
    {
        v3_w8(a, (uint32_t)toupper((int)v3_r8(a)));
    }
    STDCALL_RETURN(1, s);
}

static void CharLowerA(Cpu *c)
{
    const uint32_t s = ARG(0);
    if (s < 0x10000u)
    {
        STDCALL_RETURN(1, (uint32_t)tolower((int)(s & 0xff)));
    }
    for (uint32_t a = s; v3_r8(a); ++a)
    {
        v3_w8(a, (uint32_t)tolower((int)v3_r8(a)));
    }
    STDCALL_RETURN(1, s);
}

static void CharUpperBuffA(Cpu *c)
{
    for (uint32_t i = 0; i < ARG(1); ++i)
    {
        v3_w8(ARG(0) + i, (uint32_t)toupper((int)v3_r8(ARG(0) + i)));
    }
    STDCALL_RETURN(2, ARG(1));
}

static void CharNextA(Cpu *c)
{
    STDCALL_RETURN(1, v3_r8(ARG(0)) ? ARG(0) + 1 : ARG(0));
}

static void CharPrevA(Cpu *c)
{
    STDCALL_RETURN(2, ARG(1) > ARG(0) ? ARG(1) - 1 : ARG(0));
}

/* OEM and ANSI text are the same here. */
static void CharToOemA(Cpu *c)
{
    if (ARG(0) != ARG(1))
    {
        memmove(MEM(ARG(1)), MEM(ARG(0)), v3_string_length(ARG(0)) + 1);
    }
    STDCALL_RETURN(2, 1);
}

static void OemToCharA(Cpu *c)
{
    if (ARG(0) != ARG(1))
    {
        memmove(MEM(ARG(1)), MEM(ARG(0)), v3_string_length(ARG(0)) + 1);
    }
    STDCALL_RETURN(2, 1);
}

static void CopyRect(Cpu *c)
{
    memmove(MEM(ARG(0)), MEM(ARG(1)), 16);
    STDCALL_RETURN(2, 1);
}

static void EqualRect(Cpu *c)
{
    STDCALL_RETURN(2, memcmp(MEM(ARG(0)), MEM(ARG(1)), 16) == 0);
}

static void SetRectEmpty(Cpu *c)
{
    memset(MEM(ARG(0)), 0, 16);
    STDCALL_RETURN(1, 1);
}

/* (rect, point.x, point.y) */
static void PtInRect(Cpu *c)
{
    const int32_t x = (int32_t)ARG(1), y = (int32_t)ARG(2);
    const uint32_t r = ARG(0);
    STDCALL_RETURN(3, x >= (int32_t)v3_r32(r) && x < (int32_t)v3_r32(r + 8) &&
                          y >= (int32_t)v3_r32(r + 4) && y < (int32_t)v3_r32(r + 12));
}

/* wsprintfA (cdecl): %[-0][width](d|i|u|x|X|c|s|%), with l and h ignored. */
static void wsprintfA(Cpu *c)
{
    const uint32_t out = ARG(0);
    char format[512], text[1025];
    v3_read_string(ARG(1), format, sizeof format);
    unsigned argument = 2;
    size_t n = 0;
    for (const char *f = format; *f && n < 1024; ++f)
    {
        if (*f != '%')
        {
            text[n++] = *f;
            continue;
        }
        char spec[16] = "%";
        size_t k = 1;
        ++f;
        while ((*f == '-' || *f == '0' || *f == '#' || (*f >= '1' && *f <= '9')) && k < 12)
        {
            spec[k++] = *f++;
        }
        while (*f >= '0' && *f <= '9' && k < 12)
        {
            spec[k++] = *f++;
        }
        while (*f == 'l' || *f == 'h')
        {
            ++f;
        }
        if (!*f)
        {
            break;
        }
        char piece[600];
        spec[k] = *f;
        spec[k + 1] = 0;
        switch (*f)
        {
        case 'd':
        case 'i':
            snprintf(piece, sizeof piece, spec, (int)ARG(argument++));
            break;
        case 'u':
        case 'x':
        case 'X':
            snprintf(piece, sizeof piece, spec, (unsigned)ARG(argument++));
            break;
        case 'c':
            snprintf(piece, sizeof piece, spec, (int)(ARG(argument++) & 0xff));
            break;
        case 's':
        {
            char value[512];
            v3_read_string(ARG(argument++), value, sizeof value);
            snprintf(piece, sizeof piece, spec, value);
            break;
        }
        default:
            snprintf(piece, sizeof piece, "%c", *f);
            break;
        }
        for (const char *q = piece; *q && n < 1024; ++q)
        {
            text[n++] = *q;
        }
    }
    text[n] = 0;
    v3_write_string(out, text, n + 1);
    CDECL_RETURN(n);
}

/* --- the rest: neutral answers for a full-screen game with no menus, dialogs or scroll bars --- */

static void quiet(const char *name)
{
    static const char *seen[160];
    static unsigned count;
    for (unsigned i = 0; i < count; ++i)
    {
        if (seen[i] == name)
        {
            return;
        }
    }
    if (count < 160)
    {
        seen[count++] = name;
    }
    v3_log("%s: no effect here", name);
}

#define QUIET(name, args, value)                                                                   \
    static void name(Cpu *c)                                                                       \
    {                                                                                              \
        quiet(#name);                                                                              \
        STDCALL_RETURN(args, value);                                                               \
    }
QUIET(AdjustWindowRectEx, 4, 1)
QUIET(BeginDeferWindowPos, 1, 0x00de0001u)
QUIET(DeferWindowPos, 8, ARG(0))
QUIET(EndDeferWindowPos, 1, 1)
QUIET(BringWindowToTop, 1, 1)
QUIET(CheckDlgButton, 3, 1)
QUIET(CheckMenuItem, 3, 0)
QUIET(CheckRadioButton, 4, 1)
QUIET(CreateDialogIndirectParamA, 5, 0)
QUIET(DeleteMenu, 3, 1)
QUIET(DestroyMenu, 1, 1)
QUIET(DrawTextA, 5, 16)
QUIET(EnableMenuItem, 3, 0)
QUIET(EnableWindow, 2, 0)
QUIET(EndPaint, 2, 1)
QUIET(GetCapture, 0, 0)
QUIET(GetDialogBaseUnits, 0, 0x00100008u)
QUIET(GetDlgItemInt, 4, 0)
QUIET(GetKeyState, 1, 0)
QUIET(GetLastActivePopup, 1, ARG(0))
QUIET(GetMenu, 1, 0)
QUIET(GetMenuCheckMarkDimensions, 0, 0x000d000du)
QUIET(GetMenuItemCount, 1, 0)
QUIET(GetMenuItemID, 2, 0xffffffffu)
QUIET(GetMenuState, 3, 0xffffffffu)
QUIET(GetMessagePos, 0, 0)
QUIET(GetNextDlgTabItem, 3, 0)
QUIET(GetScrollInfo, 3, 0)
QUIET(GetScrollPos, 2, 0)
QUIET(GetSubMenu, 2, 0)
QUIET(GetTopWindow, 1, 0)
QUIET(GetWindow, 2, 0)
QUIET(GetWindowTextLengthA, 1, 0)
QUIET(GrayStringA, 9, 1)
QUIET(InsertMenuA, 5, 1)
QUIET(InvalidateRect, 3, 1)
QUIET(IsChild, 2, 0)
QUIET(IsDialogMessageA, 2, 0)
QUIET(IsDlgButtonChecked, 2, 0)
QUIET(IsIconic, 1, 0)
QUIET(IsWindowEnabled, 1, 1)
QUIET(IsWindowVisible, 1, 1)
QUIET(LoadAcceleratorsA, 2, 0x00ac0001u)
QUIET(LoadBitmapA, 2, 0)
QUIET(LoadMenuA, 2, 0)
QUIET(ModifyMenuA, 5, 1)
QUIET(ReleaseCapture, 0, 1)
QUIET(ReuseDDElParam, 5, 0)
QUIET(ScrollWindow, 5, 1)
QUIET(ScrollWindowEx, 8, 1)
QUIET(SendDlgItemMessageA, 5, 0)
QUIET(SetActiveWindow, 1, main_window)
QUIET(SetDlgItemInt, 4, 1)
QUIET(SetDlgItemTextA, 3, 1)
QUIET(SetMenu, 2, 1)
QUIET(SetMenuItemBitmaps, 5, 1)
QUIET(SetMessageQueue, 1, 1)
QUIET(SetScrollInfo, 4, 0)
QUIET(SetScrollPos, 4, 0)
QUIET(SetScrollRange, 5, 1)
QUIET(SetWindowPlacement, 2, 1)
QUIET(SetWindowTextA, 2, 1)
QUIET(ShowOwnedPopups, 2, 1)
QUIET(ShowScrollBar, 3, 1)
QUIET(SystemParametersInfoA, 4, 0)
QUIET(TabbedTextOutA, 8, 0)
QUIET(TrackPopupMenu, 7, 0)
QUIET(TranslateAcceleratorA, 3, 0)
QUIET(UnpackDDElParam, 4, 0)
QUIET(UpdateWindow, 1, 1)
QUIET(ValidateRect, 2, 1)
QUIET(WinHelpA, 4, 0)
QUIET(WindowFromPoint, 2, main_window)
#undef QUIET

static void GetScrollRange(Cpu *c)
{
    quiet("GetScrollRange");
    v3_w32(ARG(2), 0);
    v3_w32(ARG(3), 0);
    STDCALL_RETURN(4, 1);
}

static void GetWindowTextA(Cpu *c)
{
    if (ARG(2))
    {
        v3_w8(ARG(1), 0);
    }
    STDCALL_RETURN(3, 0);
}

static void GetDlgItemTextA(Cpu *c)
{
    if (ARG(3))
    {
        v3_w8(ARG(2), 0);
    }
    STDCALL_RETURN(4, 0);
}

static void GetMenuStringA(Cpu *c)
{
    if (ARG(3))
    {
        v3_w8(ARG(2), 0);
    }
    STDCALL_RETURN(5, 0);
}

/* (instance, id, buffer, size): no string table is read; an empty string. */
static void LoadStringA(Cpu *c)
{
    quiet("LoadStringA");
    if (ARG(3))
    {
        v3_w8(ARG(2), 0);
    }
    STDCALL_RETURN(4, 0);
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
    E(GetWindowLongA), E(SetWindowLongA), E(CallWindowProcA), E(SetWindowsHookExA),
    E(UnhookWindowsHookEx), E(CallNextHookEx), E(SetPropA), E(GetPropA), E(RemovePropA),
    E(GetClassInfoA), E(GetClassNameA), E(IsWindow), E(GetParent), E(GetDlgCtrlID),
    E(GetActiveWindow), E(GetFocus), E(GetClientRect), E(ClientToScreen), E(ScreenToClient),
    E(GetCursorPos), E(GetMessageTime), E(RegisterWindowMessageA), E(GetSysColor), E(GetDC),
    E(GetWindowDC), E(ReleaseDC), E(BeginPaint), E(CharUpperA), E(CharLowerA), E(CharUpperBuffA),
    E(CharNextA), E(CharPrevA), E(CharToOemA), E(OemToCharA), E(CopyRect), E(EqualRect),
    E(SetRectEmpty), E(PtInRect), E(wsprintfA), E(AdjustWindowRectEx), E(BeginDeferWindowPos),
    E(DeferWindowPos), E(EndDeferWindowPos), E(BringWindowToTop), E(CheckDlgButton),
    E(CheckMenuItem), E(CheckRadioButton), E(CreateDialogIndirectParamA), E(DeleteMenu),
    E(DestroyMenu), E(DrawTextA), E(EnableMenuItem), E(EnableWindow), E(EndPaint), E(GetCapture),
    E(GetDialogBaseUnits), E(GetDlgItemInt), E(GetKeyState), E(GetLastActivePopup), E(GetMenu),
    E(GetMenuCheckMarkDimensions), E(GetMenuItemCount), E(GetMenuItemID), E(GetMenuState),
    E(GetMessagePos), E(GetNextDlgTabItem), E(GetScrollInfo), E(GetScrollPos), E(GetSubMenu),
    E(GetTopWindow), E(GetWindow), E(GetWindowTextLengthA), E(GrayStringA), E(InsertMenuA),
    E(InvalidateRect), E(IsChild), E(IsDialogMessageA), E(IsDlgButtonChecked), E(IsIconic),
    E(IsWindowEnabled), E(IsWindowVisible), E(LoadAcceleratorsA), E(LoadBitmapA), E(LoadMenuA),
    E(ModifyMenuA), E(ReleaseCapture), E(ReuseDDElParam), E(ScrollWindow), E(ScrollWindowEx),
    E(SendDlgItemMessageA), E(SetActiveWindow), E(SetDlgItemInt), E(SetDlgItemTextA), E(SetMenu),
    E(SetMenuItemBitmaps), E(SetMessageQueue), E(SetScrollInfo), E(SetScrollPos),
    E(SetScrollRange), E(SetWindowPlacement), E(SetWindowTextA), E(ShowOwnedPopups),
    E(ShowScrollBar), E(SystemParametersInfoA), E(TabbedTextOutA), E(TrackPopupMenu),
    E(TranslateAcceleratorA), E(UnpackDDElParam), E(UpdateWindow), E(ValidateRect), E(WinHelpA),
    E(WindowFromPoint), E(GetScrollRange), E(GetWindowTextA), E(GetDlgItemTextA),
    E(GetMenuStringA), E(LoadStringA),
#undef E
    {NULL, NULL}};
