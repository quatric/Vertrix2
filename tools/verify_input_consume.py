"""Verify complete 475c30 with live pop/destructor boundaries and raw storage."""
import ctypes as c
import random
import struct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EDX,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
from original import Original
from verify_call_glue import Call,Calls
import verify_support as vs

ACTOR,EVENT,TABLE,DESTROY = 0x801000,0x802000,0x803000,0x700600
Read = c.CFUNCTYPE(c.c_int,c.c_uint32,c.c_uint,c.POINTER(c.c_uint32),c.c_void_p)
Write = c.CFUNCTYPE(c.c_int,c.c_uint32,c.c_uint,c.c_uint32,c.c_void_p)

def main():
    args = vs.parse(__doc__,2048)
    native = vs.build(args,'input-consume',['input.c','call_glue.c','actor_storage.c'])
    native.vertrix_input_queue_consume_full.argtypes = [c.c_uint32,Read,Write,c.c_void_p,c.POINTER(Calls),c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x475c30)
    regions = {}
    oracle_events,native_events,contexts = [],[],[]
    returned = 0
    mutation = False
    fail = None
    def locate(address,width):
        for base,data in regions.items():
            if base <= address and address+width <= base+len(data): return data,address-base
        return None,None
    @Read
    def read(address,width,value,context):
        contexts.append((context,width))
        data,index = locate(address,width)
        if data is None or fail == ('read',address): return 0
        value[0] = int.from_bytes(data[index:index+width],'little')
        return 1
    @Write
    def write(address,width,value,context):
        contexts.append((context,width))
        data,index = locate(address,width)
        if data is None or (fail == ('write',address) and bool(native_events)): return 0
        data[index:index+width] = value.to_bytes(4,'little')[:width]
        return 1
    def side_effects(pop,store):
        if pop:
            store(ACTOR+0x2c,struct.pack('<I',0))
            if mutation:
                store(EVENT,bytes([255]))
                store(EVENT+4,struct.pack('<3I',91,92,93))
                store(ACTOR+5,b'xyz')
                store(EVENT+0x18,struct.pack('<I',TABLE+0x40))
        elif mutation:
            store(ACTOR+0x30,b'done')
    def host_store(address,data):
        region,index=locate(address,len(data));region[index:index+len(data)] = data
    def oracle_hook(cpu,address,size,context):
        oracle_events.append((address,*[cpu.reg_read(r) for r in
            (UC_X86_REG_EAX,UC_X86_REG_EDX,UC_X86_REG_EBX,UC_X86_REG_ECX)]))
        side_effects(address==0x4d8540,cpu.mem_write)
        cpu.reg_write(UC_X86_REG_EAX,EVENT if address==0x4d8540 else returned)
        stack=cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP,struct.unpack('<I',cpu.mem_read(stack,4))[0])
        cpu.reg_write(UC_X86_REG_ESP,stack+4)
    for target in (0x4d8540,DESTROY,DESTROY+0x10):
        cpu.hook_add(UC_HOOK_CODE,oracle_hook,begin=target,end=target)
    @Call
    def call(site_pointer,context):
        site=site_pointer.contents
        contexts.append((context,0))
        native_events.append((site.target,site.eax,site.edx,site.ebx,site.ecx))
        side_effects(site.target==0x4d8540,host_store)
        return EVENT if site.target==0x4d8540 else returned
    calls=Calls(call,0x1234)
    completed=mutations=0
    for case in range(args.cases):
        count=0 if case%4==0 else rng.randrange(1,10)
        actor=bytearray(rng.randbytes(0x60));event=bytearray(rng.randbytes(28))
        struct.pack_into('<I',actor,0x2c,count)
        struct.pack_into('<I',event,0x18,TABLE)
        regions={ACTOR:actor,EVENT:event,TABLE:bytearray(struct.pack('<I',DESTROY)+bytes(0x3c)+struct.pack('<I',DESTROY+0x10))}
        for base,data in regions.items(): cpu.mem_write(base,bytes(data))
        returned=rng.getrandbits(32);mutation=case%3==0
        oracle_events.clear();native_events.clear();contexts.clear()
        wanted=original.call(0x475c30,eax=ACTOR,edx=rng.getrandbits(32),ebx=rng.getrandbits(32),ecx=rng.getrandbits(32))
        output=c.c_uint32(0xdeadbeef)
        assert native.vertrix_input_queue_consume_full(ACTOR,read,write,0x1234,c.byref(calls),c.byref(output))
        assert output.value==wanted and oracle_events==native_events,(case,wanted,output.value,oracle_events,native_events)
        assert all(context==0x1234 for context,width in contexts)
        assert all(bytes(data)==bytes(cpu.mem_read(base,len(data))) for base,data in regions.items()),case
        assert len(native_events)==(2 if count else 0)
        completed+=1;mutations+=bool(count and mutation)
    # Fail after clearing, after popping, and after partially copying the event.
    failures=0
    mutation=True
    for failure in [('read',ACTOR+0x2c),('read',EVENT+4),('write',ACTOR+0xc),('read',EVENT+0x18)]:
        regions={ACTOR:bytearray(bytes([0xaa])*0x60),EVENT:bytearray(bytes([0xbb])*28),TABLE:bytearray(struct.pack('<I',DESTROY)+bytes(0x3c)+struct.pack('<I',DESTROY+0x10))}
        struct.pack_into('<I',regions[ACTOR],0x2c,1)
        struct.pack_into('<I',regions[EVENT],0x18,TABLE)
        fail=failure;native_events.clear();contexts.clear();output=c.c_uint32(0xdeadbeef)
        assert not native.vertrix_input_queue_consume_full(ACTOR,read,write,0x1234,c.byref(calls),c.byref(output))
        assert output.value==0xdeadbeef
        if failure[1]==ACTOR+0x2c: assert regions[ACTOR][4]==0
        assert regions[ACTOR][0x14:0x16]==bytes(2) and regions[ACTOR][0x18:0x1c]==bytes(4)
        assert len(native_events)==(0 if failure[1]==ACTOR+0x2c else 1)
        if native_events: assert regions[ACTOR][5:8]==b'xyz' and regions[EVENT][4:16]==struct.pack('<3I',91,92,93)
        assert all(context==0x1234 for context,width in contexts)
        failures+=1
    assert completed==args.cases
    vs.write_report(args,'input-consume',{'status':'passed','complete_original_cases':completed,
        'mutable_pop_and_destructor_cases':mutations,'native_late_failure_cases':failures,
        'scope':'Complete original 475c30 and actual475790/4757e0 clear/copy helpers. Pop4d8540 and virtual destructor are independently logged supplied boundaries with live event mutation. Entire actor/event/vtable memory and target/eax/edx/ebx/ecx/return compare, including empty queue. Native late failures retain prior clears/pop/mutations and leave result unchanged. Allocation and destructor bodies remain boundary implementations.'})

if __name__=='__main__':main()
