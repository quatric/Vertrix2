# Destination rectangle recovery

render_rectangle.c implements original0x492dc0 over a bounded32-bit surface. Each pixel becomes ((destination >>1)&0x7f7f7f)+prepared_half_color with unsigned32-bit wrap. Pixels and rows execute forward; overlapping rows therefore retain the original sequential behavior. The API validates dimensions and complete backing before mutation and treats an empty rectangle as successful.

The complete original oracle compares4,096 cases/35,745 processed pixels, including unaligned strides, overlapping rows, zero dimensions, arbitrary packed colors and untouched surrounding bytes. It asserts the original final pointer advances by height*stride, remaining height is zero and the inner counter follows the original empty-loop rules. An additional4,096 out-of-range calls preserve native storage. See render-rectangle-verification.json.

The native surface API does not expose original global cursors. Dispatch selection, other rectangle effects, actor rendering and playable Wii application remain unfinished.

Original0x492b90 destination palette conversion now matches4,096 complete original runs with arbitrary channel bytes, shifted row pointers and overlapping/unaligned rows. Native staging retains sequential writes for overlapping rows, then publishes the full backing only after successful conversion. Invalid map references preserve destination. This uses a temporary allocation the size of the destination backing; final actor rendering integration remains unfinished.

Original0x492cc0 fixed palette rectangle conversion now retains each destination palette row while selecting the three prepared16-bit indices. All4,096 complete original comparisons pass, including cross-row indices up to255 where backing remains valid, shifted palette maps, unaligned/overlapping rows and empty areas. Missing index backing preserves native destination. All three rectangle modes use the same verified forward traversal. Two original rectangle effects and final dispatch integration remain unfinished.

Original0x492e40 averages destination/fixed palette indices before map reads while retaining the destination row. Original0x492f90 first blends destination RGB with prepared half-color, then selects both palette row and indices from that RGB. Each matches4,096 complete original bodies, including overlapping rows and arbitrary packed colors. All five rectangle effects now have native implementations.

vertrix_render_rectangle32 selects them through the recovered original flag table. An additional20,480 flag-selected calls match full original bodies, with4,096 unsupported selections preserving destination. Formatting and125 portable PowerPC modules pass. This completes the five destination rectangle leaves, not actor rendering, full scene traversal or playable Wii application.
