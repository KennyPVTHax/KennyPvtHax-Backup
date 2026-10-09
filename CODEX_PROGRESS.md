PROJECT: KennyPvtHax

CURRENT STAGE:
Stage 1 — SOURCE INSPECTION AND REBRANDING — COMPLETE
Checkpoint date: 10 October 2026 (Asia/Calcutta).
STOPPED after Stage 1. Start Stage 2 only after the user's next instruction.

COMPLETED:
- Checked `/workspace` and the uploaded archive for existing progress, repository history, and `AGENTS.md`; none existed.
- Safely extracted the real application into `/workspace/KennyPvtHax`, retaining all original sources, supplied dependencies, and `.bak` files.
- Inventoried the source tree and identified C++17, Android API 21+/arm64, bundled Dear ImGui 1.85 WIP, OpenGL ES 3 rendering, native NDK build, input handlers, navigation, configuration globals, and callbacks.
- Inspected both supplied current-interface screenshots.
- Probed the reference video and extracted/inspected seven representative frames once, at 05/09/12/15/18/24/27 seconds. Cached frames are in ignored `.reference/`.
- Recorded source ownership, all existing control bindings and ranges, measured reference proportions, and a reusable staged design in `UI_DESIGN_NOTES.md`.
- Rebranded the main ImGui window title to `KennyPvtHax`.
- Rebranded the existing HUD watermark to `KennyPvtHax` (its existing positioning/color are retained until visual polish).
- Rebranded the Lua status popup title to `KennyPvtHax`.
- Preserved native library name `Anoy`, font folder `ANOY/`, `_G.__AnoyStatus`, `AnoySetStatus`, configuration variables, callbacks, platform integration, and third-party attribution.
- Initialized a local Git repository with a selective original-source baseline commit `b73a33a`; no credentials, static libraries, generated binaries, or unrelated third-party files were added.
- Added ignores for reference frames, temporary output, binaries, credential file types, the existing login header, and original backups.

MODIFIED FILES:
- `jni/main.cpp`: one main-window display-title replacement, at line 1029.
- `jni/Helper/definition.h`: one HUD watermark text replacement, at line 1325.
- `jni/Lua_Buffer.cpp`: one status popup title replacement, at line 2030.
- `.gitignore`: new checkpoint/binary/credential exclusions.
- `UI_DESIGN_NOTES.md`: new durable inspection, binding inventory, and design plan.
- `CODEX_PROGRESS.md`: this new resumable progress checkpoint.
- Local-only `.reference/frame-{05,09,12,15,18,24,27}.jpg`: cached visual references, not committed.

VERIFICATION:
- PASS: compared every original file with the ZIP. Exactly three source files changed, each through exactly one expected display-string replacement; all other 944 original files are byte-for-byte identical. This also verifies that callbacks, defaults, input logic, backend integration, third-party files, and supplied backup copies were preserved.
- PASS: 37 checkbox/slider call sites remain unchanged, including shared Aimbot/Bullet track bindings and original ranges/formats.
- PASS: no legacy `"Anoy Hax"` or `"Anoy"` display literals remain in the three active branding-bearing files; native module and Lua compatibility identifiers remain.
- PASS: `git diff --check` reports no whitespace errors.
- PASS: host header syntax check executed successfully: `printf '#include "imgui/imgui.h"\n#include "ClaudeTheme.h"\n' | g++ -std=c++17 -fsyntax-only -x c++ -I jni -`. This checks the existing UI theme against bundled ImGui headers; it is not an Android application build.
- PASS: seven cached reference frames exist; MP4 metadata confirms 32.810667 seconds, 1920×872, 30 fps.
- PASS: credential-pattern scan of selectively tracked application sources/build files found no candidate assignments/private keys. The login header remains excluded from Git.
- Initial exact-byte verification caught an incidental added newline at the end of `Lua_Buffer.cpp`; restored the original convention and reran the full check successfully.
- NOT VERIFIED: complete Android compilation/linking, on-device branding appearance, touch/mouse interaction, overlay performance, or final visual fidelity. No application build or runtime success is claimed.

KNOWN ISSUES:
- The uploaded archive lacks `jni/SDK/`, including `PUBGM_BangJO.hpp` and six SDK `.cpp` files listed in `Android.mk`. The source upload alone cannot build the native application.
- Android NDK / `ndk-build` is unavailable in this environment; no packages were installed.
- No full APK project, application display-name resources, or app-specific manifest was provided. Keep the internal native library name for compatibility.
- No existing feature preset save/load UI or feature-configuration persistence was found. Reference presets/licensing must not become nonfunctional copied UI.
- Original menu state uses render-local and global variables with overlapping names; preserve and validate its close/reopen behavior in Stage 2.
- Existing red HUD watermark and orange/charcoal interface remain visually unchanged apart from text; Stage 1 intentionally does not implement Stage 2–5 styling.
- Git selectively tracks the initial relevant files; most untouched original sources are untracked and retained locally/in the upload. Explicitly stage only reviewed files changed in future stages.

NEXT ACTION:
WAIT for the user's instruction to continue. Then implement Stage 2 only:
1. Read this checkpoint and `UI_DESIGN_NOTES.md`; inspect `git status`/diff to preserve any intervening changes. Do not re-extract or reanalyze the video.
2. Extend `jni/ClaudeTheme.h` with the reference's deep black/lavender palette and reusable horizontal tab/pill helpers using this bundled ImGui API.
3. Modify only the menu portion of `jni/main.cpp` to build a rounded, responsive floating window with KennyPvtHax header and `Visual | Aim | Misc | Style | Settings` horizontal navigation.
4. Preserve the existing five feature-panel bindings and `Settings::Tab` meanings: Visual → Player ESP/World ESP; Aim → existing Aimbot; Misc → Bullet track/Extra features. Add secondary navigation without removing any original control. Style/Settings must have meaningful interface/application content as those stages are implemented.
5. Keep original EGL/input integration and reset callback; verify unchanged control bindings, menu toggling/dragging, layout/clipping as far as available tools allow.
6. Update this checkpoint, create a focused verified Stage 2 commit, and STOP again.

REMAINING TASKS:
- Stage 2: main window/theme/horizontal and secondary navigation.
- Stage 3: Visual and Aim panel layout.
- Stage 4: Misc, Style, Settings and existing application actions.
- Stage 5: circular controls, thin sliders, pill buttons, bounded animations/ambient effects.
- Stage 6: real Android build when NDK/SDK are available; runtime/visual verification and final polish.

REFERENCE NOTES:
- Primary evidence and full binding/source map: `UI_DESIGN_NOTES.md`.
- Original upload: `/workspace/attachments/39453fdf-2d8c-4bed-8f31-b1783cba5aa8/anony.zip`.
- Video: `/workspace/attachments/cce0f225-b1ea-452b-bcd0-4a3830221a43/VID_20261009_214158_354.mp4`.
- Panel ≈1,135×713 in 1920×872 capture, positioned near `(392,80)`, radius ≈32–36 px, near-black center with restrained purple edge glow and thin borders.
- Header ≈100 px; secondary pills ≈74 px row; two/three equal content columns; thin separators; control labels and headings are clean sans-serif.
- Enabled checkbox ≈42–44 px lavender circle/dark checkmark; disabled outline circle. Slider track ≈8–9 px with lavender progress and ≈25–27 px pale round knob; value above/right.
- Sparse panel-local stars and moving purple ambient light; no copied reference branding, licensing, or behavior.

SOURCE CHECKPOINT HASHES (SHA-256):
- `jni/main.cpp`: `2daf8e9bcb178c163523b9ea44f25d711b57cdd3e182ba14cf6cb3d4178f1e52`
- `jni/Helper/definition.h`: `e01c4f04ac3ca5fa34f3a94c41527350db75c15f516a0ce6feabf2193fd6f0b8`
- `jni/Lua_Buffer.cpp`: `b92231b93b6de973ba3f86dc4b708d1295e9b1ce92741875eac55a8165bfbebb`

GIT CHECKPOINT:
- Original selected-source baseline: `b73a33a`.
- Stage 1 commit: find with `git log -1 --oneline` (subject: `Stage 1: rebrand UI to KennyPvtHax and record design checkpoint`).
