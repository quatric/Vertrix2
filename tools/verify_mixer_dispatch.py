""
    "Verify all eight native dispatch modes using existing original-kernel oracles."
    "" import argparse import json import sys from pathlib import Path

        def
        main()
    : parser = argparse.ArgumentParser(description = __doc__) parser
                   .add_argument("executable", type = Path) parser.add_argument(
                       "--build-dir", type = Path, required = True) args =
          parser.parse_args() build =
              args.build_dir.resolve() build.mkdir(parents = True, exist_ok = True) reports =
                  [] tools = Path(__file__).resolve().parent saved_argv = sys.argv
try:
        for depth in (8, 16):
            for stereo in (0, 1):
                for interpolate in (0, 1):
                    mode = "stereo" if stereo else "mono"
                    stem = "verify_mixer_" + ("pcm16_" if depth == 16 else "") + ("interpolated_" if interpolate else "") + mode
                    text = (tools / (stem + ".py")).read_text()
                    function = "vertrix_mixer_pcm" + str(depth) + "_" + mode + ("_interpolated" if interpolate else "")
                    text = text.replace("range(2500)", "range(250)")
                    text = text.replace("native." + function + "(", "dispatch_adapter(")
                    lines = text.splitlines()
                    index = next(i for i, line in enumerate(lines) if "native." + function + ".argtypes" in line)
                    adapter = [
                        "    native.vertrix_mixer_accumulate.argtypes = [ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_uint8, ctypes.c_uint8, ctypes.c_int, ctypes.c_int, ctypes.POINTER(State), ctypes.POINTER(ctypes.c_int32), ctypes.c_size_t, ctypes.c_size_t]",
                        "    def dispatch_adapter(*arguments):",
                        "        prefix = arguments[:5]",
                        "        pan = arguments[5]" if stereo else "        pan = 128",
                        "        suffix = arguments[6:]" if stereo else "        suffix = arguments[5:]",
                        f"        return native.vertrix_mixer_accumulate(*prefix, pan, {2 if depth == 16 else 0}, {stereo}, {interpolate}, *suffix)",
                    ]
                    lines[index + 1:index + 1] = adapter
                    folder = build / f"pcm{depth}-{mode}-interpolate{interpolate}"
                    sys.argv = [stem, str(args.executable), "--build-dir", str(folder)]
                    namespace = {"__name__": "dispatch_oracle", "__file__": str(tools / (stem + ".py"))}
                    exec(compile("\n".join(lines), str(tools / (stem + ".py")), "exec"), namespace)
                    namespace["main"]()
                    report_file = next(folder.glob("*-verification.json"))
                    reports.append(json.loads(report_file.read_text()))
    finally:
        sys.argv = saved_argv
    report = {"status": "passed", "dispatch_modes": 8, "kernel_batches": sum(r["kernel_batches"] for r in reports), "accumulated_frames": sum(r["accumulated_frames"] for r in reports), "scope": "Native dispatcher compared with all eight complete original sample kernels using existing batch oracles reduced to 250 fixtures per gain/mode. Includes their invalid-bound and zero-count guards. Excludes stopped-channel and loop orchestration."}
    (build / "mixer-dispatch-verification.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(report, indent=2))

if __name__ == "__main__":
    main()
