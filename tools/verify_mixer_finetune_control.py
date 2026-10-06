""
    "Compare complete original extended finetune control."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD class State(ctypes.Structure)
    : _fields_ =
          [
              ("finetune", ctypes.c_int32), ("output", ctypes.c_uint32), ("flags", ctypes.c_uint8)
          ] def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument("executable",
                                                                                  type = Path);
parser.add_argument("--build-dir", type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      "source";
library = build / "finetune.dylib" subprocess.run(
                      [
                          "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
                          str(source / "mixer.c"), "-o", str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
native.vertrix_mixer_finetune_control.argtypes = [
    ctypes.c_uint8, ctypes.c_int32, ctypes.c_uint8, ctypes.c_int32, ctypes.c_int,
    ctypes.POINTER(State)
] original = Original(args.executable);
rng = random.Random(0x40d62d);cases=30000
    for index in range(cases):
        parameter=0x50|(index%16);tick=0 if index%2==0 else rng.randrange(-2147483648,2147483648)
        linear=(index//2)%2;data=bytearray(rng.randbytes(128));data[4]=parameter
        note=data[7];relative=struct.unpack_from("<i",data,12)[0]
        if index<10000:
            relative=rng.randrange(-96,97)
            struct.pack_into("<i",data,12,relative)
        state=State(struct.unpack_from("<i",data,8)[0],struct.unpack_from("<I",data,40)[0],data[1])
        original.cpu.mem_write(BOARD,bytes(data));original.cpu.mem_write(0x531B4C,struct.pack("<i",tick));original.cpu.mem_write(0x531B46,bytes([linear]));original.call(0x40D540,eax=BOARD)
        expected=bytes(original.cpu.mem_read(BOARD,128))
        assert native.vertrix_mixer_finetune_control(parameter,tick,note,relative,linear,ctypes.byref(state))
        actual=bytearray(data);actual[1]=state.flags;struct.pack_into("<i",actual,8,state.finetune);struct.pack_into("<I",actual,40,state.output)
        assert bytes(actual)==expected,index
    before=bytes(state)
    assert not native.vertrix_mixer_finetune_control(0x40,0,48,0,1,ctypes.byref(state)) and bytes(state)==before
    assert not native.vertrix_mixer_finetune_control(0x50,0,48,0,1,None)
    report={"status":"passed","effect_cases":cases,"scope":"Full original 0x40d540 selecting finetune case 5: all low nibbles, both tuning modes, zero/nonzero signed ticks, full-width relative notes and prior state. Whole channel preservation checked. Excludes instrument reset and full sequencing."}
    (build/"mixer-finetune-control-verification.json").write_text(json.dumps(report,indent=2)+"\n");print(json.dumps(report,indent=2))
if __name__=="__main__":main()
