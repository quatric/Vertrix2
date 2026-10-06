# Attack-state entry (0x4522c0)

`vertrix_object_enter_attack` in `source/object_events.c` reproduces the
original attack dispatcher that the armed hold (`0x452250`,
`vertrix_object_arm_hold`) installs as handler `0x4522c0`.

Disassembly (mapped-image bytes):

```
004522c0 push ebp/ebx/ecx/edx/esi/edi; edx = eax (player)
004522d0 mov eax, [eax + 0x3b0] (opponent)
004522d6 mov ecx, [edx + 0x15c] (cursor); xor edi, edi
004522de mov bl, [eax + 0x4c5]; mov esi, [eax + 0x15c] (opp cursor)
004522ea test bl, bl; je cursor_tail (edi = 1)
0045230d mov bl, [eax + 0x4cc]; cmp bl, 1; je cursor_only
00452318 cmp [eax + 0x3f4], 0; jne cursor_only
00452321 call 0x43bce0 (eax = opponent, edx = player)
00452326 mov eax, edx; mov [edx + 0x3f4], 1 (player step)
00452332 call 0x43bd00 (eax = edx = player)
00452337 mov [esi + 0xb80/b84/b88], 1 (opp cursor flags)
cursor: edx = [cursor + 0x158]; eax = cursor; call [edx + 4]
004522fe cmp edi, 1; je tail (eax = player; call 0x43bbf0)
```

The `0x43bce0` / `0x43bd00` calls carry the entry-ebx passthrough in their
upper bytes (only `bl` is set here); the oracle and the Wii call sites
enter with zero there. The cursor dispatch abstracts the vtable load: the
native boundary takes the cursor handle plus the table dword at cursor +
`0x158`, and only those two registers plus the return compare. The
`0x43bbf0` tail observes the method's leftovers, so it runs with
`(object, table, 0, cursor)`.

Verification (`tools/verify_object_attack.py`, evidence
`docs/object-attack-verification.json`): 2,048 complete original
executions pass across dead-opponent / state-1 / step-set / full-attack
buckets — return value, every Calls call, the method cursor/table/return,
and every pool object compare — plus a short-storage guard. An oracle
self-check asserts the method call arrives with the vtable in edx and the
cursor in ecx, pinning the dispatch reading.
