# Actor image geometry

actor_image_bounds.c connects portable actor positions/modes to the recovered
original4b15e0 descriptor geometry. Resolved VF images provide source dimensions
and serialized origins. Actor fieldsE/16 provide signed-word positions; mode44
and override91 select scaling, with screen220/221 supplied explicitly. Descriptor
origins retain their original low-word interpretation. Bounds use the existing
verified measurement/anchor scaling implementation and return signed32-bit
position and size without changing actor storage.

verify_actor_image_bounds.py executes complete original4b15e0 unchanged in4096
cases and compares native storage/image bounds, varying modes0..16, screen
override settings, dimensions, wrapped positions and32-bit serialized origins.
Short storage preserves output. This is descriptor geometry evidence; it does
not include clipping, effect selection, rasterization or full actor rendering.
The image adapter can accept both generated display artwork and configured
companion VF frames, but their pixels remain owned by their respective banks.

actor_image_clip.c now connects measured actor image bounds to original4b1a99
clipping, reading clip mode8e and inclusive custom boundsA8..AE from portable
actor storage. Target dimensions and cached bounds remain explicit inputs. It
preserves original word wrapping, returns visible rectangles/dimensions/source
offset/clipped flag, and does not change actor storage. Invalid inputs and
offscreen sprites preserve output.

verify_actor_image_clip.py compares4096 original clipping executions,2409 of
which remain visible. It covers modes0/1 target clipping, mode2 bypass, mode3
custom actor bounds and other modes retaining cached bounds. Source offset is
the unscaled traversal offset. The additional actor_image_clip_offset adapter
converts skipped rows and columns using original4ae99f..4aea50 scale-table
advances for modes1..15, retaining the unscaled offset for mode16. All2409
visible cases also compare these offsets against original executable fragments.
Effects, complete draw preparation and pixel rasterization remain
separate integration work.
