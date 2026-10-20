#include "process.h"

static void RegOpenKeyA(Cpu *c)
{
    char name[256];
    v3_read_string(ARG(1), name, sizeof name);
    v3_log("RegOpenKeyA(%08x, %s) -> not found", ARG(0), name);
    STDCALL_RETURN(3, 2);
}

static void RegQueryValueExA(Cpu *c)
{
    STDCALL_RETURN(6, 2);
}

static void RegCloseKey(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void InitializeSecurityDescriptor(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void SetSecurityDescriptorDacl(Cpu *c)
{
    STDCALL_RETURN(4, 1);
}

const V3Export v3_advapi32[] = {{"RegOpenKeyA", RegOpenKeyA},
                                {"RegQueryValueExA", RegQueryValueExA},
                                {"RegCloseKey", RegCloseKey},
                                {"InitializeSecurityDescriptor", InitializeSecurityDescriptor},
                                {"SetSecurityDescriptorDacl", SetSecurityDescriptorDacl},
                                {NULL, NULL}};
