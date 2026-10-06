"""Compare recovered song-start state with original mixer allocation calls captured."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, MASK
from verify_sequence_tick import Sequence, Global, Row, Column, Memory, Extended, Playback, Publication, Reader, reconstruct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
class Header(ctypes.Structure):
    _fields_ = [('name',ctypes.c_char*21)] + [(n,ctypes.c_uint16) for n in ('length','restart','channels','patterns','instruments','flags','speed','bpm')] + [('orders',ctypes.c_uint8*256)]
def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable',type=Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source'; library = build / 'start.dylib'
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/n) for n in ('sequencer.c','mixer.c','xm.c','vf.c','audio.c')],'-o',str(library)],check=True)
    native = ctypes.CDLL(str(library));
function = native.vertrix_sequence_start function.argtypes = [
    ctypes.POINTER(Header), ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(Sequence),
    ctypes.POINTER(Global), ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(Reader),
    ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory), ctypes.POINTER(Extended),
    ctypes.POINTER(Playback), ctypes.c_size_t, ctypes.POINTER(Publication),
    ctypes.POINTER(ctypes.c_uint32)
] original = Original(args.executable);
rng = random.Random(0x40ec40);
events = [];
slots = [] addresses =
    (0x40acf0, 0x40ae10, 0x40ac20, 0x40ac10)def capture(cpu, address, size, context)
    : value = cpu.reg_read(UC_X86_REG_EAX) if address == 0x40acf0 : slots.append(value);
cpu.mem_write(value, struct.pack('<I', len(slots))) elif address ==
    0x40ae10 : events.append(('pan', value, cpu.reg_read(UC_X86_REG_EDX))) elif address ==
    0x40ac20 : events.append(('tempo', value)) else
    : events.append(('register', value)) stack = cpu.reg_read(UC_X86_REG_ESP);
target = struct.unpack('<I', cpu.mem_read(stack, 4))[0] cpu.reg_write(UC_X86_REG_ESP, stack + 4);
cpu.reg_write(UC_X86_REG_EIP, target); cpu.reg_write(UC_X86_REG_EAX,0)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE,capture,begin=a,end=a) for a in addresses]
    cases = 4000; success = active = invalid = 0
    for index in range(cases):
        header = Header();
header.channels = index % 33;
header.speed = rng.randrange(65536);
header.bpm = rng.randrange(65536);
header.flags = rng.randrange(65536) default_pan = index % 2 == 0; pans = (ctypes.c_uint8*32)(*[127 if default_pan else rng.randrange(256) for _ in range(32)])
        song = bytearray(rng.randbytes(344));
struct.pack_into('<HH', song, 32, header.flags, 0);
struct.pack_into('<H', song, 38, header.channels);
struct.pack_into('<HH', song, 44, header.speed, header.bpm);
song [304:336] = bytes(pans) initial = bytearray(rng.randbytes(0x1744));
initial[0x1708] = index % 256 original.cpu.mem_write(0x53043c, bytes(initial));
original.cpu.mem_write(MASK, bytes(song));
events.clear();
slots.clear() absent = index % 7 == 0;
original.call(0x40ec40, eax = 0 if absent else MASK);
result = original.cpu.reg_read(UC_X86_REG_EAX) sequence =
    Sequence.from_buffer_copy(rng.randbytes(ctypes.sizeof(Sequence)));
sequence.flags = initial[0x1708] global_state =
    Global.from_buffer_copy(rng.randbytes(ctypes.sizeof(Global)));
reader = Reader.from_buffer_copy(rng.randbytes(ctypes.sizeof(Reader)));
delay = ctypes.c_uint32(rng.getrandbits(32));
tempo = ctypes.c_uint32(rng.getrandbits(32)) rows =
    (Row * 32).from_buffer_copy(rng.randbytes(ctypes.sizeof(Row) * 32));
columns = (Column * 32).from_buffer_copy(rng.randbytes(ctypes.sizeof(Column) * 32));
memory = (Memory * 32).from_buffer_copy(rng.randbytes(ctypes.sizeof(Memory) * 32));
extended = (Extended * 32).from_buffer_copy(rng.randbytes(ctypes.sizeof(Extended) * 32));
playback = (Playback * 32).from_buffer_copy(rng.randbytes(ctypes.sizeof(Playback) * 32)); publications = (Publication*32).from_buffer_copy(rng.randbytes(ctypes.sizeof(Publication)*32))
        before = tuple(bytes(x) for x in (sequence,global_state,reader,rows,columns,memory,extended,playback,publications)) + (delay.value,tempo.value)
        assert function(None if absent else ctypes.byref(header),None if default_pan else pans,ctypes.byref(sequence),ctypes.byref(global_state),ctypes.byref(delay),ctypes.byref(reader),rows,columns,memory,extended,playback,32,publications,ctypes.byref(tempo)) == result
        if result:
            assert tuple(bytes(x) for x in (sequence,global_state,reader,rows,columns,memory,extended,playback,publications)) + (delay.value,tempo.value) == before
            assert bytes(initial) == bytes(original.cpu.mem_read(0x53043c,len(initial))) and not events and not slots
            active += result == 3;
invalid += result == 2;
continue success += 1;
expected = bytearray(64);
expected[0] = 0x81;
struct.pack_into('<H', expected, 2, header.flags);
struct.pack_into('<I', expected, 4, header.channels); struct.pack_into('<III',expected,28,header.speed,header.bpm,64)
        assert bytes(expected[:60]) == bytes(original.cpu.mem_read(0x531b44,60))
        assert sequence.flags == global_state.flags == 0x81 and not sequence.tick and not sequence.row and not sequence.order and not sequence.rows and not sequence.pending_order and not sequence.pending_row
        assert (global_state.speed,global_state.tempo,global_state.volume,global_state.memory,delay.value,tempo.value) == (header.speed,header.bpm,64,0,0,header.bpm)
        assert not reader.data and not reader.size and not reader.cursor
        assert events == [('pan',ci+1,pans[ci]) for ci in range(header.channels)] + [('tempo',header.bpm),('register',0x40eb10)]
        for ci in range(header.channels):
            record = bytearray(180);
struct.pack_into('<I', record, 28, pans[ci]); assert bytes(record) == bytes(original.cpu.mem_read(0x530444+ci*180,180)) == reconstruct(bytes(180),rows[ci])
            assert columns[ci].pan == playback[ci].base_pan == pans[ci] and not any(bytes(memory[ci])) and not any(bytes(extended[ci]))
            assert publications[ci].count == 1 and publications[ci].commands[0].kind == 5 and publications[ci].commands[0].value == pans[ci]
    for hook in hooks: original.cpu.hook_del(hook)
    report = {'status':'passed','start_cases':cases,'successful_starts':success,'already_active':active,'missing_song':invalid,
        'scope':'Complete original 0x40ec40 with mixer allocation, pan, tempo and callback registration captured; state clearing executes normally. Zero to 32 channels, arbitrary/default pans, full-width speed/tempo, error precedence and native preservation. Whole active channel and global records match. Excludes real mixer slot allocation and runtime registration/audio.'}
    (build/'sequence-start-verification.json').write_text(json.dumps(report,indent=2)+'\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
