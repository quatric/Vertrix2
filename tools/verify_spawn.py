"""Verify original spawn-column selection and constructor coordinate inputs."""

import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path

from original import Original
from verify_random import NativeRandom
from verify_descent import Piece, DescentState
from verify_timer import Timer


class Spawn(ctypes.Structure):
    _fields_ = [("column", ctypes.c_uint32), ("x", ctypes.c_int16), ("y", ctypes.c_int16)]


class AnimationRange(ctypes.Structure):
    _fields_ = [("first", ctypes.c_uint32), ("last", ctypes.c_uint32)]

class SpawnDetails(ctypes.Structure):
    _fields_ = [("animation", Timer * 3), ("primary", Timer * 3),
                ("blink_mode", ctypes.c_uint32)]

def verify_initialization(native, oracle, chooser):
    native.vertrix_random_seed.argtypes = [ctypes.POINTER(NativeRandom), ctypes.c_uint32]
    native.vertrix_spawn_initialize.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(ctypes.c_uint32),
        ctypes.c_int16, ctypes.c_int16, ctypes.POINTER(ctypes.c_uint8), ctypes.POINTER(Piece),
        ctypes.POINTER(DescentState), ctypes.POINTER(SpawnDetails), ctypes.POINTER(NativeRandom),
        ctypes.POINTER(AnimationRange), ctypes.c_int, ctypes.c_int]
    comparisons = 0
    for seed in [0, 1, 0x12345678, 0xFFFFFFFF]:
        random_state = NativeRandom()
        native.vertrix_random_seed(ctypes.byref(random_state), seed)
        oracle.piece_seed(seed)
        for case in range(1200):
            board = [chooser.choice([255, 255, 0, 1, 5, 6]) for _ in range(65)]
            preferred = chooser.randrange(5)
            origin_x, origin_y = chooser.randrange(-32768, 32768), chooser.randrange(-32768, 32768)
            blocks = [chooser.randrange(7) for _ in range(3)]
            failed, difficulty, level = case % 2, chooser.randrange(3), chooser.randrange(10)
            frames = []
            for _ in range(7):
                first = chooser.randrange(10000)
                width = chooser.choice([1, 2, 10, 100, 65535])
                frames.append((first, first + width - 1))
            expected = oracle.spawn_initialize(board, preferred, origin_x, origin_y, blocks,
                                               difficulty, level, failed, frames)
            piece, state, details = Piece(), DescentState(), SpawnDetails()
            ctypes.memset(ctypes.byref(piece), 0xA5, ctypes.sizeof(piece))
            ctypes.memset(ctypes.byref(state), 0xA5, ctypes.sizeof(state))
            ctypes.memset(ctypes.byref(details), 0xA5, ctypes.sizeof(details))
            piece.failed = failed
            preferred_value = ctypes.c_uint32(preferred)
            actual_board = (ctypes.c_uint8 * 65)(*board)
            assert native.vertrix_spawn_initialize(actual_board, ctypes.byref(preferred_value), origin_x, origin_y,
                (ctypes.c_uint8 * 3)(*blocks), ctypes.byref(piece), ctypes.byref(state), ctypes.byref(details),
                ctypes.byref(random_state), (AnimationRange * 7)(*[AnimationRange(*r) for r in frames]), difficulty, level)
            actual = (piece.x, piece.y, tuple(piece.blocks),
                      (state.motion.period, state.motion.counter, state.motion.step, state.motion.state),
                      (state.blink.counter, state.blink.period), state.frozen, state.flash, state.cycle_mode,
                      tuple(state.block_effect), tuple((details.animation[i].period, details.animation[i].counter, details.primary[i].counter,
                                                       details.primary[i].period) for i in range(3)),
                      piece.failed, preferred_value.value, random_state.position, details.blink_mode)
            assert actual == expected, (seed, case, actual, expected)
            assert piece.active == 1 and list(actual_board) == board
            comparisons += 1
    return comparisons

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable", type=Path)
    parser.add_argument("--build-dir", type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / "spawn.dylib"
    subprocess.run(["cc", "-shared", "-fPIC", "-O2", "-Wall", "-Wextra",
                    "-Werror", *[str(root / f"source/{name}.c") for name in ("spawn", "random", "timing")], "-o", str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_spawn_position.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_uint32,
                                             ctypes.c_int16, ctypes.c_int16]
    native.vertrix_spawn_position.restype = Spawn
    oracle = Original(args.executable)
    chooser = random.Random(0x431D90)
    edges = [-32768, -32767, -1, 0, 1, 32766, 32767]
    cases = [(column, x, y) for column in range(5) for x in edges for y in edges]
    cases += [(i % 5, chooser.randrange(-32768, 32768), chooser.randrange(-32768, 32768))
              for i in range(10000)]
    for preferred, x, y in cases:
        for occupied in (False, True):
            board = [255] * 65
            if occupied:
                board[preferred * 13] = 5
                board[2 * 13] = 6
            actual = native.vertrix_spawn_position((ctypes.c_uint8 * 65)(*board), preferred, x, y)
            expected = oracle.spawn_position(board, preferred, x, y)
            if (actual.column, actual.x, actual.y) != expected:
                raise AssertionError(f"Spawn differs: {(preferred, x, y, occupied)}")
    initialization_comparisons = verify_initialization(native, oracle, chooser)
    report = {"status": "passed", "spawn_initialization_comparisons": initialization_comparisons, "spawn_position_comparisons": len(cases) * 2,
              "scope": "Original column selection and constructor position inputs; recovered native piece/timer/animation initialization and RNG consumption; rendering resource ownership and caller state-machine integration remain unfinished"}
    (args.build_dir / "spawn-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
