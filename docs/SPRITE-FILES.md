# Original sprite filename table

Original `0x4140d0..0x414118` loads `texte/SpriteFileName.ini` into the 23-slot
table at `0x533650`. The original archive contains 20 nonempty rows, followed by
three empty slots. `0x45dca0` selects entries using runtime settings; the filename
builder `0x45f540` prefixes them with the original `.\SPRITE\` string at `0x4fc188`.
For example, the interface bank at `0x5449fc` selects its row using `0x53bd09` at
`0x45dd21..0x45dd4d`. Recovering that settings value remains separate.

`vertrix_sprite_file` reads the table directly from the live VF archive and
returns the selected filename with the original prefix, case and spelling.
Missing trailing slots retain the empty filename and therefore return the prefix
alone. It supports the original file's slash-comment, space-indented and
backslash-delimited filename rows. It bounds table size and slot count and rejects
unsupported/malformed rows or insufficient output capacity without modifying
output. It does not emulate every behavior of the original generic INI parser.

The font stencil loader now resolves row 17 through this API instead of naming
Circle.spr directly. This also applies to generated interface artwork, which
uses the same stencil loader. Row 17 is the verified original default; other
runtime stencil selectors and the remaining startup resource graph still need
integration.

`tools/verify_sprite_files.py` compares all 23 original-table paths with full
execution of `0x45f540`, checks 434 insufficient-capacity preservation cases and
seven malformed tables, and supplies a renamed Circle resource through a
modified VF row 17. Both font stencil frames load successfully from the renamed
resource, proving table lookup drives loading. The existing stencil verifier
checks original frames 6/9 pixels and metadata after this change. The generated
artwork verifier separately compares the original builder, actor updates and
rendered frames. See `sprite-files-verification.json` for scope and results.

Path construction and supported-table reading are verified. Original generic
parser execution, runtime settings selection, full startup behavior and complete
gameplay are not established by these checks.
