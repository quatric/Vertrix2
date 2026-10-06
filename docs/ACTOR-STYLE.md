# Companion actor styling

Original471100 receives X/Y in AX/DX, sprite frame in EBX, and configuration
index in ECX, plus a sentinel and configuration pointer on the stack. It calls
4126f0 to read configuration[index*4+5cc], proceeding only when that value is1.
It allocates15c bytes, invokes the recovered4abd70 base constructor, and calls
4710d0 to initialize position with resource5449fc and the requested frame.
That helper sets clip flags8e=0 and8f=1. Descriptor/handler start at0.

Original4123d0 selects configuration+index*12 and writes:

| Record offset | Actor field | Width |
| --- | --- | --- |
| 2 | amount4e | byte |
| 4 | effect48 | word |
| 6 | stage52 | byte |
| 7 | flag94 | byte |
| 1 | mode95 | byte |
| 0 | flag93 | byte |
| 10 | cycle80 | zero-extended word into dword |
| 8 | cycle flag8c | byte |

actor_style_storage.c implements these writes without clamps, retaining all
other fields. verify_actor_style_storage.py compares2048 whole actor buffers
with complete original4123d0 execution without hooks, using independently varied
record indices and bytes. It also checks invalid-input preservation.

471100 subsequently sets flag110=1 when the configuration index matches the
sentinel, registers the actor through4b5e70 and returns it; disabled entries
return0 without allocation. The interface loop uses configuration indices64
upward, runtime position offsets, and sprite frame4fbfac (initialized34), then
applies its companion movement setup. Full471100 constructor execution,
configuration loading, companion VF binding and scene-wide registration remain
unfinished. No list identity assignment is inferred from this style operation.

sprite_actor_storage.c now implements original471100 initialization into caller-
owned portable storage. It validates availability and style bounds before any
mutation, preserves disabled storage, invokes the recovered base constructor,
initializes position/resource/frame/clip flags, applies the selected style, and
sets the sentinel flag. Native allocation and list registration remain external.
Configuration storage must remain separate from output actor storage.

verify_sprite_actor_storage.py executes the complete original471100 with only
4ca000 allocation supplied. Availability4126f0, constructor4abd70, positioning
4710d0/4adf20, styling4123d0, sentinel logic and original4b5e70 registration all
execute unchanged. Across2048 cases,808 enabled actors and all disabled outputs
match native results and complete storage, including untouched bytes. Original
registration count and appended handle are checked. Invalid native bounds/short
storage preserve outputs. Configuration loading and companion VF/scene updates
still require integration; this proof covers constructor behavior.

ui_companion_storage.c additionally implements the subsequent interface movement
setup46e022..46e0a3/46e1b2..46e232. Both sides use configuration index64+pair,
retain the recovered style and sprite frame, set linked ID23/24 in field4,
active124=0, source134=0, threshold58=pair+1, primary period10, secondary
period500 and handler450860. Original4ae110 stores position into128/12a and
parameters4f8c48/4f8c4c into12c/130. These parameters remain explicit inputs;
their meaning is not guessed.

The constructor verifier now compares512 complete original constructor-plus-
movement-setup executions with all native actor bytes. It varies offsets,
parameters, sprite frame and configuration, retaining padding and style fields.
Original allocation alone is supplied; constructor helpers, styling, original
list registration and movement setup execute unchanged. Native allocation/list
registration and VF descriptor binding remain external, and movement storage
dispatch still needs connection to the already recovered handlers.

ui_companion_update.c now dispatches all six original450860..4509d0 handlers
from portable actor storage. It explicitly decodes little-endian fields, invokes
the recovered movement implementation and writes only modeled fields, retaining
styling, resource binding and unrelated storage. Shared refresh remains a native
word array corresponding to original5bb714; invalid required refresh indices
fail before either actor or refresh storage changes. Linked lookup is still
external to this adapter.

verify_linked_movement.py compares the adapter with12288 complete original
handler executions without hooks. Every entire actor buffer and all shared
refresh words match, with5574 handler changes. It also checks invalid refresh
index and short-storage preservation. Companion constructor and handler proofs
are separate; scene-wide construction, lookup/scheduling and VF image binding
still require integration.

actor_lookup.c now shares original4b5eb0 linked-value resolution between display
and companion storage updates. ui_companion_storage_update_list reads the first
listed actor whose field0 matches companion field4, then dispatches the movement
handler with linked58/64. Invalid resolution preserves actor and shared refresh;
no match retains original waiting behavior. The movement verifier compares
all12288 original executions with duplicate IDs carrying different values,
including entire actor buffers and refresh storage. The alternating-display
verifier also passes12288 regression cases after adopting the shared helper.
Scene-wide allocation/order/scheduling and VF companion binding remain unfinished.

sprite_actor_image.c now binds companion frame descriptors to the configured
VF sprite bank and returns borrowed pixels plus serialized32-bit origins. The
actor's5449fc identity is mapped explicitly; descriptor IDs are local frame
indices, never dereferenced original addresses. Binding matches original4ac8a0
and4877f0 for470 VF frames across10 bank configurations. Whole actor bytes and
all independently verified frame pixels/origins match. Invalid frame preserves
actor and output values. Keep the owning bank alive until actors stop drawing.
This supplies the rendering input; effects, rasterization and scene-wide VF
resource ownership still require integration. The verifier now requires the
original executable through --executable as well as the VF archive.
