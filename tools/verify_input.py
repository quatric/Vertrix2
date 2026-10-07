"""Compare held-input repeat scheduling with the original executable."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original

class Repeat(ctypes.Structure):
    _fields_ = [("initial_delay", ctypes.c_uint32), ("repeat_delay", ctypes.c_uint32),
                ("counter", ctypes.c_uint32), ("period", ctypes.c_uint32),
                ("payload", ctypes.c_uint32 * 3), ("enabled", ctypes.c_uint8)]

class Event(ctypes.Structure):
    _fields_ = [("state", ctypes.c_uint8), ("payload", ctypes.c_uint32 * 3)]

class Queue(ctypes.Structure):
    _fields_ = [("current", Event), ("head", ctypes.c_void_p), ("tail", ctypes.c_void_p),
                ("count", ctypes.c_size_t), ("mode", ctypes.c_uint8)]

def verify_queues(native, oracle, rng):
    native.vertrix_input_queue_init.argtypes = [ctypes.POINTER(Queue), ctypes.c_uint8]
    native.vertrix_input_queue_push.argtypes = [ctypes.POINTER(Queue), ctypes.POINTER(Event)]
    native.vertrix_input_queue_update.argtypes = [ctypes.POINTER(Queue), ctypes.c_int, ctypes.c_int]
    for name in ("clear", "consume", "acknowledge", "ready"):
        getattr(native, "vertrix_input_queue_" + name).argtypes = [ctypes.POINTER(Queue)]
    comparisons = 0
    for case in range(6000):
        mode = rng.choice([0, 1, 2, 255])
        current = (rng.choice([0, 1, 2, 255]), [rng.randrange(2**32) for _ in range(3)])
        events = [(rng.choice([0, 1, 2, 255]), [rng.randrange(2**32) for _ in range(3)])
                  for _ in range(rng.randrange(17))]
        operations = [(rng.choice(["single", "drain", "consume", "acknowledge"]),
                       rng.choice([0, 1, 0xFFFFFFFF])) for _ in range(12)]
#Drain the rest explicitly, verifying FIFO order and empty consumption.
        operations += [("consume", 0)] * (len(events) + 1)
        expected = oracle.input_queue(mode, current, events, operations)
        queue = Queue()
        native.vertrix_input_queue_init(ctypes.byref(queue), mode)
        queue.current = Event(current[0], (ctypes.c_uint32 * 3)(*current[1]))
        try:
            for state, payload in events:
                event = Event(state, (ctypes.c_uint32 * 3)(*payload))
                assert native.vertrix_input_queue_push(ctypes.byref(queue), ctypes.byref(event))
            for (operation, deferred), result in zip(operations, expected):
                if operation in ("single", "drain"):
                    native.vertrix_input_queue_update(ctypes.byref(queue), operation == "drain", deferred)
                else:
                    getattr(native, "vertrix_input_queue_" + operation)(ctypes.byref(queue))
                actual = (queue.current.state, tuple(queue.current.payload), queue.count,
                          native.vertrix_input_queue_ready(ctypes.byref(queue)))
                assert actual == result[:4], (case, mode, operation, actual, result)
                assert result[4] == tuple(range(len(events) - queue.count))
                assert bool(queue.head) == bool(queue.count) == bool(queue.tail)
                comparisons += 1
        finally:
            native.vertrix_input_queue_clear(ctypes.byref(queue))
        assert queue.count == 0 and not queue.head and not queue.tail and queue.mode == mode
        assert queue.current.state == 0 and tuple(queue.current.payload) == (0, 0, 0)
#Clear a nonempty queue, then reuse it without reinitialization.
    for mode in (0, 1, 2, 255):
        queue = Queue()
        native.vertrix_input_queue_init(ctypes.byref(queue), mode)
        event = Event(1, (ctypes.c_uint32 * 3)(7, 8, 9))
        for _ in range(100):
            assert native.vertrix_input_queue_push(ctypes.byref(queue), ctypes.byref(event))
        native.vertrix_input_queue_clear(ctypes.byref(queue))
        assert not queue.count and not queue.head and not queue.tail
        assert native.vertrix_input_queue_push(ctypes.byref(queue), ctypes.byref(event))
        native.vertrix_input_queue_consume(ctypes.byref(queue))
        assert queue.current.state == 1 and tuple(queue.current.payload) == (7, 8, 9)
        native.vertrix_input_queue_clear(ctypes.byref(queue))
    return comparisons

class Action(ctypes.Structure):
    _fields_ = [("queue", Queue), ("repeat", Repeat), ("id", ctypes.c_uint16)]

class Node(ctypes.Structure):
    pass

Node._fields_ = [("event", Event), ("next", ctypes.POINTER(Node))]
Sink = ctypes.CFUNCTYPE(ctypes.c_int, ctypes.c_void_p, ctypes.c_uint16,
                       ctypes.POINTER(ctypes.c_uint32))

def verify_actions(native, oracle, rng):
    native.vertrix_input_action_init.argtypes = [ctypes.POINTER(Action), ctypes.c_uint16,
                                               ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32]
    native.vertrix_input_action_clear.argtypes = [ctypes.POINTER(Action)]
    native.vertrix_input_action_edge.argtypes = [ctypes.POINTER(Action), ctypes.POINTER(ctypes.c_uint32),
                                               ctypes.c_int, ctypes.c_int, ctypes.c_int, Sink, ctypes.c_void_p]
    native.vertrix_input_action_update.argtypes = [ctypes.POINTER(Action), ctypes.c_uint32,
                                                 ctypes.c_int, ctypes.c_int, Sink, ctypes.c_void_p]
    comparisons = 0
    for case in range(2000):
        action_id = rng.randrange(65536)
        mode = rng.choice([0, 1, 2, 255])
        values = [rng.randrange(40, 500), rng.choice([0, 50, 100]), rng.randrange(1000),
                  rng.randrange(40, 500), *[rng.randrange(2**32) for _ in range(3)]]
        enabled = rng.choice([0, 1, 2, 255])
        operations = []
        for _ in range(40):
            kind = rng.choice(["edge", "edge", "single", "drain", "acknowledge"])
            deferred = rng.choice([0, 0, 1, 0xFFFFFFFF])
            if kind == "edge":
                operations.append((kind, deferred, rng.randrange(2), rng.randrange(2),
                                   [rng.randrange(2**32) for _ in range(3)]))
            elif kind == "acknowledge":
                operations.append((kind, deferred))
            else:
                operations.append((kind, deferred, rng.randrange(501)))
        expected = oracle.input_actions(action_id, mode, values, enabled, operations)
        action = Action()
        native.vertrix_input_action_init(ctypes.byref(action), action_id, mode, values[0], values[1])
        action.repeat = Repeat(*values[:4], (ctypes.c_uint32 * 3)(*values[4:]), enabled)
        deferred_events = []
        @Sink
        def sink(context, delivered_id, payload):
            deferred_events.append((delivered_id, tuple(payload[i] for i in range(3))))
            return 1
        try:
            for operation, result in zip(operations, expected):
                kind, deferred, *args = operation
                if kind == "edge":
                    pressed, force, payload = args
                    assert native.vertrix_input_action_edge(ctypes.byref(action),
                        (ctypes.c_uint32 * 3)(*payload), pressed, force, bool(deferred), sink, None)
                elif kind == "acknowledge":
                    native.vertrix_input_queue_acknowledge(ctypes.byref(action.queue))
                else:
                    assert native.vertrix_input_action_update(ctypes.byref(action), args[0],
                                                             kind == "drain", bool(deferred), sink, None)
                repeat = action.repeat
                actual_repeat = (repeat.initial_delay, repeat.repeat_delay, repeat.counter,
                                 repeat.period, *repeat.payload)
                current = (action.queue.current.state, tuple(action.queue.current.payload))
                pending = []
                node = ctypes.cast(action.queue.head, ctypes.POINTER(Node))
                while node:
                    pending.append((node.contents.event.state, tuple(node.contents.event.payload)))
                    node = node.contents.next
                actual = (actual_repeat, repeat.enabled, current, tuple(pending), tuple(deferred_events))
                assert actual == result, (case, operation, actual, result)
                assert action.queue.count == len(pending)
                comparisons += 1
        finally:
            native.vertrix_input_action_clear(ctypes.byref(action))
        assert not action.repeat.enabled and not action.queue.count and not action.queue.head
    return comparisons

def verify_configuration(native, oracle, rng):
    native.vertrix_input_configure.argtypes = [ctypes.POINTER(Action), ctypes.POINTER(ctypes.c_uint16),
                                             ctypes.POINTER(ctypes.c_uint32), ctypes.c_uint32]
    for case in range(500):
#Duplicate bindings deliberately exercise the original ordered overwrites.
        controls = [rng.randrange(256 if case % 2 else 4) for _ in range(9)]
        delays = [rng.randrange(2**32) for _ in range(2)]
        default = rng.choice([0, 1, 0xFFFFFFFF, rng.randrange(2**32)])
        initial = [(rng.randrange(256), tuple(rng.randrange(2**32) for _ in range(7)))
                   for _ in range(256)]
        expected = oracle.input_configure(controls, delays, default, initial)
        actions = (Action * 256)()
        for i, (mode, repeat) in enumerate(initial):
            actions[i].queue.mode = mode
            actions[i].repeat = Repeat(*repeat[:4], (ctypes.c_uint32 * 3)(*repeat[4:]), 1)
        assert native.vertrix_input_configure(actions, (ctypes.c_uint16 * 9)(*controls),
                                             (ctypes.c_uint32 * 2)(*delays), default)
        for i, (mode, repeat) in enumerate(expected):
            actual = actions[i].repeat
            assert actions[i].queue.mode == mode
            assert (actual.initial_delay, actual.repeat_delay, actual.counter,
                    actual.period, *actual.payload) == repeat
            assert actual.enabled == 1
        before = bytes(actions)
        assert not native.vertrix_input_configure(actions, (ctypes.c_uint16 * 9)(*[65535] * 9),
                                                 (ctypes.c_uint32 * 2)(*delays), default)
        assert bytes(actions) == before
    return 500

def verify_full_repeat(native, oracle, cases):
    import struct
    from original import BOARD
    from verify_call_glue import Call, Calls
    from unicorn import UC_HOOK_CODE
    from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EIP, UC_X86_REG_ESP
    native.vertrix_input_repeat_tick_full.argtypes = [ctypes.POINTER(Repeat), ctypes.c_uint32,
        ctypes.c_uint32, ctypes.POINTER(Calls), ctypes.POINTER(ctypes.c_uint32)]
    original_events, native_events, contexts = [], [], []
    returns = []
    mutation = False
    repeat = None
    def mutate_native():
        repeat.payload[:] = (101, 202, 303)
        repeat.counter, repeat.period, repeat.repeat_delay, repeat.enabled = 77, 88, 99, 0
    def insert(cpu, address, size, context):
        original_events.append((address, *[cpu.reg_read(r) for r in
            (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)]))
        if mutation and len(original_events) == 1:
            cpu.mem_write(BOARD+0x4c, struct.pack('<3I', 101, 202, 303))
            cpu.mem_write(BOARD+0x40, struct.pack('<3I', 99, 77, 88))
            cpu.mem_write(BOARD+0x5a, b'\0')
        cpu.reg_write(UC_X86_REG_EAX, returns[len(original_events)-1])
        stack = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I',cpu.mem_read(stack,4))[0])
        cpu.reg_write(UC_X86_REG_ESP,stack+4)
    @Call
    def callback(site_pointer, context):
        site = site_pointer.contents
        native_events.append((site.target,site.eax,site.edx,site.ebx,site.ecx))
        contexts.append(context)
        if mutation and len(native_events) == 1: mutate_native()
        return returns[len(native_events)-1] if len(native_events) <= len(returns) else 0
    boundary = Calls(callback,0x1234)
    hook = oracle.cpu.hook_add(UC_HOOK_CODE,insert,begin=0x475b20,end=0x475b20)
    completed = mutation_cases = 0
    try:
        fixtures = [(case,False) for case in cases]
        fixtures += [(([100,50,0,2,7,8,9],1,8,None,False),True)]
        fixtures += [(([100,50,0,0,7,8,9],1,0,None,False),False)]
        for (values,enabled,elapsed,payload,stop),mutation in fixtures:
            repeat = Repeat(*values[:4],(ctypes.c_uint32*3)(*values[4:]),enabled)
            if payload is not None:
                native.vertrix_input_repeat_start(ctypes.byref(repeat),(ctypes.c_uint32*3)(*payload))
            if stop: native.vertrix_input_repeat_stop(ctypes.byref(repeat))
            raw = bytearray(0x60)
            struct.pack_into('<7I',raw,0x3c,repeat.initial_delay,repeat.repeat_delay,repeat.counter,repeat.period,*repeat.payload)
            raw[0x5a] = repeat.enabled
            oracle.cpu.mem_write(BOARD,bytes(raw))
            original_events.clear(); native_events.clear(); contexts.clear()
            returns = [(0x80000000 + i*17) & 0xffffffff for i in range(10001)]
            wanted = oracle.call(0x475e50,eax=BOARD,edx=elapsed,ebx=0x12345678,ecx=0x87654321)
            result = ctypes.c_uint32(0xdeadbeef)
            assert native.vertrix_input_repeat_tick_full(ctypes.byref(repeat),BOARD,elapsed,ctypes.byref(boundary),ctypes.byref(result))
            assert result.value == wanted and original_events == native_events, (completed,result.value,wanted,original_events,native_events)
            assert contexts == [0x1234]*len(native_events)
            expected = struct.unpack('<7I',oracle.cpu.mem_read(BOARD+0x3c,28))
            assert (repeat.initial_delay,repeat.repeat_delay,repeat.counter,repeat.period,*repeat.payload) == expected
            assert repeat.enabled == bytes(oracle.cpu.mem_read(BOARD+0x5a,1))[0]
            completed += 1
            if mutation:
                assert len(native_events)==4 and native_events[1][2:] == (101,202,303)
                mutation_cases += 1
    finally:
        oracle.cpu.hook_del(hook)
    repeat = Repeat(100,50,0,2,(ctypes.c_uint32*3)(7,8,9),1)
    result = ctypes.c_uint32(0xdeadbeef)
    assert not native.vertrix_input_repeat_tick_full(ctypes.byref(repeat),BOARD,8,None,ctypes.byref(result))
    assert repeat.counter==0 and repeat.period==50 and result.value==0xdeadbeef
    assert completed == len(cases)+2
    return completed,mutation_cases

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "input.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra",
                    "-Werror", str(root / "source/input.c"), str(root / "source/call_glue.c"),
                    str(root / "source/actor_storage.c"), "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_input_repeat_tick.argtypes = [ctypes.POINTER(Repeat), ctypes.c_uint32]
    native.vertrix_input_repeat_tick.restype = ctypes.c_uint32
    native.vertrix_input_repeat_start.argtypes = [ctypes.POINTER(Repeat), ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_input_repeat_stop.argtypes = [ctypes.POINTER(Repeat)]
    oracle = Original(args.executable)
    rng = random.Random(0x475E50)
    cases = []
    edges = [0, 1, 2, 100, 65535, 0x7FFFFFFF, 0xFFFFFFFF]
    for counter in edges:
        for elapsed in edges:
            for enabled in [0, 1, 2, 255]:
                for period in [0, 1, 100, 0xFFFFFFFF]:
                    total = (counter + elapsed) & 0xFFFFFFFF
#Keep original enqueue loop within the emulator instruction budget.
                    if total // (period or 1) <= 100:
                        cases.append(([100, 50, counter, period, 7, 8, 9], enabled, elapsed, None, False))
    for _ in range(6000):
        period = rng.randrange(1, 1000)
        values = [rng.randrange(1, 1000), rng.randrange(1000), rng.randrange(10000),
                  period, *[rng.randrange(2**32) for _ in range(3)]]
        payload = [rng.randrange(2**32) for _ in range(3)] if rng.randrange(3) == 0 else None
        cases.append((values, rng.choice([0, 1, 2]), rng.randrange(1000), payload, rng.randrange(5) == 0))
    for values, enabled, elapsed, payload, stop in cases:
        repeat = Repeat(*values[:4], (ctypes.c_uint32 * 3)(*values[4:]), enabled)
        expected, expected_enabled, events = oracle.input_repeat(values + [0], enabled, elapsed, payload, stop)
        if payload is not None:
            native.vertrix_input_repeat_start(ctypes.byref(repeat), (ctypes.c_uint32 * 3)(*payload))
        if stop:
            native.vertrix_input_repeat_stop(ctypes.byref(repeat))
        count = native.vertrix_input_repeat_tick(ctypes.byref(repeat), elapsed)
        actual = (repeat.initial_delay, repeat.repeat_delay, repeat.counter, repeat.period, *repeat.payload)
        assert actual == expected[:7] and repeat.enabled == expected_enabled, (values, enabled, elapsed)
        assert count == len(events) and all(event == tuple(repeat.payload) for event in events)
    full_repeat_comparisons, repeat_mutation_cases = verify_full_repeat(native,oracle,cases)
    queue_comparisons = verify_queues(native, oracle, rng)
    action_comparisons = verify_actions(native, oracle, rng)
    configuration_comparisons = verify_configuration(native, oracle, rng)
    report = {"status": "passed", "repeat_scheduler_comparisons": len(cases),
              "full_repeat_scheduler_comparisons": full_repeat_comparisons,
              "repeat_insertion_mutation_cases": repeat_mutation_cases,
              "repeat_missing_boundary_cases": 1,
              "queue_operation_comparisons": queue_comparisons,
              "integrated_action_comparisons": action_comparisons,
              "control_configuration_comparisons": configuration_comparisons,
              "scope": "Full original475e50 insertion target/registers/return/state matched independently, including live payload/state mutation and fixed due count; missing insertion boundary retains timing updates. Original repeat scheduler and FIFO action consumption/update/acknowledgment; host allocation replaces original pool; press/release wrappers, repeat generation and deferred delivery integrated; polling, bindings and gameplay dispatch remain separate"}
    (args.build_dir / "input-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
