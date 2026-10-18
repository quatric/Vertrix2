#include "rtljpegmasters.h"

/* libjpeg's jinit_master_decompress (jdmaster.c) with master_selection and
 * prepare_range_limit_table inlined. */

enum
{
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_PROGRESS = 8,
    CINFO_NUM_COMPONENTS = 0x24,
    CINFO_BUFFERED_IMAGE = 0x40,
    CINFO_RAW_DATA_OUT = 0x44,
    CINFO_QUANTIZE_COLORS = 0x54,
    CINFO_TWO_PASS_QUANTIZE = 0x5c,
    CINFO_ENABLE_1PASS_QUANT = 0x64,
    CINFO_ENABLE_EXTERNAL_QUANT = 0x68,
    CINFO_ENABLE_2PASS_QUANT = 0x6c,
    CINFO_OUTPUT_WIDTH = 0x70,
    CINFO_OUT_COLOR_COMPONENTS = 0x78,
    CINFO_COLORMAP = 0x88,
    CINFO_TOTAL_IMCU_ROWS = 0x140,
    CINFO_SAMPLE_RANGE_LIMIT = 0x144,
    CINFO_PROGRESSIVE_MODE = 0xdc,
    CINFO_ARITH_CODE = 0xe0,
    CINFO_MASTER = 0x1a4,
    CINFO_INPUTCTL = 0x1b4,
    CINFO_CQUANTIZE = 0x1cc,

    ERR_MSG_CODE = 0x14,
    JERR_ARITH_NOTIMPL = 1,
    JERR_NOT_COMPILED = 0x2f,
    JERR_WIDTH_OVERFLOW = 0x46,

    MEM_ALLOC_SMALL = 0,
    MEM_REALIZE_VIRT_ARRAYS = 0x18,
    JPOOL_IMAGE = 1,

    INPUTCTL_START_INPUT_PASS = 8,
    INPUTCTL_HAS_MULTIPLE_SCANS = 0x10,

    PROGRESS_PASS_COUNTER = 4,
    PROGRESS_PASS_LIMIT = 8,
    PROGRESS_COMPLETED_PASSES = 0xc,
    PROGRESS_TOTAL_PASSES = 0x10,

    /* The master (0x1c bytes): its public methods and dummy-pass flag, the pass number, whether
     * the merged upsampler is used and the two quantizers. */
    MASTER_SIZE = 0x1c,
    MASTER_PREPARE_FOR_OUTPUT_PASS = 0,
    MASTER_FINISH_OUTPUT_PASS = 4,
    MASTER_IS_DUMMY_PASS = 8,
    MASTER_PASS_NUMBER = 0xc,
    MASTER_USING_MERGED_UPSAMPLE = 0x10,
    MASTER_QUANTIZER_1PASS = 0x14,
    MASTER_QUANTIZER_2PASS = 0x18,

    /* The range limit table: 5 * 256 + 128 samples, the first 256 zero. */
    TABLE_SIZE = 0x580,
    TABLE_ZEROS = 0x100,
    MAXJSAMPLE = 0xff,
    CENTERJSAMPLE = 0x80,
    TABLE_IDENTITY_END = 0x100,
    TABLE_FULL_END = 0x200,
    TABLE_TAIL_ZEROS = 0x180,
    TABLE_WRAP = 0x380,

    PREPARE_FOR_OUTPUT_PASS = 0x4c14b7,
    FINISH_OUTPUT_PASS = 0x4c16dc,
    CALC_OUTPUT_DIMENSIONS = 0x4c0c8f,
    USE_MERGED_UPSAMPLE = 0x4c0b51,
    MEMSET = 0x4eb5c0,
    JINIT_1PASS_QUANTIZER = 0x4c6c80,
    JINIT_2PASS_QUANTIZER = 0x4c96a0,
    JINIT_MERGED_UPSAMPLER = 0x4c2280,
    JINIT_COLOR_DECONVERTER = 0x4bb6c0,
    JINIT_UPSAMPLER = 0x4c3be0,
    JINIT_D_POST_CONTROLLER = 0x4c3540,
    JINIT_INVERSE_DCT = 0x4bb9b0,
    JINIT_PHUFF_DECODER = 0x4c31a0,
    JINIT_HUFF_DECODER = 0x4bc6c0,
    JINIT_D_COEF_CONTROLLER = 0x4bb040,
    JINIT_D_MAIN_CONTROLLER = 0x4bdde0
};

/* The registers the original leaves for its callees: ebx, ecx, esi and edi (ebp is its frame). */
typedef struct
{
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Registers;

static uint32_t call(Port *port, const Registers *registers, uint32_t target, uint32_t eax,
                     uint32_t edx)
{
    return port_call_with(port, target, eax, edx, registers->ebx, registers->ecx, registers->esi,
                          registers->edi, registers->ebp);
}

/* ERREXIT: the error manager's error_exit (its first method) with the message code set. */
static void error_exit(Port *port, const Registers *registers, uint32_t cinfo, uint32_t code)
{
    const uint32_t err = port_u32(port, cinfo, CINFO_ERR);
    port_set32(port, err, ERR_MSG_CODE, code);
    call(port, registers, port_u32(port, err, 0), cinfo, port_u32(port, cinfo, CINFO_ERR));
}

/* Original 0x4c17da (eax = cinfo): jinit_master_decompress. The master comes from the image pool's
 * alloc_small and is installed with prepare_for_output_pass 0x4c14b7 and finish_output_pass
 * 0x4c16dc; jpeg_calc_output_dimensions (0x4c0c8f) runs, then the range limit table (0x580 bytes:
 * 256 zeros, the identity, 384 MAXJSAMPLEs, 384 zeros and the first 128 entries again; the sample
 * range limit points past the zeros). master_selection then picks the merged upsampler (0x4c0b51)
 * and the quantizers (one-pass for other than three output components, external with a colormap,
 * two-pass when asked, else one-pass; none unless quantizing a buffered image), initialises the
 * modules and, with a progress monitor, a single image and several scans, sets its pass counts.
 * The caller's edx is kept. */
uint32_t vertrix_port_jpeg_master_decompress_4c17da(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t mem = port_u32(&port, cinfo, CINFO_MEM);
    Registers registers = {MASTER_SIZE, mem, entry->esi, entry->edi, entry->esp - 4};
    const uint32_t master =
        call(&port, &registers, port_u32(&port, mem, MEM_ALLOC_SMALL), cinfo, JPOOL_IMAGE);
    port_set32(&port, cinfo, CINFO_MASTER, master);
    port_set32(&port, master, MASTER_PREPARE_FOR_OUTPUT_PASS, PREPARE_FOR_OUTPUT_PASS);
    port_set32(&port, master, MASTER_FINISH_OUTPUT_PASS, FINISH_OUTPUT_PASS);
    port_set32(&port, master, MASTER_IS_DUMMY_PASS, 0);
    const uint32_t installed = port_u32(&port, cinfo, CINFO_MASTER);
    call(&port, &registers, CALC_OUTPUT_DIMENSIONS, cinfo, cinfo);

    registers.ebx = TABLE_SIZE;
    registers.ecx = port_u32(&port, cinfo, CINFO_MEM);
    uint32_t table = call(&port, &registers, port_u32(&port, registers.ecx, MEM_ALLOC_SMALL), cinfo,
                          JPOOL_IMAGE);
    table += TABLE_ZEROS;
    port_set32(&port, cinfo, CINFO_SAMPLE_RANGE_LIMIT, table);
    registers.ebx = TABLE_ZEROS;
    call(&port, &registers, MEMSET, table - TABLE_ZEROS, 0);
    for (uint32_t i = 0; i <= MAXJSAMPLE; i++)
    {
        port_set8(&port, table, i, i);
    }
    table += CENTERJSAMPLE;
    for (uint32_t i = CENTERJSAMPLE; i < TABLE_FULL_END; i++)
    {
        port_set8(&port, table, i, MAXJSAMPLE);
    }
    registers.ebx = TABLE_TAIL_ZEROS;
    call(&port, &registers, MEMSET, table + TABLE_FULL_END, 0);
    const uint32_t limit = port_u32(&port, cinfo, CINFO_SAMPLE_RANGE_LIMIT);
    port_copy(&port, table + TABLE_WRAP, limit, CENTERJSAMPLE);
    registers.ecx = 0;
    registers.esi = limit + CENTERJSAMPLE;
    registers.edi = table + TABLE_WRAP;

    /* master_selection. jd_samplesperrow is the same 32-bit product as samplesperrow, so
     * JERR_WIDTH_OVERFLOW is never raised. */
    port_set32(&port, installed, MASTER_PASS_NUMBER, 0);
    const uint32_t merged = call(&port, &registers, USE_MERGED_UPSAMPLE, cinfo, cinfo);
    port_set32(&port, installed, MASTER_USING_MERGED_UPSAMPLE, merged);
    uint32_t edx = merged;
    port_set32(&port, installed, MASTER_QUANTIZER_1PASS, 0);
    port_set32(&port, installed, MASTER_QUANTIZER_2PASS, 0);
    if (port_u32(&port, cinfo, CINFO_QUANTIZE_COLORS) == 0 ||
        port_u32(&port, cinfo, CINFO_BUFFERED_IMAGE) == 0)
    {
        port_set32(&port, cinfo, CINFO_ENABLE_1PASS_QUANT, 0);
        port_set32(&port, cinfo, CINFO_ENABLE_EXTERNAL_QUANT, 0);
        port_set32(&port, cinfo, CINFO_ENABLE_2PASS_QUANT, 0);
    }
    if (port_u32(&port, cinfo, CINFO_QUANTIZE_COLORS) != 0)
    {
        if (port_u32(&port, cinfo, CINFO_RAW_DATA_OUT) != 0)
        {
            error_exit(&port, &registers, cinfo, JERR_NOT_COMPILED);
            edx = vertrix_lift_edx;
        }
        if (port_u32(&port, cinfo, CINFO_OUT_COLOR_COMPONENTS) != 3)
        {
            port_set32(&port, cinfo, CINFO_ENABLE_1PASS_QUANT, 1);
            port_set32(&port, cinfo, CINFO_ENABLE_EXTERNAL_QUANT, 0);
            port_set32(&port, cinfo, CINFO_ENABLE_2PASS_QUANT, 0);
            port_set32(&port, cinfo, CINFO_COLORMAP, 0);
        }
        else if (port_u32(&port, cinfo, CINFO_COLORMAP) != 0)
        {
            port_set32(&port, cinfo, CINFO_ENABLE_EXTERNAL_QUANT, 1);
        }
        else if (port_u32(&port, cinfo, CINFO_TWO_PASS_QUANTIZE) != 0)
        {
            port_set32(&port, cinfo, CINFO_ENABLE_2PASS_QUANT, 1);
        }
        else
        {
            port_set32(&port, cinfo, CINFO_ENABLE_1PASS_QUANT, 1);
        }
        if (port_u32(&port, cinfo, CINFO_ENABLE_1PASS_QUANT) != 0)
        {
            call(&port, &registers, JINIT_1PASS_QUANTIZER, cinfo, edx);
            edx = port_u32(&port, cinfo, CINFO_CQUANTIZE);
            port_set32(&port, installed, MASTER_QUANTIZER_1PASS, edx);
        }
        if (port_u32(&port, cinfo, CINFO_ENABLE_2PASS_QUANT) != 0 ||
            port_u32(&port, cinfo, CINFO_ENABLE_EXTERNAL_QUANT) != 0)
        {
            call(&port, &registers, JINIT_2PASS_QUANTIZER, cinfo, edx);
            edx = port_u32(&port, cinfo, CINFO_CQUANTIZE);
            port_set32(&port, installed, MASTER_QUANTIZER_2PASS, edx);
        }
    }
    if (port_u32(&port, cinfo, CINFO_RAW_DATA_OUT) == 0)
    {
        if (port_u32(&port, installed, MASTER_USING_MERGED_UPSAMPLE) != 0)
        {
            call(&port, &registers, JINIT_MERGED_UPSAMPLER, cinfo, edx);
        }
        else
        {
            call(&port, &registers, JINIT_COLOR_DECONVERTER, cinfo, edx);
            call(&port, &registers, JINIT_UPSAMPLER, cinfo, vertrix_lift_edx);
        }
        call(&port, &registers, JINIT_D_POST_CONTROLLER, cinfo,
             port_u32(&port, cinfo, CINFO_ENABLE_2PASS_QUANT));
        edx = vertrix_lift_edx;
    }
    call(&port, &registers, JINIT_INVERSE_DCT, cinfo, edx);
    if (port_u32(&port, cinfo, CINFO_ARITH_CODE) != 0)
    {
        error_exit(&port, &registers, cinfo, JERR_ARITH_NOTIMPL);
    }
    else if (port_u32(&port, cinfo, CINFO_PROGRESSIVE_MODE) != 0)
    {
        call(&port, &registers, JINIT_PHUFF_DECODER, cinfo, vertrix_lift_edx);
    }
    else
    {
        call(&port, &registers, JINIT_HUFF_DECODER, cinfo, vertrix_lift_edx);
    }
    const uint32_t use_c_buffer =
        port_u32(&port, port_u32(&port, cinfo, CINFO_INPUTCTL), INPUTCTL_HAS_MULTIPLE_SCANS) != 0 ||
        port_u32(&port, cinfo, CINFO_BUFFERED_IMAGE) != 0;
    call(&port, &registers, JINIT_D_COEF_CONTROLLER, cinfo, use_c_buffer);
    if (port_u32(&port, cinfo, CINFO_RAW_DATA_OUT) == 0)
    {
        call(&port, &registers, JINIT_D_MAIN_CONTROLLER, cinfo, 0);
    }
    const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
    call(&port, &registers, port_u32(&port, memory, MEM_REALIZE_VIRT_ARRAYS), cinfo, memory);
    const uint32_t inputctl = port_u32(&port, cinfo, CINFO_INPUTCTL);
    call(&port, &registers, port_u32(&port, inputctl, INPUTCTL_START_INPUT_PASS), cinfo, inputctl);

    /* The early returns leave cinfo, or the input controller, in eax (0x4c1b71..0x4c1b91). */
    if (port_u32(&port, cinfo, CINFO_PROGRESS) == 0 ||
        port_u32(&port, cinfo, CINFO_BUFFERED_IMAGE) != 0)
    {
        return port_return(&port, cinfo, entry->edx);
    }
    const uint32_t control = port_u32(&port, cinfo, CINFO_INPUTCTL);
    if (port_u32(&port, control, INPUTCTL_HAS_MULTIPLE_SCANS) == 0)
    {
        return port_return(&port, control, entry->edx);
    }
    const uint32_t components = port_u32(&port, cinfo, CINFO_NUM_COMPONENTS);
    const uint32_t nscans =
        port_u32(&port, cinfo, CINFO_PROGRESSIVE_MODE) != 0 ? components * 3 + 2 : components;
    /* cinfo->progress is read again for each store (0x4c1bbc..0x4c1c0e): the monitor may be
     * cinfo itself, whose progress field its pass limit then replaces. */
    port_set32(&port, port_u32(&port, cinfo, CINFO_PROGRESS), PROGRESS_PASS_COUNTER, 0);
    const uint32_t limit_passes = port_u32(&port, cinfo, CINFO_TOTAL_IMCU_ROWS) * nscans;
    port_set32(&port, port_u32(&port, cinfo, CINFO_PROGRESS), PROGRESS_PASS_LIMIT, limit_passes);
    port_set32(&port, port_u32(&port, cinfo, CINFO_PROGRESS), PROGRESS_COMPLETED_PASSES, 0);
    const uint32_t total = port_u32(&port, cinfo, CINFO_ENABLE_2PASS_QUANT) != 0 ? 3 : 2;
    port_set32(&port, port_u32(&port, cinfo, CINFO_PROGRESS), PROGRESS_TOTAL_PASSES, total);
    port_set32(&port, installed, MASTER_PASS_NUMBER,
               port_u32(&port, installed, MASTER_PASS_NUMBER) + 1);
    return port_return(&port, installed, entry->edx);
}
