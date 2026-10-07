"""Regression checks for evidence boundaries in recovered name generation."""
import tempfile
import unittest
from pathlib import Path

from gen_names import collect_names, header_pairs


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

    def test_repository_evidence(self):
        source = Path(__file__).resolve().parents[1] / "source"
        names, conflicts = collect_names(source)
        self.assertEqual(names[0x436fe0], "vertrix_board_markers_stones")
        self.assertEqual(names[0x453460], "vertrix_effect_stone_arm")
        self.assertNotIn(0x4f8d38, names)
        self.assertNotIn(0x43b5b0, names)
        self.assertEqual(conflicts[0x43b5b0], {"vertrix_ai_reaction_time", "vertrix_player_draw_delay_0"})
        self.assertEqual(names[0x4877f0], "vertrix_frame_resource_get")
        self.assertEqual(names[0x4713d0], "vertrix_title_letter_first")
        self.assertEqual(names[0x459be0], "vertrix_title_letter_count")
        self.assertEqual(names[0x459ec0], "vertrix_title_letter_digit")
        self.assertEqual(names[0x45a290], "vertrix_title_letter_fight_count")
        self.assertEqual(names[0x45a620], "vertrix_title_letter_wave_count")


if __name__ == "__main__":
    unittest.main()
