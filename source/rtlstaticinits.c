#include "rtlstaticinits.h"

enum
{
    /* RegisterWindowMessageA("commctrl_DragListMsg") and the message's global. */
    REGISTER_WINDOW_MESSAGE = 0x4f1a70,
    DRAG_LIST_NAME = 0x5123ac,
    DRAG_LIST_MESSAGE = 0x5c5c68,

    /* The four runtime objects made (0x4cf3a0) and their records pushed on the cleanup list
     * (0x4ec1f7, with 1, -1, -2 and the last callee's edx). */
    OBJECT_CONSTRUCT = 0x4cf3a0,
    CLEANUP_PUSH = 0x4ec1f7,
    OBJECT_COUNT = 4,

    /* The application linked last (0x4d30f0, edx = 0x502ae8). */
    APPLICATION = 0x5c755c,
    APPLICATION_LINK = 0x4d30f0,
    APPLICATION_ENTRY = 0x502ae8
};

static const uint32_t OBJECTS[OBJECT_COUNT] = {0x5c5c6c, 0x5c5ca8, 0x5c5ce4, 0x5c5d20};
static const uint32_t RECORDS[OBJECT_COUNT] = {0x5023f0, 0x502400, 0x502410, 0x502420};

/* The member pointers (routine, 0, 0) copied through the frame into the message tables, as
 * address and value in the original's order of stores (0x4ceb5b to 0x4cf302). */
static const uint32_t STORES[][2] = {
    {0x50279c, 0x4d2ea0}, {0x5027a0, 0x0},      {0x5027a4, 0x0},      {0x5027bc, 0x4d2ea0},
    {0x5027c0, 0x0},      {0x5027c4, 0x0},      {0x5027dc, 0x4d2ea0}, {0x5027e0, 0x0},
    {0x5027e4, 0x0},      {0x5027fc, 0x4d2ea0}, {0x502800, 0x0},      {0x502804, 0x0},
    {0x50281c, 0x4d2ea0}, {0x502820, 0x0},      {0x502824, 0x0},      {0x50283c, 0x4d2ea0},
    {0x502840, 0x0},      {0x502844, 0x0},      {0x50285c, 0x4d2ea0}, {0x502860, 0x0},
    {0x502864, 0x0},      {0x50287c, 0x4d2eb0}, {0x502880, 0x0},      {0x502884, 0x0},
    {0x50289c, 0x4d2ec0}, {0x5028a0, 0x0},      {0x5028a4, 0x0},      {0x5028bc, 0x4d2ed0},
    {0x5028c0, 0x0},      {0x5028c4, 0x0},      {0x5028dc, 0x4d2ee0}, {0x5028e0, 0x0},
    {0x5028e4, 0x0},      {0x5028fc, 0x4d2ef0}, {0x502900, 0x0},      {0x502904, 0x0},
    {0x50291c, 0x4d2f00}, {0x502920, 0x0},      {0x502924, 0x0},      {0x50293c, 0x4d2f10},
    {0x502940, 0x0},      {0x502944, 0x0},      {0x50295c, 0x4d2f20}, {0x502960, 0x0},
    {0x502964, 0x0},      {0x50297c, 0x4d2f30}, {0x502980, 0x0},      {0x502984, 0x0},
    {0x5029bc, 0x4d2f50}, {0x5029c0, 0x0},      {0x50299c, 0x4d2f40}, {0x5029a0, 0x0},
    {0x5029c4, 0x0},      {0x5029a4, 0x0},      {0x5029fc, 0x4d2f70}, {0x5029dc, 0x4d2f60},
    {0x502a00, 0x0},      {0x5029e0, 0x0},      {0x502a04, 0x0},      {0x5029e4, 0x0},
    {0x502a1c, 0x4d2f80}, {0x502a20, 0x0},      {0x502a24, 0x0},      {0x502a3c, 0x4d2f90},
    {0x502a40, 0x0},      {0x502a44, 0x0},      {0x502a5c, 0x4d2fa0}, {0x502a60, 0x0},
    {0x502a64, 0x0},      {0x502a7c, 0x4d2fb0}, {0x502a80, 0x0},      {0x502a84, 0x0},
    {0x502a9c, 0x4d2fc0}, {0x502aa0, 0x0},      {0x502aa4, 0x0},      {0x502abc, 0x4d2fd0},
    {0x502adc, 0x0},      {0x502ac0, 0x0},      {0x502ae0, 0x0},      {0x502ac4, 0x0},
    {0x502ae4, 0x0},
};

/* Original 0x4ceaa0: a static initialiser. Registers the drag list message, makes the four
 * runtime objects and pushes their cleanup records, fills the message tables' member pointers and
 * links the application object. Returns 0x4d30f0's eax; the caller's edx is kept. */
uint32_t vertrix_port_rtl_static_init_4ceaa0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t name[1] = {DRAG_LIST_NAME};
    port_set32(&port, DRAG_LIST_MESSAGE, 0,
               port_call_stack(&port, REGISTER_WINDOW_MESSAGE, entry->eax, entry->edx, entry->ebx,
                               entry->ecx, name, 1));
    const uint32_t kinds[OBJECT_COUNT - 1] = {1, 0xffffffffu, 0xfffffffeu};
    uint32_t edx = 0;
    for (unsigned i = 0; i < OBJECT_COUNT; i++)
    {
        port_call(&port, OBJECT_CONSTRUCT, OBJECTS[i], edx, entry->ebx, entry->ecx);
        edx = i + 1 < OBJECT_COUNT ? kinds[i] : vertrix_lift_edx;
        port_call(&port, CLEANUP_PUSH, RECORDS[i], edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    for (size_t i = 0; i < sizeof STORES / sizeof STORES[0]; i++)
    {
        port_set32(&port, STORES[i][0], 0, STORES[i][1]);
    }
    const uint32_t eax =
        port_call(&port, APPLICATION_LINK, APPLICATION, APPLICATION_ENTRY, entry->ebx, entry->ecx);
    return port_return(&port, eax, entry->edx);
}
