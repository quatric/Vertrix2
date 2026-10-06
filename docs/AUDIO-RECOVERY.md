# Original audio assets

The original archive includes 13 WAV sound effects and 63 MP3 resources. All WAV effects are PCM format 1, mono, unsigned eight-bit samples. Sample rates are 11,025, 11,111 and 22,050 Hz; preserving the unusual 11,111 Hz value matters for later playback pitch and duration.

`vertrix_audio_pcm8` reads RIFF/WAVE chunks directly through the VF reader, retains sample bytes and rate, and owns its sample allocation. It validates RIFF bounds, chunk lengths and padding, PCM format, channel count, bit depth, block alignment and byte rate. Unsupported files and failed reads leave output unchanged. Unknown chunks are skipped. It does not extract or resample audio.

`tools/verify_audio.py` compares every WAV effect with Python wave decoding of the original extracted assets: all 13 effects and 149,076 sample bytes agree. Rate preservation, ready-output rejection, cleanup, repeated cleanup, missing names and rejection of all 63 MP3 resources passed. The report is `audio-verification.json`. PowerPC library compilation and source formatting checks also passed.

This is an asset loader, not recovered playback behavior. Wii audio output, mixing, resampling, MP3 decoding and original event-to-sound selection remain unfinished. No audible or hardware validation has been performed. Original playback routines still need disassembly; RIFF parsing uses the asset format rather than claiming reproduction of those routines.

## Wii PCM effect adapter

`wii_audio.c` connects VF WAV loading to ASND unsigned mono eight-bit playback. Sample storage is aligned and padded to 32 bytes with unsigned silence (128). The actual original sample count, not padded length, is passed to ASND, with the original sample rate as pitch. Callers select an exclusively owned voice and explicit left/right volumes. Each clip owns at most one voice; replay stops its previous voice and cleanup stops playback before freeing storage. ASND initialization and global lifecycle remain application responsibilities.

`make wii-audio` builds this adapter. PowerPC compilation with warnings as errors, formatting checks, and a scratch Wii ELF link exercising archive opening, PCM loading, ASND initialization, play, cleanup and shutdown passed. These checks do not establish audible output, DSP timing or hardware-safe shutdown behavior. Playback has not run on Wii or Dolphin. Original event selection and volume/voice scheduling remain unrecovered.

The archive also contains 29 XM music files; the original MusicFileName.ini identifies tracker music. The 63 MP3 resources must not be assumed to be the music library. XM playback and MP3 decoding require separate integration and fidelity verification.

## Connected PCM ownership verification

`tools/verify_wii_audio.py` compiles the actual VF, WAV and Wii PCM adapter sources together under AddressSanitizer and UndefinedBehaviorSanitizer. Recorded ASND/cache stubs check unsigned mono format, original rate and sample count, explicit volume arguments and stop-before-release ordering. All 13 effects preserve 149,076 samples and add 204 unsigned-silence padding bytes. The suite verifies aligned flush ranges, ready-output rejection, invalid slot and volume rejection without playback mutation, replay across slots, simulated ASND submission failure, recovery after failure, cleanup and repeated cleanup. There are 52 submissions and 39 stops; no sanitizer errors were reported.

These checks cover adapter behavior and data ownership. ASND/DSP implementation, completion timing, hardware concurrency and audible output remain unverified. The report is `wii-audio-verification.json`.

## Independent Wii MP3 decoding

`wii_mp3.c` loads encoded MP3 bytes directly from VF, provides libmad guard bytes, and uses an independent stream/frame/synth instance for each decode. Synthesized channels are rounded and saturated to signed 16-bit samples, packed explicitly big-endian for Wii ASND, and copied into aligned storage with zero silence padding. The result retains sample rate, mono/stereo channel count, sample-frame count, actual byte count and padded size. Unsupported changing formats, decode errors other than lost synchronization, allocation failure and missing resources leave output unchanged. Cleanup requires callers to stop any playback using the sample memory first.

`make wii-mp3`, PowerPC compilation with warnings as errors, formatting checks, and a scratch Wii ELF link against installed `-lmad -lfat -logc -lm` passed. No MP3 decode execution or audio comparison has yet been performed. This is a platform replacement for compressed audio decoding, not a recovered original codec implementation. Verification of every original MP3, encoder delay/trimming, output fidelity, ASND voice integration and original event/concurrency behavior remains necessary. No claim of completed voice playback is made.

## Executed MP3 decoding verification

`tools/verify_mp3.py` builds the real decoder sources from https://github.com/devkitPro/libogc with portable FPM_64BIT arithmetic for host execution, using a scratch copy. It compiles the actual VF and Wii MP3 adapter source together with that decoder and a cache flush stub. All 63 original MP3 files decode successfully: 1,661,760 sample frames. The suite checks byte/frame/channel consistency, 32-byte alignment, zero padding, unchanged output on reloading an owned buffer, cleanup and repeated cleanup. Per-file sample rates, channel counts, sample-frame counts and PCM hashes, plus decoder checkout revision, are recorded in `mp3-verification.json`.

This supersedes the earlier statement that no decoding execution had occurred. It does not establish equivalence to the original Windows decoder, encoder-delay handling, gapless trimming or Wii FPM_PPC arithmetic. No audible, DSP or hardware verification has occurred. The host decoder checkout is a test dependency outside deliverable source; its fixed-point selection is explicitly changed only in the scratch host build.

## Recovered original output-format configuration

The Windows output builder at `0x410ffd..0x41106a`, with the eight-bit branch at `0x41110d`, creates PCM format 1. Configuration byte +5 bit zero selects one or two channels, byte +4 bit zero selects eight or sixteen bits, and word +6 supplies sample rate. Block alignment is channels times bytes per sample; byte rate is sample rate times alignment. `vertrix_audio_output_format` reproduces this decision. It describes the original output configuration, not asset format or Wii hardware output rate.

`tools/verify_audio_format.py` executes those original instructions and compares all six fields with recovered C across 20,000 configurations, including rate boundaries and upper flag bits. Every case agrees. The original capability negotiation before the builder, including the observed conditional 22,050 Hz cap, is not yet reproduced. Playback/mixing, resampling and MP3 timing remain excluded. PowerPC compilation and formatting checks passed; evidence is in `audio-format-verification.json`.

## Recovered original mixer buffer sizing

`0x41108a..0x4110b3`, with stereo doubling at `0x41111e`, takes floor(configured sample rate / 20) sample frames, doubles for sixteen-bit output and again for stereo, then rounds byte length up to sixteen. `vertrix_audio_buffer_bytes` reproduces this sizing, including zero configuration and upper flag bits. The nominal chunk interval is about 50 ms; rounding means this is not an exact fixed-duration statement.

The existing executable comparison now checks both the format builder and this sizing in 20,000 cases each. All agree. Verification stops before Windows buffer allocation; callbacks, actual mixing, queue behavior and DSP scheduling are not covered. PowerPC compilation and source formatting passed.

## Recovered tracker sample delta decoding

Original `0x411280` integrates sample deltas in place. Sample-object +0 points to bytes, +8 holds byte count and +0x16 bit zero selects sixteen-bit samples. Eight-bit mode accumulates bytes modulo 256. Sixteen-bit mode accumulates little-endian words modulo 65,536; an odd final byte is untouched. The accumulator starts at zero for each sample. The XM loading path reads sample bytes at `0x411ba5`, then calls this decoder at `0x411bac`.

`vertrix_audio_delta_decode` preserves this behavior with explicit little-endian access for Wii. The executable verifier covers 20,000 randomized byte counts and flag values, both modes, trailing storage guards and zero counts; all agree. Native pointer validation additionally rejects null nonempty storage. PowerPC compilation and formatting checks passed. The report is `audio-delta-verification.json`. Full XM instrument loading, music tick/effect handling and mixer callbacks remain unfinished.

## Recovered XM pattern event decoding

Original `0x40e690` reads the pattern cursor at `0x530440`, writes five event bytes (note, instrument, volume, effect, parameter), and advances that cursor. If the first byte has bit seven set, it consumes that mask and reads only fields selected by bits zero through four, writing zero for absent fields. Otherwise it reads all five bytes including the first note byte. A null pattern cursor produces an all-zero event without advancing. Packed-mask bits five and six have no effect.

`xm.c` implements this behavior with bounded input and transactional failure on truncation. `tools/verify_xm.py` compares complete original instructions with native C for every cell in all 29 original XM files: 967 patterns and 610,816 events agree, including cursor advancement. Another 20,000 randomized events agree, and 112 truncated packed events reject without changing cursor or output. PowerPC compilation and formatting checks passed. `xm-verification.json` records the scope.

This covers event decoding only. Original instrument/sample mapping, note periods, tick scheduling, volume/effect execution, mixing and audible music remain unfinished. The verifier reads extracted original music for fixtures; runtime VF pattern resource ownership remains to be connected.

## Direct VF XM headers and patterns

`vertrix_xm_header` reads the original XM 1.04 title, order list, song length/restart, channel/pattern/instrument counts, flags, speed and BPM directly through VF. It preserves the original limits observed at `0x4113e0..0x411448` (version 1.04, at most 256 orders/patterns, 32 channels and 128 instruments). Additional bounded-input checks reject undersized or truncated headers rather than seeking outside the resource.

`vertrix_xm_pattern_load` follows original pattern records `0x411594..0x41166c`: packing type zero, word row count and packed byte size, variable header length, and original packed data. It owns one requested pattern at a time, validates event bounds before publishing, preserves output on failure and uses a null pointer for empty patterns, matching the recovered event decoder. It does not alter notes or effects.

`tools/verify_xm_assets.py` compares all 29 track headers and all 967 pattern records against original extracted resources: 1,034,658 packed bytes and 50 empty patterns agree. Ready-output rejection, out-of-range patterns, cleanup/repeated cleanup and missing/unsupported resources pass. PowerPC compilation and formatting checks pass. `xm-assets-verification.json` records this result. Event execution, instruments, music tick/effects and playback remain separate unfinished work.

## Direct VF XM sample resources

`vertrix_xm_sample_load` traverses original variable pattern/instrument/sample headers directly through VF and owns one requested sample. Original instrument sample-count limit sixteen is preserved from `0x411800`. It preserves the twenty-two-byte sample name, byte count, loop start/length, volume, finetune, type, panning and relative note. Original initial metadata `0x411ad8..0x411b52` sets base frequency 8,363, computes loop end with unsigned wrapping, and maps type bits 0x10/1/2 to native flags 1/0x10/0x20. The loader applies recovered original delta decoding as at `0x411bac`; sixteen-bit PCM stays explicitly little-endian.

`tools/verify_xm_samples.py` independently parses all 29 original XM resources and compares each sample through the VF loader: 718 instrument entries, 713 samples, 8,739,249 bytes, including 79 empty samples and 74 sixteen-bit samples. All metadata and decoded bytes agree. Ready-output rejection, sample-index boundaries, cleanup and repeated cleanup pass. PowerPC compilation and formatting pass; the report is `xm-samples-verification.json`.

The original calls `0x40acd0` after delta decoding to prepare samples for playback. That later repair/guard stage is not included here. Full instrument envelopes, sample interpolation, loop playback, music effects/ticks and mixing remain unfinished; loaded sample bytes must not be treated as a completed music engine.

## Recovered software-mixer interpolation guards

`0x40acd0` dispatches sample updates through `0x52f05c`; software-mixer registration copies the table beginning `0x4f651c` to `0x52f028`, making this callback `0x40c990`. The callback tests native sample flag 0x10. If set, it reads four bytes at loop start and writes those bytes at loop end, loading before storing even for overlaps. Otherwise, an unsigned-wrapping update offset plus byte count reaching sample length writes four zero bytes after the sample. Ping-pong flag 0x20 alone takes this non-forward-loop branch. Sample allocation at `0x40ac50` includes four extra bytes.

`vertrix_audio_sample_guard` reproduces the callback with bounded storage. A 20,000-case comparison executes the full original `0x40c990`, including overlap and arithmetic wrapping; all destination bytes agree. Out-of-range native requests preserve storage. The report is `audio-guard-verification.json`.

The VF XM sample loader now owns byte_count + 4 bytes, initializes the extra bytes, and applies this guard after delta decoding with the original full-sample update parameters. Rechecking all 713 samples across 29 tracks passes for metadata and prepared bytes, including guards. The preceding statement that this callback was excluded from loading is superseded. PowerPC compilation and formatting checks pass. This does not implement loop playback, interpolation arithmetic, envelopes, tick/effect scheduling or the complete mixer.
