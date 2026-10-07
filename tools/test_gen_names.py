"""Regression checks for evidence boundaries in recovered name generation."""
import copy
import json
import tempfile
import unittest
from pathlib import Path

from gen_names import collect_names, header_pairs, load_registry, resolve_aliases


class NameEvidenceTests(unittest.TestCase):
    def test_annotation_spellings_and_padded_addresses(self):
        text = """
/* Original0x00436100: recovered body. */
void vertrix_compact(void);
/* Original handler 0x459be0, calls 0x4ac500. */
int vertrix_title_letter_count(void);
/* Original handlers 0x459d60 and 0x459e00. */
int vertrix_title_letter_settle(void);
int vertrix_title_letter_restart(void);
"""
        self.assertEqual(dict(header_pairs(text)), {
            0x436100: "vertrix_compact",
            0x459be0: "vertrix_title_letter_count",
            0x459d60: "vertrix_title_letter_settle",
        })

    def test_only_explicit_variants_map_all_leading_addresses(self):
        text = """
/* Original variants 0x00401010,
 * 0x401054: conversion calls 0x4ca070. */
int vertrix_mixer_output(void);
/* Original handlers 0x459d60 and 0x459e00: ordered routines. */
int vertrix_settle(void);
int vertrix_restart(void);
/* Original variants 0x0040cf50 / 0x40cfa0: two callable modes. */
enum { MODE = 1 };
int vertrix_pitch_slide(void);
"""
        self.assertEqual(dict(header_pairs(text)), {
            0x401010: "vertrix_mixer_output", 0x401054: "vertrix_mixer_output",
            0x459d60: "vertrix_settle",
            0x40cf50: "vertrix_pitch_slide", 0x40cfa0: "vertrix_pitch_slide",
        })
        with self.assertRaises(ValueError):
            list(header_pairs("/* Original variants 0x401010, 0x401054 */\nint vertrix_output(void);"))
        with self.assertRaises(ValueError):
            list(header_pairs("/* Original variants 0x401010, 0x00401010: duplicate */\nint vertrix_output(void);"))

    def test_scaffolding_and_next_annotation_boundary(self):
        text = """
/* Original 0x4713d0 and 0x4715a0. */
#define STORAGE_SIZE 0x158
/* Constants for this routine. */
enum { FIRST = 1, SECOND = 2 };
typedef struct { int value; void (*callback)(void); } Services;
int vertrix_title_letter_first(Services *services);
/* Original 0x400001: no recovered prototype. */
#define ONLY_CONSTANT 1
/* Original0x400002: next routine. */
void vertrix_second(void);
"""
        self.assertEqual(dict(header_pairs(text)), {
            0x4713d0: "vertrix_title_letter_first", 0x400002: "vertrix_second"
        })

    def test_continued_directives_do_not_supply_routine_names(self):
        for directive in ("#define DECLARE_HELPER", "#if defined(ENABLE_HELPER)"):
            with self.subTest(directive=directive):
                text = ("/* Original 0x400001: actual routine follows directives. */\n"
                        + directive + " \\\n"
                        + "void vertrix_macro_only(void); \\\n"
                        + "void vertrix_macro_second(void);\n"
                        + "void vertrix_actual(void);\n")
                for ending in ("\n", "\r\n"):
                    with self.subTest(ending=repr(ending)):
                        self.assertEqual(dict(header_pairs(text.replace("\n", ending))),
                                         {0x400001: "vertrix_actual"})

    def test_excluded_annotations_end_preceding_evidence(self):
        for marker in ("Original fragment 0x400002", "Original composition 0x400002",
                       "Original400002", "Original routine 400002"):
            with self.subTest(marker=marker):
                text = f"""
/* Original 0x400001: no recovered declaration. */
#define ONLY_CONSTANT 1
/* {marker}: not a whole-routine association. */
void vertrix_fragment(void);
/* Original 0x400003: complete routine. */
void vertrix_complete(void);
"""
                self.assertEqual(dict(header_pairs(text)), {0x400003: "vertrix_complete"})

    def test_function_type_alias_is_scaffolding_not_routine(self):
        text = """
/* Original 0x400001: callable routine below type scaffolding. */
typedef uint32_t vertrix_result_type(int value);
uint32_t vertrix_actual(vertrix_result_type *callback);
/* Original 0x400002: only a type alias, no recovered routine. */
typedef void vertrix_callback_type(void);
"""
        self.assertEqual(dict(header_pairs(text)), {0x400001: "vertrix_actual"})

    def test_member_callback_comment_does_not_leak(self):
        text = """
typedef struct {
    void *lookup; /* original 0x4877f0 behind the bind call */
    void *context;
} Services;
/* Original0x43dea0: spread particle. */
int vertrix_spawn_spread(void);
/* Original 0x400003: a variable is not a prototype. */
uint32_t some_value;
void vertrix_unrelated(void);
"""
        self.assertEqual(dict(header_pairs(text)), {0x43dea0: "vertrix_spawn_spread"})

    def test_conflicting_annotations_are_excluded(self):
        with tempfile.TemporaryDirectory() as directory:
            source = Path(directory)
            (source / "a.h").write_text("/* Original0x400001 */\nvoid vertrix_first(void);")
            (source / "b.h").write_text("/* Original0x400001 */\nvoid vertrix_second(void);")
            (source / "lifted_a.h").write_text("/* Original0x400002 */\nvoid vertrix_lifted(void);")
            names, conflicts = collect_names(source)
            self.assertEqual(names, {})
            self.assertEqual(conflicts, {0x400001: {"vertrix_first", "vertrix_second"}})

    def test_reviewed_aliases_and_invalid_evidence(self):
        candidates = {0x400001: {"vertrix_first", "vertrix_second"}}
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            (root / "evidence.h").write_text("original annotation evidence")
            valid = {"0x400001": {
                "name": "vertrix_first",
                "aliases": ["vertrix_first", "vertrix_second"],
                "evidence": ["evidence.h"],
                "reason": "Both declarations recover the same complete routine.",
            }}
            names, conflicts = resolve_aliases({0x400002: "vertrix_other"}, candidates, valid, root)
            self.assertEqual(names, {0x400001: "vertrix_first", 0x400002: "vertrix_other"})
            self.assertEqual(conflicts, {})
            self.assertEqual(candidates, {0x400001: {"vertrix_first", "vertrix_second"}})
            changes = [
                ("name", "vertrix_unknown"),
                ("aliases", ["vertrix_first"]),
                ("aliases", ["vertrix_first", "vertrix_second", "vertrix_second"]),
                ("aliases", "vertrix_first"),
                ("evidence", []),
                ("evidence", ["missing.h"]),
                ("evidence", ["../outside.h"]),
                ("evidence", [str(root / "evidence.h")]),
                ("evidence", ["."]),
                ("evidence", [None]),
                ("reason", " "),
                ("reason", None),
            ]
            for field, value in changes:
                with self.subTest(field=field, value=value):
                    invalid = copy.deepcopy(valid)
                    invalid["0x400001"][field] = value
                    with self.assertRaises(ValueError):
                        resolve_aliases({}, candidates, invalid, root)
            with self.assertRaises(ValueError):
                resolve_aliases({}, {}, valid, root)
            with self.assertRaises(ValueError):
                resolve_aliases({}, candidates, [], root)
            duplicate = copy.deepcopy(valid)
            duplicate["0x00400001"] = duplicate["0x400001"]
            with self.assertRaises(ValueError):
                resolve_aliases({}, candidates, duplicate, root)
            with tempfile.TemporaryDirectory() as outside_directory:
                outside = Path(outside_directory) / "outside.h"
                outside.write_text("outside evidence")
                (root / "link.h").symlink_to(outside)
                invalid = copy.deepcopy(valid)
                invalid["0x400001"]["evidence"] = ["link.h"]
                with self.assertRaises(ValueError):
                    resolve_aliases({}, candidates, invalid, root)

    def test_registry_rejects_duplicate_json_evidence(self):
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "registry.json"
            for text in (
                    '{"0x400001": {}, "0x400001": {}}',
                    '{"0x400001": {"name": "vertrix_first", "name": "vertrix_second"}}',
                    '{"0x400001": {"evidence": ["first.h"], "evidence": ["second.h"]}}'):
                with self.subTest(text=text):
                    path.write_text(text)
                    with self.assertRaises(ValueError):
                        load_registry(path)
            path.write_text('{"0x400001": {"name": "vertrix_first"}}')
            self.assertEqual(load_registry(path), {"0x400001": {"name": "vertrix_first"}})

    def test_repository_evidence(self):
        root = Path(__file__).resolve().parents[1]
        source = root / "source"
        names, conflicts = collect_names(source)
        self.assertNotIn(0x436fe0, names)
        self.assertEqual(names[0x453460], "vertrix_effect_stone_arm")
        self.assertNotIn(0x4f8d38, names)
        self.assertNotIn(0x43b5b0, names)
        self.assertEqual(conflicts[0x43b5b0], {"vertrix_ai_reaction_time", "vertrix_player_draw_delay_0"})
        registry = root / "docs" / "function-name-aliases.json"
        if registry.exists():
            names, conflicts = resolve_aliases(names, conflicts, json.loads(registry.read_text()), root)
            self.assertEqual(names[0x43b5b0], "vertrix_ai_reaction_time")
        for address in (0x404580, 0x425f40, 0x4523b0, 0x4713c0,
                        0x471ee0, 0x477930, 0x47f8f0, 0x4b3360):
            self.assertEqual(names[address], "vertrix_return_unchanged")
        for address, name in ((0x449360, "vertrix_actor_frame_decay_full"),
                              (0x449390, "vertrix_actor_frame_switch_full"),
                              (0x4adfb0, "vertrix_actor_refresh_value_full"),
                              (0x4adfe0, "vertrix_actor_refresh_arm_full"),
                              (0x45f9f0, "vertrix_ui_panels_destroy_full"),
                              (0x45fa70, "vertrix_ui_panels_slot1_full"),
                              (0x45fab0, "vertrix_ui_panels_slot2_full"),
                              (0x472d50, "vertrix_ui_panel_release_full")):
            self.assertEqual(names[address], name)
        self.assertEqual(names[0x41a9e0], "vertrix_record_release_global_full")
        self.assertEqual(names[0x441a80], "vertrix_record_release_full")
        self.assertNotIn(0x43f200, names)
        self.assertNotIn(0x43f200, conflicts)
        for fragment in ( 0x42b290, 0x42b310, 0x43eab0, 0x4b6240, 0x4831b0, 0x483400,
                         0x40c518, 0x40c5d8, 0x40c7d0,
                         0x40e1db, 0x40e77f, 0x40e7ba, 0x40e82c, 0x40eb14, 0x40eb6e):
            self.assertNotIn(fragment, names)
            self.assertNotIn(fragment, conflicts)
        self.assertEqual(names[0x4877f0], "vertrix_frame_resource_get")
        self.assertEqual(names[0x4713d0], "vertrix_title_letter_first")
        self.assertEqual(names[0x459be0], "vertrix_title_letter_count_call")
        self.assertEqual(names[0x459ec0], "vertrix_title_letter_digit")
        self.assertEqual(names[0x45a290], "vertrix_title_letter_fight_count")
        self.assertEqual(names[0x45a620], "vertrix_title_letter_wave_count")


if __name__ == "__main__":
    unittest.main()
