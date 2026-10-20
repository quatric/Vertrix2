"""Generate source/lifted_dispatch.[ch]: the table of every verified lifted routine by original
address and the dispatcher that runs one for a call arriving at the boundary."""
import glob
import json
import subprocess
from pathlib import Path

from dispatch_boundaries import NATIVE_PORTS, NATIVE_UNVERIFIED_BOUNDARIES, PORT_FRAMES, PORTS

ROOT = Path(__file__).resolve().parents[1]
entries = {}
unverified_entries = {}
for path in sorted(glob.glob(str(ROOT / 'docs' / 'lift' / '*.json'))):
    name = Path(path).stem
    if name == 'unverified':
        for func, meta in json.loads(Path(path).read_text()).items():
            unverified_entries[meta['address']] = (func, meta)
        continue
    for func, meta in json.loads(Path(path).read_text()).items():
        entries[meta['address']] = (func, meta)
NATIVE_PORTS = {**NATIVE_PORTS, **{a: (f, PORT_FRAMES.get(a, 0), 0) for a, f in PORTS.items()}}
for address in NATIVE_PORTS:
    entries.pop(address, None)
    unverified_entries.pop(address, None)
# The platform implements these boundaries itself (the host JPEG decode, the palette builder): a
# lifted copy, verified or not, must not shadow it.
for address in NATIVE_UNVERIFIED_BOUNDARIES:
    entries.pop(address, None)
headers = sorted(Path(p).name for p in glob.glob(str(ROOT / 'source' / 'lifted_*.h'))
                 if 'dispatch' not in p)
# Ports: every header that declares one.
headers += sorted(Path(p).name for p in glob.glob(str(ROOT / 'source' / '*.h'))
                  if not Path(p).name.startswith('lifted_')
                  and 'uint32_t vertrix_port_' in Path(p).read_text())
row_text = {a: '    {0x%x, lifted_%s, %d, %d},' % (a, entries[a][0], entries[a][1]['stack'],
                                                entries[a][1]['arguments']) for a in entries}
row_text.update({a: '    {0x%x, %s, %d, %d},' % ((a,) + port) for a, port in NATIVE_PORTS.items()})
rows = [row_text[a] for a in sorted(row_text)]
unverified_rows = ['    {0x%x, lifted_%s, %d, %d},' % (a, unverified_entries[a][0], unverified_entries[a][1]['stack'],
                                                 unverified_entries[a][1]['arguments'])
                   for a in sorted(unverified_entries)
                   if a not in entries and a not in NATIVE_UNVERIFIED_BOUNDARIES]
# The largest frame a routine is handed garbage for: lifted copies' and ports' own (none left lifted
# is fine).
maximum = max([e[1]['stack'] for e in list(entries.values()) + list(unverified_entries.values())] +
              [port[1] for port in NATIVE_PORTS.values()] + [4])
(ROOT / 'source' / 'lifted_dispatch.h').write_text('''#ifndef VERTRIX_LIFTED_DISPATCH_H
#define VERTRIX_LIFTED_DISPATCH_H
#include <stdint.h>

#include "actor_build.h"

/* Number of original routines that run as verified lifted C (tools/gen_dispatch.py). */
unsigned vertrix_lifted_count(void);

/* How many lifted routines are executing now (the frames in vertrix_lift_frames). */
unsigned vertrix_lifted_depth(void);

/* Print every dispatched routine's original address and call depth (debugging). */
void vertrix_lifted_set_trace(int enabled);

/* Called after every lifted routine returns, with its address and entry EAX (debugging). */
extern void (*vertrix_lifted_after_hook)(uint32_t target, uint32_t eax);

/* Also run the lifted routines that did not pass verification (off by default). */
void vertrix_lifted_allow_unverified(int allowed);

/* The lifted routine for an original address, or 0 when the routine stays a call boundary. */
int vertrix_lifted_has(uint32_t target);

struct LiftEntry;
typedef uint32_t (*VertrixLiftedFunction)(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals,
                                          const struct LiftEntry *entry);

/* The function a call through `calls` to `target` with no stack arguments would run now, and the
 * frame index vertrix_lifted_dispatch would set; NULL when `calls` is not a VertrixLiftedCalls,
 * when the call would not reach a routine, or when the trace or the after hook watches every
 * dispatch (vertrix_lift_routine_hook). */
VertrixLiftedFunction vertrix_lifted_function(const VertrixCalls *calls, uint32_t target,
                                              unsigned *index);

/* Run the lifted routine for site->target with the registers and stack arguments of the site.
 * Returns 1 and stores the routine's eax in *result when there is one. */
int vertrix_lifted_dispatch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const VertrixCallSite *site,
                            uint32_t *result);

/* VertrixCalls that run the lifted routine for a target when there is one and otherwise forward
 * the call to `inner` (the platform's implementation of the unrecovered routines). */
typedef struct VertrixLiftedCalls
{
    VertrixCalls calls;
    const VertrixCalls *inner;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
} VertrixLiftedCalls;

void vertrix_lifted_calls_init(VertrixLiftedCalls *adapter, const VertrixCalls *inner,
                               const VertrixFactoryServices *services,
                               const VertrixGlobals *globals);
#endif
''')
(ROOT / 'source' / 'lifted_dispatch.c').write_text('''/* Generated by tools/gen_dispatch.py: every lifted routine that verified against the original. */
#include "lifted_dispatch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%s
#include "lift_runtime.h"

enum
{
    LIFTED_ARENA_TOP = 0x7f0000,
    LIFTED_ARENA_BOTTOM = 0x7b0000,
    LIFTED_ARENA_GAP = 0x100, /* above a frame: its return slot and the arguments passed on */
    LIFTED_MAX_DEPTH = LIFT_DISPATCH_DEPTH,
    LIFTED_MAX_STACK = %d,
    LIFTED_MAX_ARGUMENTS = 17
};

typedef uint32_t (*LiftedFunction)(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

typedef struct LiftedRoutine
{
    uint32_t address;
    LiftedFunction function;
    uint32_t stack;
    uint32_t arguments;
} LiftedRoutine;

void (*vertrix_lifted_after_hook)(uint32_t target, uint32_t eax);

static const LiftedRoutine routines[] = {
%s
};

/* Lifted routines that did not pass the differential oracle. Used only after
 * vertrix_lifted_allow_unverified(1). */
static const LiftedRoutine unverified_routines[] = {
    {0, NULL, 0, 0},
%s
};

static unsigned depth;
static uint32_t arena[LIFTED_MAX_DEPTH + 1] = {LIFTED_ARENA_TOP};
static int unverified_allowed;
static int trace_enabled;

unsigned vertrix_lifted_depth(void)
{
    return depth;
}

static int find_compare(const void *key, const void *item)
{
    uint32_t address = *(const uint32_t *)key;
    uint32_t other = ((const LiftedRoutine *)item)->address;
    return address < other ? -1 : address > other;
}

/* Debugging: routines the dispatcher must pretend not to have (zero terminated). */
uint32_t vertrix_lifted_skip[8];

/* The lookups repeat for the same targets (the float helpers run for every sample the MP3
 * decoder produces): a direct-mapped cache of each target's routine (or of its absence) keeps
 * them off bsearch. vertrix_lifted_allow_unverified clears it. */
static struct
{
    uint32_t target;
    const LiftedRoutine *routine;
} find_cache[4096];

static const LiftedRoutine *find(uint32_t target)
{
    unsigned skip, slot = (target ^ (target >> 12)) & 4095u;
    const LiftedRoutine *found;
    for (skip = 0; skip < 8 && vertrix_lifted_skip[skip] != 0; skip++)
    {
        if (vertrix_lifted_skip[skip] == target)
        {
            return NULL;
        }
    }
    if (find_cache[slot].target == target && target != 0)
    {
        return find_cache[slot].routine;
    }
    found = bsearch(&target, routines, sizeof routines / sizeof routines[0], sizeof routines[0],
                    find_compare);
    if (found == NULL && unverified_allowed)
    {
        found = bsearch(&target, unverified_routines + 1,
                        sizeof unverified_routines / sizeof unverified_routines[0] - 1,
                        sizeof unverified_routines[0], find_compare);
    }
    find_cache[slot].target = target;
    find_cache[slot].routine = found;
    return found;
}

void vertrix_lifted_allow_unverified(int allowed)
{
    unverified_allowed = allowed;
    memset(find_cache, 0, sizeof find_cache);
}

void vertrix_lifted_set_trace(int enabled)
{
    trace_enabled = enabled;
}

unsigned vertrix_lifted_count(void)
{
    return (unsigned)(sizeof routines / sizeof routines[0]);
}

int vertrix_lifted_has(uint32_t target)
{
    return find(target) != NULL;
}

static uint32_t lifted_call(VertrixCallSite *site, void *context);

VertrixLiftedFunction vertrix_lifted_function(const VertrixCalls *calls, uint32_t target,
                                              unsigned *index)
{
    const LiftedRoutine *routine = calls->call == lifted_call ? find(target) : NULL;
    if (routine == NULL || depth >= LIFTED_MAX_DEPTH || trace_enabled ||
        vertrix_lifted_after_hook != NULL ||
        arena[depth] - routine->stack - LIFTED_ARENA_GAP < LIFTED_ARENA_BOTTOM)
    {
        return NULL;
    }
    *index = depth;
    return routine->function;
}

int vertrix_lifted_dispatch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const VertrixCallSite *site,
                            uint32_t *result)
{
    static const uint8_t zero[LIFTED_MAX_STACK];
    const LiftedRoutine *routine = find(site->target);
    uint32_t arguments[LIFTED_MAX_ARGUMENTS]; /* every one set below */
    LiftEntry entry;
    unsigned i;
    if (routine == NULL || depth >= LIFTED_MAX_DEPTH ||
        arena[depth] - routine->stack - LIFTED_ARENA_GAP < LIFTED_ARENA_BOTTOM)
    {
        return 0;
    }
    arguments[0] = site->stack;
    arguments[1] = site->stack_next;
    arguments[2] = site->stack_third;
    for (i = 0; i < 14; i++)
    {
        arguments[3 + i] = site->stack_rest[i];
    }
    entry.chain = vertrix_lift_chain; /* every other field is set below */
    entry.eax = site->eax;
    entry.edx = site->edx;
    entry.ebx = site->ebx;
    entry.ecx = site->ecx;
    entry.esi = vertrix_lift_in_esi;
    entry.edi = vertrix_lift_in_edi;
    entry.ebp = vertrix_lift_in_ebp;
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    /* Each frame's emulated stack lies just below its caller's (the arena descends from
     * LIFTED_ARENA_TOP); a frame larger than the old fixed 0x4000 step fits as well. */
    entry.esp = arena[depth];
    arena[depth + 1] = (entry.esp - routine->stack - LIFTED_ARENA_GAP) & ~15u;
    entry.arguments = arguments;
    entry.passed = LIFTED_MAX_ARGUMENTS;
    entry.garbage = zero;
    if (trace_enabled)
    {
        printf("%%*s%%x eax=%%x edx=%%x ebx=%%x ecx=%%x\\n", (int)depth * 2, "", (unsigned)site->target,
               (unsigned)site->eax, (unsigned)site->edx, (unsigned)site->ebx, (unsigned)site->ecx);
    }
    /* A lifted routine registers its frame in lift_begin. The native ports have none, so the slot
     * is cleared first: the host must not read through a frame that has returned. */
    vertrix_lift_frame_index = depth;
    if (depth < LIFT_FRAME_LIMIT)
    {
        vertrix_lift_frames[depth] = NULL;
    }
    depth++;
    *result = routine->function(calls, services, globals, &entry);
    depth--;
    if (depth < LIFT_FRAME_LIMIT)
    {
        vertrix_lift_frames[depth] = NULL;
    }
    if (vertrix_lifted_after_hook != NULL)
    {
        vertrix_lifted_after_hook(site->target, site->eax);
    }
    return 1;
}

static uint32_t lifted_call(VertrixCallSite *site, void *context)
{
    VertrixLiftedCalls *adapter = context;
    uint32_t result;
    if (vertrix_lifted_dispatch(&adapter->calls, adapter->services, adapter->globals, site,
                                &result))
    {
        return result;
    }
    return adapter->inner->call(site, adapter->inner->context);
}

void vertrix_lifted_calls_init(VertrixLiftedCalls *adapter, const VertrixCalls *inner,
                               const VertrixFactoryServices *services,
                               const VertrixGlobals *globals)
{
    adapter->calls.call = lifted_call;
    adapter->calls.context = adapter;
    adapter->inner = inner;
    adapter->services = services;
    adapter->globals = globals;
}
''' % ('\n'.join('#include "%s"' % h for h in headers + ['native_dispatch.h']), maximum, '\n'.join(rows), '\n'.join(unverified_rows)))
subprocess.run(['clang-format', '-i', str(ROOT / 'source' / 'lifted_dispatch.c'),
                str(ROOT / 'source' / 'lifted_dispatch.h')], check=True)
print(len(rows), 'routines, max stack', maximum)
