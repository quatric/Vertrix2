#include "process.h"
#include "threads.h"

#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const V3Platform *v3_platform;
int v3_trace_imports;

/* --- handles ------------------------------------------------------------------------------ */

enum
{
    HANDLES = 1024
};

static struct
{
    int type;
    void *object;
} handles[HANDLES];

uint32_t v3_handle_new(int type, void *object)
{
    v3_lock();
    for (unsigned i = 1; i < HANDLES; ++i)
    {
        if (!handles[i].type)
        {
            handles[i].type = type;
            handles[i].object = object;
            v3_unlock();
            return 0x100u + 4u * i;
        }
    }
    v3_unlock();
    v3_fatal("out of handles");
}

void *v3_handle_get(uint32_t handle, int type)
{
    const uint32_t i = (handle - 0x100u) / 4u;
    if (handle < 0x100u || (handle & 3u) || i >= HANDLES || !handles[i].type ||
        (type && handles[i].type != type))
    {
        return NULL;
    }
    return handles[i].object;
}

int v3_handle_type(uint32_t handle)
{
    const uint32_t i = (handle - 0x100u) / 4u;
    return handle >= 0x100u && !(handle & 3u) && i < HANDLES ? handles[i].type : 0;
}

void v3_handle_close(uint32_t handle)
{
    const uint32_t i = (handle - 0x100u) / 4u;
    if (handle >= 0x100u && !(handle & 3u) && i < HANDLES)
    {
        handles[i].type = 0;
        handles[i].object = NULL;
    }
}

/* --- guest threads ------------------------------------------------------------------------ */

static uint32_t peb;
static uint32_t next_thread_id = 0x100;

uint32_t v3_kernel_thread_block(void)
{
    V3Thread *t = v3_thread_self();
    return t ? t->cpu.fs_base : 0;
}

V3Thread *v3_current(void)
{
    return v3_thread_self();
}

static void thread_block(V3Thread *t, uint32_t stack_top, uint32_t stack_size)
{
    const uint32_t teb = v3_system_alloc(0x1000);
    v3_w32(teb + 0x00, 0xffffffffu); /* no exception handler yet */
    v3_w32(teb + 0x04, stack_top);
    v3_w32(teb + 0x08, stack_top - stack_size);
    v3_w32(teb + 0x18, teb);
    v3_w32(teb + 0x20, 0x40); /* process id */
    t->id = next_thread_id;
    next_thread_id += 4;
    v3_w32(teb + 0x24, t->id);
    v3_w32(teb + 0x2c, teb + 0xe10); /* thread local storage array (unused by the game) */
    v3_w32(teb + 0x30, peb);
    t->cpu.fs_base = teb;
    t->cpu.thread = t;
}

static void cpu_reset(Cpu *c)
{
    memset(c, 0, sizeof *c);
    v3_fpu_init(c);
}

uint32_t v3_call_guest(Cpu *c, uint32_t address, unsigned count, const uint32_t *arguments,
                       int cdecl)
{
    /* The callee may change any register but the callee-saved ones; keep them all. */
    const Cpu saved = *c;
    for (unsigned i = count; i-- > 0;)
    {
        c->esp -= 4;
        v3_w32(c->esp, arguments[i]);
    }
    c->esp -= 4;
    v3_w32(c->esp, V3_RETURN_TO_HOST);
    const uint32_t esp_after = saved.esp + (cdecl ? 4u * count : 0u);
    v3_call(c, address);
    const uint32_t result = c->eax;
    if (c->esp != saved.esp && c->esp != esp_after)
    {
        v3_log("guest call %08x left esp %08x (expected %08x)", address, c->esp, saved.esp);
    }
    const uint32_t edx = c->edx;
    const uint32_t top = c->top;
    const uint32_t tags = c->tags;
    double st[8];
    memcpy(st, c->st, sizeof st);
    *c = saved;
    c->eax = result;
    c->edx = edx;
    /* A float result stays on the x87 stack. */
    c->top = top;
    c->tags = tags;
    memcpy(c->st, st, sizeof st);
    return result;
}

static void thread_main(void *p)
{
    V3Thread *t = p;
    v3_thread_set_self(t);
    Cpu *c = &t->cpu;
    if (setjmp(t->exit) == 0)
    {
        const uint32_t argument = t->parameter;
        const uint32_t result = v3_call_guest(c, t->start, 1, &argument, 0);
        t->exit_code = result;
    }
    v3_event_set(t->done);
}

V3Thread *v3_thread_create(uint32_t start, uint32_t parameter, uint32_t stack_size)
{
    V3Thread *t = calloc(1, sizeof *t);
    cpu_reset(&t->cpu);
    if (stack_size < V3_THREAD_STACK)
    {
        stack_size = V3_THREAD_STACK;
    }
    const uint32_t stack = v3_alloc_aligned(stack_size, 16);
    if (!stack)
    {
        free(t);
        return NULL;
    }
    thread_block(t, stack + stack_size, stack_size);
    t->cpu.esp = stack + stack_size - 16;
    t->start = start;
    t->parameter = parameter;
    t->done = v3_event_create(1, 0);
    t->handle = v3_handle_new(V3_HANDLE_THREAD, t);
    return t;
}

int v3_thread_run(V3Thread *t, int priority)
{
    return v3_thread_start(thread_main, t, priority);
}

_Noreturn void v3_thread_exit(uint32_t code)
{
    V3Thread *t = v3_thread_self();
    t->exit_code = code;
    longjmp(t->exit, 1);
}

/* --- startup ------------------------------------------------------------------------------ */

static V3Thread main_thread;
static int exit_code;
static jmp_buf process_exit;
static int exiting;

static void unimplemented(Cpu *c)
{
    v3_log("unimplemented: %s", v3_host_current);
    v3_trap(c, v3_r32(c->esp), "unimplemented import");
}

_Noreturn void v3_process_exit(uint32_t code)
{
    exit_code = (int)code;
    V3Thread *t = v3_thread_self();
    if (t != &main_thread)
    {
        /* Another thread ended the process: stop it, and let the main thread notice. */
        exiting = 1;
        longjmp(t->exit, 1);
    }
    longjmp(process_exit, 1);
}

int v3_exiting(void)
{
    return exiting;
}

int v3_run(const uint8_t *image, uint32_t image_size, const char *options,
           const V3Platform *platform)
{
    static char command_line[512];
    snprintf(command_line, sizeof command_line, "\"%s\\%s\"%s%s", v3_game_directory, v3_executable,
             options ? " " : "", options ? options : "");
    v3_platform = platform;
    v3_memory_init();
    v3_map(V3_SYSTEM_BASE, V3_SYSTEM_SIZE);
    v3_note_region(V3_SYSTEM_BASE, V3_SYSTEM_SIZE);
    v3_map(V3_STACK_BASE, V3_STACK_TOP - V3_STACK_BASE);
    v3_note_region(V3_STACK_BASE, V3_STACK_TOP - V3_STACK_BASE);
    const uint32_t mapped = (image_size + 0xffffu) & ~0xffffu;
    memcpy(v3_map(V3_IMAGE_BASE, mapped), image, image_size);
    v3_note_region(V3_IMAGE_BASE, mapped);
    v3_heap_init(V3_HEAP_SIZE);

    /* Imports: each slot of the import address table gets its host function. */
    for (unsigned i = 0; i < v3_import_count; ++i)
    {
        const V3Import *imp = &v3_imports[i];
        V3Code code = v3_import(imp->dll, imp->name);
        char *label = malloc(strlen(imp->dll) + strlen(imp->name) + 2);
        sprintf(label, "%s!%s", imp->dll, imp->name);
        v3_w32(imp->slot, v3_host_function(label, code ? code : unimplemented));
    }

    peb = v3_system_alloc(0x1000);
    v3_w32(peb + 0x08, V3_IMAGE_BASE);
    v3_process_init(command_line);

    cpu_reset(&main_thread.cpu);
    thread_block(&main_thread, V3_STACK_TOP, V3_STACK_TOP - V3_STACK_BASE);
    main_thread.handle = v3_handle_new(V3_HANDLE_THREAD, &main_thread);
    main_thread.done = v3_event_create(1, 0);
    v3_thread_set_self(&main_thread);
    Cpu *c = &main_thread.cpu;
    c->esp = V3_STACK_TOP - 64;
    if (setjmp(process_exit) == 0 && setjmp(main_thread.exit) == 0)
    {
        const uint32_t entry = V3_IMAGE_BASE + v3_entry_offset;
        v3_call_guest(c, entry, 0, NULL, 0);
        v3_log("the entry point returned (eax=%08x)", c->eax);
        exit_code = (int)c->eax;
    }
    return exit_code;
}
