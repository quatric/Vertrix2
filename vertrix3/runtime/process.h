#ifndef V3_PROCESS_H
#define V3_PROCESS_H

#include <setjmp.h>

#include "runtime.h"
#include "threads.h"

#ifndef V3_HEAP_SIZE
#define V3_HEAP_SIZE 0x30000000u
#endif

extern const uint32_t v3_entry_offset;

enum
{
    V3_HANDLE_THREAD = 1,
    V3_HANDLE_EVENT,
    V3_HANDLE_MUTEX,
    V3_HANDLE_FILE,
    V3_HANDLE_CONSOLE,
    V3_HANDLE_FIND,
    V3_HANDLE_HEAP,
    V3_HANDLE_MODULE,
    V3_HANDLE_WAVE
};

enum
{
    V3_TLS_SLOTS = 64
};

typedef struct V3Thread
{
    Cpu cpu;
    uint32_t id;
    uint32_t handle;
    uint32_t start, parameter;
    uint32_t exit_code;
    uint32_t last_error;
    uint32_t tls[V3_TLS_SLOTS];
    V3Event *done;
    jmp_buf exit;
} V3Thread;

uint32_t v3_handle_new(int type, void *object);
void *v3_handle_get(uint32_t handle, int type);
int v3_handle_type(uint32_t handle);
void v3_handle_close(uint32_t handle);

V3Thread *v3_current(void);
V3Thread *v3_thread_create(uint32_t start, uint32_t parameter, uint32_t stack_size);
int v3_thread_run(V3Thread *thread, int priority);
_Noreturn void v3_thread_exit(uint32_t code);
_Noreturn void v3_process_exit(uint32_t code);
int v3_exiting(void);

void v3_note_region(uint32_t address, uint32_t size);
/* kernel32.c: the command line and environment. */
void v3_process_init(const char *command_line);

/* Import tables of the modules in vertrix3/win32. */
typedef struct
{
    const char *name;
    V3Code code;
} V3Export;

extern const V3Export v3_kernel32[];
extern const V3Export v3_user32[];
extern const V3Export v3_winmm[];
extern const V3Export v3_ole32[];
extern const V3Export v3_advapi32[];
extern const V3Export v3_d3d9[];
extern const V3Export v3_dinput8[];

/* Map a game path (".\VERTRIX3.VF", "C:\...\Settings\Vertrix3.cfg") to a host path. */
void v3_host_path(const char *game_path, char *out, size_t size);

#endif
