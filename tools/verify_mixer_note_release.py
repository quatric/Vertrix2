"""Compare complete original note-release envelope branches."""
import argparse
import ctypes
import json
import random
import struct
import subprocess
from pathlib import Path

from original import Original, BOARD, MASK
from verify_mixer_volume_slide import State


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / "source"
    library = build / "note-release.dylib"
    subprocess.run(
        [
            "cc", "-std=c11", "-Wall", "-Wextra", "-Werror", "-shared", "-fPIC",
            str(source / "mixer.c"), "-o", str(library)
        ],
        check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_note_release.argtypes = [
        ctypes.c_int, ctypes.c_uint8, ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(State)
    ]
    original = Original(args.executable)
    rng = random.Random(0x40e640)
    cases = 30000
    for index in range(cases):
        present=index%2;envelope=(index//2)%256;data=bytearray(rng.randbytes(128));struct.pack_into("<I",data,52,MASK if present else 0)
        state=State(*struct.unpack_from("<II",data,16),data[104],data[1]);active=ctypes.c_uint8(data[0])
        original.cpu.mem_write(BOARD,bytes(data));original.cpu.mem_write(MASK+188,bytes([envelope]));original.call(0x40E640,eax=BOARD)
        expected=bytes(original.cpu.mem_read(BOARD,128))
        assert native.vertrix_mixer_note_release(present,envelope,ctypes.byref(active),ctypes.byref(state))
        actual=bytearray(data);actual[0]=active.value;actual[1]=state.flags;actual[104]=state.memory;struct.pack_into("<II",actual,16,state.base,state.output)
        assert bytes(actual)==expected,index
    before=bytes(state);prior=active.value
    assert not native.vertrix_mixer_note_release(1,0,None,ctypes.byref(state)) and bytes(state)==before
    assert not native.vertrix_mixer_note_release(1,0,ctypes.byref(active),None) and active.value==prior
    report = {
        "status": "passed",
        "release_cases": cases,
        "scope": "Complete original 0x40e640, instrument present/absent, all envelope flag bytes, arbitrary active/volume/flag state. Whole channel comparison verifies envelope branch behavior and preservation. Excludes envelope advancement and trigger initialization."
    }
    (build / "mixer-note-release-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
