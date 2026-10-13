# Find unported routines whose code is identical to a ported routine's (same instructions,
# internal jumps by offset, calls and constants by absolute value).
import os, sys, re, pefile, capstone
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import lift
from dispatch_boundaries import PORTS, NATIVE_PORTS
pe = pefile.PE(str(lift.EXE))
image = pe.get_memory_mapped_image()
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
md.detail = False

def body(start):
    seen = {}
    work = [start]
    while work:
        a = work.pop()
        while a not in seen:
            off = a - 0x400000
            if off < 0 or off >= len(image) or len(seen) > 3000:
                return None
            ins = next(md.disasm(image[off:off + 16], a), None)
            if ins is None:
                return None
            seen[a] = ins
            m = ins.mnemonic
            if m in ('ret', 'retf') or (m == 'jmp' and not ins.op_str.startswith('0x')):
                break
            if m.startswith('j') or m.startswith('loop'):
                if ins.op_str.startswith('0x'):
                    t = int(ins.op_str, 16)
                    if m == 'jmp':
                        a = t
                        continue
                    work.append(t)
            a = ins.address + ins.size
    out = []
    for a in sorted(seen):
        ins = seen[a]
        op = ins.op_str
        if (ins.mnemonic.startswith('j') or ins.mnemonic.startswith('loop')) and op.startswith('0x'):
            t = int(op, 16)
            op = '@%d' % (t - start) if t in seen else op
        out.append((a - start, ins.mnemonic, op))
    return tuple(out)

disp = open(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'source', 'lifted_dispatch.c')).read()
live = [int(a, 16) for a in re.findall(r'\{(0x[0-9a-f]+), lifted_\w+,', disp)]
done = dict(PORTS)
done.update(NATIVE_PORTS)
sig = {}
for a, f in done.items():
    b = body(a)
    if b:
        sig.setdefault(b, (a, f))
for a in live:
    if a in done:
        continue
    b = body(a)
    if b and b in sig:
        print(hex(a), hex(sig[b][0]), sig[b][1], len(b))
