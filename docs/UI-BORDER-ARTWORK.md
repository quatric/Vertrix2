# Additional generated interface image

Original `0x45e530` initializes one-frame resource `0x5466a4`, resolves stencil
frame 9 from `0x546538`, selects an interface frame from `0x5449fc` using global
`0x4fbf74`, applies solid stencil `0x4831b0`, and publishes the image. The verified
initialized value of `0x4fbf74` is 20. This resource is separate from the paired
solid/hollow images at `0x546618` and `0x546634`.

`vertrix_ui_border_artwork_build` implements that builder using already loaded
interface and stencil banks. Source frame and descriptor format are explicit.
It owns its generated image, retains wrapping source origins plus half the
stencil dimensions, and exposes a one-frame descriptor. Metadata word 0 remains
an unused native placeholder; pixels are owned through image.rgba. Free with
`vertrix_sprite_free`. Inputs remain borrowed, and failed construction preserves
output.

The artwork verifier executes complete original `0x45e530` with resource
construction and allocation supplied, while the original lookup, stencil and
publication routines execute. In eight configured-VF cases, generated pixels,
dimensions and descriptor words 1 through 9 compare. Word 0 is the original
allocation pointer and is checked through pixel access rather than pointer
identity. Existing paired-artwork and consecutive-frame checks also run.

The portable module compiles for PowerPC. The combined startup resource map now
owns and publishes this image under its original token. Its source selection is
part of the native selection storage and initializes to the verified value 20.
Recovering consuming actors, other startup builders and full gameplay remains
unfinished.
