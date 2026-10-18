#include "rtljpegmarkersaves.h"

enum
{
    /* The decompressor: the error manager, the memory manager, the source, the saved marker list,
     * the marker being read and the marker reader. */
    CINFO_ERR = 0,
    CINFO_MEM = 4,
    CINFO_SRC = 0x18,
    CINFO_MARKER_LIST = 0x130,
    CINFO_UNREAD_MARKER = 0x1a0,
    CINFO_MARKER = 0x1b8,

    /* The marker reader: the length limits (COM, then APP0..APP15 from +0x64), the marker being
     * saved and the bytes of it read so far. */
    MARKER_LIMIT_COM = 0x60,
    MARKER_LIMIT_APP = 0x64,
    MARKER_CURRENT = 0xa4,
    MARKER_BYTES_READ = 0xa8,

    /* A saved marker: next, the marker code (a byte), the original and saved lengths, the data. */
    SAVED_NEXT = 0,
    SAVED_CODE = 4,
    SAVED_LENGTH = 8,
    SAVED_DATA_LENGTH = 0xc,
    SAVED_DATA = 0x10,
    SAVED_SIZE = 0x14,

    SRC_NEXT = 0,
    SRC_LEFT = 4,
    SRC_FILL = 0xc,
    SRC_SKIP = 0x10,
    MEM_ALLOC_LARGE = 4,
    POOL_IMAGE = 1,
    ERR_EMIT = 4,
    ERR_CODE = 0x14,
    ERR_PARM = 0x18,
    TRACE_LEVEL = 1,

    M_APP0 = 0xe0,
    M_APP14 = 0xee,
    M_COM = 0xfe,
    JTRC_MISC_MARKER = 0x5b,

    EXAMINE_APP0 = 0x4bef10,
    EXAMINE_APP14 = 0x4bf190
};

/* The source's bytes: where the next one is and how many are left, as the original keeps them in
 * edi and esi. */
typedef struct Input
{
    uint32_t next;
    uint32_t left;
} Input;

/* fill_input_buffer (the source's +0xc) with the registers the original leaves; 0 when it
 * suspends. */
static uint32_t fill(Port *port, uint32_t cinfo, uint32_t src, Input *in, uint32_t edx,
                     uint32_t ebx, uint32_t ecx)
{
    if (port_call(port, port_u32(port, src, SRC_FILL), cinfo, edx, ebx, ecx) == 0)
    {
        return 0;
    }
    in->next = port_u32(port, src, SRC_NEXT);
    in->left = port_u32(port, src, SRC_LEFT);
    return 1;
}

static uint32_t take(Port *port, Input *in)
{
    const uint32_t byte = port_u8(port, in->next, 0);
    in->next++;
    in->left--;
    return byte;
}

/* Original 0x4bf3e0 (eax = the decompressor): libjpeg save_marker. A new marker's length is read
 * (two bytes, less 2), a record of up to the marker's length limit allocated (+0x14 bytes, image
 * pool) and filled; a suspended one carries on from the bytes read. The data is copied while the
 * source has bytes, saving the position before each refill. A finished record goes at the end of
 * the marker list (+0x130); then APP0 and APP14 are examined (0x4bef10, 0x4bf190, with the data,
 * its length and the bytes not saved) and any other marker traced (JTRC_MISC_MARKER), and the bytes
 * not saved are skipped (the source's +0x10). Returns 1, or 0 when the source suspends (the
 * original's shared tail at 0x4bf342/0x4bf347); keeps edx. The method calls get the registers the
 * original leaves. */
uint32_t vertrix_port_jpeg_save_marker_4bf3e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t marker = port_u32(&port, cinfo, CINFO_MARKER);
    uint32_t saved = port_u32(&port, marker, MARKER_CURRENT);
    const uint32_t src = port_u32(&port, cinfo, CINFO_SRC);
    Input in = {port_u32(&port, src, SRC_NEXT), port_u32(&port, src, SRC_LEFT)};
    uint32_t length = 0;
    uint32_t data;
    uint32_t limit;
    uint32_t bytes_read;

    if (saved == 0)
    {
        if (in.left == 0 && !fill(&port, cinfo, src, &in, src, entry->ebx, saved))
        {
            return port_return(&port, 0, entry->edx);
        }
        length = take(&port, &in) << 8;
        if (in.left == 0 && !fill(&port, cinfo, src, &in, src, entry->ebx, saved))
        {
            return port_return(&port, 0, entry->edx);
        }
        length = length + take(&port, &in) - 2;
        if ((int32_t)length < 0)
        {
            limit = 0;
            bytes_read = 0;
            data = 0;
        }
        else
        {
            const uint32_t code = port_u32(&port, cinfo, CINFO_UNREAD_MARKER);
            limit = code == M_COM ? port_u32(&port, marker, MARKER_LIMIT_COM)
                                  : port_u32(&port, marker + (code - M_APP0) * 4, MARKER_LIMIT_APP);
            if (length < limit)
            {
                limit = length;
            }
            const uint32_t mem = port_u32(&port, cinfo, CINFO_MEM);
            saved = port_call(&port, port_u32(&port, mem, MEM_ALLOC_LARGE), cinfo, POOL_IMAGE,
                              limit + SAVED_SIZE, mem);
            port_set32(&port, saved, SAVED_NEXT, 0);
            port_set8(&port, saved, SAVED_CODE, port_u8(&port, cinfo, CINFO_UNREAD_MARKER));
            port_set32(&port, saved, SAVED_LENGTH, length);
            port_set32(&port, saved, SAVED_DATA_LENGTH, limit);
            data = saved + SAVED_SIZE;
            port_set32(&port, saved, SAVED_DATA, data);
            port_set32(&port, marker, MARKER_BYTES_READ, 0);
            port_set32(&port, marker, MARKER_CURRENT, saved);
            bytes_read = 0;
        }
    }
    else
    {
        bytes_read = port_u32(&port, marker, MARKER_BYTES_READ);
        data = port_u32(&port, saved, SAVED_DATA) + bytes_read;
        limit = port_u32(&port, saved, SAVED_DATA_LENGTH);
    }

    while (bytes_read < limit && !port.env.failed)
    {
        port_set32(&port, src, SRC_NEXT, in.next);
        port_set32(&port, src, SRC_LEFT, in.left);
        port_set32(&port, marker, MARKER_BYTES_READ, bytes_read);
        if (in.left == 0 && !fill(&port, cinfo, src, &in, bytes_read, limit, src))
        {
            return port_return(&port, 0, entry->edx);
        }
        while (bytes_read < limit && in.left != 0 && !port.env.failed)
        {
            port_set8(&port, data, 0, take(&port, &in));
            data++;
            bytes_read++;
        }
    }

    if (saved != 0)
    {
        const uint32_t list = port_u32(&port, cinfo, CINFO_MARKER_LIST);
        if (list == 0)
        {
            port_set32(&port, cinfo, CINFO_MARKER_LIST, saved);
        }
        else
        {
            uint32_t last = list;
            while (port_u32(&port, last, SAVED_NEXT) != 0 && !port.env.failed)
            {
                last = port_u32(&port, last, SAVED_NEXT);
            }
            port_set32(&port, last, SAVED_NEXT, saved);
        }
        data = port_u32(&port, saved, SAVED_DATA);
        length = port_u32(&port, saved, SAVED_LENGTH) - limit;
    }
    port_set32(&port, marker, MARKER_CURRENT, 0);

    const uint32_t code = port_u32(&port, cinfo, CINFO_UNREAD_MARKER);
    uint32_t ecx;
    if (code == M_APP0 || code == M_APP14)
    {
        port_call(&port, code == M_APP0 ? EXAMINE_APP0 : EXAMINE_APP14, cinfo, data, limit, length);
        ecx = length;
    }
    else
    {
        const uint32_t err = port_u32(&port, cinfo, CINFO_ERR);
        port_set32(&port, err, ERR_CODE, JTRC_MISC_MARKER);
        port_set32(&port, err, ERR_PARM, code);
        port_set32(&port, err, ERR_PARM + 4, limit + length);
        port_call(&port, port_u32(&port, err, ERR_EMIT), cinfo, TRACE_LEVEL, limit + length, err);
        ecx = err;
    }
    port_set32(&port, src, SRC_NEXT, in.next);
    port_set32(&port, src, SRC_LEFT, in.left);
    if ((int32_t)length > 0)
    {
        port_call(&port, port_u32(&port, src, SRC_SKIP), cinfo, length, src, ecx);
    }
    return port_return(&port, 1, entry->edx);
}
