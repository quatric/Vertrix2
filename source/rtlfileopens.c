#include "rtlfileopens.h"

enum
{
    /* The frame under the return slot: three saved registers, then (from its low end S) the
     * security attributes (S: length, descriptor, inherit), the share mode (S+0xc), the access
     * (S+0x10), the permission mode (S+0x14), the creation retried (S+0x18) and the flags
     * (S+0x1c). */
    BELOW = 0x2c,
    ATTRIBUTES = 0,
    ATTRIBUTES_LENGTH = 0xc,
    SHARE = 0xc,
    ACCESS = 0x10,
    PERMISSION = 0x14,
    RETRY_CREATION = 0x18,
    FLAGS = 0x1c,

    /* The open flags: the access mode (bits 0-2), no inheriting, create, truncate, the binary and
     * text modes, and exclusive. */
    ACCESS_MASK = 7,
    ACCESS_READ = 0,
    ACCESS_WRITE = 1,
    ACCESS_BOTH = 2,
    O_APPEND = 0x10,
    O_CREAT = 0x20,
    O_TRUNC = 0x40,
    O_NOINHERIT = 0x80,
    O_BINARY = 0x100,
    O_TEXT = 0x200,
    O_EXCL = 0x400,
    /* The permission's write and read bits. */
    S_IWRITE = 0x80,
    S_IREAD = 0x100,

    CREATE_NEW = 1,
    CREATE_ALWAYS = 2,
    OPEN_EXISTING = 3,
    OPEN_ALWAYS = 4,
    TRUNCATE_EXISTING = 5,
    FILE_ATTRIBUTE_READONLY = 1,
    FILE_ATTRIBUTE_NORMAL = 0x80,
    INVALID_HANDLE = 0xffffffffu,

    /* The handle's mode bits: read, write, both, append, device, text. */
    MODE_READ = 1,
    MODE_WRITE = 2,
    MODE_BOTH = 3,
    MODE_APPEND = 0x80,
    MODE_DEVICE = 0x2000,
    MODE_TEXT = 0x40,
    DEFAULT_TEXT = 0x200,

    EMFILE_CODE = 0xb,
    EBADF_CODE = 5,

    UMASK = 0x507d54,
    HANDLE_LIMIT = 0x507c34,
    DEFAULT_MODE = 0x505440,
    MAKE_HANDLE_SLOT = 0x507ca8,
    DEVICE_OPEN = 0x507d04,
    DEVICE_NAME = 0x5123a8,

    HANDLES_FULL = 0x4e0250,
    SET_ERRNO = 0x4dae70,
    OPEN_MODES = 0x4e0960,
    SHARE_MODE = 0x4e0994,
    COMPARE_NOCASE = 0x4e09f0,
    MAKE_HANDLE = 0x4e0490,
    MAP_ERROR = 0x4e0884,
    IS_DEVICE = 0x4e0a30,
    SET_HANDLE_MODE = 0x4e0228,
    CREATE_FILE = 0x4f1b34,
    CLOSE_HANDLE = 0x4f1b2c
};

/* CreateFileA with the frame's access and share mode. */
static uint32_t create_file(Port *port, uint32_t path, uint32_t frame, uint32_t attributes,
                            uint32_t creation, uint32_t flags_and_attributes, uint32_t edx)
{
    const uint32_t access = port_u32(port, frame, ACCESS);
    const uint32_t share = port_u32(port, frame, SHARE);
    const uint32_t args[7] = {path, access, share, attributes, creation, flags_and_attributes, 0};
    return port_call_stack(port, CREATE_FILE, attributes, edx, share, access, args, 7);
}

/* Original 0x4cd56c (eax = the path, edx = the open flags, ebx = the share flags, ecx = the
 * variable arguments, holding the permission mode with O_CREAT): the runtime's open. With every
 * handle slot taken (0x4e0250) it sets errno 0xb and returns -1. The access and creation (0x4e0960)
 * and share mode (0x4e0994) come from the flags; the handle inherits unless O_NOINHERIT. A device
 * name (0x5123a8 against the path, when the hook 0x507d04 is set) opens through that hook.
 * Otherwise CreateFileA: with O_CREAT the umasked permission (read-only without S_IWRITE but with
 * S_IREAD) and CREATE_NEW when exclusive, else CREATE_NEW then CREATE_ALWAYS when truncating, else
 * OPEN_EXISTING then OPEN_ALWAYS (the retry without the attributes); without it OPEN_EXISTING, or
 * TRUNCATE_EXISTING when truncating. A failure maps the error (0x4e0884, its eax returned). The
 * handle gets a slot (0x507ca8; past the limit 0x507c34 it is closed and errno 5 returned as -1),
 * and the slot's mode (0x4e0228): the access, append, device (0x4e0a30) and text bits. Returns the
 * slot. */
uint32_t vertrix_port_rtl_open_4cd56c(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t path = entry->eax;
    const uint32_t frame = entry->esp - BELOW;
    port_set32(&port, frame, FLAGS, entry->edx);
    if (port_call(&port, HANDLES_FULL, path, entry->edx, entry->ebx, entry->ecx) != 0)
    {
        port_call(&port, SET_ERRNO, EMFILE_CODE, vertrix_lift_edx, entry->ebx, entry->ecx);
        return port_return(&port, INVALID_HANDLE, vertrix_lift_edx);
    }
    const uint32_t access_mode = vertrix_lift_edx & ACCESS_MASK;
    port_call(&port, OPEN_MODES, access_mode, frame + ACCESS, frame + PERMISSION, entry->ecx);
    port_call(&port, SHARE_MODE, entry->ebx | access_mode, frame + SHARE, 0, entry->ecx);
    const uint32_t flags = port_u8(&port, frame, FLAGS);
    port_set32(&port, frame, ATTRIBUTES, ATTRIBUTES_LENGTH);
    port_set32(&port, frame, ATTRIBUTES + 4, 0);
    port_set32(&port, frame, ATTRIBUTES + 8, (flags & O_NOINHERIT) == 0);

    uint32_t slot;
    uint32_t mode;
    /* The edx the original carries into CreateFileA (imports keep it): 0xc, or the name
     * compare's, with the flags' low byte, or the variable argument pointer, or 1. */
    uint32_t edx = ATTRIBUTES_LENGTH;
    const int hooked = port_u32(&port, DEVICE_OPEN, 0) != 0;
    uint32_t compared = 1;
    if (hooked)
    {
        compared = port_call(&port, COMPARE_NOCASE, path, DEVICE_NAME, 0, entry->ecx);
        edx = vertrix_lift_edx;
    }
    if (hooked && compared == 0)
    {
        const uint32_t handle = port_call(&port, MAKE_HANDLE, 0, vertrix_lift_edx, 0, entry->ecx);
        slot = port_call(&port, port_u32(&port, MAKE_HANDLE_SLOT, 0), handle, vertrix_lift_edx, 0,
                         entry->ecx);
        const uint32_t args[3] = {0, slot, INVALID_HANDLE};
        port_call_stack(&port, port_u32(&port, DEVICE_OPEN, 0), slot, MODE_DEVICE, 0, slot, args,
                        3);
        mode = vertrix_lift_edx;
    }
    else
    {
        uint32_t attributes = FILE_ATTRIBUTE_NORMAL;
        uint32_t creation;
        edx = (edx & 0xffffff00u) | flags;
        if ((flags & O_CREAT) != 0)
        {
            const uint32_t arguments = entry->ecx;
            const uint32_t next = port_u32(&port, arguments, 0) + 4;
            edx = next;
            port_set32(&port, arguments, 0, next);
            port_set32(&port, frame, PERMISSION, port_u32(&port, next, -4u));
            port_set32(&port, arguments, 0, 0);
            const uint32_t permission =
                port_u32(&port, frame, PERMISSION) & ~port_u32(&port, UMASK, 0);
            port_set32(&port, frame, PERMISSION, permission);
            if ((permission & S_IREAD) != 0 && (permission & S_IWRITE) == 0)
            {
                attributes = FILE_ATTRIBUTE_READONLY;
            }
            const uint32_t flags_high = port_u8(&port, frame, FLAGS + 1) << 8;
            if ((flags_high & O_EXCL) != 0)
            {
                port_set32(&port, frame, RETRY_CREATION, CREATE_NEW);
                creation = CREATE_NEW;
                edx = 1;
            }
            else if ((flags & O_TRUNC) != 0)
            {
                port_set32(&port, frame, RETRY_CREATION, CREATE_ALWAYS);
                creation = CREATE_NEW;
            }
            else
            {
                port_set32(&port, frame, RETRY_CREATION, OPEN_ALWAYS);
                creation = OPEN_EXISTING;
            }
        }
        else
        {
            creation = (flags & O_TRUNC) != 0 ? TRUNCATE_EXISTING : OPEN_EXISTING;
        }
        uint32_t handle =
            create_file(&port, path, frame, frame + ATTRIBUTES, creation, attributes, edx);
        if (handle == INVALID_HANDLE && (port_u8(&port, frame, FLAGS) & O_CREAT) != 0)
        {
            handle = create_file(&port, path, frame, 0, port_u32(&port, frame, RETRY_CREATION),
                                 attributes, port_u32(&port, frame, ACCESS));
        }
        if (handle == INVALID_HANDLE)
        {
            const uint32_t mapped = port_call(&port, MAP_ERROR, handle, vertrix_lift_edx, handle,
                                              port_u32(&port, frame, ACCESS));
            return port_return(&port, mapped, vertrix_lift_edx);
        }
        slot = port_call(&port, port_u32(&port, MAKE_HANDLE_SLOT, 0), handle, vertrix_lift_edx,
                         handle, port_u32(&port, frame, ACCESS));
        if (slot >= port_u32(&port, HANDLE_LIMIT, 0))
        {
            const uint32_t args[1] = {handle};
            port_call_stack(&port, CLOSE_HANDLE, slot, 0, handle, slot, args, 1);
            port_call(&port, SET_ERRNO, EBADF_CODE, vertrix_lift_edx, handle, slot);
            return port_return(&port, INVALID_HANDLE, vertrix_lift_edx);
        }
        mode = port_call(&port, IS_DEVICE, slot, 0, handle, slot) != 0 ? MODE_DEVICE : 0;
    }
    if (access_mode == ACCESS_BOTH)
    {
        mode |= MODE_BOTH;
    }
    else if (access_mode == ACCESS_READ)
    {
        mode |= MODE_READ;
    }
    else if (access_mode == ACCESS_WRITE)
    {
        mode |= MODE_WRITE;
    }
    if ((port_u8(&port, frame, FLAGS) & O_APPEND) != 0)
    {
        mode |= MODE_APPEND;
    }
    const uint32_t text = mode | MODE_TEXT;
    const uint32_t flags_high = port_u8(&port, frame, FLAGS + 1) << 8;
    if ((flags_high & (O_TEXT | O_BINARY)) != 0)
    {
        if ((flags_high & O_TEXT) != 0)
        {
            mode = text;
        }
    }
    else if (port_u32(&port, DEFAULT_MODE, 0) == DEFAULT_TEXT)
    {
        mode = text;
    }
    port_call(&port, SET_HANDLE_MODE, slot, mode, flags_high >> 8, slot);
    return port_return(&port, slot, vertrix_lift_edx);
}
