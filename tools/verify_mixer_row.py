""
    "Verify complete original row initialization, including cross-instrument samples."
    "" import argparse,
    ctypes, json, random, struct, subprocess from pathlib import Path from original import Original,
    BOARD, MASK, BLOCKS from verify_mixer_sample_selection import Pitch,
    State as Selection from verify_mixer_trigger_reset import State as Reset, NAMES, OFFSETS,
    BYTES from verify_mixer_timed_trigger import Instrument as Trigger
        from verify_mixer_row_instrument import Instrument,
    Defaults

    class View(ctypes.Structure)
    : _fields_ =
          [
              ('trigger', Trigger), ('volumes', ctypes.POINTER(ctypes.c_uint8)),
              ('pans', ctypes.POINTER(ctypes.c_uint8))
          ] class State(ctypes.Structure)
    : _fields_ =
          [
              ('instrument', Instrument), ('owner', ctypes.c_uint32), ('selection', Selection),
              ('reset', Reset), ('defaults', Defaults), ('parameter', ctypes.c_uint8)
          ]

      def main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument('executable',
                                                                                  type = Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source';
library = build / 'row.dylib' subprocess.run(
                      [
                          'cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC',
                          str(source / 'mixer.c'), '-o', str(library)
                      ],
                      check = True) native = ctypes.CDLL(str(library));
function = native.vertrix_mixer_row function.argtypes = [
    ctypes.POINTER(ctypes.c_uint8), ctypes.c_int, ctypes.c_uint8, ctypes.POINTER(View),
    ctypes.c_uint16, ctypes.POINTER(State)
] original = Original(args.executable);
rng = random.Random(0x40e770);
cases = 20000; instrument_base = 0x808000
    for index in range(cases):
        data = bytearray(rng.randbytes(192));
views = (View * 2)(); keep = []
        for owner in range(2):
            descriptor = bytearray(rng.randbytes(252)); samples = rng.randbytes(16 * 60)
            mapping = (ctypes.c_uint8 * 96)(*[rng.randrange(21) for _ in range(96)])
            pitches = (Pitch * 16)(*[Pitch(*struct.unpack_from('<bb',samples,i * 60 + 34)) for i in range(16)])
            volumes = (ctypes.c_uint8 * 16)(*[samples[i * 60 + 32] for i in range(16)])
            pans = (ctypes.c_uint8 * 16)(*[samples[i * 60 + 33] for i in range(16)])
            descriptor[32:128] = bytes(mapping);
struct.pack_into('<H', descriptor, 128, 16) struct.pack_into('<I', descriptor, 248,
                                                             BLOCKS + owner * 960) views[owner] =
    View(Trigger(mapping, pitches, 16, struct.unpack_from('<H', descriptor, 134)[0],
                 descriptor[188], descriptor[244], descriptor[131], descriptor[132]),
         volumes, pans) keep.extend((mapping, pitches, volumes,
                                     pans)) original.cpu.mem_write(instrument_base + owner * 252,
                                                                   bytes(descriptor));
original.cpu.mem_write(BLOCKS + owner * 960, samples) selected = index % 3;
owner = 0 if index % 7 == 0 else rng.randrange(1, 3); sample = rng.randrange(16) if owner else 0xffffffff
        struct.pack_into('<I',data,52,0 if selected == 0 else instrument_base + (selected - 1) * 252)
        struct.pack_into('<I',data,56,0 if owner == 0 else BLOCKS + (owner - 1) * 960 + sample * 60)
        event = (ctypes.c_uint8 * 5)(index % 256,rng.randrange(5),rng.randrange(256),(0,3,4,5,6,rng.randrange(256))[index % 6],rng.randrange(256))
        linear,module = index % 2,rng.randrange(256)
        selection = Selection(sample,struct.unpack_from('<i',data,12)[0],struct.unpack_from('<i',data,8)[0],*struct.unpack_from('<II',data,36),data[7],data[0],data[6],data[3],data[2],data[1])
        reset = Reset(*[struct.unpack_from('<I',data,o)[0] for o in OFFSETS],*[data[o] for o in BYTES])
        state = State(Instrument(selected,data[5]),owner,selection,reset,Defaults(*struct.unpack_from('<II',data,16),struct.unpack_from('<I',data,28)[0],data[1]),data[4])
        original.cpu.mem_write(BOARD,bytes(data));
original.cpu.mem_write(MASK + 42, struct.pack('<H', 2));
original.cpu.mem_write(MASK + 340, struct.pack('<I', instrument_base)) original.cpu.mem_write(
    0x53043c, struct.pack('<I', MASK));
original.cpu.mem_write(0x531b46, bytes([linear]));
original.cpu.mem_write(0x531b47,
                       bytes([module])) original.cpu.mem_write(0x809000,
                                                               bytes([0x9f]) + bytes(event));
original.cpu.mem_write(0x530440, struct.pack('<I', 0x809000)) original.call(0x40e770,
                                                                            eax = BOARD) assert
    function(event, linear, module, views, 2, ctypes.byref(state)),
    index actual = bytearray(data);
sel = state.selection actual [0:8] =
    bytes((sel.active, sel.flags, sel.volume, sel.effect, state.parameter, state.instrument.number,
           sel.mapping, sel.note)) struct.pack_into('<ii', actual, 8, sel.finetune, sel.relative);
struct.pack_into('<II', actual, 36, sel.base, sel.output) struct
    .pack_into('<I', actual, 52,
               0 if state.instrument.selected ==
                   0 else instrument_base + (state.instrument.selected - 1) * 252) struct
    .pack_into('<I', actual, 56,
               0 if sel.selected == 0xffffffff else BLOCKS + (state.owner - 1) * 960 +
                                        sel.selected * 60) struct.pack_into('<II', actual, 16,
                                                                            state.defaults.base,
                                                                            state.defaults.output); struct.pack_into('<I',actual,28,state.defaults.pan)
        for name,offset in zip(NAMES,OFFSETS): struct.pack_into('<I',actual,offset,getattr(state.reset,name))
        for name,offset in zip(('waveform','state_112','state_114','state_115'),BYTES): actual[offset] = getattr(state.reset,name)
        assert bytes(actual) == bytes(original.cpu.mem_read(BOARD,192)),index
    before = bytes(state);
state.instrument.selected = 3;
invalid_before = bytes(state) assert not function(event, 0, 0, None, 2, ctypes.byref(state)) and
                 bytes(state) ==
                     invalid_before assert not function(None, 0, 0, views, 2, ctypes.byref(state))
                         report = {
    'status' : 'passed',
    'complete_row_cases' : cases,
    'scope' :
        'Complete original 0x40e770 including packed decode, effect transition, instrument selection, note selection/release, reset and sample defaults. Whole 192-byte channels, translated instrument/sample handles, cross-instrument sample retention, invalid notes/mappings and module flags. Excludes effect dispatch and row scheduling.'
}(build / 'mixer-row-verification.json')
                                      .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
