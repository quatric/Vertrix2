# Record slots

`record_slots.c`: a table of 12 byte records inside an object (122 records plus the current
record at `+0x5c0`). `0x412650`/`0x412690` copy a record to/from the current record (12 bytes
as three forward dword moves; a disassembler listing omits the `rep` prefix). `0x4120a0`
initializes the table, `0x4125e0` reads a field (selectors 0..7: signed byte, signed byte,
byte, signed word, byte, signed byte, signed byte, word), `0x412430`/`0x412510` step a field up
or down within fixed limits (field 7 wraps).

Verification: `tools/verify_record_slots.py`, 4,096 to 45,056 executions each; the whole
2 KiB storage compares. Evidence: `record-slots-verification.json`.
