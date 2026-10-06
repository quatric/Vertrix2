"""Translate original x86 routines of Vertrix2.exe into C, one statement per instruction.

    python3 tools/lift.py Vertrix2.exe 0x456d80 0x456de0 ... --output source/bonus_lifted.c

The output is a statement-for-statement translation, not a hand recovery: registers are C
variables, the flags are computed as each instruction sets them, jumps are gotos, and every memory
access, call and virtual call goes through source/lifted_runtime.h. tools/verify_lifted.py runs
each lifted routine against the original under Unicorn and compares the results, so a routine is
only kept when that comparison passes. Routines that use instructions outside the supported subset
(string operations, the FPU, ...) are refused.
"""
import argparse
import re
import sys
from pathlib import Path

import capstone
from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG

sys.path.insert(0, str(Path(__file__).resolve().parent))
from original import Original

REG32 = ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp")
SUB16 = {"ax": "eax", "bx": "ebx", "cx": "ecx", "dx": "edx", "si": "esi", "di": "edi",
         "bp": "ebp", "sp": "esp"}
SUB8 = {"al": ("eax", 0), "bl": ("ebx", 0), "cl": ("ecx", 0), "dl": ("edx", 0),
        "ah": ("eax", 8), "bh": ("ebx", 8), "ch": ("ecx", 8), "dh": ("edx", 8)}
JCC = {"je": "ZF", "jne": "!ZF", "jl": "SF != OF", "jge": "SF == OF",
       "jle": "ZF || SF != OF", "jg": "!ZF && SF == OF", "jb": "CF", "jae": "!CF",
       "jbe": "CF || ZF", "ja": "!CF && !ZF", "js": "SF", "jns": "!SF", "jo": "OF",
       "jno": "!OF", "jp": "PF", "jnp": "!PF"}
SETCC = {"sete": "ZF", "setne": "!ZF", "setl": "SF != OF", "setge": "SF == OF",
         "setle": "ZF || SF != OF", "setg": "!ZF && SF == OF", "setb": "CF", "setae": "!CF",
         "setbe": "CF || ZF", "seta": "!CF && !ZF", "sets": "SF", "setns": "!SF"}


class Unsupported(Exception):
    pass


class Lifter:
    def __init__(self, original):
        self.original = original
        self.md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
        self.md.detail = True
        self.ret_cache = {}

    def decode(self, address):
        data = bytes(self.original.cpu.mem_read(address, 16))
        for insn in self.md.disasm(data, address):
            return insn
        raise Unsupported(f"cannot decode {address:#x}")

    def callee_arguments(self, target):
        """Stack dwords a callee pops: the immediate of its first ret."""
        if target in self.ret_cache:
            return self.ret_cache[target]
        count = 0
        address = target
        for _ in range(400):
            try:
                insn = self.decode(address)
            except Unsupported:
                break
            if insn.mnemonic == "ret":
                count = insn.operands[0].imm // 4 if insn.operands else 0
                break
            address += insn.size
        self.ret_cache[target] = count
        return count

    # ---- operands ----------------------------------------------------------------------------
    def reg(self, insn, op):
        return insn.reg_name(op.reg)

    def address(self, insn, op):
        mem = op.mem
        parts = []
        if mem.base:
            parts.append(insn.reg_name(mem.base))
        if mem.index:
            scale = f" * {mem.scale}u" if mem.scale != 1 else ""
            parts.append(insn.reg_name(mem.index) + scale)
        if mem.disp or not parts:
            parts.append(f"{mem.disp & 0xffffffff:#x}u")
        base_only = mem.base and not mem.index
        base = insn.reg_name(mem.base) if base_only and insn.reg_name(mem.base) not in ("esp", "ebp") else "0"
        return " + ".join(parts), base

    def read(self, insn, op, width=None):
        width = width or op.size * 8
        if op.type == X86_OP_IMM:
            return f"{op.imm & 0xffffffff:#x}u"
        if op.type == X86_OP_REG:
            name = self.reg(insn, op)
            if name in REG32:
                return name
            if name in SUB16:
                return f"({SUB16[name]} & 0xffffu)"
            if name in SUB8:
                base, shift = SUB8[name]
                return f"(({base} >> {shift}) & 0xffu)"
            raise Unsupported(f"register {name}")
        if op.type == X86_OP_MEM:
            addr, base = self.address(insn, op)
            return f"vertrix_lift_read(L, {addr}, {width}, {base})"
        raise Unsupported("operand")

    def write(self, insn, op, value, width=None):
        width = width or op.size * 8
        if op.type == X86_OP_REG:
            name = self.reg(insn, op)
            if name in REG32:
                return f"{name} = {value};"
            if name in SUB16:
                full = SUB16[name]
                return f"{full} = ({full} & 0xffff0000u) | (({value}) & 0xffffu);"
            if name in SUB8:
                base, shift = SUB8[name]
                return f"{base} = ({base} & ~(0xffu << {shift})) | ((({value}) & 0xffu) << {shift});"
            raise Unsupported(f"register {name}")
        if op.type == X86_OP_MEM:
            addr, base = self.address(insn, op)
            return f"vertrix_lift_write(L, {addr}, {width}, {value}, {base});"
        raise Unsupported("operand")

    def width(self, insn):
        for op in insn.operands:
            if op.type == X86_OP_REG:
                name = self.reg(insn, op)
                if name in REG32:
                    return 32
                if name in SUB16:
                    return 16
                return 8
            if op.type == X86_OP_MEM:
                return op.size * 8
        return 32

    # ---- instructions ------------------------------------------------------------------------
    def flags(self, width, result, kind, a="0", b="0"):
        """C statements that set ZF, SF, CF, OF (and PF) after an operation of the given width."""
        m = f"{(1 << width) - 1:#x}u"
        sign = f"{1 << (width - 1):#x}u"
        out = [f"r = ({result}) & {m};", f"ZF = r == 0; SF = (r & {sign}) != 0;",
               "PF = !__builtin_parity(r & 0xffu);"]
        if kind == "add":
            out.append(f"CF = (uint64_t)({a}) + (uint64_t)({b}) > (uint64_t){m}; "
                       f"OF = ((~(({a}) ^ ({b})) & (({a}) ^ r)) & {sign}) != 0;")
        elif kind == "sub":
            out.append(f"CF = (({a}) & {m}) < (({b}) & {m}); "
                       f"OF = (((({a}) ^ ({b})) & (({a}) ^ r)) & {sign}) != 0;")
        else:
            out.append("CF = 0; OF = 0;")
        return " ".join(out)

    def translate(self, insn, labels, nxt):
        mn = insn.mnemonic
        ops = insn.operands
        w = self.width(insn)
        m = f"{(1 << w) - 1:#x}u"
        if mn == "push":
            value = self.read(insn, ops[0], 32)
            return [f"esp -= 4; vertrix_lift_write(L, esp, 32, {value}, 0);"]
        if mn == "pop":
            return ["t = vertrix_lift_read(L, esp, 32, 0); esp += 4; " + self.write(insn, ops[0], "t", 32)]
        if mn in ("mov",):
            return [self.write(insn, ops[0], self.read(insn, ops[1], w), w)]
        if mn in ("movsx", "movzx"):
            src_w = ops[1].size * 8
            value = self.read(insn, ops[1], src_w)
            if mn == "movsx":
                value = f"(uint32_t)(int32_t)(int{src_w}_t)({value})"
            return [self.write(insn, ops[0], value, 32)]
        if mn == "lea":
            addr, _ = self.address(insn, ops[1])
            return [self.write(insn, ops[0], f"({addr})", 32)]
        if mn in ("add", "sub", "cmp", "and", "or", "xor", "test", "adc", "sbb"):
            if mn in ("adc", "sbb"):
                raise Unsupported(mn)
            a = self.read(insn, ops[0], w)
            b = self.read(insn, ops[1], w)
            if mn == "xor" and ops[0].type == X86_OP_REG and ops[1].type == X86_OP_REG and \
                    insn.reg_name(ops[0].reg) == insn.reg_name(ops[1].reg):
                b = a
            op_c = {"add": "+", "sub": "-", "cmp": "-", "and": "&", "or": "|", "xor": "^",
                    "test": "&"}[mn]
            kind = {"add": "add", "sub": "sub", "cmp": "sub"}.get(mn, "logic")
            out = [f"a = {a}; b = {b} & {m};", self.flags(w, f"a {op_c} b", kind, "a", "b")]
            if mn not in ("cmp", "test"):
                out.append(self.write(insn, ops[0], "r", w))
            return out
        if mn in ("inc", "dec"):
            a = self.read(insn, ops[0], w)
            sign = f"{1 << (w - 1):#x}u"
            op_c = "+" if mn == "inc" else "-"
            of = (f"OF = (r == {sign}); " if mn == "inc" else f"OF = (r == {sign} - 1u); ")
            return [f"a = {a}; r = (a {op_c} 1u) & {m}; ZF = r == 0; SF = (r & {sign}) != 0; "
                    f"PF = !__builtin_parity(r & 0xffu); {of}", self.write(insn, ops[0], "r", w)]
        if mn == "neg":
            a = self.read(insn, ops[0], w)
            return [f"a = {a}; r = (0u - a) & {m}; CF = a != 0; ZF = r == 0; "
                    f"SF = (r & {1 << (w - 1):#x}u) != 0; OF = (a == {1 << (w - 1):#x}u); "
                    f"PF = !__builtin_parity(r & 0xffu);", self.write(insn, ops[0], "r", w)]
        if mn == "not":
            return [self.write(insn, ops[0], f"~{self.read(insn, ops[0], w)}", w)]
        if mn in ("shl", "sal", "shr", "sar"):
            a = self.read(insn, ops[0], w)
            count = self.read(insn, ops[1], 8) if len(ops) > 1 else "1u"
            sign = f"{1 << (w - 1):#x}u"
            if mn in ("shl", "sal"):
                body = (f"r = (a << c) & {m}; CF = (a >> ({w} - c)) & 1u; "
                        f"OF = ((r & {sign}) != 0) != CF;")
            elif mn == "shr":
                body = f"r = a >> c; CF = (a >> (c - 1)) & 1u; OF = (a & {sign}) != 0;"
            else:
                body = (f"s = (int32_t)(a << {32 - w}) >> {32 - w}; "
                        f"r = (uint32_t)(s >> c) & {m}; CF = (uint32_t)(s >> (c - 1)) & 1u; OF = 0;")
            return [f"a = {a}; c = {count} & 31u;",
                    f"if (c) {{ {body} ZF = r == 0; SF = (r & {sign}) != 0; "
                    f"PF = !__builtin_parity(r & 0xffu); " + self.write(insn, ops[0], "r", w) + " }"]
        if mn == "imul":
            if len(ops) == 2:
                a, b = self.read(insn, ops[0], 32), self.read(insn, ops[1], 32)
            elif len(ops) == 3:
                a, b = self.read(insn, ops[1], 32), self.read(insn, ops[2], 32)
            else:
                raise Unsupported("one-operand imul")
            return [f"p = (int64_t)(int32_t)({a}) * (int64_t)(int32_t)({b}); r = (uint32_t)p; "
                    f"CF = OF = p != (int64_t)(int32_t)r; ZF = r == 0; SF = (r >> 31) != 0;",
                    self.write(insn, ops[0], "r", 32)]
        if mn in ("idiv", "div"):
            d = self.read(insn, ops[0], 32)
            if mn == "idiv":
                return [f"d = {d}; if (d == 0 || ((((int64_t)(int32_t)edx << 32) | eax) / (int32_t)d) > 2147483647LL || "
                        f"((((int64_t)(int32_t)edx << 32) | eax) / (int32_t)d) < -2147483648LL) {{ L->failed = 1; return 0; }} "
                        f"p = (((int64_t)(int32_t)edx << 32) | eax); "
                        f"eax = (uint32_t)(int32_t)(p / (int32_t)d); edx = (uint32_t)(int32_t)(p % (int32_t)d);"]
            return [f"d = {d}; if (d == 0) {{ L->failed = 1; return 0; }} "
                    f"u = ((uint64_t)edx << 32) | eax; "
                    f"if (u / d > 0xffffffffu) {{ L->failed = 1; return 0; }} "
                    f"eax = (uint32_t)(u / d); edx = (uint32_t)(u % d);"]
        if mn == "cwde":
            return ["eax = (uint32_t)(int32_t)(int16_t)(eax & 0xffffu);"]
        if mn == "mul":
            return [f"d = {self.read(insn, ops[0], 32)}; u = (uint64_t)eax * d; eax = (uint32_t)u; "
                    f"edx = (uint32_t)(u >> 32); CF = OF = edx != 0;"]
        if mn == "cdq":
            return ["edx = (uint32_t)((int32_t)eax >> 31);"]
        if mn in SETCC:
            return [self.write(insn, ops[0], f"({SETCC[mn]}) ? 1u : 0u", 8)]
        if mn == "nop" or mn == "int3":
            return []
        if mn == "call":
            if ops[0].type == X86_OP_IMM:
                target = ops[0].imm
                count = self.callee_arguments(target)
                return [f"eax = vertrix_lift_call(L, {target:#x}, eax, edx, ebx, ecx, esp, {count}); "
                        f"esp += {4 * count}u; if (L->failed) return 0;"]
            if ops[0].type == X86_OP_MEM and ops[0].mem.base and not ops[0].mem.index:
                slot = (ops[0].mem.disp & 0xffffffff) // 4
                return [f"eax = vertrix_lift_virtual(L, eax, {slot}u); if (L->failed) return 0;"]
            raise Unsupported("indirect call")
        if mn == "ret":
            return ["return eax;"]
        if mn == "jmp":
            if ops[0].type != X86_OP_IMM:
                raise Unsupported("indirect jmp")
            return [f"goto L_{ops[0].imm:x};"]
        if mn in JCC:
            return [f"if ({JCC[mn]}) goto L_{ops[0].imm:x};"]
        raise Unsupported(mn)

    def lift(self, start):
        instructions = {}
        work = [start]
        targets = set()
        while work:
            address = work.pop()
            while address not in instructions:
                insn = self.decode(address)
                instructions[address] = insn
                if insn.mnemonic == "ret":
                    break
                if insn.mnemonic == "jmp":
                    if insn.operands[0].type != X86_OP_IMM:
                        raise Unsupported("indirect jmp")
                    targets.add(insn.operands[0].imm)
                    work.append(insn.operands[0].imm)
                    break
                if insn.mnemonic in JCC:
                    targets.add(insn.operands[0].imm)
                    work.append(insn.operands[0].imm)
                address += insn.size
        lines = []
        order = sorted(instructions)
        for index, address in enumerate(order):
            insn = instructions[address]
            if address in targets:
                lines.append(f"L_{address:x}:;")
            lines.append(f"    /* {address:x}: {insn.mnemonic} {insn.op_str} */")
            for statement in self.translate(insn, targets, None):
                if re.fullmatch(r"(\w+) = \(?\1\)?;", statement):
                    continue
                lines.append("    " + statement)
            if insn.mnemonic not in ("ret", "jmp"):
                following = address + insn.size
                if following not in instructions:
                    raise Unsupported(f"falls off the end at {address:#x}")
                if index + 1 >= len(order) or order[index + 1] != following:
                    lines.append(f"    goto L_{following:x};")
                    targets.add(following)
        # labels may have been added after emission: re-run once so every goto has its label
        body = []
        for line in lines:
            body.append(line)
        text = "\n".join(body)
        for target in sorted(targets):
            if f"L_{target:x}:;" not in text:
                head = f"    /* {target:x}:"
                text = text.replace(head, f"L_{target:x}:;\n{head}", 1)
        return text


FUNCTION = """uint32_t vertrix_lift_{address:06x}(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx,
                              uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                              uint32_t esp)
{{
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t r;
    uint32_t t;
    uint64_t u;
    int64_t p;
    int32_t s;
    unsigned ZF = 0;
    unsigned SF = 0;
    unsigned CF = 0;
    unsigned OF = 0;
    unsigned PF = 0;
    (void)a; (void)b; (void)c; (void)d; (void)r; (void)t; (void)u; (void)p; (void)s;
    (void)ZF; (void)SF; (void)CF; (void)OF; (void)PF; (void)esi; (void)edi; (void)ebp;
    (void)L; (void)eax; (void)edx; (void)ebx; (void)ecx; (void)esp;
{body}
}}
"""


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("executable", type=Path)
    parser.add_argument("addresses", nargs="+")
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    lifter = Lifter(Original(args.executable))
    chunks, lifted, refused = [], [], {}
    for address in sorted({int(text, 16) for text in args.addresses}):
        try:
            body = lifter.lift(address)
        except Unsupported as error:
            refused[f"{address:#x}"] = str(error)
            continue
        chunks.append(FUNCTION.format(address=address, body=body))
        lifted.append(address)
    header = ('/* Generated by tools/lift.py from Vertrix2.exe: do not edit. Each routine is a\n'
              ' * statement-for-statement translation of the original x86 code and is only kept when\n'
              ' * tools/verify_lifted.py reproduces the original on it. */\n'
              '#include "lifted_runtime.h"\n\n')
    table = ("typedef uint32_t (*VertrixLiftFunction)(LiftContext *, uint32_t, uint32_t, uint32_t,\n"
             "                                       uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);\n\n"
             "static const struct\n{\n    uint32_t address;\n    VertrixLiftFunction function;\n}\n"
             "routines[] = {\n" + "".join(f"    {{0x{a:06x}, vertrix_lift_{a:06x}}},\n" for a in lifted) +
             "};\n\n"
             "uint32_t vertrix_lift_count(void)\n{\n    return (uint32_t)(sizeof(routines) / sizeof(routines[0]));\n}\n\n"
             "VertrixLiftFunction vertrix_lift_find(uint32_t address)\n{\n"
             "    uint32_t low = 0;\n    uint32_t high = vertrix_lift_count();\n"
             "    while (low < high)\n    {\n        uint32_t middle = (low + high) / 2;\n"
             "        if (routines[middle].address == address)\n        {\n            return routines[middle].function;\n        }\n"
             "        if (routines[middle].address < address)\n        {\n            low = middle + 1;\n        }\n"
             "        else\n        {\n            high = middle;\n        }\n    }\n    return NULL;\n}\n")
    args.output.write_text(header + "\n".join(chunks) + "\n" + table)
    declarations = "\n".join(
        f"uint32_t vertrix_lift_{a:06x}(LiftContext *L, uint32_t eax, uint32_t edx, uint32_t ebx,"
        f" uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp, uint32_t esp);" for a in lifted)
    args.output.with_suffix(".h").write_text(
        "#ifndef VERTRIX_BONUS_LIFTED_H\n#define VERTRIX_BONUS_LIFTED_H\n"
        '#include "lifted_runtime.h"\n\n'
        "typedef uint32_t (*VertrixLiftFunction)(LiftContext *, uint32_t, uint32_t, uint32_t,\n"
        "                                       uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);\n\n"
        "/* Number of lifted routines and the lifted routine for an original address (NULL when there\n"
        " * is none). Arguments: context, eax, edx, ebx, ecx, esi, edi, ebp, esp. */\n"
        "uint32_t vertrix_lift_count(void);\nVertrixLiftFunction vertrix_lift_find(uint32_t address);\n\n"
        + declarations + "\n#endif\n")
    print(f"lifted {len(lifted)}, refused {len(refused)}")
    if args.report:
        import json
        args.report.write_text(json.dumps({"lifted": [hex(a) for a in lifted],
                                           "refused": refused}, indent=1))


if __name__ == "__main__":
    main()
