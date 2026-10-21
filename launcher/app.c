#include "app.h"

#include <fat.h>
#include <gccore.h>
#include <ogc/machine/processor.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* The stub that copies the DOL's sections and jumps to it (boot_stub.S), and where it runs: high
 * in MEM1, above any game's sections and below where dolxz's loader keeps its own copy and the
 * arguments (0x817c0000). The command line sits beside it until the new program's crt0 moves it. */
extern const uint8_t vertrix_boot_stub[], vertrix_boot_stub_end[];
extern const uint8_t vertrix_sc_handler[], vertrix_sc_handler_end[];
#define STUB_ADDRESS 0x81700000u
#define ARGUMENTS_ADDRESS 0x81710000u
#define BOOT_ARGV_MAGIC 0x5f617267u
#define MAX_DOL (16u * 1024 * 1024)

static int app_argc;
static char **app_argv;
static uint8_t *scratch;
static uint32_t scratch_size;

void vertrix_app_init(int argc, char **argv)
{
    app_argc = argc;
    app_argv = argv;
}

int vertrix_app_from_launcher(void)
{
    return app_argc >= 3 && app_argv != NULL && app_argv[1] != NULL && app_argv[2] != NULL &&
           app_argv[1][0] != '\0' && app_argv[2][0] != '\0';
}

const char *vertrix_app_directory(const char *standalone)
{
    return vertrix_app_from_launcher() ? app_argv[1] : standalone;
}

void vertrix_app_set_scratch(void *start, unsigned size)
{
    scratch = (uint8_t *)(((uint32_t)start + 31u) & ~31u);
    scratch_size = size > (uint32_t)(scratch - (uint8_t *)start)
                       ? size - (uint32_t)(scratch - (uint8_t *)start)
                       : 0;
}

static uint32_t big_endian(const uint8_t *p)
{
    return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
}

/* The header's 7 text and 11 data sections: file offsets at 0x00, addresses at 0x48, sizes at
 * 0x90; the entry point at 0xe0. Every section must lie in the file and in MEM1 below the stub. */
static int valid_dol(const uint8_t *dol, uint32_t size)
{
    const uint32_t entry = big_endian(dol + 0xe0);
    int sections = 0;
    if (size < 0x100 || entry < 0x80003000u || entry >= STUB_ADDRESS)
    {
        return 0;
    }
    for (int i = 0; i < 18; ++i)
    {
        const uint32_t offset = big_endian(dol + 4 * i);
        const uint32_t address = big_endian(dol + 0x48 + 4 * i);
        const uint32_t length = big_endian(dol + 0x90 + 4 * i);
        if (length == 0)
        {
            continue;
        }
        if (offset > size || length > size - offset || address < 0x80003000u ||
            address >= STUB_ADDRESS || length > STUB_ADDRESS - address)
        {
            return 0;
        }
        ++sections;
    }
    return sections > 0;
}

static FILE *open_dol(const char *path)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        fatInitDefault(); /* a game may have unmounted the card when it closed its archive */
        file = fopen(path, "rb");
    }
    return file;
}

int vertrix_app_boot(const char *path, int argc, const char *const *args)
{
    /* The command line as the Homebrew Channel passes it: the arguments, each ended by a NUL. */
    static char command_line[1024];
    uint32_t length = 0;
    for (int i = 0; i < argc; ++i)
    {
        const size_t n = strlen(args[i]) + 1;
        if (length + n > sizeof command_line)
        {
            return -1;
        }
        memcpy(command_line + length, args[i], n);
        length += (uint32_t)n;
    }

    FILE *file = open_dol(path);
    if (file == NULL)
    {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    const long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    uint8_t *dol;
    if (size <= 0 || (uint32_t)size > MAX_DOL)
    {
        fclose(file);
        return -1;
    }
    if (scratch != NULL && scratch_size >= (uint32_t)size)
    {
        dol = scratch;
    }
    else
    {
        /* The top of MEM2's arena: the heap grows from the bottom. */
        const uint32_t high = (uint32_t)SYS_GetArena2Hi();
        const uint32_t low = (uint32_t)SYS_GetArena2Lo();
        const uint32_t at = (high - (uint32_t)size) & ~31u;
        if (high - low < (uint32_t)size + 32 || at < low)
        {
            fclose(file);
            return -1;
        }
        dol = (uint8_t *)at;
        SYS_SetArena2Hi(dol);
    }
    const size_t got = fread(dol, 1, (size_t)size, file);
    fclose(file);
    if (got != (size_t)size || !valid_dol(dol, (uint32_t)size))
    {
        return -1;
    }
    DCFlushRange(dol, (uint32_t)size);

    fatUnmount("sd");
    fatUnmount("usb");
    VIDEO_SetBlack(TRUE);
    VIDEO_Flush();
    VIDEO_WaitVSync();
    VIDEO_WaitVSync();
    SYS_ResetSystem(SYS_SHUTDOWN, 0, 0);
    uint32_t level;
    _CPU_ISR_Disable(level);
    (void)level;

    /* The system call vector, which dolxz's loader uses before it installs its own. */
    const uint32_t handler_size = (uint32_t)(vertrix_sc_handler_end - vertrix_sc_handler);
    memcpy((void *)0x80000c00, vertrix_sc_handler, handler_size);
    DCFlushRange((void *)0x80000c00, handler_size);
    ICInvalidateRange((void *)0x80000c00, handler_size);
    const uint32_t stub_size = (uint32_t)(vertrix_boot_stub_end - vertrix_boot_stub);
    memcpy((void *)STUB_ADDRESS, vertrix_boot_stub, stub_size);
    DCFlushRange((void *)STUB_ADDRESS, stub_size);
    ICInvalidateRange((void *)STUB_ADDRESS, stub_size);
    /* The argument block: magic, command line, length (libogc's struct __argv starts so). */
    uint32_t *block = (uint32_t *)ARGUMENTS_ADDRESS;
    char *line = (char *)(ARGUMENTS_ADDRESS + 0x20);
    memcpy(line, command_line, length);
    block[0] = BOOT_ARGV_MAGIC;
    block[1] = (uint32_t)line;
    block[2] = length;
    DCFlushRange(block, 0x20 + length);

    void (*stub)(const uint8_t *, const uint32_t *) =
        (void (*)(const uint8_t *, const uint32_t *))STUB_ADDRESS;
    stub(dol, length != 0 ? block : NULL);
    return -1; /* not reached */
}

void vertrix_app_return(void)
{
    if (!vertrix_app_from_launcher())
    {
        return;
    }
    /* "back" tells the launcher not to check for updates again. */
    const char *args[2] = {app_argv[2], "back"};
    vertrix_app_boot(app_argv[2], 2, args);
}
