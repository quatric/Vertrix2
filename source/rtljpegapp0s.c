#include "rtljpegapp0s.h"

/* libjpeg's examine_app0 (jdmarker.c): looks at an APP0 marker's first bytes for a JFIF or JFXX
 * header and traces what it finds. */

enum
{
    CINFO_ERR = 0,
    CINFO_SAW_JFIF_MARKER = 0x118,
    CINFO_JFIF_MAJOR_VERSION = 0x11c,
    CINFO_JFIF_MINOR_VERSION = 0x11d,
    CINFO_DENSITY_UNIT = 0x11e,
    CINFO_X_DENSITY = 0x120,
    CINFO_Y_DENSITY = 0x122,
    /* jpeg_error_mgr: emit_message, msg_code and the integer message parameters. */
    ERR_EMIT_MESSAGE = 4,
    ERR_MSG_CODE = 0x14,
    ERR_MSG_PARM = 0x18,

    APP0_DATA_LEN = 14,
    JFXX_DATA_LEN = 6,

    JTRC_APP0 = 0x4d,
    JTRC_JFIF = 0x57,
    JTRC_JFIF_BADTHUMBNAILSIZE = 0x58,
    JTRC_JFIF_EXTENSION = 0x59,
    JTRC_JFIF_THUMBNAIL = 0x5a,
    JTRC_THUMB_JPEG = 0x6c,
    JTRC_THUMB_PALETTE = 0x6d,
    JTRC_THUMB_RGB = 0x6e,
    JWRN_JFIF_MAJOR = 0x77
};

static uint32_t error_manager(Port *port, uint32_t cinfo)
{
    return port_u32(port, cinfo, CINFO_ERR);
}

static void set_parm(Port *port, uint32_t cinfo, unsigned index, uint32_t value)
{
    port_set32(port, error_manager(port, cinfo), ERR_MSG_PARM + index * 4, value);
}

/* cinfo->err->emit_message(cinfo, level) for a message whose code and parameters are set. A
 * method call: ebx and ecx are what the original leaves in them, given at each call. */
static void emit(Port *port, uint32_t cinfo, uint32_t code, uint32_t level, uint32_t ebx,
                 uint32_t ecx)
{
    port_set32(port, error_manager(port, cinfo), ERR_MSG_CODE, code);
    port_call(port, port_u32(port, error_manager(port, cinfo), ERR_EMIT_MESSAGE), cinfo, level, ebx,
              ecx);
}

/* TRACEMS1 and friends, after which the original leaves the error manager in ecx. */
static void trace(Port *port, uint32_t cinfo, uint32_t code, uint32_t ebx)
{
    emit(port, cinfo, code, 1, ebx, error_manager(port, cinfo));
}

static uint32_t word_be(Port *port, uint32_t data, uint32_t offset)
{
    return (port_u8(port, data, offset) << 8) + port_u8(port, data, offset + 1);
}

static int matches(Port *port, uint32_t data, const char *tag)
{
    for (unsigned i = 0; i < 5; i++)
    {
        if (port_u8(port, data, i) != (uint8_t)tag[i])
        {
            return 0;
        }
    }
    return 1;
}

/* Original 0x4bef10 (eax = cinfo, edx = data, ebx = datalen, ecx = remaining). */
uint32_t vertrix_port_jpeg_examine_app0_4bef10(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t cinfo = entry->eax;
    const uint32_t data = entry->edx;
    const uint32_t datalen = entry->ebx;
    const uint32_t totallen = datalen + entry->ecx;

    if (datalen >= APP0_DATA_LEN && matches(&port, data, "JFIF"))
    {
        /* Found JFIF APP0 marker: save info. */
        port_set32(&port, cinfo, CINFO_SAW_JFIF_MARKER, 1);
        port_set8(&port, cinfo, CINFO_JFIF_MAJOR_VERSION, port_u8(&port, data, 5));
        port_set8(&port, cinfo, CINFO_JFIF_MINOR_VERSION, port_u8(&port, data, 6));
        port_set8(&port, cinfo, CINFO_DENSITY_UNIT, port_u8(&port, data, 7));
        port_set16(&port, cinfo, CINFO_X_DENSITY, word_be(&port, data, 8));
        port_set16(&port, cinfo, CINFO_Y_DENSITY, word_be(&port, data, 10));
        const uint32_t major = port_u8(&port, cinfo, CINFO_JFIF_MAJOR_VERSION);
        const uint32_t minor = port_u8(&port, cinfo, CINFO_JFIF_MINOR_VERSION);
        if (major != 1)
        {
            set_parm(&port, cinfo, 0, major);
            set_parm(&port, cinfo, 1, minor);
            emit(&port, cinfo, JWRN_JFIF_MAJOR, 0xffffffffu, error_manager(&port, cinfo), totallen);
        }
        set_parm(&port, cinfo, 0, major);
        set_parm(&port, cinfo, 1, minor);
        set_parm(&port, cinfo, 2, port_u16(&port, cinfo, CINFO_X_DENSITY));
        set_parm(&port, cinfo, 3, port_u16(&port, cinfo, CINFO_Y_DENSITY));
        set_parm(&port, cinfo, 4, port_u8(&port, cinfo, CINFO_DENSITY_UNIT));
        emit(&port, cinfo, JTRC_JFIF, 1, error_manager(&port, cinfo), totallen);
        const uint32_t thumb_width = port_u8(&port, data, 12);
        const uint32_t thumb_height = port_u8(&port, data, 13);
        if ((thumb_width | thumb_height) != 0)
        {
            set_parm(&port, cinfo, 0, thumb_width);
            set_parm(&port, cinfo, 1, thumb_height);
            emit(&port, cinfo, JTRC_JFIF_THUMBNAIL, 1, error_manager(&port, cinfo), totallen);
        }
        const uint32_t thumb_pixels = port_u8(&port, data, 12) * port_u8(&port, data, 13);
        const uint32_t rest = totallen - APP0_DATA_LEN;
        if (rest != thumb_pixels * 3)
        {
            set_parm(&port, cinfo, 0, rest);
            trace(&port, cinfo, JTRC_JFIF_BADTHUMBNAILSIZE, thumb_pixels);
        }
    }
    else if (datalen >= JFXX_DATA_LEN && matches(&port, data, "JFXX"))
    {
        /* Found JFIF "JFXX" extension APP0 marker. The original leaves 'X' over ebx's low byte. */
        const uint32_t ebx = (datalen & ~0xffu) | 'X';
        const uint32_t code = port_u8(&port, data, 5);
        switch (code)
        {
            case 0x10:
                set_parm(&port, cinfo, 0, totallen);
                trace(&port, cinfo, JTRC_THUMB_JPEG, ebx);
                break;
            case 0x11:
                set_parm(&port, cinfo, 0, totallen);
                trace(&port, cinfo, JTRC_THUMB_PALETTE, ebx);
                break;
            case 0x13:
                set_parm(&port, cinfo, 0, totallen);
                trace(&port, cinfo, JTRC_THUMB_RGB, ebx);
                break;
            default:
                set_parm(&port, cinfo, 0, code);
                set_parm(&port, cinfo, 1, totallen);
                trace(&port, cinfo, JTRC_JFIF_EXTENSION, error_manager(&port, cinfo));
                break;
        }
    }
    else
    {
        /* Start of APP0 does not match "JFIF" or "JFXX", or too short. The original's ebx holds
         * data[2] in its low byte once the JFXX test has read it. */
        uint32_t ebx = datalen;
        if (datalen >= JFXX_DATA_LEN && port_u8(&port, data, 0) == 'J' &&
            port_u8(&port, data, 1) == 'F')
        {
            ebx = (datalen & ~0xffu) | port_u8(&port, data, 2);
        }
        set_parm(&port, cinfo, 0, totallen);
        trace(&port, cinfo, JTRC_APP0, ebx);
    }
    return port_return(&port, 0, 0);
}
