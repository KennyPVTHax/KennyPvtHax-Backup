# Crimson Eclipse — Electric Starfield

Presentation-only experiment on `ui/classic-electric-starfield`. The owner-working
full UI baseline is `2a54a41`; the development parent is `a374ad0` (documentation
checkpoint for compiled audio-recovery source `9a3de44`). The preserved previous
library SHA-256 is `1541f3479db659627da124c448ed7d43e5d3316de817f619a849a3ee5f380f4d`.
This experiment does not claim that the audio-recovery library or new effects have
been device-tested. The blank `jni/Helper/bypass.h` remains byte-identical.

## Reference and composition

Inspected the actual attachment `Screenrecording_20261014_145726.mp4`, rather than
assuming the different filename in the task exists. It is a 14.387-second,
1080 × 2376 H.264 screen recording, approximately 60.39 average fps. Four frames
at 2/5/8/11 seconds show braided vertical filaments, luminous junctions, particles,
and energy traveling between connections. No video, reference UI, text or audio
is embedded. Ignored reference frames live in `.verification/electric-reference/`.

The new background preserves the dark Classic shell, layout and foreground.
Activity follows the sides and lower negative space; a spatial attenuation mask
keeps the header and label regions quieter. Fine companion strands and branches
connect to a stable perimeter network. No violet accent or lightning sound is used.

## Rendering and time

`jni/KennyElectricStarfield.h` uses the existing ImGui atlas white pixel and draw
lists. It contains 17 fixed filaments × 33 sampled points: ten connections, four
attached branches, three braided companion strands. Anchored curves combine broad
bends with interpolated seeded noise at two scales. Their topology never changes
randomly every frame. Three tapered layers provide faint wide crimson glow,
crimson filaments and narrow white cores. Nine junctions and seeded stars add depth.

At most two pulses travel on existing paths, using independent periods and smooth
fade envelopes. A local luminance envelope brightens the existing filament and a
short dot trail follows the head. There are no full-window flashes. Pulses do not
run continuously or produce sound. All halos, line geometry and AA fringes remain
inside the rounded menu; every emitted vertex is tested against that boundary.

The bounded star array holds 96 deterministic seeds. Low/Medium/High draw 32/64/96
stars with stationary points, slowly drifting crimson particles and rare soft
shimmers. No teleporting respawns, per-frame RNG or media decoding is involved.

One Classic-owned double-precision visible clock drives analytic motion. Advance
is idempotent within a frame. It uses existing safe delta clamping (0–100 ms),
skips hidden/inactive frame gaps, and does not reset seeds/time when reopening or
switching themes. Simulation is not advanced for Aurora/Anime. No threads, hooks,
textures, context ownership, resource loading or audio calls are added.

## Settings and persistence

The existing Settings child contains **Classic Background Effects**, after the
existing audio section, visible only for Classic:

| Preference | Default |
| --- | --- |
| Enable Electric Starfield | On |
| Star Density | Medium (64) |
| Lightning intensity | 45% |
| Sparkle intensity | 55% |
| Animation speed | 50% |
| Energy Pulses | On |
| Reduced Motion | Off |

Zero speed freezes the current pose. Local or existing global Reduced motion
freezes drift/filament evolution/twinkle and suppresses traveling pulses; the
static dark atmosphere remains. Off restores the pre-upgrade Classic surface.
No inactive Classic update is performed. Drawing paused geometry still has a
bounded cost; this is not an Android power/FPS claim.

Existing app-private appearance storage is unchanged. Schema 5 appends seven
Classic preferences; versions 1–4 retain their previous values and default the
new fields. Finite percentage values clamp to 0–100; density clamps to 0–2.
Malformed new fields retain valid older appearance/audio/character preferences
and report the failure. Existing atomic private saves, no-idle-write behavior,
Reset appearance and unrelated feature persistence remain intact.

## Host verification and reproducibility

All existing 13 ASan/UBSan suites plus the new electric suite passed. Focused
menu/launcher/effect tests are rerun after visual polish. The fixture extracts
all 37 original binding/range/format statements and the unchanged full feature
callback. `main.cpp`, startup, SDK, EGL/input, blank bypass header, Aurora, audio,
character registry/GL owner, launcher and build workflow are unchanged.

Focused checks cover 30/60/90/120 Hz agreement, invalid/stalled timing, same-frame
idempotence, hidden/theme pause, Reduced/off behavior, coherent connected paths,
pulse bounds, rounded clipping across four scales, 1,000 warmed allocation and
buffer-capacity samples, and schema migration/restart/corruption/normalization.
Native captures test real settings toggles, density choices, sliders, routing,
small/large viewports and unchanged feature snapshots. Existing suites test
launcher taps/drag/close/reopen, all original controls, scrolling, themes and audio.

Use the existing runner:

```sh
python3 tests/run_ui_regressions.py --sanitizers --user-media .verification/user-media --label electric-regressions
```

The optional private media directory is needed only for supplied-recording tests;
its files are not in the source repository. Without it, omit `--user-media`.
For matched baseline captures, run `python3 tests/kenny_electric_baseline.py`.
Build/run `tests/kenny_electric_capture.cpp` with bundled ImGui, zlib,
`IMGUI_ENABLE_TEST_ENGINE`, and `-I jni -I .verification`. Build
`tests/kenny_host_rasterize.cpp` to `.verification/electric-rasterize`, then run
`python3 tests/kenny_electric_package.py`. Fixtures must exist first.

Previews under `previews/classic-electric/` are actual production C++/ImGui indexed
geometry and original fonts CPU-rasterized, not invented UI screenshots or Android
GPU captures. The package includes 0/3/6/10-second images, real before/after output,
all feature panels, settings, Reduced/off and 640/2560 viewport captures, a contact
sheet, a self-contained viewer and a 145-frame continuous 1280 × 720 MP4. Native
frames advance at 60 Hz, captured at 12 fps; this is offline preview timing, not
Android FPS. Aurora/Anime captures are compared at matching state to actual
read-only baseline rendering; generated evidence records exact pixel differences.

Performance is measured separately in optimized host builds, including CPU p50/p95
and worst-case native vertices/indices. See the final verification JSON for actual
numbers. There are no growing warmed ImGui allocations or geometry capacities.
These results exclude GPU work and do not predict Android device performance.

## Build and device requirements

Use the unchanged `build-native.yml`, full presentation, NDK 25.2.9519653 and
arm64-v8a. Final run/artifact/library hash are recorded in
`CLASSIC_ELECTRIC_BUILD_VERIFICATION.json` after the build. Native module remains
`libAnoy.so`; only the optional loader package renames it to root `libloader.so`.
No live Anilxkenny upload/manifest change or release-branch promotion is authorized
by this experimental task.

Test the exact artifact through the existing Android loader, then select Classic.
Check all seven screens, settings persistence after process restart, controls and
scrolling, launcher/drag/open/close, rapid themes, Reduced/off, and background
contrast at normal device brightness. Measure UI responsiveness, CPU/GPU/frame
pacing on the target device at its supported refresh modes. Check app resume and
context recreation through the existing lifecycle. Aurora/Anime and Rias audio
should behave as before; the private media installation requirement is unchanged.
Device GPU blending, actual Android timing/power use and visual smoothness remain
unverified until the owner tests. No media, logo/video work or startup fix is bundled.

## Modified files

`jni/KennyElectricStarfield.h`, `jni/KennyMenu.h`, `jni/KennyThemePreferences.h`,
`jni/KennyAppearanceStore.h`, `jni/KennyAppearance.h`; electric check/capture/
baseline/package scripts and existing regression runner; this document,
`UI_DESIGN_NOTES.md`, `CODEX_PROGRESS.md`, `tests/README.md`, and final build metadata.
