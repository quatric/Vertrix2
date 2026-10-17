#include "rtljpegmaincontrollers.h"

/* libjpeg's jinit_d_main_controller (jdmainct.c). */

enum
{
    /* cinfo fields. */
    CINFO_ERR = 0x0,
    CINFO_MEM = 0x4,
    CINFO_COMPONENTS = 0x24,
    CINFO_COMP_INFO = 0xd8,
    CINFO_MIN_DCT_SCALED = 0x13c,
    CINFO_MAIN = 0x1a8,
    CINFO_UPSAMPLE = 0x1c4,
    UPSAMPLE_CONTEXT_ROWS = 0x8,
    ERR_CODE = 0x14,

    /* The memory manager's methods: alloc_small, alloc_sarray. */
    MEM_ALLOC_SMALL = 0x0,
    MEM_ALLOC_SARRAY = 0x8,
    POOL_IMAGE = 1,

    /* The main controller: 0x50 bytes, start_pass, the funny xbuffer lists and the buffers. */
    MAIN_SIZE = 0x50,
    MAIN_START_PASS = 0x4bd750,
    MAIN_XBUFFER0 = 0x38,
    MAIN_XBUFFER1 = 0x3c,
    MAIN_BUFFER = 0x8,

    /* jpeg_component_info: stride, v_samp_factor, width_in_blocks, DCT_scaled_size. */
    COMPONENT_SIZE = 0x54,
    COMPONENT_V_SAMP = 0xc,
    COMPONENT_WIDTH = 0x1c,
    COMPONENT_DCT_SCALED = 0x24,

    JERR_BAD_BUFFER_MODE = 0x4,
    JERR_NOTIMPL = 0x2f
};

/* The registers the original holds when it calls a method: eax is cinfo, and the rest are what it
 * leaves in them (each method is an unknown call, which reads all four). */
typedef struct
{
    Port *port;
    const LiftEntry *entry;
    uint32_t cinfo;
    uint32_t mem;
} Main;

static uint32_t method(Main *m, uint32_t target, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    return port_call_with(m->port, target, m->cinfo, edx, ebx, ecx, m->cinfo, m->mem,
                          m->entry->esp - 4);
}

/* ERREXIT: the error code into err->msg_code and error_exit, eax = cinfo, edx = err. */
static void error_exit(Main *m, uint32_t code, uint32_t ebx, uint32_t ecx)
{
    const uint32_t err = port_u32(m->port, m->cinfo, CINFO_ERR);
    port_set32(m->port, err, ERR_CODE, code);
    method(m, port_u32(m->port, err, 0), err, ebx, ecx);
}

/* The row groups of a component: v_samp_factor * DCT_scaled_size / min_DCT_scaled_size, with
 * idiv's signed quotient. */
static uint32_t row_group(Port *port, uint32_t cinfo, uint32_t component)
{
    uint32_t eax = port_u32(port, component, COMPONENT_V_SAMP) *
                   port_u32(port, component, COMPONENT_DCT_SCALED);
    uint32_t edx = (uint32_t)((int32_t)eax >> 31);
    LiftFlags flags;
    memset(&flags, 0, sizeof flags);
    lift_idiv1(32, port_u32(port, cinfo, CINFO_MIN_DCT_SCALED), &eax, &edx, &flags);
    return eax;
}

/* Original 0x4bdde0 (eax = cinfo, edx = need_full_buffer): allocates the 0x50-byte main
 * controller (alloc_small), stores it at cinfo +0x1a8 with start_pass 0x4bd750, and raises
 * JERR_BAD_BUFFER_MODE for a full buffer. When the upsampler needs context rows it raises
 * JERR_NOTIMPL for a min_DCT_scaled_size below 2, then allocates the two funny xbuffer pointer
 * lists (alloc_funny_pointers: 2 * components pointers, then per component rgroup * (M + 4)
 * pointers, the lists starting rgroup in), and takes M + 2 row groups; otherwise M. Then one
 * sample array per component (alloc_sarray: width_in_blocks * DCT_scaled_size samples, rgroup *
 * row groups rows) into main->buffer. No caller reads a result. */
uint32_t vertrix_port_jpeg_init_main_controller_4bdde0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t need_full = entry->edx;
    Main m = {&port, entry, cinfo, port_u32(&port, cinfo, CINFO_MEM)};

    const uint32_t main_controller =
        method(&m, port_u32(&port, m.mem, MEM_ALLOC_SMALL), POOL_IMAGE, MAIN_SIZE, need_full);
    port_set32(&port, cinfo, CINFO_MAIN, main_controller);
    port_set32(&port, main_controller, 0, MAIN_START_PASS);
    if (need_full != 0)
    {
        error_exit(&m, JERR_BAD_BUFFER_MODE, MAIN_SIZE, need_full);
    }

    uint32_t groups;
    const uint32_t upsample = port_u32(&port, cinfo, CINFO_UPSAMPLE);
    if (port_u32(&port, upsample, UPSAMPLE_CONTEXT_ROWS) != 0)
    {
        if ((int32_t)port_u32(&port, cinfo, CINFO_MIN_DCT_SCALED) < 2)
        {
            error_exit(&m, JERR_NOTIMPL, MAIN_SIZE, need_full);
        }
        const uint32_t controller = port_u32(&port, cinfo, CINFO_MAIN);
        m.mem = port_u32(&port, cinfo, CINFO_MEM);
        const uint32_t scaled = port_u32(&port, cinfo, CINFO_MIN_DCT_SCALED);
        const uint32_t components = port_u32(&port, cinfo, CINFO_COMPONENTS);
        const uint32_t lists = method(&m, port_u32(&port, m.mem, MEM_ALLOC_SMALL), POOL_IMAGE,
                                      components << 3, need_full);
        port_set32(&port, controller, MAIN_XBUFFER0, lists);
        port_set32(&port, controller, MAIN_XBUFFER1,
                   port_u32(&port, controller, MAIN_XBUFFER0) +
                       (port_u32(&port, cinfo, CINFO_COMPONENTS) << 2));
        uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
        for (uint32_t ci = 0;
             (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_COMPONENTS) && !port.env.failed;
             ci++)
        {
            const uint32_t rgroup = row_group(&port, cinfo, component);
            const uint32_t rows = rgroup * (scaled + 4);
            m.mem = port_u32(&port, cinfo, CINFO_MEM);
            uint32_t xbuf =
                method(&m, port_u32(&port, m.mem, MEM_ALLOC_SMALL), POOL_IMAGE, rows * 8, cinfo);
            xbuf += rgroup * 4;
            port_set32(&port, port_u32(&port, controller, MAIN_XBUFFER0) + ci * 4, 0, xbuf);
            xbuf += rows * 4;
            port_set32(&port, port_u32(&port, controller, MAIN_XBUFFER1) + ci * 4, 0, xbuf);
            component += COMPONENT_SIZE;
        }
        groups = port_u32(&port, cinfo, CINFO_MIN_DCT_SCALED) + 2;
    }
    else
    {
        groups = port_u32(&port, cinfo, CINFO_MIN_DCT_SCALED);
    }

    uint32_t component = port_u32(&port, cinfo, CINFO_COMP_INFO);
    uint32_t buffer = main_controller;
    for (uint32_t ci = 0;
         (int32_t)ci < (int32_t)port_u32(&port, cinfo, CINFO_COMPONENTS) && !port.env.failed; ci++)
    {
        const uint32_t rows = groups * row_group(&port, cinfo, component);
        const uint32_t samples = port_u32(&port, component, COMPONENT_DCT_SCALED) *
                                 port_u32(&port, component, COMPONENT_WIDTH);
        m.mem = port_u32(&port, cinfo, CINFO_MEM);
        const uint32_t array =
            method(&m, port_u32(&port, m.mem, MEM_ALLOC_SARRAY), POOL_IMAGE, samples, rows);
        port_set32(&port, buffer, MAIN_BUFFER, array);
        buffer += 4;
        component += COMPONENT_SIZE;
    }
    return port_return(&port, 0, 0);
}
