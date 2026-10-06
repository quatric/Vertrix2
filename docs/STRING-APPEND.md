# String append helper (0x45f540)

`vertrix_string_append` in `source/path_text.c` reproduces the leaf used
by 145 callers: copy the source string, then append the suffix string
(both copies run two bytes at a time in the original, which is just an
unrolled byte copy). Returns the destination on success; short or null
storage is preserved and reports zero (the original has no bounds and
would fault, so overflow is a native-only guard).

Verification (`tools/verify_string_append.py`, evidence
`docs/string-append-verification.json`): 1,024 complete original
executions pass over random source/suffix strings (including empties and
embedded nulls), comparing the returned destination, the full destination
buffer and the exact concatenation.
