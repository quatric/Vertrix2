#include "rtlexceptionallocs.h"

enum
{
    /* The frame under the return slot: four saved registers and 0x3c bytes of locals, then the
     * entry's eax, edx and ebx pushed (from its low end S: ebx, edx, eax). Two argument records
     * for 0x4e36d2 lie at S+0xc and S+0x20 (their +0x10 cleared after the copy). */
    BELOW = 0x58,
    SAVED_EBX = 0,
    SAVED_EDX = 4,
    SAVED_EAX = 8,
    RECORD_ONE = 0xc,
    RECORD_TWO = 0x20,
    RECORD_ARGUMENT = 0x10,

    /* The exception memory: its lock (0x509828), its free list's head (0x509824, first set to one
     * block 0x509838 of the pool's size 0x509820 less 0x18). A free block: next, size. */
    LOCK = 0x509828,
    FREE_HEAD = 0x509824,
    POOL_SIZE = 0x509820,
    FIRST_BLOCK = 0x509838,
    BLOCK_NEXT = 0,
    BLOCK_SIZE = 4,
    BLOCK_HEADER = 0x18,
    MINIMUM = 0x18,
    OVERHEAD = 0x2b,

    /* The exception made, from the block's +4: the list link, the descriptor, its type, its kind
     * (5), two cleared fields, a flag and the value copied at +0x24. The thread data's list: +8. */
    EXCEPTION_LINK = 0,
    EXCEPTION_DESCRIPTOR = 4,
    EXCEPTION_TYPE = 8,
    EXCEPTION_KIND = 0xc,
    EXCEPTION_FLAGS = 0xe,
    EXCEPTION_FIELD_ONE = 0x1c,
    EXCEPTION_FIELD_TWO = 0x20,
    EXCEPTION_VALUE = 0x24,
    EXCEPTION_KIND_VALUE = 5,
    THREAD_EXCEPTIONS = 8,
    DESCRIPTOR_TYPE = 4,

    /* The type record: its kind, its size and its copy constructor. */
    TYPE_KIND = 0,
    TYPE_SIZE = 4,
    TYPE_COPY = 8,
    POINTER_SIZE = 4,
    RECORD_KIND = 5,

    OUT_OF_MEMORY = 0x51281d,

    LOCK_ENTER = 0x4e14b0,
    LOCK_LEAVE = 0x4e14b7,
    TYPE_RECORD = 0x4e37fe,
    TYPE_SIZE_OF = 0x4e6c98,
    FATAL = 0x4dee73,
    RECORD_STORE = 0x4e36d2,
    RECORD_RELEASE = 0x4e36e4,
    BAD_KIND = 0x4e0bf8
};

/* Copy-constructs the value through the type's constructor (+8) under an argument record. */
static void construct(Port *port, uint32_t frame, uint32_t record, uint32_t type,
                      uint32_t exception, int source_in_ebx)
{
    const uint32_t args[1] = {exception};
    port_call_stack(port, RECORD_STORE, frame + record, port_u32(port, frame, SAVED_EBX), 0,
                    RECORD_KIND, args, 1);
    const uint32_t source = port_u32(port, frame, SAVED_EAX);
    if (source_in_ebx)
    {
        port_call(port, port_u32(port, type, TYPE_COPY), exception + EXCEPTION_VALUE, 0, source,
                  RECORD_KIND);
    }
    else
    {
        port_call(port, port_u32(port, type, TYPE_COPY), exception + EXCEPTION_VALUE, source, 0,
                  RECORD_KIND);
    }
    port_set32(port, frame, record + RECORD_ARGUMENT, 0);
    port_call(port, RECORD_RELEASE, frame + record, 0, 0, RECORD_KIND);
}

/* Original 0x4e0c56 (eax = the value thrown, edx = its descriptor, ebx = the thread data): makes
 * a thrown exception. Under the lock 0x509828 a block of the type's size (0x4e6c98 of the type
 * record 0x4e37fe) + 0x2b, at least 0x18, rounded to 4 in its low word, is taken from the free
 * list (first set up as one block): adjacent free blocks are merged first, an exact fit is
 * unlinked, a block larger by more than 0x18 gives its end, else the walk goes on (an empty list
 * reports 0x51281d through 0x4dee73). The exception (the block + 4) is linked into the thread's
 * list (+8) and filled in, then the value is copied by kind: 0 and 4 by the type's copy
 * constructor (under an argument record, the source in edx or ebx), 3 and 8 by the type's size,
 * 1, 6 and 7 as a pointer, others reported by 0x4e0bf8. Returns the exception. The exception frame
 * at fs:[0] is left out (docs/NATIVE-PORTS.md). */
uint32_t vertrix_port_rtl_exception_allocate_4e0c56(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - BELOW;
    port_set32(&port, frame, SAVED_EBX, entry->ebx);
    port_set32(&port, frame, SAVED_EDX, entry->edx);
    port_set32(&port, frame, SAVED_EAX, entry->eax);
    port_call(&port, LOCK_ENTER, LOCK, entry->edx, entry->ebx, entry->ecx);
    if (port_u32(&port, FREE_HEAD, 0) == 0)
    {
        const uint32_t pool = port_u32(&port, POOL_SIZE, 0);
        port_set32(&port, FIRST_BLOCK, BLOCK_NEXT, 0);
        port_set32(&port, FREE_HEAD, 0, FIRST_BLOCK);
        port_set32(&port, FIRST_BLOCK, BLOCK_SIZE, pool - BLOCK_HEADER);
    }
    const uint32_t descriptor = entry->edx;
    const uint32_t type =
        port_call(&port, TYPE_RECORD, port_u32(&port, descriptor, DESCRIPTOR_TYPE),
                  vertrix_lift_edx, entry->ebx, entry->ecx);
    uint32_t size =
        port_call(&port, TYPE_SIZE_OF, type, vertrix_lift_edx, entry->ebx, entry->ecx) + OVERHEAD;
    if (size < MINIMUM)
    {
        size = MINIMUM;
    }
    size += 3;
    size = (size & 0xffff0000u) | (size & 0xfffc);
    const uint32_t larger = size + BLOCK_HEADER;
    uint32_t previous = FREE_HEAD;
    uint32_t block;
    uint32_t taken;
    for (;;)
    {
        block = port_u32(&port, previous, BLOCK_NEXT);
        if (block == 0)
        {
            port_call(&port, FATAL, OUT_OF_MEMORY, 1, previous, block);
        }
        uint32_t next = port_u32(&port, block, BLOCK_NEXT);
        while (block + port_u32(&port, block, BLOCK_SIZE) == next && !port.env.failed)
        {
            port_set32(&port, block, BLOCK_SIZE,
                       port_u32(&port, block, BLOCK_SIZE) + port_u32(&port, next, BLOCK_SIZE));
            next = port_u32(&port, next, BLOCK_NEXT);
            port_set32(&port, block, BLOCK_NEXT, next);
        }
        if (port.env.failed)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        if (size == port_u32(&port, block, BLOCK_SIZE))
        {
            taken = block;
            port_set32(&port, previous, BLOCK_NEXT, next);
            break;
        }
        if (larger < port_u32(&port, block, BLOCK_SIZE))
        {
            port_set32(&port, block, BLOCK_SIZE, port_u32(&port, block, BLOCK_SIZE) - size);
            taken = block + port_u32(&port, block, BLOCK_SIZE);
            break;
        }
        previous = block;
    }
    port_call(&port, LOCK_LEAVE, LOCK, vertrix_lift_edx, previous, block);
    port_set32(&port, taken, 0, size);
    port_set32(&port, taken, BLOCK_HEADER, POOL_SIZE);
    const uint32_t exception = taken + 4;
    const uint32_t thread = port_u32(&port, entry->ebx, 0);
    port_set32(&port, exception, EXCEPTION_LINK, port_u32(&port, thread, THREAD_EXCEPTIONS));
    port_set32(&port, thread, THREAD_EXCEPTIONS, exception);
    port_set8(&port, exception, EXCEPTION_KIND, EXCEPTION_KIND_VALUE);
    port_set32(&port, exception, EXCEPTION_FIELD_ONE, 0);
    port_set32(&port, exception, EXCEPTION_FIELD_TWO, 0);
    port_set32(&port, exception, EXCEPTION_TYPE, port_u32(&port, descriptor, DESCRIPTOR_TYPE));
    port_set8(&port, exception, EXCEPTION_FLAGS, port_u8(&port, exception, EXCEPTION_FLAGS) & 0xfe);
    port_set32(&port, exception, EXCEPTION_DESCRIPTOR, descriptor);
    const uint32_t kind = port_u8(&port, type, TYPE_KIND);
    uint32_t copied = 0;
    switch (kind)
    {
        case 0:
            construct(&port, frame, RECORD_ONE, type, exception, 0);
            break;
        case 4:
            construct(&port, frame, RECORD_TWO, type, exception, 1);
            break;
        case 3:
        case 8:
            copied = port_u32(&port, type, TYPE_SIZE);
            break;
        case 1:
        case 6:
        case 7:
            copied = POINTER_SIZE;
            break;
        default:
            port_call(&port, BAD_KIND, kind <= 8 ? kind : (descriptor & 0xffffff00u) | kind,
                      vertrix_lift_edx, previous, block);
            break;
    }
    for (uint32_t i = 0; i < copied && !port.env.failed; i++)
    {
        port_set8(&port, exception + EXCEPTION_VALUE + i, 0, port_u8(&port, entry->eax + i, 0));
    }
    return port_return(&port, exception, vertrix_lift_edx);
}
