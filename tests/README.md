# Phase C3 acquisition and actual-pack verification

C3 adds private CC0 Cici Fyre alternative voice **data**, without modifying any
application `jni/` source. No Rias artwork/original voice was installed. Permission
review and content/quality limits: [C3_ASSET_VALIDATION.md](../C3_ASSET_VALIDATION.md).
Run from the repository root with the current private assets retained:

```sh
timeout 30s python3 tests/kenny_host_fixture.py
timeout 30s python3 tests/kenny_c2_fixtures.py
timeout 120s g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_c3_check.cpp -lz -o .verification/c3_check
timeout 30s .verification/c3_check
timeout 60s python3 tests/kenny_c3_validate.py
timeout 120s g++ -std=c++17 -O1 -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_c3_capture.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -lz -o .verification/c3_capture
timeout 60s .verification/c3_capture
timeout 60s g++ -std=c++17 -O2 -Wall -Wextra -Werror tests/kenny_host_rasterize.cpp -o .verification/kenny_host_rasterize
timeout 60s python3 tests/kenny_c3_package.py
```

The integrity script needs `.verification/c3-review/` original licensed archive/
WAVs and `/workspace/attachments/` uploaded OGGs; override with `--review-root`
and `--uploads-root`. It validates file content, not legal permission. The
alternative PCM clips are ignored/private and must be preserved separately from
the Git checkpoint. Packaging compares actual retained C2 baseline PNGs; it
neither regenerates nor overwrites them. All `jni/` files remain byte-identical
to `6f300ae`, so existing compiled regressions were rerun against unchanged code.
The strict C2 loader test was rebuilt after isolating its negative empty root;
diagnostic manifests retain only diagnostic packs. No assertion was weakened.

C3 checks actual five-file/seven-event decode/routing/cooldown/mute/volume and
fresh-store pack/preferences restoration. Native C3 captures additionally test
the installed selector, voice controls, no slider sound events, missing artwork
and 640 viewport. Eleven actual PNGs, genuine C1 PCM demo, self-contained viewer,
hash provenance and 15-entry ZIP live privately in `previews/phase_c3/`. Normal
captures expose unavailable Android audio; `host-pcm-test-settings.png` is
explicitly a real portable-mixer test sink. English speech labels corroborated
by offline machine recognition, not human audition. No Android/OGG playback or
Rias artwork/voice claim. Existing C1/menu/theme/Aurora/effect/C2 tests below pass.

# Phase C2 host verification

C2 reuses the actual C1 mixer/backend. No permitted Rias media was acquired.
These fixtures are diagnostic transparent pixels/test tones, confined to ignored
`.verification/`; they are never installed or rendered as Rias assets. Run the
existing C1/menu/theme/Aurora/effects regressions below as well.

```sh
python3 tests/kenny_host_fixture.py
python3 tests/kenny_c2_fixtures.py
timeout 120s g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_c2_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -lz -o .verification/c2_check
timeout 40s .verification/c2_check
timeout 120s g++ -std=c++17 -O1 -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_c2_capture.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -lz -o .verification/c2_capture
timeout 60s .verification/c2_capture
python3 tests/kenny_c2_baseline.py
timeout 60s g++ -std=c++17 -O2 -Wall -Wextra -Werror tests/kenny_host_rasterize.cpp -o .verification/kenny_host_rasterize
timeout 60s python3 tests/kenny_c2_package.py
```

The bounded baseline script compiles actual C1 headers from `c5e9ef0` read-only
under `.verification/c2-baseline/`. It never checks out, resets or changes history.
Captures use production ImGui controls, original statements/fonts and native
input. PNGs rasterize the emitted indexed triangles and show honest missing
assets/unavailable playback; no substitute character media enters the previews.

Strict C2 checks cover byte-exact alpha, corrupt/truncated/opaque PNG rejection,
safe paths/symlinks/FIFOs, bounded manifests/WAV downmix/resampling, registry
extension/fallback, texture-owner callbacks, voice variation/cooldown/mute/volume,
500 switches, 10,000 allocation-free warmed dispatch/mix iterations, schema 2→3
persistence, invalid references and native aspect-fit UVs. Existing theme tests
also verify schema 1 migration. Native C2 captures test missing-media selection
and minimum 36-pixel selector height at 640×360. The broad menu suite still covers
all 37 bindings/ranges and original interaction behavior.

`previews/phase_c2/` has 12 validated PNGs (eight new screens, two C1 baselines,
contact sheet and comparison), SHA-256 provenance, self-contained offline HTML
and a 15-entry ZIP. Comparison records observed pixels without Android claims.
Missing SDK/NDK/device prevent Android build, APK staging, GLES/OpenSL playback
and real device verification. See [ANIME_CHARACTER_ASSETS.md](../ANIME_CHARACTER_ASSETS.md)
for supported formats and installation. Stop after C2. Historical C1 notes follow.

# Phase C / Checkpoint C1 host verification

Continue in the existing repository. C1 adds the production K launcher and portable PCM/event mixer plus a real Android OpenSL ES adapter. SDK/NDK/device compilation and sound playback remain unverified; do not supply fake OpenSL/SDK headers. Keep assertions enabled.

```sh
python3 tests/kenny_host_fixture.py
timeout 60s g++ -std=c++17 -O1 -Wall -Wextra -Werror -pthread -I jni tests/kenny_audio_check.cpp -o .verification/c1_audio_check
timeout 45s .verification/c1_audio_check
timeout 120s g++ -std=c++17 -O1 -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_c1_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/c1_launcher_check
timeout 90s .verification/c1_launcher_check
timeout 60s g++ -std=c++17 -O2 -Wall -Wextra -Werror tests/kenny_host_rasterize.cpp -o .verification/kenny_host_rasterize
timeout 60s python3 tests/kenny_c1_package.py
```

Also compile/run the existing menu, theme/store, aurora and effects checks below against current source. Production portable headers can be checked strictly with a small include/Draw translation unit; the native capture fixture retains pre-existing embedded font macro warnings.

The source fixture compares all 37 original calls/ranges/formats and the entire feature callback to the approved baseline. C1 checks exercise genuine native input, real PCM generation/mixing/dispatch, scoped successful interactions, profile selector, volume/mute, logo hitbox/drag, transitions/Reduced motion, closing input isolation, repeated launcher cycles and unchanged feature snapshots. The PCM test checks four voices/31 queued commands, mute epochs, throttling, finite inputs, 20,000 allocation-free iterations and 50,000 concurrent producer submissions. Theme/store tests now cover all audio fields and real schema 1 migration without resetting prior preferences. No Guest Reset execution or C2 voice recordings/loader.

`previews/phase_c1/` contains ten actual native PNGs, two original-mixer WAVs, source/hash provenance, self-contained offline image/audio viewer and a 15-entry ZIP. Host screenshots expose unavailable playback honestly; `audio-test-settings.png` is explicitly labeled as a real portable-mixer test sink, not Android output. `launcher-detail.png` enlarges original native crops, without replacing their rendering. PNGs are CPU-rasterized actual ImGui geometry, not Android captures. WAVs are playable actual 48kHz/16-bit mono synthesis/mixer samples; browser playback does not test OpenSL ES.

The external asset owner registers a transparent logo texture and must Clear before deletion/context loss. No asset loader or invented artwork/voice is present. Android build/link, output/latency/callback lifecycle, private-path restart, touch/GPU/resource lifetime and performance require the user's restored SDK/NDK/device. **Stop after C1 for approval before C2.** Historical documentation follows.

# SDK-independent Phase B checks

Run from the repository root. The SDK remains absent; these compile production UI headers with bundled native ImGui and embedded fonts, plus the **exact original** main.cpp panel statements/configuration. No SDK stand-ins or Android runtime claims. Keep assertions enabled; original font-header macro warnings in the menu/capture fixture are pre-existing.

```sh
python3 tests/kenny_host_fixture.py
timeout 120s g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni -I .verification tests/kenny_theme_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/phase_b_theme_check
timeout 60s .verification/phase_b_theme_check
timeout 120s g++ -std=c++17 -O0 -g -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_menu_host_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/phase_b_check
timeout 60s .verification/phase_b_check
timeout 120s g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_aurora_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/phase_b_aurora_check
timeout 60s .verification/phase_b_aurora_check
timeout 120s g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_effects_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/phase_b_effects_check
timeout 60s .verification/phase_b_effects_check
timeout 120s g++ -std=c++17 -O0 -g -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification tests/kenny_phase_b_capture.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o .verification/phase_b_capture
timeout 60s .verification/phase_b_capture
timeout 60s g++ -std=c++17 -O2 -Wall -Wextra -Werror tests/kenny_host_rasterize.cpp -o .verification/kenny_host_rasterize
timeout 60s python3 tests/kenny_phase_b_package.py
```

The extractor compares all 37 binding/range/format statements and the entire feature callback body to 58cbf6c, and generates a read-only approved aurora header under `.verification/` for exact behavior comparisons. The theme test exercises genuine 0600 filesystem writes, all preferences/themes through fresh Store instances, malformed/unavailable storage, atomic saves and no idle rewrites. It also compares 1,800 default physics steps and byte-identical native draw geometry against the approved Phase A code. Asset tests use diagnostic texture handles solely to inspect UVs/rounded geometry and provider lifecycle; they supply no screenshot artwork.

The menu suite retains all original native binding/range/keyboard/navigation/drag/close/scroll/viewport checks, adds 90 native theme-card switches, functional Aurora options, all-panel routing, all 30 original checkbox sites under all three themes at 640×360, inactive physics/provider pause and Reduced asset frame hold. A 1,000-frame allocation/capacity loop cycles seven panels and all three themes. The destructive/platform ResetLogin callback is never invoked. Regression captures use a separate `phase_b-regression-` prefix and do not overwrite approved Phase A evidence.

`previews/phase_b/` contains 13 actual native captures, two labeled contact sheets, source/state/hash provenance, a self-contained offline viewer and an 18-entry ZIP. Anime screenshots show the honest missing-artwork surface; no placeholder art is fabricated. Captures use actual ImGui draw triangles/atlas CPU-rasterized, with a neutral backdrop rather than the game or Android renderer. Android build, activity-private storage/restart, real touch/GPU/asset lifecycle and mobile performance remain unverified.

Stop after Phase B. Historical Phase A/earlier documentation below reflects those original checkpoints; current Aurora integration covers all seven panels.

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

# Classic Electric Starfield

See [CLASSIC_ELECTRIC_STARFIELD.md](../CLASSIC_ELECTRIC_STARFIELD.md). The existing
`run_ui_regressions.py --sanitizers` runner includes the strict bounded renderer/
clock/persistence check. `kenny_electric_capture.cpp` exercises actual native
Classic preferences/inputs and emits real draw data. `kenny_electric_baseline.py`
reads a374ad0 UI headers without changing the checkout; packaging compares matched
Aurora/Anime output and exports authentic continuous render frames. No Android
GPU/FPS or audio-output claim is inferred from host checks.

# Supplied Anime video and photo launcher

`run_ui_regressions.py --sanitizers --user-media .verification/user-media --presentation-media .verification/anime-video-logo/private`
adds the real supplied-media PNG/ownership/persistence/pacing test. The native
capture uses actual movie frames decoded offline with FFmpeg and real ImGui;
`kenny_video_logo_package.py` exports private screenshots/video/viewer. No Android
GPU/MediaCodec proof is implied. See [ANIME_VIDEO_LOGO.md](../ANIME_VIDEO_LOGO.md).
