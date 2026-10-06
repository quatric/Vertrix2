# Direct actor geometry

actor_render_geometry.c composes descriptor bounds, actor clipping and source-offset recovery for original4ae3e0 direct-coordinate mode (EDX1). It ignores actor91 screen override, reads anchors from frame metadata3/4 and subtracts actor1e vertical displacement with signed-word wrapping. Scale advances resolve clipped source displacement. Unsuccessful calls preserve output.

All4,096 complete original preparation executions match visibility and, for2,593 visible cases, dimensions, source displacement and destination pointer. The fixture covers target clipping mode1, scales1..16, negative/positive positions, anchors/displacement and both screen-override bytes. All4,096 truncated storage requests preserve native output. No drawing calls are involved.

Other clip modes, screen-relative geometry, transform preparation, final drawing integration and playable Wii application remain unfinished. See actor-render-geometry-verification.json.
