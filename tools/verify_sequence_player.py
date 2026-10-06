"""Compare VF-backed player buffers with the original complete scheduler."""
import argparse, ctypes as c, json, struct, subprocess
from pathlib import Path
from original import Original, MASK, BOARD
from verify_sequence_module_pcm import original_song
from verify_sequence_tick import Sequence, Global, SN, SO
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP

def main():
    p=argparse.ArgumentParser(description=__doc__)
    for name in ('executable','archive','music'):p.add_argument(name,type=Path)
    p.add_argument('--build-dir',type=Path,required=True);
p.add_argument('--buffers', type = int, default = 64) p.add_argument(
    '--encoded', action = 'store_true',
    help = 'Also compare original PCM8/PCM16 output encoding') a = p.parse_args();
a.build_dir.mkdir(parents = True, exist_ok = True) source = Path(__file__).resolve().parents[1] /
                                                            'source';lib=a.build_dir.resolve()/'player.dylib'
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror','-shared','-fPIC',*[str(source/f) for f in ('sequencer.c','mixer.c','xm.c','vf.c','audio.c')],'-o',str(lib)],check=True)
    n=c.CDLL(str(lib))
    n.vertrix_vf_open.argtypes=[c.c_char_p];
n.vertrix_vf_open.restype = c.c_void_p;
n.vertrix_vf_close.argtypes = [c.c_void_p] n.vertrix_sequence_module_load.argtypes =
    [ c.c_void_p, c.c_char_p, c.c_uint8, c.c_void_p ];
n.vertrix_sequence_module_load.restype = c.c_void_p;
n.vertrix_sequence_module_free.argtypes = [c.c_void_p] n.vertrix_sequence_player_create.argtypes =
    [ c.c_void_p, c.c_uint32, c.c_uint32, c.c_int, c.c_int ];
n.vertrix_sequence_player_create.restype = c.c_void_p;
n.vertrix_sequence_player_free.argtypes = [c.c_void_p] n.vertrix_sequence_player_mix.argtypes =
    [ c.c_void_p, c.POINTER(c.c_int32), c.c_size_t,
      c.c_size_t ] n.vertrix_sequence_player_pcm.argtypes =
        [
            c.c_void_p, c.c_size_t, c.c_int, c.POINTER(c.c_int32), c.c_size_t, c.POINTER(c.c_uint8),
            c.c_size_t
        ] n.vertrix_sequence_player_state.argtypes =
            [
                c.c_void_p, c.POINTER(Sequence), c.POINTER(Global), c.POINTER(c.c_uint32),
                c.POINTER(c.c_uint32)
            ] o = Original(a.executable);
o.cpu.mem_map(0x900000, 0x1000000);
o.cpu.mem_map(0x2000000, 0x20000);
o.cpu.mem_map(0x2020000, 0x10000) def write(address, value)
    : o.cpu.mem_write(address, struct.pack('<I', value)) write(0x52f910, 0x2000000);
write(0x52f914, 0x2020000);
write(0x52fc2c, 1) write(0x52f044, 0x40cd30);write(0x52f048,0x40cd40)
    for addr,target in zip(range(0x52f060,0x52f07c,4),(0x40c9d0,0x40ca70,0x40caa0,0x40cad0,0x40cb10,0x40cb70,0x40cbb0)):write(addr,target)
    slots=[]
    def allocate(cpu,address,size,context):
        destination=cpu.reg_read(UC_X86_REG_EAX);
slots.append(destination);
write(destination, len(slots)) stack = cpu.reg_read(UC_X86_REG_ESP);
target = struct.unpack('<I', cpu.mem_read(stack, 4))[0];
cpu.reg_write(UC_X86_REG_ESP, stack + 4);
cpu.reg_write(UC_X86_REG_EIP, target);
cpu.reg_write(UC_X86_REG_EAX, 0) o.cpu.hook_add(UC_HOOK_CODE, allocate, begin = 0x40acf0,
                                                end = 0x40acf0) songs = [];total=0
    for index,path in enumerate(sorted(a.music.glob('*.xm'))):
        vf=n.vertrix_vf_open(str(a.archive.resolve()).encode());
assert vf module = n.vertrix_sequence_module_load(vf, ('musique/' + path.name).encode(), 0, None);
n.vertrix_vf_close(vf);assert module
        stereo=(index//2)%2;interpolate=index%2;rate=(32000,48000)[index%2];master=255
        player=n.vertrix_sequence_player_create(module,rate,master,stereo,interpolate);assert player
        try:
            assert not n.vertrix_sequence_player_create(module,0,master,stereo,interpolate)
            assert not n.vertrix_sequence_player_create(module,rate,257,stereo,interpolate)
            assert n.vertrix_sequence_player_mix(player,None,0,0)
            sentinel=(c.c_int32*2)(123,456)
            assert not n.vertrix_sequence_player_mix(player,sentinel,3,2)
            assert list(sentinel)==[123,456]
            encoded_sentinel=(c.c_uint8*2)(17,19)
            assert not n.vertrix_sequence_player_pcm(player,3,1,sentinel,2,encoded_sentinel,2)
            assert list(sentinel)==[123,456] and list(encoded_sentinel)==[17,19]
            assert n.vertrix_sequence_player_pcm(player,0,1,None,0,None,0)
            original_song(o,path.read_bytes());o.cpu.mem_write(0x52fc1d,bytes([stereo]));o.call(0x40c7d0,eax=1,edx=master)
            kernels=((0x40109c,0x402934),(0x401328,0x402c18)) if not interpolate else ((0x401cd0,0x4036c8),(0x401f9c,0x4039e4))
            write(0x52fc34,kernels[stereo][0]);write(0x52fc38,kernels[stereo][1]);write(0x52fc20,rate);write(0x52fc28,0);write(0x52fc30,0);write(0x52fc18,32)
            o.call(0x40c910);o.cpu.mem_write(0x531b44,bytes(60));slots.clear();o.call(0x40ec40,eax=MASK)
            for buffer in range(a.buffers):
                frames=(1,63,64,65,257,512,1024)[buffer%7];values=frames*(1+stereo);output=(c.c_int32*values)()
                o.cpu.mem_write(BOARD+8192,bytes(values*4));o.call(0x40c5c0,eax=BOARD+8192,edx=values)
                if a.encoded:
                    sixteen=(index//4)%2;encoded=(c.c_uint8*(values*(1+sixteen)))()
                    assert n.vertrix_sequence_player_pcm(player,frames,sixteen,output,values,encoded,len(encoded)),(path.name,buffer,'encoded render')
                    o.call(0x401054 if sixteen else 0x401010,args=(BOARD+32768,BOARD+8192,values))
                    assert bytes(encoded)==bytes(o.cpu.mem_read(BOARD+32768,len(encoded))),(path.name,buffer,'encoded PCM')
                else:
                    assert n.vertrix_sequence_player_mix(player,output,frames,values),(path.name,buffer,'render')
                assert bytes(output)==bytes(o.cpu.mem_read(BOARD+8192,values*4)),(path.name,buffer,'PCM')
                seq=Sequence();glob=Global();period=c.c_uint32();phase=c.c_uint32()
                assert n.vertrix_sequence_player_state(player,c.byref(seq),c.byref(glob),c.byref(period),c.byref(phase))
                raw=o.cpu.mem_read(0x531b44,60)
                for field,offset in zip(SN,SO):assert getattr(seq,field)==struct.unpack_from('<I',raw,offset)[0],(path.name,buffer,field)
                assert seq.flags==raw[0]
                assert (glob.speed,glob.tempo,glob.volume,glob.memory)==struct.unpack_from('<4I',raw,28)
                assert (period.value,phase.value)==struct.unpack('<II',o.cpu.mem_read(0x52fc24,8)),(path.name,buffer,'timing')
                total+=values
            songs.append({'name':path.name,'buffers':a.buffers,'stereo':stereo,'interpolate':interpolate,'rate':rate});print(path.name+' passed',flush=True)
        finally:n.vertrix_sequence_player_free(player);n.vertrix_sequence_module_free(module)
    report={'status':'passed','modules':len(songs),'buffers':len(songs)*a.buffers,'pcm_values':total,'encoded_pcm':a.encoded,'songs':songs,'scope':'Exact original 0x40c5c0 scheduler, real tempo setter and tick callback; VF-backed native player compared across varying buffer sizes. Optional encoding executes original 0x401010/0x401054. Only original mixer slot allocation intercepted. Hardware audio and whole game integration remain unverified.'}
    filename='sequence-player-pcm-verification.json' if a.encoded else 'sequence-player-verification.json'
    (a.build_dir/filename).write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({
k:v for k,v in report.items() if k!='songs'},indent=2))
if __name__=='__main__':main()
