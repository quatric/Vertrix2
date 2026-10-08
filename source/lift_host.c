#include "lift_host.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lift_imports.h"

#include "lift_runtime.h"

/* Set by the Wii driver to list the files the original opens. */
int lift_host_trace_files;
#include "palette_tables.h"
#include "rtl_double_add.h"
#include "rtl_double_multiply.h"
#include "rtl_float.h"
#include "rtl_single_divide.h"
#include "rtl_single_multiply.h"

static int in_image(uint32_t address, unsigned size)
{
    return address >= LIFT_HOST_IMAGE_BASE &&
           (uint64_t)address + size <= (uint64_t)LIFT_HOST_IMAGE_BASE + LIFT_HOST_IMAGE_SIZE;
}

static int in_heap(const LiftHost *host, uint32_t address, unsigned size)
{
    return address >= LIFT_HOST_HEAP_BASE &&
           (uint64_t)address + size <= (uint64_t)LIFT_HOST_HEAP_BASE + host->heap_top;
}

static uint8_t *bytes_at(const LiftHost *host, uint32_t address, unsigned size)
{
    if (in_image(address, size))
    {
        return host->image + (address - LIFT_HOST_IMAGE_BASE);
    }
    if (in_heap(host, address, size))
    {
        return host->heap + (address - LIFT_HOST_HEAP_BASE);
    }
    {
        unsigned frame = vertrix_lifted_depth();
        while (frame-- > 0)
        {
            const LiftEnv *env = frame < LIFT_FRAME_LIMIT ? vertrix_lift_frames[frame] : NULL;
            if (env != NULL && lift_in_stack(env, address, size))
            {
                return env->stack + (address - env->low);
            }
        }
    }
    return NULL;
}

uint32_t lift_host_read(const LiftHost *host, uint32_t address, unsigned size)
{
    const uint8_t *bytes = bytes_at(host, address, size);
    uint32_t value = 0;
    unsigned i;
    for (i = 0; bytes != NULL && i < size; i++)
    {
        value |= (uint32_t)bytes[i] << (8 * i);
    }
    return value;
}

static uint32_t host_read(uint32_t address, void *context)
{
    return lift_host_read(context, address, 4);
}

static void host_write(LiftHost *host, uint32_t address, unsigned size, uint32_t value)
{
    uint8_t *bytes = bytes_at(host, address, size);
    unsigned i;
    for (i = 0; bytes != NULL && i < size; i++)
    {
        bytes[i] = (uint8_t)(value >> (8 * i));
    }
}

static int host_resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    LiftHost *host = context;
    if (!in_heap(host, handle, 1))
    {
        return 0;
    }
    *storage = host->heap + (handle - LIFT_HOST_HEAP_BASE);
    *size = host->heap_top - (handle - LIFT_HOST_HEAP_BASE);
    return 1;
}

static uint32_t host_allocate(uint32_t size, void *context)
{
    LiftHost *host = context;
    uint32_t address = LIFT_HOST_HEAP_BASE + host->heap_top;
    uint32_t rounded = (size + 15u) & ~15u;
    if (rounded > host->heap_size - host->heap_top)
    {
        return 0;
    }
    memset(host->heap + host->heap_top, 0, rounded);
    host->heap_top += rounded;
    return address;
}

static void host_write(LiftHost *host, uint32_t address, unsigned size, uint32_t value);

/* Move (0x4e1140): eax = destination, edx = source, ebx = byte count; overlap-safe. */
static void host_move(LiftHost *host, uint32_t destination, uint32_t source, uint32_t count)
{
    uint8_t *to = bytes_at(host, destination, count);
    uint8_t *from = bytes_at(host, source, count);
    if (to != NULL && from != NULL && count != 0)
    {
        memmove(to, from, count);
    }
}

/* TList insert (0x4d88a0): eax = list, edx = index, ecx = number of slots, ebx = the value stored
 * in each new slot. A list is { +4 items, +8 count, +0xc capacity }; 0x4d8770 resizes it. */
static void host_list_insert(LiftHost *host, uint32_t list, uint32_t index, uint32_t count,
                             uint32_t value)
{
    VertrixCallSite resize;
    uint32_t old = lift_host_read(host, list + 8, 4);
    uint32_t items;
    uint32_t i;
    memset(&resize, 0, sizeof resize);
    resize.target = 0x4d8770;
    resize.eax = list;
    resize.edx = (index >= old ? index : old) + count;
    resize.ebx = 0xffffffffu;
    host->calls.calls.call(&resize, host->calls.calls.context);
    items = lift_host_read(host, list + 4, 4);
    if (index < old)
    {
        host_move(host, items + (index + count) * 4, items + index * 4, (old - index) * 4);
        if (count != 0 && bytes_at(host, items + index * 4, count * 4) != NULL)
        {
            memset(bytes_at(host, items + index * 4, count * 4), 0, count * 4);
        }
    }
    for (i = 0; i < count; i++)
    {
        host_write(host, items + (index + i) * 4, 4, value);
    }
}

uint32_t lift_host_allocate(LiftHost *host, uint32_t size)
{
    return host_allocate(size, host);
}

enum
{
    LIFT_COM_BASE = 0xe0000000u,
    COM_DRAW = 1,
    COM_SURFACE = 2
};

static uint32_t host_com_object(LiftHost *host, unsigned interface_id);

static uint32_t site_argument(const VertrixCallSite *site, unsigned index)
{
    return index == 0   ? site->stack
           : index == 1 ? site->stack_next
           : index == 2 ? site->stack_third
                        : site->stack_rest[index - 3];
}

static uint32_t host_string_length(LiftHost *host, uint32_t address)
{
    uint32_t length = 0;
    while (bytes_at(host, address + length, 1) != NULL && *bytes_at(host, address + length, 1) != 0)
    {
        length++;
    }
    return length;
}

/* Look a path up in the archive: drops a leading ".\\" or drive, folds separators. */
static int host_find_file(LiftHost *host, uint32_t name, uint32_t *index)
{
    char text[300];
    unsigned length = 0;
    const char *start = text;
    if (host->archive == NULL)
    {
        return 0;
    }
    while (length < sizeof text - 1 && lift_host_read(host, name + length, 1) != 0)
    {
        text[length] = (char)lift_host_read(host, name + length, 1);
        length++;
    }
    text[length] = 0;
    {
        int found = vertrix_vf_find(host->archive, start, index);
        if (lift_host_trace_files || getenv("TRACE_FILES"))
        {
            printf("file %s -> %d\n", text, found);
        }
        return found;
    }
}

/* The Win32 imports the original's runtime reaches, served on the host. Returns 1 and the result
 * in *result when the import is implemented. Arguments are the stdcall stack dwords. */
static int host_import(LiftHost *host, const VertrixCallSite *site, const char *name,
                       uint32_t *result)
{
    uint32_t a0 = site_argument(site, 0), a1 = site_argument(site, 1), a2 = site_argument(site, 2);
    if (getenv("TRACE_IMPORTS"))
    {
        printf("import %s(%x, %x, %x)\n", name, (unsigned)a0, (unsigned)a1, (unsigned)a2);
    }
    if (strcmp(name, "timeSetEvent") == 0) /* (delay, resolution, proc, user, flags) */
    {
        host->timer_period = a0;
        host->timer_proc = a2;
        host->timer_user = site_argument(site, 3);
        *result = 1;
    }
    else if (strcmp(name, "CoCreateInstance") == 0) /* (clsid, outer, context, iid, out): no COM classes */
    {
        host_write(host, site_argument(site, 4), 4, 0);
        *result = 0x80040154u; /* REGDB_E_CLASSNOTREG */
    }
    else if (strcmp(name, "DirectInput8Create") == 0) /* (instance, version, iid, out, outer) */
    {
        host_write(host, site_argument(site, 3), 4, 0);
        *result = 0x80004002u; /* E_NOINTERFACE: no input device layer yet */
    }
    else if (strcmp(name, "CoInitialize") == 0 || strcmp(name, "CoUninitialize") == 0 ||
             strcmp(name, "CoInitializeEx") == 0)
    {
        *result = 0;
    }
    else if (strcmp(name, "timeGetTime") == 0 || strcmp(name, "GetTickCount") == 0)
    {
        *result = host->clock_ms;
        host->clock_ms += 1; /* a routine that waits on the clock sees it move */
    }
    else if (strcmp(name, "lstrlenA") == 0)
    {
        *result = host_string_length(host, a0);
    }
    else if (strcmp(name, "lstrcpynA") == 0 || strcmp(name, "lstrcpyA") == 0)
    {
        uint32_t length = host_string_length(host, a1);
        uint32_t limit = strcmp(name, "lstrcpynA") == 0 ? (a2 == 0 ? 0 : a2 - 1) : length;
        uint32_t i;
        if (limit > length)
        {
            limit = length;
        }
        for (i = 0; i < limit; i++)
        {
            host_write(host, a0 + i, 1, lift_host_read(host, a1 + i, 1));
        }
        if (strcmp(name, "lstrcpynA") != 0 || a2 != 0)
        {
            host_write(host, a0 + limit, 1, 0);
        }
        *result = a0;
    }
    else if (strcmp(name, "InterlockedDecrement") == 0 || strcmp(name, "InterlockedIncrement") == 0)
    {
        *result = lift_host_read(host, a0, 4) + (name[11] == 'D' ? 0xffffffffu : 1u);
        host_write(host, a0, 4, *result);
    }
    else if (strcmp(name, "InterlockedExchange") == 0)
    {
        *result = lift_host_read(host, a0, 4);
        host_write(host, a0, 4, a1);
    }
    else if (strcmp(name, "GlobalAlloc") == 0 || strcmp(name, "LocalAlloc") == 0)
    {
        *result = host_allocate(a1, host);
    }
    else if (strcmp(name, "GlobalLock") == 0 || strcmp(name, "GlobalHandle") == 0 ||
             strcmp(name, "GlobalReAlloc") == 0)
    {
        *result = a0;
    }
    else if (strcmp(name, "DirectDrawCreateEx") == 0) /* (guid, out, iid, outer) */
    {
        uint32_t device = host_com_object(host, COM_DRAW);
        host_write(host, a1, 4, device);
        *result = device == 0 ? 0x8007000eu : 0;
    }
    else if (strcmp(name, "GetFullPathNameA") == 0) /* (name, size, buffer, file part) */
    {
        uint32_t length = host_string_length(host, a0), i;
        for (i = 0; i <= length && i < a1; i++)
        {
            host_write(host, a2 + i, 1, lift_host_read(host, a0 + i, 1));
        }
        *result = length;
    }
    else if (strcmp(name, "TlsAlloc") == 0)
    {
        *result = host->tls_count < 64 ? host->tls_count++ : 0xffffffffu;
    }
    else if (strcmp(name, "TlsGetValue") == 0)
    {
        *result = a0 < 64 ? host->tls[a0] : 0;
    }
    else if (strcmp(name, "TlsSetValue") == 0)
    {
        if (a0 < 64)
        {
            host->tls[a0] = a1;
        }
        *result = a0 < 64;
    }
    else if (strcmp(name, "TlsFree") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "FileTimeToLocalFileTime") == 0)
    {
        host_write(host, a1, 4, lift_host_read(host, a0, 4));
        host_write(host, a1 + 4, 4, lift_host_read(host, a0 + 4, 4));
        *result = 1;
    }
    else if (strcmp(name, "FileTimeToSystemTime") == 0)
    {
        uint32_t i;
        for (i = 0; i < 16; i += 4)
        {
            host_write(host, a1 + i, 4, 0);
        }
        host_write(host, a1, 2, 2004);
        host_write(host, a1 + 2, 2, 1);
        host_write(host, a1 + 6, 2, 1);
        *result = 1;
    }
    else if (strcmp(name, "GetTimeZoneInformation") == 0)
    {
        uint32_t i;
        for (i = 0; i < 172; i += 4)
        {
            host_write(host, a0 + i, 4, 0);
        }
        *result = 0; /* TIME_ZONE_ID_UNKNOWN, UTC */
    }
    else if (strcmp(name, "GetStringTypeA") == 0) /* (locale, type, text, count, out) */
    {
        uint32_t count = site_argument(site, 3), out = site_argument(site, 4), i;
        if (count == 0xffffffffu)
        {
            count = host_string_length(host, a2) + 1;
        }
        for (i = 0; i < count; i++)
        {
            int c = (int)lift_host_read(host, a2 + i, 1);
            uint32_t bits = 0;
            bits |= isupper(c) ? 1 : 0;
            bits |= islower(c) ? 2 : 0;
            bits |= isdigit(c) ? 4 : 0;
            bits |= isspace(c) ? 8 : 0;
            bits |= ispunct(c) ? 0x10 : 0;
            bits |= iscntrl(c) ? 0x20 : 0;
            bits |= (c == ' ' || c == '\t') ? 0x40 : 0;
            bits |= isxdigit(c) ? 0x80 : 0;
            bits |= isalpha(c) ? 0x100 : 0;
            host_write(host, out + 2 * i, 2, bits);
        }
        *result = 1;
    }
    else if (strcmp(name, "LoadLibraryA") == 0)
    {
        *result = 0x70000000u; /* a library handle; GetProcAddress is not served */
    }
    else if (strcmp(name, "FreeLibrary") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "CharUpperA") == 0)
    {
        if (a0 < 0x10000u)
        {
            *result = a0 >= 'a' && a0 <= 'z' ? a0 - 32 : a0;
        }
        else
        {
            uint32_t i;
            for (i = 0; lift_host_read(host, a0 + i, 1) != 0; i++)
            {
                uint32_t c = lift_host_read(host, a0 + i, 1);
                host_write(host, a0 + i, 1, c >= 'a' && c <= 'z' ? c - 32 : c);
            }
            *result = a0;
        }
    }
    else if (strcmp(name, "FindFirstFileA") == 0) /* (name, find data) */
    {
        uint32_t index, size, i, length;
        if (!host_find_file(host, a0, &index) || !vertrix_vf_size(host->archive, index, &size))
        {
            *result = 0xffffffffu;
            return 1;
        }
        for (i = 0; i < 320; i += 4)
        {
            host_write(host, a1 + i, 4, 0);
        }
        host_write(host, a1, 4, 0x80);
        host_write(host, a1 + 32, 4, size);
        length = host_string_length(host, a0);
        for (i = 0; i < length && i < 259; i++)
        {
            host_write(host, a1 + 44 + i, 1, lift_host_read(host, a0 + i, 1));
        }
        *result = 0x1001;
    }
    else if (strcmp(name, "FindClose") == 0)
    {
        *result = 1;
    }
    else if (strcmp(name, "CreateFileA") == 0)
    {
        uint32_t index, size;
        unsigned slot;
        *result = 0xffffffffu;
        if (host_find_file(host, a0, &index) && vertrix_vf_size(host->archive, index, &size))
        {
            for (slot = 0; slot < 16; slot++)
            {
                if (!host->files[slot].open)
                {
                    host->files[slot].open = 1;
                    host->files[slot].index = index;
                    host->files[slot].position = 0;
                    host->files[slot].size = size;
                    *result = 0x100 + slot;
                    break;
                }
            }
        }
    }
    else if (strcmp(name, "ReadFile") == 0) /* (handle, buffer, count, read*, overlapped) */
    {
        unsigned slot = a0 - 0x100;
        uint32_t count = a2, available;
        uint8_t *to =
            a0 >= 0x100 && slot < 16 && host->files[slot].open ? bytes_at(host, a1, count) : NULL;
        *result = 0;
        if (to != NULL || count == 0)
        {
            available = host->files[slot].size - host->files[slot].position;
            if (count > available)
            {
                count = available;
            }
            if (count == 0 || vertrix_vf_read(host->archive, host->files[slot].index,
                                              host->files[slot].position, to, count))
            {
                host->files[slot].position += count;
                if (site_argument(site, 3) != 0)
                {
                    host_write(host, site_argument(site, 3), 4, count);
                }
                *result = 1;
            }
        }
    }
    else if (strcmp(name, "SetFilePointer") == 0) /* (handle, distance, high*, method) */
    {
        unsigned slot = a0 - 0x100;
        uint32_t method = site_argument(site, 3);
        *result = 0xffffffffu;
        if (a0 >= 0x100 && slot < 16 && host->files[slot].open)
        {
            uint32_t base = method == 0   ? 0
                            : method == 1 ? host->files[slot].position
                                          : host->files[slot].size;
            host->files[slot].position = base + a1;
            *result = host->files[slot].position;
        }
    }
    else if (strcmp(name, "GetFileSize") == 0)
    {
        unsigned slot = a0 - 0x100;
        *result = a0 >= 0x100 && slot < 16 && host->files[slot].open ? host->files[slot].size
                                                                     : 0xffffffffu;
        if (a1 != 0)
        {
            host_write(host, a1, 4, 0);
        }
    }
    else if (strcmp(name, "CloseHandle") == 0)
    {
        unsigned slot = a0 - 0x100;
        if (a0 >= 0x100 && slot < 16)
        {
            host->files[slot].open = 0;
        }
        *result = 1;
    }
    else if (strcmp(name, "GetVolumeInformationA") == 0) /* (root, name, size, serial, ...) */
    {
        uint32_t serial = site_argument(site, 3), length = site_argument(site, 4),
                 flags = site_argument(site, 5);
        if (a1 != 0)
        {
            host_write(host, a1, 1, 0);
        }
        if (serial != 0)
        {
            host_write(host, serial, 4, 0x1234abcdu);
        }
        if (length != 0)
        {
            host_write(host, length, 4, 255);
        }
        if (flags != 0)
        {
            host_write(host, flags, 4, 0);
        }
        *result = 1;
    }
    else if (strcmp(name, "GetVersion") == 0)
    {
        *result = 0x0a280005u; /* Windows XP style: major 5, minor 1 packs as 0x0a280105 */
    }
    else if (strcmp(name, "GlobalFree") == 0 || strcmp(name, "LocalFree") == 0 ||
             strcmp(name, "GlobalUnlock") == 0 || strcmp(name, "InitializeCriticalSection") == 0 ||
             strcmp(name, "DeleteCriticalSection") == 0 ||
             strcmp(name, "EnterCriticalSection") == 0 ||
             strcmp(name, "LeaveCriticalSection") == 0 || strcmp(name, "SetLastError") == 0 ||
             strcmp(name, "GetLastError") == 0)
    {
        *result = 0;
    }
    else
    {
        return 0;
    }
    return 1;
}

/* ---- DirectDraw emulation -------------------------------------------------------------------
 * COM objects are heap blocks { +0 vtable, +4 pixels, +8 width, +12 height, +16 pitch, +20 bytes
 * per pixel }; a vtable entry is the fake address LIFT_COM_BASE + interface * 0x100 + index, which
 * lands on the boundary where host_com serves it. Interfaces: 1 IDirectDraw7, 2 surface. */
static uint32_t host_com_object(LiftHost *host, unsigned interface_id)
{
    uint32_t object = host_allocate(32, host);
    uint32_t table = host_allocate(0x100 * 4, host);
    uint32_t i;
    for (i = 0; object != 0 && table != 0 && i < 0x40; i++)
    {
        host_write(host, table + 4 * i, 4, LIFT_COM_BASE + interface_id * 0x100 + i);
    }
    if (object != 0)
    {
        host_write(host, object, 4, table);
    }
    return object;
}

uint32_t lift_host_surface(const LiftHost *host, uint32_t surface, uint32_t *width,
                           uint32_t *height, uint32_t *pitch, uint32_t *bytes_per_pixel)
{
    if (surface == 0)
    {
        return 0;
    }
    *width = lift_host_read(host, surface + 8, 4);
    *height = lift_host_read(host, surface + 12, 4);
    *pitch = lift_host_read(host, surface + 16, 4);
    *bytes_per_pixel = lift_host_read(host, surface + 20, 4);
    return lift_host_read(host, surface + 4, 4);
}

static uint32_t host_create_surface(LiftHost *host, uint32_t desc, uint32_t out)
{
    uint32_t flags = lift_host_read(host, desc + 4, 4);
    uint32_t height = (flags & 2) ? lift_host_read(host, desc + 8, 4) : host->display_height;
    uint32_t width = (flags & 4) ? lift_host_read(host, desc + 12, 4) : host->display_width;
    uint32_t bits = (flags & 0x1000) ? lift_host_read(host, desc + 84, 4) : host->display_bits;
    uint32_t caps = lift_host_read(host, desc + 104, 4);
    uint32_t surface = host_com_object(host, COM_SURFACE);
    uint32_t pixels;
    if (bits == 0)
    {
        bits = 32;
    }
    if ((caps & 0x200) != 0 && width == 0)
    {
        width = 640;
        height = 480;
    }
    if (width == 0 || height == 0)
    {
        width = 640;
        height = 480;
    }
    pixels = host_allocate(width * height * (bits / 8), host);
    if (surface == 0 || pixels == 0)
    {
        return 0x8007000e; /* E_OUTOFMEMORY */
    }
    host_write(host, surface + 4, 4, pixels);
    host_write(host, surface + 8, 4, width);
    host_write(host, surface + 12, 4, height);
    host_write(host, surface + 16, 4, width * (bits / 8));
    host_write(host, surface + 20, 4, bits / 8);
    if ((caps & 0x200) != 0)
    {
        host->primary_surface = surface;
    }
    host_write(host, out, 4, surface);
    return 0;
}

/* Copy a rectangle between emulated surfaces of the same pixel size; a zero rectangle pointer is
 * the whole surface. Clipped to both. */
static void host_surface_copy(LiftHost *host, uint32_t target, uint32_t tx, uint32_t ty,
                              uint32_t source, uint32_t rect)
{
    uint32_t sw, sh, sp, sb, tw, th, tp, tb;
    uint32_t spixels = lift_host_surface(host, source, &sw, &sh, &sp, &sb);
    uint32_t tpixels = lift_host_surface(host, target, &tw, &th, &tp, &tb);
    int32_t left = 0, top = 0, right = (int32_t)sw, bottom = (int32_t)sh, x, y;
    if (spixels == 0 || tpixels == 0 || sb != tb || sb == 0)
    {
        return;
    }
    if (rect != 0)
    {
        left = (int32_t)lift_host_read(host, rect, 4);
        top = (int32_t)lift_host_read(host, rect + 4, 4);
        right = (int32_t)lift_host_read(host, rect + 8, 4);
        bottom = (int32_t)lift_host_read(host, rect + 12, 4);
    }
    for (y = top; y < bottom; y++)
    {
        int32_t dy = (int32_t)ty + (y - top);
        if (y < 0 || y >= (int32_t)sh || dy < 0 || dy >= (int32_t)th)
        {
            continue;
        }
        for (x = left; x < right; x++)
        {
            int32_t dx = (int32_t)tx + (x - left);
            uint32_t i;
            if (x < 0 || x >= (int32_t)sw || dx < 0 || dx >= (int32_t)tw)
            {
                continue;
            }
            for (i = 0; i < sb; i++)
            {
                host_write(host, tpixels + dy * tp + dx * tb + i, 1,
                           lift_host_read(host, spixels + y * sp + x * sb + i, 1));
            }
        }
    }
}

static uint32_t host_com(LiftHost *host, unsigned interface_id, unsigned index,
                         const VertrixCallSite *site)
{
    uint32_t this_ = site_argument(site, 0);
    if (getenv("TRACE_IMPORTS"))
    {
        printf("com %s[%u](%x, %x, %x)\n", interface_id == COM_DRAW ? "DirectDraw" : "Surface",
               index, (unsigned)this_, (unsigned)site_argument(site, 1),
               (unsigned)site_argument(site, 2));
    }
    if (interface_id == COM_DRAW)
    {
        if (index == 6) /* CreateSurface(this, desc, out, outer) */
        {
            return host_create_surface(host, site_argument(site, 1), site_argument(site, 2));
        }
        if (index == 21) /* SetDisplayMode(this, width, height, bits, ...) */
        {
            host->display_width = site_argument(site, 1);
            host->display_height = site_argument(site, 2);
            host->display_bits = site_argument(site, 3);
        }
        return 0; /* QueryInterface, SetCooperativeLevel and the rest report DD_OK */
    }
    if (interface_id == COM_SURFACE)
    {
        uint32_t pixels = lift_host_read(host, this_ + 4, 4);
        if (index == 12) /* GetAttachedSurface(this, caps, out): the back buffer, same size */
        {
            uint32_t back = host_com_object(host, COM_SURFACE);
            uint32_t bytes = lift_host_read(host, this_ + 20, 4);
            uint32_t width = lift_host_read(host, this_ + 8, 4);
            uint32_t height = lift_host_read(host, this_ + 12, 4);
            uint32_t memory = host_allocate(width * height * bytes, host);
            if (back == 0 || memory == 0)
            {
                return 0x8007000e;
            }
            host_write(host, back + 4, 4, memory);
            host_write(host, back + 8, 4, width);
            host_write(host, back + 12, 4, height);
            host_write(host, back + 16, 4, width * bytes);
            host_write(host, back + 20, 4, bytes);
            host_write(host, site_argument(site, 2), 4, back);
            if (this_ == host->primary_surface)
            {
                host->back_surface = back;
            }
            return 0;
        }
        if (index == 5) /* Blt(this, target rect, source, source rect, flags, effects) */
        {
            uint32_t target_rect = site_argument(site, 1);
            host_surface_copy(host, this_,
                              target_rect != 0 ? lift_host_read(host, target_rect, 4) : 0,
                              target_rect != 0 ? lift_host_read(host, target_rect + 4, 4) : 0,
                              site_argument(site, 2), site_argument(site, 3));
            return 0;
        }
        if (index == 7) /* BltFast(this, x, y, source, source rect, flags) */
        {
            host_surface_copy(host, this_, site_argument(site, 1), site_argument(site, 2),
                              site_argument(site, 3), site_argument(site, 4));
            return 0;
        }
        if (index == 11) /* Flip: the back buffer becomes what the primary shows */
        {
            if (host->primary_surface == this_)
            {
                host_surface_copy(host, this_, 0, 0, host->back_surface, 0);
            }
            host->frames_presented++;
            return 0;
        }
        if (index == 25) /* Lock(this, rect, desc, flags, event) */
        {
            uint32_t desc = site_argument(site, 2);
            host_write(host, desc + 4, 4, 0x100f | 0x1000);
            host_write(host, desc + 8, 4, lift_host_read(host, this_ + 12, 4));
            host_write(host, desc + 12, 4, lift_host_read(host, this_ + 8, 4));
            host_write(host, desc + 16, 4, lift_host_read(host, this_ + 16, 4));
            host_write(host, desc + 36, 4, pixels);
            host_write(host, desc + 84, 4, 8 * lift_host_read(host, this_ + 20, 4));
        }
        return 0; /* Unlock, Blt, GetFlipStatus, Restore, Release... report DD_OK */
    }
    return 0;
}

typedef struct
{
    LiftHost *host;
    int cache_published;
} HostSingleContext;

static void host_single_publish(HostSingleContext *context, const VertrixRtlFloatState *state)
{
    if (!context->cache_published)
    {
        host_write(context->host, 0x503ea0, 4, state->helper);
        host_write(context->host, 0x503ea4, 4, state->multiply);
        host_write(context->host, 0x503ea8, 4, state->divide);
        context->cache_published = 1;
    }
}

static void host_single_refresh(VertrixRtlFloatState *state, LiftHost *host)
{
    state->helper = lift_host_read(host, 0x503ea0, 4);
    state->multiply = lift_host_read(host, 0x503ea4, 4);
    state->divide = lift_host_read(host, 0x503ea8, 4);
    state->hardware = lift_host_read(host, 0x5054a1, 1);
    state->capability = lift_host_read(host, 0x508798, 1);
    state->control = host->rtl_single_control;
}

static void host_single_exception(uint32_t target, VertrixRtlFloatState *state, void *opaque)
{
    HostSingleContext *context = opaque;
    LiftHost *host = context->host;
    /* Publish lazy initialization before the first boundary. Refresh before each call so
     * direct writes by the previous boundary remain live. Explicit state-field changes by
     * the boundary commit to host globals; otherwise its direct host writes are retained. */
    host_single_publish(context, state);
    host_single_refresh(state, host);
    VertrixRtlFloatState before = *state;
    host->rtl_single_exception(target, state, host->rtl_single_exception_context);
    if (state->helper != before.helper)
        host_write(host, 0x503ea0, 4, state->helper);
    if (state->multiply != before.multiply)
        host_write(host, 0x503ea4, 4, state->multiply);
    if (state->divide != before.divide)
        host_write(host, 0x503ea8, 4, state->divide);
    if (state->hardware != before.hardware)
        host_write(host, 0x5054a1, 1, state->hardware);
    if (state->capability != before.capability)
        host_write(host, 0x508798, 1, state->capability);
    if (state->control != before.control)
        host->rtl_single_control = state->control;
    host_single_refresh(state, host);
}

static uint32_t host_rtl_arithmetic(VertrixCallSite *site, LiftHost *host)
{
    VertrixRtlFloatState state = {site->eax,
                                  site->edx,
                                  site->ebx,
                                  site->ecx,
                                  lift_host_read(host, 0x503ea0, 4),
                                  lift_host_read(host, 0x503ea4, 4),
                                  lift_host_read(host, 0x503ea8, 4),
                                  lift_host_read(host, 0x5054a1, 1),
                                  lift_host_read(host, 0x508798, 1),
                                  host->rtl_single_control};
    HostSingleContext context = {host, 0};
    VertrixRtlFloatCall call = host->rtl_single_exception ? host_single_exception : NULL;
    int ok;
    switch (site->target)
    {
        case 0x4db350:
            ok = vertrix_rtl_double_add_full(&state, call, &context);
            break;
        case 0x4db507:
            ok = vertrix_rtl_double_multiply_full(&state, call, &context);
            break;
        case 0x4d809c:
            ok = vertrix_rtl_single_subtract_full(&state, call, &context);
            break;
        case 0x4d80a6:
            ok = vertrix_rtl_single_add_full(&state, call, &context);
            break;
        case 0x4d8177:
            ok = vertrix_rtl_single_multiply_full(&state, call, &context);
            break;
        default:
            ok = vertrix_rtl_single_divide_full(&state, call, &context);
            break;
    }
    if (!ok)
    {
        host->rtl_single_failures++;
        site->out_value = site->edx;
        return site->eax;
    }
    host_single_publish(&context, &state);
    site->edx = state.edx;
    site->ebx = state.ebx;
    site->ecx = state.ecx;
    site->out_value = state.edx;
    return state.eax;
}

/* Original 0x475090: the RGB lookup, hue and auxiliary tables and the pointer tables that index
 * them. The lifted routine scans 101 channel values per colour for 262144 colours, which is too
 * slow on the Wii, so the recovered builder (palette_tables.c, verified against the original)
 * fills the same memory. */
static uint32_t host_palette_build(LiftHost *host)
{
    VertrixPaletteTables tables = {0};
    uint32_t lookup, hue, i;
    if (!vertrix_palette_tables_build(&tables))
    {
        return 0;
    }
    lookup = host_allocate(0x100000, host);
    hue = host_allocate(0x40000, host);
    host_write(host, 0x54b800, 4, lookup);
    host_write(host, 0x54b804, 4, hue);
    for (i = 0; i < 262144; i++)
    {
        host_write(host, lookup + 4 * i, 4, tables.lookup[i]);
        host_write(host, hue + i, 1, tables.hue[i]);
    }
    for (i = 0; i < sizeof tables.channels; i++)
    {
        host_write(host, 0x5468b0 + i, 1, tables.channels[i]);
    }
    for (i = 0; i < 255; i++)
    {
        host_write(host, 0x54c1d4 + 4 * i, 4, tables.auxiliary[i]);
    }
    for (i = 4; i <= 0x3fc; i += 4) /* 0x4753e4: the copy and the constant 100 column */
    {
        host_write(host, 0x54c9c8 + i, 4, 0x64);
        host_write(host, 0x54c5cc + i, 4, (uint32_t)host_read(0x54c1d0 + i, host));
    }
    for (i = 4; i <= 0x320; i += 4)
    {
        host_write(host, 0x54b86c + i, 4, 0x5468b0);
        host_write(host, 0x54beb0 + i, 4, 0x54b798);
    }
    for (i = 0; i < 0x324; i += 4)
    {
        host_write(host, 0x54bb90 + i, 4, 0x5468b0 + 0x65 * (i / 4));
    }
    host_write(host, 0x54d1d0, 4, 0x54c9cc);
    for (i = 0; i < 255; i++)
    {
        host_write(host, 0x54d1d4 + 4 * i, 4, 0x54c1d4 + 4 * i);
    }
    host_write(host, 0x54cdc8, 4, 0x54bb90);
    host_write(host, 0x54cdcc, 4, 0x54d1d0);
    return 0;
}

static uint32_t host_boundary(VertrixCallSite *site, void *context)
{
    LiftHost *host = context;
    unsigned i;
    if (site->target >= LIFT_COM_BASE && site->target < LIFT_COM_BASE + 0x400)
    {
        return host_com(host, (site->target - LIFT_COM_BASE) >> 8,
                        (site->target - LIFT_COM_BASE) & 0xff, site);
    }
    {
        uint32_t slot = vertrix_import_slot(host->image, LIFT_HOST_IMAGE_BASE, site->target);
        const char *name = vertrix_import_name(slot);
        uint32_t result;
        if (name != NULL && host_import(host, site, name, &result))
        {
            return result;
        }
        site->target = slot;
    }
    if (site->target == 0x4d88a0)
    {
        host_list_insert(host, site->eax, site->edx, site->ecx, site->ebx);
        return site->eax;
    }
    if (site->target == 0x482310) /* mov [eax + 0x30], 0x516b94; ret */
    {
        host_write(host, site->eax + 0x30, 4, 0x516b94);
        return site->eax;
    }
    if (site->target == 0x475090)
        return host_palette_build(host);
    if (site->target == 0x48ac50 || site->target == 0x48ad00) /* load an image file: eax = path, the result is a surface object */
    {
        char text[260];
        unsigned k;
        uint8_t *pixels = NULL;
        uint32_t width = 0, height = 0, surface, base, pitch, x, y;
        VertrixCallSite create;
        for (k = 0; k < sizeof text - 1 && (text[k] = (char)lift_host_read(host, site->eax + k, 1)) != 0; k++)
        {
        }
        text[k] = 0;
        if (host->decode_jpeg == NULL || !host->decode_jpeg(host->archive, text, &pixels, &width, &height))
        {
            if (lift_host_trace_files)
            {
                printf("image %s: not decoded\n", text);
            }
            return 0;
        }
        memset(&create, 0, sizeof create);
        create.target = 0x478d10; /* a width by height surface of 4 bytes per pixel */
        create.eax = width;
        create.edx = height;
        create.ebx = 4;
        surface = host->calls.calls.call(&create, host->calls.calls.context);
        base = lift_host_read(host, surface, 4);
        pitch = lift_host_read(host, surface + 0x14, 4);
        for (y = 0; surface != 0 && y < height; y++)
        {
            for (x = 0; x < width; x++)
            {
                const uint8_t *p = pixels + 4 * ((size_t)y * width + x);
                host_write(host, base + y * pitch + 4 * x, 4,
                           (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16);
            }
        }
        if (lift_host_trace_files)
        {
            printf("image %s: %ux%u surface %x pixels %x first %x\n", text, (unsigned)width, (unsigned)height, (unsigned)surface, (unsigned)base, (unsigned)lift_host_read(host, base + 4 * (width * height / 2 + width / 2), 4));
        }
        free(pixels);
        return surface;
    }
    if (site->target == 0x48ae00) /* JPEG decode: no bitmap until a native decoder exists */
        return 0;
    if (site->target == 0x4d809c || site->target == 0x4d80a6 || site->target == 0x4d8177 ||
        site->target == 0x4d81fe || site->target == 0x4db350 || site->target == 0x4db507)
    {
        return host_rtl_arithmetic(site, host);
    }
    if (site->target == 0x4eb652) /* RTL double divide: edx:eax / ecx:ebx */
    {
        union
        {
            uint64_t bits;
            double value;
        } left, right, out;
        left.bits = ((uint64_t)site->edx << 32) | site->eax;
        right.bits = ((uint64_t)site->ecx << 32) | site->ebx;
        out.value = left.value / right.value;
        if ((uint32_t)(out.bits >> 32) == 0x80000000u)
        {
            out.bits = 0;
        }
        site->out_value = (uint32_t)(out.bits >> 32);
        return (uint32_t)out.bits;
    }
    if (site->target == 0x4e04f4 || site->target == 0x4e0f8b)
    {
        return site->eax; /* a bare ret; 0x4e0f8b is the exception-state check, no exception is pending */
    }
    if (site->target == 0x4eb5e0)
    {
        host_move(host, site->eax, site->edx, site->ebx); /* copy edx to eax, ebx bytes */
        return site->eax;
    }
    if (site->target == 0x4e1140)
    {
        host_move(host, site->eax, site->edx, site->ebx);
        return site->eax;
    }
    if (site->target == LIFT_GLOBAL_STORE)
    {
        {
            static int shown;
            if (shown++ < 40)
                fprintf(stderr, "gstore %x = %x (depth %u)\n", site->eax, site->edx,
                        vertrix_lifted_depth());
        }
        host_write(host, site->eax, site->stack, site->edx);
        return 0;
    }
    if (site->target == LIFT_HOST_ALLOCATOR || site->target == LIFT_HOST_GETMEM)
    {
        return host_allocate(site->eax, host);
    }
    host->boundary_calls++;
    for (i = 0; i < host->boundary_distinct; i++)
    {
        if (host->boundary_targets[i] == site->target)
        {
            host->boundary_counts[i]++;
            return 0;
        }
    }
    if (host->boundary_distinct < LIFT_HOST_TARGETS)
    {
        host->boundary_targets[host->boundary_distinct] = site->target;
        host->boundary_counts[host->boundary_distinct++] = 1;
    }
    return 0;
}

void lift_host_init(LiftHost *host, uint8_t *image, const uint8_t *original, uint8_t *heap,
                    uint32_t heap_size)
{
    memset(host, 0, sizeof *host);
    memcpy(image, original, LIFT_HOST_IMAGE_SIZE);
    host->image = image;
    host->heap = heap;
    host->heap_size = heap_size;
    host->rtl_single_control = 0x037f;
    host->inner.call = host_boundary;
    host->inner.context = host;
    host->globals.read = host_read;
    host->globals.context = host;
    host->services.resolve = host_resolve;
    host->services.allocate = host_allocate;
    host->services.context = host;
    vertrix_lifted_calls_init(&host->calls, &host->inner, &host->services, &host->globals);
}

uint32_t lift_host_run(LiftHost *host, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                       uint32_t ecx, int *lifted)
{
    VertrixCallSite site;
    *lifted = vertrix_lifted_has(target);
    if (!*lifted)
    {
        return 0;
    }
    memset(&site, 0, sizeof site);
    site.target = target;
    site.eax = eax;
    site.edx = edx;
    site.ebx = ebx;
    site.ecx = ecx;
    return host->calls.calls.call(&site, host->calls.calls.context);
}
