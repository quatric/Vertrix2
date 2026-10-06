# Code formatting

- Format all C and C++ source and headers with the project's `.clang-format` before finishing an edit.
- Use four spaces, Allman braces, and a 100-column limit.
- Keep each statement on its own line. Do not compress control flow onto one line.
- Check formatting with `clang-format --dry-run --Werror source/*.c source/*.h`.
- Keep formatting changes separate from changes to recovered behavior.

# Port fidelity

- Recover and preserve the original game behavior. Do not substitute guessed rules, timings, AI, or bonus behavior.
- Record the executable addresses and verification evidence for recovered logic.
- Keep experimental reconstructions outside the deliverable source tree.
