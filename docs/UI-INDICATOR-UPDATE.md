# Player companion indicator updates

`ui_indicator_update.c` connects the recovered five-phase `linked_indicator`
behavior to serialized actor storage. It maps original byte, signed-word and
DWORD fields explicitly, preserving all other bytes. The list wrapper uses
the original first matching identity lookup. `ui_actor_frame` dispatches
callbacks `0x44ff90`, `0x44fff0`, `0x450040`, `0x4500b0` and `0x450100` through
this adapter, making them available to the existing scene update path.

The callbacks show the selected preview slot when the linked player's signed
state reaches its threshold, transition its amount toward 100, and fade it
back to zero on the original state conditions. Timer wrap and zero-period
behavior use the already recovered timer and byte transition implementation.

The updated linked indicator verifier compares entire serialized actors with
original callback execution in 10,240 cases and checks short-storage rejection.
The scene verifier executes original `0x4b6200` without hooks in 512 mixed
scenes, covering 6,059 actor updates with all seventeen currently supported
callbacks and idle actors. Actor bytes, list order and shared refresh storage
match. Fixtures exclude interactions and child chains. Final companion image
binding, complete player construction and gameplay remain
unfinished; these checks do not establish a playable port.
