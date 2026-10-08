#include <string.h>
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
    _exit(3);
}

static void report(const char *what, const LiftHost *host, uint32_t result)
{
    unsigned i;
    printf("%s: result %x, %u boundary calls, heap %x\n", what, result, host->boundary_calls,
           host->heap_top);
    for (i = 0; i < host->boundary_distinct; i++)
    {
        printf("  boundary %06x x%u %s\n", host->boundary_targets[i], host->boundary_counts[i], vertrix_import_name(host->boundary_targets[i]) ? vertrix_import_name(host->boundary_targets[i]) : "");
    }
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
    host.archive = vertrix_vf_open(getenv("VF") ? getenv("VF") : "hardware-check/Vertrix2.vf");
    if (host.archive == NULL) { fprintf(stderr, "no archive\n"); return 2; }
    vertrix_lifted_allow_unverified(1);
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
        uint32_t display = lift_host_allocate(&host, 0x800);
        host_store(&host, 0x544070, display);
        if (getenv("TRACE")) vertrix_lifted_set_trace(1);
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
        host_store(&host, wrapper + 0xc, bytes | ((getenv("KIND") ? atoi(getenv("KIND")) : 0) << 8)); /* bytes per pixel; sub-format byte */
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
        printf("478eb0(w,3,2) = %x\n", lift_host_run(&host, 0x478eb0, wrapper, 3, 2, 0, &lifted));
        printf("pre-draw wrapper: base %x pitch %u bpp %u\n", lift_host_read(&host, wrapper, 4), lift_host_read(&host, wrapper + 0x14, 4), lift_host_read(&host, wrapper + 0xc, 4));
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
