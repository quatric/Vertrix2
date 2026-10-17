"""The registers a routine of the original reads on entry: register_inputs.py ADDRESS...

A clean port written as ordinary C hands each callee its arguments, not the values its registers
happen to hold. The port verifier (tools/verify_port.py) compares a call's eax, edx, ebx and ecx
only where the callee reads them, which this works out from the original's code: a register is an
input when some path from the entry reads it before writing it.

The analysis is conservative where it cannot see:
- a call inside the routine reads what its callee reads and writes nothing; a call through a
  fixed global (call [0x507cb8], the memory manager) reads what the code pointer the image holds
  there reads, one through the sound driver's slots what either driver's routine reads (HOOKS), and any other indirect call reads all four (the original passes arguments in ebx
  too: 0x45e9e0, the RTL move 0x4eb5e0);
- a jump through an unbounded table, an undecodable instruction or a routine too deep to follow
  reads all four;
- partial writes (al, ax) keep the register live; nothing is live after a ret.
Pushes are reads only where the pushed value is read back:
- ebx, esi, edi and ebp are callee-saved in Delphi's convention: pushing one saves it;
- a prologue push after `mov ebp, esp` fills the frame slot under ebp, followed as a variable of
  its own (read by any access overlapping it, an indexed access of the frame, or an address taken
  of the slot itself);
- a frameless prologue push of a register the epilogue pops again is a save, unless the routine
  reads through esp at or above the locals the prologue reserves.
"""
import sys

from capstone import CS_AC_READ, CS_AC_WRITE
from capstone import x86_const as X

import lift

# The registers a call compares (the stub logs them), then the ones a port hands over through
# port_call_with: a callee that reads those needs them passed.
COMPARED = ('eax', 'edx', 'ebx', 'ecx')
NAMES = COMPARED + ('esi', 'edi', 'ebp')
ALL = frozenset(NAMES)
WIDE = {X.X86_REG_EAX: 'eax', X.X86_REG_EDX: 'edx', X.X86_REG_EBX: 'ebx', X.X86_REG_ECX: 'ecx',
        X.X86_REG_ESI: 'esi', X.X86_REG_EDI: 'edi', X.X86_REG_EBP: 'ebp'}
SAVED = (X.X86_REG_EBX, X.X86_REG_ESI, X.X86_REG_EDI, X.X86_REG_EBP)
PART = {}
for table in (lift.REG16, lift.REG8L, lift.REG8H):
    for reg, name in table.items():
        if name in NAMES:
            PART[reg] = name
# Instructions whose register operands are written, not read, when both operands are the same
# register (xor eax, eax).
CLEARS = ('xor', 'sub')

_known = {}
_active = set()


def _regs(insn):
    """The registers (of the four) an instruction reads and fully writes."""
    ops = insn.operands
    if (insn.mnemonic in ('lea', 'mov') and len(ops) == 2 and ops[0].type == X.X86_OP_REG and
            ((ops[1].type == X.X86_OP_REG and ops[1].reg == ops[0].reg) or
             (insn.mnemonic == 'lea' and ops[1].mem.base == ops[0].reg and not ops[1].mem.index
              and not ops[1].mem.disp))):
        return set(), set()  # padding: lea edx, [edx] / mov eax, eax
    reads, writes = insn.regs_access()
    used, defined = set(), set()
    for reg in reads:
        name = WIDE.get(reg) or PART.get(reg)
        if name:
            used.add(name)
    for reg in writes:
        if reg in WIDE:
            defined.add(WIDE[reg])
    if (insn.mnemonic in CLEARS and len(insn.operands) == 2 and
            insn.operands[0].type == X.X86_OP_REG and insn.operands[1].type == X.X86_OP_REG and
            insn.operands[0].reg == insn.operands[1].reg and insn.operands[0].reg in WIDE):
        used.discard(WIDE[insn.operands[0].reg])
    return used, defined


def _slots(insn, slots):
    """The frame slots (ebp offsets) an instruction reads and fully writes."""
    used, defined = set(), set()
    for op in insn.operands:
        if op.type != X.X86_OP_MEM or op.mem.base != X.X86_REG_EBP:
            continue
        if insn.mnemonic == 'lea':
            if insn.operands[0].reg == X.X86_REG_ESP:
                return set(), set()  # the epilogue's lea esp, [ebp - n]
            # An address into the pushed slots escapes them; one of a local below them does not
            # reach them (Delphi's locals lie under the registers it saves).
            return {s for s in slots if s <= op.mem.disp < s + 4}, set()
        if op.mem.index:
            return set(slots), set()
        low, high = op.mem.disp, op.mem.disp + op.size
        for slot in slots:
            if low < slot + 4 and slot < high:
                if op.access & CS_AC_READ:
                    used.add(slot)
                elif op.access & CS_AC_WRITE and low == slot and op.size == 4:
                    defined.add(slot)
                elif op.access & CS_AC_WRITE:
                    used.add(slot)  # a partial write keeps the rest
    return used, defined


def _prologue(seen, start):
    """The prologue's register pushes: address -> frame slot (an ebp offset) for a push after
    `mov ebp, esp`, None for one before it."""
    found = {}
    framed = False
    address = start
    depth = 0
    while address in seen:
        insn = seen[address]
        if insn.mnemonic == 'push' and insn.operands[0].type == X.X86_OP_REG:
            depth += 4
            found[address] = -depth if framed else None
        elif insn.mnemonic == 'mov' and insn.op_str == 'ebp, esp':
            framed = True
            depth = 0
        else:
            break
        address += insn.size
    return found


def _epilogue_pops(seen):
    """The registers popped by the run of pops right before each ret, if every ret has them."""
    popped = None
    for address, insn in seen.items():
        if insn.mnemonic != 'ret':
            continue
        regs = set()
        back = address
        while True:
            before = [a for a in seen if a < back and a + seen[a].size == back]
            if not before or seen[before[0]].mnemonic not in ('pop', 'mov'):
                break
            prior = seen[before[0]]
            if prior.mnemonic == 'pop' and prior.operands[0].type == X.X86_OP_REG:
                regs.add(prior.operands[0].reg)
            elif prior.op_str != 'esp, ebp':
                break
            back = before[0]
        popped = regs if popped is None else popped & regs
    return popped or set()


def _reserved(seen, start):
    """The bytes of locals the prologue reserves under its pushes (sub esp, n / add esp, -n)."""
    address = start
    while address in seen:
        insn = seen[address]
        if insn.mnemonic == 'push' or (insn.mnemonic == 'mov' and insn.op_str == 'ebp, esp'):
            address += insn.size
            continue
        if (insn.mnemonic in ('sub', 'add') and insn.operands[0].type == X.X86_OP_REG and
                insn.operands[0].reg == X.X86_REG_ESP and insn.operands[1].type == X.X86_OP_IMM):
            amount = insn.operands[1].imm & 0xffffffff
            return amount if insn.mnemonic == 'sub' else (-amount) & 0xffffffff
        break
    return 0


def _reads_esp(seen, reserve):
    """Whether the routine may read its pushed registers back through esp: an esp-based access at
    or above the reserved locals (pushes later in the routine only move esp further down)."""
    return any(op.type == X.X86_OP_MEM and op.mem.base == X.X86_REG_ESP and
               (op.mem.index or op.mem.disp >= reserve)
               for insn in seen.values() for op in insn.operands if insn.mnemonic != 'lea' or
               insn.operands[0].reg != X.X86_REG_ESP)


def _import_slot(insn):
    op = insn.operands[0]
    return (op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index and
            0x4f1000 <= (op.mem.disp & 0xffffffff) < 0x4f4000)


# The sound driver's routines, called through 0x52f028 .. 0x52f08f: 0x40a830 fills the slots from
# the silent driver's table 0x4f7670, and choosing a driver (0x40aa10) from the software mixer's
# 0x4f651c (or a driver record's own table, which no driver of the original has).
HOOKS = (0x52f028, 0x68, (0x4f7670, 0x4f651c))


# Indirect calls whose callee is known by what installs it: the registers read, or the routines
# that can be called there.
SITES = {
    # GetMem's C++ new-handler (0x4ca000; thread data +0x28 by 0x4ce780), called with the size in
    # eax. No routine of the original installs one, so the call never happens.
    0x4ca02f: frozenset(('eax',)),
    # The thread value's constructor (0x4dbf80, call esi): the edx of every caller (0x4cbf01,
    # 0x4ce22a, 0x4ce74a, 0x4ce78f, 0x4d9410 and 0x4d9444) is one of these.
    0x4dbfe3: (0x4cc780, 0x4ce7c0, 0x4ce7a0),
}


def _through(insn, depth):
    """What an indirect call or jump reads: the registers of its operand, and the callee's."""
    known = SITES.get(insn.address)
    if isinstance(known, frozenset):
        return set(known)
    if known is not None:
        return set().union(*(inputs(target, depth + 1) for target in known))
    own, _ = _regs(insn)
    op = insn.operands[0]
    slot = op.mem.disp & 0xffffffff if op.type == X.X86_OP_MEM else None
    if (slot is not None and not op.mem.base and not op.mem.index and
            HOOKS[0] <= slot < HOOKS[0] + HOOKS[1]):
        used = set(own)
        for table in HOOKS[2]:
            target = int.from_bytes(lift.code_at(table + slot - HOOKS[0], 4), 'little')
            used |= inputs(target, depth + 1)
        return used
    if op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index:
        try:
            target = int.from_bytes(lift.code_at(op.mem.disp & 0xffffffff, 4), 'little')
        except Exception:  # noqa: BLE001 - outside the image
            return set(ALL)
        if lift.BASE + 0x1000 <= target < lift.BASE + 0xf1000:
            return own | set(inputs(target, depth + 1))
    # A method or procedure variable: Delphi code, which takes no arguments in esi, edi or ebp
    # (the runtime's assembly that does is only called directly).
    return own | set(COMPARED)


def inputs(start, depth=0):
    """The set of eax, edx, ebx and ecx the routine at `start` reads before writing."""
    if start in _known:
        return _known[start]
    if start in _active or depth > 24:
        return ALL
    if not lift.BASE <= start < lift.BASE + 0xf1000:
        return ALL
    _active.add(start)
    try:
        result = _inputs(start, depth)
    except (NotImplementedError, ValueError, IndexError):
        result = ALL
    finally:
        _active.discard(start)
    _known[start] = result
    return result


def _inputs(start, depth, entry=True):
    seen = lift.trace(start)
    prologue = _prologue(seen, start) if entry else {}
    slots = sorted(s for s in prologue.values() if s is not None)
    saves = (_epilogue_pops(seen) if entry and not _reads_esp(seen, _reserved(seen, start))
             else set())
    order = sorted(seen)
    successors = {}
    effects = {}
    nothing = (frozenset(), frozenset())
    for address in order:
        insn = seen[address]
        mnemonic = insn.mnemonic
        nxt = address + insn.size
        used, defined = set(), set()
        if mnemonic == 'ret':
            successors[address] = ()
        elif mnemonic == 'jmp':
            op = insn.operands[0]
            if op.type == X.X86_OP_IMM and op.imm in seen:
                successors[address] = (op.imm,)
            elif op.type == X.X86_OP_IMM:
                successors[address] = ()  # a tail jump into another routine
                used = set(inputs(op.imm, depth + 1))
            elif address in lift.TABLES:
                successors[address] = tuple(lift.TABLES[address])
                used, _ = _regs(insn)
            elif _import_slot(insn):
                successors[address] = ()
            else:
                successors[address] = ()
                used = _through(insn, depth)
        elif mnemonic in lift.JUMPS:
            successors[address] = (insn.operands[0].imm, nxt)
            used, defined = _regs(insn)
        else:
            successors[address] = (nxt,)
            if mnemonic == 'call':
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    used = set(inputs(op.imm, depth + 1))
                elif not _import_slot(insn):
                    used = _through(insn, depth)
            elif mnemonic == 'push' and insn.operands[0].type == X.X86_OP_REG:
                reg = insn.operands[0].reg
                name = WIDE.get(reg)
                slot = prologue.get(address)
                if reg in SAVED or name is None:
                    pass
                elif slot is not None:
                    # Read when its slot is: the pair is joined below.
                    used, defined = {('push', slot, name)}, set()
                elif address in prologue and reg in saves:
                    pass
                else:
                    used = {name}
            else:
                used, defined = _regs(insn)
        frame_used, frame_defined = _slots(insn, slots) if slots else (set(), set())
        effects[address] = (frozenset(used | frame_used), frozenset(defined | frame_defined))
    live = {address: frozenset() for address in order}
    changed = True
    while changed:
        changed = False
        for address in reversed(order):
            used, defined = effects[address]
            out = frozenset()
            for successor in successors[address]:
                out |= live.get(successor, ALL)
            value = set(out - defined)
            for item in used:
                if isinstance(item, tuple):
                    _, slot, name = item
                    value.discard(slot)  # the push fills the slot
                    if slot in out:
                        value.add(name)
                else:
                    value.add(item)
            value = frozenset(value)
            if value != live[address]:
                live[address] = value
                changed = True
    return frozenset(n for n in live[start] if n in NAMES)


def live_at(address):
    """The registers (of the four) read before written from `address` on, inside a routine (a
    call's return address): no prologue there."""
    try:
        return _inputs(address, 0, entry=False)
    except (NotImplementedError, ValueError, IndexError):
        return ALL


_image = None


def _code():
    global _image
    if _image is None:
        _image = lift.pe.get_memory_mapped_image()
    return _image


def returned_read(start, name='edx'):
    """Whether a caller of the routine at `start` may read the register it leaves (edx: the high
    half of a 64-bit result). Every direct call site is followed from its return address; a tail
    jump to the routine, or its address held anywhere in the image (a method table, a pointer
    pushed or stored), counts as a reader."""
    image = _code()
    text = start.to_bytes(4, 'little')
    if image.find(text) >= 0:
        return True
    for at in range(0x1000, 0xf1000 - 5):
        opcode = image[at]
        if opcode not in (0xe8, 0xe9):
            continue
        site = lift.BASE + at
        target = (site + 5 + int.from_bytes(image[at + 1:at + 5], 'little', signed=True)) \
            & 0xffffffff
        if target != start:
            continue
        if opcode == 0xe9 or name in live_at(site + 5):
            return True
    return False


def mask(start):
    """The four compared call registers as a tuple of booleans (eax, edx, ebx, ecx)."""
    found = inputs(start)
    return tuple(name in found for name in COMPARED)


def main():
    for text in sys.argv[1:]:
        address = int(text, 16)
        print('%x reads %s; callers %s edx' % (
            address, ' '.join(n for n in NAMES if n in inputs(address)) or '-',
            'read' if returned_read(address) else 'never read'))


if __name__ == '__main__':
    main()
