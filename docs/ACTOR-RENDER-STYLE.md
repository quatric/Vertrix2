# Direct actor rendering state

actor_render_style.c extracts the state supplied by original direct preparation:
cycle flag8c to73a, draw flag93 to739, effect95 to00d, amount4e to00e,
stage52 to000, transform94 to00c and effect word48 to002. Format730 is13.
Actor clip bytes8e/8f become ffe/005; low byte80 supplies cycle7b8, and44
supplies scale738. Amount100 clears739 regardless of actor93.

verify_actor_render_style.py compares4096 original preparation-fragment
executions, including explicit amount100 cases. All extracted fields match;
actor bytes remain unchanged and invalid short storage preserves output. These
are direct-mode fragments, not complete4ae3e0 execution. Screen-relative mode,
interaction/border handling, remaining effect tables, clipping and rasterization
still require integration. The output connects to the existing recovered
render-dispatch flag representation without assigning guessed effect meanings.
