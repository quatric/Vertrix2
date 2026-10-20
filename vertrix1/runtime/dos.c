#include "dos.h"

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

/* DOS, the DPMI host and the BIOS services, for a program in protected mode under a DOS/4G
 * compatible extender: pointers are 32-bit offsets in the segment registers' segments (ds:edx,
 * es:edi), counts are 32-bit. Files live in the driver's directory, which the program sees as
 * C:\VERTRIX, its current directory. */

#define CF_SET()                                                                                   \
    do                                                                                             \
    {                                                                                              \
        c->cf = 1;                                                                                 \
    } while (0)
#define CF_CLEAR()                                                                                 \
    do                                                                                             \
    {                                                                                              \
        c->cf = 0;                                                                                 \
    } while (0)

#define AL (c->eax & 0xffu)
#define AH ((c->eax >> 8) & 0xffu)
#define BL (c->ebx & 0xffu)
#define BH ((c->ebx >> 8) & 0xffu)
#define CX (c->ecx & 0xffffu)
#define DX (c->edx & 0xffffu)
#define BX (c->ebx & 0xffffu)
#define SET_AX(v) (c->eax = (c->eax & 0xffff0000u) | ((uint32_t)(v) & 0xffffu))
#define SET_AL(v) (c->eax = (c->eax & 0xffffff00u) | ((uint32_t)(v) & 0xffu))
#define SET_BX(v) (c->ebx = (c->ebx & 0xffff0000u) | ((uint32_t)(v) & 0xffffu))
#define SET_CX(v) (c->ecx = (c->ecx & 0xffff0000u) | ((uint32_t)(v) & 0xffffu))
#define SET_DX(v) (c->edx = (c->edx & 0xffff0000u) | ((uint32_t)(v) & 0xffffu))
#define DS(offset) (c->seg_base[3] + (offset))
#define ES(offset) (c->seg_base[0] + (offset))

static void dos_error(Cpu *c, unsigned code)
{
    SET_AX(code);
    CF_SET();
}

/* --- the console ---------------------------------------------------------------------------- */

static char console_line[256];
static size_t console_length;

static void console_put(char ch)
{
    if (ch == '\r')
    {
        return;
    }
    if (ch != '\n')
    {
        console_line[console_length++] = ch;
    }
    if (ch == '\n' || console_length == sizeof console_line - 1)
    {
        if (v1_platform->console)
        {
            v1_platform->console(console_line, console_length);
        }
        else
        {
            v3_log("console: %.*s", (int)console_length, console_line);
        }
        console_length = 0;
    }
}

/* --- files ---------------------------------------------------------------------------------- */

enum
{
    HANDLES = 40
};

static FILE *handles[HANDLES];
static char handle_path[HANDLES][512];
static uint32_t dta = 0;
static char cwd[64] = "VERTRIX";

/* A DOS path as a host path in the game's directory: the drive is dropped, C:\VERTRIX is the
 * directory itself, and each name is matched without regard to case. */
static void host_path(const char *dos, char *out, size_t size)
{
    char path[256];
    size_t n = 0;
    if (dos[0] && dos[1] == ':')
    {
        dos += 2;
    }
    int absolute = dos[0] == '\\' || dos[0] == '/';
    char full[256];
    if (absolute)
    {
        snprintf(full, sizeof full, "%s", dos + 1);
    }
    else
    {
        snprintf(full, sizeof full, "%s\\%s", cwd, dos);
    }
    for (const char *p = full; *p && n + 1 < sizeof path; ++p)
    {
        path[n++] = *p == '\\' ? '/' : *p;
    }
    path[n] = 0;
    /* Drop the game's own directory and "." components. */
    const char *rest = path;
    if (strncasecmp(rest, "VERTRIX/", 8) == 0)
    {
        rest += 8;
    }
    else if (strcasecmp(rest, "VERTRIX") == 0)
    {
        rest = "";
    }
    while (rest[0] == '.' && rest[1] == '/')
    {
        rest += 2;
    }
    snprintf(out, size, "%s/%s", v1_platform->directory, rest);
    /* Case: look each component up when the name as given is not there. */
    struct stat st;
    if (stat(out, &st) == 0)
    {
        return;
    }
    char built[512];
    snprintf(built, sizeof built, "%s", v1_platform->directory);
    char copy[256];
    snprintf(copy, sizeof copy, "%s", rest);
    for (char *part = strtok(copy, "/"); part; part = strtok(NULL, "/"))
    {
        char found[256] = "";
        DIR *dir = opendir(built);
        if (dir)
        {
            struct dirent *e;
            while ((e = readdir(dir)) != NULL)
            {
                if (strcasecmp(e->d_name, part) == 0)
                {
                    snprintf(found, sizeof found, "%s", e->d_name);
                    break;
                }
            }
            closedir(dir);
        }
        const size_t len = strlen(built);
        snprintf(built + len, sizeof built - len, "/%s", found[0] ? found : part);
    }
    snprintf(out, size, "%s", built);
}

static int handle_new(FILE *f, const char *path)
{
    for (int h = 5; h < HANDLES; ++h)
    {
        if (!handles[h])
        {
            handles[h] = f;
            snprintf(handle_path[h], sizeof handle_path[h], "%s", path);
            return h;
        }
    }
    fclose(f);
    return -1;
}

static void dos_open(Cpu *c, int create)
{
    char name[256];
    char path[512];
    v3_read_string(DS(c->edx), name, sizeof name);
    host_path(name, path, sizeof path);
    FILE *f;
    if (create)
    {
        f = fopen(path, "w+b");
    }
    else
    {
        const unsigned mode = AL & 3;
        f = fopen(path, mode == 0 ? "rb" : "r+b");
    }
    if (!f)
    {
        v3_log("dos: %s %s failed", create ? "create" : "open", name);
        dos_error(c, create ? 5 : 2);
        return;
    }
    const int h = handle_new(f, path);
    if (h < 0)
    {
        dos_error(c, 4);
        return;
    }
    v3_log("dos: %s %s -> %d", create ? "create" : "open", name, h);
    SET_AX(h);
    CF_CLEAR();
}

static FILE *handle_file(Cpu *c, unsigned h)
{
    if (h >= HANDLES || !handles[h])
    {
        dos_error(c, 6);
        return NULL;
    }
    return handles[h];
}

static void dos_read(Cpu *c)
{
    const unsigned h = BX;
    if (h == 0)
    {
        /* stdin: a line from the keyboard; the game reads none. */
        c->eax = 0;
        CF_CLEAR();
        return;
    }
    FILE *f = handle_file(c, h);
    if (!f)
    {
        return;
    }
    const uint32_t address = DS(c->edx);
    uint32_t done = 0;
    uint8_t buffer[4096];
    while (done < c->ecx)
    {
        uint32_t chunk = c->ecx - done;
        if (chunk > sizeof buffer)
        {
            chunk = sizeof buffer;
        }
        const size_t got = fread(buffer, 1, chunk, f);
        for (size_t i = 0; i < got; ++i)
        {
            v1_vw8(address + done + (uint32_t)i, buffer[i]);
        }
        done += (uint32_t)got;
        if (got < chunk)
        {
            break;
        }
    }
    c->eax = done;
    CF_CLEAR();
}

static void dos_write(Cpu *c)
{
    const unsigned h = BX;
    const uint32_t address = DS(c->edx);
    if (h == 1 || h == 2)
    {
        for (uint32_t i = 0; i < c->ecx; ++i)
        {
            console_put((char)v3_r8(address + i));
        }
        c->eax = c->ecx;
        CF_CLEAR();
        return;
    }
    if (h < 5)
    {
        c->eax = c->ecx;
        CF_CLEAR();
        return;
    }
    FILE *f = handle_file(c, h);
    if (!f)
    {
        return;
    }
    if (c->ecx == 0)
    {
        /* Truncate at the current position. */
        const long at = ftell(f);
        fflush(f);
        if (ftruncate(fileno(f), at) != 0)
        {
            v3_log("dos: truncate %s failed", handle_path[h]);
        }
        c->eax = 0;
        CF_CLEAR();
        return;
    }
    uint32_t done = 0;
    uint8_t buffer[4096];
    while (done < c->ecx)
    {
        uint32_t chunk = c->ecx - done;
        if (chunk > sizeof buffer)
        {
            chunk = sizeof buffer;
        }
        for (uint32_t i = 0; i < chunk; ++i)
        {
            buffer[i] = (uint8_t)v1_vr8(address + done + i);
        }
        const size_t put = fwrite(buffer, 1, chunk, f);
        done += (uint32_t)put;
        if (put < chunk)
        {
            break;
        }
    }
    c->eax = done;
    CF_CLEAR();
}

static void dos_seek(Cpu *c)
{
    FILE *f = handle_file(c, BX);
    if (!f)
    {
        return;
    }
    const long offset = (long)(int32_t)(CX << 16 | DX);
    const int whence = AL == 0 ? SEEK_SET : AL == 1 ? SEEK_CUR : SEEK_END;
    if (fseek(f, offset, whence) != 0)
    {
        dos_error(c, 0x19);
        return;
    }
    const long at = ftell(f);
    SET_AX((uint32_t)at);
    SET_DX((uint32_t)at >> 16);
    CF_CLEAR();
}

/* The disk transfer area of findfirst/findnext: the pattern's directory scanned again from the
 * position kept in the reserved bytes. */
static int dos_match(const char *pattern, const char *name)
{
    /* DOS 8.3 wildcards: '*' to the end of the part, '?' one character. */
    char pbase[16] = "", pext[8] = "", nbase[16] = "", next[8] = "";
    const char *dot = strrchr(pattern, '.');
    snprintf(pbase, sizeof pbase, "%.*s", (int)(dot ? dot - pattern : (long)strlen(pattern)),
             pattern);
    snprintf(pext, sizeof pext, "%s", dot ? dot + 1 : "");
    dot = strrchr(name, '.');
    snprintf(nbase, sizeof nbase, "%.*s", (int)(dot ? dot - name : (long)strlen(name)), name);
    snprintf(next, sizeof next, "%s", dot ? dot + 1 : "");
    const char *parts[2][2] = {{pbase, nbase}, {pext, next}};
    for (int k = 0; k < 2; ++k)
    {
        const char *p = parts[k][0];
        const char *n = parts[k][1];
        for (; *p; ++p)
        {
            if (*p == '*')
            {
                n = "";
                break;
            }
            if (!*n)
            {
                if (*p != '?')
                {
                    return 0;
                }
                continue;
            }
            if (*p != '?' && toupper((unsigned char)*p) != toupper((unsigned char)*n))
            {
                return 0;
            }
            ++n;
        }
        if (*n)
        {
            return 0;
        }
    }
    return 1;
}

static char find_pattern[256];
static char find_dir[512];

static void dos_find(Cpu *c, int first)
{
    if (first)
    {
        char name[256];
        v3_read_string(DS(c->edx), name, sizeof name);
        const char *base = name;
        for (const char *p = name; *p; ++p)
        {
            if (*p == '\\' || *p == '/' || *p == ':')
            {
                base = p + 1;
            }
        }
        snprintf(find_pattern, sizeof find_pattern, "%s", base);
        char dir[256];
        snprintf(dir, sizeof dir, "%.*s", (int)(base - name), name);
        host_path(dir[0] ? dir : ".", find_dir, sizeof find_dir);
        v3_w32(dta, 0);
    }
    uint32_t index = v3_r32(dta);
    DIR *d = opendir(find_dir);
    if (!d)
    {
        dos_error(c, 0x12);
        return;
    }
    struct dirent *e;
    uint32_t seen = 0;
    while ((e = readdir(d)) != NULL)
    {
        if (e->d_name[0] == '.' || !dos_match(find_pattern, e->d_name))
        {
            continue;
        }
        if (seen++ < index)
        {
            continue;
        }
        char path[800];
        snprintf(path, sizeof path, "%s/%s", find_dir, e->d_name);
        struct stat st;
        if (stat(path, &st) != 0 || S_ISDIR(st.st_mode))
        {
            continue;
        }
        v3_w32(dta, seen);
        v3_w8(dta + 21, 0x20);
        v3_w16(dta + 22, 0);
        v3_w16(dta + 24, (1997 - 1980) << 9 | 1 << 5 | 1);
        v3_w32(dta + 26, (uint32_t)st.st_size);
        char upper[13];
        size_t k = 0;
        for (; e->d_name[k] && k < 12; ++k)
        {
            upper[k] = (char)toupper((unsigned char)e->d_name[k]);
        }
        upper[k] = 0;
        v3_write_string(dta + 30, upper, 13);
        closedir(d);
        CF_CLEAR();
        SET_AX(0);
        return;
    }
    closedir(d);
    dos_error(c, 0x12);
}

/* --- DOS memory ------------------------------------------------------------------------------ */

enum
{
    DOS_BLOCKS = 32
};

static struct
{
    uint32_t address, size, selector;
} dos_blocks[DOS_BLOCKS];

static uint32_t dos_alloc(uint32_t bytes, uint32_t *largest)
{
    bytes = (bytes + 15u) & ~15u;
    uint32_t at = V1_DOS_MEMORY;
    uint32_t best = 0;
    for (;;)
    {
        uint32_t next_used = V1_DOS_MEMORY_END;
        uint32_t clash = 0;
        for (unsigned i = 0; i < DOS_BLOCKS; ++i)
        {
            if (dos_blocks[i].size && dos_blocks[i].address < at + bytes &&
                dos_blocks[i].address + dos_blocks[i].size > at)
            {
                clash = dos_blocks[i].address + dos_blocks[i].size;
            }
            if (dos_blocks[i].size && dos_blocks[i].address >= at &&
                dos_blocks[i].address < next_used)
            {
                next_used = dos_blocks[i].address;
            }
        }
        if (!clash && at + bytes <= V1_DOS_MEMORY_END)
        {
            break;
        }
        if (next_used - at > best && next_used > at)
        {
            best = next_used - at;
        }
        if (!clash || clash >= V1_DOS_MEMORY_END)
        {
            *largest = best;
            return 0;
        }
        at = clash;
    }
    for (unsigned i = 0; i < DOS_BLOCKS; ++i)
    {
        if (!dos_blocks[i].size)
        {
            dos_blocks[i].address = at;
            dos_blocks[i].size = bytes;
            dos_blocks[i].selector = v1_selector_alloc(at, bytes - 1);
            memset(MEM(at), 0, bytes);
            return at;
        }
    }
    *largest = 0;
    return 0;
}

static int dos_block_of_selector(uint32_t selector)
{
    for (unsigned i = 0; i < DOS_BLOCKS; ++i)
    {
        if (dos_blocks[i].size && dos_blocks[i].selector == selector)
        {
            return (int)i;
        }
    }
    return -1;
}

/* --- int 21h ------------------------------------------------------------------------------- */

static int pending_scan = -1;

static int console_key(Cpu *c, uint32_t next, int wait)
{
    if (pending_scan >= 0)
    {
        const int k = pending_scan;
        pending_scan = -1;
        return k;
    }
    for (;;)
    {
        const int key = v1_bios_key_read();
        if (key >= 0)
        {
            if ((key & 0xff) == 0 || (key & 0xff) == 0xe0)
            {
                pending_scan = key >> 8;
                return 0;
            }
            return key & 0xff;
        }
        if (!wait)
        {
            return -1;
        }
        v1_idle(c, next);
    }
}

static void int21(Cpu *c, uint32_t next)
{
    const unsigned ah = AH;
    switch (ah)
    {
        case 0x01:
        case 0x07:
        case 0x08:
            SET_AL(console_key(c, next, 1));
            if (ah == 0x01)
            {
                console_put((char)AL);
            }
            return;
        case 0x02:
            console_put((char)(c->edx & 0xff));
            return;
        case 0x06:
            if ((c->edx & 0xff) == 0xff)
            {
                const int k = console_key(c, next, 0);
                c->zf = k < 0;
                SET_AL(k < 0 ? 0 : k);
            }
            else
            {
                console_put((char)(c->edx & 0xff));
            }
            return;
        case 0x09:
            for (uint32_t a = DS(c->edx); v3_r8(a) != '$'; ++a)
            {
                console_put((char)v3_r8(a));
            }
            return;
        case 0x0b:
            v1_service(c, next);
            SET_AL(pending_scan >= 0 || v1_bios_key_peek() >= 0 ? 0xff : 0);
            return;
        case 0x0c:
            while (v1_bios_key_read() >= 0)
            {
            }
            pending_scan = -1;
            if (AL == 0x01 || AL == 0x06 || AL == 0x07 || AL == 0x08)
            {
                c->eax = (c->eax & 0xffff00ffu) | AL << 8;
                int21(c, next);
            }
            return;
        case 0x0e:
            SET_AL(26);
            return;
        case 0x19:
            SET_AL(2);
            return;
        case 0x1a:
            dta = DS(c->edx);
            return;
        case 0x25:
            v1_vector_set(AL, c->sreg[3], c->edx);
            return;
        case 0x2a:
        case 0x2c:
        {
            const time_t t = time(NULL);
            const struct tm *tm = localtime(&t);
            if (ah == 0x2a)
            {
                SET_CX(tm->tm_year + 1900);
                SET_DX((tm->tm_mon + 1) << 8 | tm->tm_mday);
                SET_AL(tm->tm_wday);
            }
            else
            {
                SET_CX(tm->tm_hour << 8 | tm->tm_min);
                SET_DX(tm->tm_sec << 8 | (unsigned)(v1_clock() / 10000u % 100u));
            }
            return;
        }
        case 0x2f:
            v1_load_segment(c, 0, V1_SEL_DATA);
            c->ebx = dta;
            return;
        case 0x30:
            /* MS-DOS 6.22; the high half of eax stays as given (not Phar Lap's "DX"). */
            SET_AX(0x1606);
            SET_BX(0xff00);
            return;
        case 0x33:
            if (AL == 0)
            {
                SET_DX(c->edx & 0xff00u);
            }
            else if (AL == 5)
            {
                SET_DX((c->edx & 0xff00u) | 3);
            }
            return;
        case 0x35:
        {
            uint32_t selector, offset;
            v1_vector_get(AL, &selector, &offset);
            v1_load_segment(c, 0, selector);
            c->ebx = offset;
            return;
        }
        case 0x36:
            SET_AX(64);
            SET_BX(0x4000);
            SET_CX(512);
            SET_DX(0x8000);
            return;
        case 0x39:
        case 0x3a:
            CF_CLEAR();
            return;
        case 0x3b:
        {
            char name[128];
            v3_read_string(DS(c->edx), name, sizeof name);
            v3_log("dos: chdir %s", name);
            CF_CLEAR();
            return;
        }
        case 0x3c:
            dos_open(c, 1);
            return;
        case 0x3d:
            dos_open(c, 0);
            return;
        case 0x3e:
        {
            const unsigned h = BX;
            if (h < 5)
            {
                CF_CLEAR();
                return;
            }
            FILE *f = handle_file(c, h);
            if (f)
            {
                fclose(f);
                handles[h] = NULL;
                CF_CLEAR();
            }
            return;
        }
        case 0x3f:
            dos_read(c);
            return;
        case 0x40:
            dos_write(c);
            return;
        case 0x41:
        {
            char name[256];
            char path[512];
            v3_read_string(DS(c->edx), name, sizeof name);
            host_path(name, path, sizeof path);
            if (remove(path) != 0)
            {
                dos_error(c, 2);
                return;
            }
            CF_CLEAR();
            return;
        }
        case 0x42:
            dos_seek(c);
            return;
        case 0x43:
        {
            char name[256];
            char path[512];
            struct stat st;
            v3_read_string(DS(c->edx), name, sizeof name);
            host_path(name, path, sizeof path);
            if (stat(path, &st) != 0)
            {
                dos_error(c, 2);
                return;
            }
            if (AL == 0)
            {
                SET_CX(S_ISDIR(st.st_mode) ? 0x10 : 0x20);
            }
            CF_CLEAR();
            return;
        }
        case 0x44:
            switch (AL)
            {
                case 0x00:
                {
                    const unsigned h = BX;
                    if (h < 5)
                    {
                        SET_DX(h == 0 ? 0x80d3 : h == 1 || h == 2 ? 0x80d3 : 0x80c0);
                        CF_CLEAR();
                        return;
                    }
                    if (handle_file(c, h))
                    {
                        SET_DX(0x0002);
                        CF_CLEAR();
                    }
                    return;
                }
                case 0x01:
                    CF_CLEAR();
                    return;
                case 0x06:
                case 0x07:
                    SET_AL(0xff);
                    CF_CLEAR();
                    return;
                case 0x08:
                    SET_AX(1);
                    CF_CLEAR();
                    return;
                default:
                    v1_log_once("dos: ioctl %02x", AL);
                    dos_error(c, 1);
                    return;
            }
        case 0x45:
        case 0x46:
            v1_log_once("dos: dup %02x", ah);
            dos_error(c, 4);
            return;
        case 0x47:
            v3_write_string(DS(c->esi), cwd, 64);
            CF_CLEAR();
            return;
        case 0x4c:
            v3_log("dos: exit %u", AL);
            v1_exit((int)AL);
        case 0x4e:
            dos_find(c, 1);
            return;
        case 0x4f:
            dos_find(c, 0);
            return;
        case 0x56:
        {
            char from[256], to[256], hfrom[512], hto[512];
            v3_read_string(DS(c->edx), from, sizeof from);
            v3_read_string(ES(c->edi), to, sizeof to);
            host_path(from, hfrom, sizeof hfrom);
            host_path(to, hto, sizeof hto);
            if (rename(hfrom, hto) != 0)
            {
                dos_error(c, 5);
                return;
            }
            CF_CLEAR();
            return;
        }
        case 0x57:
            if (AL == 0)
            {
                SET_CX(0);
                SET_DX((1997 - 1980) << 9 | 1 << 5 | 1);
            }
            CF_CLEAR();
            return;
        case 0x58:
            SET_AX(0);
            CF_CLEAR();
            return;
        case 0x59:
            SET_AX(0);
            SET_BX(0);
            SET_CX(0);
            return;
        case 0x62:
            SET_BX(V1_SEL_PSP);
            return;
        case 0x67:
        case 0x68:
            CF_CLEAR();
            return;
        case 0xff:
            /* DOS/4G's identification (dx = 0x78): an extender of that family answers. */
            if (AL == 0 && DX == 0x78)
            {
                SET_AL(1);
                return;
            }
            break;
    }
    v1_log_once("dos: int 21h ah=%02x al=%02x unsupported", ah, AL);
    dos_error(c, 1);
}

/* --- int 31h: DPMI 0.9 ---------------------------------------------------------------------- */

static uint32_t real_vectors[256];

static void int31(Cpu *c)
{
    const unsigned ax = c->eax & 0xffffu;
    CF_CLEAR();
    switch (ax)
    {
        case 0x0000:
        {
            const uint32_t first = v1_selector_alloc(0, 0);
            for (unsigned i = 1; i < CX; ++i)
            {
                v1_selector_alloc(0, 0);
            }
            if (!first)
            {
                dos_error(c, 0x8011);
                return;
            }
            SET_AX(first);
            return;
        }
        case 0x0001:
            v1_selector_free(BX);
            return;
        case 0x0002:
        {
            const uint32_t s = v1_selector_alloc(BX << 4, 0xffff);
            SET_AX(s);
            return;
        }
        case 0x0003:
            SET_AX(8);
            return;
        case 0x0006:
        {
            if (!v1_segment_valid(BX))
            {
                dos_error(c, 0x8022);
                return;
            }
            const uint32_t base = v1_selector_base(BX);
            SET_CX(base >> 16);
            SET_DX(base);
            return;
        }
        case 0x0007:
            if (!v1_selector_set(BX, 0, CX << 16 | DX))
            {
                dos_error(c, 0x8022);
            }
            return;
        case 0x0008:
            if (!v1_selector_set(BX, 1, CX << 16 | DX))
            {
                dos_error(c, 0x8022);
            }
            return;
        case 0x0009:
            return;
        case 0x000a:
        {
            const uint32_t s = v1_selector_alloc(v1_selector_base(BX), v1_segment_limit(BX));
            SET_AX(s);
            return;
        }
        case 0x0100:
        {
            uint32_t largest = 0;
            const uint32_t at = dos_alloc(BX << 4, &largest);
            if (!at)
            {
                SET_AX(8);
                SET_BX(largest >> 4);
                CF_SET();
                return;
            }
            for (unsigned i = 0; i < DOS_BLOCKS; ++i)
            {
                if (dos_blocks[i].address == at)
                {
                    SET_DX(dos_blocks[i].selector);
                }
            }
            SET_AX(at >> 4);
            return;
        }
        case 0x0101:
        {
            const int i = dos_block_of_selector(DX);
            if (i < 0)
            {
                dos_error(c, 9);
                return;
            }
            v1_selector_free(dos_blocks[i].selector);
            dos_blocks[i].size = 0;
            return;
        }
        case 0x0200:
            SET_CX(real_vectors[BL] >> 16);
            SET_DX(real_vectors[BL]);
            return;
        case 0x0201:
            real_vectors[BL] = CX << 16 | DX;
            return;
        case 0x0202:
            SET_CX(V1_SEL_CODE);
            c->edx = 0;
            return;
        case 0x0203:
            return;
        case 0x0204:
        {
            uint32_t selector, offset;
            v1_vector_get(BL, &selector, &offset);
            SET_CX(selector);
            c->edx = offset;
            return;
        }
        case 0x0205:
            v1_vector_set(BL, CX, c->edx);
            return;
        case 0x0300:
        {
            /* Simulate a real mode interrupt: the registers from the call structure at es:edi. */
            const uint32_t s = ES(c->edi);
            Cpu r = *c;
            r.edi = v3_r32(s);
            r.esi = v3_r32(s + 4);
            r.ebp = v3_r32(s + 8);
            r.ebx = v3_r32(s + 16);
            r.edx = v3_r32(s + 20);
            r.ecx = v3_r32(s + 24);
            r.eax = v3_r32(s + 28);
            r.cf = v3_r16(s + 32) & 1u;
            r.sreg[0] = v3_r16(s + 34);
            r.seg_base[0] = r.sreg[0] << 4;
            r.sreg[3] = v3_r16(s + 36);
            r.seg_base[3] = r.sreg[3] << 4;
            v1_log_once("dpmi: real mode int %02x ax=%04x", BL, r.eax & 0xffff);
            v1_dos_int(&r, BL, 0);
            v3_w32(s, r.edi);
            v3_w32(s + 4, r.esi);
            v3_w32(s + 8, r.ebp);
            v3_w32(s + 16, r.ebx);
            v3_w32(s + 20, r.edx);
            v3_w32(s + 24, r.ecx);
            v3_w32(s + 28, r.eax);
            v3_w16(s + 32, (v3_r16(s + 32) & ~0x41u) | r.cf | r.zf << 6);
            v3_w16(s + 34, r.sreg[0]);
            return;
        }
        case 0x0400:
            SET_AX(0x005a);
            SET_BX(0x0005);
            c->ecx = (c->ecx & 0xffffff00u) | 4;
            SET_DX(0x0870);
            return;
        case 0x0500:
        {
            const uint32_t free_bytes = V1_HEAP_SIZE - v3_heap_used();
            const uint32_t s = ES(c->edi);
            v3_w32(s, free_bytes);
            for (unsigned i = 1; i < 12; ++i)
            {
                v3_w32(s + 4 * i, i <= 3 || i == 7 ? free_bytes >> 12 : 0xffffffffu);
            }
            return;
        }
        case 0x0501:
        {
            const uint32_t size = BX << 16 | CX;
            const uint32_t at = v3_alloc_aligned(size ? size : 1, 4096);
            if (!at)
            {
                dos_error(c, 0x8013);
                return;
            }
            SET_BX(at >> 16);
            SET_CX(at);
            c->esi = (c->esi & 0xffff0000u) | at >> 16;
            c->edi = (c->edi & 0xffff0000u) | (at & 0xffffu);
            return;
        }
        case 0x0502:
            v3_free((c->esi & 0xffffu) << 16 | (c->edi & 0xffffu));
            return;
        case 0x0503:
        {
            const uint32_t old = (c->esi & 0xffffu) << 16 | (c->edi & 0xffffu);
            const uint32_t size = BX << 16 | CX;
            const uint32_t at = v3_alloc_aligned(size ? size : 1, 4096);
            if (!at)
            {
                dos_error(c, 0x8013);
                return;
            }
            const uint32_t keep = v3_alloc_size(old) < size ? v3_alloc_size(old) : size;
            memmove(MEM(at), MEM(old), keep);
            v3_free(old);
            SET_BX(at >> 16);
            SET_CX(at);
            c->esi = (c->esi & 0xffff0000u) | at >> 16;
            c->edi = (c->edi & 0xffff0000u) | (at & 0xffffu);
            return;
        }
        case 0x0600:
        case 0x0601:
        case 0x0602:
        case 0x0603:
            return;
        case 0x0604:
            SET_BX(0);
            SET_CX(4096);
            return;
        case 0x0800:
            /* Physical addresses below 1 MB are linear ones here. */
            return;
        case 0x0900:
        case 0x0901:
        {
            const uint32_t was = c->iflag;
            c->iflag = ax == 0x0901;
            SET_AL(was);
            return;
        }
        case 0x0902:
            SET_AL(c->iflag);
            return;
        case 0x0e00:
            SET_AX(0x0045);
            return;
        case 0x0e01:
            return;
    }
    v1_log_once("dpmi: int 31h ax=%04x unsupported", ax);
    dos_error(c, 0x8001);
}

/* --- int 10h --------------------------------------------------------------------------------- */

static void int10(Cpu *c)
{
    const unsigned ah = AH;
    switch (ah)
    {
        case 0x00:
            v1_vga_set_mode(AL & 0x7f);
            v3_w8(0x449, AL & 0x7f);
            v3_w16(0x44a, (AL & 0x7f) == 0x13 ? 40 : 80);
            return;
        case 0x01:
        case 0x02:
            if (ah == 0x02)
            {
                v3_w16(0x450 + 2 * (BH & 7), DX);
            }
            return;
        case 0x03:
            SET_DX(v3_r16(0x450 + 2 * (BH & 7)));
            SET_CX(0x0607);
            return;
        case 0x05:
        case 0x06:
        case 0x07:
            return;
        case 0x08:
            SET_AX(0x0720);
            return;
        case 0x09:
        case 0x0a:
            return;
        case 0x0e:
            console_put((char)AL);
            return;
        case 0x0f:
            SET_AX(v3_r16(0x44a) << 8 | v3_r8(0x449));
            c->ebx &= 0xffff00ffu;
            return;
        case 0x10:
            switch (AL)
            {
                case 0x10:
                    v1_vga_dac_set(BX & 0xff, (c->edx >> 8) & 0x3f, (c->ecx >> 8) & 0x3f,
                                   c->ecx & 0x3f);
                    return;
                case 0x12:
                    for (unsigned i = 0; i < CX; ++i)
                    {
                        const uint32_t a = ES(c->edx) + 3 * i;
                        v1_vga_dac_set((BX + i) & 0xff, v3_r8(a), v3_r8(a + 1), v3_r8(a + 2));
                    }
                    return;
                case 0x15:
                {
                    unsigned r, g, b;
                    v1_vga_dac_get(BX & 0xff, &r, &g, &b);
                    c->edx = (c->edx & 0xffff00ffu) | r << 8;
                    SET_CX(g << 8 | b);
                    return;
                }
                case 0x17:
                    for (unsigned i = 0; i < CX; ++i)
                    {
                        unsigned r, g, b;
                        const uint32_t a = ES(c->edx) + 3 * i;
                        v1_vga_dac_get((BX + i) & 0xff, &r, &g, &b);
                        v3_w8(a, r);
                        v3_w8(a + 1, g);
                        v3_w8(a + 2, b);
                    }
                    return;
                default:
                    v1_log_once("bios: int 10h ax=%04x", c->eax & 0xffff);
                    return;
            }
        case 0x11:
            if (AL == 0x30)
            {
                SET_CX(16);
                SET_DX((c->edx & 0xff00u) | 24);
            }
            return;
        case 0x12:
            if (BL == 0x10)
            {
                SET_BX(0x0003);
                SET_CX(0x0009);
            }
            else
            {
                SET_AL(0x12);
            }
            return;
        case 0x1a:
            if (AL == 0)
            {
                SET_AL(0x1a);
                SET_BX(0x0008);
            }
            return;
        case 0x1b:
            return;
        case 0x4f:
            /* No VESA BIOS: the call is not supported (al is not 4Fh). */
            SET_AX(0x0100);
            return;
    }
    v1_log_once("bios: int 10h ax=%04x unsupported", c->eax & 0xffff);
}

/* --- int 16h, 1Ah, 2Fh, 33h ------------------------------------------------------------------ */

static void int16(Cpu *c, uint32_t next)
{
    switch (AH)
    {
        case 0x00:
        case 0x10:
        {
            int key;
            while ((key = v1_bios_key_read()) < 0)
            {
                v1_idle(c, next);
            }
            SET_AX(key);
            return;
        }
        case 0x01:
        case 0x11:
        {
            v1_service(c, next);
            const int key = v1_bios_key_peek();
            c->zf = key < 0;
            if (key >= 0)
            {
                SET_AX(key);
            }
            return;
        }
        case 0x02:
        case 0x12:
            SET_AL(v1_bios_shift_flags());
            return;
    }
    v1_log_once("bios: int 16h ah=%02x", AH);
}

static void int1a(Cpu *c)
{
    if (AH == 0x00)
    {
        const uint32_t ticks = v3_r32(0x46c);
        SET_CX(ticks >> 16);
        SET_DX(ticks);
        SET_AL(v3_r8(0x470));
        v3_w8(0x470, 0);
        CF_CLEAR();
        return;
    }
    const time_t t = time(NULL);
    const struct tm *tm = localtime(&t);
#define BCD(v) ((unsigned)(((v) / 10) << 4 | ((v) % 10)))
    if (AH == 0x02)
    {
        SET_CX(BCD(tm->tm_hour) << 8 | BCD(tm->tm_min));
        SET_DX(BCD(tm->tm_sec) << 8);
        CF_CLEAR();
        return;
    }
    if (AH == 0x04)
    {
        const unsigned year = (unsigned)tm->tm_year + 1900u;
        SET_CX(BCD(year / 100) << 8 | BCD(year % 100));
        SET_DX(BCD(tm->tm_mon + 1) << 8 | BCD(tm->tm_mday));
        CF_CLEAR();
        return;
    }
#undef BCD
    v1_log_once("bios: int 1ah ah=%02x", AH);
    CF_SET();
}

void v1_dos_int(Cpu *c, unsigned vector, uint32_t next)
{
    switch (vector)
    {
        case 0x10:
            int10(c);
            return;
        case 0x11:
            SET_AX(v3_r16(0x410));
            return;
        case 0x12:
            SET_AX(640);
            return;
        case 0x16:
            int16(c, next);
            return;
        case 0x1a:
            int1a(c);
            return;
        case 0x21:
            int21(c, next);
            return;
        case 0x2f:
            if ((c->eax & 0xffff) == 0x1686)
            {
                SET_AX(0); /* in protected mode under DPMI */
            }
            else if ((c->eax & 0xffff) == 0x1680)
            {
                SET_AL(0);
            }
            else
            {
                v1_log_once("bios: int 2fh ax=%04x", c->eax & 0xffff);
            }
            return;
        case 0x31:
            int31(c);
            return;
        case 0x33:
            if ((c->eax & 0xffff) == 0)
            {
                SET_AX(0); /* no mouse */
            }
            return;
    }
    v1_log_once("int %02xh ax=%04x has no handler", vector, c->eax & 0xffff);
    CF_SET();
}

/* --- the process ------------------------------------------------------------------------------ */

void v1_dos_init(void)
{
    /* The PSP: int 20h, the environment's selector, the command tail. */
    memset(MEM(V1_PSP), 0, 0x100);
    v3_w16(V1_PSP, 0x20cd);
    v3_w16(V1_PSP + 2, V1_DOS_MEMORY_END >> 4);
    v3_w16(V1_PSP + 0x2c, V1_SEL_ENV);
    char tail[127] = "";
    if (v1_platform->arguments && v1_platform->arguments[0])
    {
        snprintf(tail, sizeof tail, " %s", v1_platform->arguments);
    }
    const size_t n = strlen(tail);
    v3_w8(V1_PSP + 0x80, (uint32_t)n);
    v3_write_string(V1_PSP + 0x81, tail, 127);
    v3_w8(V1_PSP + 0x81 + (uint32_t)n, 13);
    /* The environment: the variables, an empty one, a count, the program's path. */
    static const char *const variables[] = {"COMSPEC=C:\\COMMAND.COM", "PATH=C:\\DOS",
                                            "BLASTER=A220 I7 D1 T3", NULL};
    uint32_t at = V1_ENVIRONMENT;
    for (unsigned i = 0; variables[i]; ++i)
    {
        v3_write_string(at, variables[i], 256);
        at += (uint32_t)strlen(variables[i]) + 1;
    }
    v3_w8(at++, 0);
    v3_w16(at, 1);
    at += 2;
    v3_write_string(at, "C:\\VERTRIX\\VERTRIX.EXE", 64);
    dta = V1_PSP + 0x80;
}
