# Board scene update recovery

`source/scene.c/h` recovers the board update tail `0x42fc56..0x42fd81`, not the entire enclosing `0x42fb60` handler. It preserves active-object parameter setters and virtual update, collection traversal, optional extra-object update, conditional layout, dynamic-list update/pruning and all ten native flag resets. Object/layout/list implementations remain explicit dispatch operations supplied by the runtime.

Original active-object setters `0x42a960` and `0x42a970` store low bytes at object `+0x16c/+0x16d`. Their input is the sign-extended board bytes `+0xa64/+0xa65`. The virtual update is vtable `+4`. Collection helper `0x4b23c0` skips null entries and reads each slot immediately before updating its object. Native traversal therefore also permits earlier updates to modify later slots.

Collection order is original board offsets `+0x220` (65), `+0x87c` (65), `+0x988` (5), `+0x9e8` (13), `+0xa2c` (13), `+0x324` (260), `+0xbdc` (65): 486 handles in total. The extra object at `+0xce0` updates afterward. Layout `0x430930` runs only when board `+0xb8c` is zero, evaluated after object updates. List operations `0x4b6200` and `0x4b5f50` target board `+0xcec`. Reset methods run in original order: `0x42f850`, `0x42f860`, `0x42ef00`, `0x42ef10`, `0x42ef20`, `0x42ef30`, `0x42ef40`, `0x42ef50`, `0x42f870`, `0x42f880`.

`tools/verify_scene.py` compares 512 randomized cases against original tail execution, totaling 218,618 matched dispatch operations and 99,328 matching reset bytes. Original collection traversal, active-byte setters and all ten reset methods execute normally; only object/layout/list operations are captured. Half the cases change a later collection entry and the layout flag during a virtual update, verifying live traversal and deferred gate evaluation. Signed-byte parameters, null slots, active/extra presence, layout suppression, and invalid native arguments are covered. Evidence: `scene-verification.json`. Wii compilation and formatting checks pass.

This proves dispatch order and flag-reset state changes. It does not verify the caller-supplied object/layout/list methods, preceding effect/descent handling, complete object ownership, rendering or the full game scheduler. The full playable port remains unfinished.

## Native reset storage

The original setters zero two 65-byte cell grids at board `+0x15c/+0x19d` (`0x42f8b0/0x42f8e0`), two five-byte column arrays at `+0x99c/+0x9a1` (`0x42ef60/0x42ef80`), four 13-byte row arrays at `+0x9a6/+0x9b3/+0x9c0/+0x9cd` (`0x42f7d0/0x42f7f0/0x42f810/0x42f830`), and the two active-parameter bytes at `+0xa64/+0xa65` (`0x42f890/0x42f8a0`). Their ten wrapper methods supply zero. Native scene storage mirrors these arrays and clears them after dynamic-list update/pruning, matching original execution. Their gameplay meaning is not inferred from names.

The differential verifier initializes every flag byte independently and compares all 194 bytes after each frame. Active parameters are supplied to the active object before reset, preserving that frame's values. These resets no longer require caller-dispatched leaf implementations.

## Original board object layout

`vertrix_scene_layout` recovers position writes throughout complete `0x430930`. Both 65-object cell collections use 24-pixel column/row spacing and signed cell offset bytes. Five incoming-column objects sit at origin Y +312; incoming row objects sit at origin X -24 and +120. The 260 smaller objects are four per cell, positioned at offsets (0,0), (12,0), (0,12), (12,12). The final 65-object collection at board +0xbdc is not repositioned by this routine.

For the first five collections, object mode 16 bypasses centering. Other modes add the original unsigned `(24 - measured_dimension) >> 1` to the initial coordinate, then retain the signed low word. Smaller quadrant objects do not center. Coordinates wrap as original signed words, and offset bytes are signed. Handles may alias; collection order determines the final coordinates. A pure resolver supplies object storage and dimensions calculated by the separately recovered resource measurement routine. An unresolved nonzero handle rejects further work after any already-completed positions. This API recovers position state; it does not reproduce renderer measurement-cache globals.

`tools/verify_scene_layout.py` runs the complete original function while intercepting only `0x4b14c0` to provide measured dimensions. 512 randomized boards produce 32,768 matching object-coordinate comparisons. Coverage includes both cell collections, incoming columns/rows, all quadrants, repeated/null handles, all original object modes, signed offsets, extreme origins/dimensions, wrapping and centering. Invalid scene/resolver/handle calls are rejected. Evidence is in `scene-layout-verification.json`. Wii compilation and formatting checks pass.

The scene update callback can now route original layout operation `0x430930` to this native routine. Object runtime storage, direct rendering integration, list operations, preceding board-update branches and the complete playable game remain unfinished.

## Dynamic object-list update and removal

The two list operations previously described as cleanup/finalization are now recovered precisely. `0x4b6200` snapshots list count at +8, reads handles through storage +4 and invokes virtual update +4 for each object. It does not clear the list. `0x4b5f50` compares each object's 32-bit +0x154 state (`0x4ac900`) with incoming EDX. The board update supplies zero. Matching entries are destroyed and removed, with the same index rechecked afterward.

Board construction at `0x42e8b8` initializes its +0xcec list through `0x4b5db0`, installing vtable `0x518344`. Removal slot +0x14 resolves to `0x4b5ee0`: invoke each removed object's virtual destructor +0 with EDX=2, then shift storage through `0x4d8950`. The original shift leaves stale pointers beyond the reduced count. Native `object_list.c/h` preserves these update/filter/destruction/shift semantics using caller-owned handle storage and object callbacks. Object implementations remain external. No allocation occurs. Callbacks must preserve list allocation/count; later handles and object states can change.

`tools/verify_object_list.py` runs actual original update, state getter, filter, virtual removal and memory-move routines, capturing only object update/destructor leaves. Flat 32-bit GDT descriptors are supplied because the original CRT memory move reloads ES. All 2,048 cases pass: 32,733 updated objects and 8,140 destroyed objects. Update/destruction order, post-update state matching, list count and all backing storage including stale tail match. Null handles/invalid native storage reject before update. Evidence: `object-list-verification.json`. Wii compilation and formatting checks pass.

The scene callback can route `0x4b6200` and `0x4b5f50` to these native operations. Complete runtime object implementations, allocation/insertion, preceding board branches, presentation/application and hardware game verification remain unfinished.

## Composed native scene frame

`scene_frame.c/h` connects the recovered board tail to native layout, active-object parameter setters, dynamic-list update/pruning, object-state reads and flag resets. A handle resolver supplies live native object storage, including measured dimensions, 32-bit state and the two active-parameter bytes. Actual virtual update/destructor handlers remain supplied by the object runtime. The composed path allocates nothing and owns no resources. Invalid/unresolved state returns failure; runtime failure can follow earlier progress and the scene tail's resets, so valid live handles remain required.

`tools/verify_scene_frame.py` compares this whole native composition with actual original `0x42fc56..0x42fd81`. Original layout, list traversal, state getter/filter, virtual removal/storage shift, and all resets execute normally. Only sprite dimensions and object virtual update/destructor leaves are supplied. Object updates alter states before the following list prune, exercising integration across those phases.

All 256 randomized frames pass: 16,384 object-state/position/active-parameter comparisons, 106,206 matching virtual operations and 1,972 matching removals. Complete backing list storage/count and every flag array match. Tests cover aliases across scene collections, optional active/extra objects, layout suppression, signed/wrapped positions, varied modes/dimensions and empty/populated lists. Evidence is in `scene-frame-verification.json`. Wii compilation and formatting checks pass.

This proves the recovered scene tail composition, not a full game frame. The enclosing board handler's preceding effects/descent branches, runtime object handlers/creation, input/player state machine, full presentation and actual Wii game verification remain unfinished.

## Board effect prefix

`board_effects.c/h` recovers `0x42fb60..0x42fbba`, preceding active-piece descent and the scene tail. Optional objects are original board +0xb70 and +0xb78, with parameters read from +0xb84 and +0xb88 as each branch is reached. Each parameter is copied unchanged to its object. Nonzero parameters select state 1; zero selects state 0. Entering from state 0 initializes flash to 1; leaving state 1 clears flash. Other prior states preserve flash before selecting the new state. The first object also clears its effect word on these transitions.

Enabled objects advance blink counter +0xdc by original elapsed milliseconds, with unsigned wrapping. A due timer resets its counter to zero and toggles flash as wrapping `1-flash`. First-object effect becomes 0xff38 when prior flash was zero, otherwise zero. The first enabled object resets primary counter +0xbc every update; the second does not. Disabled objects reset blink counter but retain primary counter. Both invoke their virtual update after these changes. The visitor can change the second parameter before its branch is read. No character/effect meaning is guessed.

Original methods execute normally in `tools/verify_board_effects.py`: state setters `0x42bab0/0x42b110`, toggles `0x42ba70/0x42b0f0`, and timers `0x4ac600/0x4ac610/0x4ac620/0x4ac510`. Only virtual updates are captured. All 4,096 cases pass, with 8,192 whole-object comparisons and 4,090 matching virtual updates. Absent objects, arbitrary parameters/state/flash values, zero/wrapped timers and live second-parameter changes are covered. Invalid native objects/handles are rejected. Evidence is in `board-effects-verification.json`. Wii compilation and formatting checks pass.

The effect prefix still needs composition with active-piece descent/locking and the scene tail using real object ownership. Full player/game scheduling, presentation and actual Wii verification remain unfinished.

## Falling-piece object transfer

`scene_lock.c/h` recovers complete `0x431c60` using actual block handles, complementing the earlier byte-board placement routine. The active piece supplies three child handles and signed-word pixel coordinates; original coordinate conversion identifies the column/top row. Current native API accepts board columns 0..4.

When top row is greater than -3, each child transfers into the corresponding in-board cell slot, or is destroyed with original flag 2 when outside rows 0..12. Placed objects receive original fields +0x93=0, +0x4e=50, +0x48=0. Each child slot clears after its transfer/destructor call. The piece is then destroyed with flag 2 and the active handle clears. Original return is 1, including pieces wholly below the board. Top <=-3 returns 0 and leaves all children owned by the piece destructor. The native API reports validation success separately from this original lock result. The caller supplies actual object destructors; runtime resolution failure may follow partial transfers. No allocation occurs.

`tools/verify_scene_lock.py` executes actual original placement and coordinate conversion, capturing only virtual destructors. All 4,096 cases pass: 6,865 transferred blocks, 6,927 destructor calls and 864 original failed-lock results. Cell handles, child ownership observed at each destructor, final child/active clearing, return result and whole block records match. Cases cover all five columns, sub-cell positions, origins, placements above/within/below the board and existing cell handles. Evidence is in `scene-lock-verification.json`. Wii compilation and formatting checks pass.

Real destructors/actor storage, integrating pixel descent with these transfers, complete enclosing board/player scheduling and the playable Wii application remain unfinished.

## Pixel descent with object transfer

`scene_descent.c/h` joins original per-pixel descent `0x42fc2d..0x42fc56/0x42fe81` with real handle-based locking. Occupancy comes from the scene's first 65 slots. Every pixel checks the original downward probe before movement. A clear pixel increments the signed-word piece Y and synchronizes the resolved live object's Y. Budget exhaustion retains the active piece; no early locking occurs. A blocked probe calls native object locking and sets original board failure flag +0xbd8 to 0 or 1 from the lock result. This flag remains unchanged while still falling. No allocation occurs.

The API requires live piece storage/handle resolution and valid storage-reaching probes. It rejects negative rows or out-of-board columns before calling occupancy code rather than accessing invalid memory. Failure may follow earlier progress. It does not assume ownership of objects; actual destructors remain supplied by the runtime.

`tools/verify_scene_descent.py` compares 2,048 randomized falls against actual original pixel-loop execution, downward probing, coordinate conversion and object locking. Only virtual destructors are captured. All comparisons pass: 5,637 block transfers and 2,349 destructor calls. Final pixel coordinates, active/child handles, failure flag, complete cell-handle storage, ownership observed at destruction and whole block records match. Budgets 0..600, sub-cell positions, positive original-style board origins, all five columns and varied occupancy are covered. Evidence is in `scene-descent-verification.json`. Wii compilation and formatting checks pass.

Timer/frozen-state integration, the complete enclosing board handler, actor implementations, player/game scheduling, presentation and playable Wii verification remain unfinished.

## Timed/frozen fall with live objects

`vertrix_descent_budget` factors the already recovered active-piece timer/frozen preparation from `descent.c`, retaining original wrapping counters, scaled step, blink transitions and child effect values. Existing byte-board descent uses the same helper. `scene_fall.c/h` publishes those child effect values to live objects before executing recovered handle-based pixel descent/locking. Consequently callbacks at destruction observe original pre-transfer effects, while placed blocks receive the original locking metadata resets.

`tools/verify_scene_fall.py` compares complete original active-piece slice `0x42fbba..0x42fc56`, including the out-of-line frozen/blink branches. Original timer, freeze, probe and locking routines execute; only object destructors are captured. All 2,048 cases pass, with 1,926 transfers and 786 destructor calls. Timers/frozen/flash state, positions, child effects/metadata, handles, ownership observations and failure flags match. Evidence is in `scene-fall-verification.json`. The existing descent verifier also passes after factoring: 6,000 timed updates, 10,000 pixel falls and 20,000 horizontal movement comparisons.

## Complete board handler composition

`board_frame.c/h` now composes complete original board handler `0x42fb60`: optional effect prefix, active-piece timer/frozen/descent/object locking, followed by scene object updates, layout, dynamic-list update/state pruning and ten flag resets. Caller-owned runtime object storage and actual virtual methods remain external. Elapsed time is a stable frame sample. Callbacks can change later board fields before their stage. No allocation occurs. Runtime failure can follow earlier progress; live valid object handles are required.

`tools/verify_board_frame.py` compares this composition with actual original execution from `0x42fb60` through its return. Only object virtual updates/destructors and resource dimension measurement are supplied. All recovered board orchestration, effect methods, timers, frozen transitions, pixel probing, object locking, layout, list removal/storage movement and resets execute normally in the oracle.

All 256 randomized frames pass: 16,640 object state/position/parameter/metadata comparisons, 105,939 matching virtual operations and 1,932 matching dynamic-list removals. Full scene slots, list storage/count, piece child ownership, failure flag, effect/descent timer state and all scene flag arrays match. Optional effects/active piece, paused/frozen modes, wrapped timers, normal/negative step words, layout suppression, object aliases and varied occupancy/dimensions are covered. Evidence is in `board-frame-verification.json`. Wii compilation and formatting checks pass.

This proves complete board-handler composition with supplied object leaves, not a playable game. Actual virtual object handlers/creation, player and character state machines, menus, complete rendering/presentation, real asset-driven runtime and Wii gameplay verification remain unfinished.

## Normal block virtual update

`block_update.c/h` recovers normal block handler `0x44c860`: forward-loop animation through `0x4ac1f0`, then descriptor binding through `0x4ac8a0`. The original binding uses resource pointer +0xb0, frame +0xb8, and stores the selected descriptor at +0xb4. Resource selector `0x4877f0` follows child resources/indices when resource kind +0x14 equals 1; otherwise it indexes the direct descriptor table. Native receives an independently resolved descriptor table in original frame order and uses the already recovered animation routine. Invalid storage/state rejects before mutating animation or descriptor. No allocation occurs.

`tools/verify_block_update.py` executes complete original `0x44c860` with no routine interception. All 1,024 whole-block comparisons pass, including 682 one/two-level linked resource cases, direct resources with non-1 kind values, zero periods, varied elapsed/counter values, frame wrapping and invalid native capacity. Evidence: `block-update-verification.json`. Wii compilation and formatting checks pass.

The method is now native, but actor creation/resource graph construction and VF sprite-to-runtime binding remain unfinished. Other virtual object handlers, player/game orchestration, menus, rendering/presentation and physical Wii gameplay verification are still required.

## Moving block handler

`block_motion.c/h` recovers complete moving-block handler `0x44c880`. It advances forward-loop animation, adds elapsed time to the primary counter, checks due time, consumes whole cycles and moves Y toward its target through original `0x4acab0`. The step is signed word +0x1a; current Y is +0x16, target +0x18. Cycle multiplication and candidate arithmetic wrap in 32 bits before signed clamp comparisons, then coordinates retain their low signed word. Negative or overflowing steps preserve original arithmetic rather than imposing a new movement rule. Arrival changes object +0x154 to normal handler `0x44c860`. Descriptor binding occurs for both due and not-due paths.

Native output preserves animation/motion/descriptor on invalid input. The supplied resolved descriptor order remains caller-owned. No allocation occurs. The object +0x154 field used by list filtering holds this handler value for these block objects; zero-handler removal must preserve that original role.

`tools/verify_block_motion.py` runs complete original handler and all its timer/movement/binding routines with no hooks. All 1,024 whole-object comparisons pass, including 682 linked-resource cases, zero primary periods, wrapped/full-width counters, signed step extremes, both travel directions, already-reached targets, mode switching and signed-word coordinate wrapping. Invalid native frame capacity preserves all outputs. Evidence: `block-motion-verification.json`. Wii compilation and formatting checks pass.

Actor dispatch/resource binding, remaining block/effect handlers, player/character logic, complete presentation and actual Wii gameplay verification remain unfinished.

## Block fade handler

`block_fade.c/h` recovers complete `0x44c960`. The handler sets object +0x93=1 every update, advances looping animation and the primary timer, and binds the selected descriptor. Due timer cycles are consumed before assigning byte target +0x4f=0 and signed step word +0x50=8. Transition helper `0x4ad580` operates on unsigned current byte +0x4e using wrapping 32-bit cycle/step arithmetic and signed clamping, then stores the low byte. Arrival changes +0x154 to handler `0x44c940`. Not-due frames retain target/step/handler. No allocation occurs; invalid input preserves all outputs.

`tools/verify_block_fade.py` executes the complete original handler, animation, primary timer, byte transition and binding with no routine hooks. All 1,024 whole-object comparisons pass, including 682 linked-resource cases, varied current/target values, zero/full-width primary periods, wrapped counters and invalid native capacity. Evidence: `block-fade-verification.json`. Wii compilation and formatting checks pass.

This handler switches to another live handler; it is not assumed to delete the object or complete board clearing. Native actor/resource binding, other transition handlers, player/character logic, full presentation and actual Wii gameplay verification remain unfinished.

## Alternating signed block effect

`block_pulse.c/h` recovers complete handlers `0x44c9d0` and `0x44ca40`. Both loop animation, advance the primary timer and bind the current descriptor. Due cycles select signed effect targets +200 and -200 respectively, with step 4, then apply original signed-word transition `0x4ad530`. Arrival switches to the opposite handler; not-due frames retain target/step/handler. The signed transition shares the already verified wrapping/clamping arithmetic with moving blocks. Invalid input preserves all outputs. No allocation occurs.

`tools/verify_block_pulse.py` runs both complete original handlers and their original transition/timer/resource routines without hooks. All 1,024 whole-object comparisons pass, including 682 linked-resource cases, timer wrapping, zero periods, full-width primary counters, signed effect bounds, already-reached targets and phase switching. Evidence is in `block-pulse-verification.json`. Wii compilation and formatting checks pass. Verification/build temporary files used project scratch storage after the host temporary directory reported insufficient space.

Actual block actor/resource binding, remaining object handlers, player/character state machines, menus, full presentation and physical Wii gameplay verification remain unfinished.

## Combined byte/word transitions

`block_combined.c/h` recovers complete handlers `0x44cab0/0x44cb50`. Both set object +0x93=1 and +0x95=3 every update, advance looping animation and the primary timer, and bind the current frame. Due cycles are consumed once and applied to both original transition routines: byte amount +0x4e (`0x4ad580`) and signed effect +0x48 (`0x4ad530`). First handler targets amount 100 with step 8 and effect 0 with step 16; second targets amount 0 with step 8 and effect 100 with step 8. Both must reach their targets before +0x154 switches to normal handler `0x44c860`. Arithmetic wraps before signed clamp comparisons and low-byte/word storage. Invalid input preserves all outputs; no allocation occurs.

`tools/verify_block_combined.py` executes both complete original handlers, animation, primary timer, both transition helpers and resource binding without hooks. All 1,024 whole-object comparisons pass, including 682 linked-resource cases, already-reached targets, arbitrary initial transition fields, timer wrapping/full-width counts, paired completion and handler switching. Evidence: `block-combined-verification.json`. Wii compilation and formatting checks pass.

Actual VF actor/resource binding, remaining object handlers, player/character logic, menus, rendering/presentation and playable Wii verification remain unfinished.
