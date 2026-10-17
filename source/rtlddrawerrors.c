#include "rtlddrawerrors.h"

/* The text of a DirectDraw error for the error messages: a prefix and the result code's name. */

enum
{
    /* The text's buffer. */
    ERROR_TEXT = 0x5b9a48
};

typedef struct
{
    uint32_t code;
    uint32_t name;
} ErrorName;

/* The codes the original tests (DirectDraw's 0x8876xxxx and the generic COM ones), with the
 * address of each one's name. */
static const ErrorName NAMES[] = {
    {0x80004001u, 0x5105fd}, /* DDERR_UNSUPPORTED */
    {0x80004005u, 0x510003}, /* DDERR_GENERIC */
    {0x800401f0u, 0x5103e2}, /* DDERR_NOTINITIALIZED */
    {0x8007000eu, 0x510474}, /* DDERR_OUTOFMEMORY */
    {0x80070057u, 0x5100e9}, /* DDERR_INVALIDPARAMS */
    {0x88760005u, 0x50fe91}, /* DDERR_ALREADYINITIALIZED */
    {0x8876000au, 0x50fec0}, /* DDERR_CANNOTATTACHSURFACE */
    {0x88760014u, 0x50feda}, /* DDERR_CANNOTDETACHSURFACE */
    {0x88760028u, 0x50ff87}, /* DDERR_CURRENTLYNOTAVAIL */
    {0x88760037u, 0x50ffd5}, /* DDERR_EXCEPTION */
    {0x8876005au, 0x510011}, /* DDERR_HEIGHTALIGN */
    {0x8876005fu, 0x510065}, /* DDERR_INCOMPATIBLEPRIMARY */
    {0x88760064u, 0x51007f}, /* DDERR_INVALIDCAPS */
    {0x8876006eu, 0x510091}, /* DDERR_INVALIDCLIPLIST */
    {0x88760078u, 0x5100c3}, /* DDERR_INVALIDMODE */
    {0x88760082u, 0x5100d5}, /* DDERR_INVALIDOBJECT */
    {0x88760091u, 0x5100fd}, /* DDERR_INVALIDPIXELFORMAT */
    {0x88760096u, 0x51012c}, /* DDERR_INVALIDRECT */
    {0x887600a0u, 0x510157}, /* DDERR_LOCKEDSURFACES */
    {0x887600aau, 0x51016c}, /* DDERR_NO3D */
    {0x887600b4u, 0x510177}, /* DDERR_NOALPHAHW */
    {0x887600cdu, 0x510195}, /* DDERR_NOCLIPLIST */
    {0x887600d2u, 0x5101be}, /* DDERR_NOCOLORCONVHW */
    {0x887600d4u, 0x5101f6}, /* DDERR_NOCOOPERATIVELEVELSET */
    {0x887600d7u, 0x5101d2}, /* DDERR_NOCOLORKEY */
    {0x887600dcu, 0x5101e3}, /* DDERR_NOCOLORKEYHW */
    {0x887600deu, 0x510243}, /* DDERR_NODIRECTDRAWSUPPORT */
    {0x887600e1u, 0x51026f}, /* DDERR_NOEXCLUSIVEMODE */
    {0x887600e6u, 0x510285}, /* DDERR_NOFLIPHW */
    {0x887600f0u, 0x510294}, /* DDERR_NOGDI */
    {0x887600fau, 0x5102be}, /* DDERR_NOMIRRORHW */
    {0x887600ffu, 0x5103d3}, /* DDERR_NOTFOUND */
    {0x88760104u, 0x5102e3}, /* DDERR_NOOVERLAYHW */
    {0x88760118u, 0x51031f}, /* DDERR_NORASTEROPHW */
    {0x88760122u, 0x510332}, /* DDERR_NOROTATIONHW */
    {0x88760136u, 0x510345}, /* DDERR_NOSTRETCHHW */
    {0x8876013cu, 0x510357}, /* DDERR_NOT4BITCOLOR */
    {0x8876013du, 0x51036a}, /* DDERR_NOT4BITCOLORINDEX */
    {0x88760140u, 0x510382}, /* DDERR_NOT8BITCOLOR */
    {0x8876014au, 0x5103ae}, /* DDERR_NOTEXTUREHW */
    {0x8876014fu, 0x51042f}, /* DDERR_NOVSYNCHW */
    {0x88760154u, 0x51043f}, /* DDERR_NOZBUFFERHW */
    {0x8876015eu, 0x510451}, /* DDERR_NOZOVERLAYHW */
    {0x88760168u, 0x510464}, /* DDERR_OUTOFCAPS */
    {0x8876017cu, 0x510486}, /* DDERR_OUTOFVIDEOMEMORY */
    {0x8876017eu, 0x51049d}, /* DDERR_OVERLAYCANTCLIP */
    {0x88760180u, 0x5104b3}, /* DDERR_OVERLAYCOLORKEYONLYONEACTIVE */
    {0x88760183u, 0x5104ee}, /* DDERR_PALETTEBUSY */
    {0x88760190u, 0x50ff72}, /* DDERR_COLORKEYNOTSET */
    {0x8876019au, 0x510537}, /* DDERR_SURFACEALREADYATTACHED */
    {0x887601a4u, 0x510554}, /* DDERR_SURFACEALREADYDEPENDENT */
    {0x887601aeu, 0x510572}, /* DDERR_SURFACEBUSY */
    {0x887601b3u, 0x50ff1b}, /* DDERR_CANTLOCKSURFACE */
    {0x887601b8u, 0x510584}, /* DDERR_SURFACEISOBSCURED */
    {0x887601c2u, 0x51059c}, /* DDERR_SURFACELOST */
    {0x887601ccu, 0x5105ae}, /* DDERR_SURFACENOTATTACHED */
    {0x887601d6u, 0x5105c7}, /* DDERR_TOOBIGHEIGHT */
    {0x887601e0u, 0x5105da}, /* DDERR_TOOBIGSIZE */
    {0x887601eau, 0x5105eb}, /* DDERR_TOOBIGWIDTH */
    {0x887601feu, 0x51060f}, /* DDERR_UNSUPPORTEDFORMAT */
    {0x88760208u, 0x510627}, /* DDERR_UNSUPPORTEDMASK */
    {0x88760219u, 0x510653}, /* DDERR_VERTICALBLANKINPROGRESS */
    {0x8876021cu, 0x510671}, /* DDERR_WASSTILLDRAWING */
    {0x88760230u, 0x510697}, /* DDERR_XALIGN */
    {0x88760231u, 0x5100a7}, /* DDERR_INVALIDDIRECTDRAWGUID */
    {0x88760232u, 0x50ffb6}, /* DDERR_DIRECTDRAWALREADYCREATED */
    {0x88760233u, 0x51022e}, /* DDERR_NODIRECTDRAWHW */
    {0x88760234u, 0x510500}, /* DDERR_PRIMARYSURFACEALREADYEXISTS */
    {0x88760235u, 0x51025d}, /* DDERR_NOEMULATION */
    {0x88760236u, 0x510522}, /* DDERR_REGIONTOOSMALL */
    {0x88760237u, 0x50ff59}, /* DDERR_CLIPPERISUSINGHWND */
    {0x88760238u, 0x5101a6}, /* DDERR_NOCLIPPERATTACHED */
    {0x88760239u, 0x5102a0}, /* DDERR_NOHWND */
    {0x8876023au, 0x510038}, /* DDERR_HWNDSUBCLASSED */
    {0x8876023bu, 0x510023}, /* DDERR_HWNDALREADYSET */
    {0x8876023cu, 0x5102f5}, /* DDERR_NOPALETTEATTACHED */
    {0x8876023du, 0x51030d}, /* DDERR_NOPALETTEHW */
    {0x8876023eu, 0x50feaa}, /* DDERR_BLTFASTCANTCLIP */
    {0x8876023fu, 0x510187}, /* DDERR_NOBLTHW */
    {0x88760240u, 0x51021d}, /* DDERR_NODDROPSHW */
    {0x88760241u, 0x5104d6}, /* DDERR_OVERLAYNOTVISIBLE */
    {0x88760242u, 0x5102cf}, /* DDERR_NOOVERLAYDEST */
    {0x88760243u, 0x510116}, /* DDERR_INVALIDPOSITION */
    {0x88760244u, 0x510395}, /* DDERR_NOTAOVERLAYSURFACE */
    {0x88760245u, 0x50ffe5}, /* DDERR_EXCLUSIVEMODEALREADYSET */
    {0x88760246u, 0x5103c0}, /* DDERR_NOTFLIPPABLE */
    {0x88760247u, 0x50ff07}, /* DDERR_CANTDUPLICATE */
    {0x88760248u, 0x5103f7}, /* DDERR_NOTLOCKED */
    {0x88760249u, 0x50fef4}, /* DDERR_CANTCREATEDC */
    {0x8876024au, 0x510212}, /* DDERR_NODC */
    {0x8876024bu, 0x510687}, /* DDERR_WRONGMODE */
    {0x8876024cu, 0x51004d}, /* DDERR_IMPLICITLYCREATED */
    {0x8876024du, 0x51041b}, /* DDERR_NOTPALETTIZED */
    {0x8876024eu, 0x51063d}, /* DDERR_UNSUPPORTEDMODE */
    {0x8876024fu, 0x5102ad}, /* DDERR_NOMIPMAPHW */
    {0x88760250u, 0x51013e}, /* DDERR_INVALIDSURFACETYPE */
    {0x8876026cu, 0x50ff9f}, /* DDERR_DCALREADYCREATED */
    {0x88760280u, 0x50ff31}, /* DDERR_CANTPAGELOCK */
    {0x88760294u, 0x50ff44}, /* DDERR_CANTPAGEUNLOCK */
    {0x887602a8u, 0x510407}, /* DDERR_NOTPAGELOCKED */
};

/* strcpy inside the original's address space. */
static void copy(Port *port, uint32_t to, uint32_t from)
{
    uint32_t c;
    do
    {
        c = port_u8(port, from++, 0);
        port_set8(port, to++, 0, c);
    } while (c != 0 && !port->env.failed);
}

/* strcat: the copy after the text already there. */
static void append(Port *port, uint32_t to, uint32_t from)
{
    while (port_u8(port, to, 0) != 0 && !port->env.failed)
    {
        to++;
    }
    copy(port, to, from);
}

/* Original 0x485700 (ebx = the prefix, ecx = the result code): the prefix copied to 0x5b9a48 and,
 * for a code it knows, the code's name after it; an unknown code adds nothing. Its callers read
 * eax: the caller's, with the low byte the copy's terminating 0. */
uint32_t vertrix_port_ddraw_error_text_485700(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    copy(&port, ERROR_TEXT, entry->ebx);
    for (size_t i = 0; i < sizeof NAMES / sizeof NAMES[0]; i++)
    {
        if (NAMES[i].code == entry->ecx)
        {
            append(&port, ERROR_TEXT, NAMES[i].name);
            break;
        }
    }
    return port_return(&port, entry->eax & 0xffffff00u, 0);
}
