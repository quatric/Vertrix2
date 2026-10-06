"""Verify original renderer flag-rule and kernel-address selection."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_EDX

class Traversal(ctypes.Structure):
    _fields_ = [('row', ctypes.c_uint32), ('image', ctypes.c_uint32)]

class FlagState(ctypes.Structure):
    _fields_ = [(name,ctypes.c_uint8) for name in ("flag_73a","flag_739","effect_00d",
        "amount_00e","format_000","format_730","transform_00c")] + [("word_002",ctypes.c_uint16)]

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable",type=Path)
    parser.add_argument("--build-dir",type=Path,required=True)
    args=parser.parse_args()
    args.build_dir.mkdir(parents=True,exist_ok=True)
    root=Path(__file__).resolve().parents[1]
    library=args.build_dir.resolve()/"render-dispatch.dylib"
    subprocess.run(["rtk","proxy","cc","-shared","-fPIC","-O2","-Wall","-Wextra","-Werror",
                    str(root/"source/render_dispatch.c"),str(root/"source/surface.c"),"-o",str(library)],check=True)
    native=ctypes.CDLL(str(library))
    native.vertrix_render_rule.argtypes=[ctypes.c_uint32]
    native.vertrix_render_rule.restype=ctypes.c_uint32
    native.vertrix_render_kernel_address.argtypes=[ctypes.c_uint32,ctypes.c_uint8]
    native.vertrix_render_kernel_address.restype=ctypes.c_uint32
    native.vertrix_render_flags.argtypes=[FlagState,ctypes.c_uint32]
    native.vertrix_render_flags.restype=ctypes.c_uint32
    native.vertrix_render_traversal_flags.argtypes=[ctypes.c_uint8]*3
    native.vertrix_render_traversal_index.argtypes=[ctypes.c_uint32]
    native.vertrix_render_traversal_group.argtypes=[ctypes.c_uint32]
    native.vertrix_render_pixels_enabled.argtypes=[ctypes.c_uint32,ctypes.c_uint8,FlagState]
    native.vertrix_render_traversal.argtypes=[ctypes.c_uint8]*4+[ctypes.POINTER(Traversal)]
    oracle=Original(args.executable)
    rules=list(struct.iter_unpack("<II",oracle.cpu.mem_read(0x4FED44,92*8)))
    rng=random.Random(0x4AF2A0)
    flags=[required | (allowed & rng.randrange(2**32)) for required,allowed in rules for _ in range(100)]
    flags += [rng.randrange(2**32) for _ in range(10000)]
    selected=set()
    for value in flags:
        expected=oracle.call(0x4AF2A0,edx=value)
        assert native.vertrix_render_rule(value)==expected
        selected.add(expected)
        for format_byte in (0,1,2,4,3,255):
            row={0:3,1:2,2:1}.get(format_byte,0)
            oracle.call(0x4B1FDE,eax=expected,ecx=row,stop=0x4B2006 if expected<92 else 0x4B2017)
            address=struct.unpack("<I",oracle.cpu.mem_read(0x5BB72C,4))[0]
            assert native.vertrix_render_kernel_address(value,format_byte)==address
    flag_states = 30000
    for index in range(flag_states):
        values=[rng.choice((0,1,2,255)),rng.choice((0,1,2,255)),rng.choice(tuple(range(12))+(127,255)),
                rng.choice((0,49,50,51,100,255)),rng.randrange(16),rng.randrange(16),
                rng.choice((0,1,2,3,255)),rng.choice((0,1,32768,65535))]
        state=FlagState(*values)
        mode=rng.choice((0,1,2,255,0xffffffff))
        for address,value in zip((0x5BB73A,0x5BB739,0x5BC00D,0x5BC00E,0x5BC000,0x5BB730,0x5BC00C),values):
            oracle.cpu.mem_write(address,bytes([value]))
        oracle.cpu.mem_write(0x5BC002,struct.pack("<H",values[-1]))
        expected=oracle.call(0x4AF370,edx=mode)
        assert native.vertrix_render_flags(state,mode)==expected,(values,mode,expected)
        assert oracle.cpu.mem_read(0x5BC00D,2)==bytes(values[2:4])
        assert native.vertrix_render_rule(expected)==oracle.call(0x4AF2A0,edx=expected)
    traversal_cases=20000
    for index in range(traversal_cases):
        a,b,c=rng.choice((0,1,2,255)),rng.choice((0,1,15,16,17,255)),rng.choice((0,1,2,255))
        for address,value in ((0x5BBFFF,a),(0x5BB738,b),(0x5BBFF0,c)):
            oracle.cpu.mem_write(address,bytes([value]))
        expected=oracle.call(0x4AF530)
        assert native.vertrix_render_traversal_flags(a,b,c)==expected
        assert native.vertrix_render_traversal_index(expected)==oracle.call(0x4AF2E0,edx=expected)
        assert native.vertrix_render_traversal_group(expected&12)==oracle.call(0x4AF340,edx=expected&12)
        value=rng.choice(tuple(range(20))+(rng.randrange(2**32),))
        assert native.vertrix_render_traversal_index(value)==oracle.call(0x4AF2E0,edx=value)
        assert native.vertrix_render_traversal_group(value)==oracle.call(0x4AF340,edx=value)
        format_index=index%4
        target_format=(4,2,1,0)[format_index]
        oracle.cpu.reg_write(UC_X86_REG_EBP,0x708800)
        oracle.cpu.mem_write(0x5bb72c,struct.pack('<I',1))
        oracle.call(0x4af707,ecx=format_index,stop=0x4af77d)
        selected_traversal=Traversal()
        assert native.vertrix_render_traversal(a,b,c,target_format,
            ctypes.byref(selected_traversal))==1
        assert selected_traversal.row==oracle.cpu.reg_read(UC_X86_REG_EBX)
        assert selected_traversal.image==oracle.cpu.reg_read(UC_X86_REG_EDX)
        before=bytes(selected_traversal)
        assert native.vertrix_render_traversal(a,b,c,3,ctypes.byref(selected_traversal))==0
        assert bytes(selected_traversal)==before
    gate_cases=10000
    for _ in range(gate_cases):
        values=[rng.choice((0,1,2,255)),rng.choice((0,1,2,255)),rng.randrange(256),
                rng.choice((0,1,50,255)),rng.choice((0,1,13)),rng.choice((0,1,13)),
                rng.randrange(256),rng.choice((0,1,65535))]
        resource,scale=rng.choice((0,1,0xffffffff)),rng.choice((0,1,16,255))
        expected=oracle.render_pixels_enabled(resource,scale,values)
        assert bool(native.vertrix_render_pixels_enabled(resource,scale,FlagState(*values)))==expected
    report={"pixel_gate_cases_verified":gate_cases,"traversal_state_cases_verified":traversal_cases,"flag_state_cases_verified":flag_states,"status":"passed","flag_cases_verified":len(flags),"kernel_selections_verified":len(flags)*6,
            "selected_rule_indices":sorted(selected),
            "scope":"Original 0x4af2a0 executes unchanged. Address lookup phase 0x4b1fde executes through 0x4b2006 or unmatched-rule endpoint 0x4b2017. Flag construction 0x4af370 also executes unchanged, followed by original rule matching. Traversal helpers 0x4af530, 0x4af2e0 and 0x4af340 execute unchanged. Drawing kernel bodies remain separate."}
    report['scope']+= ' Traversal binding 0x4af707..0x4af77d executes unchanged across all four target formats; drawing bodies and actor dispatch remain separate.'
    report['traversal_binding_cases_verified']=traversal_cases
    report['invalid_traversal_binding_cases_verified']=traversal_cases
    (args.build_dir/"render-dispatch-verification.json").write_text(json.dumps(report,indent=2)+"\n")
    print(json.dumps({
k:v for k,v in report.items() if k!='selected_rule_indices'},indent=2))

if __name__=="__main__":
    main()
