# Correct original executable memory mapping

The verified Borland executable's `.bss` section starts at RVA `0x11f000`, has
uninitialized-data flag `0x80`, no raw-data file pointer, and a declared raw size
of 695,296 bytes despite containing no file-backed data. `pefile`'s generic
`get_memory_mapped_image` result places bytes from file offset zero into that
range. Those are executable-file bytes, not the section's loader initial state.

`tools/original.py` now builds the oracle image through `original_image`: it
preserves initialized section payloads and explicitly zeroes uninitialized
sections with no raw-data pointer. Bounds are checked against SizeOfImage. This
matches the uninitialized section/file-backing distinction documented in the
[Microsoft PE specification](https://learn.microsoft.com/en-us/windows/win32/debug/pe-format).
It does not run the Windows process loader or emulate all its behavior.

The practical correction is that `0x53bd09` starts at zero, selecting damier.spr;
the prior value 13 was a harness artifact. The first-source selector `0x5466c4`
also starts at zero. Initialized settings `0x513c4d..0x513c5f` and source frame
`0x4fbfac` retain their actual initialized bytes. The native sprite-selection
initializer records these verified loader values, not a guessed configuration.

`tools/verify_original_image.py` compares every initialized section payload
against file-backed bytes, all 695,296 uninitialized bytes against zero, and the
oracle's interface selector after its RNG initialization. It includes a
regression check that the uncorrected pefile mapping yielded 13.

`tools/recheck_original.py` discovers executable original-oracle verifier entry
points, supplies their declared inputs and records logs/results. Helper modules
without their own executable entry point are listed separately; their tests run
through parent verifiers where applicable. Resume retains successful checks and
runs failed or newly resolvable checks. It does not infer pass results from merely
importing a module. See `original-image-verification.json` and
`original-recheck.json` for the current correction audit and its scope.

Old reports generated with the incorrect mapping are historical evidence.
The correction audit establishes only the checks listed in its results; it does
not turn component evidence into proof of full game startup or Wii gameplay.
