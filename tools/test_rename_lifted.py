"""Regression fixtures for identifier-only verified chunk renaming."""
import json
from pathlib import Path
import tempfile
import unittest

from rename_lifted import plan_renames, readable_names, rename_tokens, token_digest


class RenameLiftedTests(unittest.TestCase):
    def fixture(self, root, names=None):
        (root / "source").mkdir()
        (root / "tools").mkdir()
        (root / "docs" / "lift").mkdir(parents=True)
        names = names if names is not None else {"0x401000": "vertrix_first", "0x402000": "vertrix_second"}
        (root / "docs" / "names.json").write_text(json.dumps(names))
        metadata = {
            "alpha": {"address": 0x401000, "stack": 8, "arguments": 0, "callees": {"0x403000": [1, False]}},
            "beta": {"address": 0x402000, "stack": 12, "arguments": 1, "constants": [17, 29]},
        }
        (root / "docs" / "lift" / "whole_0.json").write_text(json.dumps(metadata, indent=1))
        header = """enum { LIFTED_ALPHA_STACK = 8, LIFTED_BETA_STACK = 12 };
/* Original 0x401000. */
uint32_t lifted_alpha(void);
/* Original 0x402000. */
uint32_t lifted_beta(void);
"""
        body = """uint32_t lifted_alpha(void)
{
    uint8_t stack[LIFTED_ALPHA_STACK];
    /* lifted_alpha and LIFTED_ALPHA_STACK in comments stay untouched. */
    const char *example = "lifted_alpha";
    return LIFTED_ALPHA_STACK + 17;
}
uint32_t lifted_beta(void)
{
    uint8_t stack[LIFTED_BETA_STACK];
    return LIFTED_BETA_STACK + 29;
}
"""
        (root / "source" / "lifted_whole_0.h").write_text(header)
        (root / "source" / "lifted_whole_0.c").write_text(body)
        (root / "source" / "lifted_dispatch.c").write_text(
            "routines[] = {{0x401000, lifted_alpha, 8, 0}, {0x402000, lifted_beta, 12, 1}};"
        )
        return metadata

    def test_plan_preserves_bodies_and_metadata_without_writing(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            metadata = self.fixture(root)
            before = {path: path.read_bytes() for path in root.rglob("*") if path.is_file()}
            staged, changes = plan_renames(root)
            self.assertEqual(changes, {"alpha": "first", "beta": "second"})
            self.assertEqual(len(staged), 4)
            self.assertEqual(before, {path: path.read_bytes() for path in before})
            body = staged[root / "source" / "lifted_whole_0.c"]
            self.assertIn('"lifted_alpha"', body)
            self.assertIn('/* lifted_alpha and LIFTED_ALPHA_STACK', body)
            renamed_meta = json.loads(staged[root / "docs" / "lift" / "whole_0.json"])
            self.assertEqual(list(renamed_meta.values()), list(metadata.values()))
            for path, replacement in staged.items():
                path.write_text(replacement)
            self.assertEqual(plan_renames(root), ({}, {}))

    def test_swaps_are_simultaneous(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            self.fixture(root, {"0x401000": "vertrix_beta", "0x402000": "vertrix_alpha"})
            staged, changes = plan_renames(root)
            self.assertEqual(changes, {"alpha": "beta", "beta": "alpha"})
            body = staged[root / "source" / "lifted_whole_0.c"]
            self.assertIn("return LIFTED_BETA_STACK + 17", body)
            self.assertIn("return LIFTED_ALPHA_STACK + 29", body)
            for path, replacement in staged.items():
                path.write_text(replacement)
            self.assertEqual(plan_renames(root), ({}, {}))

    def test_collision_and_stale_metadata_rejected_before_writes(self):
        mutations = [
            ("docs/names.json", lambda text: json.dumps({"0x401000": "vertrix_BETA", "0x402000": "vertrix_beta"})),
            ("docs/lift/whole_0.json", lambda text: text.replace('"alpha"', '"stale"', 1)),
            ("docs/lift/whole_0.json", lambda text: text.replace('"stack": 8', '"stack": 9', 1)),
            ("source/lifted_whole_0.h", lambda text: text.replace('0x401000', '0x401001')),
            ("source/lifted_whole_0.c", lambda text: text.replace('LIFTED_ALPHA_STACK', 'OTHER_STACK')),
            ("source/lifted_dispatch.c", lambda text: text.replace('lifted_alpha, 8', 'lifted_alpha, 9')),
            ("source/lifted_dispatch.c", lambda text: text.replace('lifted_beta', 'lifted_unknown')),
            ("source/lifted_whole_0.h", lambda text: text.replace("lifted_alpha(void)", "lifted_alpha(int value)")),
            ("source/lifted_whole_0.c", lambda text: text + '\nint lifted_first;\n'),
        ]
        for filename, mutate in mutations:
            with self.subTest(filename=filename), tempfile.TemporaryDirectory() as directory:
                root = Path(directory).resolve()
                self.fixture(root)
                path = root / filename
                path.write_text(mutate(path.read_text()))
                before = {file: file.read_bytes() for file in root.rglob("*") if file.is_file()}
                with self.assertRaises(ValueError):
                    plan_renames(root)
                self.assertEqual(before, {file: file.read_bytes() for file in before})

    def test_verified_screen_override_remains_unchanged(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            self.fixture(root)
            metadata_path = root / "docs" / "lift" / "whole_0.json"
            metadata = json.loads(metadata_path.read_text())
            metadata["alpha"]["address"] = 0x46b810
            metadata_path.write_text(json.dumps(metadata))
            header = root / "source" / "lifted_whole_0.h"
            header.write_text(header.read_text().replace("0x401000", "0x46b810"))
            screen_meta = root / "docs" / "lift" / "hud_decor.json"
            screen_meta.write_text(json.dumps({"address": 0x46b810, "stack": 16, "arguments": 0}))
            (root / "source" / "lifted_hud_decor.h").write_text("uint32_t lifted_hud_decor(void);")
            (root / "source" / "lifted_hud_decor.c").write_text("uint32_t lifted_hud_decor(void) { return 1; }")
            dispatch = root / "source" / "lifted_dispatch.c"
            dispatch.write_text(dispatch.read_text().replace("0x401000, lifted_alpha, 8", "0x46b810, lifted_hud_decor, 16"))
            staged, changes = plan_renames(root)
            self.assertEqual(changes["alpha"], "f46b810")
            self.assertIn("0x46b810, lifted_hud_decor, 16", staged[dispatch])
            self.assertNotIn(screen_meta, staged)
            self.assertNotIn(root / "source" / "lifted_hud_decor.c", staged)
            dispatch.write_text(dispatch.read_text().replace("lifted_hud_decor, 16", "lifted_hud_decor, 17"))
            with self.assertRaisesRegex(ValueError, "Dispatcher metadata mismatch"):
                plan_renames(root)

    def test_external_references_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            self.fixture(root)
            (root / "tools" / "verify_fixture.py").write_text('routine = "lifted_alpha"')
            with self.assertRaisesRegex(ValueError, "External obsolete identifiers"):
                plan_renames(root)

    def test_address_fallback_and_first_name_owner(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            self.fixture(root, {"0x402000": "vertrix_shared", "0x401000": "vertrix_shared"})
            names = readable_names(root / "docs" / "names.json")
            self.assertEqual(names, {0x401000: "shared", 0x402000: "shared_402000"})
            _, changes = plan_renames(root)
            self.assertEqual(changes, {"alpha": "shared", "beta": "shared_402000"})

    def test_variant_suffixes_do_not_steal_real_base_names(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory).resolve()
            self.fixture(root, {
                "0x405000": "vertrix_shared_402000_2",
                "0x403000": "vertrix_shared_402000",
                "0x402000": "vertrix_shared",
                "0x401000": "vertrix_shared",
                "0x404000": "vertrix_shared",
            })
            path = root / "docs" / "names.json"
            expected = {
                0x401000: "shared", 0x402000: "shared_402000_3",
                0x403000: "shared_402000", 0x404000: "shared_404000",
                0x405000: "shared_402000_2",
            }
            self.assertEqual(readable_names(path), expected)
            content = json.loads(path.read_text())
            path.write_text(json.dumps(dict(reversed(list(content.items())))))
            self.assertEqual(readable_names(path), expected)
            _, changes = plan_renames(root)
            self.assertEqual(changes["beta"], "shared_402000_3")

    def test_shared_reader_rejects_invalid_and_duplicate_addresses(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "names.json"
            for contents in (
                '{"0x401000": "vertrix_name", "0x00401000": "vertrix_other"}',
                '{"0x401000": "vertrix_name", "0x401000": "vertrix_other"}',
                '{"0x401000": "invalid-name"}',
                '{"401000": "vertrix_name"}',
                '{"0x401000": null}',
                '[]',
            ):
                with self.subTest(contents=contents):
                    path.write_text(contents)
                    with self.assertRaises(ValueError):
                        readable_names(path)

    def test_normalized_tokens_cover_enums_and_numeric_behavior(self):
        before = 'enum { LIFTED_A_STACK = 8 }; uint32_t lifted_a(void) { return 17; }'
        mapping = {"lifted_a": "lifted_b", "LIFTED_A_STACK": "LIFTED_B_STACK"}
        after = rename_tokens(before, mapping)
        self.assertEqual(token_digest(before, mapping), token_digest(after))
        self.assertNotEqual(token_digest(before, mapping), token_digest(after.replace('17', '18')))
        self.assertNotEqual(token_digest(before, mapping), token_digest(after.replace('= 8', '= 9')))


if __name__ == "__main__":
    unittest.main()
