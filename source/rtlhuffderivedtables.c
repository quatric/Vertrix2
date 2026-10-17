#include "rtlhuffderivedtables.h"

/* libjpeg's jpeg_make_d_derived_tbl (jdhuff.c): expands a Huffman table into the decoder's form,
 * the codes' sizes and values (figures C.1 and C.2 of the standard), the largest code and value
 * offset of each length (F.15) and the 8-bit lookahead tables. */

enum
{
    /* huffsize[257] and huffcode[257] stay at the original's places in its frame: their indexes
     * come from the table, and an error exit may return. */
    BELOW = 0x554,
    HUFFSIZE = 0x14c,
    HUFFCODE = 0x550,

    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_DC_HUFF_TBL_PTRS = 0xb4,
    CINFO_AC_HUFF_TBL_PTRS = 0xc4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,
    MEM_ALLOC_SMALL = 0,
    JPOOL_IMAGE = 1,
    NUM_HUFF_TBLS = 4,
    JERR_BAD_HUFF_TABLE = 8,
    JERR_NO_HUFF_TABLE = 0x32,

    /* The JHUFF_TBL: bits[17] (bits[0] unused), then huffval[256]. */
    HTBL_BITS = 0,
    HTBL_HUFFVAL = 0x11,

    /* The d_derived_tbl: maxcode[18], valoffset[17], the table, look_nbits[256], look_sym[256]. */
    DTBL_BYTES = 0x590,
    DTBL_MAXCODE = 0,
    DTBL_VALOFFSET = 0x48,
    DTBL_PUB = 0x8c,
    DTBL_LOOK_NBITS = 0x90,
    DTBL_LOOK_SYM = 0x490,
    HUFF_LOOKAHEAD = 8,

    MEMSET = 0x4eb5c0
};

/* ERREXIT through error_exit, a method, with what the original leaves in edx, ebx and ecx. */
static void error_exit(Port *port, uint32_t cinfo, uint32_t code, uint32_t edx, uint32_t ebx,
                       uint32_t ecx)
{
    port_set32(port, port_u32(port, cinfo, CINFO_ERR), ERR_MSG_CODE, code);
    port_call(port, port_u32(port, port_u32(port, cinfo, CINFO_ERR), 0), cinfo, edx, ebx, ecx);
}

/* Original 0x4bbc00 (eax = cinfo, edx = isDC, ebx = the table number, ecx = where the derived
 * table goes, allocated there when it is still null). */
uint32_t vertrix_port_jpeg_make_huff_derived_table_4bbc00(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t huffsize = frame - HUFFSIZE;
    const uint32_t huffcode = frame - HUFFCODE;
    const uint32_t cinfo = entry->eax;
    const uint32_t is_dc = entry->edx;
    const uint32_t tblno = entry->ebx;
    const uint32_t pdtbl = entry->ecx;

    if ((int32_t)tblno < 0 || (int32_t)tblno >= NUM_HUFF_TBLS)
    {
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JERR_NO_HUFF_TABLE);
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM, tblno);
        const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
        port_call(&port, port_u32(&port, err, 0), cinfo, err, tblno, pdtbl);
    }
    const uint32_t htbl =
        port_u32(&port, cinfo + tblno * 4, is_dc ? CINFO_DC_HUFF_TBL_PTRS : CINFO_AC_HUFF_TBL_PTRS);
    if (htbl == 0)
    {
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_CODE, JERR_NO_HUFF_TABLE);
        port_set32(&port, port_u32(&port, cinfo, CINFO_ERR), ERR_MSG_PARM, tblno);
        const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
        port_call(&port, port_u32(&port, err, 0), cinfo, err, tblno, pdtbl);
    }
    if (port_u32(&port, pdtbl, 0) == 0)
    {
        /* alloc_small, a method: the original leaves pdtbl in ecx. */
        const uint32_t memory = port_u32(&port, cinfo, CINFO_MEM);
        port_set32(&port, pdtbl, 0,
                   port_call(&port, port_u32(&port, memory, MEM_ALLOC_SMALL), cinfo, JPOOL_IMAGE,
                             DTBL_BYTES, pdtbl));
    }
    const uint32_t dtbl = port_u32(&port, pdtbl, 0);
    port_set32(&port, dtbl, DTBL_PUB, htbl);

    /* Figure C.1: the size of each code, in order. */
    uint32_t p = 0;
    for (uint32_t l = 1; l <= 16 && !port.env.failed; l++)
    {
        uint32_t count = port_u8(&port, htbl, HTBL_BITS + l);
        if (p + count > 256)
        {
            error_exit(&port, cinfo, JERR_BAD_HUFF_TABLE, count, p, htbl + l);
        }
        for (; count != 0 && !port.env.failed; count--)
        {
            port_set8(&port, huffsize, p++, l);
        }
    }
    port_set8(&port, huffsize, p, 0);
    const uint32_t numsymbols = p;

    /* Figure C.2: the codes themselves. */
    uint32_t code = 0;
    uint32_t si = port_u8(&port, huffsize, 0);
    p = 0;
    while (port_u8(&port, huffsize, p) != 0 && !port.env.failed)
    {
        while (port_u8(&port, huffsize, p) == si && !port.env.failed)
        {
            port_set32(&port, huffcode, p * 4, code);
            p++;
            code++;
        }
        /* The code is now one past the last of this length: it must still fit. */
        if ((int32_t)code >= (int32_t)port_shl(1, si))
        {
            const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
            port_set32(&port, err, ERR_MSG_CODE, JERR_BAD_HUFF_TABLE);
            port_call(&port, port_u32(&port, port_u32(&port, cinfo, CINFO_ERR), 0), cinfo, code, p,
                      port_u32(&port, cinfo, CINFO_ERR));
        }
        code <<= 1;
        si++;
    }

    /* Figure F.15: the largest code and the value offset of each length. */
    p = 0;
    for (uint32_t l = 1; l <= 16 && !port.env.failed; l++)
    {
        const uint32_t count = port_u8(&port, htbl, HTBL_BITS + l);
        if (count == 0)
        {
            port_set32(&port, dtbl, DTBL_MAXCODE + l * 4, 0xffffffffu);
            continue;
        }
        port_set32(&port, dtbl, DTBL_VALOFFSET + l * 4, p - port_u32(&port, huffcode, p * 4));
        p += count;
        port_set32(&port, dtbl, DTBL_MAXCODE + l * 4, port_u32(&port, huffcode, (p - 1) * 4));
    }
    /* The sentinel that ensures jpeg_huff_decode terminates. */
    port_set32(&port, dtbl, DTBL_MAXCODE + 17 * 4, 0xfffff);

    /* The lookahead tables: for each code of up to 8 bits, every 8-bit prefix that starts with
     * it. */
    port_call(&port, MEMSET, dtbl + DTBL_LOOK_NBITS, 0, 0x400, 0);
    p = 0;
    for (uint32_t l = 1; l <= HUFF_LOOKAHEAD && !port.env.failed; l++)
    {
        for (uint32_t i = 1;
             (int32_t)i <= (int32_t)port_u8(&port, htbl, HTBL_BITS + l) && !port.env.failed;
             i++, p++)
        {
            uint32_t lookbits = port_shl(port_u32(&port, huffcode, p * 4), HUFF_LOOKAHEAD - l);
            for (int32_t ctr = 1 << (HUFF_LOOKAHEAD - l); ctr > 0 && !port.env.failed; ctr--)
            {
                port_set32(&port, dtbl + lookbits * 4, DTBL_LOOK_NBITS, l);
                port_set8(&port, dtbl + lookbits, DTBL_LOOK_SYM,
                          port_u8(&port, htbl + p, HTBL_HUFFVAL));
                lookbits++;
            }
        }
    }

    /* A DC table's symbols are bit counts, 0 to 15. */
    if (is_dc)
    {
        for (uint32_t i = 0; (int32_t)i < (int32_t)numsymbols && !port.env.failed; i++)
        {
            if (port_u8(&port, htbl + i, HTBL_HUFFVAL) > 15)
            {
                const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
                port_set32(&port, err, ERR_MSG_CODE, JERR_BAD_HUFF_TABLE);
                port_call(&port, port_u32(&port, port_u32(&port, cinfo, CINFO_ERR), 0), cinfo, i,
                          port_u32(&port, cinfo, CINFO_ERR), htbl + i);
            }
        }
    }
    return port_return(&port, 0, 0);
}
