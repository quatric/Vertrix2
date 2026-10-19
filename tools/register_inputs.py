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
  reads its slot back: the stack depth of every instruction is followed (pushes, pops, esp
  arithmetic and the ret counts of callees), and an esp access at an unknown depth counts as
  reading every slot.
"""
import bisect
import re
import sys
from pathlib import Path

from capstone import CS_AC_READ, CS_AC_WRITE
from capstone import x86_const as X

import lift
from import_args import BY_SLOT

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


def _padding(insn):
    """Alignment padding that does nothing: lea edx, [edx] / mov eax, eax."""
    ops = insn.operands
    return (insn.mnemonic in ('lea', 'mov') and len(ops) == 2 and ops[0].type == X.X86_OP_REG and
            ((ops[1].type == X.X86_OP_REG and ops[1].reg == ops[0].reg) or
             (insn.mnemonic == 'lea' and ops[1].mem.base == ops[0].reg and not ops[1].mem.index
              and not ops[1].mem.disp and not ops[1].mem.segment)))


def _regs(insn):
    """The registers (of the four) an instruction reads and fully writes."""
    if _padding(insn):
        return set(), set()
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


def _halves(names):
    """Registers as the units the liveness follows: the two low bytes and the high 16 bits (a
    16-bit write replaces both low bytes, a byte write its own byte)."""
    return {name + unit for name in names for unit in ('.b0', '.b1', '.hi')}


WORDS = {reg: name for reg, name in lift.REG16.items() if name in NAMES}
# The units a 16-bit or byte register covers.
UNITS = {}
for reg, name in WORDS.items():
    UNITS[reg] = {name + '.b0', name + '.b1'}
for reg, name in lift.REG8L.items():
    if name in NAMES:
        UNITS[reg] = {name + '.b0'}
for reg, name in lift.REG8H.items():
    if name in NAMES:
        UNITS[reg] = {name + '.b1'}


EVERY = frozenset(_halves(NAMES))


def _regs_halves(insn):
    """_regs in register units (_halves)."""
    if _padding(insn):
        return set(), set()
    reads, writes = insn.regs_access()
    used, defined = set(), set()
    for reg in reads:
        if reg in WIDE:
            used |= _halves((WIDE[reg],))
        elif reg in UNITS:
            used |= UNITS[reg]
    for reg in writes:
        if reg in WIDE:
            defined |= _halves((WIDE[reg],))
        elif reg in UNITS:
            defined |= UNITS[reg]
    ops = insn.operands
    if (insn.mnemonic in CLEARS and len(ops) == 2 and ops[0].type == X.X86_OP_REG and
            ops[1].type == X.X86_OP_REG and ops[0].reg == ops[1].reg):
        if ops[0].reg in WIDE:
            used -= _halves((WIDE[ops[0].reg],))
        elif ops[0].reg in UNITS:
            used -= UNITS[ops[0].reg]
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
            if not before:
                break
            prior = seen[before[0]]
            if prior.mnemonic == 'pop' and prior.operands[0].type == X.X86_OP_REG:
                regs.add(prior.operands[0].reg)
            elif not (prior.op_str == 'esp, ebp' or prior.mnemonic == 'nop' or
                      _padding(prior)):
                break
            back = before[0]
        popped = regs if popped is None else popped & regs
    return popped or set()


TABLES = {}


def _jump_table(seen, insn):
    """lift.jump_table, and also a byte index zero-extended after its bound check (0x4da48f:
    `cmp al, 6; ja ...; movzx eax, al; jmp [eax*4 + table]`)."""
    try:
        return lift.jump_table(seen, insn)
    except NotImplementedError:
        mem = insn.operands[0].mem
        if insn.operands[0].type != X.X86_OP_MEM or mem.base or not mem.index or mem.scale != 4:
            raise
        prior = sorted((a for a in seen if a < insn.address), reverse=True)[:8]
        if not prior or seen[prior[0]].mnemonic != 'movzx':
            raise
        source = seen[prior[0]].operands[1]
        if source.type != X.X86_OP_REG or seen[prior[0]].operands[0].reg != mem.index:
            raise
        count = None
        for address in prior[1:]:
            check = seen[address]
            if (check.mnemonic == 'cmp' and check.operands[0].type == X.X86_OP_REG and
                    check.operands[0].reg == source.reg and
                    check.operands[1].type == X.X86_OP_IMM):
                count = check.operands[1].imm + 1
                break
        if count is None or not 0 < count <= 256:
            raise
        base = mem.disp & 0xffffffff
        return [int.from_bytes(lift.code_at(base + 4 * i, 4), 'little') for i in range(count)]


_entries = None


def _foreign(target, start):
    """Whether a jump to `target` leaves the routine at `start` for another one: a tail call to an
    address some instruction calls directly, to a tail shared by routines (jumps reach it from
    sites over 0x800 bytes apart: 0x4dee00 ends 0x4cf8d0, 0x4dd430, 0x4ddc30 and 0x4e1200), or to
    one before the start."""
    global _entries
    if _entries is None:
        image = _code()
        _entries = set()
        jumps = {}
        for at in range(0x1000, 0xf1000 - 6):
            site = lift.BASE + at
            if image[at] in (0xe8, 0xe9):
                to = (site + 5 + int.from_bytes(image[at + 1:at + 5], 'little', signed=True)) \
                    & 0xffffffff
                if image[at] == 0xe8:
                    _entries.add(to)
                else:
                    jumps.setdefault(to, []).append(site)
            elif image[at] == 0x0f and 0x80 <= image[at + 1] <= 0x8f:
                to = (site + 6 + int.from_bytes(image[at + 2:at + 6], 'little', signed=True)) \
                    & 0xffffffff
                jumps.setdefault(to, []).append(site)
        _entries |= {to for to, sites in jumps.items() if max(sites) - min(sites) > 0x800}
    return target != start and (target < start or target in _entries)


def _trace(start):
    """lift.trace with the jump tables of _jump_table, kept in TABLES, not following tail calls."""
    seen, todo = {}, [start]
    while todo:
        address = todo.pop()
        while address not in seen:
            insn = lift.insn_at(address)
            if insn is None:
                raise ValueError('undecodable %x' % address)
            seen[address] = insn
            mnemonic = insn.mnemonic
            if mnemonic in lift.JUMPS:
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    if not _foreign(op.imm, start):
                        todo.append(op.imm)
                elif mnemonic == 'jmp' and not _import_slot(insn):
                    targets = _jump_table(seen, insn)
                    TABLES[insn.address] = targets
                    todo.extend(targets)
                if mnemonic == 'jmp':
                    break
            if mnemonic == 'ret':
                break
            address += insn.size
    return seen


def _successors(seen, address):
    insn = seen[address]
    nxt = address + insn.size
    if insn.mnemonic == 'ret':
        return ()
    if insn.mnemonic == 'jmp':
        op = insn.operands[0]
        if op.type == X.X86_OP_IMM:
            return (op.imm,) if op.imm in seen else ()
        return tuple(TABLES.get(address, ()))
    if insn.mnemonic in lift.JUMPS:
        return (insn.operands[0].imm, nxt)
    return (nxt,)


def _popped(insn):
    """The stack bytes a call's callee removes with its ret, or None when unknown."""
    op = insn.operands[0]
    if op.type == X.X86_OP_IMM:
        count = lift.callee_args(op.imm)
    elif _import_slot(insn):
        count = BY_SLOT.get(op.mem.disp & 0xffffffff)
    elif op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index:
        target = _stored_code(op.mem.disp & 0xffffffff)
        count = None if target is None else lift.callee_args(target)
    else:
        count = None
    return None if count is None else 4 * count


def _step(insn, depth):
    """The bytes pushed since the entry after the instruction, or None when not known."""
    mnemonic = insn.mnemonic
    ops = insn.operands
    # An operand-size prefix makes a 2-byte push; segment registers push 4 bytes.
    size = 2 if 0x66 in insn.prefix else 4
    if mnemonic == 'push':
        return depth + size
    if mnemonic == 'pop':
        return depth - size
    if mnemonic in ('pushal', 'pushad'):
        return depth + 32
    if mnemonic in ('popal', 'popad'):
        return depth - 32
    if mnemonic in ('pushfd', 'pushf'):
        return depth + 4
    if mnemonic in ('popfd', 'popf'):
        return depth - 4
    if mnemonic == 'call':
        popped = _popped(insn)
        return None if popped is None else depth - popped
    if (mnemonic in ('sub', 'add') and ops[0].type == X.X86_OP_REG and
            ops[0].reg == X.X86_REG_ESP):
        if ops[1].type != X.X86_OP_IMM:
            return None
        amount = ops[1].imm if ops[1].imm < 0x80000000 else ops[1].imm - 0x100000000
        return depth + amount if mnemonic == 'sub' else depth - amount
    _, writes = insn.regs_access()
    if X.X86_REG_ESP in writes:
        return None
    return depth


def _depths(seen, start):
    """The bytes pushed since the entry before each instruction (None where paths disagree or the
    routine moves esp in a way not followed)."""
    depth = {start: 0}
    todo = [start]
    while todo:
        address = todo.pop()
        here = depth[address]
        after = None if here is None else _step(seen[address], here)
        for successor in _successors(seen, address):
            if successor not in seen:
                continue
            if successor not in depth:
                depth[successor] = after
                todo.append(successor)
            elif depth[successor] is not None and depth[successor] != after:
                depth[successor] = None
                todo.append(successor)
    return depth


def _saves(seen, start, prologue):
    """The registers of the frameless prologue pushes that are only saved: popped again before
    every ret, and their slots never read (through esp, or through an ebp set up after them)."""
    popped = _epilogue_pops(seen)
    slots = {}
    offset = 0
    ebp_depth = None
    address = start
    while address in seen:
        insn = seen[address]
        if address in prologue and prologue[address] is None:
            offset += 4
            slots[insn.operands[0].reg] = -offset
        elif insn.mnemonic == 'mov' and insn.op_str == 'ebp, esp':
            ebp_depth = offset
        elif address not in prologue:
            break
        address += insn.size
    if not slots:
        return set()
    reserve = 0
    if address in seen:
        first = seen[address]
        if (first.mnemonic in ('sub', 'add') and first.operands[0].type == X.X86_OP_REG and
                first.operands[0].reg == X.X86_REG_ESP and first.operands[1].type == X.X86_OP_IMM):
            amount = first.operands[1].imm & 0xffffffff
            reserve = amount if first.mnemonic == 'sub' else (-amount) & 0xffffffff
    depths = _depths(seen, start)
    unsafe = set()
    for address, insn in seen.items():
        for op in insn.operands:
            if op.type != X.X86_OP_MEM:
                continue
            if op.mem.base == X.X86_REG_ESP:
                if insn.mnemonic == 'lea' and insn.operands[0].reg == X.X86_REG_ESP:
                    continue
                if op.mem.index:
                    return set()
                here = depths.get(address)
                if here is None:
                    # esp only goes further down after the prologue in balanced code: an access
                    # inside the locals the prologue reserves stays below the saves.
                    if op.mem.disp + op.size <= reserve:
                        continue
                    return set()
                low = -here + op.mem.disp
            elif op.mem.base == X.X86_REG_EBP and ebp_depth is not None:
                if op.mem.index:
                    return set()
                low = -ebp_depth + op.mem.disp
            else:
                continue
            reads = insn.mnemonic == 'lea' or op.access & CS_AC_READ
            high = low + (1 if insn.mnemonic == 'lea' else op.size)
            for reg, slot in slots.items():
                if reads and low < slot + 4 and slot < high:
                    unsafe.add(reg)
    return {reg for reg in slots if reg in popped and reg not in unsafe}


IMPORTS = (0x4f1000, 0x4f4000)


def _import_slot(insn):
    op = insn.operands[0]
    return (op.type == X.X86_OP_MEM and not op.mem.base and not op.mem.index and
            IMPORTS[0] <= (op.mem.disp & 0xffffffff) < IMPORTS[1])


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


def _stored_code(slot):
    """The code address the image holds in a global, or None."""
    try:
        target = int.from_bytes(lift.code_at(slot, 4), 'little')
    except Exception:  # noqa: BLE001 - outside the image
        return None
    return target if lift.BASE + 0x1000 <= target < lift.BASE + 0xf1000 else None


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


# Routines whose arguments are known better than the analysis can see.
ROUTINES = {
    # The C++ runtime's thread data (0x4ce740) and its +0x1038 part (0x4ce780): they load their
    # TLS key and constructor and call 0x4dbf80, taking no register argument. Only a failure to
    # create the data reaches the exception machinery (0x4da66e), which records whatever
    # registers it is handed.
    0x4ce740: frozenset(),
    0x4ce780: frozenset(),
}


def inputs(start, depth=0):
    """The set of eax, edx, ebx and ecx the routine at `start` reads before writing."""
    if start in ROUTINES:
        return ROUTINES[start]
    if IMPORTS[0] <= start < IMPORTS[1]:
        return frozenset()  # a Windows import (called through its slot): stack arguments only
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


def _inputs(start, depth, entry=True, at_return=()):
    seen = _trace(start)
    prologue = _prologue(seen, start) if entry else {}
    slots = sorted(s for s in prologue.values() if s is not None)
    saves = _saves(seen, start, prologue) if entry else set()
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
            used = _halves(at_return)
        elif mnemonic == 'jmp':
            op = insn.operands[0]
            if op.type == X.X86_OP_IMM and op.imm in seen:
                successors[address] = (op.imm,)
            elif op.type == X.X86_OP_IMM:
                successors[address] = ()  # a tail jump into another routine
                used = _halves(inputs(op.imm, depth + 1))
            elif address in TABLES:
                successors[address] = tuple(TABLES[address])
                used, _ = _regs_halves(insn)
            elif _import_slot(insn):
                successors[address] = ()
            else:
                successors[address] = ()
                used = _halves(_through(insn, depth))
        elif mnemonic in lift.JUMPS:
            target = insn.operands[0].imm
            if target in seen:
                successors[address] = (target, nxt)
                used, defined = _regs_halves(insn)
            else:
                # A conditional tail call: either branch.
                successors[address] = (nxt,)
                used = _regs_halves(insn)[0] | _halves(inputs(target, depth + 1))
        else:
            successors[address] = (nxt,)
            if mnemonic == 'call':
                op = insn.operands[0]
                if op.type == X.X86_OP_IMM:
                    used = _halves(inputs(op.imm, depth + 1))
                elif not _import_slot(insn):
                    used = _halves(_through(insn, depth))
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
                    used = _halves((name,))
            else:
                used, defined = _regs_halves(insn)
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
                out |= live.get(successor, EVERY)
            value = set(out - defined)
            for item in used:
                if isinstance(item, tuple):
                    _, slot, name = item
                    value.discard(slot)  # the push fills the slot
                    if slot in out:
                        value |= _halves((name,))
                else:
                    value.add(item)
            value = frozenset(value)
            if value != live[address]:
                live[address] = value
                changed = True
    return frozenset(n for n in NAMES if _halves((n,)) & live[start])


def live_at(address, at_return=()):
    """The registers (of the four) read before written from `address` on, inside a routine (a
    call's return address): no prologue there. Those in `at_return` count as read by its `ret`."""
    try:
        return _inputs(address, 0, entry=False, at_return=at_return)
    except (NotImplementedError, ValueError, IndexError):
        return ALL


_starts = None


def _enclosing(site):
    """The start of the dispatched routine holding `site` (the nearest at or below it), or None."""
    global _starts
    if _starts is None:
        text = (Path(__file__).resolve().parents[1] / 'source' / 'lifted_dispatch.c').read_text()
        _starts = sorted(int(a, 16) for a in re.findall(r'^    \{(0x[0-9a-f]+), ', text, re.M))
    index = bisect.bisect_right(_starts, site) - 1
    return _starts[index] if index >= 0 else None


_image = None


def _code():
    global _image
    if _image is None:
        _image = lift.pe.get_memory_mapped_image()
    return _image


def returned_read(start, name='edx', _outer=None):
    """Whether a caller of the routine at `start` may read the register it leaves (eax: its result;
    edx: the high half of a 64-bit result, or what a routine that keeps it leaves). Every direct call site is followed from its return address; a tail
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
        # Left unchanged to a ret, the register is the caller's own result (0x43ab60 pops two
        # registers and returns 0x4279b0's eax, which 0x452e00 tests): read if the caller's
        # callers read it. A cycle or an unknown caller counts as read.
        if name in live_at(site + 5, at_return=(name,)):
            outer = _outer if _outer is not None else set()
            enclosing = _enclosing(site)
            if enclosing is None or enclosing in outer or len(outer) > 16:
                return True
            if returned_read(enclosing, name, outer | {start}):
                return True
    return False


def mask(start):
    """The four compared call registers as a tuple of booleans (eax, edx, ebx, ecx)."""
    found = inputs(start)
    return tuple(name in found for name in COMPARED)


def main():
    for text in sys.argv[1:]:
        address = int(text, 16)
        left = [n for n in ('eax', 'edx') if returned_read(address, n)]
        print('%x reads %s; callers read %s' % (
            address, ' '.join(n for n in NAMES if n in inputs(address)) or '-',
            ' and '.join(left) if left else 'neither eax nor edx'))


if __name__ == '__main__':
    main()
