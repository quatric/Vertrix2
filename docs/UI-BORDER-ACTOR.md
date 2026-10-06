# Actor setup for the additional interface image

Original `0x42b370` creates three actor pairs associated with a player. The border
actor in each pair uses generated resource `0x5466a4`. `ui_border_actor.c` recovers
its base constructor plus setup fragment `0x42b4d7..0x42b55b`: source frame zero,
timer 12, amount 50, effect 4, enabled effect flag, anchor zero, supplied linked
identity and no cached source pointer. Constructor-defined fields are written;
all other bytes retain their prior values. Positions are explicitly signed words.

The preceding selection fragment `0x42b3ac..0x42b3d0` chooses three positions
from the original tables. Left x values are 143, 133, 153; right values are 477,
467, 487. Both use y values 129, 147, 147. Zero side selects left and any nonzero
byte selects right. `vertrix_ui_border_actor_position` exposes that selection.

`tools/verify_ui_border_actor.py` executes the original base constructor and
complete setup fragment without hooks and compares every byte of extended actor
storage in 2,048 cases. Signed coordinates and linked identities vary, and short
storage failures preserve output. It separately executes the actual position
selection for all 256 side bytes and all three indices, producing 768 comparisons.
See `ui-border-actor-verification.json`.

The native constructor accepts caller-owned storage. Allocation, attachment to
the player, the other actor of each pair, scene registration, subsequent image
binding and complete player updates remain separate. This recovery does not
establish the entire `0x42b370` routine or playable gameplay. The component
compiles for PowerPC and follows the project's formatting rules.
