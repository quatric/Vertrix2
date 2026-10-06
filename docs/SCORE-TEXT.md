# Score text

`0x417790` (`source/score_text.c`) formats a score clamped to 99,999,999 as eight zero-padded digits (`%08lu`). `tools/verify_score_text.py` runs the original 4,096 times with the runtime format call hooked. Evidence: `score-text-verification.json`.
