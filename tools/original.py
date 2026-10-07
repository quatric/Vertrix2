"""Execute identified original x86 routines as a development-time oracle.

The Wii code does not depend on this module or execute x86 instructions.
"""

import hashlib
import os
import struct
from pathlib import Path

import pefile
from unicorn import UC_ARCH_X86, UC_MODE_32, UC_HOOK_CODE, Uc
from unicorn.x86_const import (
    UC_X86_REG_EAX,
    UC_X86_REG_EBX,
    UC_X86_REG_ECX,
    UC_X86_REG_EDX,
    UC_X86_REG_EIP,
    UC_X86_REG_ESP,
    UC_X86_REG_ESI,
)

EXECUTABLE_SHA256 = "4db546b7957136179bedf22a37b7e5db401ea25bc668b715643adf84ce525e28"
BOARD = 0x800000
MASK = 0x801000
COUNTER = 0x802000
BLOCKS = 0x804000
STACK = 0x708000
RETURN = 0x700000


def original_image(pe):
    """Map initialized bytes and zero uninitialized sections without file backing."""
    image = bytearray(pe.get_memory_mapped_image())
    for section in pe.sections:
        if section.Characteristics & 0x80 and not section.PointerToRawData:
            extent = max(section.Misc_VirtualSize, section.SizeOfRawData)
            start = section.VirtualAddress
            if start + extent > pe.OPTIONAL_HEADER.SizeOfImage:
                raise ValueError("Uninitialized section exceeds the loaded image")
            if start + extent > len(image):
                image.extend(bytes(start + extent - len(image)))
            image[start:start + extent] = bytes(extent)
    return bytes(image)


class Original:
    def __init__(self, executable):
        data = Path(executable).read_bytes()
        if hashlib.sha256(data).hexdigest() != EXECUTABLE_SHA256:
            raise ValueError("This oracle requires the verified Vertrix 2 v2.0 executable")
        self.pe = pefile.PE(data=data)
        self.cpu = Uc(UC_ARCH_X86, UC_MODE_32)
#Supply the original single - thread SEH chain storage for constructors.
        self.cpu.mem_map(0, 0x1000)
        self.cpu.mem_map(0x400000, 0x200000)
#This Borland PE reports a nonzero raw size for.bss but no raw - data
#pointer.pefile's mapped image copies file-offset-zero bytes there.
#The loader reserves zero - filled uninitialized data instead.Preserve
#initialized sections and clear only explicitly uninitialized backing.
        self.cpu.mem_write(0x400000, original_image(self.pe))
        self.cpu.mem_map(0x700000, 0x10000)
        self.cpu.mem_map(0x800000, 0x10000)
#The CRT asks for thread - local storage through this function pointer.
#Supply storage for the single oracle thread.The original srand / rand
#code and all their arithmetic still execute unchanged.
        self.cpu.mem_write(0x700100, b"\xb8\x00\x30\x80\x00\xc3")
        self.cpu.mem_write(0x507C9C, struct.pack("<I", 0x700100))
        self.call(0x417C80)

    def call(self, address, eax=BOARD, edx=MASK, ebx=0, ecx=0, args=(), stop=RETURN):
        self.cpu.mem_write(STACK, struct.pack("<" + "I" * (1 + len(args)), RETURN, *args))
        for register, value in (
            (UC_X86_REG_ESP, STACK),
            (UC_X86_REG_EAX, eax),
            (UC_X86_REG_EDX, edx),
            (UC_X86_REG_EBX, ebx),
            (UC_X86_REG_ECX, ecx),
        ):
            self.cpu.reg_write(register, value)
        self.cpu.emu_start(address, stop, count=int(os.environ.get('VERTRIX_ORACLE_LIMIT', 1_000_000)))
        if self.cpu.reg_read(UC_X86_REG_EIP) != stop:
            raise RuntimeError(f"Original routine {address:#x} did not reach its return boundary")
        return self.cpu.reg_read(UC_X86_REG_EAX)

    def read_mask(self):
        return list(struct.unpack("<65I", self.cpu.mem_read(MASK, 260)))

    def matches(self, board, threshold, figures):
        self.cpu.mem_write(BOARD, bytes(board))
        self.cpu.mem_write(MASK, bytes(260))
        self.cpu.mem_write(COUNTER, bytes(4))
        if figures:
            self.call(0x434EE0, ecx=1, args=(COUNTER,))
# 0x432480 keeps the unmodified board for its subsequent line pass.
            self.cpu.mem_write(BOARD, bytes(board))
        self.call(0x4346B0, ebx=threshold, ecx=COUNTER)
        reward = struct.unpack("<H", self.cpu.mem_read(COUNTER, 2))[0]
        return reward, self.read_mask()

    def falling(self, board):
        self.cpu.mem_write(BOARD, bytes(board))
        result = self.call(0x4328E0)
        return result, self.read_mask()

    def pixel_cell(self, origin_x, origin_y, pixel_x, pixel_y):
        self.cpu.mem_write(BOARD, bytes(0x18))
        self.cpu.mem_write(BOARD + 0xE, struct.pack("<h", origin_x))
        self.cpu.mem_write(BOARD + 0x16, struct.pack("<h", origin_y))
        self.call(0x431AE0, edx=pixel_x & 0xFFFF, ebx=pixel_y & 0xFFFF,
                  ecx=MASK, args=(MASK + 4,))
        return struct.unpack("<2i", self.cpu.mem_read(MASK, 8))

    def side_contact(self, board, row_mask, origin_x, origin_y, piece_x, piece_y, right, pattern=0):
        data = bytearray(0xD00)
        struct.pack_into("<h", data, 0xE, origin_x)
        struct.pack_into("<h", data, 0x16, origin_y)
        struct.pack_into("<I", data, 0xA60, BLOCKS)
        for i, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", data, 0x220 + 4 * i, 0x808000)
        piece = bytearray(0x18)
        struct.pack_into("<h", piece, 0xE, piece_x)
        struct.pack_into("<h", piece, 0x16, piece_y)
        self.cpu.mem_write(BOARD, bytes(data))
        self.cpu.mem_write(BLOCKS, bytes(piece))
#Explicit table input : preserve original decision instructions while
#varying the row - mask bytes.Mode selection is a separate recovery.
        if row_mask is not None:
            self.cpu.mem_write(0x4F9AD8, bytes(row_mask))
        return self.call(0x42F120 if right else 0x42F030, edx=pattern, ebx=0)

    def down_clear(self, board, origin_x, origin_y, piece_x, piece_y, horizontal=None, active=True):
#Same original board / piece representation, without Windows graphics.
        data = bytearray(0xD00)
        struct.pack_into("<h", data, 0xE, origin_x)
        struct.pack_into("<h", data, 0x16, origin_y)
        struct.pack_into("<I", data, 0xA60, BLOCKS if active else 0)
        for i, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", data, 0x220 + 4 * i, 0x808000)
        piece = bytearray(0x18)
        struct.pack_into("<h", piece, 0xE, piece_x)
        struct.pack_into("<h", piece, 0x16, piece_y)
        self.cpu.mem_write(BOARD, bytes(data))
        self.cpu.mem_write(BLOCKS, bytes(piece))
        if horizontal is not None:
            result = self.call(0x431140 if horizontal else 0x431100)
            x = struct.unpack("<h", self.cpu.mem_read(BLOCKS + 0xE, 2))[0]
            return result, x
        return self.call(0x431B80)

    def lock(self, board, column, top, blocks, descent=None, timed=None):
        data = bytearray(0xD00)
        piece_address = 0x802000
        struct.pack_into("<I", data, 0xA60, piece_address)
        for i, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", data, 0x220 + 4 * i, 0x808000 + color * 4)
        piece = bytearray(0x190)
        struct.pack_into("<h", piece, 0xE, column * 24)
        struct.pack_into("<h", piece, 0x16, top * 24)
        if descent is not None:
            struct.pack_into("<h", piece, 0x16, descent[0])
            struct.pack_into("<I", data, 0xBD8, descent[2])
        if timed is not None:
            y, motion, blink, frozen_state, flash, cycle, effects, elapsed, paused, frozen, blink_mode, origin_y = timed
            struct.pack_into("<h", piece, 0x16, y)
            struct.pack_into("<h", data, 0x16, origin_y)
            struct.pack_into("<I", piece, 0xC0, motion[0])
            struct.pack_into("<I", piece, 0xBC, motion[1])
            struct.pack_into("<H", piece, 0x1A, motion[2])
            struct.pack_into("<I", piece, 0x168, motion[3])
            struct.pack_into("<2I", piece, 0xDC, *blink)
            struct.pack_into("<I", piece, 0x180, frozen_state)
            struct.pack_into("<I", piece, 0x184, flash)
            struct.pack_into("<I", piece, 0x17C, cycle)
            struct.pack_into("<I", data, 0xB80, frozen)
            struct.pack_into("<I", data, 0xB90, blink_mode)
            struct.pack_into("<I", data, 0xCE8, 0x80C000)
            self.cpu.mem_write(0x80C000, bytes(0x500))
            self.cpu.mem_write(0x80C4CC, bytes([paused]))
            self.cpu.mem_write(0x5BD834, struct.pack("<I", elapsed))
        struct.pack_into("<I", piece, 0x158, 0x803100)
        for i in range(3):
            pointer = BLOCKS + i * 0x180
            struct.pack_into("<I", piece, 0x15C + 4 * i, pointer)
            block = bytearray([255] * 0x180)
            struct.pack_into("<I", block, 0x158, 0x803100)
            if timed is not None:
                struct.pack_into("<H", block, 0x48, effects[i])
            self.cpu.mem_write(pointer, bytes(block))
        self.cpu.mem_write(BOARD, bytes(data))
        self.cpu.mem_write(piece_address, bytes(piece))
        self.cpu.mem_write(0x803100, struct.pack("<I", 0x700200))
        self.cpu.mem_write(0x700200, b"\xc3")
        destroyed = []
        hook = self.cpu.hook_add(UC_HOOK_CODE, lambda cpu, address, size, context:
                                 destroyed.append(cpu.reg_read(UC_X86_REG_EAX)),
                                 begin=0x700200, end=0x700200)
        try:
            if timed is not None:
                self.call(0x42FBBA, ecx=BOARD, stop=0x42FC56)
            elif descent is None:
                result = self.call(0x431C60)
            else:
                self.call(0x42FC2D, ecx=BOARD, edx=descent[1], ebx=1, stop=0x42FC56)
        finally:
            self.cpu.hook_del(hook)
        pointers = {0: 255}
        pointers.update({0x808000 + color * 4: color for color in range(7)})
        pointers.update({BLOCKS + i * 0x180: blocks[i] for i in range(3)})
        placed = [pointers[p] for p in struct.unpack("<65I", self.cpu.mem_read(BOARD + 0x220, 260))]
        if descent is not None or timed is not None:
            active = int(struct.unpack("<I", self.cpu.mem_read(BOARD + 0xA60, 4))[0] != 0)
            y = struct.unpack("<h", self.cpu.mem_read(piece_address + 0x16, 2))[0]
            failed = struct.unpack("<I", self.cpu.mem_read(BOARD + 0xBD8, 4))[0]
            if timed is not None:
                motion_counter = struct.unpack("<I", self.cpu.mem_read(piece_address + 0xBC, 4))[0]
                blink_counter = struct.unpack("<I", self.cpu.mem_read(piece_address + 0xDC, 4))[0]
                frozen_state = struct.unpack("<I", self.cpu.mem_read(piece_address + 0x180, 4))[0]
                flash = struct.unpack("<I", self.cpu.mem_read(piece_address + 0x184, 4))[0]
                effects = tuple(struct.unpack("<H", self.cpu.mem_read(BLOCKS + i * 0x180 + 0x48, 2))[0]
                                for i in range(3))
                return placed, active, y, failed, motion_counter, blink_counter, frozen_state, flash, effects
            return placed, active, y, failed
        assert self.cpu.mem_read(BOARD + 0xA60, 4) == bytes(4)
        for i in range(3):
            if 0 <= top + i < 13:
                pointer = BLOCKS + i * 0x180
                assert self.cpu.mem_read(pointer + 0x93, 1) == b"\x00"
                assert self.cpu.mem_read(pointer + 0x4E, 1) == b"\x32"
                assert self.cpu.mem_read(pointer + 0x48, 2) == bytes(2)
        expected_calls = [] if top <= -3 else [BLOCKS + i * 0x180 for i in range(3)
                                               if not 0 <= top + i < 13]
        assert destroyed == expected_calls + [piece_address]
        return result, placed

    def collapse(self, board):
        self.cpu.mem_write(BOARD, bytes(board))
        self.call(0x432980)
        return bytes(self.cpu.mem_read(BOARD, 65))

    def shift(self, board, incoming, right):
        incoming_offset = 0x988 if right is None else (0x9E8 if right else 0xA2C)
        data = bytearray(0xD00)
        values = board + incoming
        pointers = {}
        for i, value in enumerate(values):
            pointer = 0 if value == 255 else BLOCKS + i * 0x180
            pointers[pointer] = value
            if pointer:
                self.cpu.mem_write(pointer + 0x158, struct.pack("<I", 0x803100))
            offset = 0x220 + i * 4 if i < 65 else incoming_offset + (i - 65) * 4
            struct.pack_into("<I", data, offset, pointer)
        pointers[0] = 255
        self.cpu.mem_write(BOARD, bytes(data))
        self.cpu.mem_write(0x803100, struct.pack("<I", 0x700200))
        self.cpu.mem_write(0x700200, b"\xc3")
        destroyed = []

        def destructor(cpu, address, size, context):
            destroyed.append(pointers[cpu.reg_read(UC_X86_REG_EAX)])

        hook = self.cpu.hook_add(UC_HOOK_CODE, destructor, begin=0x700200, end=0x700200)
        try:
            self.call(0x42F310 if right is None else (0x42F580 if right else 0x42F620))
        finally:
            self.cpu.hook_del(hook)
        result = [pointers[p] for p in struct.unpack("<65I", self.cpu.mem_read(BOARD + 0x220, 260))]
        remaining = [pointers[p] for p in struct.unpack(f"<{len(incoming)}I", self.cpu.mem_read(
            BOARD + incoming_offset, len(incoming) * 4))]
        return result, remaining, destroyed

    def estimate(self, board, pattern):
        self.cpu.mem_write(BOARD, bytes(board))
        self.call(0x434300, ebx=COUNTER, ecx=pattern)
        stones = struct.unpack("<I", self.cpu.mem_read(MASK, 4))[0]
        total = struct.unpack("<I", self.cpu.mem_read(COUNTER, 4))[0]
        return stones, total

    def blast(self, board, pattern, radius):
#Represent the original graphics - object pointers without replacing any
#game decision.Each nonempty cell points to an object with its type
#byte at + 0x15c, exactly as 0x4327e0 reads it.
        object_data = bytearray(0x1000)
        block_data = bytearray(65 * 0x180)
        for index, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", object_data, 0x220 + index * 4, BLOCKS + index * 0x180)
                block_data[index * 0x180 + 0x15C] = color
        object_data[0x838] = radius
        object_data[0x839] = pattern
        self.cpu.mem_write(BOARD, bytes(object_data))
        self.cpu.mem_write(BLOCKS, bytes(block_data))
#Stop after the complete mask, before creation of Windows FX objects.
        self.call(0x433E20, stop=0x433F43)
        return list(self.cpu.mem_read(0x540858, 65))

    def power(self, character, slot):
        result = self.call(0x4178D0, eax=character, edx=slot)
        return -1 if result == 0xFFFFFFFF else result

    def score_add(self, score, reward, difficulty):
        self.cpu.mem_write(BOARD, bytes(0x500))
        self.cpu.mem_write(BOARD + 0x174, struct.pack("<I", score))
        self.cpu.mem_write(0x532BBC, struct.pack("<I", difficulty))
        self.call(0x43BA90, edx=reward)
        return struct.unpack("<I", self.cpu.mem_read(BOARD + 0x174, 4))[0]

    def timer(self, counter, period, elapsed, scale, second):
        self.cpu.mem_write(BOARD, bytes(0x180))
        offset = 0xDC if second else 0xBC
        base = 0x4AC600 if second else 0x4AC500
        self.cpu.mem_write(BOARD + offset, struct.pack("<2I", counter, period))
        self.cpu.mem_write(0x5BD834, struct.pack("<I", elapsed))
        self.call(base)
        updated = struct.unpack("<I", self.cpu.mem_read(BOARD + offset, 4))[0]
        due = self.call(base + 0x20)
        cycles = self.call(base + 0x40)
        scaled = self.call(base + 0x90, edx=scale)
        self.call(base + 0xB0)
        remainder = struct.unpack("<I", self.cpu.mem_read(BOARD + offset, 4))[0]
        return updated, due, cycles, scaled, remainder

    def frame_sample(self, previous, elapsed, now):
#Supply the Windows clock import result; execute original comparisons,
#subtraction, baseline update and cap unchanged.
        self.cpu.mem_write(0x700300, b"\xa1\x00\x35\x80\x00\xc3")
        self.cpu.mem_write(0x803500, struct.pack("<I", now))
        self.cpu.mem_write(0x4F172C, struct.pack("<I", 0x700300))
        self.cpu.mem_write(0x5BD844, struct.pack("<I", previous))
        self.cpu.mem_write(0x5BD834, struct.pack("<I", elapsed))
        self.call(0x4B7D10)
        return (struct.unpack("<I", self.cpu.mem_read(0x5BD844, 4))[0],
                struct.unpack("<I", self.cpu.mem_read(0x5BD838, 4))[0],
                struct.unpack("<I", self.cpu.mem_read(0x5BD834, 4))[0])

    def spawn_position(self, board, preferred, origin_x, origin_y):
        data = bytearray(0xD00)
        struct.pack_into("<h", data, 0xE, origin_x)
        struct.pack_into("<h", data, 0x16, origin_y)
        struct.pack_into("<I", data, 0xA68, preferred)
        for i, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", data, 0x220 + 4 * i, 0x808000)
        self.cpu.mem_write(BOARD, bytes(data))

        def object_boundary(cpu, address, size, context):
#Supply allocated object storage; stop before its initializer.
#Allocation / graphics construction does not choose spawn position.
            cpu.reg_write(UC_X86_REG_EAX, BLOCKS)
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)

        hooks = [self.cpu.hook_add(UC_HOOK_CODE, object_boundary, begin=address, end=address)
                 for address in (0x4CA000, 0x42A310)]
        try:
            self.call(0x431D90, stop=0x431E28)
        finally:
            for hook in hooks:
                self.cpu.hook_del(hook)
        column = struct.unpack("<I", self.cpu.mem_read(BOARD + 0xA68, 4))[0]
        x = self.cpu.reg_read(UC_X86_REG_ECX)
        stack = self.cpu.reg_read(UC_X86_REG_ESP)
        y = struct.unpack("<i", self.cpu.mem_read(stack, 4))[0]
        return column, x if x < 2**31 else x - 2**32, y

    def speeds(self):
        return struct.unpack("<19I", self.pe.get_data(0xF8D38, 76))

    def random_seed(self, seed):
        object_data = bytearray(20)
        struct.pack_into("<I", object_data, 0, BLOCKS)
        self.cpu.mem_write(BOARD, bytes(object_data))
        self.call(0x482640, edx=seed)
        return list(struct.unpack("<4097H", self.cpu.mem_read(BLOCKS, 8194)))

    def random_range(self, minimum, width):
        result = self.call(0x482770, edx=minimum, ebx=width)
        position = struct.unpack("<H", self.cpu.mem_read(BOARD + 12, 2))[0]
        return result, position

    def random_clock(self, clock):
#Replace the platform time() boundary, preserving original refill,
#srand / rand instructions, mode branch, and sample consumption.
        def provide_time(cpu, address, size, context):
            value = clock() & 0xFFFFFFFF
            pointer = cpu.reg_read(UC_X86_REG_EAX)
            cpu.mem_write(pointer, struct.pack("<I", value))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            destination = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_EAX, value)
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, destination)

        self.clock_hook = self.cpu.hook_add(UC_HOOK_CODE, provide_time,
                                             begin=0x4EC1A0, end=0x4EC1A0)
        object_data = bytearray(20)
        struct.pack_into("<I", object_data, 0, BLOCKS)
        object_data[4] = 1
        self.cpu.mem_write(BOARD, bytes(object_data))
        self.call(0x482550)
        return self.random_samples()

    def random_samples(self):
        return list(struct.unpack("<4097H", self.cpu.mem_read(BLOCKS, 8194)))

    def timing_seed(self, seed):
        self.random_seed(seed)
        self.cpu.mem_write(0x598D48, bytes(self.cpu.mem_read(BOARD, 20)))

    def motion_level(self, difficulty, level, period, counter, step, state, fast=False):
        data = bytearray(0xD00)
        struct.pack_into("<I", data, 0xA60, BLOCKS)
        piece = bytearray(0x180)
        struct.pack_into("<I", piece, 0xC0, period)
        struct.pack_into("<I", piece, 0xBC, counter)
        struct.pack_into("<H", piece, 0x1A, step)
        struct.pack_into("<I", piece, 0x168, state)
        self.cpu.mem_write(BOARD, bytes(data))
        self.cpu.mem_write(BLOCKS, bytes(piece))
        self.cpu.mem_write(0x532BBC, struct.pack("<I", difficulty))
        self.call(0x431390 if fast else 0x431400, edx=level)
        values = (struct.unpack("<I", self.cpu.mem_read(BLOCKS + 0xC0, 4))[0],
                struct.unpack("<I", self.cpu.mem_read(BLOCKS + 0xBC, 4))[0],
                struct.unpack("<H", self.cpu.mem_read(BLOCKS + 0x1A, 2))[0])
        if fast:
            return values + (struct.unpack("<I", self.cpu.mem_read(BLOCKS + 0x168, 4))[0],)
        return values

    def piece_seed(self, seed):
        self.random_seed(seed)
        self.cpu.mem_write(0x598D30, bytes(self.cpu.mem_read(BOARD, 20)))

    def piece(self, mode):
        self.cpu.mem_write(BOARD, bytes(0x500))
        self.cpu.mem_write(BOARD + 0x4C8, struct.pack("<I", mode))
        self.call(0x43D180, edx=MASK, ebx=MASK + 1, ecx=MASK + 2)
        position = struct.unpack("<H", self.cpu.mem_read(0x598D30 + 12, 2))[0]
        return list(self.cpu.mem_read(MASK, 3)), position

    def piece_operation(self, blocks, cycle):
#Store child objects outside the RNG sample buffer at BLOCKS.
        child_base = 0x802000
        data = bytearray(0x180)
        for i, color in enumerate(blocks):
            pointer = child_base + i * 0x180
            struct.pack_into("<I", data, 0x15C + 4 * i, pointer)
            child = bytearray(0x180)
            child[0x15C] = color
            self.cpu.mem_write(pointer, bytes(child))
        self.cpu.mem_write(BOARD, bytes(data))
        self.call(0x42A8B0 if cycle else 0x42A8E0)
        pointers = struct.unpack("<3I", self.cpu.mem_read(BOARD + 0x15C, 12))
        result = [self.cpu.mem_read(pointer + 0x15C, 1)[0] for pointer in pointers]
        position = struct.unpack("<H", self.cpu.mem_read(0x598D30 + 12, 2))[0]
        return result, position

    def timing(self, character, difficulty, level, parameter):
        player = bytearray(0x500)
        struct.pack_into("<I", player, 0x488, character)
        struct.pack_into("<I", player, 0x17C, level)
        self.cpu.mem_write(BOARD, bytes(player))
        self.cpu.mem_write(0x532BBC, struct.pack("<I", difficulty))
        self.call((0x43B5B0, 0x43B660, 0x43B680)[parameter])
        result = struct.unpack("<I", self.cpu.mem_read(BOARD + 0x458 + parameter * 4, 4))[0]
        position = struct.unpack("<H", self.cpu.mem_read(0x598D48 + 12, 2))[0]
        return result, position

    def input_repeat(self, values, enabled, elapsed, start_payload=None, stop=False):
        """Run original scheduler; intercept only queue insertion to observe events."""
        self.cpu.mem_write(BOARD, bytes(0x60))
        self.cpu.mem_write(BOARD + 0x3C, struct.pack("<8I", *values))
        self.cpu.mem_write(BOARD + 0x5A, bytes([enabled]))
        if start_payload is not None:
            self.call(0x475AD0, edx=start_payload[0], ebx=start_payload[1], ecx=start_payload[2])
        if stop:
            self.call(0x475AF0)
        events = []
        def enqueue(cpu, address, size, context):
            events.append(tuple(cpu.reg_read(register) for register in
                                (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        hook = self.cpu.hook_add(UC_HOOK_CODE, enqueue, begin=0x475B20, end=0x475B20)
        try:
            self.call(0x475E50, edx=elapsed)
        finally:
            self.cpu.hook_del(hook)
        state = struct.unpack("<8I", self.cpu.mem_read(BOARD + 0x3C, 32))
        return state, self.cpu.mem_read(BOARD + 0x5A, 1)[0], events

    def input_queue(self, mode, current, events, operations):
        """Execute original queue pop/copy/update; skip only storage destruction."""
        self.cpu.mem_write(BOARD, bytes(0x60))
        self.cpu.mem_write(BOARD, bytes([mode]))
        def store_event(pointer, event, vtable=0):
            state, payload = event
            data = bytearray(28)
            data[0] = state
            struct.pack_into("<3I", data, 4, *payload)
            struct.pack_into("<H", data, 16, 123)
            struct.pack_into("<I", data, 20, 456)
            struct.pack_into("<I", data, 24, vtable)
            self.cpu.mem_write(pointer, bytes(data))
        store_event(BOARD + 4, current)
        self.cpu.mem_write(0x803100, struct.pack("<I", 0x700400))
        self.cpu.mem_write(0x700400, b"\xc3")
        pointers = [MASK + i * 16 for i in range(len(events))]
        for i, event in enumerate(events):
            node = pointers[i]
            event_pointer = BLOCKS + i * 32
            store_event(event_pointer, event, 0x803100)
            self.cpu.mem_write(node, struct.pack("<3I", pointers[i + 1] if i + 1 < len(events) else 0,
                                               pointers[i - 1] if i else 0, event_pointer))
        self.cpu.mem_write(BOARD + 0x24, struct.pack("<3I", pointers[0] if pointers else 0,
                                                  pointers[-1] if pointers else 0, len(events)))
        destroyed = []
        def boundary(cpu, address, size, context):
            if address == 0x700400:
                destroyed.append((cpu.reg_read(UC_X86_REG_EAX) - BLOCKS) // 32)
            else:
# 0x4d83c0 releases the now - empty container's allocation pool.
                stack = cpu.reg_read(UC_X86_REG_ESP)
                target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
                cpu.reg_write(UC_X86_REG_ESP, stack + 4)
                cpu.reg_write(UC_X86_REG_EIP, target)
        hooks = [self.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a)
                 for a in (0x700400, 0x4D83C0)]
        results = []
        try:
            for operation, deferred in operations:
                self.cpu.mem_write(0x553648, struct.pack("<I", deferred))
                if operation == "acknowledge":
                    self.call(0x476320, edx=0)
                else:
                    self.call({"single": 0x475CD0, "drain": 0x475D20,
                               "consume": 0x475C30}[operation])
                state = self.cpu.mem_read(BOARD + 4, 1)[0]
                payload = struct.unpack("<3I", self.cpu.mem_read(BOARD + 8, 12))
                count = struct.unpack("<I", self.cpu.mem_read(BOARD + 0x2C, 4))[0]
                ready = self.call(0x475D70)
                results.append((state, payload, count, ready, tuple(destroyed)))
        finally:
            for hook in hooks:
                self.cpu.hook_del(hook)
        return results

    def input_actions(self, action_id, mode, repeat_values, enabled, operations):
        """Execute input edge wrappers and integrated repeat/queue updates."""
        self.cpu.mem_write(BOARD, bytes(0x60))
        self.cpu.mem_write(BOARD, bytes([mode]))
        self.cpu.mem_write(BOARD + 0x3C, struct.pack("<7I", *repeat_values))
        self.cpu.mem_write(BOARD + 0x58, struct.pack("<H", action_id))
        self.cpu.mem_write(BOARD + 0x5A, bytes([enabled]))
        self.cpu.mem_write(0x803100, struct.pack("<I", 0x700400))
        self.cpu.mem_write(0x700400, b"\xc3")
        serial = 0
        deferred_events = []
        def boundary(cpu, address, size, context):
            nonlocal serial
            if address in (0x475B20, 0x475BE0):
                state = 1 if address == 0x475B20 else 2
                payload = tuple(cpu.reg_read(reg) for reg in
                                (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX))
                deferred = struct.unpack("<I", cpu.mem_read(0x553648, 4))[0]
                if deferred:
                    if state == 1:
                        deferred_events.append((action_id, payload))
                else:
                    assert serial < 700, "Oracle scratch queue capacity exceeded"
                    node = 0x80A000 + serial * 16
                    event = BLOCKS + serial * 32
                    serial += 1
                    data = bytearray(28)
                    data[0] = state
                    struct.pack_into("<3I", data, 4, *payload)
                    struct.pack_into("<I", data, 24, 0x803100)
                    cpu.mem_write(event, bytes(data))
                    tail = struct.unpack("<I", cpu.mem_read(BOARD + 0x28, 4))[0]
                    cpu.mem_write(node, struct.pack("<3I", 0, tail, event))
                    if tail:
                        cpu.mem_write(tail, struct.pack("<I", node))
                    else:
                        cpu.mem_write(BOARD + 0x24, struct.pack("<I", node))
                    cpu.mem_write(BOARD + 0x28, struct.pack("<I", node))
                    count = struct.unpack("<I", cpu.mem_read(BOARD + 0x2C, 4))[0]
                    cpu.mem_write(BOARD + 0x2C, struct.pack("<I", count + 1))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        hooks = [self.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a)
                 for a in (0x475B20, 0x475BE0, 0x4D83C0)]
        results = []
        try:
            for operation in operations:
                kind, deferred, *args = operation
                self.cpu.mem_write(0x553648, struct.pack("<I", deferred))
                if kind == "edge":
                    pressed, force, payload = args
                    address = ((0x476360 if force else 0x4761D0) if pressed
                               else (0x4763C0 if force else 0x476280))
                    self.call(address, edx=0, ebx=payload[0], ecx=payload[1], args=(payload[2],))
                elif kind == "acknowledge":
                    self.call(0x476320, edx=0)
                else:
                    self.call(0x475CD0 if kind == "single" else 0x475D20, edx=args[0])
                current = (self.cpu.mem_read(BOARD + 4, 1)[0],
                           struct.unpack("<3I", self.cpu.mem_read(BOARD + 8, 12)))
                pending = []
                pointer = struct.unpack("<I", self.cpu.mem_read(BOARD + 0x24, 4))[0]
                while pointer:
                    next_pointer, previous_pointer, event = struct.unpack("<3I", self.cpu.mem_read(pointer, 12))
                    pending.append((self.cpu.mem_read(event, 1)[0],
                                    struct.unpack("<3I", self.cpu.mem_read(event + 4, 12))))
                    pointer = next_pointer
                repeat = struct.unpack("<7I", self.cpu.mem_read(BOARD + 0x3C, 28))
                results.append((repeat, self.cpu.mem_read(BOARD + 0x5A, 1)[0], current,
                                tuple(pending), tuple(deferred_events)))
        finally:
            for hook in hooks:
                self.cpu.hook_del(hook)
        return results

    def input_configure(self, controls, player_delays, default_delay, initial):
        """Run original ordered settings application, stopping before caller epilogue."""
        base = 0x54D640
        for i, (mode, repeat) in enumerate(initial):
            self.cpu.mem_write(base + i * 96, bytes(96))
            self.cpu.mem_write(base + i * 96, bytes([mode]))
            self.cpu.mem_write(base + i * 96 + 0x3C, struct.pack("<7I", *repeat))
        self.cpu.mem_write(0x532B6C, struct.pack("<9H", *controls))
        self.cpu.mem_write(0x532B80, struct.pack("<2I", *player_delays))
        self.cpu.mem_write(0x553644, struct.pack("<I", default_delay))
        self.call(0x425B8D, stop=0x425D26)
        return [(self.cpu.mem_read(base + i * 96, 1)[0],
                 struct.unpack("<7I", self.cpu.mem_read(base + i * 96 + 0x3C, 28)))
                for i in range(256)]

    def controls_dispatch(self, board, origin, position, blocks, motion, bindings,
                          mode, cycle_mode, difficulty, failed, deferred, inputs):
        """Execute the original player's complete active-piece input dispatch slice."""
        piece_address, player, opponent, feedback = 0x802000, 0x80C000, 0x80D000, 0x80E000
        data = bytearray(0xD00)
        struct.pack_into("<h", data, 0xE, origin[0])
        struct.pack_into("<h", data, 0x16, origin[1])
        struct.pack_into("<I", data, 0xA60, piece_address)
        struct.pack_into("<I", data, 0xBD8, failed)
        for i, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", data, 0x220 + i * 4, 0x808000)
        self.cpu.mem_write(BOARD, bytes(data))
        piece = bytearray(0x180)
        struct.pack_into("<h", piece, 0xE, position[0])
        struct.pack_into("<h", piece, 0x16, position[1])
        struct.pack_into("<I", piece, 0xC0, motion[0])
        struct.pack_into("<I", piece, 0xBC, motion[1])
        struct.pack_into("<H", piece, 0x1A, motion[2])
        struct.pack_into("<I", piece, 0x168, motion[3])
        struct.pack_into("<I", piece, 0x17C, cycle_mode)
        for i, color in enumerate(blocks):
            pointer = 0x806100 + i * 0x180
            struct.pack_into("<I", piece, 0x15C + i * 4, pointer)
            child = bytearray(0x180)
            child[0x15C] = color
            self.cpu.mem_write(pointer, bytes(child))
        self.cpu.mem_write(piece_address, bytes(piece))
        player_data = bytearray(0x500)
        struct.pack_into("<I", player_data, 0x15C, BOARD)
        struct.pack_into("<4H", player_data, 0x168, *bindings[:4])
        struct.pack_into("<I", player_data, 0x3B0, opponent)
        struct.pack_into("<I", player_data, 0x450, feedback)
        player_data[0x4C5] = 1
        struct.pack_into("<I", player_data, 0x4C8, mode)
        self.cpu.mem_write(player, bytes(player_data))
        self.cpu.mem_write(opponent, bytes(0x500))
        self.cpu.mem_write(opponent + 0x160, struct.pack("<2H", *bindings[4:]))
        self.cpu.mem_write(feedback, bytes(0x180))
        base = 0x54D640
        for i, (state, payload, enabled, repeat) in enumerate(inputs):
            action = bytearray(96)
            action[4] = state
            struct.pack_into("<3I", action, 8, *payload)
            struct.pack_into("<7I", action, 0x3C, *repeat)
            struct.pack_into("<H", action, 0x58, i)
            action[0x5A] = enabled
            self.cpu.mem_write(base + i * 96, bytes(action))
        self.cpu.mem_write(0x532BBC, struct.pack("<I", difficulty))
        self.cpu.mem_write(0x553648, struct.pack("<I", deferred))
        emitted = []
        def boundary(cpu, address, size, context):
            if address != 0x43AD70:
                action_id = (cpu.reg_read(UC_X86_REG_EAX) - base) // 96
                state = 1 if address == 0x475B20 else 2
                payload = tuple(cpu.reg_read(reg) for reg in
                                (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX))
                if not deferred or state == 1:
                    emitted.append((action_id, state, payload, bool(deferred)))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        hooks = [self.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a)
                 for a in (0x43AD70, 0x475B20, 0x475BE0)]
        try:
            self.call(0x450FF0, eax=player, stop=0x4511BB)
        finally:
            for hook in hooks:
                self.cpu.hook_del(hook)
        pointers = struct.unpack("<3I", self.cpu.mem_read(piece_address + 0x15C, 12))
        colors = tuple(self.cpu.mem_read(pointer + 0x15C, 1)[0] for pointer in pointers)
        output_inputs = []
        for i in range(len(inputs)):
            action = base + i * 96
            output_inputs.append((self.cpu.mem_read(action + 4, 1)[0],
                                  struct.unpack("<3I", self.cpu.mem_read(action + 8, 12)),
                                  self.cpu.mem_read(action + 0x5A, 1)[0],
                                  struct.unpack("<7I", self.cpu.mem_read(action + 0x3C, 28))))
        output_motion = (struct.unpack("<I", self.cpu.mem_read(piece_address + 0xC0, 4))[0],
                         struct.unpack("<I", self.cpu.mem_read(piece_address + 0xBC, 4))[0],
                         struct.unpack("<H", self.cpu.mem_read(piece_address + 0x1A, 2))[0],
                         struct.unpack("<I", self.cpu.mem_read(piece_address + 0x168, 4))[0])
        refresh = struct.unpack("<I", self.cpu.mem_read(feedback + 0x178, 4))[0]
        rng_position = struct.unpack("<H", self.cpu.mem_read(0x598D30 + 12, 2))[0]
        x = struct.unpack("<h", self.cpu.mem_read(piece_address + 0xE, 2))[0]
        return x, colors, output_motion, tuple(output_inputs), tuple(emitted), refresh, rng_position

    def spawn_initialize(self, board, preferred, origin_x, origin_y, blocks, difficulty,
                         level, failed, frames):
        """Run full original spawn/constructors, replacing only heap allocation."""
        data = bytearray(0xD00)
        struct.pack_into("<h", data, 0xE, origin_x)
        struct.pack_into("<h", data, 0x16, origin_y)
        struct.pack_into("<I", data, 0xA68, preferred)
        struct.pack_into("<I", data, 0xBD8, failed)
        for i, color in enumerate(board):
            if color != 255:
                struct.pack_into("<I", data, 0x220 + i * 4, 0x808000)
        self.cpu.mem_write(BOARD, bytes(data))
        self.cpu.mem_write(0x532BBC, struct.pack("<I", difficulty))
        self.cpu.mem_write(0x53BCD0, b"".join(struct.pack("<2I", *frame) for frame in frames))
        allocations = []
        def allocate(cpu, address, size, context):
            requested = cpu.reg_read(UC_X86_REG_EAX)
            pointer = 0x802000 if not allocations else 0x806100 + (len(allocations) - 1) * 0x180
            assert requested == (0x188 if not allocations else 0x160)
            allocations.append(pointer)
            cpu.mem_write(pointer, bytes([0xA5]) * requested)
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_EAX, pointer)
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        hook = self.cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x4CA000, end=0x4CA000)
        try:
            self.call(0x431D90, edx=blocks[0], ebx=blocks[1], ecx=blocks[2], args=(level,))
        finally:
            self.cpu.hook_del(hook)
        assert len(allocations) == 4
        piece = struct.unpack("<I", self.cpu.mem_read(BOARD + 0xA60, 4))[0]
        x = struct.unpack("<h", self.cpu.mem_read(piece + 0xE, 2))[0]
        y = struct.unpack("<h", self.cpu.mem_read(piece + 0x16, 2))[0]
        pointers = struct.unpack("<3I", self.cpu.mem_read(piece + 0x15C, 12))
        colors = tuple(self.cpu.mem_read(pointer + 0x15C, 1)[0] for pointer in pointers)
        motion = (struct.unpack("<I", self.cpu.mem_read(piece + 0xC0, 4))[0],
                  struct.unpack("<I", self.cpu.mem_read(piece + 0xBC, 4))[0],
                  struct.unpack("<H", self.cpu.mem_read(piece + 0x1A, 2))[0],
                  struct.unpack("<I", self.cpu.mem_read(piece + 0x168, 4))[0])
        blink = struct.unpack("<2I", self.cpu.mem_read(piece + 0xDC, 8))
        frozen, flash = struct.unpack("<2I", self.cpu.mem_read(piece + 0x180, 8))
        cycle = struct.unpack("<I", self.cpu.mem_read(piece + 0x17C, 4))[0]
        effects = tuple(struct.unpack("<H", self.cpu.mem_read(pointer + 0x48, 2))[0] for pointer in pointers)
        visuals = tuple((struct.unpack("<I", self.cpu.mem_read(pointer + 0xD0, 4))[0],
                         struct.unpack("<I", self.cpu.mem_read(pointer + 0xCC, 4))[0],
                         *struct.unpack("<2I", self.cpu.mem_read(pointer + 0xBC, 8)))
                        for pointer in pointers)
        failed = struct.unpack("<I", self.cpu.mem_read(BOARD + 0xBD8, 4))[0]
        preferred = struct.unpack("<I", self.cpu.mem_read(BOARD + 0xA68, 4))[0]
        position = struct.unpack("<H", self.cpu.mem_read(0x598D30 + 12, 2))[0]
        blink_mode = struct.unpack("<I", self.cpu.mem_read(BOARD + 0xB90, 4))[0]
        return x, y, colors, motion, blink, frozen, flash, cycle, effects, visuals, failed, preferred, position, blink_mode

    def asset_animation_ranges(self, rows, character):
        self.cpu.mem_write(0x5336AC, b"".join(struct.pack("<I", rows[row][column])
                                             for column in range(14) for row in range(20)))
        self.call(0x415330, eax=character)
        return tuple(struct.unpack("<2I", self.cpu.mem_read(0x53BCD0 + color * 8, 8))
                     for color in range(7))

    def animation(self, counter, period, frame, frame_count, elapsed, mode):
        self.cpu.mem_write(BOARD, bytes(0x15C))
        self.cpu.mem_write(BOARD + 0xCC, struct.pack("<2I", counter, period))
        self.cpu.mem_write(BOARD + 0xB8, struct.pack("<I", frame))
        self.cpu.mem_write(BOARD + 0xB0, struct.pack("<I", MASK))
        self.cpu.mem_write(MASK + 4, struct.pack("<I", frame_count))
        self.cpu.mem_write(0x5BD834, struct.pack("<I", elapsed))
        result = self.call((0x4AC1F0, 0x4AC250, 0x4AC2B0, 0x4AC310)[mode])
        return (struct.unpack("<I", self.cpu.mem_read(BOARD + 0xCC, 4))[0],
                struct.unpack("<I", self.cpu.mem_read(BOARD + 0xB8, 4))[0],
                result if mode in (1, 2) else 1)

    def image_binary_alpha(self, pixels):
        if len(pixels) % 4 or len(pixels) > 16384:
            raise ValueError("Alpha oracle requires a whole-pixel chunk up to 16 KB")
        self.cpu.mem_write(BOARD, bytes(40))
        self.cpu.mem_write(BOARD, struct.pack("<3I", BLOCKS, len(pixels) // 4, 1))
        self.cpu.mem_write(BOARD + 0x27, b"\x04")
        self.cpu.mem_write(BLOCKS, pixels)
        self.call(0x483750)
        return bytes(self.cpu.mem_read(BLOCKS, len(pixels)))

    def image_color_order(self, pixels, masks):
        if len(pixels) % 4 or len(pixels) > 16384:
            raise ValueError("Color oracle requires a whole-pixel chunk up to 16 KB")
        self.cpu.mem_write(BOARD, bytes(40))
        self.cpu.mem_write(BOARD, struct.pack("<3I", BLOCKS, len(pixels) // 4, 1))
        self.cpu.mem_write(BOARD + 0x27, b"\x04")
        self.cpu.mem_write(MASK, bytes(40))
        self.call(0x481BC0, eax=MASK, edx=masks[0], ebx=masks[1],
                  ecx=masks[2], args=(0xFF000000,))
        bgra = bytearray(pixels)
        for offset in range(0, len(bgra), 4):
            bgra[offset], bgra[offset + 2] = bgra[offset + 2], bgra[offset]
        self.cpu.mem_write(BLOCKS, bytes(bgra))
        self.call(0x483ED0, edx=MASK)
        result = bytearray(self.cpu.mem_read(BLOCKS, len(pixels)))
        for offset in range(0, len(result), 4):
            result[offset], result[offset + 2] = result[offset + 2], result[offset]
        return bytes(result)

    def block_frame_layout(self, sheet_column):
        captures = []
        def boundary(cpu, address, size, data):
            if address == 0x4877F0:
                resource = cpu.reg_read(UC_X86_REG_EAX)
                frame = cpu.reg_read(UC_X86_REG_EDX)
                captures.append(((resource - 0x544AC0) // 28, frame))
                cpu.reg_write(UC_X86_REG_EAX, BOARD)
            elif address == 0x482E10:
                captures[-1] += (cpu.reg_read(UC_X86_REG_EBX), cpu.reg_read(UC_X86_REG_ECX))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        hooks = [self.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a)
                 for a in (0x4877F0, 0x482E10, 0x483ED0)]
        try:
            self.call(0x45F0C0, edx=sheet_column)
            return captures
        finally:
            for hook in hooks:
                self.cpu.hook_del(hook)

    def board_render_geometry(self, origin_x, origin_y, offsets, dimensions=None):
        self.cpu.mem_write(BOARD, bytes(0xC00))
        self.cpu.mem_write(BOARD + 0xC, struct.pack("<I", (origin_x & 65535) << 16))
        self.cpu.mem_write(BOARD + 0x14, struct.pack("<I", (origin_y & 65535) << 16))
        self.cpu.mem_write(MASK, bytes(0x160))
        self.call(0x42FF10)
        clip = struct.unpack("<4h", self.cpu.mem_read(MASK + 0xA8, 8))
        for index, (x, y) in enumerate(offsets):
            cell = BLOCKS + index * 0x180
            self.cpu.mem_write(cell, bytes(0x180))
            self.cpu.mem_write(cell + 0x44, b"\x10" if dimensions is None else b"\x00")
            self.cpu.mem_write(BOARD + 0x220 + index * 4, struct.pack("<I", cell))
            self.cpu.mem_write(BOARD + 0x15C + index, bytes([x & 255]))
            self.cpu.mem_write(BOARD + 0x19D + index, bytes([y & 255]))
        def measurement(cpu, address, size, data):
            index = (cpu.reg_read(UC_X86_REG_EAX) - BLOCKS) // 0x180
            width, height = dimensions[index]
            cpu.mem_write(cpu.reg_read(UC_X86_REG_EDX), struct.pack("<i", width))
            cpu.mem_write(cpu.reg_read(UC_X86_REG_EBX), struct.pack("<i", height))
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)
        hook = self.cpu.hook_add(UC_HOOK_CODE, measurement, begin=0x4B14C0, end=0x4B14C0) if dimensions is not None else None
        try:
            self.call(0x430930, stop=0x4309F9)
        finally:
            if hook is not None:
                self.cpu.hook_del(hook)
        positions = [(struct.unpack("<h", self.cpu.mem_read(BLOCKS + i * 0x180 + 0xE, 2))[0],
                      struct.unpack("<h", self.cpu.mem_read(BLOCKS + i * 0x180 + 0x16, 2))[0])
                     for i in range(65)]
        return clip, positions

    def resource_measure(self, width, height, mode, descriptor=True, screen_override=0, screen_unscaled=0, screen_mode=16):
        if not getattr(self, "render_tables_initialized", False):
            self.call(0x4B9050)
            self.render_tables_initialized = True
        self.cpu.mem_write(BOARD, bytes(0x160))
        self.cpu.mem_write(BOARD + 0x44, bytes([mode]))
        self.cpu.mem_write(BOARD + 0x91, bytes([screen_override]))
        self.cpu.mem_write(0x544070, struct.pack("<I", 0x809000))
        self.cpu.mem_write(0x809220, bytes([screen_unscaled, screen_mode]))
        if descriptor:
            self.cpu.mem_write(MASK, struct.pack("<3I", 0, width, height) + bytes(28))
            self.cpu.mem_write(BOARD + 0xB4, struct.pack("<I", MASK))
        else:
            self.cpu.mem_write(BOARD + 0xF4, struct.pack("<H", width))
            self.cpu.mem_write(BOARD + 0xF8, struct.pack("<H", height))
        self.call(0x4B14C0, edx=COUNTER, ebx=COUNTER + 4)
        return struct.unpack("<2i", self.cpu.mem_read(COUNTER, 8))

    def resource_bounds(self, width, height, anchor_x, anchor_y, mode, x, y):
        self.resource_measure(width, height, mode)
        self.cpu.mem_write(MASK + 12, struct.pack("<HH", anchor_x & 65535, 0))
        self.cpu.mem_write(MASK + 16, struct.pack("<H", anchor_y & 65535))
        self.cpu.mem_write(BOARD + 12, struct.pack("<I", (x & 65535) << 16))
        self.cpu.mem_write(BOARD + 20, struct.pack("<I", (y & 65535) << 16))
        self.call(0x4B15E0, edx=COUNTER, ebx=COUNTER + 4, ecx=COUNTER + 8,
                  args=(COUNTER + 12,))
        return struct.unpack("<4i", self.cpu.mem_read(COUNTER, 16))

    def sprite_clip(self, x, y, width, height, clip, mode=None, target=(640,480), object_clip=(0,119,0,311)):
        def write(address, value):
            self.cpu.mem_write(address, struct.pack("<H", value & 65535))
        self.cpu.mem_write(0x5BB790, bytes(4))
        self.cpu.mem_write(0x5BB70C, bytes(4))
        self.cpu.mem_write(0x5BBFFE, bytes([3]))
        for address, value in [(0x5BB7A0,x),(0x5BB7A2,y),(0x5BB748,x+width-1),
                               (0x5BB74A,y+height-1),(0x5BB74C,width),(0x5BB74E,height),
                               (0x5BB750,width),(0x5BB752,height),(0x5BBFF2,x),(0x5BBFF4,y),
                               (0x5BBFF6,clip[0]),(0x5BBFF8,clip[1]),
                               (0x5BBFFA,clip[2]),(0x5BBFFC,clip[3])]:
            write(address,value)
        if mode is not None:
            self.cpu.mem_write(0x5BBFFE, bytes([mode]))
            self.cpu.mem_write(0x5BC010, struct.pack("<I",MASK))
            write(MASK+4,target[0])
            write(MASK+8,target[1])
            for index,value in enumerate(object_clip):
                write(BOARD+0xA8+index*2,value)
            self.cpu.reg_write(UC_X86_REG_ESI,BOARD)
        failed = False
        def reject(cpu, address, size, data):
            nonlocal failed
            failed = True
            cpu.reg_write(UC_X86_REG_EIP, 0x4B1C6F)
        hook = self.cpu.hook_add(UC_HOOK_CODE, reject, begin=0x4B1D44, end=0x4B1D44)
        try:
            self.call(0x4B1A99 if mode is not None else 0x4B1AE9, stop=0x4B1C6F)
        finally:
            self.cpu.hook_del(hook)
        if failed:
            return None
        def signed(address):
            return struct.unpack("<h",self.cpu.mem_read(address,2))[0]
        return (signed(0x5BB7A0),signed(0x5BB748),signed(0x5BB7A2),signed(0x5BB74A),
                *struct.unpack("<2H",self.cpu.mem_read(0x5BB750,4)),
                struct.unpack("<I",self.cpu.mem_read(0x5BB790,4))[0],
                self.cpu.mem_read(0x5BC014,1)[0])

    def surface_pixel(self, data, width, height, stride, bpp, x, y, value):
        descriptor = bytearray(32)
        struct.pack_into("<3I", descriptor, 0, BLOCKS, width, height)
        descriptor[12] = bpp
        struct.pack_into("<I", descriptor, 20, stride)
        self.cpu.mem_write(BOARD,bytes(descriptor))
        self.cpu.mem_write(BLOCKS,data)
        address = self.call(0x478EB0,edx=x,ebx=y)
        read = self.call(0x478F10,edx=x,ebx=y)
        self.call(0x478ED0,edx=x,ebx=y,ecx=value)
        return address - BLOCKS, read, bytes(self.cpu.mem_read(BLOCKS,len(data)))

    def scale_clip_offset(self, mode, width, columns, rows, initial):
        if not getattr(self, "render_tables_initialized", False):
            self.call(0x4B9050)
            self.render_tables_initialized = True
        base=0x5C1C00+mode*1024
        for address,value in ((0x5BB7D4,base),(0x5BB7D8,base),(0x5BB790,initial)):
            self.cpu.mem_write(address,struct.pack("<I",value))
        for address,value in ((0x5BB7A0,columns),(0x5BB7A2,rows),
                              (0x5BBFF2,0),(0x5BBFF4,0),(0x5BB7B4,width)):
            self.cpu.mem_write(address,struct.pack("<H",value))
        self.call(0x4AE99F,stop=0x4AEA50)
        offset=struct.unpack("<I",self.cpu.mem_read(0x5BB790,4))[0]
        consumed_rows=struct.unpack("<I",self.cpu.mem_read(0x5BB7D4,4))[0]-base
        consumed_columns=struct.unpack("<I",self.cpu.mem_read(0x5BB7D8,4))[0]-base
        assert (consumed_columns,consumed_rows)==(columns,rows)
        return offset

    def render_pixels_enabled(self, resource, scale, state):
        self.cpu.mem_write(BOARD,bytes(0x160))
        self.cpu.mem_write(BOARD+0x134,struct.pack("<I",resource))
        for address,value in zip((0x5BB73A,0x5BB739,0x5BC00D,0x5BC00E,
                                  0x5BC000,0x5BB730,0x5BC00C),state):
            self.cpu.mem_write(address,bytes([value]))
        self.cpu.mem_write(0x5BC002,struct.pack("<H",state[-1]))
        self.cpu.mem_write(0x5BB738,bytes([scale]))
        enabled=True
        def skipped(cpu,address,size,data):
            nonlocal enabled
            enabled=False
            cpu.reg_write(UC_X86_REG_EIP,0x4AF6AD)
        hook=self.cpu.hook_add(UC_HOOK_CODE,skipped,begin=0x4AF583,end=0x4AF583)
        try:
            self.call(0x4AF560,stop=0x4AF6AD)
        finally:
            self.cpu.hook_del(hook)
        return enabled

    def render_binding(self, base, offset, source_width, target_width, visible_width, stride, extra, bpp):
        self.cpu.mem_write(MASK,struct.pack("<I",base))
        self.cpu.mem_write(0x5BB734,struct.pack("<I",MASK))
        self.cpu.mem_write(0x5BC010,struct.pack("<I",BOARD))
        for address,value in ((0x5BB790,offset),(BOARD+0x14,stride),(BOARD+0x18,extra)):
            self.cpu.mem_write(address,struct.pack("<I",value))
        for address,value in ((0x5BB7B4,source_width),(BOARD+4,target_width),(0x5BB750,visible_width)):
            self.cpu.mem_write(address,struct.pack("<H",value))
        self.cpu.mem_write(0x5BB732,bytes([bpp]))
        self.call(0x4AF0EE,stop=0x4AF187)
        result=[]
        for address,signed in ((0x5BB764,False),(0x5BB7C0,False),(0x5BB7BC,True),
                               (0x5BB794,True),(0x5BB7C4,False),(0x5BB7C8,False)):
            result.append(struct.unpack("<i" if signed else "<I",self.cpu.mem_read(address,4))[0])
        assert self.cpu.mem_read(0x5BB764,4)==self.cpu.mem_read(0x5BB76C,4)
        return tuple(result)

    def draw_prepared_dispatch(self, source_base, scale, binary, effect=0, amount=100, alpha=False):
        self.cpu.mem_write(BOARD,bytes(0x160))
        self.cpu.mem_write(BOARD+0x134,struct.pack("<I",source_base))
        self.cpu.mem_write(BOARD+0x150,struct.pack("<I",int(alpha)))
        state=((0x5BB738,scale),(0x5BBFFF,int(binary)),(0x5BBFF0,0),
               (0x5BB733,4),(0x5BB73A,0),(0x5BB739,int(bool(effect))),
               (0x5BC00D,effect),(0x5BC00E,amount),(0x5BC000,13),(0x5BB730,13),
               (0x5BC00C,0))
        for address,value in state:
            self.cpu.mem_write(address,bytes([value]))
        self.cpu.mem_write(0x5BC002,bytes(2))
        self.call(0x4AF560)

    def image_mask(self, pixels, indices, graded_offset=None):
        if len(pixels) != len(indices) * 4 or len(pixels) > 16384:
            raise ValueError("Mask oracle requires matching pixels up to 16 KB")
        self.cpu.mem_write(BOARD, struct.pack("<3I", BLOCKS, len(indices), 1))
        self.cpu.mem_write(MASK, struct.pack("<3I", 0x809000, len(indices), 1))
        self.cpu.mem_write(BLOCKS, pixels)
        self.cpu.mem_write(0x809000, indices)
        if graded_offset is not None and not getattr(self, "graded_table_initialized", False):
            self.call(0x4807EA, stop=0x48087A)
            self.graded_table_initialized = True

        def boundary(cpu, address, size, data):
            if address == 0x4816F0:
                cpu.reg_write(UC_X86_REG_EAX, MASK)
            stack = cpu.reg_read(UC_X86_REG_ESP)
            target = struct.unpack("<I", cpu.mem_read(stack, 4))[0]
            cpu.reg_write(UC_X86_REG_ESP, stack + 4)
            cpu.reg_write(UC_X86_REG_EIP, target)

        hooks = [self.cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a)
                 for a in (0x4816F0, 0x478D80)]
        try:
            self.call(0x4797F0 if graded_offset is None else 0x4798B0,
                      ebx=0 if graded_offset is None else graded_offset & 0xFFFFFFFF)
            return bytes(self.cpu.mem_read(BLOCKS, len(pixels)))
        finally:
            for hook in hooks:
                self.cpu.hook_del(hook)
