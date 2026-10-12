# Android stability audit — read-only findings

Inspected baseline: **a4d7eea8c98e3a0f6f1ffc32d89f5c6c9fc536f5**.
Application code is identical to the device-test build **c975a6d**.
Repository: KennyPVTHax/KennyPvtHax-Backup, PUBLIC; authenticated ADMIN access.
The original worktree/main, diagnostic artifact 11694306093, runtime checksum
9824c2841aabb36176d837d061d8cb0e1cf45ca48d271cc0640014553958ad14
are preserved. Work is isolated on `audit/android-stability`. No merge authorized.

Assessment: host-testable components are extensively bounded and recover from
missing media. Source review nevertheless identifies conditional freezes,
texture-upload isolation defects and multitouch ambiguity. Startup crash root
cause remains unknown without the device checkpoints/backtrace. An ARM64 build
success is not evidence of working device startup, GPU, audio or Android storage.

## Findings delivered before application changes

Counts: **P0 0 / P1 4 / P2 6 / P3 2**. These include explicitly labeled risks;
there are no newly established unconditional startup crash causes. Locations
below refer to the frozen baseline, not line numbers after corrections.

| ID / priority | Baseline location | Evidence and reproduction | Impact / correction | Change risk / required test / confidence |
|---|---|---|---|---|
| A01 P1 confirmed | jni/KennyAppearanceStore.h:28 | Blocking O_RDONLY open, no regular-file check. Replace app-owned .conf with FIFO with no writer. | Render-thread Configure blocks indefinitely. Use NONBLOCK, fstat regular/size bounds and bounded read. | Low; real FIFO/symlink/oversize/truncation tests; high. |
| A02 P1 confirmed | jni/KennyCharacterGL.h:60; jni/imgui/backends/imgui_impl_opengl3.cpp:511 | Font upload changes ROW_LENGTH without restoring it; both uploads inherit PBO, SKIP_ROWS/PIXELS and other unpack state. Set nonzero host unpack state before initialization. | CPU pointer can be interpreted as a PBO offset, or upload reads beyond the intended pixel rows; fonts can report success after GL failure. Save/reset/restore supported unpack fields/PBO, check allocation. | Moderate; state-isolation tests and genuine Android compile, actual EGL driver test required; high source confidence. |
| A03 P1 risk | jni/KennyAndroidAudio.h:25,83,98 | Callback Render/slot/idleSamples and render-thread Pump restart use ordinary consumer fields; Stop is not explicitly fenced against in-flight callback. | Possible concurrent PCM/consumer access or shutdown overlap; obtain callback lifecycle trace and verify backend guarantees before replacing scheduling. | High; OpenSL stress/device lifecycle + race tooling required; medium, no demonstrated device race. |
| A04 P1 risk | jni/main.cpp:943-964 | renderStorageAttempted is read/written before RenderGuard; android_app window/config fields are host lifecycle-owned. Atomic app publication does not synchronize subsequent host mutations. | Concurrent swap callbacks/lifecycle transitions can race. Move trivial private flag beneath a gate only after integration evidence; acquire host-approved lifecycle snapshot rather than guessing a lock. | High integration risk; simultaneous swap, pause/resume/rotation tests required; medium. No offsets/loader changes proposed. |
| A05 P2 confirmed | jni/main.cpp:92-104 | POINTER_DOWN/UP of any finger changes single ImGui mouse; MOVE chooses index zero, not the initiating pointer ID. | Second finger can release or move the first gesture. Track one primary pointer by ID; ignore secondary ownership changes; cancel consistently. | Moderate; pure adapter stress and device two-finger tests; high. |
| A06 P2 confirmed | jni/KennyAppearanceStore.h:64-81 | Single write/read calls do not retry EINTR/short transfer; snprintf length unchecked; directory entry is not fsynced after rename. | Legitimate interruptions lose save; oversized direct Save can over-read formatted buffer. Add bounded formatting, retry loops, directory durability status. | Low/moderate; syscall fault injection, old file retention, ENOSPC and restart; high. |
| A07 P2 confirmed | jni/KennyAppearanceStore.h:84-89 | Sync assigns observed even when Save fails. Retry same preferences after disk becomes writable. | Preferences silently remain unsaved indefinitely unless changed again. Keep committed and attempted state separate, retry with bounded backoff. | Low; recovered storage/idle write-count tests; high. |
| A08 P2 confirmed | jni/KennyCharacterGL.h:23-33 | StageFile writes directly to final O_EXCL file; process kill mid-copy leaves partial file, skipped forever on next staging. | Optional pack stays broken; loader safely falls back. Future change: unique staging + no-overwrite atomic install. | Moderate; actual APK staging/SIGKILL test required; high source confidence, deferred. |
| A09 P2 conditional | jni/imgui/backends/imgui_impl_opengl3.cpp:149-151 | GLES3 sampler binding is not reset/restored (desktop-only macro). Bind host sampler to texture unit 0. | Host sampler can override UI texture parameters, causing rendering differences. Add tested GLES3 sampler isolation when genuine GL harness/device evidence exists. | Moderate; actual GLES texture/sample comparison required; high source, device occurrence unknown. |
| A10 P2 confirmed limitation | jni/KennyDiagnostics.h:108 | Directory fsync after report rename ignored; mid-rotation failure has no transaction recovery beyond preserved moved reports. | Power-loss metadata durability weaker than process-kill durability. Check failure and preserve discoverable evidence; do not reduce milestone fsync before measuring. | Moderate; filesystem fault/power interruption tests; high source, no device data-loss evidence. |
| A11 P3 confirmed | jni/KennyMenu.h:93; jni/main.cpp:1120 | Registry Prepare called before launcher and again inside open menu. | Duplicate cached checks, not duplicate uploads. Measure before removing; keep actual successful interaction routing. | Low; voice routing/100 theme switches and CPU benchmark; high, minor. |
| A12 P3 confirmed | jni/imgui/backends/imgui_impl_opengl3.cpp:409 | Temporary VAO generated/deleted every submitted UI frame. | Driver overhead, not proven mobile bottleneck; avoid optimization without GPU timing/context correctness. | Moderate; real driver profiling and recreation tests; high source, performance magnitude unknown. |

## Ten highest-impact recommendations

1. Retrieve the running diagnostic's last checkpoint plus matching fatal backtrace.
2. Correct A01 preference FIFO handling before accepting arbitrary local files.
3. Isolate/check pixel upload state (A02), preserving foreign application state.
4. Verify OpenSL callback handoff/shutdown before changing A03 scheduling.
5. Confirm host lifecycle synchronization for A04; pointers are not lifetime proof.
6. Fix A05 single-touch ownership without changing native registrations.
7. Correct atomic save transfer/durability and bounded retry (A06/A07).
8. Make asset installation interruption-safe in a separately tested task (A08).
9. Exercise GLES samplers, context reuse/loss and texture failure on-device (A09).
10. Verify logger metadata durability and profile startup fsync/VAO costs (A10/A12).

## Coverage and preserved boundaries

Reviewed all application-owned Kenny headers (startup/input, diagnostics, menu,
launcher, controls, paint/identity, motion/effects/Aurora, themes/preferences/store,
assets/characters/GL and audio), startup/render portions of main.cpp, Android
backends, build scripts/workflow, existing tests and asset manifests. Inventory
includes genuine restored SDK and 40 static libraries. SDK/third-party/gameplay
sources are inventoried and build-checked, not exhaustively semantically audited
or certified. Game offsets, loader registration, algorithms and SDK remain intact.

Startup checkpoints cover prerequisites and first submitted frame; startup runtime
waits and first-frame asset/font/audio work can delay the launcher. These are
observations, not a diagnosed failure. Missing/corrupt artwork and unsupported
voices remain optional; all image/audio budgets and path restrictions are retained.
The 40-star/three-layer renderer, settings and approved appearance are unchanged.

No new source permissions, network logging, signal handler, anti-detection or
crash-report suppression. Manual Guest Reset remains an original destructive
callback: never invoke it during diagnostics/regression. Only permitted CC0
runtime clips are in the public repository; unverified OGGs remain excluded.

## Implementation decision following this report

Implement only A01/A06/A07 (one preferences commit), A05 (input commit), and A02
(upload commit) on the audit branch. A03/A04/A08/A09/A10/A11/A12 remain explicit
follow-up items; their integration risk does not justify speculative edits during
ongoing device diagnosis. Add reproducible host benchmark/regression automation
and separate branch artifact metadata. Final verification follows in a later
section; this report is first committed before application code changes.
