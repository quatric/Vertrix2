#include "process.h"

#include <stdio.h>

static void CoInitialize(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void CoInitializeEx(Cpu *c)
{
    STDCALL_RETURN(2, 0);
}

static void CoUninitialize(Cpu *c)
{
    STDCALL_RETURN(0, 0);
}

static void CoCreateInstance(Cpu *c)
{
    const uint32_t g = ARG(0);
    v3_log("CoCreateInstance({%08x-%04x-%04x-...}) -> class not registered", v3_r32(g),
           v3_r16(g + 4), v3_r16(g + 6));
    if (ARG(4))
    {
        v3_w32(ARG(4), 0);
    }
    STDCALL_RETURN(5, 0x80040154u);
}

const V3Export v3_ole32[] = {{"CoInitialize", CoInitialize},
                             {"CoInitializeEx", CoInitializeEx},
                             {"CoUninitialize", CoUninitialize},
                             {"CoCreateInstance", CoCreateInstance},
                             {NULL, NULL}};
