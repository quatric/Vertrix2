# Rendering operation selection

vertrix_render_operation recovers original0x4af786..0x4af86d after a valid pixel kernel and row/image binding. Rule zero with no alpha override uses a fast copy only for group0 and traversal indices0/1. Rule zero with an alpha override checks the original alpha table when group<2; zero table entries fall back to prepared image traversal. Every other supported selection requires preparation before calling its selected image operation.

The returned addresses are original evidence identifiers, never callable native pointers. The comparison executes original decisions and observes the actual preparation/drawing call boundaries across1,536 cases. It supplies those calls rather than executing their bodies. Another1,536 invalid-rule calls preserve native output. This verifies operation selection only; full actor dispatch, preparation, transforms and playable application remain unfinished. See render-operation-verification.json.
