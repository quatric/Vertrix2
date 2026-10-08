"""Compare the original title letter builder 0x4713d0 and 0x4715a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
FRAME = STACK - 4
TEXT = 0x50e61f
GLOBAL = 0x4f9c0a
CALLEES = {0x4ca070: 0, 0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5,
           0x43f420: 0, 0x4ac950: 0, 0x4ac8a0: 0, 0x4ac8f0: 0, 0x4ad510: 0, 0x4826c0: 0,
           0x4ac7d0: 0, 0x4ac510: 0, 0x4b5e70: 0, 0x4ca210: 0, 0x4cdfb0: 3}
GLOBALS = [0x4f8a48, 0x4f8a4c, 0x4f8a50, 0x4f8a54, 0x4f9c02]


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def verify_full_builders(args,native):
    original=Original(args.executable);cpu=original.cpu;rng=random.Random(0x4713d1)
    actors=(0x806000,0x806200);text_base=0x806400;local=FRAME-0x20
    regions=((actors[0],SIZE),(actors[1],SIZE),(text_base,SIZE),(0x4f8a44,24),(0x4f9c02,4),(local,4))
    host={};tokens={};patches={};out_pointer=0;constructed=actors[0]
    original_events=[];native_events=[];errors=[]
    counts={};calls_compared=completed=0
    pointer_replacements=constructor_changes=formatter_calls=0
    def locate(address):
        for base,size in regions:
            if base<=address<base+size:return base,address-base,size
        return None,0,0
    @Resolve
    def resolve(handle,storage,size,context):
        base,offset,extent=locate(handle)
        if base is None:errors.append(('resolve',handle));return 0
        storage[0]=c.addressof(host[base])+offset;size[0]=extent-offset;return 1
    services=Services(resolve)
    def snapshot(read):return tuple(read(base,size) for base,size in regions)
    def mutations(target):
        writes=list(patches[target])
        if target==0x4ca070:writes.append((local,bytes(4)))
        if target==0x4cdfb0:writes.append((local,struct.pack('<I',out_pointer)))
        # The initialize callback can replace the local pointer before glyph mapping.
        if target==0x4adf20:writes.append((local,struct.pack('<I',text_base+0x20)))
        if target==0x4ca210:writes.append((local,bytes(4)))
        return writes
    def oracle(target,eax,edx,ebx,ecx,stack):
        original_events.append((target,eax,edx,ebx,ecx,stack,snapshot(lambda a,w:bytes(cpu.mem_read(a,w)))))
        for at,data in mutations(target):cpu.mem_write(at,data)
        return actors[0] if target==0x4ca000 else constructed if target==0x4abd70 else tokens[target]
    stubs=Stubs(cpu,oracle)
    for target,num in CALLEES.items():stubs.add(target,num,cdecl=target==0x4cdfb0)
    @Call
    def boundary(site,context):
        x=site.contents;target=x.target
        if target not in CALLEES:errors.append(('call',target));return 0
        stack=(x.stack,x.stack_next,x.stack_third) if target==0x4cdfb0 else ((x.stack,x.stack_next,x.stack_third,x.rest0,x.rest1) if target==0x4adf20 else ())
        native_events.append((target,x.eax,x.edx,x.ebx,x.ecx,stack,snapshot(lambda a,w:host[a].raw)))
        for at,data in mutations(target):
            base,offset,extent=locate(at)
            if base is None or offset+len(data)>extent:errors.append(('mutation',at));return 0
            c.memmove(c.addressof(host[base])+offset,data,len(data))
        if target==0x4cdfb0:x.out_value=out_pointer
        return actors[0] if target==0x4ca000 else constructed if target==0x4abd70 else tokens[target]
    calls=Calls(boundary,None)
    routines=((0x4713d0,'vertrix_title_letter_first_call'),(0x4715a0,'vertrix_title_letter_second_call'))
    for address,name in routines:
        function=getattr(native,name);function.argtypes=[c.POINTER(Calls),c.POINTER(Services),U,U,U];function.restype=U
        counts[hex(address)]=0
        for case in range(args.cases):
            host={base:c.create_string_buffer(rng.randbytes(size),size) for base,size in regions}
            for base,buf in host.items():cpu.mem_write(base,buf.raw)
            constructed=actors[case%2];out_pointer=text_base+(0xc if case%2 else 0x10)
            tokens={target:rng.getrandbits(32) for target in CALLEES}
            patches={target:[] for target in CALLEES}
            for target in CALLEES:
                for actor in actors:
                    patches[target]+=[(actor+off,rng.randbytes(width)) for off,width in((4,8),(0x24,16),(0x44,1),(0x52,1),(0x58,12),(0xb0,12),(0x154,8))]
                patches[target]+=[(0x4f8a44,rng.randbytes(24)),(0x4f9c02,rng.randbytes(4)),(text_base,rng.randbytes(64))]
            mode=rng.choice([0,1,2,0xffffffff,rng.getrandbits(32)])
            previous=rng.choice([0,0xffffffff,rng.getrandbits(32)])
            cpu.mem_write(0,struct.pack('<I',previous))
            original_events.clear();native_events.clear();errors.clear();stubs.log.clear()
            expected=original.call(address,eax=mode,edx=rng.getrandbits(32),ebx=rng.getrandbits(32),ecx=rng.getrandbits(32))
            got=function(c.byref(calls),c.byref(services),FRAME,mode,previous)
            assert not errors,(case,errors)
            assert got==expected==previous,(hex(address),case,got,expected,previous)
            assert native_events==original_events,(hex(address),case,[(i,a[:6],b[:6]) for i,(a,b) in enumerate(zip(native_events,original_events)) if a!=b],len(native_events),len(original_events))
            assert all(buf.raw==bytes(cpu.mem_read(base,len(buf))) for base,buf in host.items()),case
            assert int.from_bytes(cpu.mem_read(0,4),'little')==previous,case
            counts[hex(address)]+=1;completed+=1;calls_compared+=len(stubs.log)
            pointer_replacements+=sum(entry[0]==0x4adf20 for entry in stubs.log)
            formatter_calls+=sum(entry[0]==0x4cdfb0 for entry in stubs.log)
            constructor_changes+=constructed!=actors[0]
    assert completed==2*args.cases
    for address,name in routines:
        function=getattr(native,name)
        for runtime,service in((None,c.byref(services)),(c.byref(Calls(Call(),None)),c.byref(services)),
                              (c.byref(calls),None),(c.byref(calls),c.byref(Services(Resolve())))):
            before=snapshot(lambda a,w:host[a].raw);native_events.clear()
            assert function(runtime,service,FRAME,mode,previous)==0
            assert not native_events and snapshot(lambda a,w:host[a].raw)==before
    return {'complete_original_executions':counts,'exact_callback_register_stack_state_comparisons':calls_compared,
            'native_missing_boundary_guards':8,
            'mutable_string_pointer_replacement_cases':pointer_replacements,
            'constructor_result_handle_change_cases':constructor_changes,
            'cdecl_formatter_calls':formatter_calls,'scope':'Full normal builder return equals saved exception token. '
            'All callback registers/stack and independent actor/string/global/local storage compare '
            'before every callback and after completion under mutations, including constructor '
            'output handle changes and local string pointer replacement after formatting. Cdecl '
            'formatter stack cleanup and restored FS chain are verified. Faulting allocation, '
            'register clobbers and exception stack/unwind behavior remain outside boundary.'}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'title-letter', ['title_letter.c', 'call_glue.c', 'actor_storage.c'])
    for name in ('vertrix_title_letter_first', 'vertrix_title_letter_second'):
        getattr(n, name).argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
        getattr(n, name).restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x46f000)
    pool = Pool(cpu, 24, SIZE)
    globs = {g: c.create_string_buffer(4) for g in GLOBALS}
    length = [0]
    string_handle = pool.handles[23]

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in globs:
            storage[0], size[0] = c.addressof(globs[handle]), 4
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, outs, native_log, replay = [], [], [], []
    free = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4cdfb0:
            cpu.mem_write(stack[0], struct.pack('<I', string_handle + 0xc))
            outs.append(string_handle + 0xc)
        if address == 0x4ca000:
            returns.append(1)
        elif address == 0x4abd70:
            returns.append(free.pop(0))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count, cdecl=address == 0x4cdfb0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack, s.stack_next, s.stack_third) if s.target == 0x4cdfb0 else
            ((s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1) if s.target == 0x4adf20 else ())))
        if s.target == 0x4cdfb0:
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        for g, buffer in globs.items():
            word = struct.pack('<I', rng.getrandbits(32))
            buffer.raw = word
            cpu.mem_write(g, word)
        free[:] = pool.handles[:1]
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        which = rng.choice([(0x4713d0, 'vertrix_title_letter_first'),
                            (0x4715a0, 'vertrix_title_letter_second')])
        mode = rng.choice([1, 1, 0, 2, rng.getrandbits(32)])
        original.call(which[0], eax=mode)
        replay[:] = list(returns)
        free[:] = pool.handles[:1]
        assert getattr(n, which[1])(c.byref(calls), c.byref(services), FRAME, mode), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        totals[hex(which[0])] = totals.get(hex(which[0]), 0) + 1
    full = verify_full_builders(args,n)
    report = {'full_builder_abi': full, 'status': 'passed', 'complete_original_executions': totals,
              
              'scope': 'The routine executes completely in the original with the string runtime, '
                       'the allocation and the actor setters stubbed and logged (0x4cdfb0 storing '
                       'the new string through its stack pointer); every '
                       'call with its registers and stack arguments and every actor object compare.'}
    (args.build_dir / 'title-letter-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
