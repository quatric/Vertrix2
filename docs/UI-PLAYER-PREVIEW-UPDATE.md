# Nested player preview update

Original `0x42b310` calls parent base update `0x4ae150` first, then virtual
updates for the three nonnull companion handles, then the three nonnull border
handles. Handles are read as each slot is reached; repeated handles are updated
repeatedly. These actors belong to the parent traversal rather than independent
scene roots in this recovered path.

`ui_player_preview_update.c` implements this traversal for parent class
`0x514814` and the supported base-class children. `ui_actor_frame` now exposes
an explicit base-call entry point that preserves a derived class token;
the original virtual entry point still validates base class `0x517af4`.
The linked-player lookup list is supplied separately from scene-root ownership.
The caller supplies the same timing, refresh, resources and shared random state
as the surrounding frame. A failure retains preceding successful updates.

The scene verifier executes complete original `0x42b310` without hooks in 512
cases after mixed scene updates. Parent and child bytes, shared refresh and
random cursor match across 2,664 nested updates, with null slots and repeated
handles. Parent fixtures use an idle callback and exclude interaction targets
and child chains. Other parent callback combinations remain restricted to the
already recovered base handlers. The existing 512 scene-update comparisons
remain included.

Nested drawing `0x42b290`, dispatch from the surrounding player classes,
complete scene ownership and scheduling, and full Wii gameplay still need
integration. This evidence does not establish a playable application.
