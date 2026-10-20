#include "process.h"

#include <string.h>

/* The shell, common controls, common dialogs and the print spooler, which the game's framework
 * (MFC) links: no files are dropped on the window, no printer exists and the controls need no
 * setup. */

static void DragAcceptFiles(Cpu *c)
{
    STDCALL_RETURN(2, 0);
}

static void DragFinish(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void DragQueryFileA(Cpu *c)
{
    STDCALL_RETURN(4, 0);
}

static void SHGetFileInfoA(Cpu *c)
{
    STDCALL_RETURN(5, 0);
}

static void InitCommonControls(Cpu *c)
{
    STDCALL_RETURN(0, 0);
}

/* GetFileTitleA(path, title, size): the file's name without its directory. */
static void GetFileTitleA(Cpu *c)
{
    char path[260];
    v3_read_string(ARG(0), path, sizeof path);
    const char *title = path;
    for (const char *p = path; *p; ++p)
    {
        if (*p == '\\' || *p == '/' || *p == ':')
        {
            title = p + 1;
        }
    }
    uint32_t needed = (uint32_t)strlen(title) + 1u;
    if (!ARG(1) || ARG(2) < needed)
    {
        STDCALL_RETURN(3, needed);
    }
    v3_write_string(ARG(1), title, ARG(2));
    STDCALL_RETURN(3, 0);
}

static void OpenPrinterA(Cpu *c)
{
    STDCALL_RETURN(3, 0);
}

static void ClosePrinter(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void DocumentPropertiesA(Cpu *c)
{
    STDCALL_RETURN(6, 0xffffffffu);
}

const V3Export v3_shell32[] = {{"DragAcceptFiles", DragAcceptFiles},
                               {"DragFinish", DragFinish},
                               {"DragQueryFileA", DragQueryFileA},
                               {"SHGetFileInfoA", SHGetFileInfoA},
                               {NULL, NULL}};

/* COMCTL32 is imported by ordinal: 17 is InitCommonControls. */
const V3Export v3_comctl32[] = {
    {"#17", InitCommonControls}, {"InitCommonControls", InitCommonControls}, {NULL, NULL}};

const V3Export v3_comdlg32[] = {{"GetFileTitleA", GetFileTitleA}, {NULL, NULL}};

const V3Export v3_winspool[] = {{"OpenPrinterA", OpenPrinterA},
                                {"ClosePrinter", ClosePrinter},
                                {"DocumentPropertiesA", DocumentPropertiesA},
                                {NULL, NULL}};
