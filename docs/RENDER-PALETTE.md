# Original palette drawing

render_palette.c implements the unchanged pixel conversion kernels48d740 and
48d7f0. Both quantize source RGB to a six-bit-per-channel lookup index using
original54b800. The low lookup byte selects a channel map through54cdc8.
48d740 reads red, green and blue indices from the lookup's other three bytes;
48d7f0 instead uses the full words54d5dc/de/e0. The output is packed RGB without
alpha. Tables are borrowed caller-owned native arrays, never original pointers.
Bounds validation preserves output on failure. Fixed word indices can exceed
255, matching original byte addressing when the supplied map storage permits it.

verify_render_palette.py compares8192 cases against the original executable
without instruction hooks, using randomized lookup entries, channel maps,
source pixels and full-word fixed indices. Both kernels match. The verifier
supplies tables explicitly; it does not prove original palette generation,
scene-specific table selection, or complete actor rendering. Those remain
required for faithful full-game integration.

The initial convenience conversion accepts256-byte rows. The explicit layout
API now accepts the original475419 pointer layout:201 rows separated by101
bytes. It validates row selection and arithmetic before addressing, including
cross-row fixed word indices when backed by enough storage. Additional4096
original kernel executions match conversions through the recovered channel
table. Lookup entries are supplied fixtures in this comparison; it does not
establish the original RGB-to-lookup generator.

The generator475090 iterates262144 colors, deriving RGB channels as
four times the three six-bit indices. It calls474560 RGB-to-HSV, then scans101
channel-map entries for each channel, preserving the first minimum difference.
The resulting lookup packs the selected red/green/blue indices in bytes3/2/1
and the map row in the low word. It also builds a separate262144-byte hue
table, and255 auxiliary color entries using474910. The complete generator
verification is described below; ordinary HSV conversion is insufficient
evidence because the original software arithmetic has observable rounding.

palette_lookup_entry now implements the475183..47525c nearest-channel scan.
Given the original map selector and RGB channels, it visits101 entries for each
channel and changes the selected index only on a strictly smaller absolute
difference. Equal distances retain the first index. The packed output preserves
original red/green/blue byte order and map selector. Invalid rows or short
storage preserve output. verify_palette_lookup_entry.py compares4096 unchanged
original fragment executions:2048 using the recovered original channel table
and2048 using arbitrary tables with duplicates and nonmonotonic values. This
proves lookup assembly once RGB-to-HSV has supplied the map selector; it does
not prove the full262144-entry generated table yet.

palette_color.c now recovers original474910 HSV conversion for hue0..360 and
saturation/value0..100. Single-precision stages and original software subtraction
rounding matter: ordinary IEEE subtraction gives25 instead of26 for the green
and blue channels at HSV(0,80,50). The portable implementation reproduces the
original aligned-mantissa rounding before normalization. Its valid range keeps
all subtraction operands nonnegative and ordered.

The same module builds the201-by101 channel table5468b0 from original474cd0,
including the triangular extension of its first101 rows. Verification executes
complete original474910 in15977 cases and complete474cd0 without instruction
hooks, matching all20301 table bytes. Scene table selection still needs
recovery. Native compilation does not establish Wii
hardware floating-point equivalence.

palette_rgb now implements complete474560 RGB-to-HSV for RGB0..255. It
normalizes channels through the original double constant1/255, uses the
recovered software subtraction before saturation/division, preserves red-first
maximum selection, truncates hue, and rounds saturation/value half upward.
It returns the original chromatic/grayscale flag separately. Verification
executes complete474560 with its software math helpers unchanged:all262144
quantized RGB inputs used by475090 plus256 grayscale and8192 random inputs
match, for270592 cases. This proves the lookup selector inputs for the entire
builder domain. Full builder and auxiliary hue-table comparisons are described
below; other scene table selections remain unfinished.

palette_tables.c now assembles the complete475090 RGB lookup, hue table,
channel table and255 auxiliary entries as owned native data. The auxiliary
hue sequence uses integer i*359/254; chromatic lookup hues use h*254/359+1,
with grayscale stored as0. Outputs must be zero-initialized; allocation failure
and occupied output preserve state, and free releases allocations and clears
the structure. Approximately1.3MiB is retained per instance. Original global
pointer tables are represented by the explicit rendering layout rather than
serialized executable pointers.

verify_palette_tables.py executes complete475090, replacing only calloc.
All262144 lookup entries,262144 hue bytes,20301 channel bytes and255 auxiliary
entries match the portable builder. The default binding from475495 is exposed
by palette_tables_pixel, using the recovered201-by101 channel layout. Additional
pixel comparisons execute original48d740/48d7f0 using the actual tables and
pointer selection left by the original builder. Other scene pointer selections,
full drawing traversal and the playable application remain unfinished.

palette_tables_cycle recovers4754e0 auxiliary pointer cycling as bounded native
lookups. The original first pointer selects255 constant100 entries at54c9cc;
the other255 pointers select consecutive auxiliary entries at54c1d4. Each cycle
adds cycle*4 to every pointer. Auxiliary indices255..509 read the zero-filled
tail established by474cd0. A boundary detail matters: index0/cycle255 reaches
adjacent global54cdc8, not another constant100. That value is an explicit opaque
input to the native adapter, never a dereferenced host pointer. Complete render
preparation must supply its current selected-table identity when that case occurs.

verify_palette_cycle.py executes complete4754e0 without hooks for all256 cycles,
resolving all256 resulting original pointers each time. All65536 entries match
native lookups using the original memory layout, arbitrary auxiliary values,
zero tail and an explicit adjacent-global value. Full4ae250 preparation also
selects weighted channel tables and color-specific values; those paths remain
unfinished.

render_preparation.c now composes complete4ae250 decisions. Format mismatch
updates fixed-color state through render_color_prepare. Flag739 exactly1
selects the source/destination byte and word percentage rows; otherwise those
bindings retain prior state. The signed word002 becomes a pointer-table shift,
with no row clamping. Flag73a exactly1 enables auxiliary cycling; the cycle
describes the recovered4754e0 binding. Native weight views borrow the caller's
tables; selected map shifts and cycling still need resolution by pixel dispatch.
Invalid inputs preserve the whole prior preparation state. The wrapper supports
the original13 color-bank indices and percentage amounts0..100; other original
byte values require explicit additional backing data rather than out-of-bounds
host reads.

verify_render_preparation.py executes complete4ae250 unchanged in4096 consecutive
cases, including actual4754e0. Fixed-color globals, conditional weight bindings,
signed map-pointer selection and all256 auxiliary pointer shifts match the
native decisions, preserving previous color and weight state when the original
does. Full actor4ae3e0 draw preparation, map-view resolution, traversal and the
playable application remain unfinished.

palette_map.c now resolves default channel-map pointer slots after signed
4ae2de shifting. Original475400..475441 initializes200 prefix pointers to
row0,201 normal pointers to rows0..200, and200 suffix pointers to54b798.
That suffix address is exactly5468b0+200*101:the last already recovered channel
row, not separate unknown data. Relative slots-200..-1 repeat row0 and201..400
repeat row200. The native view borrows table bytes and bounds channel accesses;
uninitialized/unbacked slots outside this layout reject without changing output.
The shifted pixel adapter connects these views to original48d740/48d7f0
lookup or fixed-channel conversion, avoiding executable-pointer arithmetic.

verify_palette_map.py executes the original pointer-layout initializer fragment
unchanged and compares all601 backed relative slots. It then compares4096
complete original pixel kernels through shifted bindings using arbitrary
channel bytes, lookup values and fixed indices. Prefix, normal and suffix
selection all match. These are map/pixel integration proofs; full actor draw
preparation, effect dispatch and a playable application remain unfinished.

render_palette_half_pixel implements complete48dba0. It quantizes source and
destination to their original lookup entries, averages each pair of channel
indices with integer truncation, then resolves all three averages through the
SOURCE lookup's channel-map row. It does not average the resolved RGB colors,
and it does not select the destination's row. Both distinctions affect original
colors. Explicit layout arguments support the original101-byte row spacing
and other already-supported regular map layouts. Invalid storage preserves output.

verify_palette_half.py compares8192 complete original kernel executions without
hooks:4096 use the recovered complete palette tables and4096 use arbitrary
lookup/channel values. Source alpha, destination alpha, differing row selectors
and odd/even channel sums vary across fixtures. The complete table generator
was proved separately; this verifier supplies its output as original kernel
inputs. Full scene selection, traversal and actor rendering remain unfinished.

render_palette_weighted_pixel implements complete490340. It uses the source
lookup's channel-map row and feeds each source/destination channel INDEX through
its selected256-byte weight table (original55f1f0/55f1f4), sums the returned
bytes, then resolves the sum through the source map. It preserves cross-row
addressing for sums above255 when supplied storage contains those bytes;
invalid storage and missing weight tables preserve output. The API borrows the
two explicit weight tables, avoiding an unproved assumption about their builder.

verify_palette_half.py now also compares8192 complete490340 executions without
hooks:4096 use the recovered palette with percentage-table fixtures covering
amounts0..100, and4096 use arbitrary palette/weight bytes, including index sums
up to510. These fixtures prove the kernel's table use, not the original weight
table generator. Original4ae250 selects weight rows at558cf0 + amount*256 and
558cf0 + (100-amount)*256 when flag739 equals1; its complete state preparation,
full drawing integration remain unfinished.

render_weights.c recovers original480730..4807e8 percentage-table construction:
101 rows of256 byte entries at558cf0 and101 rows of512 word entries at55f1f8.
Both use integer value*amount/100 with truncation. Words are native numerical
values, preserving Wii endianness independently of original serialized memory.
Its borrowed row selector implements4ae26d..4ae2b9 for valid amounts0..100;
invalid selection preserves both outputs.

verify_render_weights.py executes the original initialization loops unchanged
and compares all25856 bytes and51712 words. It also executes original weight
row selection for every valid amount, comparing both selected byte rows.
verify_palette_half.py now feeds the generated native weight rows into its
4096 recovered-palette weighted-kernel comparisons, alongside4096 arbitrary
weight fixtures. Full render preparation remains unfinished; the game is still
not playable.

render_weights_build now covers complete480730, including alpha tables at
578600 and588600. Both contain65536 bytes. The first stores alpha*channel/255;
the second writes the same values into row255-alpha, reproducing the original
descending address traversal. Expanded native storage contains all four tables;
callers must use the updated structure size. Complete original480730 executes
without hooks and all percentage plus131072 alpha bytes match. Percentage row
selection and the palette blend comparisons still pass with the expanded
structure. This initializer does not itself establish full alpha-kernel or
scene rendering integration.

render_color.c recovers fixed-color preparation4ae2ff..4ae3b3 for the format
mismatch path. Explicit banks correspond to54b808 lookup colors and54b83c RGB
colors;54b804 supplies the hue table. It extracts fixed channel indices,
stores the complete color, prepares truncated half-color, extracts RGB bytes,
and resolves the quantized color's hue. It does not decide whether the original
format comparison takes this branch. All native outputs are numerical values
and no original address is dereferenced. Short banks/hue storage preserve output.

verify_render_color.py compares4096 unchanged original fragment executions,
varying all13 adjacent-bank entries,32-bit lookup/color values and hue bytes.
Every modified fixed-color global matches the corresponding native field.
The original creation of these13 color-bank entries and complete4ae250/4ae3e0
preparation remain required for full rendering integration.

render_color_bank.c now recovers complete474e00. It initializes the original13
lookup colors and12 format colors, applies the destination mask ordering through
the already recovered481e10 image conversion, and resolves the13 RGB colors
through the explicitly supplied selected channel-map row100. No fixed default
row is assumed because54cdc8 can select another map. Initial channel indices
are at most100, so101 bytes suffice. Invalid inputs preserve the output bank.

verify_render_color_bank.py compares256 complete original474e00 executions
without hooks, including original source-format initialization and481e10.
All13 lookup entries,13 resolved colors and12 format colors match across all
RGB32 and RGB565 mask permutations with varying row bytes. Complete render
state preparation, traversal and playable application integration remain
unfinished.
