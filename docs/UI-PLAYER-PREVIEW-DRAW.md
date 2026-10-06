# Nested preview drawing

`ui_player_preview_draw.c` implements original `0x42b290`: the parent itself
has no direct draw; nonnull companion slots are visited first, followed by
nonnull border slots. Each handle is read as reached. Supported base-class
children bind their explicitly mapped sprite bank and draw their `0x108`
chains through the existing recovered chain renderer. Repeated roots retain
repeated draws. A total draw budget bounds malformed chains across all slots.
Earlier completed bindings and draws persist on failure.

The parent class must be `0x514814`; resolved children must have the recovered
base class `0x517af4`. Direct geometry and renderer restrictions remain those
of `sprite_chain_draw`. Bank and actor ownership remain caller-managed.

The extended actor-render verifier compares complete original `0x42b290`
execution without drawing hooks in 512 cases and 9,639 nested draws using
original VF sprite fixtures.
Null/repeated roots and overlapping draw chains are included. The destination,
all actor bytes and parent storage compare, and native resolver visitation
matches the recovered order. Descriptor pointers normalize to native local
indices as in the existing actor draw comparisons.

Complete scene dispatch for player roots, actual constructed preview update
and draw frames, full player scheduling and playable Wii execution still need
integration. These fixture comparisons do not establish a full game port.
