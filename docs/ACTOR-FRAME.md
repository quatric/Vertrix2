# Interface actor frame entry point

The base class token517af4 has virtual update+4=4ae150. Original scene list
4b6200 invokes that method for each handle in snapshot list order. The wrapper
calls4adf70, clearing actor120 only when global5bb710==1, then4ade20.
4ade20 processes interaction state through4ad870 and invokes the root handler,
following child chain108. It is not simply a direct handler call.

ui_actor_frame.c now implements this entry point for the recovered interface
actors with class517af4, interaction target104=0 and child chain108=0. These
are the constructor-defined values for the displays and companions. It stages
actor storage, clears refresh conditionally, resolves linked values in scene
order and dispatches either recovered six-phase handler family. Unknown class,
handler, interaction target or child chain fails before mutation. No-handler
actors still perform the original conditional refresh clearing.

The alternating and movement verifiers each compare12288 complete original
4ae150 executions without hooks with actor storage output; movement additionally
compares shared refresh. This covers24576 full frame cases, separate from the
same tests' direct-handler and lookup comparisons. Original4ad870 executes its
no-target path. A no-handler original comparison and unsupported-state native
preservation checks also pass. The wrapper's root-handler reuse across children
and interaction behavior still require recovery before supporting those states.

Full scene scheduling, other actor classes and rendering remain unfinished.
This entry point is a verified component of the requested port, not evidence
that the whole game is playable.

ui_scene_frame.c now connects interface actor storage to original4b6200 list
iteration: snapshot initial count, read each handle as reached, resolve stable
mutable storage, invoke the recovered virtual frame entry. Lookup reads the same
live scene storage, including earlier updates. Callbacks preserve list allocation
and count during a frame. Failures report0 after any preceding updates; this is
not an atomic whole-scene transaction. Other classes/interaction chains still
require recovery.

verify_ui_scene_frame.py executes complete original4b6200 without hooks over512
mixed scenes, covering6276 actor updates. It compares every entire actor buffer,
all shared refresh words and list order while exercising both recovered handler
families, idle actors, duplicate identities and conditional refresh clearing.
Fixtures supply direct image resource banks, with interaction104 and chain108
zero. Full scene construction, other actor classes, VF scene integration and
rendering remain outstanding.
