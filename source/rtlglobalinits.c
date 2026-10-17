#include "rtlglobalinits.h"

/* The game's static initializer: its global strings, string arrays and lists, the records it
 * registers for finalization, and globals copied from the image's constants. */

enum
{
    /* The type information of the string arrays. */
    STRING_ARRAY_TYPE = 0x513e60,

    STRING_ASSIGN = 0x4ca280,
    STRING_CLEAR = 0x4ca070,
    STRING_ARRAY_INIT = 0x4ccf3b,
    FINALIZATION_PUSH = 0x4ec1f7,
    LIST_A_INIT = 0x4b6ea0,
    LIST_B_INIT = 0x4b7600
};

typedef enum
{
    /* A string variable set from a literal. */
    STRING,
    /* An array of `count` strings made empty. */
    STRINGS,
    /* A string variable made empty. */
    EMPTY,
    /* A record pushed on the finalization list. */
    FINALIZER,
    /* The two list objects (0x4b6ea0, 0x4b7600). */
    LIST_A,
    LIST_B,
    /* A global copied from another, plus `add`. */
    COPY
} StepKind;

typedef struct
{
    StepKind kind;
    uint32_t target;
    uint32_t source;
    uint32_t add;
} Step;

/* In the original's order. */
static const Step STEPS[] = {{STRING, 0x532ab8, 0x50caa7, 0}, {STRING, 0x532abc, 0x50caac, 0},
                             {STRING, 0x532ac0, 0x50cab3, 0}, {FINALIZER, 0x4f7750, 0, 0},
                             {STRING, 0x532ac4, 0x50cab8, 0}, {STRING, 0x532ac8, 0x50caba, 0},
                             {STRING, 0x532acc, 0x50cabc, 0}, {STRING, 0x532ad0, 0x50cabe, 0},
                             {STRING, 0x532ad4, 0x50cac0, 0}, {STRING, 0x532ad8, 0x50cac2, 0},
                             {STRING, 0x532adc, 0x50cac4, 0}, {STRING, 0x532ae0, 0x50cac6, 0},
                             {STRING, 0x532ae4, 0x50cac8, 0}, {STRING, 0x532ae8, 0x50caca, 0},
                             {FINALIZER, 0x4f7760, 0, 0},     {STRING, 0x532aec, 0x50cacc, 0},
                             {STRING, 0x532af0, 0x50cacf, 0}, {FINALIZER, 0x4f7770, 0, 0},
                             {STRING, 0x532af4, 0x50cad3, 0}, {STRING, 0x532af8, 0x50cad6, 0},
                             {FINALIZER, 0x4f7780, 0, 0},     {STRING, 0x532afc, 0x50cada, 0},
                             {STRING, 0x532b00, 0x50cadc, 0}, {STRING, 0x532b04, 0x50cadf, 0},
                             {FINALIZER, 0x4f7790, 0, 0},     {STRING, 0x532b08, 0x50cae2, 0},
                             {STRING, 0x532b0c, 0x50cae7, 0}, {STRING, 0x532b10, 0x50caef, 0},
                             {STRING, 0x532b14, 0x50caf4, 0}, {STRING, 0x532b18, 0x50cafb, 0},
                             {STRING, 0x532b1c, 0x50cb00, 0}, {FINALIZER, 0x4f77a0, 0, 0},
                             {STRING, 0x532b20, 0x50cb08, 0}, {STRING, 0x532b24, 0x50cb10, 0},
                             {STRING, 0x532b28, 0x50cb15, 0}, {STRING, 0x532b2c, 0x50cb1c, 0},
                             {STRING, 0x532b30, 0x50cb21, 0}, {FINALIZER, 0x4f77b0, 0, 0},
                             {EMPTY, 0x532be8, 0, 0},         {FINALIZER, 0x4f77c0, 0, 0},
                             {EMPTY, 0x532bec, 0, 0},         {FINALIZER, 0x4f77d0, 0, 0},
                             {EMPTY, 0x532bf0, 0, 0},         {FINALIZER, 0x4f77e0, 0, 0},
                             {EMPTY, 0x532bf4, 0, 0},         {FINALIZER, 0x4f77f0, 0, 0},
                             {LIST_A, 0x532c04, 0, 0},        {FINALIZER, 0x4f7800, 0, 0},
                             {EMPTY, 0x532c1c, 0, 0},         {FINALIZER, 0x4f7810, 0, 0},
                             {EMPTY, 0x532c20, 0, 0},         {FINALIZER, 0x4f7820, 0, 0},
                             {LIST_B, 0x532c24, 0, 0},        {FINALIZER, 0x4f7830, 0, 0},
                             {STRING, 0x532c44, 0x50cb29, 0}, {STRING, 0x532c48, 0x50cb2b, 0},
                             {STRING, 0x532c4c, 0x50cb2d, 0}, {FINALIZER, 0x4f7840, 0, 0},
                             {STRING, 0x532c50, 0x50cb2f, 0}, {STRING, 0x532c54, 0x50cb31, 0},
                             {STRING, 0x532c58, 0x50cb33, 0}, {STRING, 0x532c5c, 0x50cb35, 0},
                             {STRING, 0x532c60, 0x50cb37, 0}, {STRING, 0x532c64, 0x50cb39, 0},
                             {STRING, 0x532c68, 0x50cb3b, 0}, {STRING, 0x532c6c, 0x50cb3d, 0},
                             {STRING, 0x532c70, 0x50cb3f, 0}, {STRING, 0x532c74, 0x50cb41, 0},
                             {FINALIZER, 0x4f7850, 0, 0},     {STRING, 0x532c78, 0x50cb43, 0},
                             {STRING, 0x532c7c, 0x50cb45, 0}, {FINALIZER, 0x4f7860, 0, 0},
                             {STRING, 0x532c80, 0x50cb47, 0}, {STRING, 0x532c84, 0x50cb49, 0},
                             {FINALIZER, 0x4f7870, 0, 0},     {STRING, 0x532c88, 0x50cb4b, 0},
                             {STRING, 0x532c8c, 0x50cb4d, 0}, {FINALIZER, 0x4f7880, 0, 0},
                             {STRING, 0x532c90, 0x50cb4f, 0}, {STRING, 0x532c94, 0x50cb53, 0},
                             {FINALIZER, 0x4f7890, 0, 0},     {STRING, 0x532c9c, 0x50cb5a, 0},
                             {STRING, 0x532ca0, 0x50cb69, 0}, {FINALIZER, 0x4f78a0, 0, 0},
                             {STRINGS, 0x532d8c, 0x4c, 0},    {FINALIZER, 0x4f78b0, 0, 0},
                             {STRINGS, 0x532ebc, 0x4c, 0},    {FINALIZER, 0x4f78c0, 0, 0},
                             {STRINGS, 0x532fec, 0x1c, 0},    {FINALIZER, 0x4f78d0, 0, 0},
                             {STRINGS, 0x53305c, 0x13, 0},    {FINALIZER, 0x4f78e0, 0, 0},
                             {STRINGS, 0x5330a8, 0x2f, 0},    {FINALIZER, 0x4f78f0, 0, 0},
                             {STRINGS, 0x5332a8, 0x5, 0},     {FINALIZER, 0x4f7900, 0, 0},
                             {STRINGS, 0x5332c0, 0x14, 0},    {FINALIZER, 0x4f7910, 0, 0},
                             {STRINGS, 0x533310, 0x14, 0},    {FINALIZER, 0x4f7920, 0, 0},
                             {STRINGS, 0x533360, 0x14, 0},    {FINALIZER, 0x4f7930, 0, 0},
                             {STRINGS, 0x5333b0, 0x14, 0},    {FINALIZER, 0x4f7940, 0, 0},
                             {STRINGS, 0x533400, 0x14, 0},    {FINALIZER, 0x4f7950, 0, 0},
                             {STRINGS, 0x533450, 0x14, 0},    {FINALIZER, 0x4f7960, 0, 0},
                             {STRINGS, 0x5334a0, 0x36, 0},    {FINALIZER, 0x4f7970, 0, 0},
                             {STRINGS, 0x533578, 0x36, 0},    {FINALIZER, 0x4f7980, 0, 0},
                             {STRINGS, 0x533650, 0x17, 0},    {FINALIZER, 0x4f7990, 0, 0},
                             {STRINGS, 0x533b0c, 0x70, 0},    {FINALIZER, 0x4f79a0, 0, 0},
                             {COPY, 0x533cd0, 0x4f84e8, 0},   {COPY, 0x533cd4, 0x4f84ec, 0},
                             {COPY, 0x533cd8, 0x4f84f0, 0},   {COPY, 0x533cdc, 0x4f84f4, 0},
                             {COPY, 0x533ce0, 0x4f84f8, 0},   {COPY, 0x533ce4, 0x4f84fc, 0},
                             {COPY, 0x533ce8, 0x4f8500, 0},   {COPY, 0x533cec, 0x4f8504, 0},
                             {COPY, 0x533cf0, 0x4f8508, 0},   {COPY, 0x533cf4, 0x4f850c, 0},
                             {COPY, 0x533cf8, 0x4f8510, 0},   {COPY, 0x533cfc, 0x4f8514, 0},
                             {COPY, 0x533d00, 0x4f8530, 0},   {COPY, 0x533d04, 0x4f8534, 0},
                             {COPY, 0x533d08, 0x4f8538, 0},   {COPY, 0x533d0c, 0x4f853c, 0},
                             {COPY, 0x533d10, 0x4f8544, 0},   {COPY, 0x533d14, 0x4f8548, 0},
                             {COPY, 0x533d18, 0x4f8540, 0},   {COPY, 0x533d1c, 0x4f8550, 0},
                             {COPY, 0x533d78, 0x4f8c54, 1},   {STRINGS, 0x533d7c, 0x14, 0},
                             {FINALIZER, 0x4f79b0, 0, 0},     {STRINGS, 0x533dcc, 0x14, 0},
                             {FINALIZER, 0x4f79c0, 0, 0},     {STRINGS, 0x533e1c, 0x1a2, 0},
                             {FINALIZER, 0x4f79d0, 0, 0},     {STRINGS, 0x53453c, 0x13, 0},
                             {FINALIZER, 0x4f79e0, 0, 0},     {STRINGS, 0x534588, 0x13, 0},
                             {FINALIZER, 0x4f79f0, 0, 0},     {STRINGS, 0x5345d4, 0x13, 0},
                             {FINALIZER, 0x4f7a00, 0, 0},     {STRINGS, 0x534620, 0x14, 0},
                             {FINALIZER, 0x4f7a10, 0, 0},     {STRINGS, 0x534670, 0x14, 0},
                             {FINALIZER, 0x4f7a20, 0, 0},     {STRINGS, 0x5346c0, 0x14, 0},
                             {FINALIZER, 0x4f7a30, 0, 0},     {STRINGS, 0x534710, 0x10, 0},
                             {FINALIZER, 0x4f7a40, 0, 0},     {STRINGS, 0x534750, 0x14, 0},
                             {FINALIZER, 0x4f7a50, 0, 0},     {STRINGS, 0x53483c, 0x13, 0},
                             {FINALIZER, 0x4f7a60, 0, 0},     {STRINGS, 0x534920, 0xbe, 0},
                             {FINALIZER, 0x4f7a70, 0, 0},     {STRINGS, 0x534f5c, 0x474, 0},
                             {FINALIZER, 0x4f7a80, 0, 0},     {STRINGS, 0x53612c, 0x474, 0},
                             {FINALIZER, 0x4f7a90, 0, 0},     {STRINGS, 0x53ba88, 0x14, 0},
                             {FINALIZER, 0x4f7aa0, 0, 0},     {STRINGS, 0x53bdfc, 0xb4, 0},
                             {FINALIZER, 0x4f7ab0, 0, 0},     {STRINGS, 0x53c0cc, 0x21c, 0},
                             {FINALIZER, 0x4f7ac0, 0, 0},     {STRINGS, 0x53c93c, 0x402, 0},
                             {FINALIZER, 0x4f7ad0, 0, 0},     {COPY, 0x53d948, 0x5332bc, 0},
                             {COPY, 0x53d94c, 0x4f84d4, 0},   {COPY, 0x53d950, 0x4f84bc, 0},
                             {COPY, 0x53d954, 0x4f849c, 0},   {COPY, 0x53d958, 0x4f84c0, 0},
                             {COPY, 0x53d95c, 0x4f84b0, 0},   {COPY, 0x53d960, 0x4f84a8, 0},
                             {COPY, 0x53d964, 0x4f84a0, 0},   {COPY, 0x53d968, 0x4f84d8, 0},
                             {COPY, 0x53d96c, 0x4f84c4, 0},   {COPY, 0x53d970, 0x4f84a4, 0},
                             {COPY, 0x53d974, 0x4f84ac, 0},   {COPY, 0x53d978, 0x4f84d0, 0},
                             {COPY, 0x53d97c, 0x4f84b4, 0},   {COPY, 0x53d980, 0x4f84dc, 0},
                             {COPY, 0x53d984, 0x4f84c8, 0},   {COPY, 0x53d988, 0x4f84cc, 0},
                             {COPY, 0x53d98c, 0x4f84b8, 0},   {COPY, 0x53d990, 0x4f84e0, 0},
                             {COPY, 0x53d994, 0x4f84e4, 0},   {STRINGS, 0x53d998, 0x8e8, 0},
                             {FINALIZER, 0x4f7ae0, 0, 0},     {STRINGS, 0x53fe20, 0x78, 0},
                             {FINALIZER, 0x4f7af0, 0, 0},     {STRING, 0x540010, 0x50cb77, 0},
                             {FINALIZER, 0x4f7b00, 0, 0},     {STRINGS, 0x540050, 0x5, 0},
                             {FINALIZER, 0x4f7b10, 0, 0},     {STRINGS, 0x54008c, 0x19, 0},
                             {FINALIZER, 0x4f7b20, 0, 0},     {STRINGS, 0x5400f0, 0x19, 0},
                             {FINALIZER, 0x4f7b30, 0, 0}};

/* Original 0x412700. The original keeps an exception frame with a state word moved on as each
 * global is made; nothing reads it (NATIVE-PORTS.md). Its caller reads eax and edx: the exception
 * chain it had (the original returns its frame's saved chain head) and its own edx (saved). */
uint32_t vertrix_port_game_globals_init_412700(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t chain = port.env.chain;
    for (size_t i = 0; i < sizeof STEPS / sizeof STEPS[0] && !port.env.failed; i++)
    {
        const Step *step = &STEPS[i];
        switch (step->kind)
        {
            case STRING:
                port_call(&port, STRING_ASSIGN, step->target, step->source, 0, 0);
                break;
            case STRINGS:
                port_call(&port, STRING_ARRAY_INIT, step->target, step->source, STRING_ARRAY_TYPE,
                          0);
                break;
            case EMPTY:
                port_call(&port, STRING_CLEAR, step->target, 0, 0, 0);
                break;
            case FINALIZER:
                port_call(&port, FINALIZATION_PUSH, step->target, 0, 0, 0);
                break;
            case LIST_A:
                port_call(&port, LIST_A_INIT, step->target, 0, 0, 0);
                break;
            case LIST_B:
                port_call(&port, LIST_B_INIT, step->target, 0, 0, 0);
                break;
            case COPY:
                port_set32(&port, step->target, 0, port_u32(&port, step->source, 0) + step->add);
                break;
        }
    }
    return port_return(&port, chain, entry->edx);
}
