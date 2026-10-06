"""Compare integrated pixel descent and locking with the original loop slice."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original
from verify_timing import Motion
from verify_timer import Timer


class Piece(ctypes.Structure):
    _fields_ = [("x", ctypes.c_int16), ("y", ctypes.c_int16), ("blocks", ctypes.c_uint8 * 3), ("active", ctypes.c_uint8), ("failed", ctypes.c_uint8)]


class DescentState(ctypes.Structure):
    _fields_ = [("motion", Motion), ("blink", Timer), ("frozen", ctypes.c_uint32), ("flash", ctypes.c_uint32), ("cycle_mode", ctypes.c_uint32), ("block_effect", ctypes.c_uint16 * 3)]


def verify_ticks(native, oracle, chooser):
    native.vertrix_descent_tick.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_int16, ctypes.c_int16, ctypes.POINTER(Piece), ctypes.POINTER(DescentState), ctypes.c_uint32, ctypes.c_int, ctypes.c_uint32, ctypes.c_uint32]
    edges = [0, 1, 2, 24, 65535, 0x7FFFFFFF, 0xFFFFFFFF]
    for case in range(6000):
        board = [chooser.choice([255, 255, 255, 0, 1, 5, 6]) for _ in range(65)]
        if case % 3 == 0:
            board = [255] * 65
        column = case % 5
        origin_y = 200
        y = origin_y + chooser.randrange(- 120, 312)
        blocks = [chooser.randrange(7) for _ in range(3)]
        period, counter, elapsed = [chooser.choice(edges) for _ in range(3)]
        step = chooser.choice([0, 1, 2, 24, 32767, 32768, 65535])
        motion = (period, counter, step, chooser.randrange(3))
        blink = (chooser.choice(edges), chooser.choice(edges))
        frozen_state, flash, cycle = [chooser.choice(edges) for _ in range(3)]
        effects = [chooser.randrange(65536) for _ in range(3)]
        paused, frozen, blink_mode = chooser.randrange(2), chooser.choice([0, 0, 1, 2]), chooser.randrange(3)
        failed = case % 2
        piece = Piece(column * 24, y, (ctypes.c_uint8 * 3)(* blocks), 1, failed)
        state = DescentState(Motion(* motion), Timer(* blink), frozen_state, flash, cycle, (ctypes.c_uint16 * 3)(* effects))
        actual_board = (ctypes.c_uint8 * 65)(* board)
        expected = oracle.lock(board, column, 0, blocks, descent=(y, 0, failed), timed=(y, motion, blink, frozen_state, flash, cycle, effects, elapsed, paused, frozen, blink_mode, origin_y))
        native.vertrix_descent_tick(actual_board, 0, origin_y, ctypes.byref(piece), ctypes.byref(state), elapsed, paused, frozen, blink_mode)
        actual = (list(actual_board), piece.active, piece.y, piece.failed, state.motion.counter, state.blink.counter, state.frozen, state.flash)
        assert actual == expected[: 8], (case, motion, elapsed, paused, frozen, blink_mode, actual, expected)
        if piece.active:
            assert tuple(state.block_effect) == expected[8], (case, state.frozen, state.flash)
#Child effects cease to describe active objects once ownership transfers at lock.
        assert (state.motion.period, state.motion.step, state.motion.state) == (motion[0], motion[2], motion[3])
        assert state.blink.period == blink[1] and state.cycle_mode == cycle
    return 6000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "descent.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra", "-Werror", * [str(root / f"source/{name}.c") for name in ("board", "collision", "descent", "timer")], "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_descent.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_int16, ctypes.c_int16, ctypes.POINTER(Piece), ctypes.c_uint32]
    native.vertrix_move_horizontal.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_int16, ctypes.c_int16, ctypes.POINTER(Piece), ctypes.c_int]
    oracle = Original(args.executable)
    chooser = random.Random(0x42FC2D)
    for case in range(10000):
        board = [chooser.choice([255, 255, 255, 0, 1, 5, 6]) for _ in range(65)]
        if case % 3 == 0:
            board = [255] * 65
        column = case % 5
        y = chooser.randrange(- 72, 312)
        pixels = chooser.choice([1, 2, 23, 24, 25, 72, 500])
        blocks = [chooser.randrange(7) for _ in range(3)]
        failed = case % 2
        piece = Piece(column * 24, y, (ctypes.c_uint8 * 3)(* blocks), 1, failed)
        actual = (ctypes.c_uint8 * 65)(* board)
        expected = oracle.lock(board, column, 0, blocks, descent=(y, pixels, failed))
        native.vertrix_descent(actual, 0, 0, ctypes.byref(piece), pixels)
        if (list(actual), piece.active, piece.y, piece.failed) != expected:
            raise AssertionError(f"Descent differs: case={case}, y={y}, budget={pixels}")
    horizontal_cases = 0
    for case in range(10000):
        board = [chooser.choice([255, 255, 255, 0, 1, 5, 6]) for _ in range(65)]
        origin_x, origin_y = chooser.randrange(- 1000, 1000), chooser.randrange(100, 1000)
        x = origin_x + (case % 5) * 24 + chooser.randrange(24)
        y = origin_y + chooser.randrange(- 120, 240)
        active = case % 11 != 0
        for right in (0, 1):
            piece = Piece(x, y, (ctypes.c_uint8 * 3)(0, 1, 2), active, 0)
            actual = (ctypes.c_uint8 * 65)(* board)
            moved = native.vertrix_move_horizontal(actual, origin_x, origin_y, ctypes.byref(piece), right)
            expected = oracle.down_clear(board, origin_x, origin_y, x, y, horizontal=right, active=active)
            if (moved, piece.x) != expected or list(actual) != board or piece.y != y:
                raise AssertionError(f"Horizontal movement differs: case={case}, right={right}")
                horizontal_cases += 1
                tick_comparisons = verify_ticks(native, oracle, chooser)
    report = {"status": "passed", "timed_descent_comparisons": tick_comparisons, "integrated_descent_comparisons": 10000, "horizontal_movement_comparisons": horizontal_cases, "scope": "Original pixel loop, downward probe, board locking and " "failure flag; elapsed timers and frozen blinking integrated; " "surrounding board/player loop and rendering remain incomplete"}
    (args.build_dir / "descent-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))
if __name__ == "__main__":
    main()
