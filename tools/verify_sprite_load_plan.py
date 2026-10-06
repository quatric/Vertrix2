"""Compare startup filename selections with complete original45dca0 control flow."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_wii_platform_check import resource
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EIP, UC_X86_REG_ESP


class Entry(c.Structure):
    _fields_ = [('token', c.c_uint32), ('slot', c.c_uint8), ('filename', c.c_char * 256)]


class Plan(c.Structure):
    _fields_ = [('entries', Entry * 20)]


class Selection(c.Structure):
    _fields_ = [('settings', c.c_uint8 * 19), ('interface_slot', c.c_uint8), ('first_source', c.c_uint32), ('artwork_source', c.c_uint32), ('border_source', c.c_uint32)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build / 'sprite-load-plan.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(root / 'source' / n) for n in ('sprite_load_plan.c', 'sprite_files.c', 'vf.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_sprite_load_plan.argtypes = [c.c_void_p, c.POINTER(c.c_uint8), c.c_uint8, c.POINTER(Plan)]
    table = resource(args.archive.read_bytes(), b'texte/spritefilename.ini')
    names = [line.split(b'\\')[0] for line in table.splitlines() if line and not line.startswith(b'/')]
    names += [b''] * (23 - len(names))
    original = Original(args.executable)
    cpu = original.cpu
    pointers = []
    for i, name in enumerate(names):
        address = 0x804000 + i * 256
        cpu.mem_write(address, name + b'\0')
        pointers.append(address)
    cpu.mem_write(0x533650, struct.pack('<23I', * pointers))
    recorded = []
    def boundary(cpu, address, size, unused):
        if address == 0x4873d0:
            token = cpu.reg_read(UC_X86_REG_EAX)
            pointer = cpu.reg_read(UC_X86_REG_EDX)
            filename = bytes(cpu.mem_read(pointer, 256)).split(b'\0')[0]
            recorded.append((token, filename))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
#Only filename / control - flow recovery : supply resource side - effect boundaries.
    addresses = (0x4873d0, 0x418270, 0x487790, 0x4877d0, 0x45ec00, 0x45e400, 0x45eac0, 0x45e3c0, 0x45e490, 0x45e530)
    hooks = [cpu.hook_add(UC_HOOK_CODE, boundary, begin=a, end=a) for a in addresses]
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    rng = random.Random(0x45dca0)
    defaults = bytes(cpu.mem_read(0x513c4d, 19))
    initial_interface = bytes(cpu.mem_read(0x53bd09, 1))[0]
    native.vertrix_sprite_selection_init.argtypes = [c.POINTER(Selection)]
    selection = Selection()
    assert native.vertrix_sprite_selection_init(c.byref(selection))
    assert bytes(selection.settings) == defaults
    assert selection.interface_slot == initial_interface == 0
    assert selection.first_source == struct.unpack('<I', cpu.mem_read(0x5466c4, 4))[0] == 0
    assert selection.artwork_source == struct.unpack('<I', cpu.mem_read(0x4fbfac, 4))[0] == 34
    assert selection.border_source == struct.unpack('<I', cpu.mem_read(0x4fbf74, 4))[0] == 20
    assert not native.vertrix_sprite_selection_init(None)
    default_plan = []
    for case in range(512):
        selections = defaults if case == 0 else bytes(rng.randrange(23) for _ in range(19))
        interface = initial_interface if case == 0 else rng.randrange(23)
        cpu.mem_write(0x513c4d, selections)
        cpu.mem_write(0x53bd09, bytes([interface]))
        recorded.clear()
        original.call(0x45dca0)
        settings = (c.c_uint8 * 19).from_buffer_copy(selections)
        plan = Plan()
        assert native.vertrix_sprite_load_plan(archive, settings, interface, c.byref(plan))
        assert len(recorded) == 20
        assert [(e.token, bytes(e.filename)) for e in plan.entries] == recorded
        for entry in plan.entries:
            assert bytes(entry.filename) == b'.\\SPRITE\\' + names[entry.slot]
            if case == 0:
                default_plan = [{'token': hex(e.token), 'slot': e.slot, 'filename': bytes(e.filename).decode('ascii')} for e in plan.entries]
        before = bytes(plan)
        assert not native.vertrix_sprite_load_plan(archive, settings, 23, c.byref(plan))
        assert bytes(plan) == before
        settings[rng.randrange(19)] = 255
        assert not native.vertrix_sprite_load_plan(archive, settings, interface, c.byref(plan))
        assert bytes(plan) == before
    for hook in hooks:
        cpu.hook_del(hook)
    native.vertrix_vf_close(archive)
    report = {'status': 'passed', 'original_startup_selection_cases': 512, 'load_entries_compared': 10240, 'invalid_preservation_cases': 1024, 'loader_initial_selection_verified': True, 'initial_image_settings_plan': default_plan, 'scope': 'Complete original45dca0 control flow and actual45f540 path building. ' 'Hooks supply sprite load, progress, mirror/clone and derived-resource ' 'boundaries; they do not validate resource side effects. VF table is ' 'independently parsed and supplied to original pointer table. Settings ' 'are explicit, including initial EXE bytes, not post-configuration startup.'}
    (build / 'sprite-load-plan-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({k: v for k, v in report.items() if k != 'initial_image_settings_plan'}, indent=2))
if __name__ == '__main__':
    main()
