# Recovered function names

Run `python3 tools/gen_names.py` to regenerate `docs/names.json` from the recovered headers. The lifting batch reads this map when combining verified routines. Recombine after regeneration to apply names to lifted declarations and stack constants.

Names identify recovered behavior; they are not original debug symbols. Keep executable addresses in generated header comments and lift metadata so renamed routines remain traceable. Unknown or ambiguous routines retain address names. Conflicting header associations are reported and excluded instead of selecting a name by file order. Reviewed decisions in `docs/function-name-aliases.json` select canonical names only when the exact header candidate set still matches. Each decision records its rationale and evidence files; stale or invalid decisions abort generation before the map is written.

A routine annotation must belong to its declaration. Do not infer ownership from arbitrary Markdown lines: these often mention callees or data addresses. In particular, `0x436fe0` is the board stone marker helper, whereas the stone effect arm routine is `0x453460`; `0x4f8d38` is a data table and must not receive a function name.

For annotations grouping multiple routines, only the first address is mapped to the first declaration. Additional variants need explicit individual annotations before they can be named safely.

Validate extraction with `python3 tools/test_gen_names.py`. This check exercises annotation boundaries, padded addresses, callback comments, and known recovered mappings without changing executable behavior.

The reviewed registry resolves thirty overlapping recoveries. `0x43f200` remains unnamed: `font_cell` and `image_bmp_keyed` recover different fragments, and neither proves a whole-routine name. Canonical aliases identify an original routine; they do not assert that native C functions with different boundary APIs are interchangeable.

Apply the map to existing verified chunks with `python3 tools/rename_lifted.py` (dry run), then `python3 tools/rename_lifted.py --write`. This changes exact lifted identifiers, stack constants, and metadata keys together. It validates declarations, definitions, dispatcher addresses, and unchanged metadata values before writing, and compares normalized C tokens to prove function bodies only change by identifier substitution. Reserved screen functions retain their explicit dispatcher entries. Run `python3 tools/test_rename_lifted.py` to validate that workflow.
