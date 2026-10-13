# Original-based recovery — Stage 1

User-established device result: the original source/library launches and opens
its menu; the modified library crashes. This is accepted as the golden runtime
foundation. No retest of the unchanged original is requested. Device evidence
has not yet identified which modified component caused the crash.

## Exact original recovered

Source archive: original uploaded anony.zip, SHA256
ab08123caaed3af08274f49058165006fe911c0f4e83181ab0811943f1d1c5c2.
Archive CRC passes; all 947 regular file bytes recovered in a new worktree.
Original main.cpp SHA256:
dfa078639e742faff37e35235606d20d4148fc29bda7b7857bd73a1b9ec2eb08.
Original main/theme/build/definition files match pre-redesign Git checkpoint
b73a33a exactly. This branch forks that checkpoint, not the crashing modified
source or audit branch. The genuine owner-supplied SDK (2,391 files) is restored
at jni/SDK/ unchanged. All 40 original static libraries are included.

947 archive entries are inventoried in RECOVERY_ORIGINAL_MANIFEST.json.
The three unused .bak files remain local, excluded from publication/build.
All other original dependencies are restored, rather than inferred from the
seven files tracked by the first historical checkpoint. Original runtime source
and backend files are recovered from archive bytes, not rewritten from memory.

## Original versus main at a4d7eea

Only seven paths already present in the ZIP differ in main. Added application
modules are a separate category; absence from the ZIP is not an original change.

| Path / mechanism | Changes in modified project | Stage 1 recovery decision |
|---|---|---|
| jni/main.cpp — constructor/worker | Diagnostic milestones, detach/error handling, global-init barrier, atomic app publication, startup log/storage. | Original constructor and worker bytes restored, including existing registrations/calls/offsets. |
| jni/main.cpp — input/window hooks | _OI forwarding-only, bounded callback queue, renderer IO handoff and later pointer ownership work. | Original _OI, _HAI, native width/height wrappers retained exactly. No new hooks or input adapter. |
| jni/main.cpp — EGL/render | Current-context checks/owner tracking, render locking, explicit backend device checks, context-loss teardown/rebuild, frame/resource diagnostics. | Original eglSwapBuffers setup/forwarding, NewFrame ordering and backend lifetime retained exactly. |
| jni/main.cpp — fonts | Extra 32px menu/icon fonts, atlas ownership configs/build checks. | Original four font-add call sites retained without extra menu fonts or lifecycle changes. UI scales existing fonts. |
| jni/main.cpp — optional modules | Preference/character initialization, APK staging, GPU artwork, audio bank/OpenSL player and floating K launcher. | None included or initialized. Original Menu/Close floating toggle retained verbatim. |
| jni/imgui/backends/imgui_impl_opengl3.cpp/.h | Shader/device failure checks and forget-device context-loss interface; audit adds shared upload guard. | Both backend files restored byte-for-byte from original archive. Android input backend/core ImGui already match archive. |
| jni/Android.mk | OpenSLES link, diagnostics/debug/isolation flags. | Original build script restored exactly; no OpenSLES or isolation flags. Original Application.mk unchanged. Working Actions r25c retained. |
| jni/ClaudeTheme.h | Lavender, crimson, later layered styling/component changes. | Static crimson appearance transferred from Stage 3; colors/spacing only, no effects engine. |
| jni/Helper/definition.h | Visible overlay name. | Only Anoy → KennyPvtHax visible string; all other bytes match original. |
| jni/Lua_Buffer.cpp | Existing report-dialog title. | Only Anoy Hax → KennyPvtHax title; no Lua behavior changes. |
| New Kenny modules | Aurora/effects/motion/audio/character/asset/preference/launcher/startup/diagnostics infrastructure. | Absent from this stage's source/build. Only presentation-only KennyMenu.h retained/adapted. |

## Deliberate exception to restoration

Original FixGameCrash() deleted app files and obstructed crash-report paths.
Its body remains a no-op; its original worker call slot is retained. Restoring
that destructive/report-suppression behavior would contradict the user's explicit
restriction. No replacement bypass or deletion routine is introduced.
Original manually invoked Guest Reset remains part of the preserved UI callback;
never invoke it during diagnosis/tests. Test fixtures abort instead of deleting data.

## Stage 1 presentation scope

KennyPvtHax branding, static deep black/crimson theme, rounded menu, horizontal
Visual/Aim/Misc/Style/Settings navigation, feature secondary pills, restrained
panel separators and scrollable native original controls. The existing draggable
Menu/Close toggle is used, not a new logo launcher. No new textures, particles,
audio engine, asset loading, background thread, persistence or external storage.
Style/Settings contain honest informational text; their future preferences await
Stage 2. No fake functional options replace the original five feature panels.

All 37 original checkbox/slider call sites and one Guest Reset action remain
exactly as original, with identical order, labels, bindings, ranges, formats,
conditional FOV visibility and callback body. Native ImGui controls retain original
semantics; custom animated widgets are deferred. Menu geometry/font scaling is
presentation only. No extra menu-font atlas allocation is required.

## What verification can establish

Source gates compare original constructor/worker, input/hook wrappers, EGL/font/
backend/NewFrame prefix, render submission and original toggle. They also hash
all original dependencies and compare full original feature code. Build scripts,
SDK and native module Anoy remain compatible by source identity. Host fixtures
exercise real ImGui menu input/draw geometry; their safe atlas-cleanup config is
test-only and is not transplanted into Android startup. Native Android build is
performed with NDK 25.2.9519653. Real device compatibility of this Stage 1 binary
must be established by the next user test, not inferred from build success.

main, prior diagnostic artifacts and audit/android-stability are untouched.
No merge, force push, additional recovery stage or new asset acquisition.


## Completed Stage 1 build

Source commit: **3ce538cdedb9422f608b23d5cee2b814878418a1**.
Actions run: https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38362303903
Both native and original-source/ASan/UBSan UI host jobs passed with NDK r25c.
Artifact: https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38362303903/artifacts/11794839657

Extract **libs/arm64-v8a/libAnoy.so**; keep .verification/recovery-build-info.txt.
Runtime size: 6,565,888 bytes.
Runtime SHA256: 43de845910a452dfadb83865cd34189b7015088e8b324aeb674518e0c8efd165.
BuildID: 264bcffa247ce6d25382373306ba62aadbb7dfe6.
ZIP SHA256: 1d0374e5d5a6c8542835bd312c63b3ec137781e4cc7cff64a4f5f87b0e7cb1b8.

The downloaded archive's CRC, two-entry allowlist, SHA256, ARM64 ELF, build metadata
and absence of OpenSLES dependency were verified. This original release setup
strips debugging information; no private symbols or device reports were uploaded.
Machine-readable facts are in RECOVERY_STAGE1_BUILD_VERIFICATION.json.

Actual host ImGui geometry was CPU-rasterized and visually inspected. The previews
show the static crimson header/navigation, original square native widgets, native
sliders and scrollable contents. No artwork/mockup/AI screenshot was generated.
The original 16px font atlas is scaled for the menu; new high-resolution font
atlases and custom-control implementations are deliberately not transferred yet.
The host fixture's cleanup-only font ownership config is not an Android init change.

**Next device test:** install this exact library using the already-working original
host/loading pipeline. Expect the original **Menu** floating button, not a K logo.
Tap Menu, switch Visual/Aim/Misc subpanels, drag/close/reopen, and check startup.
Style/Settings preferences and cinematic features are deferred. Do not invoke the
original manual Guest Reset action during this test. If it crashes, keep the exact
binary identity and gather Android's fatal/backtrace/logcat evidence; Stage 1 has
no new automatic logger or private report export interface. Do not retest the
unchanged original. Do not move to Stage 2 or merge until this result is reviewed.

This final verification update changes documents/ignore rules only; compiled source
and all native inputs remain exactly at 3ce538c. Main is still a4d7eea, and the audit
branch/previous diagnostic build are preserved.
