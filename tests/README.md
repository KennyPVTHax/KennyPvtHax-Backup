# SDK-independent Stage 5.5 checks

## Stage 5.6 / Phase A — living aurora

The new production effect is `jni/KennyAurora.h`; integration in `KennyMenu.h` routes it only to Visual → Player ESP. Everything below uses real ImGui; it does not replace/recreate SDK headers. Keep assertions enabled. No package installation is necessary with the existing host compiler, Python/Pillow and FFmpeg.

```sh
mkdir -p .verification
timeout 120s g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_aurora_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/kenny_aurora_check
timeout 60s .verification/kenny_aurora_check
python3 tests/kenny_host_fixture.py
timeout 120s g++ -std=c++17 -O0 -g -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_menu_host_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/stage5_6_check
timeout 60s .verification/stage5_6_check
timeout 120s g++ -std=c++17 -O0 -g -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_phase_a_capture.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/stage5_6_capture
timeout 60s .verification/stage5_6_capture
timeout 60s g++ -std=c++17 -O2 -Wall -Wextra -Werror tests/kenny_host_rasterize.cpp -o .verification/kenny_host_rasterize
timeout 300s python3 tests/kenny_phase_a_package.py
```

The focused test checks deterministic initialization, distance-based attraction, continuous release/home recovery, frame-rate agreement, bounded variable-dt integration, malformed time, hidden/reduced/same-frame behavior, long-session noise continuity, actual rounded draw vertices, all stars/halos remaining drawable and stable warmed native allocations/capacities. It covers 20,000 edge/drag steps, 600 geometry samples and 1,000 allocation frames.

The source extractor asserts exactly 37 original binding sites and extracts their actual unchanged statements/configuration. The tracked menu harness retains the full earlier seven-panel native interaction suite, plus first-press background attraction and checkbox priority, held/drag/release dispersion, outside-origin/exit cancellation, header dragging, non-Player isolation and reduced-motion freeze. `ResetLogin()` aborts in the host harness; the real destructive/platform callback is never invoked. Original embedded-font macro warnings are pre-existing; production headers and focused tests pass strict warnings.

The capture executable submits the actual menu, original panels, embedded fonts and native mouse input. PNG/video output comes from the actual emitted indexed triangles/atlas, CPU-rasterized with `kenny_host_rasterize.cpp`. The video contains 145 consecutive captures at 12 fps, with 60 Hz input and bounded 120 Hz physics. It is not Android/device FPS. This faster offline rasterizer agrees with the earlier Python baseline to within one 8-bit channel level; no source UI is simulated.

Packaging uses the retained `.verification/stage5_5-player-1920.draw`, its feature snapshot/atlas and `previews/stage5_5/verification.json` as af8a337 baseline evidence. Keep these ignored earlier artifacts; missing baseline evidence blocks comparison packaging rather than generating a fake replacement. Prior PNGs are preserved. Output is `previews/stage5_6/`: 15 PNGs, MP4, self-contained HTML, provenance JSON, README and a 19-entry ZIP. The HTML embeds exact images/video and supports individual downloads offline.

SDK/NDK/device/GPU/Android touch testing remains unavailable. Native geometry/allocation tests do not prove mobile FPS or GPU blending fidelity. Stop after Phase A; applying the new background to other panels needs the user's next instruction.

Run from the repository root with the bundled ImGui sources and a C++17 host compiler:

```sh
g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_effects_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o /tmp/kenny_effects_check
timeout 30s /tmp/kenny_effects_check
```

Keep assertions enabled. This exercises production animation/effect code and actual ImGui draw vertices. It checks the floating-toggle wrapper's unchanged hitbox/native release/disabled behavior, interpolation across frame rates, rapid target switching, hidden/reduced-frame recovery, nested reduction scopes, long-running lighting continuity, fixed cache capacity, full/reduced rounded clipping including halos/fringes/glints, and stable warmed geometry allocations. It neither compiles the SDK-dependent Android application nor proves device FPS, GPU appearance, or platform input behavior.

The broader local interaction harness under `.verification/stage5_5_*` extracts the unchanged real panel statements/configuration declarations and tests all original bindings, navigation, native input, appearance actions (including Full/Reduced motion), scrolling and viewports. It also checks stable warmed ImGui allocations/draw capacities across 1,000 frames switching all seven panels. Its captures feed the CPU rasterizer; generated output remains ignored. A separate read-only header snapshot from commit 4eaedda reproduces the matched baseline without switching or reverting the working tree.
