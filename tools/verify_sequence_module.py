""
    "Verify owned complete music modules loaded directly from original VF."
    "" import argparse,
    ctypes, json, struct,
    subprocess from pathlib import Path from verify_sequence_tick import Song from
        verify_sequence_process import RuntimeInstrument from verify_mixer_attach import Binding
            from verify_xm_samples import decode

                def
                main()
    : parser = argparse.ArgumentParser(description = __doc__) parser.add_argument('archive',
                                                                                  type = Path);
parser.add_argument('music', type = Path);
parser.add_argument('--build-dir', type = Path, required = True) args = parser.parse_args();
build = args.build_dir.resolve();
build.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                      'source'; library = build / 'module.dylib'
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/n) for n in ('sequencer.c','mixer.c','xm.c','vf.c','audio.c')],'-o',str(library)],check=True)
    native = ctypes.CDLL(str(library));
native.vertrix_vf_open.argtypes = [ctypes.c_char_p];
native.vertrix_vf_open.restype = ctypes.c_void_p;
native.vertrix_vf_close.argtypes = [ctypes.c_void_p] native.vertrix_sequence_module_load.argtypes =
    [ ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint8, ctypes.c_void_p ];
native.vertrix_sequence_module_load.restype =
    ctypes.c_void_p native.vertrix_sequence_module_free.argtypes =
        [ctypes.c_void_p] native.vertrix_sequence_module_song.argtypes = [ctypes.c_void_p];
native.vertrix_sequence_module_song.restype =
    ctypes.POINTER(Song) native.vertrix_sequence_module_bindings.argtypes =
        [ ctypes.c_void_p, ctypes.POINTER(ctypes.c_size_t) ]; native.vertrix_sequence_module_bindings.restype = ctypes.POINTER(Binding)
    modules = patterns_checked = instruments_checked = samples_checked = pcm_bytes = 0
    for path in sorted(args.music.glob('*.xm')):
        vf = native.vertrix_vf_open(str(args.archive.resolve()).encode());
assert vf
try : module
    = native.vertrix_sequence_module_load(vf, ('musique/' + path.name).encode(), 0x80, None);
assert module, path.name assert not native
                   .vertrix_sequence_module_load(vf, b 'musique/missing.xm', 0, None) finally
    : native.vertrix_vf_close(vf)
try : song
    = native.vertrix_sequence_module_song(module).contents;
data = path.read_bytes() length, restart, channels, patterns, instruments,
    flags = struct.unpack_from('<6H', data, 64)
                assert(song.length, song.restart, song.pattern_count, song.instrument_count,
                       song.linear, song.module_flags) ==
            (length, restart, patterns, instruments, bool(flags & 1),
             0x80) assert ctypes.string_at(song.orders,
                                           256) == data [80:336] count = ctypes.c_size_t();
bindings = native.vertrix_sequence_module_bindings(module, ctypes.byref(count));
runtime = ctypes.cast(song.instruments, ctypes.POINTER(RuntimeInstrument)) offset =
    60 + struct.unpack_from('<I', data, 60)[0]; first = 0
            for index in range(patterns):
                header_size = struct.unpack_from('<I',data,offset)[0];
rows, packed = struct.unpack_from('<HH', data, offset + 5);
offset += header_size view = song.patterns[index];
assert(view.channels, view.rows, view.size) ==
    (channels, rows,
     packed)assert(ctypes.string_at(view.packed,
                                    packed) if packed else b'') == data [offset:offset + packed];
offset += packed; patterns_checked += 1
            for index in range(instruments):
                header_size = struct.unpack_from('<I',data,offset)[0];
samples = struct.unpack_from('<H', data, offset + 27)[0];
sample_header_size = struct.unpack_from('<I', data, offset + 29)[0] if samples else 0 view =
    runtime[index];
assert view.first_sample == first and view.trigger.count ==
    samples assert ctypes.string_at(view.trigger.mapping, 96) ==
    ctypes.string_at(song.row_instruments[index].trigger.mapping, 96) offset += header_size; payload = offset+samples*sample_header_size
                for sample in range(samples):
                    h = data[offset+sample*sample_header_size:offset+sample*sample_header_size+40];
size, start, loop = struct.unpack_from('<III', h);
binding = bindings[first] expected =
    bytearray(decode(data [payload:payload + size], h[14] & 16)) + bytes(4);
payload +=
    size sample_flags = (1 if h[14] & 16 else 0) | (16 if h[14] & 1 else 0) |
                        (32 if h[14] & 2 else 0) assert(binding.count, binding.start, binding.end,
                                                        binding.flags) ==
                                (size, start, (start + loop) & 0xffffffff, sample_flags) if size
    : if sample_flags & 16 : expected [start + loop:start + loop + 4] =
expected [start:start + 4] assert ctypes.string_at(binding.samples, size + 4) ==
    bytes(expected) else : assert not binding.samples assert view.trigger.samples[sample].relative
    == int.from_bytes(h [16:17], 'little', signed = True) and
    view.trigger.samples[sample].finetune ==
        int.from_bytes(h [13:14], 'little', signed = True) assert song.row_instruments[index]
            .volumes[sample] == h[12] and
    song.row_instruments[index].pans[sample] == h[15] first += 1;
samples_checked += 1;
pcm_bytes += size offset = payload;
instruments_checked += 1 assert count.value == first;
modules += 1 finally : native.vertrix_sequence_module_free(module)
                           native.vertrix_sequence_module_free(None);
assert not native.vertrix_sequence_module_song(None)
    report = {
    'status' : 'passed',
    'modules' : modules,
    'patterns' : patterns_checked,
    'instruments' : instruments_checked,
    'samples' : samples_checked,
    'pcm_bytes' : pcm_bytes,
    'scope' :
        'Complete original VF modules remain readable after archive closure. Original packed bytes, owned PCM including interpolation guards, song/order data, tuning/defaults, stable instrument views and flat sample binding offsets match independent source parsing. Missing-resource/null cleanup checked. Underlying decoders have separate original-executable proofs. Excludes music ticks and audio delivery.'
}(build / 'sequence-module-verification.json')
                 .write_text(json.dumps(report, indent = 2) + '\n');
print(json.dumps(report, indent = 2)) if __name__ == '__main__' : main()
