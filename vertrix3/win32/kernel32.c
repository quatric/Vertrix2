#include "process.h"
#include "win32.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

/* The game's working directory as it sees it. */

static uint32_t command_line_a, command_line_w, environment_a, environment_w;
static const uint32_t KERNEL32_MODULE = 0x7c800000u;
static const uint32_t USER32_MODULE = 0x7e410000u;

static void set_error(uint32_t code)
{
    V3Thread *t = v3_current();
    if (t)
    {
        t->last_error = code;
    }
}

static uint32_t wide_string(const char *text)
{
    const uint32_t n = (uint32_t)strlen(text);
    const uint32_t at = v3_system_alloc(2 * n + 2);
    for (uint32_t i = 0; i <= n; ++i)
    {
        v3_w16(at + 2 * i, (uint8_t)text[i]);
    }
    return at;
}

void v3_process_init(const char *command_line)
{
    command_line_a = v3_system_string(command_line);
    command_line_w = wide_string(command_line);
    static const char env[] = "PATH=C:\\Windows\0OS=Windows_NT\0\0";
    environment_a = v3_system_alloc(sizeof env);
    memcpy(MEM(environment_a), env, sizeof env);
    environment_w = v3_system_alloc(2 * sizeof env);
    for (uint32_t i = 0; i < sizeof env; ++i)
    {
        v3_w16(environment_w + 2 * i, (uint8_t)env[i]);
    }
}

void v3_host_path(const char *game_path, char *out, size_t size)
{
    /* Drop a drive and the game directory, and ".\"; the rest is relative to the platform's
     * directory, with forward slashes. */
    const char *p = game_path;
    if (strncasecmp(p, v3_game_directory, strlen(v3_game_directory)) == 0 &&
        p[strlen(v3_game_directory)] == '\\')
    {
        p += strlen(v3_game_directory) + 1;
    }
    else if (p[0] && p[1] == ':')
    {
        p += 2;
    }
    while (p[0] == '.' && (p[1] == '\\' || p[1] == '/'))
    {
        p += 2;
    }
    while (*p == '\\' || *p == '/')
    {
        ++p;
    }
    snprintf(out, size, "%s/%s", v3_platform->directory, p);
    for (char *q = out; *q; ++q)
    {
        if (*q == '\\')
        {
            *q = '/';
        }
    }
}

/* --- process and module ----------------------------------------------------------------- */

static void GetCommandLineA(Cpu *c)
{
    STDCALL_RETURN(0, command_line_a);
}

static void GetStartupInfoA(Cpu *c)
{
    const uint32_t info = ARG(0);
    memset(MEM(info), 0, 68);
    v3_w32(info, 68);
    STDCALL_RETURN(1, 0);
}

static void GetModuleHandleA(Cpu *c)
{
    char name[64];
    v3_read_string(ARG(0), name, sizeof name);
    uint32_t module = 0;
    if (!ARG(0))
    {
        module = V3_IMAGE_BASE;
    }
    else if (strncasecmp(name, "kernel32", 8) == 0)
    {
        module = KERNEL32_MODULE;
    }
    else if (strncasecmp(name, "user32", 6) == 0)
    {
        module = USER32_MODULE;
    }
    if (!module)
    {
        set_error(126);
    }
    STDCALL_RETURN(1, module);
}

static void GetModuleHandleW(Cpu *c)
{
    char name[64];
    uint32_t i = 0;
    const uint32_t w = ARG(0);
    for (; w && i < sizeof name - 1 && v3_r16(w + 2 * i); ++i)
    {
        name[i] = (char)v3_r16(w + 2 * i);
    }
    name[i] = 0;
    uint32_t module = !w ? V3_IMAGE_BASE : strncasecmp(name, "kernel32", 8) == 0 ? KERNEL32_MODULE : 0;
    STDCALL_RETURN(1, module);
}

/* DLLs the host provides: LoadLibraryA hands out a module handle and GetProcAddress finds
 * their exports among the imports it implements. Vertrix 2 v2.0 loads and frees dpnhpast.dll
 * (DirectPlay's NAT helper, new in DirectX 8.1) only to check that DirectX 8.1 is installed
 * (0x484b30); it exports nothing the game asks for. */
static const struct
{
    const char *name;
    const char *dll;
    uint32_t handle;
} LIBRARIES[] = {{"d3d9", "D3D9.DLL", 0x4fdf0000u}, {"dinput8", "DINPUT8.DLL", 0x4f800000u},
                 {"kernel32", "KERNEL32.DLL", 0x7c800000u}, {"user32", "USER32.DLL", 0x7e410000u},
                 {"dpnhpast", "DPNHPAST.DLL", 0x4e800000u}};

static void LoadLibraryA(Cpu *c);

static void GetProcAddress(Cpu *c)
{
    char name[64];
    v3_read_string(ARG(1), name, sizeof name);
    for (unsigned i = 0; i < sizeof LIBRARIES / sizeof LIBRARIES[0]; ++i)
    {
        if (ARG(0) == LIBRARIES[i].handle && ARG(1) >= 0x10000u)
        {
            V3Code code = v3_import(LIBRARIES[i].dll, name);
            if (code)
            {
                static struct
                {
                    V3Code code;
                    uint32_t address;
                } made[32];
                static unsigned made_count;
                for (unsigned k = 0; k < made_count; ++k)
                {
                    if (made[k].code == code)
                    {
                        STDCALL_RETURN(2, made[k].address);
                    }
                }
                char *label = malloc(strlen(LIBRARIES[i].dll) + strlen(name) + 2);
                sprintf(label, "%s!%s", LIBRARIES[i].dll, name);
                const uint32_t address = v3_host_function(label, code);
                if (made_count < 32)
                {
                    made[made_count].code = code;
                    made[made_count++].address = address;
                }
                v3_log("GetProcAddress(%s) -> host", label);
                STDCALL_RETURN(2, address);
            }
        }
    }
    /* The runtime library asks for newer kernel32 entries (FlsAlloc, EncodePointer...) and
     * copes without them. */
    static char asked[1024];
    if (!strstr(asked, name) && strlen(asked) + strlen(name) + 2 < sizeof asked)
    {
        strcat(asked, name);
        strcat(asked, ",");
        v3_log("GetProcAddress(%08x, %s) -> not provided", ARG(0), name);
    }
    set_error(127);
    STDCALL_RETURN(2, 0);
}

static void LoadLibraryA(Cpu *c)
{
    char name[128];
    v3_read_string(ARG(0), name, sizeof name);
    for (unsigned i = 0; i < sizeof LIBRARIES / sizeof LIBRARIES[0]; ++i)
    {
        if (strncasecmp(name, LIBRARIES[i].name, strlen(LIBRARIES[i].name)) == 0)
        {
            v3_log("LoadLibraryA(%s)", name);
            STDCALL_RETURN(1, LIBRARIES[i].handle);
        }
    }
    v3_log("LoadLibraryA(%s) -> not provided", name);
    set_error(126);
    STDCALL_RETURN(1, 0);
}

static void FreeLibrary(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void GetModuleFileNameA(Cpu *c)
{
    char path[260];
    snprintf(path, sizeof path, "%s\\%s", v3_game_directory, v3_executable);
    const uint32_t size = ARG(2);
    v3_write_string(ARG(1), path, size);
    const uint32_t n = (uint32_t)strlen(path);
    STDCALL_RETURN(3, n < size ? n : size);
}

static void GetCurrentDirectoryA(Cpu *c)
{
    const uint32_t size = ARG(0);
    const char *dir = v3_game_directory;
    const uint32_t n = (uint32_t)strlen(dir);
    if (size <= n)
    {
        STDCALL_RETURN(2, n + 1);
    }
    v3_write_string(ARG(1), dir, size);
    STDCALL_RETURN(2, n);
}

static void GetFullPathNameA(Cpu *c)
{
    char name[260], full[300];
    v3_read_string(ARG(0), name, sizeof name);
    if (name[0] && name[1] == ':')
    {
        snprintf(full, sizeof full, "%s", name);
    }
    else
    {
        const char *p = name;
        while (p[0] == '.' && p[1] == '\\')
        {
            p += 2;
        }
        snprintf(full, sizeof full, "%s\\%s", v3_game_directory, p);
    }
    const uint32_t n = (uint32_t)strlen(full);
    const uint32_t size = ARG(1);
    if (size <= n)
    {
        STDCALL_RETURN(4, n + 1);
    }
    v3_write_string(ARG(2), full, size);
    if (ARG(3))
    {
        const char *slash = strrchr(full, '\\');
        v3_w32(ARG(3), ARG(2) + (uint32_t)(slash ? slash + 1 - full : 0));
    }
    STDCALL_RETURN(4, n);
}

static void GetCurrentProcess(Cpu *c)
{
    STDCALL_RETURN(0, 0xffffffffu);
}

static void GetCurrentProcessId(Cpu *c)
{
    STDCALL_RETURN(0, 0x40);
}

static void GetCurrentThreadId(Cpu *c)
{
    STDCALL_RETURN(0, v3_current()->id);
}

static void SetPriorityClass(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void ExitProcess(Cpu *c)
{
    v3_log("ExitProcess(%u)", ARG(0));
    v3_process_exit(ARG(0));
}

static void TerminateProcess(Cpu *c)
{
    v3_log("TerminateProcess(%u)", ARG(1));
    v3_process_exit(ARG(1));
}

static void UnhandledExceptionFilter(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void SetUnhandledExceptionFilter(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void IsDebuggerPresent(Cpu *c)
{
    STDCALL_RETURN(0, 0);
}

static void IsProcessorFeaturePresent(Cpu *c)
{
    /* No MMX, SSE or 3DNow! (see v3_cpuid). */
    STDCALL_RETURN(1, 0);
}

static void GetSystemInfo(Cpu *c)
{
    const uint32_t info = ARG(0);
    memset(MEM(info), 0, 36);
    v3_w32(info + 4, 4096);           /* page size */
    v3_w32(info + 8, 0x10000);        /* minimum application address */
    v3_w32(info + 12, 0x7ffeffff);    /* maximum */
    v3_w32(info + 16, 1);             /* active processor mask */
    v3_w32(info + 20, 1);             /* processors */
    v3_w32(info + 24, 586);           /* processor type */
    v3_w32(info + 28, 0x10000);       /* allocation granularity */
    v3_w16(info + 32, 6);             /* level */
    STDCALL_RETURN(1, 0);
}

static void SetErrorMode(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void GetLastError(Cpu *c)
{
    STDCALL_RETURN(0, v3_current()->last_error);
}

static void SetLastError(Cpu *c)
{
    v3_current()->last_error = ARG(0);
    STDCALL_RETURN(1, 0);
}

static void OutputDebugStringA(Cpu *c)
{
    char text[512];
    v3_read_string(ARG(0), text, sizeof text);
    v3_log("debug: %s", text);
    STDCALL_RETURN(1, 0);
}

static void FormatMessageA(Cpu *c)
{
    STDCALL_RETURN(7, 0);
}

static void RaiseException(Cpu *c)
{
    v3_log("RaiseException(code %08x, flags %x, %u arguments)", ARG(0), ARG(1), ARG(2));
    v3_trap(c, v3_r32(c->esp), "exception raised");
}

static void RtlUnwind(Cpu *c)
{
    v3_trap(c, v3_r32(c->esp), "RtlUnwind");
}

/* --- environment, locale, code pages ---------------------------------------------------- */

static void GetEnvironmentStrings(Cpu *c)
{
    STDCALL_RETURN(0, environment_a);
}

static void GetEnvironmentStringsW(Cpu *c)
{
    STDCALL_RETURN(0, environment_w);
}

static void FreeEnvironmentStringsA(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void SetEnvironmentVariableA(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void GetACP(Cpu *c)
{
    STDCALL_RETURN(0, 1252);
}

static void GetOEMCP(Cpu *c)
{
    STDCALL_RETURN(0, 437);
}

static void IsValidCodePage(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void GetCPInfo(Cpu *c)
{
    const uint32_t info = ARG(1);
    memset(MEM(info), 0, 20);
    v3_w32(info, 1);         /* MaxCharSize */
    v3_w8(info + 4, '?');    /* DefaultChar */
    STDCALL_RETURN(2, 1);
}

static void GetUserDefaultLCID(Cpu *c)
{
    STDCALL_RETURN(0, 0x409);
}

static void IsValidLocale(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void EnumSystemLocalesA(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static const char *locale_info(uint32_t type)
{
    switch (type & 0xffffu)
    {
    case 0x1004: /* LOCALE_IDEFAULTANSICODEPAGE */
        return "1252";
    case 0xb: /* LOCALE_IDEFAULTCODEPAGE */
        return "437";
    case 0x1001: /* LOCALE_SENGLANGUAGE */
        return "English";
    case 0x1002: /* LOCALE_SENGCOUNTRY */
        return "United States";
    case 0x3: /* LOCALE_SABBREVLANGNAME */
        return "ENU";
    case 0x7: /* LOCALE_SABBREVCTRYNAME */
        return "USA";
    case 0xe: /* LOCALE_SDECIMAL */
        return ".";
    case 0xf: /* LOCALE_STHOUSAND */
        return ",";
    case 0x10: /* LOCALE_SGROUPING */
        return "3;0";
    default:
        return "";
    }
}

static void GetLocaleInfoA(Cpu *c)
{
    const char *text = locale_info(ARG(1));
    const uint32_t n = (uint32_t)strlen(text) + 1;
    if (ARG(3) == 0)
    {
        STDCALL_RETURN(4, n);
    }
    v3_write_string(ARG(2), text, ARG(3));
    STDCALL_RETURN(4, n <= ARG(3) ? n : 0);
}

static void GetLocaleInfoW(Cpu *c)
{
    const char *text = locale_info(ARG(1));
    const uint32_t n = (uint32_t)strlen(text) + 1;
    if (ARG(3) == 0)
    {
        STDCALL_RETURN(4, n);
    }
    for (uint32_t i = 0; i < n && i < ARG(3); ++i)
    {
        v3_w16(ARG(2) + 2 * i, (uint8_t)text[i]);
    }
    STDCALL_RETURN(4, n <= ARG(3) ? n : 0);
}

static void MultiByteToWideChar(Cpu *c)
{
    const uint32_t src = ARG(2);
    int32_t n = (int32_t)ARG(3);
    const uint32_t dst = ARG(4);
    const uint32_t room = ARG(5);
    if (n < 0)
    {
        n = (int32_t)v3_string_length(src) + 1;
    }
    if (room == 0)
    {
        STDCALL_RETURN(6, n);
    }
    if ((uint32_t)n > room)
    {
        set_error(122);
        STDCALL_RETURN(6, 0);
    }
    for (int32_t i = 0; i < n; ++i)
    {
        v3_w16(dst + 2u * (uint32_t)i, v3_r8(src + (uint32_t)i));
    }
    STDCALL_RETURN(6, n);
}

static void WideCharToMultiByte(Cpu *c)
{
    const uint32_t src = ARG(2);
    int32_t n = (int32_t)ARG(3);
    const uint32_t dst = ARG(4);
    const uint32_t room = ARG(5);
    if (n < 0)
    {
        n = 0;
        while (v3_r16(src + 2u * (uint32_t)n))
        {
            ++n;
        }
        ++n;
    }
    if (room == 0)
    {
        STDCALL_RETURN(8, n);
    }
    if ((uint32_t)n > room)
    {
        set_error(122);
        STDCALL_RETURN(8, 0);
    }
    for (int32_t i = 0; i < n; ++i)
    {
        const uint32_t w = v3_r16(src + 2u * (uint32_t)i);
        v3_w8(dst + (uint32_t)i, w < 256 ? w : '?');
    }
    if (ARG(7))
    {
        v3_w32(ARG(7), 0);
    }
    STDCALL_RETURN(8, n);
}

static uint32_t map_char(uint32_t ch, uint32_t flags)
{
    if (ch < 128)
    {
        if (flags & 0x200)
        {
            return (uint32_t)toupper((int)ch);
        }
        if (flags & 0x100)
        {
            return (uint32_t)tolower((int)ch);
        }
    }
    return ch;
}

static void LCMapStringA(Cpu *c)
{
    const uint32_t flags = ARG(1);
    const uint32_t src = ARG(2);
    int32_t n = (int32_t)ARG(3);
    if (n < 0)
    {
        n = (int32_t)v3_string_length(src) + 1;
    }
    if (ARG(5) == 0)
    {
        STDCALL_RETURN(6, n);
    }
    for (int32_t i = 0; i < n && (uint32_t)i < ARG(5); ++i)
    {
        v3_w8(ARG(4) + (uint32_t)i, map_char(v3_r8(src + (uint32_t)i), flags));
    }
    STDCALL_RETURN(6, n);
}

static void LCMapStringW(Cpu *c)
{
    const uint32_t flags = ARG(1);
    const uint32_t src = ARG(2);
    int32_t n = (int32_t)ARG(3);
    if (n < 0)
    {
        n = 0;
        while (v3_r16(src + 2u * (uint32_t)n))
        {
            ++n;
        }
        ++n;
    }
    if (ARG(5) == 0)
    {
        STDCALL_RETURN(6, n);
    }
    for (int32_t i = 0; i < n && (uint32_t)i < ARG(5); ++i)
    {
        v3_w16(ARG(4) + 2u * (uint32_t)i, map_char(v3_r16(src + 2u * (uint32_t)i), flags));
    }
    STDCALL_RETURN(6, n);
}

static uint32_t char_type(uint32_t ch)
{
    /* CT_CTYPE1: upper 1, lower 2, digit 4, space 8, punct 0x10, cntrl 0x20, blank 0x40,
     * xdigit 0x80, alpha 0x100. */
    uint32_t t = 0;
    if (ch >= 128)
    {
        return (ch >= 0xc0 && ch != 0xd7 && ch != 0xf7) ? 0x100u | (ch < 0xe0 ? 1u : 2u) : 0x10u;
    }
    const int k = (int)ch;
    if (isupper(k))
        t |= 1;
    if (islower(k))
        t |= 2;
    if (isdigit(k))
        t |= 4;
    if (isspace(k))
        t |= 8;
    if (ispunct(k))
        t |= 0x10;
    if (iscntrl(k))
        t |= 0x20;
    if (k == ' ' || k == '\t')
        t |= 0x40;
    if (isxdigit(k))
        t |= 0x80;
    if (isalpha(k))
        t |= 0x100;
    return t;
}

static void GetStringTypeA(Cpu *c)
{
    /* (locale, info type, string, count, out) */
    const uint32_t src = ARG(2);
    int32_t n = (int32_t)ARG(3);
    if (n < 0)
    {
        n = (int32_t)v3_string_length(src) + 1;
    }
    for (int32_t i = 0; i < n; ++i)
    {
        v3_w16(ARG(4) + 2u * (uint32_t)i, char_type(v3_r8(src + (uint32_t)i)));
    }
    STDCALL_RETURN(5, 1);
}

static void GetStringTypeW(Cpu *c)
{
    /* (info type, string, count, out) */
    const uint32_t src = ARG(1);
    int32_t n = (int32_t)ARG(2);
    if (n < 0)
    {
        n = 0;
        while (v3_r16(src + 2u * (uint32_t)n))
        {
            ++n;
        }
        ++n;
    }
    for (int32_t i = 0; i < n; ++i)
    {
        v3_w16(ARG(3) + 2u * (uint32_t)i, char_type(v3_r16(src + 2u * (uint32_t)i)));
    }
    STDCALL_RETURN(4, 1);
}

static int compare_strings(uint32_t flags, uint32_t a, int32_t na, uint32_t b, int32_t nb, int wide)
{
    const uint32_t step = wide ? 2u : 1u;
    if (na < 0)
    {
        na = 0;
        while (wide ? v3_r16(a + 2u * (uint32_t)na) : v3_r8(a + (uint32_t)na))
            ++na;
    }
    if (nb < 0)
    {
        nb = 0;
        while (wide ? v3_r16(b + 2u * (uint32_t)nb) : v3_r8(b + (uint32_t)nb))
            ++nb;
    }
    for (int32_t i = 0;; ++i)
    {
        if (i == na || i == nb)
        {
            return na == nb ? 2 : (na < nb ? 1 : 3);
        }
        uint32_t x = wide ? v3_r16(a + step * (uint32_t)i) : v3_r8(a + (uint32_t)i);
        uint32_t y = wide ? v3_r16(b + step * (uint32_t)i) : v3_r8(b + (uint32_t)i);
        if (flags & 1)
        {
            x = map_char(x, 0x100);
            y = map_char(y, 0x100);
        }
        if (x != y)
        {
            return x < y ? 1 : 3;
        }
    }
}

static void CompareStringA(Cpu *c)
{
    STDCALL_RETURN(6, compare_strings(ARG(1), ARG(2), (int32_t)ARG(3), ARG(4), (int32_t)ARG(5), 0));
}

static void CompareStringW(Cpu *c)
{
    STDCALL_RETURN(6, compare_strings(ARG(1), ARG(2), (int32_t)ARG(3), ARG(4), (int32_t)ARG(5), 1));
}

/* --- memory ----------------------------------------------------------------------------- */

static void HeapCreate(Cpu *c)
{
    STDCALL_RETURN(3, v3_handle_new(V3_HANDLE_HEAP, NULL));
}

static void HeapAlloc(Cpu *c)
{
    const uint32_t p = v3_alloc(ARG(2));
    STDCALL_RETURN(3, p);
}

static void HeapFree(Cpu *c)
{
    v3_free(ARG(2));
    STDCALL_RETURN(3, 1);
}

static void HeapSize(Cpu *c)
{
    STDCALL_RETURN(3, v3_alloc_size(ARG(2)));
}

static void HeapReAlloc(Cpu *c)
{
    const uint32_t flags = ARG(1);
    const uint32_t old = ARG(2);
    const uint32_t size = ARG(3);
    if (flags & 0x10) /* HEAP_REALLOC_IN_PLACE_ONLY */
    {
        STDCALL_RETURN(4, size <= v3_alloc_size(old) ? old : 0);
    }
    const uint32_t old_size = v3_alloc_size(old);
    const uint32_t p = v3_realloc(old, size);
    if (p && size > old_size)
    {
        memset(MEM(p + old_size), 0, size - old_size);
    }
    STDCALL_RETURN(4, p);
}

static void VirtualAlloc(Cpu *c)
{
    const uint32_t address = ARG(0);
    const uint32_t size = ARG(1);
    if (address)
    {
        /* Committing pages of a reservation made earlier: they are already usable. */
        STDCALL_RETURN(4, address);
    }
    STDCALL_RETURN(4, v3_alloc_aligned(size, 0x10000));
}

static void VirtualFree(Cpu *c)
{
    if (ARG(2) & 0x8000) /* MEM_RELEASE */
    {
        v3_free(ARG(0));
    }
    STDCALL_RETURN(3, 1);
}

static void VirtualQuery(Cpu *c)
{
    const uint32_t address = ARG(0);
    const uint32_t info = ARG(1);
    memset(MEM(info), 0, 28);
    v3_w32(info, address & ~0xfffu);
    v3_w32(info + 4, address & ~0xffffu);
    v3_w32(info + 8, 4);           /* PAGE_READWRITE */
    v3_w32(info + 12, 0x10000);    /* region size */
    v3_w32(info + 16, 0x1000);     /* MEM_COMMIT */
    v3_w32(info + 20, 4);
    v3_w32(info + 24, 0x20000);    /* MEM_PRIVATE */
    STDCALL_RETURN(3, 28);
}

static void GlobalAlloc(Cpu *c)
{
    STDCALL_RETURN(2, v3_alloc(ARG(1)));
}

static void GlobalLock(Cpu *c)
{
    STDCALL_RETURN(1, ARG(0));
}

static void GlobalUnlock(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void GlobalFree(Cpu *c)
{
    v3_free(ARG(0));
    STDCALL_RETURN(1, 0);
}

static void LocalFree(Cpu *c)
{
    v3_free(ARG(0));
    STDCALL_RETURN(1, 0);
}

/* --- threads and synchronisation -------------------------------------------------------- */

static void TlsAlloc(Cpu *c)
{
    /* Slot 0 is never handed out, so that 0 never names a slot. */
    static uint32_t next = 1;
    v3_lock();
    const uint32_t slot = next < V3_TLS_SLOTS ? next++ : 0xffffffffu;
    v3_unlock();
    STDCALL_RETURN(0, slot);
}

static void TlsFree(Cpu *c)
{
    STDCALL_RETURN(1, 1);
}

static void TlsGetValue(Cpu *c)
{
    const uint32_t slot = ARG(0);
    v3_current()->last_error = 0;
    STDCALL_RETURN(1, slot < V3_TLS_SLOTS ? v3_current()->tls[slot] : 0);
}

static void TlsSetValue(Cpu *c)
{
    const uint32_t slot = ARG(0);
    if (slot < V3_TLS_SLOTS)
    {
        v3_current()->tls[slot] = ARG(1);
    }
    STDCALL_RETURN(2, slot < V3_TLS_SLOTS);
}

static void InterlockedIncrement(Cpu *c)
{
    v3_lock();
    const uint32_t v = v3_r32(ARG(0)) + 1;
    v3_w32(ARG(0), v);
    v3_unlock();
    STDCALL_RETURN(1, v);
}

static void InterlockedDecrement(Cpu *c)
{
    v3_lock();
    const uint32_t v = v3_r32(ARG(0)) - 1;
    v3_w32(ARG(0), v);
    v3_unlock();
    STDCALL_RETURN(1, v);
}

/* Critical sections: the host mutex is kept in the structure's LockSemaphore field (+0x10) as
 * an index into this table (plus one). */
enum
{
    SECTIONS = 512
};
static V3Mutex *sections[SECTIONS];
static unsigned section_count;

static V3Mutex *section(uint32_t cs)
{
    uint32_t index = v3_r32(cs + 0x10);
    if (index == 0 || index > section_count || index != (v3_r32(cs + 0x14) ^ 0x5ec70000u))
    {
        v3_lock();
        index = v3_r32(cs + 0x10);
        if (index == 0 || index > section_count || index != (v3_r32(cs + 0x14) ^ 0x5ec70000u))
        {
            if (section_count == SECTIONS)
            {
                v3_fatal("too many critical sections");
            }
            sections[section_count++] = v3_mutex_create();
            index = section_count;
            v3_w32(cs + 0x10, index);
            v3_w32(cs + 0x14, index ^ 0x5ec70000u);
        }
        v3_unlock();
    }
    return sections[index - 1];
}

static void InitializeCriticalSection(Cpu *c)
{
    memset(MEM(ARG(0)), 0, 24);
    v3_w32(ARG(0) + 4, 0xffffffffu);
    section(ARG(0));
    STDCALL_RETURN(1, 0);
}

static void InitializeCriticalSectionAndSpinCount(Cpu *c)
{
    memset(MEM(ARG(0)), 0, 24);
    v3_w32(ARG(0) + 4, 0xffffffffu);
    section(ARG(0));
    STDCALL_RETURN(2, 1);
}

static void DeleteCriticalSection(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void EnterCriticalSection(Cpu *c)
{
    v3_mutex_lock(section(ARG(0)));
    STDCALL_RETURN(1, 0);
}

static void LeaveCriticalSection(Cpu *c)
{
    v3_mutex_unlock(section(ARG(0)));
    STDCALL_RETURN(1, 0);
}

static void CreateEventA(Cpu *c)
{
    V3EventObject *e = calloc(1, sizeof *e);
    e->event = v3_event_create((int)ARG(1), (int)ARG(2));
    set_error(0);
    STDCALL_RETURN(4, v3_handle_new(V3_HANDLE_EVENT, e));
}

static void SetEvent(Cpu *c)
{
    V3EventObject *e = v3_handle_get(ARG(0), V3_HANDLE_EVENT);
    if (e)
    {
        v3_event_set(e->event);
    }
    STDCALL_RETURN(1, e != NULL);
}

static void ResetEvent(Cpu *c)
{
    V3EventObject *e = v3_handle_get(ARG(0), V3_HANDLE_EVENT);
    if (e)
    {
        v3_event_reset(e->event);
    }
    STDCALL_RETURN(1, e != NULL);
}

static void CreateMutexA(Cpu *c)
{
    set_error(0);
    STDCALL_RETURN(3, v3_handle_new(V3_HANDLE_MUTEX, v3_mutex_create()));
}

static V3Event *waitable(uint32_t handle)
{
    switch (v3_handle_type(handle))
    {
    case V3_HANDLE_EVENT:
        return ((V3EventObject *)v3_handle_get(handle, V3_HANDLE_EVENT))->event;
    case V3_HANDLE_THREAD:
        return ((V3Thread *)v3_handle_get(handle, V3_HANDLE_THREAD))->done;
    default:
        return NULL;
    }
}

static uint32_t wait_for(const uint32_t *handle_list, uint32_t count, int all, uint32_t timeout)
{
    V3Event *events[64];
    if (count == 1 && v3_handle_type(handle_list[0]) == V3_HANDLE_MUTEX)
    {
        V3Mutex *m = v3_handle_get(handle_list[0], V3_HANDLE_MUTEX);
        if (timeout == 0xffffffffu)
        {
            v3_mutex_lock(m);
            return 0;
        }
        return v3_mutex_try_lock(m) ? 0 : 0x102;
    }
    for (uint32_t i = 0; i < count && i < 64; ++i)
    {
        events[i] = waitable(handle_list[i]);
        if (!events[i])
        {
            v3_log("wait on unsupported handle %08x", handle_list[i]);
            return 0xffffffffu;
        }
    }
    const int got = v3_event_wait(events, count, all, timeout);
    return got < 0 ? 0x102u : (uint32_t)got;
}

static void WaitForSingleObject(Cpu *c)
{
    const uint32_t h = ARG(0);
    STDCALL_RETURN(2, wait_for(&h, 1, 0, ARG(1)));
}

static void WaitForMultipleObjects(Cpu *c)
{
    uint32_t list[64];
    const uint32_t count = ARG(0) < 64 ? ARG(0) : 64;
    for (uint32_t i = 0; i < count; ++i)
    {
        list[i] = v3_r32(ARG(1) + 4 * i);
    }
    STDCALL_RETURN(4, wait_for(list, count, (int)ARG(2), ARG(3)));
}

static void CreateThread(Cpu *c)
{
    V3Thread *t = v3_thread_create(ARG(2), ARG(3), ARG(1));
    if (!t)
    {
        STDCALL_RETURN(6, 0);
    }
    if (ARG(5))
    {
        v3_w32(ARG(5), t->id);
    }
    v3_log("CreateThread(start %08x, parameter %08x) -> thread %x", ARG(2), ARG(3), t->id);
    if (ARG(4) & 4) /* CREATE_SUSPENDED */
    {
        v3_log("suspended thread creation is not supported; starting it now");
    }
    v3_thread_run(t, 0);
    STDCALL_RETURN(6, t->handle);
}

static void SetThreadPriority(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void Sleep(Cpu *c)
{
    v3_sleep_ms(ARG(0));
    STDCALL_RETURN(1, 0);
}

static void CloseHandle(Cpu *c)
{
    const uint32_t h = ARG(0);
    const int type = v3_handle_type(h);
    if (type == V3_HANDLE_FILE)
    {
        FILE *f = v3_handle_get(h, V3_HANDLE_FILE);
        fclose(f);
    }
    if (type && type != V3_HANDLE_THREAD && type != V3_HANDLE_CONSOLE)
    {
        v3_handle_close(h);
    }
    STDCALL_RETURN(1, type != 0);
}

/* --- time ------------------------------------------------------------------------------- */

/* Windows 98 (4.10, build 2222): Vertrix 2 v1.2 (2001) then keeps its runtime on the ANSI calls
 * (the high bit marks Windows 9x). */
static void GetVersion(Cpu *c)
{
    STDCALL_RETURN(0, 0xc8ae0a04u);
}

static void GetTickCount(Cpu *c)
{
    STDCALL_RETURN(0, (uint32_t)(v3_microseconds() / 1000u));
}

static void QueryPerformanceCounter(Cpu *c)
{
    v3_w64(ARG(0), v3_microseconds());
    STDCALL_RETURN(1, 1);
}

static void GetSystemTimeAsFileTime(Cpu *c)
{
    /* 2009-06-01, plus the time since start. */
    const uint64_t t = 128882016000000000ull + v3_microseconds() * 10u;
    v3_w64(ARG(0), t);
    STDCALL_RETURN(1, 0);
}

/* --- files and console ------------------------------------------------------------------ */

static uint32_t console[3];

static void GetStdHandle(Cpu *c)
{
    const uint32_t which = ARG(0);
    const unsigned i = which == 0xfffffff6u ? 0 : which == 0xfffffff5u ? 1 : 2;
    if (!console[i])
    {
        console[i] = v3_handle_new(V3_HANDLE_CONSOLE, NULL);
    }
    STDCALL_RETURN(1, console[i]);
}

static void SetStdHandle(Cpu *c)
{
    STDCALL_RETURN(2, 1);
}

static void SetHandleCount(Cpu *c)
{
    STDCALL_RETURN(1, ARG(0));
}

static void GetFileType(Cpu *c)
{
    const int type = v3_handle_type(ARG(0));
    STDCALL_RETURN(1, type == V3_HANDLE_CONSOLE ? 2 : type == V3_HANDLE_FILE ? 1 : 0);
}

static void GetConsoleCP(Cpu *c)
{
    STDCALL_RETURN(0, 437);
}

static void GetConsoleOutputCP(Cpu *c)
{
    STDCALL_RETURN(0, 437);
}

static void GetConsoleMode(Cpu *c)
{
    STDCALL_RETURN(2, 0);
}

static void WriteConsoleA(Cpu *c)
{
    char text[512];
    const uint32_t n = ARG(2) < sizeof text - 1 ? ARG(2) : (uint32_t)sizeof text - 1;
    memcpy(text, MEM(ARG(1)), n);
    text[n] = 0;
    v3_log("console: %s", text);
    if (ARG(3))
    {
        v3_w32(ARG(3), ARG(2));
    }
    STDCALL_RETURN(5, 1);
}

static void WriteConsoleW(Cpu *c)
{
    if (ARG(3))
    {
        v3_w32(ARG(3), ARG(2));
    }
    STDCALL_RETURN(5, 1);
}

static void CreateFileA(Cpu *c)
{
    char name[260], path[600];
    v3_read_string(ARG(0), name, sizeof name);
    v3_host_path(name, path, sizeof path);
    const uint32_t access = ARG(1);
    const uint32_t disposition = ARG(4);
    const char *mode;
    FILE *f = NULL;
    if (access & 0x40000000u) /* GENERIC_WRITE */
    {
        if (disposition == 3 || disposition == 4) /* OPEN_EXISTING, OPEN_ALWAYS */
        {
            f = fopen(path, "r+b");
        }
        if (!f && disposition != 3 && disposition != 5)
        {
            f = fopen(path, "w+b");
        }
        else if (f && disposition == 2) /* CREATE_ALWAYS */
        {
            fclose(f);
            f = fopen(path, "w+b");
        }
        mode = "write";
    }
    else
    {
        f = fopen(path, "rb");
        mode = "read";
    }
    v3_log("CreateFileA(%s, %s) -> %s", name, mode, f ? "opened" : "missing");
    if (!f)
    {
        set_error(2);
        STDCALL_RETURN(7, 0xffffffffu);
    }
    set_error(0);
    STDCALL_RETURN(7, v3_handle_new(V3_HANDLE_FILE, f));
}

static void ReadFile(Cpu *c)
{
    FILE *f = v3_handle_get(ARG(0), V3_HANDLE_FILE);
    uint32_t got = 0;
    if (f)
    {
        const uint32_t want = ARG(2);
        if (v3_contiguous(ARG(1), want))
        {
            got = (uint32_t)fread(MEM(ARG(1)), 1, want, f);
        }
        else
        {
            v3_log("ReadFile into a split buffer");
        }
    }
    if (ARG(3))
    {
        v3_w32(ARG(3), got);
    }
    STDCALL_RETURN(5, f != NULL);
}

static void WriteFile(Cpu *c)
{
    const int type = v3_handle_type(ARG(0));
    uint32_t done = ARG(2);
    if (type == V3_HANDLE_FILE)
    {
        FILE *f = v3_handle_get(ARG(0), V3_HANDLE_FILE);
        done = (uint32_t)fwrite(MEM(ARG(1)), 1, ARG(2), f);
    }
    else if (type == V3_HANDLE_CONSOLE)
    {
        char text[512];
        const uint32_t n = ARG(2) < sizeof text - 1 ? ARG(2) : (uint32_t)sizeof text - 1;
        memcpy(text, MEM(ARG(1)), n);
        text[n] = 0;
        v3_log("stdout: %s", text);
    }
    if (ARG(3))
    {
        v3_w32(ARG(3), done);
    }
    STDCALL_RETURN(5, type != 0);
}

static void SetFilePointer(Cpu *c)
{
    FILE *f = v3_handle_get(ARG(0), V3_HANDLE_FILE);
    if (!f)
    {
        STDCALL_RETURN(4, 0xffffffffu);
    }
    int64_t distance = (int32_t)ARG(1);
    if (ARG(2))
    {
        distance = (int64_t)(((uint64_t)v3_r32(ARG(2)) << 32) | ARG(1));
    }
    const int whence = ARG(3) == 0 ? SEEK_SET : ARG(3) == 1 ? SEEK_CUR : SEEK_END;
    fseek(f, (long)distance, whence);
    const long at = ftell(f);
    if (ARG(2))
    {
        v3_w32(ARG(2), 0);
    }
    STDCALL_RETURN(4, (uint32_t)at);
}

static void GetFileSize(Cpu *c)
{
    FILE *f = v3_handle_get(ARG(0), V3_HANDLE_FILE);
    if (!f)
    {
        STDCALL_RETURN(2, 0xffffffffu);
    }
    const long at = ftell(f);
    fseek(f, 0, SEEK_END);
    const long size = ftell(f);
    fseek(f, at, SEEK_SET);
    if (ARG(1))
    {
        v3_w32(ARG(1), 0);
    }
    STDCALL_RETURN(2, (uint32_t)size);
}

static void FlushFileBuffers(Cpu *c)
{
    FILE *f = v3_handle_get(ARG(0), V3_HANDLE_FILE);
    if (f)
    {
        fflush(f);
    }
    STDCALL_RETURN(1, 1);
}

static void GetDriveTypeA(Cpu *c)
{
    STDCALL_RETURN(1, 3);
}

static void CreateDirectoryA(Cpu *c)
{
    char name[260], path[600];
    v3_read_string(ARG(0), name, sizeof name);
    v3_host_path(name, path, sizeof path);
    const int ok = mkdir(path, 0755) == 0;
    set_error(ok ? 0 : 183);
    STDCALL_RETURN(2, ok);
}

static void FindFirstFileA(Cpu *c)
{
    char name[260], path[600];
    v3_read_string(ARG(0), name, sizeof name);
    v3_host_path(name, path, sizeof path);
    struct stat st;
    const int found = strchr(path, '*') == NULL && stat(path, &st) == 0;
    v3_log("FindFirstFileA(%s) -> %s", name, found ? "found" : "none");
    if (!found)
    {
        set_error(2);
        STDCALL_RETURN(2, 0xffffffffu);
    }
    const uint32_t data = ARG(1);
    memset(MEM(data), 0, 320);
    v3_w32(data, S_ISDIR(st.st_mode) ? 0x10 : 0x80);
    v3_w32(data + 32, (uint32_t)st.st_size);
    const char *base = strrchr(name, '\\');
    v3_write_string(data + 44, base ? base + 1 : name, 260);
    STDCALL_RETURN(2, v3_handle_new(V3_HANDLE_FIND, NULL));
}

static void FindClose(Cpu *c)
{
    v3_handle_close(ARG(0));
    STDCALL_RETURN(1, 1);
}

/* --- Vertrix 2 v1.2's Watcom runtime -------------------------------------------------------- */

static void GetCommandLineW(Cpu *c)
{
    STDCALL_RETURN(0, command_line_w);
}

static void GetModuleFileNameW(Cpu *c)
{
    char path[260];
    snprintf(path, sizeof path, "%s\\%s", v3_game_directory, v3_executable);
    const uint32_t out = ARG(1), size = ARG(2);
    uint32_t n = (uint32_t)strlen(path);
    if (n >= size)
    {
        n = size ? size - 1 : 0;
    }
    for (uint32_t i = 0; i < n; ++i)
    {
        v3_w16(out + 2 * i, (uint8_t)path[i]);
    }
    if (size)
    {
        v3_w16(out + 2 * n, 0);
    }
    STDCALL_RETURN(3, n);
}

/* A pseudo handle, as Windows returns. */
static void GetCurrentThread(Cpu *c)
{
    STDCALL_RETURN(0, 0xfffffffeu);
}

static void GetProcessVersion(Cpu *c)
{
    STDCALL_RETURN(1, 0x00040000u);
}

/* The host's clock as local time, in a SYSTEMTIME. */
static void put_system_time(uint32_t at, uint64_t filetime)
{
    const time_t seconds = (time_t)(filetime / 10000000u - 11644473600ull);
    struct tm tm;
#ifdef GEKKO
    tm = *gmtime(&seconds);
#else
    gmtime_r(&seconds, &tm);
#endif
    v3_w16(at + 0, (uint16_t)(tm.tm_year + 1900));
    v3_w16(at + 2, (uint16_t)(tm.tm_mon + 1));
    v3_w16(at + 4, (uint16_t)tm.tm_wday);
    v3_w16(at + 6, (uint16_t)tm.tm_mday);
    v3_w16(at + 8, (uint16_t)tm.tm_hour);
    v3_w16(at + 10, (uint16_t)tm.tm_min);
    v3_w16(at + 12, (uint16_t)tm.tm_sec);
    v3_w16(at + 14, (uint16_t)(filetime / 10000u % 1000u));
}

static uint64_t now_filetime(void)
{
    return 128882016000000000ull + v3_microseconds() * 10u;
}

static void GetLocalTime(Cpu *c)
{
    put_system_time(ARG(0), now_filetime());
    STDCALL_RETURN(1, 0);
}

static void FileTimeToSystemTime(Cpu *c)
{
    put_system_time(ARG(1), v3_r64(ARG(0)));
    STDCALL_RETURN(2, 1);
}

/* Local time is UTC (no zone). */
static void FileTimeToLocalFileTime(Cpu *c)
{
    v3_w64(ARG(1), v3_r64(ARG(0)));
    STDCALL_RETURN(2, 1);
}

static void LocalFileTimeToFileTime(Cpu *c)
{
    v3_w64(ARG(1), v3_r64(ARG(0)));
    STDCALL_RETURN(2, 1);
}

static void GetTimeZoneInformation(Cpu *c)
{
    memset(MEM(ARG(0)), 0, 172);
    STDCALL_RETURN(1, 0); /* TIME_ZONE_ID_UNKNOWN */
}

static void GetVolumeInformationA(Cpu *c)
{
    if (ARG(1))
    {
        v3_write_string(ARG(1), "VERTRIX", ARG(2));
    }
    if (ARG(3))
    {
        v3_w32(ARG(3), 0x12345678u);
    }
    if (ARG(4))
    {
        v3_w32(ARG(4), 255);
    }
    if (ARG(5))
    {
        v3_w32(ARG(5), 0x3);
    }
    if (ARG(6))
    {
        v3_write_string(ARG(6), "FAT32", ARG(7));
    }
    STDCALL_RETURN(8, 1);
}

/* Global and local memory: a handle is the block's address. */
static void GlobalHandle(Cpu *c)
{
    STDCALL_RETURN(1, ARG(0));
}

static void GlobalReAlloc(Cpu *c)
{
    const uint32_t old = ARG(0), size = ARG(1);
    const uint32_t old_size = v3_alloc_size(old);
    const uint32_t p = v3_realloc(old, size);
    if (p && size > old_size && (ARG(2) & 0x40)) /* GMEM_ZEROINIT */
    {
        memset(MEM(p + old_size), 0, size - old_size);
    }
    STDCALL_RETURN(3, p);
}

static void GlobalFlags(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void LocalAlloc(Cpu *c)
{
    const uint32_t p = v3_alloc(ARG(1));
    if (p && (ARG(0) & 0x40)) /* LMEM_ZEROINIT */
    {
        memset(MEM(p), 0, ARG(1));
    }
    STDCALL_RETURN(2, p);
}

static void LocalReAlloc(Cpu *c)
{
    const uint32_t old = ARG(0), size = ARG(1);
    const uint32_t old_size = v3_alloc_size(old);
    const uint32_t p = v3_realloc(old, size);
    if (p && size > old_size && (ARG(2) & 0x40))
    {
        memset(MEM(p + old_size), 0, size - old_size);
    }
    STDCALL_RETURN(3, p);
}

/* a * b / c, rounded half away from zero, as Windows does; -1 for c = 0. */
static void MulDiv(Cpu *c)
{
    const int64_t product = (int64_t)(int32_t)ARG(0) * (int32_t)ARG(1);
    const int64_t divisor = (int32_t)ARG(2);
    if (divisor == 0)
    {
        STDCALL_RETURN(3, 0xffffffffu);
    }
    const int64_t a = product < 0 ? -product : product, b = divisor < 0 ? -divisor : divisor;
    const int64_t q = (a + b / 2) / b;
    STDCALL_RETURN(3, (uint32_t)(int32_t)((product < 0) != (divisor < 0) ? -q : q));
}

static void IsDBCSLeadByte(Cpu *c)
{
    STDCALL_RETURN(1, 0);
}

static void GetThreadLocale(Cpu *c)
{
    STDCALL_RETURN(0, 0x0409);
}

static void lstrlenA(Cpu *c)
{
    STDCALL_RETURN(1, ARG(0) ? v3_string_length(ARG(0)) : 0);
}

static void lstrcpyA(Cpu *c)
{
    const uint32_t n = v3_string_length(ARG(1));
    memmove(MEM(ARG(0)), MEM(ARG(1)), n + 1);
    STDCALL_RETURN(2, ARG(0));
}

static void lstrcpynA(Cpu *c)
{
    const uint32_t out = ARG(0), in = ARG(1), size = ARG(2);
    uint32_t i = 0;
    for (; i + 1 < size; ++i)
    {
        const uint8_t ch = v3_r8(in + i);
        if (!ch)
        {
            break;
        }
        v3_w8(out + i, ch);
    }
    if (size)
    {
        v3_w8(out + i, 0);
    }
    STDCALL_RETURN(3, out);
}

static void lstrcatA(Cpu *c)
{
    const uint32_t at = ARG(0) + v3_string_length(ARG(0));
    const uint32_t n = v3_string_length(ARG(1));
    memmove(MEM(at), MEM(ARG(1)), n + 1);
    STDCALL_RETURN(2, ARG(0));
}

static void lstrcmpA(Cpu *c)
{
    char a[1024], b[1024];
    v3_read_string(ARG(0), a, sizeof a);
    v3_read_string(ARG(1), b, sizeof b);
    const int r = strcmp(a, b);
    STDCALL_RETURN(2, (uint32_t)(r < 0 ? -1 : r > 0));
}

static void lstrcmpiA(Cpu *c)
{
    char a[1024], b[1024];
    v3_read_string(ARG(0), a, sizeof a);
    v3_read_string(ARG(1), b, sizeof b);
    const int r = strcasecmp(a, b);
    STDCALL_RETURN(2, (uint32_t)(r < 0 ? -1 : r > 0));
}

const V3Export v3_kernel32[] = {
#define E(name) {#name, name}
    E(GetCurrentProcess), E(SetPriorityClass), E(Sleep), E(ResetEvent), E(WaitForMultipleObjects),
    E(MultiByteToWideChar), E(WideCharToMultiByte), E(SetEvent), E(TerminateProcess),
    E(UnhandledExceptionFilter), E(SetUnhandledExceptionFilter), E(IsDebuggerPresent),
    E(GetDriveTypeA), E(GetLastError), E(GetFullPathNameA), E(WriteFile), E(GetConsoleCP),
    E(GetConsoleMode), E(GetCommandLineA), E(GetStartupInfoA), E(HeapFree), E(HeapAlloc),
    E(RaiseException), E(GetCPInfo), E(InterlockedIncrement), E(InterlockedDecrement), E(GetACP),
    E(GetOEMCP), E(IsValidCodePage), E(GetModuleHandleW), E(GetProcAddress), E(TlsGetValue),
    E(TlsAlloc), E(TlsSetValue), E(TlsFree), E(SetLastError), E(GetCurrentThreadId),
    E(LCMapStringA), E(LCMapStringW), E(HeapSize), E(ExitProcess), E(GetCurrentDirectoryA),
    E(DeleteCriticalSection), E(GetConsoleOutputCP), E(WriteConsoleW),
    E(InitializeCriticalSection), E(SetHandleCount), E(GetStdHandle), E(GetFileType),
    E(SetStdHandle), E(CreateFileA), E(GetModuleFileNameA), E(GetEnvironmentStrings),
    E(GetEnvironmentStringsW), E(HeapCreate), E(VirtualFree), E(QueryPerformanceCounter),
    E(GetTickCount), E(GetCurrentProcessId), E(GetSystemTimeAsFileTime), E(VirtualAlloc),
    E(HeapReAlloc), E(RtlUnwind), E(GetStringTypeA), E(GetStringTypeW), E(GetUserDefaultLCID),
    E(GetLocaleInfoA), E(EnumSystemLocalesA), E(IsValidLocale), E(FreeLibrary), E(LoadLibraryA),
    E(InitializeCriticalSectionAndSpinCount), E(ReadFile), E(GetLocaleInfoW), E(FlushFileBuffers),
    E(VirtualQuery), E(CompareStringW), E(SetEnvironmentVariableA), E(CreateMutexA),
    E(GetModuleHandleA), E(IsProcessorFeaturePresent), E(GetSystemInfo), E(CloseHandle),
    E(WaitForSingleObject), E(CreateEventA), E(LeaveCriticalSection), E(EnterCriticalSection),
    E(SetFilePointer), E(OutputDebugStringA), E(WriteConsoleA), E(CompareStringA), E(GlobalFree),
    E(GlobalUnlock), E(GlobalLock), E(GlobalAlloc), E(SetThreadPriority), E(CreateThread),
    E(SetErrorMode), E(FormatMessageA), E(LocalFree), E(CreateDirectoryA), E(GetFileSize),
    E(FindFirstFileA), E(FindClose), E(GetVersion),
    E(GetCommandLineW), E(GetModuleFileNameW), E(GetCurrentThread), E(GetProcessVersion),
    E(GetLocalTime), E(FileTimeToSystemTime), E(FileTimeToLocalFileTime),
    E(LocalFileTimeToFileTime), E(GetTimeZoneInformation), E(GetVolumeInformationA),
    E(GlobalHandle), E(GlobalReAlloc), E(GlobalFlags), E(LocalAlloc), E(LocalReAlloc), E(MulDiv),
    E(IsDBCSLeadByte), E(GetThreadLocale), E(lstrlenA), E(lstrcpyA), E(lstrcpynA), E(lstrcatA),
    E(lstrcmpA), E(lstrcmpiA),
    {"FreeEnvironmentStringsA", FreeEnvironmentStringsA},
    {"FreeEnvironmentStringsW", FreeEnvironmentStringsA},
#undef E
    {NULL, NULL}};
