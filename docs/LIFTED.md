# Lifted routines

`tools/lift.py` translates routines of `Vertrix2.exe` from x86 to C one instruction at a time
(`source/bonus_lifted.c`, generated, do not edit). It is how the regular state handlers of the
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
case disagrees and at least 15 of 60 cases complete.

`python3 tools/finalize_lifted.py Vertrix2.exe <reports> --cases 60` regenerates
`source/bonus_lifted.c` from the routines that pass and writes `docs/lifted-verification.json`.

## Result

490 routines kept (`docs/lifted-verification.json`, key `kept`), 180 lifted but with too few
completed cases (`weak`: pointer or buffer arguments the random inputs cannot supply), 6 failing
(`failed`: 0x4321b0 and 0x4b3340 take a virtual call the original does not, 0x4bbf30 enters in the
middle of a shared tail, 0x4b5630, 0x482d00 and 0x48b2f0 differ on globals or calls). The
translation refuses 113 routines: 106 call the Win32 import table (`call [0x52f0xx]`), 6 call a
routine with more than eleven stack arguments, one is recursive.

## Limits

- The lifted code reads and writes registers exactly as the original, so the callers must pass the
  registers the original receives (`eax`, `edx`, `ebx`, `ecx`, `esi`, `edi`, `ebp` and the entry
  `esp`, see `vertrix_lift_find`); only `eax` comes back.
- Pointers into an object that are not the object's handle are global memory to the lifted code.
- The routines are statement-for-statement translations, not readable recoveries; they are the
  working specification until a hand recovery replaces them.
