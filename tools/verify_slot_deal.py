"""Compare the complete original slot shuffle with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EDX
import verify_common_a as common

U = c.c_uint32
Draw = c.CFUNCTYPE(U, U, c.c_void_p)


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'slot-deal', 'slot_deal.c')
    n.vertrix_slot_deal.argtypes = [U, U, U, Draw, c.c_void_p, c.POINTER(U)]
    n.vertrix_slot_deal.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x415c60)
    draws, replay = [], []

    def on_draw(uc):
        limit = uc.reg_read(UC_X86_REG_EDX)
        pick = rng.randrange(limit) | (rng.getrandbits(16) << 16 if rng.random() < 0.3 else 0)
        draws.append((limit, pick))
        cpu.mem_write(common.DATA, struct.pack('<I', pick))

    common.stub(cpu, 0x4826c0, on_draw)

    @Draw
    def draw(limit, context):
        replay.append((limit, draws[len(replay)][1]))
        return draws[len(replay) - 1][1]

    totals = {'deal': 0}
    for case in range(args.cases):
first, second,
    third = rng.sample(range(19), 3) cpu.mem_write(0x4f84e0, struct.pack('<I', first))
                cpu.mem_write(0x4f84cc, struct.pack('<I', second))
                    cpu.mem_write(0x4f84b8, struct.pack('<I', third)) noise =
        rng.randbytes(0x40) cpu.mem_write(0x53bad8, noise) out =
            (U * 15).from_buffer_copy(noise[:60]) draws.clear();
replay.clear() original.call(0x415c60) assert n.vertrix_slot_deal(first, second, third, draw, None,
                                                                  out) == 1 assert draws
    == replay and len(draws) == 16,
    case assert bytes(out) == bytes(cpu.mem_read(0x53bad8, 60)),
    (case, list(out), struct.unpack('<15I', cpu.mem_read(0x53bad8, 60)), first, second, third)assert
        struct.unpack('<3I', cpu.mem_read(0x4f84e0, 4) + cpu.mem_read(0x4f84cc, 4) +
                                 cpu.mem_read(0x4f84b8, 4)) == (first, second, third),
    case totals['deal'] +=
    1 common.report(
        args, 'slot-deal', totals,
        'Complete 415c60 runs in the original (draw 4826c0 stubbed and replayed) over random ' 'distinct reserved slots; all 15 output dwords and the 16 draws compare.')

        if __name__
    == '__main__':
main()
