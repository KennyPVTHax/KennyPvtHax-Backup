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

Counts: **P0 0 / P1 4 / P2 8 / P3 2**. These include explicitly labeled risks;
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

| A13 P2 confirmed | jni/KennyStartup.h:39-48 | Key down/up drain in one frame; overflow injects mouse release only. | Fast key taps disappear or dropped key-up leaves a held key. Preserve keyboard frame boundaries and reset all input on overflow. | Low/moderate; stress queue plus actual ImGui keyboard tests; high. |

| A14 P2 compatibility risk | jni/Application.mk:2; diagnostic ELF program headers | Actual c975a6d runtime LOAD alignment is 0x1000; current r25c setup has no explicit 16 KiB-page opt-in. | Native loading on 16 KiB Android 15/16 devices/host packaging may require alignment changes. First collect getconf PAGE_SIZE and loader errors; do not alter the ongoing binary or NDK. | Moderate build/packaging risk; 16 KiB device/emulator and APK alignment test required; high ELF evidence, device compatibility unverified. |

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

Implement only A01/A06/A07 (one preferences commit), A05/A13 (input commit), and A02
(upload commit) on the audit branch. A03/A04/A08/A09/A10/A11/A12 remain explicit
follow-up items; their integration risk does not justify speculative edits during
ongoing device diagnosis. Add reproducible host benchmark/regression automation
and separate branch artifact metadata. Final verification follows in a later
section; this report is first committed before application code changes.

## Final results — audit branch only

**Six findings addressed:** A01/A06/A07 in c2df83e; A05/A13 in 182f35f;
A02 in 38af445. Separate report commit 09c25bd preceded application changes.
Automation/CI additions: cda9b96 and b14eb6b. All commits are independently
reversible; no main merge, force push or diagnostic artifact replacement.

**Remaining:** A03/A04/A08/A09/A10/A11/A12/A14. Original 14 findings comprise
P0=0, P1=4, P2=8, P3=2; remaining after scoped corrections: P1=2, P2=4, P3=2.
Two P1 entries are explicitly integration/concurrency risks requiring evidence,
not newly demonstrated crashes. Asset interrupted installation (A08) and logger
metadata durability (A10) remain confirmed limitations needing separately scoped
fault/lifecycle tests. No device startup root cause has been established.

### Verification

- Baseline host suites passed after correcting the new runner's omitted ImGui
  link inputs for C2. The original application did not need a correction for that.
- All **12** local ASan/UBSan suites passed: menu, launcher, PCM/audio, themes/store,
  Aurora, effects, characters, CC0 media, diagnostics/input queue, real embedded
  fonts, injected storage failures and pointer/keyboard stress.
- All **12 CI ASan/UBSan suites** passed on b14eb6b in
  [run 38196241061](https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38196241061).
  The initial audit workflow run's native job passed but its host fixture-generation
  step failed; synthetic RGBA generation now uses only Python stdlib, with no new
  Pillow installation. Failure logs now surface in CI. No production media changed.
- Actual Mesa EGL/desktop OpenGL upload/state/readback and 100 resource cycles
  passed. This does not establish Android GLES driver/context-loss behavior.
- Original 37 bindings/ranges/full callback, native worker/constructor/registration,
  SDK/40 libraries, Aurora, existing menu/launcher/audio/registry/decoder/logger
  modules remain unchanged byte-for-byte except the specifically listed fixes.
- Tracked-source inventory: 3,407 paths at the source checkpoint; no missing tracked
  files; no high-confidence private-key/GitHub/AWS token signatures. This is a focused
  scan, not a guarantee of absence of every possible secret. No new media, crash
  reports, credentials or plaintext debugging symbols were uploaded.
- Host timing/draw/allocation results and actual downloaded ELF metadata are in
  ANDROID_AUDIT_VERIFICATION.json and ANDROID_PERFORMANCE_BASELINE.md.

### Native audit artifact — separate from device-test diagnostic

Compiled source: **b14eb6b5415b30aee5c79cc2697c84c926aad732**; NDK r25c unchanged.
Both host and native jobs succeeded. Output remains libs/arm64-v8a/libAnoy.so.
[Audit runtime artifact](https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38196241061/artifacts/11723363117).
ZIP SHA256: 8f27583918f88899965c2cb102b3570bb0990f07e7bfd23bd40b32365eed6dea.
Runtime SHA256: c510806619e7c5ac4b7b14be42b2db11f18a67931fe84a5217585c2231803716.
BuildID: e536ae3c760d78bd857bab16964e211b2ef91b00.
Downloaded ZIP digest/CRC/two expected entries, ARM64 ELF and both diagnostic
exported interfaces were checked. CI asserts runtime/unstripped BuildIDs match.
Private encrypted symbols were not retained because recipient setup is absent;
plaintext symbols are never published. Actual device reports remain local.

Original artifact 11694306093 remains unexpired and has unchanged digest
2befd89516a51ef3e713319dd2e9714c5b8be38ec22961c3f81231718e906d67.
GitHub main remains a4d7eea8c98e3a0f6f1ffc32d89f5c6c9fc536f5.
Continue the existing diagnostic device test before deciding whether to test the
audit build. No root cause, crash-free startup, mobile FPS, OpenSL playback,
Android 10–16 support or Documents export success is claimed.

### Exact changed files

Application: jni/KennyAppearanceStore.h, jni/KennyStartup.h, jni/main.cpp
(input adapter/reset only), jni/KennyCharacterGL.h, jni/KennyGLUpload.h (new),
jni/imgui/backends/imgui_impl_opengl3.cpp.

Tests/automation: .github/workflows/build-native.yml; tests/run_android_stability.py;
tests/kenny_storage_stability_check.cpp; tests/kenny_input_stability_check.cpp;
tests/kenny_gl_stability.py; tests/kenny_gl_stability_check.cpp;
tests/kenny_benchmark.py; tests/kenny_performance_baseline.cpp;
tests/kenny_theme_check.cpp; tests/kenny_c2_fixtures.py.

Documentation: ANDROID_STABILITY_AUDIT.md; ANDROID_PERFORMANCE_BASELINE.md;
ANDROID_COMPATIBILITY_MATRIX.md; ANDROID_STABILITY_TEST_PLAN.md;
ANDROID_AUDIT_VERIFICATION.json; CODEX_PROGRESS.md; ANDROID_BUILD_INSTRUCTIONS.md.

### Next action

Review the findings and current c975a6d device checkpoints/backtrace. Preserve the
exact binary identity. Test the targeted branch corrections only when the owner
chooses; confirm OpenSL callback lifetime, host window synchronization and actual
GLES/context behavior before further integration edits or merge review. No UI
redesign, new asset acquisition, key-entry features or release stage was started.
