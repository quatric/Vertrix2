#include "process.h"

#include <string.h>

/* GDI without a screen. The game draws through DirectDraw; its framework (MFC) still sets up
 * device contexts, fonts, brushes and pens, asks about the display and measures text. Each
 * created object gets a handle that remembers its type, the display reports 640x480 at 16 bits,
 * and drawing has no effect. */

enum
{
    OBJ_PEN = 1,
    OBJ_BRUSH = 2,
    OBJ_DC = 3,
    OBJ_PAL = 5,
    OBJ_FONT = 6,
    OBJ_BITMAP = 7,
    OBJ_REGION = 8,
    OBJ_EXTPEN = 11,
    STOCK_BASE = 0x01900000u,
    OBJECT_BASE = 0x01a00000u,
    OBJECTS = 4096,
    FONT_HEIGHT = 16,
    FONT_WIDTH = 7
};

static uint8_t object_types[OBJECTS];
static uint32_t next_object;

static uint32_t new_object(int type)
{
    uint32_t i = next_object++ % OBJECTS;
    object_types[i] = (uint8_t)type;
    return OBJECT_BASE + 1u + i;
}

/* The types of the stock objects GetStockObject(0..19) hands out. */
static int stock_type(uint32_t index)
{
    if (index <= 5)
    {
        return OBJ_BRUSH;
    }
    if (index <= 8)
    {
        return OBJ_PEN;
    }
    if (index == 15)
    {
        return OBJ_PAL;
    }
    if (index == 21)
    {
        return OBJ_BITMAP;
    }
    return OBJ_FONT;
}

static int object_type(uint32_t handle)
{
    if (handle >= STOCK_BASE && handle < STOCK_BASE + 32u)
    {
        return stock_type(handle - STOCK_BASE);
    }
    if (handle > OBJECT_BASE && handle <= OBJECT_BASE + OBJECTS)
    {
        return object_types[handle - OBJECT_BASE - 1u];
    }
    return handle ? OBJ_DC : 0;
}

static void write_pair(uint32_t address, uint32_t x, uint32_t y)
{
    if (address)
    {
        v3_w32(address, x);
        v3_w32(address + 4u, y);
    }
}

static void GetDeviceCaps(Cpu *c)
{
    uint32_t value;
    switch (ARG(1))
    {
        case 0: /* DRIVERVERSION */
            value = 0x400;
            break;
        case 2: /* TECHNOLOGY: DT_RASDISPLAY */
            value = 1;
            break;
        case 4: /* HORZSIZE, mm */
            value = 320;
            break;
        case 6: /* VERTSIZE, mm */
            value = 240;
            break;
        case 8: /* HORZRES */
            value = 640;
            break;
        case 10: /* VERTRES */
            value = 480;
            break;
        case 12: /* BITSPIXEL */
            value = 16;
            break;
        case 14: /* PLANES */
            value = 1;
            break;
        case 24: /* NUMCOLORS */
            value = 0xffffffffu;
            break;
        case 38: /* RASTERCAPS: BITBLT, BITMAP64, DI_BITMAP, DIBTODEV, STRETCHBLT, STRETCHDIB */
            value = 0x0001u | 0x0008u | 0x0080u | 0x0200u | 0x0800u | 0x2000u;
            break;
        case 88: /* LOGPIXELSX */
        case 90: /* LOGPIXELSY */
            value = 96;
            break;
        case 116: /* VREFRESH */
            value = 60;
            break;
        case 118: /* DESKTOPVERTRES */
            value = 480;
            break;
        case 117: /* DESKTOPHORZRES */
            value = 640;
            break;
        default:
            value = 0;
            break;
    }
    STDCALL_RETURN(2, value);
}

static void GetStockObject(Cpu *c)
{
    STDCALL_RETURN(1, STOCK_BASE + (ARG(0) & 31u));
}

static void GetObjectType(Cpu *c)
{
    STDCALL_RETURN(1, object_type(ARG(0)));
}

static void GetObjectA(Cpu *c)
{
    uint32_t handle = ARG(0), size = ARG(1), out = ARG(2);
    uint32_t needed;
    switch (object_type(handle))
    {
        case OBJ_PEN:
            needed = 16; /* LOGPEN */
            break;
        case OBJ_BRUSH:
            needed = 12; /* LOGBRUSH */
            break;
        case OBJ_BITMAP:
            needed = 24; /* BITMAP */
            break;
        case OBJ_PAL:
            needed = 2; /* the entry count */
            break;
        default:
            needed = 60; /* LOGFONTA */
            break;
    }
    if (!out)
    {
        STDCALL_RETURN(3, needed);
    }
    uint32_t n = size < needed ? size : needed;
    for (uint32_t i = 0; i < n; ++i)
    {
        v3_w8(out + i, 0);
    }
    if (object_type(handle) == OBJ_FONT && n >= 8)
    {
        v3_w32(out, (uint32_t)-FONT_HEIGHT); /* lfHeight */
        v3_w32(out + 4u, FONT_WIDTH);        /* lfWidth */
    }
    STDCALL_RETURN(3, n);
}

static void GetTextMetricsA(Cpu *c)
{
    uint32_t out = ARG(1);
    for (uint32_t i = 0; i < 56; ++i)
    {
        v3_w8(out + i, 0);
    }
    v3_w32(out, FONT_HEIGHT);          /* tmHeight */
    v3_w32(out + 4u, FONT_HEIGHT - 3); /* tmAscent */
    v3_w32(out + 8u, 3);               /* tmDescent */
    v3_w32(out + 20u, FONT_WIDTH);     /* tmAveCharWidth */
    v3_w32(out + 24u, 2 * FONT_WIDTH); /* tmMaxCharWidth */
    v3_w32(out + 28u, 400);            /* tmWeight */
    v3_w32(out + 36u, 96);             /* tmDigitizedAspectX */
    v3_w32(out + 40u, 96);             /* tmDigitizedAspectY */
    v3_w8(out + 44u, ' ');             /* tmFirstChar */
    v3_w8(out + 45u, 0xff);            /* tmLastChar */
    v3_w8(out + 46u, '?');             /* tmDefaultChar */
    v3_w8(out + 47u, ' ');             /* tmBreakChar */
    v3_w8(out + 51u, 0x06);            /* tmPitchAndFamily: variable pitch, TrueType */
    STDCALL_RETURN(2, 1);
}

static void GetTextExtentPointA(Cpu *c)
{
    write_pair(ARG(3), ARG(2) * FONT_WIDTH, FONT_HEIGHT);
    STDCALL_RETURN(4, 1);
}

static void GetClipBox(Cpu *c)
{
    uint32_t rect = ARG(1);
    write_pair(rect, 0, 0);
    write_pair(rect + 8u, 640, 480);
    STDCALL_RETURN(2, 2); /* SIMPLEREGION */
}

static void SaveDC(Cpu *c)
{
    static uint32_t depth;
    STDCALL_RETURN(1, ++depth);
}

static void SelectObject(Cpu *c)
{
    /* The previous object: a stock object of the same type. */
    switch (object_type(ARG(1)))
    {
        case OBJ_PEN:
        case OBJ_EXTPEN:
            STDCALL_RETURN(2, STOCK_BASE + 7u); /* BLACK_PEN */
        case OBJ_BRUSH:
            STDCALL_RETURN(2, STOCK_BASE + 0u); /* WHITE_BRUSH */
        case OBJ_REGION:
            STDCALL_RETURN(2, 2); /* SIMPLEREGION */
        case OBJ_BITMAP:
            STDCALL_RETURN(2, STOCK_BASE + 21u);
        default:
            STDCALL_RETURN(2, STOCK_BASE + 13u); /* SYSTEM_FONT */
    }
}

/* Functions that set a value and return the previous one, or the old origin or extent. */
#define SETTER(name, args, previous)                                                               \
    static void name(Cpu *c)                                                                       \
    {                                                                                              \
        STDCALL_RETURN(args, previous);                                                            \
    }
#define PAIR(name, args, out, x, y)                                                                \
    static void name(Cpu *c)                                                                       \
    {                                                                                              \
        write_pair(ARG(out), x, y);                                                                \
        STDCALL_RETURN(args, 1);                                                                   \
    }
#define CREATE(name, args, type)                                                                   \
    static void name(Cpu *c)                                                                       \
    {                                                                                              \
        STDCALL_RETURN(args, new_object(type));                                                    \
    }

CREATE(CreateBitmap, 5, OBJ_BITMAP)
CREATE(CreateDIBPatternBrushPt, 2, OBJ_BRUSH)
CREATE(CreateFontIndirectA, 1, OBJ_FONT)
CREATE(CreateHatchBrush, 2, OBJ_BRUSH)
CREATE(CreatePatternBrush, 1, OBJ_BRUSH)
CREATE(CreatePen, 3, OBJ_PEN)
CREATE(CreateRectRgn, 4, OBJ_REGION)
CREATE(CreateSolidBrush, 1, OBJ_BRUSH)
CREATE(ExtCreatePen, 5, OBJ_EXTPEN)

SETTER(ArcTo, 9, 1)
SETTER(DeleteDC, 1, 1)
SETTER(DeleteObject, 1, 1)
SETTER(EnumMetaFile, 4, 1)
SETTER(Escape, 5, 0)
SETTER(ExcludeClipRect, 5, 2)
SETTER(ExtSelectClipRgn, 3, 2)
SETTER(ExtTextOutA, 8, 1)
SETTER(GetClipRgn, 2, 0)
SETTER(IntersectClipRect, 5, 2)
SETTER(LineTo, 3, 1)
SETTER(OffsetClipRgn, 3, 2)
SETTER(PlayMetaFileRecord, 4, 1)
SETTER(PlayMetaFile, 2, 1)
SETTER(PolyBezierTo, 3, 1)
SETTER(PolyDraw, 4, 1)
SETTER(PolylineTo, 3, 1)
SETTER(PtVisible, 3, 1)
SETTER(RectVisible, 2, 1)
SETTER(RestoreDC, 2, 1)
SETTER(SelectClipPath, 2, 1)
SETTER(SelectClipRgn, 2, 2)
SETTER(SelectPalette, 3, STOCK_BASE + 15u)
SETTER(SetArcDirection, 2, 1)
SETTER(SetBkColor, 2, 0x00ffffffu)
SETTER(SetBkMode, 2, 2)
SETTER(SetColorAdjustment, 2, 1)
SETTER(SetMapMode, 2, 1)
SETTER(SetMapperFlags, 2, 0)
SETTER(SetPolyFillMode, 2, 1)
SETTER(SetROP2, 2, 13)
SETTER(SetStretchBltMode, 2, 1)
SETTER(SetTextAlign, 2, 0)
SETTER(SetTextCharacterExtra, 2, 0)
SETTER(SetTextColor, 2, 0)
SETTER(SetTextJustification, 3, 1)
SETTER(StartDocA, 2, 0)
SETTER(TextOutA, 5, 1)

PAIR(GetCurrentPositionEx, 2, 1, 0, 0)
PAIR(GetViewportExtEx, 2, 1, 1, 1)
PAIR(GetWindowExtEx, 2, 1, 1, 1)
PAIR(MoveToEx, 4, 3, 0, 0)
PAIR(OffsetViewportOrgEx, 4, 3, 0, 0)
PAIR(OffsetWindowOrgEx, 4, 3, 0, 0)
PAIR(ScaleViewportExtEx, 6, 5, 1, 1)
PAIR(ScaleWindowExtEx, 6, 5, 1, 1)
PAIR(SetViewportExtEx, 4, 3, 1, 1)
PAIR(SetViewportOrgEx, 4, 3, 0, 0)
PAIR(SetWindowExtEx, 4, 3, 1, 1)
PAIR(SetWindowOrgEx, 4, 3, 0, 0)

#define EXPORT(name) {#name, name}
const V3Export v3_gdi32[] = {EXPORT(ArcTo),
                             EXPORT(CreateBitmap),
                             EXPORT(CreateDIBPatternBrushPt),
                             EXPORT(CreateFontIndirectA),
                             EXPORT(CreateHatchBrush),
                             EXPORT(CreatePatternBrush),
                             EXPORT(CreatePen),
                             EXPORT(CreateRectRgn),
                             EXPORT(CreateSolidBrush),
                             EXPORT(DeleteDC),
                             EXPORT(DeleteObject),
                             EXPORT(EnumMetaFile),
                             EXPORT(Escape),
                             EXPORT(ExcludeClipRect),
                             EXPORT(ExtCreatePen),
                             EXPORT(ExtSelectClipRgn),
                             EXPORT(ExtTextOutA),
                             EXPORT(GetClipBox),
                             EXPORT(GetClipRgn),
                             EXPORT(GetCurrentPositionEx),
                             EXPORT(GetDeviceCaps),
                             EXPORT(GetObjectA),
                             EXPORT(GetObjectType),
                             EXPORT(GetStockObject),
                             EXPORT(GetTextExtentPointA),
                             EXPORT(GetTextMetricsA),
                             EXPORT(GetViewportExtEx),
                             EXPORT(GetWindowExtEx),
                             EXPORT(IntersectClipRect),
                             EXPORT(LineTo),
                             EXPORT(MoveToEx),
                             EXPORT(OffsetClipRgn),
                             EXPORT(OffsetViewportOrgEx),
                             EXPORT(OffsetWindowOrgEx),
                             EXPORT(PlayMetaFileRecord),
                             EXPORT(PlayMetaFile),
                             EXPORT(PolyBezierTo),
                             EXPORT(PolyDraw),
                             EXPORT(PolylineTo),
                             EXPORT(PtVisible),
                             EXPORT(RectVisible),
                             EXPORT(RestoreDC),
                             EXPORT(SaveDC),
                             EXPORT(ScaleViewportExtEx),
                             EXPORT(ScaleWindowExtEx),
                             EXPORT(SelectClipPath),
                             EXPORT(SelectClipRgn),
                             EXPORT(SelectObject),
                             EXPORT(SelectPalette),
                             EXPORT(SetArcDirection),
                             EXPORT(SetBkColor),
                             EXPORT(SetBkMode),
                             EXPORT(SetColorAdjustment),
                             EXPORT(SetMapMode),
                             EXPORT(SetMapperFlags),
                             EXPORT(SetPolyFillMode),
                             EXPORT(SetROP2),
                             EXPORT(SetStretchBltMode),
                             EXPORT(SetTextAlign),
                             EXPORT(SetTextCharacterExtra),
                             EXPORT(SetTextColor),
                             EXPORT(SetTextJustification),
                             EXPORT(SetViewportExtEx),
                             EXPORT(SetViewportOrgEx),
                             EXPORT(SetWindowExtEx),
                             EXPORT(SetWindowOrgEx),
                             EXPORT(StartDocA),
                             EXPORT(TextOutA),
                             {NULL, NULL}};
