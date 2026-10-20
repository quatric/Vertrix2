#include "process.h"

#include <string.h>
#include <strings.h>

static V3Code find(const V3Export *table, const char *name)
{
    for (; table->name; ++table)
    {
        if (strcmp(table->name, name) == 0)
        {
            return table->code;
        }
    }
    return NULL;
}

V3Code v3_import(const char *dll, const char *name)
{
    static const struct
    {
        const char *dll;
        const V3Export *table;
    } modules[] = {
        {"KERNEL32.DLL", v3_kernel32}, {"USER32.DLL", v3_user32},     {"WINMM.DLL", v3_winmm},
        {"OLE32.DLL", v3_ole32},       {"ADVAPI32.DLL", v3_advapi32}, {"D3D9.DLL", v3_d3d9},
        {"DINPUT8.DLL", v3_dinput8},   {"DINPUT.DLL", v3_dinput},     {"GDI32.DLL", v3_gdi32},
        {"SHELL32.DLL", v3_shell32},   {"COMCTL32.DLL", v3_comctl32}, {"COMDLG32.DLL", v3_comdlg32},
        {"WINSPOOL.DRV", v3_winspool}, {"DDRAW.DLL", v3_ddraw}};
    for (unsigned i = 0; i < sizeof modules / sizeof modules[0]; ++i)
    {
        if (strcasecmp(modules[i].dll, dll) == 0)
        {
            return find(modules[i].table, name);
        }
    }
    return NULL;
}
