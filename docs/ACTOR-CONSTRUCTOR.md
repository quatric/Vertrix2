# Original actor constructor

The interface creation code calls original4abd70 after allocating0x15c bytes.
tools/recover_actor_constructor.py verifies the executable hash, decodes the
complete routine4abd70..4ac122 and records every immediate memory write. All121
writes are checked against512 complete original executions without hooks.
actor-constructor-verification.json contains the reproducible exact write plan.

The constructor preserves11 bytes:56,57,96,97,102,103,111,112,113,14a,14b
(hexadecimal offsets). Allocation contents and these bytes must not be confused
with constructor-defined defaults. The oracle retains randomized prior storage
and compares all0x160 bytes, including the four bytes beyond the allocation.

Nonzero defaults include scale modes44/45=16, amounts4e/4f=50, stages52/53=13,
clip flag8e=1, flag94=2, mode95=1, masks118=00ffffff/11c=ff000000,
refresh120=1, source134=1, fields138/13c/144=1, and refresh index148=ffff.
The class metadata token158=517af4 is an original address, not a native Wii
pointer. Native class dispatch needs an explicit mapping when actor storage is
integrated. All timer counters/periods, modeled effect/transition values and
resource/frame/descriptor/handler fields are zeroed by this constructor.

The subsequent position setter and display-specific initialization have separate
whole-object execution evidence in ui-display-setup-verification.json. They
override source to0 and configure the already recovered VF-backed resource.
Allocation, full actor representation, list insertion and derived constructors
remain unfinished; the write plan alone does not establish a playable runtime.

actor_storage.c now implements all121 writes in instruction order using explicit
little-endian field access. It accepts existing base/derived storage, preserves
untouched bytes and bytes beyond the base, and rejects short/null storage before
writing. Field access supports widths1/2/4 with overflow-safe bounds checks.
The updated constructor verifier compiles this native module and compares its
complete storage with all512 original executions, checks every initialized
field through the native reader, and checks invalid-bounds preservation.
Use --build-dir for its temporary native library. Original address fields remain
identity tokens; a native resource/handler mapping is still required before actor
update integration. The module compiles as part of the verified Wii library.
