"""Compare original active-piece input dispatch with integrated native systems."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original
from verify_descent import Piece
from verify_input import Action, Event, Node, Repeat, Sink
from verify_random import NativeRandom
from verify_timing import Motion


class Controls(ctypes.Structure):
    _fields_ = [("piece", ctypes.POINTER(Piece)), ("motion", ctypes.POINTER(Motion)), ("random", ctypes.POINTER(NativeRandom)), ("actions", ctypes.POINTER(Action)), ("control", ctypes.c_uint16 * 4), ("opponent", ctypes.c_uint16 * 2), ("mode", ctypes.c_uint32), ("cycle_mode", ctypes.c_uint32), ("difficulty", ctypes.c_int), ("deferred", ctypes.c_int), ("sink", Sink), ("sink_context", ctypes.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "controls.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", * [str(root / f"source/{name}.c") for name in ("controls", "input", "board", "collision", "descent", "timer", "piece", "random", "timing")], "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_random_seed.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint32]
    native.vertrix_input_action_init.argtypes = [ctypes.POINTER(Action), ctypes.c_uint16, ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32]
    native.vertrix_input_action_clear.argtypes = [ctypes.POINTER(Action)]
    native.vertrix_controls_dispatch.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_int16, ctypes.c_int16, ctypes.POINTER(Controls), ctypes.POINTER(ctypes.c_uint8)]
    oracle = Original(args.executable)
    rng = random.Random(0x451048)
    comparisons = 0
    for seed in [0, 1, 0x12345678, 0xFFFFFFFF]:
        random_state = NativeRandom()
        native.vertrix_random_seed(ctypes.byref(random_state), seed)
        oracle.piece_seed(seed)
        for case in range(1250):
            board = [rng.choice([255, 255, 255, 0, 1, 5, 6]) for _ in range(65)]
            if case % 3 == 0:
                board = [255] * 65
            origin = (rng.randrange(- 1000, 1000), rng.randrange(100, 1000))
            position = (origin[0] + (case % 5) * 24 + rng.randrange(24), origin[1] + rng.randrange(- 120, 240))
            blocks = [rng.randrange(7) for _ in range(3)]
            motion_values = (rng.randrange(2 ** 32), rng.randrange(2 ** 32), rng.randrange(65536), rng.choice([0, 0, 1, 2, 0xFFFFFFFF]))
            bindings = [rng.randrange(8) for _ in range(6)]
            mode, cycle_mode = rng.choice([0, 0x2B, 0x2B, 0xFFFFFFFF]), rng.choice([0, 1, 2])
            difficulty, failed, deferred = rng.randrange(3), case % 13 == 0, rng.choice([0, 0, 1])
            inputs = [(rng.choice([0, 1, 1, 2, 255]), tuple(rng.randrange(2 ** 32) for _ in range(3)), rng.choice([0, 1, 2, 255]), tuple(rng.randrange(2 ** 32) for _ in range(7))) for _ in range(8)]
            expected = oracle.controls_dispatch(board, origin, position, blocks, motion_values, bindings, mode, cycle_mode, difficulty, int(failed), deferred, inputs)
            actions = (Action * 256)()
            for i, (state, payload, enabled, repeat) in enumerate(inputs):
                native.vertrix_input_action_init(ctypes.byref(actions[i]), i, 0, repeat[0], repeat[1])
                actions[i].queue.current = Event(state, (ctypes.c_uint32 * 3)(* payload))
                actions[i].repeat = Repeat(* repeat[: 4], (ctypes.c_uint32 * 3)(* repeat[4:]), enabled)
            piece = Piece(* position, (ctypes.c_uint8 * 3)(* blocks), 1, failed)
            motion = Motion(* motion_values)
            delivered = []
            @ Sink
            def sink(context, action_id, payload):
                delivered.append((action_id, 1, tuple(payload[i] for i in range(3)), True))
                return 1
            controls = Controls(ctypes.pointer(piece), ctypes.pointer(motion), ctypes.pointer(random_state), actions, (ctypes.c_uint16 * 4)(* bindings[: 4]), (ctypes.c_uint16 * 2)(* bindings[4:]), mode, cycle_mode, difficulty, deferred, sink, None)
            refresh = ctypes.c_uint8(0)
            try:
                assert native.vertrix_controls_dispatch((ctypes.c_uint8 * 65)(* board), * origin, ctypes.byref(controls), ctypes.byref(refresh))
                actual_inputs = []
                for i in range(8):
                    q, r = actions[i].queue, actions[i].repeat
                    actual_inputs.append((q.current.state, tuple(q.current.payload), r.enabled, (r.initial_delay, r.repeat_delay, r.counter, r.period, * r.payload)))
                    pending = []
                    node = ctypes.cast(q.head, ctypes.POINTER(Node))
                    while node:
                        pending.append((i, node.contents.event.state, tuple(node.contents.event.payload), False))
                        node = node.contents.next
                    assert tuple(pending) == tuple(event for event in expected[4] if event[0] == i and not event[3])
                    assert q.count == len(pending)
                assert tuple(delivered) == tuple(event for event in expected[4] if event[3])
                actual = (piece.x, tuple(piece.blocks), (motion.period, motion.counter, motion.step, motion.state), tuple(actual_inputs), refresh.value, random_state.position)
                target = expected[: 4] + expected[5:
                    ]
                assert actual == target, (seed, case, bindings, actual, target)
                assert piece.y == position[1] and piece.active == 1 and piece.failed == failed
            finally:
                for i in range(8):
                    native.vertrix_input_action_clear(ctypes.byref(actions[i]))
            comparisons += 1
    report = {"status": "passed", "active_piece_dispatch_comparisons": comparisons, "scope": "Original input order, movement, cycle/bottom-color RNG, fast drop, opponent input generation, acknowledgments and refresh request; surrounding player/board state loop and rendering remain unfinished"}
    (args.build_dir / "controls-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
