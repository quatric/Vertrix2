#include <string.h>
#include <stdio.h>
#include "jpeg_decode.h"
#include <time.h>
/* Host experiment: build the title screen with the lifted routines, then run the original's
 * frame (0x4b6200 updates, 0x4b6240 depth-sorted draws) over the scene list 0x54671c and print
 * the calls that reach the platform boundary. usage: host_title IMAGE.bin [frames] */
#include "palette_tables.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#include "lift_host.h"
#include "lift_runtime.h"
#include "lift_imports.h"

static uint8_t original[LIFT_HOST_IMAGE_SIZE];
static uint8_t image[LIFT_HOST_IMAGE_SIZE];
static uint8_t heap[0x10000000];

static void host_store(LiftHost *host, uint32_t address, uint32_t value)
{
    unsigned i;
    for (i = 0; i < 4; i++)
    {
        if (address >= LIFT_HOST_HEAP_BASE) host->heap[address - LIFT_HOST_HEAP_BASE + i] = (uint8_t)(value >> (8 * i)); else host->image[address - LIFT_HOST_IMAGE_BASE + i] = (uint8_t)(value >> (8 * i));
    }
}

static LiftHost *current_host;
static uint32_t g_form;

static void on_alarm(int signal)
{
    unsigned i;
    (void)signal;
    printf("TIMEOUT: %u boundary calls so far\n", current_host->boundary_calls);
    for (i = 0; i < current_host->boundary_distinct; i++)
    {
        printf("  boundary %06x x%u\n", current_host->boundary_targets[i],
               current_host->boundary_counts[i]);
    }
    {
        uint32_t o = lift_host_read(current_host, 0x544070, 4), k;
        printf("obj %x names:", (unsigned)o);
        for (k = 0; k < 40; k++) printf(" %02x", (unsigned)lift_host_read(current_host, o + k, 1));
        printf("\n+104:");
        for (k = 0; k < 40; k++) printf(" %02x", (unsigned)lift_host_read(current_host, o + 0x104 + k, 1));
        printf("\n");
    }
    _exit(3);
}

static void report(const char *what, const LiftHost *host, uint32_t result)
{
    { static clock_t last; clock_t now = clock(); if (getenv("TIMES")) printf("[%s took %.2fs]\n", what, (double)(now - last) / CLOCKS_PER_SEC); last = now; }
    unsigned i;
    printf("%s: result %x, %u boundary calls, heap %x\n", what, result, host->boundary_calls,
           host->heap_top);
    for (i = 0; i < host->boundary_distinct; i++)
    {
        printf("  boundary %06x x%u %s\n", host->boundary_targets[i], host->boundary_counts[i], vertrix_import_name(host->boundary_targets[i]) ? vertrix_import_name(host->boundary_targets[i]) : "");
    }
}

static void host_store2(LiftHost *h, uint32_t a, int v) { h->image[a - LIFT_HOST_IMAGE_BASE] = (uint8_t)v; h->image[a - LIFT_HOST_IMAGE_BASE + 1] = (uint8_t)(v >> 8); }
static void host_write_dword(LiftHost *h, uint32_t a, uint32_t v) { unsigned i; for (i = 0; i < 4; i++) { uint8_t b = (uint8_t)(v >> (8 * i)); if (a >= LIFT_HOST_HEAP_BASE) h->heap[a - LIFT_HOST_HEAP_BASE + i] = b; else h->image[a - LIFT_HOST_IMAGE_BASE + i] = b; } }


extern uint32_t vertrix_debug_watch;
static LiftHost *g_hook_host;
static unsigned g_hook_last, g_hook_on;
static unsigned lit_target(void)
{
    uint32_t wr = lift_host_read(g_hook_host, 0x558c7c, 4), px = lift_host_read(g_hook_host, wr, 4), n = lift_host_read(g_hook_host, wr + 4, 4) * lift_host_read(g_hook_host, wr + 8, 4), q, lit = 0;
    for (q = 0; q < n; q++) if (lift_host_read(g_hook_host, px + 4 * q, 4)) lit++;
    return lit;
}
static void after_hook(uint32_t target, uint32_t eax)
{
    if (g_hook_on && getenv("HOOKW")) { { static uint32_t ring[16], rn; ring[rn++ % 16] = target; if (g_hook_host && lift_host_read(g_hook_host, 0x15440b0 + 4, 4) != 640 && !getenv("RINGDONE")) { unsigned q; fprintf(stderr, "ring:"); for (q = 0; q < 16; q++) fprintf(stderr, " %x", ring[(rn + q) % 16]); fprintf(stderr, "\n"); setenv("RINGDONE", "1", 1); } } static uint32_t lw = 640; uint32_t w = lift_host_read(g_hook_host, 0x15440b0 + 4, 4); if (w != lw) { fprintf(stderr, "width %u -> %u after %x eax=%x\n", lw, w, target, eax); lw = w; } return; }
    if (g_hook_on && getenv("HOOK478")) { if (target == 0x478d10 || target == 0x47ce10 || target == 0x482f80 || target == 0x483ed0 || target == 0x48ac50) fprintf(stderr, "ret %x eax=%x\n", target, eax); return; }
    if (g_hook_on && getenv("HOOKV")) fprintf(stderr, "hook %x\n", target);
    if (!g_hook_on || (!getenv("HOOKALL") && target != 0x4ae0f0 && target != 0x4af560 && target != 0x4ae3e0 && target != 0x4ae140)) return;
    if (getenv("HOOK478") && target == 0x478d10) fprintf(stderr, "created surface %x\n", eax);
    { unsigned lit = lit_target(); if (lit != g_hook_last) { fprintf(stderr, "HOOK after %x eax=%x: lit %u -> %u\n", target, eax, g_hook_last, lit); g_hook_last = lit; } }
}
int main(int argc, char **argv)
{
    FILE *file;
    signal(SIGALRM, on_alarm);
    alarm(getenv("ALARM") ? atoi(getenv("ALARM")) : 20);
    setvbuf(stdout, NULL, _IOLBF, 0);
    LiftHost host;
    int lifted, frame, frames = argc > 2 ? atoi(argv[2]) : 1;
    uint32_t result, surface, pixels, wrapper;
    if (argc < 2 || (file = fopen(argv[1], "rb")) == NULL || fread(original, 1, sizeof original, file) == 0)
    {
        fprintf(stderr, "usage: host_title IMAGE.bin [frames]\n");
        return 2;
    }
    fclose(file);
    lift_host_init(&host, image, original, heap, sizeof heap);
    current_host = &host;
    host.decode_jpeg = jpeg_decode;
    host.archive = vertrix_vf_open(getenv("VF") ? getenv("VF") : "hardware-check/Vertrix2.vf");
    if (host.archive == NULL) { fprintf(stderr, "no archive\n"); return 2; }
    vertrix_lifted_allow_unverified(1);
    if (getenv("VSKIP")) { extern uint32_t vertrix_lifted_skip[8]; char *sp = getenv("VSKIP"); unsigned si = 0; while (*sp && si < 7) { vertrix_lifted_skip[si++] = (uint32_t)strtoul(sp, &sp, 16); while (*sp == ',') sp++; } }
    if (getenv("THELP"))
    {
        FILE *in = fopen("/tmp/helpers.txt", "r");
        unsigned t, a, d, b, c;
        while (in && fscanf(in, "%u %u %u %u %u", &t, &a, &d, &b, &c) == 5)
        {
            VertrixCallSite site;
            uint32_t res;
            memset(&site, 0, sizeof site);
            site.target = t; site.eax = a; site.edx = d; site.ebx = b; site.ecx = c;
            vertrix_lift_edx = d;
            res = host.calls.calls.call(&site, host.calls.calls.context);
            printf("%u %u %u %u %u %u %u %u %u %u %u\n", t, a, d, b, c, res, vertrix_lift_edx, vertrix_lift_fl.zf, vertrix_lift_fl.sf, vertrix_lift_fl.cf, vertrix_lift_fl.of);
        }
        return 0;
    }
    if (getenv("T474560"))
    {
        static const uint32_t cases[5][3] = {{100,50,20},{255,0,0},{10,10,10},{0,200,100},{252,128,64}};
        uint32_t scratch = lift_host_allocate(&host, 0x1000), k;
        for (k = 0; k < 5; k++)
        {
            VertrixCallSite site;
            uint32_t res;
            memset(&site, 0, sizeof site);
            site.target = 0x474560;
            site.eax = cases[k][0]; site.edx = cases[k][1]; site.ebx = cases[k][2];
            site.ecx = scratch; site.stack = scratch + 0x100; site.stack_next = scratch + 0x200;
            res = host.calls.calls.call(&site, host.calls.calls.context);
            printf("%u %u %u eax %x out1 %04x %04x %04x out2 %x %x\n", cases[k][0], cases[k][1], cases[k][2], res, lift_host_read(&host, scratch + 0x100, 2), lift_host_read(&host, scratch + 0x102, 2), lift_host_read(&host, scratch + 0x104, 2), lift_host_read(&host, scratch + 0x200, 4), lift_host_read(&host, scratch + 0x204, 4));
        }
        report("t474560", &host, 0);
        return 0;
    }
    if (getenv("T474910"))
    {
        uint32_t e, scratch = lift_host_allocate(&host, 0x1000);
        if (getenv("T474CD0"))
        {
            FILE *o; uint8_t b[20301];
            lift_host_run(&host, 0x474cd0, 0, 0, 0, 0, &lifted);
            for (e = 0; e < 20301; e++) b[e] = (uint8_t)lift_host_read(&host, 0x5468b0 + e, 1);
            o = fopen("/tmp/host_channels.bin", "wb"); fwrite(b, 1, sizeof b, o); fclose(o);
            return 0;
        }
        {
            static const uint32_t cases[3][3] = {{0, 1, 1}, {0, 2, 1}, {0, 1, 2}};
            unsigned k, g;
            for (k = 0; k < 3; k++)
            {
                VertrixCallSite site;
                memset(&site, 0, sizeof site);
                site.target = 0x474910;
                site.eax = cases[k][0]; site.edx = cases[k][1]; site.ebx = cases[k][2];
                site.ecx = scratch; site.stack = scratch + 0x100; site.stack_next = scratch + 0x200;
                host.calls.calls.call(&site, host.calls.calls.context);
                printf("%u %u %u byte %x:", cases[k][0], cases[k][1], cases[k][2], lift_host_read(&host, scratch + 0x100, 4));
                for (g = 0x54687c; g < 0x5468b0; g += 4) printf(" %x", lift_host_read(&host, g, 4));
                printf("\n");
            }
        }
        report("t474910", &host, 0);
        return 0;
    }
    if (getenv("MASTER"))
    {
        uint32_t form = lift_host_allocate(&host, 0x1000);
        g_form = form;
        uint32_t display = lift_host_allocate(&host, 0x800);
        host_store(&host, 0x544070, display);
        if (getenv("TRACE")) vertrix_lifted_set_trace(1);
        lift_host_run(&host, 0x4df307, 0, 0, 0, 0, &lifted); /* RTL thread-variable block */
        lift_host_run(&host, 0x475660, 0, 0, 0, 0, &lifted); /* input unit initialization */
        printf("4df307: [5c5c54] = %x (lifted %d)\n", (unsigned)lift_host_read(&host, 0x5c5c54, 4), lifted);
        result = lift_host_run(&host, 0x41a080, form, 0, 0, 0, &lifted);
        report("startup 41a080", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x41a540, form, 0, 0, 0, &lifted);
        report("load 41a540", &host, result);
        vertrix_lifted_set_trace(0);
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);
        report("load banks 45dca0", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
    }
    else
    {
        uint32_t display = lift_host_allocate(&host, 0x800);
        host_store(&host, 0x544070, display);
        result = lift_host_run(&host, 0x484b60, 0x5b9c50, 0, 0x14, 0, &lifted);
        report("display init 484b60", &host, result);
        { unsigned k; for (k = 0; k < 0x100; k += 4) { if (k % 32 == 0) printf("\n%x:", 0x5b9c50 + k); printf(" %x", lift_host_read(&host, 0x5b9c50 + k, 4)); } printf("\n"); }
        printf("display object: +60 %x +64 %x +68 %x +6c %x primary %x bits %u\n", lift_host_read(&host, 0x5b9c50 + 0x60, 4),
               lift_host_read(&host, 0x5b9c50 + 0x64, 4), lift_host_read(&host, 0x5b9c50 + 0x68, 4),
               lift_host_read(&host, 0x5b9c50 + 0x6c, 4), host.primary_surface, host.display_bits);
        host.boundary_calls = host.boundary_distinct = 0;
    }
    if (!getenv("MASTER"))
    {
        result = lift_host_run(&host, 0x413bd0, 0, 0, 0, 0, &lifted);
        report("init tables 413bd0", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x45dca0, 0, 0, 0, 0, &lifted);
        report("load banks 45dca0", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
    }
    if (getenv("TICKS"))
    {
        unsigned n = (unsigned)atoi(getenv("TICKS")), t;
        printf("form %x: +bc=%x +c0=%x +b8=%x\n", g_form, lift_host_read(&host, g_form + 0xbc, 4), lift_host_read(&host, g_form + 0xc0, 4), lift_host_read(&host, g_form + 0xb8, 4));
        { unsigned i; printf("bg idx %u %u %u; table:", lift_host_read(&host,0x53bd08,1), lift_host_read(&host,0x513c18,1), lift_host_read(&host,0x513c19,1)); for (i = 0; i < 6; i++) { uint32_t sp = lift_host_read(&host, 0x5334a0 + 4 * i, 4); char b[40]; unsigned q; for (q = 0; q < 39 && (b[q] = (char)lift_host_read(&host, sp + q, 1)); q++) {} b[q] = 0; printf(" %x:'%s'", sp, b); } printf("\n"); }
        printf("idle: [5328b4]=%x [5328b8]=%x [5328bc]=%x\n", lift_host_read(&host,0x5328b4,4), lift_host_read(&host,0x5328b8,4), lift_host_read(&host,0x5328bc,4));
        printf("timer: proc %x user %x period %u; [user] = %x; [598db0] = %x\n", host.timer_proc, host.timer_user, host.timer_period, lift_host_read(&host, host.timer_user, 4), lift_host_read(&host, 0x598db0, 4));
        for (t = 0; t < n; t++)
        {
            uint32_t handler = lift_host_read(&host, g_form + 0xbc, 4);
            uint32_t r = 0;
            int ran;
            host.boundary_calls = host.boundary_distinct = 0;
            host.clock_ms += getenv("CLOCKSTEP") ? (uint32_t)atoi(getenv("CLOCKSTEP")) : 14;
            if (getenv("SHOWALL") && t >= (unsigned)atoi(getenv("SHOWALL"))) { uint32_t lst = lift_host_read(&host, 0x54671c + 4, 4), cnt = lift_host_read(&host, 0x54671c + 8, 4), q; for (q = 0; q < cnt; q++) host_write_dword(&host, lift_host_read(&host, lst + 4 * q, 4) + 0x124, 0); }
            if (getenv("KEY") && t >= (unsigned)atoi(getenv("KEYAT") ? getenv("KEYAT") : "100")) { unsigned ph = (t - (unsigned)atoi(getenv("KEYAT") ? getenv("KEYAT") : "100")) % 40, k = (unsigned)strtoul(getenv("KEY"), 0, 0); if (ph == 0) lift_host_key(&host, k, 1); if (ph == 6) lift_host_key(&host, k, 0); }
            { static uint32_t last, lw; uint32_t cur = lift_host_read(&host, 0x558c7c, 4); if (getenv("WATCH7C") && (cur != last || lift_host_read(&host, cur + 4, 4) != lw)) { lw = lift_host_read(&host, cur + 4, 4); { printf("tick %u: [558c7c] %x -> %x (w=%u h=%u)\n", t, last, cur, lift_host_read(&host, cur + 4, 4), lift_host_read(&host, cur + 8, 4)); last = cur; } } }
            if (getenv("WATCHADDR")) vertrix_debug_watch = ((t >= (unsigned)atoi(getenv("WATCHTICK")) && t < (unsigned)atoi(getenv("WATCHTICK")) + (getenv("WATCHLEN") ? (unsigned)atoi(getenv("WATCHLEN")) : 1)) ? (uint32_t)strtoul(getenv("WATCHADDR"), 0, 16) : 0);
            if (getenv("DUMPOBJ") && (t == (unsigned)atoi(getenv("DUMPOBJ")) || t == (unsigned)atoi(getenv("DUMPOBJ")) + 5)) { uint32_t lbase = getenv("DUMPLIST") ? (uint32_t)strtoul(getenv("DUMPLIST"), 0, 16) : 0x54671c; uint32_t lst = lift_host_read(&host, lbase + 4, 4), cnt = lift_host_read(&host, lbase + 8, 4), q, k; printf("DUMP tick %u list n=%u\n", t, cnt); for (q = 0; q < cnt && q < 64; q++) { uint32_t ob = lift_host_read(&host, lst + 4 * q, 4); printf("  obj %x vt=%x x=%d y=%d fr=%u 124=%x 13c=%x 138=%x 110=%u:", ob, lift_host_read(&host, ob, 4), (int16_t)lift_host_read(&host, ob + 0xe, 2), (int16_t)lift_host_read(&host, ob + 0x16, 2), lift_host_read(&host, ob + 0xb8, 4), lift_host_read(&host, ob + 0x124, 4), lift_host_read(&host, ob + 0x13c, 4), lift_host_read(&host, ob + 0x138, 4), lift_host_read(&host, ob + 0x110, 1)); for (k = 0; k < 8; k++) printf(" %x", lift_host_read(&host, ob + 0x118 + 4 * k, 4)); printf("\n"); } }
            if (getenv("SHOW13C") && t >= 100) { uint32_t lb = 0x546730, lst = lift_host_read(&host, lb + 4, 4), cnt = lift_host_read(&host, lb + 8, 4), q; for (q = 0; q < cnt; q++) host_write_dword(&host, lift_host_read(&host, lst + 4 * q, 4) + 0x124, 0); }
            if (getenv("SHOW13C") && t >= 100) { uint32_t lb = 0x546744, lst = lift_host_read(&host, lb + 4, 4), cnt = lift_host_read(&host, lb + 8, 4), q; for (q = 0; q < cnt; q++) host_write_dword(&host, lift_host_read(&host, lst + 4 * q, 4) + 0x124, 0); }
            if (getenv("DUMPTAB") && t == (unsigned)atoi(getenv("DUMPTAB"))) { unsigned q; for (q = 0; q < 54; q++) { uint32_t sp = lift_host_read(&host, 0x5334a0 + 4 * q, 4), sp2 = lift_host_read(&host, 0x533578 + 4 * q, 4); char b[64] = {0}, c[64] = {0}; unsigned k; for (k = 0; sp && k < 60; k++) { b[k] = (char)lift_host_read(&host, sp + k, 1); if (!b[k]) break; } for (k = 0; sp2 && k < 60; k++) { c[k] = (char)lift_host_read(&host, sp2 + k, 1); if (!c[k]) break; } printf("tab %u: %x '%s' | %x '%s'\n", q, sp, b, sp2, c); } }
            if (getenv("DUMPSLOT") && t >= 148 && t <= 175) { unsigned q; fprintf(stderr, "slot t%u:", t); for (q = 0; q < 0x5c; q += 4) fprintf(stderr, " %x", (unsigned)lift_host_read(&host, (getenv("SLOTBASE") ? (uint32_t)strtoul(getenv("SLOTBASE"),0,16) : 0x5501c0) + q, 4)); fprintf(stderr, " | mouse %x %x %x\n", (unsigned)lift_host_read(&host, 0x558944, 4), (unsigned)lift_host_read(&host, 0x558958, 4), (unsigned)lift_host_read(&host, 0x5588f8+0x38, 4)); }
            if (getenv("DUMPACT") && t == (unsigned)atoi(getenv("DUMPACT"))) { uint32_t n = lift_host_read(&host, 0x546724, 4), arr = lift_host_read(&host, 0x546720, 4), q; fprintf(stderr, "mouse x %d y %d\n", (int)lift_host_read(&host, 0x5588f8 + 0x48, 2), (int)lift_host_read(&host, 0x5588f8 + 0x4a, 2)); fprintf(stderr, "actors %u:", (unsigned)n); for (q = 0; q < n; q++) { uint32_t a = lift_host_read(&host, arr + 4 * q, 4); fprintf(stderr, " [%x t%x h%x]", (unsigned)a, (unsigned)lift_host_read(&host, a + 0x14c, 4), (unsigned)lift_host_read(&host, a + 0x154, 4)); } fprintf(stderr, "\n"); }
            if (getenv("MSCAN") && t >= 320 && (t - 320) % 40 == 0) { static int cx = 320, cy = 240; char *sc = strdup(getenv("MSCAN")), *tok = sc; unsigned idx = (t - 320) / 40, q = 0; while (tok && q < idx) { tok = strchr(tok, ','); if (tok) tok++; q++; } if (tok && *tok) { int x = atoi(tok), y = atoi(strchr(tok, ':') + 1); host_store2(&host, 0x5588f8 + 0x48, x); host_store2(&host, 0x5588f8 + 0x4a, y); cx = x; cy = y; fprintf(stderr, "scan move %d %d at tick %u\n", x, y, t); } free(sc); }
            if (getenv("CALLADDR") && t == (unsigned)atoi(getenv("CALLAT"))) { int ok2; uint32_t rr = lift_host_run(&host, (uint32_t)strtoul(getenv("CALLADDR"), 0, 16), g_form, 0, 0, 0, &ok2); printf("called %s -> %x lifted %d\n", getenv("CALLADDR"), rr, ok2); }
            if (getenv("MCLICK") && t >= (unsigned)atoi(getenv("MCLICKAT") ? getenv("MCLICKAT") : "150")) { unsigned ph = (t - (unsigned)atoi(getenv("MCLICKAT") ? getenv("MCLICKAT") : "150")) % 40; if (ph == 0 && t == (unsigned)atoi(getenv("MCLICKAT") ? getenv("MCLICKAT") : "150") && getenv("MDX")) { lift_host_mouse(&host, 0, atoi(getenv("MDX"))); lift_host_mouse(&host, 4, atoi(getenv("MDY"))); } if (getenv("MAT3") && t == (unsigned)atoi(getenv("MAT3"))) { lift_host_mouse(&host, 0, atoi(getenv("MDX3"))); lift_host_mouse(&host, 4, atoi(getenv("MDY3"))); } if (ph == 0 && t > (unsigned)atoi(getenv("MCLICKAT") ? getenv("MCLICKAT") : "150") && t <= 230 && getenv("MDY2")) lift_host_mouse(&host, 4, atoi(getenv("MDY2"))); if (ph == 2) lift_host_mouse(&host, 12, 0x80); if (ph == (getenv("MHOLD") ? (unsigned)atoi(getenv("MHOLD")) : 8)) lift_host_mouse(&host, 12, 0); }
            if (getenv("VTDUMP") && t == (unsigned)atoi(getenv("VTDUMP"))) { uint32_t lbs[3] = {0x54671c, 0x546744, 0x546730}, li; for (li = 0; li < 3; li++) { uint32_t lst = lift_host_read(&host, lbs[li] + 4, 4), cnt = lift_host_read(&host, lbs[li] + 8, 4), q, k; for (q = 0; q < cnt && q < 6; q++) { uint32_t ob = lift_host_read(&host, lst + 4 * q, 4), vt = lift_host_read(&host, ob + 0x158, 4); printf("list %u obj %x vtable %x:", li, ob, vt); for (k = 0; k < 8; k++) printf(" %x", lift_host_read(&host, vt + 4 * k, 4)); printf("\n"); } } }
            if (getenv("RAWOBJ") && t == (unsigned)atoi(getenv("RAWOBJ"))) { uint32_t lst = lift_host_read(&host, 0x54671c + 4, 4), cnt = lift_host_read(&host, 0x54671c + 8, 4), q, k; for (q = 0; q < cnt && q < 5; q++) { uint32_t ob = lift_host_read(&host, lst + 4 * q, 4); printf("RAW %x:", ob); for (k = 0; k < 0x5c; k++) printf("%s%x", k % 8 == 0 ? "\n  " : " ", lift_host_read(&host, ob + 4 * k, 4)); printf("\n"); } }
            if (getenv("ACTIVE") && t == 1) host_write_dword(&host, 0x5328bc, 1);
            if (getenv("UNHIDE") && t >= (unsigned)atoi(getenv("UNHIDE"))) host_write_dword(&host, 0x5bb710, 0);
            if (getenv("REQ") && t == (unsigned)atoi(getenv("REQAT") ? getenv("REQAT") : "100")) { uint32_t v = (uint32_t)strtoul(getenv("REQ"), 0, 0); host_write_dword(&host, 0x532a4c, v); }
            if (getenv("HOOKAT") && t == (unsigned)atoi(getenv("HOOKAT"))) { g_hook_host = &host; g_hook_last = lit_target(); g_hook_on = 1; vertrix_lifted_after_hook = after_hook; }
            if (getenv("HOOKAT") && t == (unsigned)atoi(getenv("HOOKAT")) + (getenv("HOOKLEN") ? (unsigned)atoi(getenv("HOOKLEN")) : 1)) g_hook_on = 0;
            if (getenv("TRACEFROM") && t == (unsigned)atoi(getenv("TRACEFROM"))) vertrix_lifted_set_trace(1);
            if (host.timer_proc && getenv("TIMERTICK")) { unsigned k, per = host.timer_period ? host.timer_period : 10, cs = getenv("CLOCKSTEP") ? (unsigned)atoi(getenv("CLOCKSTEP")) : 14; int ok; for (k = 0; k < cs / per; k++) lift_host_run(&host, 0x4b7b80, 0, 0, 0, 0, &ok); }
            { clock_t c0 = clock(); r = lift_host_run(&host, handler, g_form, 0, 0, 0, &ran); if (getenv("TICKTIME") && (double)(clock() - c0) / CLOCKS_PER_SEC > 0.2) printf("tick %u handler %x took %.2fs\n", t, handler, (double)(clock() - c0) / CLOCKS_PER_SEC); }
            if (getenv("TRACEFROM") && t == (unsigned)atoi(getenv("TRACEFROM"))) { vertrix_lifted_set_trace(0); return 0; }
            { static uint32_t last_handler; if (handler != last_handler) { printf("tick %u: handler change %x -> frames %u pixels?\n", t, handler, host.frames_presented); fflush(stdout); last_handler = handler; } }
            if (getenv("TICKLOG") || t < 3 || !ran) printf("tick %u: handler %x %s -> %x, next %x, %u boundary calls\n", t, handler, ran ? "lifted" : "MISSING", r, lift_host_read(&host, g_form + 0xbc, 4), host.boundary_calls);
            if (!ran) break;
            if (host.boundary_calls) report("tick", &host, 0);
        }
        { uint32_t w, h, pitch, bytes, base = lift_host_surface(&host, host.primary_surface, &w, &h, &pitch, &bytes), k, nz = 0;
          FILE *o = fopen(getenv("PPM") ? getenv("PPM") : "/tmp/ticks.ppm", "wb");
          fprintf(o, "P6\n%u %u\n255\n", w, h);
          for (k = 0; k < w * h; k++) { uint32_t v = lift_host_read(&host, base + 4 * k, 4); if (v) nz++; fputc((v >> 16) & 255, o); fputc((v >> 8) & 255, o); fputc(v & 255, o); }
          fclose(o);
          g_hook_host = &host; printf("front target lit %u\n", lit_target());
          printf("kbd struct 55608c: +0=%x +4=%x +8=%x +c=%x +10=%x\n", lift_host_read(&host,0x55608c,4), lift_host_read(&host,0x556090,4), lift_host_read(&host,0x556094,4), lift_host_read(&host,0x556098,4), lift_host_read(&host,0x55609c,4));
          printf("flags 5328bc=%x 55608c=%x 5588f8=%x\n", lift_host_read(&host,0x5328bc,4), lift_host_read(&host,0x55608c,4), lift_host_read(&host,0x5588f8,4));
          printf("screen cur %x req %x [5bb710]=%x [5328b4]=%x\n", lift_host_read(&host,0x532a4c,4), lift_host_read(&host,0x532a98,4), lift_host_read(&host,0x5bb710,4), lift_host_read(&host,0x5328b4,4));
          { uint32_t t = lift_host_read(&host, 0x558c7c, 4); printf("target %x: +0 %x +4 %u +8 %u +c %x +d %x +10 %x +14 %x\n", t, lift_host_read(&host,t,4), lift_host_read(&host,t+4,4), lift_host_read(&host,t+8,4), lift_host_read(&host,t+0xc,1), lift_host_read(&host,t+0xd,1), lift_host_read(&host,t+0x10,4), lift_host_read(&host,t+0x14,4)); }
          { uint32_t d = lift_host_read(&host, 0x544070, 4); printf("display %x: 208=%u 20c=%u 214=%u 216=%u 226=%u 268=%x 270=%x 274=%x\n", d, lift_host_read(&host,d+0x208,2), lift_host_read(&host,d+0x20c,2), lift_host_read(&host,d+0x214,2), lift_host_read(&host,d+0x216,2), lift_host_read(&host,d+0x226,2), lift_host_read(&host,d+0x268,4), lift_host_read(&host,d+0x270,4), lift_host_read(&host,d+0x274,4)); }
          { uint32_t list[] = {0x15440b0, 0x16705b0, 0x1670540, 0x16bb5d0, 0x2d3cb90, 0x259f450 - 0x30, 0x1706710, 0x27eaa90}, gi; for (gi = 0; gi < 8; gi++) { uint32_t t = list[gi]; printf("fmt surface %x: w=%u h=%u +c=%u +d=%u\n", t, lift_host_read(&host,t+4,4), lift_host_read(&host,t+8,4), lift_host_read(&host,t+0xc,1), lift_host_read(&host,t+0xd,1)); } }
          printf("surfaces: primary %x back %x bgobj-surface %x\n", host.primary_surface, host.back_surface, lift_host_read(&host, lift_host_read(&host, 0x544070, 4) + 0x268, 4));
          { uint32_t wr = lift_host_read(&host, 0x5bc010, 4), px = lift_host_read(&host, wr, 4), ww = lift_host_read(&host, wr + 4, 4), wh = lift_host_read(&host, wr + 8, 4), q, nzw = 0;
            for (q = 0; q < ww * wh; q++) if (lift_host_read(&host, px + 4 * q, 4)) nzw++;
            printf("render target %x: %ux%u px %x lit %u; scenes n=%u\n", wr, ww, wh, px, nzw, lift_host_read(&host, 0x54671c + 8, 4)); }
          { uint32_t lst = lift_host_read(&host, 0x54671c + 4, 4), cnt = lift_host_read(&host, 0x54671c + 8, 4), q;
            for (q = 0; q < cnt; q++) { uint32_t o = lift_host_read(&host, lst + 4 * q, 4);
              { uint32_t im = lift_host_read(&host, o + 0xb4, 4); if (im && getenv("IMGSTAT")) { uint32_t px=lift_host_read(&host,im,4),w=lift_host_read(&host,im+4,4),h=lift_host_read(&host,im+8,4),q,a=0,nz=0; for(q=0;q<w*h&&q<200000;q++){uint32_t v=lift_host_read(&host,px+4*q,4); a+=(v>>24)!=0; nz+=v!=0;} printf("imgstat %x %ux%u alpha-nz=%u nz=%u first=%x\n",im,w,h,a,nz,lift_host_read(&host,px,4)); } printf("pos obj %x: x=%d y=%d z1e=%d img+0=%x w=%u h=%u 4e=%u 8e=%u 93=%u\n", o, (int16_t)lift_host_read(&host,o+0xe,2), (int16_t)lift_host_read(&host,o+0x16,2), (int16_t)lift_host_read(&host,o+0x1e,2), im ? lift_host_read(&host,im,4) : 0, im ? lift_host_read(&host,im+4,4) : 0, im ? lift_host_read(&host,im+8,4) : 0, lift_host_read(&host,o+0x4e,1), lift_host_read(&host,o+0x8e,1), lift_host_read(&host,o+0x93,1)); }
              printf("draw obj %x: 13c=%x 110=%x bank=%x img=%x frame=%x vt=%x 120=%x 124=%x 128=%x 12c=%x 130=%x 138=%x 146=%x 148=%x\n", o, lift_host_read(&host,o+0x13c,4), lift_host_read(&host,o+0x110,1), lift_host_read(&host,o+0xb0,4), lift_host_read(&host,o+0xb4,4), lift_host_read(&host,o+0xb8,4), lift_host_read(&host,o+0x158,4), lift_host_read(&host,o+0x120,4), lift_host_read(&host,o+0x124,4), lift_host_read(&host,o+0x128,4), lift_host_read(&host,o+0x12c,4), lift_host_read(&host,o+0x130,4), lift_host_read(&host,o+0x138,4), lift_host_read(&host,o+0x146,4), lift_host_read(&host,o+0x148,2)); } }
          { uint32_t g[4] = {0x558c7c, 0x558c80, 0x558c84, 0x558c88}, gi;
            for (gi = 0; gi < 4; gi++) { uint32_t wr = lift_host_read(&host, g[gi], 4), px = lift_host_read(&host, wr, 4), ww = lift_host_read(&host, wr + 4, 4), wh = lift_host_read(&host, wr + 8, 4), q, nzw = 0;
              if (ww && wh && ww < 4096 && wh < 4096) for (q = 0; q < ww * wh; q++) if (lift_host_read(&host, px + 4 * q, 4)) nzw++;
              printf("global %x -> %x: %ux%u px %x lit %u\n", g[gi], wr, ww, wh, px, nzw); } }
          { uint32_t wr = 0x1706710, px = lift_host_read(&host, wr, 4), ww = lift_host_read(&host, wr + 4, 4), wh = lift_host_read(&host, wr + 8, 4), q, nzw = 0;
            for (q = 0; q < ww * wh && ww < 4096; q++) if (lift_host_read(&host, px + 4 * q, 4)) nzw++;
            printf("loading surface %x: %ux%u lit %u first %x mid %x\n", wr, ww, wh, nzw, lift_host_read(&host, px, 4), lift_host_read(&host, px + 4 * (ww * wh / 2 + ww / 2), 4)); }
          { uint32_t o = lift_host_read(&host, 0x544070, 4), sf = lift_host_read(&host, o + 0x268, 4), px = lift_host_read(&host, sf, 4), ww = lift_host_read(&host, sf + 4, 4), wh = lift_host_read(&host, sf + 8, 4), q, nzw = 0;
            for (q = 0; q < ww * wh && ww < 4096; q++) if (lift_host_read(&host, px + 4 * q, 4)) nzw++;
            if (getenv("BGDUMP")) { FILE *bf = fopen(getenv("BGDUMP"), "wb"); if (bf) { fprintf(bf, "P6\n%u %u\n255\n", ww, wh); for (q = 0; q < ww * wh; q++) { uint32_t v = lift_host_read(&host, px + 4 * q, 4); fputc((v >> 16) & 255, bf); fputc((v >> 8) & 255, bf); fputc(v & 255, bf); } fclose(bf); } }
            printf("bg obj %x surface %x: %ux%u lit %u; 558c84=%x 5b9c50+? ready\n", o, sf, ww, wh, nzw, lift_host_read(&host, 0x558c84, 4)); }
          printf("state: req %x cur %x; table", lift_host_read(&host, 0x532a4c, 4), lift_host_read(&host, 0x532a98, 4));
          { unsigned q; for (q = 0; q < 20; q++) printf(" %x", lift_host_read(&host, 0x4f7b44 + 4 * q, 4)); printf("\n"); }
          { uint32_t o = lift_host_read(&host, 0x544070, 4); unsigned q; printf("bg fields"); for (q = 0x208; q < 0x22c; q += 2) printf(" %x:%x", q, (unsigned)lift_host_read(&host, o + q, 2)); printf("; disp %x %x\n", (unsigned)lift_host_read(&host, 0x5b9c8e, 2), (unsigned)lift_host_read(&host, 0x5b9c90, 2)); }
          { uint32_t sv[2] = {host.primary_surface, host.back_surface}, gi;
            for (gi = 0; gi < 2; gi++) { uint32_t w, h, pitch, bytes, base = lift_host_surface(&host, sv[gi], &w, &h, &pitch, &bytes), q, nzw = 0;
              for (q = 0; q < w * h; q++) if (lift_host_read(&host, base + 4 * q, 4)) nzw++;
              printf("dd surface %x: %ux%u base %x lit %u\n", sv[gi], w, h, base, nzw); } }
          printf("5bb710 = %x\n", (unsigned)lift_host_read(&host, 0x5bb710, 4));
          printf("after %u ticks: %u lit pixels, frames presented %u, handler now %x\n", n, nz, host.frames_presented, lift_host_read(&host, g_form + 0xbc, 4)); }
        return 0;
    }
    result = lift_host_run(&host, 0x465af0, 0, 0xffffffffu, 0, 0, &lifted);
    report("title build", &host, result);
    surface = lift_host_allocate(&host, 0x20);
    pixels = lift_host_allocate(&host, 640 * 480 * 4);
    host_store(&host, surface + 0, pixels);
    host_store(&host, surface + 4, 640);
    host_store(&host, surface + 8, 480);
    host_store(&host, surface + 0xc, 0x00000004); /* 4 bytes per pixel, sub-format 0 */
    host_store(&host, surface + 0x10, 0);
    host_store(&host, surface + 0x14, 640 * 4);
    {
        uint32_t items = lift_host_read(&host, 0x54671c + 4, 4), n = lift_host_read(&host, 0x54671c + 8, 4), i;
        for (i = 0; i < 6 && i < n; i++)
        {
            uint32_t a = lift_host_read(&host, items + 4 * i, 4);
            printf("actor %u at %x: x %d y %d image(+b4) %x flag(+13c) %x bank(+144) %x vt(+158) %x\n", i, a,
                   (int)(int16_t)lift_host_read(&host, a + 0xe, 2), (int)(int16_t)lift_host_read(&host, a + 0x16, 2),
                   lift_host_read(&host, a + 0xb4, 4), lift_host_read(&host, a + 0x13c, 4),
                   lift_host_read(&host, a + 0x144, 4), lift_host_read(&host, a + 0x158, 4));
        }
    }
    {
        printf("surfaces: primary %x back %x bits %u; display obj +60 %x +64 %x +68 %x +6c %x\n", host.primary_surface, host.back_surface, host.display_bits, lift_host_read(&host, 0x5b9c50 + 0x60, 4), lift_host_read(&host, 0x5b9c50 + 0x64, 4), lift_host_read(&host, 0x5b9c50 + 0x68, 4), lift_host_read(&host, 0x5b9c50 + 0x6c, 4));
        uint32_t w, h, pitch, bytes, base = lift_host_surface(&host, host.back_surface, &w, &h, &pitch, &bytes);
        wrapper = lift_host_allocate(&host, 0x40);
        host_store(&host, wrapper + 0, base);
        host_store(&host, wrapper + 4, w);
        host_store(&host, wrapper + 8, h);
        host_store(&host, wrapper + 0xc, bytes | ((getenv("KIND") ? atoi(getenv("KIND")) : 4) << 8)); /* bytes per pixel; sub-format byte */
        host_store(&host, wrapper + 0x10, 0);
        host_store(&host, wrapper + 0x14, pitch);
        host_store(&host, 0x5bc010, wrapper); /* the current render target */
        printf("wrapper %x: base %x w %u h %u bpp %u pitch %u\n", wrapper, base, w, h, bytes, pitch);
        {
            uint32_t view = lift_host_read(&host, 0x544070, 4);
            host_store(&host, view + 0x208, 640);
            host_store(&host, view + 0x20c, 480);
        }
    }
    printf("tables: 54d5d0=%x 54d5ec=%x 54d5f0=%x\n", lift_host_read(&host,0x54d5d0,4), lift_host_read(&host,0x54d5ec,4), lift_host_read(&host,0x54d5f0,4));
    {
        VertrixPaletteTables ref = {0};
        uint32_t t = lift_host_read(&host, 0x54b800, 4), bad = 0, i, first = 0;
        vertrix_palette_tables_build(&ref);
        for (i = 0; i < 262144; i++)
            if (lift_host_read(&host, t + 4 * i, 4) != ref.lookup[i]) { if (!bad) first = i; bad++; }
        { uint32_t q[5]={0,1,100,5000,200000}; int z; for(z=0;z<5;z++) printf("  [%u] host %x ref %x\n", q[z], lift_host_read(&host,t+4*q[z],4), ref.lookup[q[z]]); }
        { uint32_t cb = 0; for (i = 0; i < 20301; i++) if ((uint8_t)lift_host_read(&host, 0x5468b0 + i, 1) != ref.channels[i]) cb++;
          printf("channel mismatches %u of 20301 (host %x ref %x at 0)\n", cb, lift_host_read(&host, 0x5468b0, 4), *(uint32_t *)ref.channels); }
        printf("palette lookup mismatches %u of 262144 (first %u: host %x ref %x)\n", bad, first, lift_host_read(&host, t + 4 * first, 4), ref.lookup[first]);
    }
    { uint32_t b = 0x188cb20, k, nz = 0; for (k = 0; k < 0x12ea; k++) if (lift_host_read(&host, b + k, 1)) nz++; printf("spr buffer %x nonzero %u first %x %x\n", b, nz, lift_host_read(&host, b, 4), lift_host_read(&host, b + 4, 4)); }
    printf("scene list count %u\n", lift_host_read(&host, 0x54671c + 8, 4));
    for (frame = 0; frame < frames; frame++)
    {
        host.boundary_calls = host.boundary_distinct = 0;
        result = lift_host_run(&host, 0x4b6200, 0x54671c, 0, 0, 0, &lifted);
        report("update", &host, result);
        host.boundary_calls = host.boundary_distinct = 0;
        if (getenv("TRACE_DRAW")) vertrix_lifted_set_trace(1);
        if (getenv("DUMP"))
        {
            FILE *o = fopen("/tmp/dump_image.bin", "wb"); fwrite(image, 1, sizeof image, o); fclose(o);
            o = fopen("/tmp/dump_heap.bin", "wb"); fwrite(heap, 1, 0x2000000, o); fclose(o);
            printf("dumped; wrapper %x\n", wrapper);
        }
        printf("478eb0(w,3,2) = %x\n", lift_host_run(&host, 0x478eb0, wrapper, 3, 2, 0, &lifted));
        printf("pre-draw wrapper: base %x pitch %u bpp %u\n", lift_host_read(&host, wrapper, 4), lift_host_read(&host, wrapper + 0x14, 4), lift_host_read(&host, wrapper + 0xc, 4));
        if (getenv("PERACTOR"))
        {
            uint32_t items = lift_host_read(&host, 0x54671c + 4, 4), n = lift_host_read(&host, 0x54671c + 8, 4), i, k, b = lift_host_read(&host, wrapper, 4);
            printf("[");
            for (i = 0; i < n; i++)
            {
                uint32_t nz = 0;
                if (getenv("TRACEA") && i == (uint32_t)atoi(getenv("TRACEA"))) vertrix_lifted_set_trace(1);
                lift_host_run(&host, 0x4b5550, lift_host_read(&host, items + 4 * i, 4), wrapper, 0, 0, &lifted);
                vertrix_lifted_set_trace(0);
                if (getenv("TRACEA") && i == (uint32_t)atoi(getenv("TRACEA"))) { printf("\n5bb72c=%x\n", lift_host_read(&host, 0x5bb72c, 4)); report("actor", &host, 0); }
                for (k = 0; k < 640 * 480; k++) if (lift_host_read(&host, b + 4 * k, 4)) nz++;
                printf("%u%s", nz, i + 1 < n ? ", " : "");
            }
            printf("]\n");
            return 0;
        }
        result = lift_host_run(&host, 0x4b6240, 0x54671c, wrapper, 0, 0, &lifted);
        vertrix_lifted_set_trace(0);
        report("draw", &host, result);
    }
    {
        uint32_t items = lift_host_read(&host, 0x54671c + 4, 4), n = lift_host_read(&host, 0x54671c + 8, 4), i, with_image = 0;
        for (i = 0; i < n; i++)
        {
            uint32_t a = lift_host_read(&host, items + 4 * i, 4);
            with_image += lift_host_read(&host, a + 0xb4, 4) != 0;
            if (i < 4 || (i > 40 && i < 44))
            {
                printf("after: actor %u x %d y %d image %x token(+144) %x frame(+1e) %d kind(+94) %u vt %x\n", i,
                       (int)(int16_t)lift_host_read(&host, a + 0xe, 2), (int)(int16_t)lift_host_read(&host, a + 0x16, 2),
                       lift_host_read(&host, a + 0xb4, 4), lift_host_read(&host, a + 0x144, 4),
                       (int)(int16_t)lift_host_read(&host, a + 0x1e, 2), lift_host_read(&host, a + 0x94, 1),
                       lift_host_read(&host, a + 0x158, 4));
            }
        }
        printf("%u of %u actors have an image\n", with_image, n);
    }
    {
        uint32_t w, h, pitch, bytes, base = lift_host_surface(&host, host.back_surface, &w, &h, &pitch, &bytes);
        unsigned painted = 0, x, y;
        FILE *out = fopen("/tmp/title.ppm", "wb");
        if (out != NULL)
        {
            fprintf(out, "P6\n%u %u\n255\n", w, h);
        }
        for (y = 0; base != 0 && y < h; y++)
        {
            for (x = 0; x < w; x++)
            {
                uint32_t p = lift_host_read(&host, base + y * pitch + x * bytes, bytes);
                painted += (p & 0xffffff) != 0;
                if (out != NULL)
                {
                    fputc(bytes == 4 ? (p >> 16) & 255 : p & 255, out);
                    fputc(bytes == 4 ? (p >> 8) & 255 : p & 255, out);
                    fputc(bytes == 4 ? p & 255 : p & 255, out);
                }
            }
        }
        if (out != NULL)
        {
            fclose(out);
        }
        { uint32_t t=lift_host_read(&host,0x54b800,4), n=0,k; for(k=0;k<32768;k++) if(lift_host_read(&host,t+4*k,4)) n++; printf("table nonzero entries %u of 32768; sample %x %x %x\n", n, lift_host_read(&host,t+4*100,4), lift_host_read(&host,t+4*20000,4), lift_host_read(&host,t+4*32767,4)); { uint32_t w=lift_host_read(&host,0x54cdc8,4); printf("weights: %x %x %x\n", lift_host_read(&host,w,4), lift_host_read(&host,w+4,4), lift_host_read(&host,w+400,4)); } }
        printf("tbl: 54b800=%x 54cdc8=%x\n", lift_host_read(&host,0x54b800,4), lift_host_read(&host,0x54cdc8,4));
        printf("tints: 54d5ec=%x 54d5e8=%x 5bc008=%x 5bb79e=%x\n", lift_host_read(&host,0x54d5ec,4), lift_host_read(&host,0x54d5e8,4), lift_host_read(&host,0x5bc008,4), lift_host_read(&host,0x5bb79e,4));
        printf("blit globals: 774=%x 778=%x 750=%x 752=%x 5bb734=%x\n", lift_host_read(&host,0x5bb774,4), lift_host_read(&host,0x5bb778,4), lift_host_read(&host,0x5bb750,2), lift_host_read(&host,0x5bb752,2), lift_host_read(&host,0x5bb734,4));
        printf("back buffer %ux%u, %u bytes per pixel, non-zero pixels after drawing: %u\n", w, h, bytes, painted);
    }
    return 0;
}
