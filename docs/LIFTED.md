# Lifted routines

`tools/lift.py` translates routines of `Vertrix2.exe` from x86 to C one instruction at a time
(`reference/lifted/bonus_lifted.c`, generated, do not edit; a reference, not recovered source). It is how the regular state handlers of the
bonus effects, the HUD and many other unported routines are brought across without a hand
recovery. A lifted routine keeps the original's registers, flags, jumps, calls and memory accesses:

- registers and flags are C variables, set as each instruction sets them;
- jumps are gotos (a backward jump counts against a step limit so bad data cannot hang the caller);
- `[reg + disp]` reads and writes go to the object the register names (`resolve`), the stack is a
  shadow buffer, everything else is global data (`global`, `global_write`);
- every call to a routine that is not itself lifted, and every virtual call, goes through the
  `VertrixCalls` boundary with its registers and stack arguments;
- `fs:[0]` (the exception chain) is global data.

`tools/verify_lifted.py` is the evidence: each routine runs in the original under Unicorn with
random objects, random entry registers and stack arguments and stubbed callees, then natively on
the same inputs. The ordered call log (registers and stack arguments), the virtual calls, the
result, every object and every global written must agree. Cases on which the original faults, does
not finish or follows a pointer into an object are skipped and counted. A routine is kept when no
case disagrees and enough cases complete.

`python3 tools/finalize_lifted.py Vertrix2.exe <reports> --cases 60` regenerates
`source/bonus_lifted.c` from the routines that pass and writes `docs/lifted-verification.json`.

## Result

706 routines kept (`docs/lifted-verification.json`, key `kept`): they pass the comparison in
the final form of the file (30 cases each, at least 10 completing). 195 are lifted but
too few cases complete (pointer or buffer arguments the random inputs cannot supply), 6
fail. The translation refuses 106 routines that call the Win32 import table, 6 that call a routine
with more than eleven stack arguments and one that is recursive.

## Plan

The translations are the specification for hand recovery: name each routine, untangle it into
readable source under `source/`, and verify the recovery against the original as the other modules
are. The lifted file then stops being needed.

## Limits

- The lifted code reads and writes registers exactly as the original, so the callers must pass the
  registers the original receives (`eax`, `edx`, `ebx`, `ecx`, `esi`, `edi`, `ebp` and the entry
  `esp`, see `vertrix_lift_find`); only `eax` comes back.
- Pointers into an object that are not the object's handle are global memory to the lifted code.
- The routines are statement-for-statement translations, not readable recoveries; they are the
  working specification until a hand recovery replaces them.
