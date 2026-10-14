## Audio recovery checkpoint A

Preserve working full themes, launcher/layout and native startup. Only the existing
Anime Settings voice section gains a configured event selector, silent Test Voice
action and truthful diagnostic results. Queued/cooldown/speakers are distinct.
User installed only the .so; media installation remains an authorized host task.
The new logo is JPEG, not alpha PNG; video ZIP integrity fails. Checkpoints B/C
remain separate. See AUDIO_RECOVERY_CHECKPOINT_A.md.

## Supplied media integration — full UI continuation

No theme/layout redesign. User-supplied Rias JPEG converted to a transparent,
RGB-preserving alpha cutout with explicit user approval. Existing Anime renderer,
opacity/visibility/contain/clipping and launcher remain. No separate logo provided:
K emblem fallback remains. Four private named OGGs convert offline to existing PCM
format and map only to Aim ON/OFF, Bullet ON and Extra navigation (confirmed).
No user media is published; see SUPPLIED_MEDIA_INTEGRATION.md for installation.

## Full UI continuation — working baseline 7934582

Preserve the owner-confirmed full build and empty Helper/bypass.h. Existing
Classic/Aurora geometry and physics remain unchanged. Anime Settings adds artwork
visibility and optional control voice feedback inside the existing character
section. New optional theme_switch/settings_navigation mappings use the existing
voice engine and cooldown. Schema 4 preserves prior preferences. No substitute
Rias media is introduced: installed recordings are the named Cici Fyre alternative;
Rias artwork/launcher/original recordings remain missing. See FULL_UI_CONTINUATION.md.

# KennyPvtHax — source map and reference design

## Current C3 — asset validation, 10 October 2026

No UI redesign: all 24 tracked `jni/` files remain byte-identical to `6f300ae`.
Five real CC0 Cici Fyre clips now populate a separately named English alternative
voice pack using the existing C2 registry/Settings/C1 mixer. They are not original
Rias dialogue. Seven existing event mappings, independent gain/mute/cooldown and
schema-3 persistence work without additional application code. Rias artwork,
launcher and original voices remain missing/unverified. No alpha or quality
claim is made for undownloaded candidate images; K/artwork fallbacks remain.

Actual C++/ImGui host captures under `previews/phase_c3/` show the available pack,
explicit missing artwork and disabled Android playback state. Separate host-PCM
controls and WAV demonstrate the actual portable mixer, not Android audio.
Matched Aurora and Classic are pixel-identical to C2. Contact sheet/Settings/
small scrolling/K fallback inspected; no unrelated layout change needed.
See [C3_ASSET_VALIDATION.md](C3_ASSET_VALIDATION.md) for sources, rights review,
machine speech verification, full-length conversion and remaining requirements.
No private media publication; stop after C3, Android verification deferred.

Stages 1–5.5 and Stage 5.6 Phase A completed, 10 October 2026 UTC. **Current identity: Crimson Eclipse; Phase B adds Aurora / Anime / Classic themes.** Aurora remains the default across all seven panels. Phase C1 adds the K launcher and UI audio. Phase C2 adds local character packs, transparent PNG rendering and optional character voices through that same audio engine. Rias media remain missing; Stage 6 remains deferred. Earlier sections describe historical checkpoints.

## Phase C2 — character integration, 10 October 2026 UTC

The C1 design remains intact. Anime settings extend the existing Settings table,
with compact character/artwork/launcher and voice sections. Selectors have minimum
36-pixel height. Missing media are stated explicitly; unavailable launcher/voice
controls are disabled. No Rias render or voice was acquired with established
permission, so the actual result is a selected Rias definition, dark Anime
surface, K launcher and optional original C1 tones.

`KennyCharacters.h` centralizes character metadata, bounded local manifests,
cached artwork/voice packs, event mapping and controlled variation.
`KennyAssetIO.h` implements strict relative-file access and RGBA PNG/PCM WAV
decoding using existing zlib, without new dependencies. `KennyCharacterGL.h`
provides native GLES upload/deletion and optional offline APK-to-private staging.
No runtime network requests or per-frame file loads occur. Textures are cached;
context loss invalidates references after clearing the launcher. Full aspect-fit
cutouts sit inside the right content region behind controls, preserving alpha,
silhouette and existing dimming. No background rectangle is added.

The C1 OpenSL player, dispatcher, generated profiles and four effect voices remain.
One recorded-PCM character channel, epoch cancellation, independent voice gain,
cooldown and up-to-three variations add optional voices without overlapping
dialogue. Only successful interactions route audio. Global mute and leaving Anime
suppress/cancel character playback. Login/skin/error names remain integration
hooks; no new gameplay/authentication triggers exist. Details and the event table
are in [ANIME_CHARACTER_ASSETS.md](ANIME_CHARACTER_ASSETS.md).

Private appearance schema 3 retains the existing filename and migrates schemas
1/2 without changing old values. New character/pack/artwork/voice/launcher fields
are normalized; invalid C2 tails preserve valid earlier preferences. Existing
37 bindings, whole panel callback, SDK logic, native input and approved Aurora
physics/draw formulas remain untouched.

Host evidence includes strict portable builds, original regressions, byte-exact
PNG alpha/corruption tests, safe paths/FIFO/symlink rejection, WAV validation,
registry extension/fallback, voice controls/cooldown/routing, 500 switches,
10,000 allocation-free cached dispatch/mix iterations, filesystem migration and
restart, aspect-fit geometry, native selection and 640 scrolling. Eight new
production screenshots, two real C1 captures and two composites are under
`previews/phase_c2/`. Classic pixels match C1 exactly; Aurora differs by one
8-bit channel level at one header pixel. Settings, small viewport, K fallback
and comparison were inspected. These are CPU-rasterized native ImGui output,
not Android captures. Diagnostic test pixels/tones never appear as Rias media.

No media was downloaded, invented, committed or published. PNG requires actual
8-bit RGBA transparency; WebP has no available decoder. Voices require bounded
PCM16 WAV; compressed audio is unsupported. Restore the real SDK/NDK and install
permitted media before verifying APK staging, compile/link, GPU alpha/context
lifecycle, OpenSL voice playback, real touch and performance. Stop after C2;
do not start key-entry or release work.

## Source baseline

- Original upload: `anony.zip`, 1,104 entries, 77,110,862 uncompressed bytes, all under `jni/`. Extracted without overwriting any existing files into `/workspace/KennyPvtHax`.
- No `AGENTS.md`, `CODEX_PROGRESS.md`, or Git history was present. Existing orange/charcoal styling in `ClaudeTheme.h` and the three supplied `.bak` files were retained.
- Application: C++17 native Android shared library, Android API 21+, `arm64-v8a`, static C++ runtime. This archive is the native source component, not a complete APK project.
- UI: bundled Dear ImGui `1.85 WIP` (`IMGUI_VERSION_NUM` 18416), immediate-mode rendering with Android and OpenGL ES 3 backends. Keep this version's APIs; current ImGui examples may use incompatible enums/signatures.
- Build: `jni/Android.mk` and `jni/Application.mk`, Android NDK `ndk-build`. `LOCAL_MODULE := Anoy` is a library output/linkage identifier, not a display name; retain it.
- Dependencies: bundled ImGui, embedded TTF/icon font arrays, nlohmann JSON, curl/OpenSSL, native app glue, and existing native integration/static libraries. No dependency additions are needed for the redesign.
- There is no app-level manifest/display-name resource or splash asset in this archive. ImGui's example Android manifest belongs to third-party sample code and must retain its original identity.

## UI ownership

| Responsibility | Existing source / entry point |
| --- | --- |
| Main window and initialization | `jni/main.cpp`, `_eglSwapBuffers`, approximately lines 925–1127 |
| Menu position/size/dragging | Main ImGui window: first-use size is 46% of framebuffer width and 58% of height; ImGui supplies dragging. Separate draggable `##toggle` window begins at `(20,20)` |
| Open/close state | Local static `ShowMenu` and `opened` in `_eglSwapBuffers`; `Claude::PrimaryButton` toggles visibility; `ImGui::Begin` supplies the close button |
| Navigation | Five vertical `Claude::NavItem` calls in `main.cpp`; `Settings::Tab` (1–5) is defined near the end of `Helper/definition.h` |
| Panel content/bindings | `main.cpp` tab branches, approximately lines 1054–1114 |
| Palette/background/spacing | `jni/ClaudeTheme.h`, `Claude::Dark`, layout constants, `Claude::Apply` |
| Buttons and section headings | `Claude::PrimaryButton`, `SecondaryButton`, `NavItem`, `SectionHeader` |
| Checkbox and slider rendering | Standard ImGui calls in `main.cpp`; implementation in bundled `imgui_widgets.cpp`. Extend application wrappers instead of modifying third-party widgets |
| Configuration globals/defaults | `jni/Helper/definition.h`, `Cheat::Esp`, `Aimbot`, `BulletTrack`, `Memory`; startup defaults also set in `AutoEspOn` in `main.cpp` |
| Overlay render integration | Existing EGL swap callback and OpenGL3 draw-data backend; keep integration and frame order |
| Input | `main.cpp`: `_OI` and `_HAI`; Android backend maps key and pointer input and supports physical-mouse wheel scrolling. Touch coordinates are scaled to framebuffer coordinates |
| Main visible branding | `main.cpp` ImGui window title, `Helper/definition.h` HUD watermark, `Lua_Buffer.cpp` status popup title |
| Existing reset callback | `Guest Reset` invokes `ResetLogin`; preserve callback and avoid invoking it during UI verification |

ImGui child windows already provide vertical scrolling. Keyboard mappings exist in the backend, but keyboard navigation is not explicitly enabled by the application; the redesign must not promise unsupported text input/soft keyboard behavior.

## Binding inventory to preserve

All addresses below are the existing control bindings, not proposed backend changes. Every control must remain reachable after navigation changes.

| Current panel | Controls and original bindings |
| --- | --- |
| Player ESP (tab 1) | ESP line → `Cheat::Esp::Line`; ESP name → `Name`; ESP distance → `Distance`; ESP health → `Health`; ESP skeleton → `Skeleton`; ESP box → `Box`; Alert → `Alert`; Loot box → `LootBox`; Counter → `Counter`; Vehicle name → `Cheat::Esp::Vehicle::Name` |
| World ESP (tab 2) | Throwable → `Cheat::Esp::Throwable`; Enemy weapon → `WeaponName`; Target line → `Target` |
| Aimbot (tab 3) | Enable aimbot → `Cheat::Aimbot::Enable`; Enable FOV → `EnableFov`; conditional Aim FOV → `Radius` (float 0–400); conditional Show FOV circle → `ShowFovCircle`; Aim range → `Range` (float 0–400, metres); Aim smoothing → `Smoothing` (float 1–4, `%.0f`); Recoil compensation → `RecoilSet` (float 0–2); Visibility check → `VisCheck`; Ignore knocked → `IgnoreKnock`; Ignore bot → `IgnoreBot` |
| Bullet track (tab 4) | Enable bullet track → `Cheat::BulletTrack::Enable`; Enable FOV, conditional Aim FOV, conditional Show FOV circle, Aim range, Visibility check, Ignore knocked, Ignore bot use the **same Aimbot variables/ranges** as tab 3; Force headshot on full → `Cheat::BulletTrack::ForceHeadshotWhenFull`; Tracking accuracy → `TrackingAccuracy` (integer 1–3, `%d/3`) |
| Extra features (tab 5) | Small cross → `Cheat::Memory::Small`; X-hit effect → `Hit`; iPad view → `IPad`; 6-hour fixer → `IslandBp`; Guest Reset → `ResetLogin()` |

There are 37 checkbox/slider call sites, including repeated shared controls. Unused configuration globals are not additional functioning UI features and should not be exposed as new gameplay controls by this redesign.

No feature configuration save/load implementation or preset UI was found in the active application sources. ImGui's default `imgui.ini` mechanism remains available, but the main and toggle windows use `NoSavedSettings`. The file write in `Lua_Buffer.cpp` is a debug log, not feature persistence. Keep existing identifiers, paths, defaults, shared bindings, and conditional visibility. Do not copy reference licensing or pretend save/load functionality exists.

## Inspected references

- Both supplied current-UI screenshots show the same vertical five-section menu, warm orange square checks, chunky sliders, orange menu toggle, and red `Anoy` HUD watermark.
- MP4: 32.810667 seconds; 1920×872; 30 fps. Seven frames were extracted **once** with FFmpeg at 5, 9, 12, 15, 18, 24, and 27 seconds, and all seven were inspected.
- Frame directory: `.reference/frame-05.jpg` through `frame-27.jpg` at those timestamps, ignored by Git. Keep these files for visual comparison; do not re-extract the video each stage.
- Frame 05: Visual/Players, three columns, circular checkboxes.
- Frame 09: Visual/360 alert, rounded dark dropdowns, thin sliders.
- Frame 12: Aim/Target, three columns, values above slider tracks.
- Frames 15 and 18: Aim/FOV, two equal columns, gentle purple ambient highlights at different positions/intensities.
- Frame 24: Style/Look, segmented pills, three columns.
- Frame 27: Settings, pill buttons and three columns. Reference login/license/preset details are visual examples only.

## Measured visual proportions

- Main panel bounds approximately `(392,80)` to `(1527,793)` in the 1920×872 video: 1,135×713, about 59% of screen width and 82% of height. Center approximately `(960,436)`.
- Outer radius approximately 32–36 px. Thin lavender-gray perimeter, nearly black center, purple ambient glow confined to the panel, slight translucency near edges. No requirement to darken the underlying game.
- Header approximately 100 px high, bottom divider at y≈180. Compact lavender identity mark at the left, five evenly spaced outline-icon navigation labels, close glyph on the right.
- Active primary tab has lavender icon/text and a thin rounded underline. Inactive labels are muted lavender-gray.
- Secondary row approximately 74 px high (y≈180–254), centered rounded pill tabs with subtle borders and translucent purple selected fill.
- Content has two or three equal columns, thin dim vertical separators, roughly 24–28 px outer padding, left-aligned headings. Avoid the old heavy nested cards.
- Reference text is a clean sans-serif: headings about 28 px, control labels about 25–26 px at recorded resolution. The existing embedded base font and Font Awesome icons should be reused first; scale for the actual framebuffer.
- Circular checkboxes are about 42–44 px in diameter, with a dark centered tick when enabled; disabled outlines are subdued purple-gray. Rows are about 65–67 px apart. Make the label part of the hit target.
- Sliders have roughly 8–9 px rounded tracks, lavender filled segments, 25–27 px pale circular handles; label and value sit above the track. Retain numerical formats/ranges and ImGui interaction semantics.
- Dropdowns and buttons are dark outlined pills about 50–52 px high; selected buttons use lavender fill with dark text.
- Small sparse white/lavender stars and a few brighter moving points decorate the panel; the purple corner glow changes between timestamps. A static sample does not establish exact hover timing or opening animation duration.

## Reusable implementation plan (future stages)

1. **Stage 2:** evolve `ClaudeTheme.h` into application-owned black/lavender styling without a second competing theme. Build a rounded panel/header, primary `Visual | Aim | Misc | Style | Settings`, and a secondary pill row using existing ImGui buttons and shared theme helpers. Keep `Settings::Tab` meanings for existing feature panels. Route Visual to Player/World, Aim to existing Aimbot, Misc to Bullet track/Extra features. Reserve Style and Settings for interface options and existing application actions. Use a branded header/initial instead of copying the reference logo.
2. **Stage 3:** use scrollable two/three-column layouts for existing Visual and Aim controls. Preserve every inventory entry and shared pointer binding. Responsive column reduction and scaled fonts must accommodate smaller overlay surfaces; do not multiply style scale every frame.
3. **Stage 4:** lay out Misc, Style, Settings. Only introduce appearance preferences that actually affect the interface. Retain the existing reset callback. No new gameplay controls, authentication, licensing, bypass behavior, or fictitious presets.
4. **Stage 5:** polish the reusable application checkbox/slider/pill helpers (checkboxes/sliders implemented early in Stage 3 at the user's explicit request). Draw bounded particles/glow through the menu's clipped draw list, with fixed storage and no new dependencies. Animations should be time-based and lightweight. Do not change global ESP/game colors when styling UI chrome.
5. **Stage 6:** compile using the real Android NDK and missing SDK once available, inspect the actual UI, and compare cached reference frames. Report static checks separately from device/build evidence.

## Baseline limitations

- No Android NDK / `ndk-build` is available in the current workspace. Host `g++`, Git, FFmpeg, and FFprobe are available.
- The supplied archive lacks the entire `jni/SDK/` directory, including `PUBGM_BangJO.hpp` required by `SDK.hpp` and six `.cpp` files explicitly listed in `Android.mk`. A complete native build cannot succeed from this upload alone.
- Stage 4 clarification from the user: the SDK was intentionally excluded to reduce upload size. Keep every integration intact; native compilation will use the user's original SDK and compatible NDK later.
- Existing menu-close flow resets `opened` and hides the menu on the following frame. Global and render-local `ShowMenu`/`opened` names overlap. Retained in Stage 1; validate behavior carefully when implementing Stage 2.
- No device/emulator overlay preview or real application runtime verification was performed in Stage 1. Recorded dimensions are design targets, not validated final layout measurements.

## Git/checkpoint policy

A local Git repository was initialized because the upload had none. The baseline commit selectively tracks the three branding-bearing sources, existing theme header, build makefiles, and `.gitignore`; other original sources remain on disk and in the original archive. Future stages should explicitly add only the files they modify. The login header, original backups, static libraries, generated artifacts, and reference images are excluded. Do not use `git add .` across the unreviewed legacy source tree.

## Stage 2 implementation — completed

- `jni/ClaudeTheme.h` now provides the black/lavender palette, neutral hover feedback, horizontal `NavItem` buttons, and reusable outlined `PillTab` buttons. The existing namespace/file is retained to avoid introducing competing themes.
- `jni/KennyMenu.h` owns window measurement, viewport constraints, header dragging/close control, navigation state, animated selection underline, secondary pills, and a separate scrollable content container. It only uses application styling and the bundled ImGui API; there is no SDK/platform/backend dependency in the shell.
- `jni/main.cpp` integrates the shell through `KennyMenu::Draw` and supplies its original five panel branches as a callback. Their tokens, 37 control call arguments, conditional FOV controls, and `ResetLogin` callback are unchanged. EGL frame order, Android input handlers, startup defaults, and the existing Menu/Close toggle logic remain unchanged.
- `Settings::Tab` retains values 1–5. The primary category is independent UI state: Visual remembers 1/2, Aim selects 3, Misc remembers 4/5. Style/Settings retain the last feature tab but render only their reserved containers, so no feature controls leak into those sections and no new backend tab values are created.
- Style has an Appearance container; Settings has a General container. Both clearly state that no settings are available yet, with no fabricated save/load or appearance actions.
- At 1920×872, the default shell is approximately 1,133×715, centered near `(394,78)`, with a 34 px radius, 100 px primary header, and 74 px secondary band. This closely follows the reference's shell geometry; it is not a claim that unfinished panel/control styling matches the final reference.
- The full KennyPvtHax name occupies the left header area, so the primary tabs begin farther right than the reference's logo-only layout. Navigation uses the existing Font Awesome glyphs rather than copying the reference logo/assets.
- Compact layouts split branding/close and primary navigation into two header rows. Both primary and secondary controls have bounded interactive areas; content scrolling leaves navigation fixed. The window is initially centered and retains its dragged position on subsequent frames/reopens, constrained when the viewport changes.
- This ImGui version multiplies a child font scale by its parent's. The root uses `2.0 * layout.scale`; the content child uses `1.0` to inherit it without multiplying twice. Global font scaling and ESP text colors are not changed.
- Navigation padding is smaller than settings-control padding so the Settings label fits even at the smallest tested viewport. The selection underline uses a single time-based interpolation value with no animation dependency or per-tab state allocation.

### Stage 2 validation and visual evidence

The local `.verification/` directory contains a host harness, extracted UI/configuration fixture, cached core object files, indexed draw data/font atlas, and a small CPU rasterizer. All are ignored by Git. The harness compiles the **production** `KennyMenu::Draw`, bundled ImGui core, and original panel statements with their SDK-independent configuration declarations. It excludes Android/game integration; the destructive reset is a fail-fast test boundary and was never invoked. It does not replace SDK headers or alter application callbacks.

- PASS: actual button input routes through all five primary categories and all five original panels, with remembered secondary tabs and reserved sections preserving backend tab values.
- PASS: header drag changes and retains window position; close changes the existing `opened` state; reopening the shell retains navigation state.
- PASS: original checkbox and FOV controls change their bound variables, FOV-dependent content appears, and an original slider changes its bound value within the preserved range.
- PASS: content scrolls while the root/navigation position remains fixed; all pushed ImGui style/color entries are balanced.
- PASS: viewport bounds and primary-label fit at 2340×1080, 1280×720, 960×540, and 640×360, plus initial rendering at 1920×872.
- PASS: static comparison with commit `8bffdcd` shows all 37 original control calls/ranges/formats unchanged and complete feature-panel bodies preserved modulo indentation. Code outside the main window is unchanged apart from the new header include and theme comment.
- PASS: new shell/theme header syntax checked with `g++ -std=c++17 -Wall -Wextra -Werror -fsyntax-only`; host ImGui shell build and interaction harness executed successfully; `git diff --check` passed.
- Inspected actual ImGui draw-output previews at `.verification/visual-1920.png`, `aim-1920.png`, `visual-1280.png`, and `visual-640.png`, compared with cached frame 05. These are CPU rasterizations of the shell and original controls using the supplied fonts, on a neutral background, without the game or floating toggle. Corrected inconsistent font scaling and narrow-tab text padding before finishing.
- Original embedded `fontAwesome.hpp` emits malformed/redefined-macro warnings in the host fixture; the file remains untouched. The new SDK-independent shell header passes its strict syntax check without warnings.
- Still blocked/unverified: complete Android native compilation/linking (missing SDK and NDK), device touch integration, live game overlay, GPU appearance, runtime frame rate, and final visual fidelity. No package/environment installation was performed.

For local reproduction while `.verification/` exists: run `python .verification/make_harness.py`, compile `.verification/menu_check.cpp` with the four bundled ImGui core `.cpp` files and `-I jni -I .verification`, run the resulting binary with `timeout 30s`, and rasterize its `.draw` files using `.verification/rasterize.py`. Generated objects/binaries, fixture files, and previews are not application dependencies.

## Stage 3 — completed: crimson Visual and Aim panels

The user explicitly changed the accent system to crimson/fire-red and requested circular checkboxes/thin sliders in Stage 3. Those controls are implemented now rather than deferred to Stage 5. Stage 2 shell geometry, routing, remembered subtabs, close/drag, and isolated content scrolling remain intact.

### Current palette and typography

| Role | Current value |
| --- | --- |
| Root background | `#08070A`, alpha 0.97 |
| Secondary surface | `#141014`, alpha 0.72 |
| Raised/control surface | `#1A1012` |
| Inactive slider track | `#26171B` |
| Primary accent | `#C1121F` |
| Selected text/hover highlight | `#E63946` |
| Small control highlight ring | `#FF5A5F`, alpha 0.12–0.24 |
| Dividers and perimeter | `#7A1C24`, subdued alpha |
| Primary text | `#F5F2F2` |
| Secondary text | `#B7A9AC` |
| Active secondary pill | `#34151C`, border `#C44551` |

The same embedded typeface is baked once at 32 px, with 30 px merged icons, into a dedicated `KennyMenu::Font`. The shell pushes/pops this font and uses local `layout.scale`; the content inherits a factor of 0.875 (28 px at reference scale), with 10 px row spacing. This replaces the historical Stage 2 enlargement of a 16 px atlas and improves glyph sharpness. Original base/toggle, ESP, fallback fonts and global font scale remain unchanged. No external typeface/dependency was introduced.

### Layout and inventory

- `KennyPanels::Begin/Section/EndSection/End` uses the bundled ImGui table API, equal stretch columns, dim inner dividers, matching heading baselines, and short red title markers. Column count derives from available width and font size; narrow windows reduce columns and retain native child scrolling. Styling and item-width pushes are balanced, including the non-visible table case.
- Player ESP: **Player** (line, skeleton, health, box), **Labels** (name, distance, counter), **World** (alert, loot box, vehicle name). All ten original bindings remain in tab 1; wide windows use three columns.
- World ESP: **Threats & targeting** (throwable, target line), **Equipment** (enemy weapon). All three original bindings remain in tab 2; wide windows use two columns. This panel has only three genuine settings. It retains the shell proportions and consequently has free space below its compact groups; no filler settings were invented or controls moved between panels.
- Aimbot: **Targeting** (enable, range), **Filtering** (visibility, ignore knocked/bot), **Tuning** (smoothing, recoil), **Field of view** (enable FOV, conditional radius/show circle). Two balanced columns and two group rows replace the single long list. All ten original call sites/ranges/formats/FOV conditions remain in tab 3.
- Misc/Extra receive the same reusable checkbox/slider artwork to keep the interface consistent. Their layout/order, variables, conditions, and reset callback are unchanged; Stage 4 organization and reserved Style/Settings functionality remain pending.

### Native controls with custom artwork

`KennyControls` registers real ImGui controls; it does not substitute visual-only items or write configuration independently. Checkboxes keep native IDs, focus/activation, whole-label hit areas, change return values, and minimum 36 px interaction height. Native square artwork is transparent; a clipped circular crimson fill/outline and centered white tick are drawn over the native item. A circular focus/hover outline replaces the checkbox's rectangular navigation artwork.

Sliders keep the caller's original label ID using this bundled version's `PushOverrideID` and native `SliderScalar`. Labels/formatted values appear above thin rounded tracks; a small circular handle follows native linear grab geometry, including integer grab sizing. Narrow headers place the numeric value on a second line. Dragging, native keyboard behavior, and Ctrl-click numeric entry are delegated to ImGui. Drawing clamps only the visual ratio, without changing actual values/ranges/defaults. The Android application's existing keyboard support is unchanged; host numeric-entry tests do not imply Android soft-keyboard support.

There are no particle systems, new opening animations, gameplay changes, configuration keys, login/licensing changes, SDK substitutes, or new dependencies in Stage 3. Small control rings use bounded circle segments, not blur passes. Runtime GPU performance remains unmeasured.

### Verification and actual preview provenance

- Strict C++17 syntax check passed for `KennyMenu.h` and `KennyPanels.h` (including theme/control headers) with `-Wall -Wextra -Werror`.
- Production UI host harness passed: every primary category/secondary route, remembered tabs, reserved-container isolation, checkbox pointer/native navigation activation, all 30 original checkbox call sites toggling/restoring actual variables through label hits at 640×360 after scrolling into view, FOV-dependent visibility, all original float slider endpoints (range/FOV 0–400, smoothing 1–4, recoil 0–2), integer endpoints 1–3, and Ctrl-click typed value.
- Host checks passed for drag/position retention, close/reopen, scrolling with fixed root/navigation, balanced font/style/color stacks, no horizontal control clipping in tables, viewport bounds and primary-label fit at 1920×872, 2340×1080, 1280×720, 960×540, and 640×360.
- Static comparison with `042e39c` passed for all 37 original control sites, per-panel membership, exact bindings/ranges/formats, unchanged Misc/Extra bodies modulo wrapper namespace, unchanged configuration/default declarations/build files/branding, and unchanged gameplay/input/EGL integration. Allowed changes outside the feature branches are only the UI helper include, theme comment, and dedicated menu-font initialization.
- Inspected all three final 1920×872 previews, Player at 1280×720, and all three panels at 640×360. Corrected enlarged-font softness, Aim vertical fit, and inherited table-heading baseline differences. At small resolutions the captured top of scrollable content is intentionally partial; labels/navigation do not overlap horizontally.
- Public artifacts: `previews/stage3/{player-1920,world-1920,aim-1920}.png`, smaller PNGs, `index.html`, `verification.json`, `README.md`, and `stage3-previews.zip`. Every PNG passed signature/chunk-CRC/Pillow verification/full decoding; the offline viewer embeds byte-identical main PNGs with download links. ZIP integrity passed. All generated artifacts are ignored by Git; Stage 2 images/viewer remain intact.
- These are **actual production ImGui UI draw-data rasterizations**, using exact panel statements extracted from `main.cpp`, original SDK-independent configuration declarations, embedded fonts, and host test state. The CPU rasterizer is a verification-only rendering backend, not an application UI simulation. Not AI imagery or an Android/game/GPU capture. The host enables some test states to demonstrate checks/FOV; application defaults are unchanged.
- Still blocked: missing `jni/SDK/` and Android NDK; no full native application compilation/linking, device touch/overlay behavior, GPU appearance/performance, or final on-device fidelity verification. Original font-header macro warnings remain unrelated and untouched. A temporary edit-tool transport error recovered on retry; no source work was lost.

Local Stage 3 reproduction, while the ignored verification files exist: run `python .verification/stage3_fixture.py`; compile `.verification/stage3_check.cpp` with the cached four ImGui core objects (or the real bundled core `.cpp` sources), `-std=c++17 -I jni -I .verification`; run `timeout 30s .verification/stage3_check`; rasterize `.verification/stage3-*.draw` through `.verification/rasterize.py`. Its `atlas.rgba` is the current Stage 3 atlas. The old Stage 2 harness/draw output are historical; regenerate their matching atlas with their original executable if needed. Neither harness is part of the Android build.

## Stage 4 — completed: Misc, Style, and Settings

Resumed verified commit `f744bc4` without reverting earlier work, extracting the archive, or repeating video processing. Existing Stage 3 previews and these design notes guided the implementation. The user clarified that `jni/SDK/` was intentionally excluded: all SDK/gameplay integrations stay untouched and full native compilation remains deferred to their original SDK/compatible NDK.

### Misc inventory and layout

- Bullet track uses the existing `KennyPanels` equal-width layout: **Tracking** (enable, force headshot on full, tracking accuracy), **Filtering** (visibility, ignore knocked/bot), **Field of view** (enable FOV, conditional radius/show circle, range). All ten original call sites remain in tab 4 with their exact pointers, ranges, and formats. The FOV/filter/range controls still share the original Aimbot variables. No feature behavior was changed.
- Wide reference-size and 1280×720 windows show three balanced sections. Responsive column measurement now optionally accounts for the widest checkbox's actual text, native touch target, and table padding; Bullet track supplies its long original label to prevent narrow-column clipping. Existing Visual/Aim calls retain their original default measurement and bodies.
- Extra features uses **Presentation** (small cross, X-hit, iPad view) and **Utilities** (6-hour fixer, Guest Reset). All four original checkbox bindings and the original `ResetLogin()` callback remain in tab 5. Guest Reset is rendered through the shared pill-button helper; its callback and activation semantics are unchanged and it was never invoked during host verification.
- New `KennyControls::Button` and `Choice` reuse the existing `Claude::PillTab` native-button implementation. Action pills fill their group column; two-option choices have equal width, native IDs/focus/activation, clear selected states, and a minimum 36 px height. `KennyPanels::Note` wraps secondary text within the same column.

### Style and Settings contain working presentation functionality

`KennyAppearance.h` is application-owned, SDK-independent UI code. `Preferences` resides in the existing static menu state, separate from every feature/configuration variable. It is session-only: changes persist through navigation and menu close/reopen, and restart restores defaults. No file I/O, feature persistence changes, new configuration keys, or save/load buttons were introduced.

| Panel / group | Item | Actual effect |
| --- | --- | --- |
| Style / Surface | Menu opacity, 85–100%, default 97% | Scoped root-window background alpha. Text/control alpha and the global overlay palette are unchanged. Native numeric entry is bounded for this new preference only. |
| Style / Layout | Standard / Compact row spacing | Content row spacing changes from `10 * layout.scale` to `6 * layout.scale`. Checkbox/slider/button touch targets remain at least 36 px. Default Standard preserves Stage 3 spacing. |
| Settings / Menu | Center window | Requests centered positioning on the following frame, using the existing viewport measurement/constraints; navigation and appearance remain intact. |
| Settings / Menu | Reset appearance | Restores only 97% opacity and Standard spacing. Original feature states, callback behavior, and menu position remain intact. |
| Settings / About | KennyPvtHax, Crimson / Fire Red, Android landscape interface | Minimal read-only application information. No fabricated version, license, account state, or backend feature. |

Style and Settings render inside the existing fixed-navigation/scrollable-content shell and never invoke the feature callback or create backend tab values. The Appearance/General secondary containers remain. Existing header drag/close, sizing, fonts, red theme, icons, selection interpolation, and feature routing are retained. Empty space below these deliberately small genuine panels is retained rather than filled with dummy settings.

### Verification and preview evidence

- Strict SDK-independent C++17 header syntax check passed with `-Wall -Wextra -Werror`; `KennyMenu.h` transitively compiles the new appearance/panel/control helpers.
- Compiled and ran `.verification/stage4_check.cpp` against the real bundled ImGui core with `IMGUI_ENABLE_TEST_ENGINE`. Its built-in item hooks observe actual native item registration for new buttons/choices/opacity input; they are verification-only, not application dependencies. Exact feature statements are extracted from current `main.cpp` with their original SDK-independent configuration declarations. No SDK replacements were created.
- Passed retained Stage 3 host checks: all five categories/five feature panels, tab memory, all 30 original checkbox call sites toggling/restoring bound variables through labels at 640×360 after scrolling, float endpoints (range/FOV 0–400, smoothing 1–4, recoil 0–2), integer endpoints 1–3, native checkbox navigation activation and Ctrl-click numeric entry, drag/close/reopen, scrolling, balanced stacks, viewport bounds and primary label fit.
- Passed Stage 4-specific checks: Bullet track FOV-dependent visibility, shared range variable retained across Misc/Aim, native Guest Reset item accessible with preserved minimum height, live opacity 85/100 endpoints and scoped background alpha, both spacing choices changing actual content spacing, numeric-entry bounds, Center window after dragging, Reset appearance preserving a snapshot of every original feature variable, and appearance state surviving close/reopen.
- Native item rectangles fit their table columns horizontally; all four new panels and both spacing modes preserve navigation/accessibility at 1920×872, 2340×1080, 1280×720, 960×540, and 640×360. At small sizes content scrolls below the visible region, with both navigation rows fixed. Wrapped informational text stays within its column.
- Static comparison against `f744bc4` passed for all 37 original control arguments, per-panel membership, ranges/formats/bindings, exact unchanged Visual/World/Aim branches and all `main.cpp` code outside Misc, retained Guest Reset callback, and unchanged configuration/default declarations, branding, build files, SDK integrations, and crimson palette.
- Visually inspected all four final 1920×872 previews, Bullet track at 1280×720, and all four panels at 640×360. No new visible horizontal clipping or overlap found. Host previews do not establish final Android/reference/GPU fidelity.
- `previews/stage4/` contains `bullet-1920.png`, `extra-1920.png`, `style-1920.png`, `settings-1920.png`, five smaller PNGs, self-contained `index.html`, `verification.json`, `README.md`, and `stage4-previews.zip`. Nine PNG signatures/chunk CRCs/Pillow integrity/full decodes, eight byte-exact viewer image/download embeds, and ZIP integrity passed. Earlier Stage 2/3 PNG hashes were verified unchanged.
- Preview provenance: production `KennyMenu::Draw`, `KennyAppearance`, actual extracted feature panels, shared controls/layout, original configuration declarations, bundled fonts/ImGui, host test state, and CPU rasterization of emitted indexed draw data/font atlas. These are actual-source UI renders, not AI imagery or a standalone mock UI. Game, floating toggle, Android platform callbacks, GPU rendering, and runtime frame rate are excluded.
- Full Android compilation/linking/device touch/overlay/GPU/performance remain unverified because this workspace intentionally lacks the SDK and has no NDK/device environment. No installation was attempted. The original font-header macro warnings remain untouched.

Reproduction while ignored host files remain: `python .verification/stage4_fixture.py`; compile `.verification/stage4_check.cpp` together with `jni/imgui/{imgui,imgui_draw,imgui_widgets,imgui_tables}.cpp`, `-std=c++17 -O1 -g -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification`, output `.verification/stage4_check`; run `timeout 30s .verification/stage4_check`; rasterize its `.draw` files with `.verification/stage4_rasterize.py` using its matching `stage4-atlas.rgba`. Existing Stage 3 harness/atlas/artifacts remain intact. Generated fixtures, executables, draw data, and previews are ignored by Git.

Next authorized stage: **Stage 5 — Advanced Crimson Visual Effects, Animations, and Final UI Polish**. Stage 4 does not add advanced particles, ambient/opening animations, or new gameplay functionality. Wait for the user before implementing Stage 5.


## Stage 5 — completed: restrained cinematic crimson presentation

The cached video frames 05/18 still govern the rounded proportions, quiet dark center, corner illumination, sparse points and compact horizontal navigation. Stage 5 changes presentation only; the Stage 4 window measurements, typography, responsive tables, content spacing and every main.cpp feature statement remain unchanged. No new gameplay or appearance controls were introduced.

### Actual rendering and timing

- `KennyEffects.h` draws two soft crimson blooms through the existing ImGui draw list/atlas white pixel. A fixed 24×24 triangle grid (625 mesh vertices) uses denser quarter-circle sampling near corners and a 0.25 px conservative inset, avoiding both the first preview's diagonal corner cutoff and floating-point boundary excursions. Colors remain deep red over a nearly black center; no blur passes or textures are created.
- 48 constexpr fixed seeds produce tiny gently drifting ember/star points, faint halos and occasional muted-white cores. Analytic positions avoid particle containers/physics allocations. Visibility testing includes the halo plus antialias fringe against the rounded shell, in addition to draw-list rectangular clipping; core and halo geometry stay inside it. Three low-alpha inward boundary strokes provide depth without drawing over the underlying application outside the menu.
- The visible-only double clock is bounded to 4,096 seconds and only advances when consecutive menu frames are rendered. Hidden frames do no atmosphere rendering or catch-up. Opening/reopening restarts a short exponential atmosphere reveal; layout, text and all interaction remain immediate. Cached effects use the existing frame delta, safely clamped to 0–0.1 seconds; bad timing does not enter animation state.
- The mesh, seeds and animation cache have fixed bounds. Row curve geometry is calculated once per row, not per mesh vertex. Existing ImGui buffers may reserve during warmup and then reuse capacity. No framework/resource creation or unrelated dependency was added.

### Shared transitions and controls

- `KennyMotion.h` supplies color mixing and exponential interpolation. Its fixed 192-entry cache uses widget IDs plus independent channels, resets context/stale items, handles same-frame samples consistently and snaps newly visible controls. Storage is 3,072 bytes. It never stores configuration or native input state.
- Primary navigation uses eased crimson icon/text emphasis and hover surfaces. The existing shared active underline keeps its dimensions, adds a faint halo, and moves without overshoot during rapid category changes. On reopening it snaps to the current category rather than animating across hidden history.
- Secondary pills, action buttons and Style choices ease selected fills, borders and hover feedback using native ImGui buttons with unchanged sizes/IDs/return values. The existing floating toggle becomes rounded with eased surface color; its 84×36 interaction rectangle, release activation and disabled semantics remain native.
- Circular checkboxes ease only fill, outline emphasis, halo and checkmark opacity. Native checkbox hit areas, focus/navigation and immediate bound-value changes are retained. All colors respect the existing style alpha.
- Sliders ease inactive artwork toward programmatic/shared-value changes; active edits snap the handle directly to the native value. The header number always represents the actual value. Track size, ranges, formats, native drag/keyboard/temporary input and call-site bindings are unchanged. Hover/active glow is modest and smoothly decays.
- The title uses a restrained blend of light text and fire red. Ambient depth balances sparse World/Extra/Settings areas without fake options or additional decoration. Original rounded groups, thin separators, fonts, row spacing, crimson defaults, navigation and real Style/Settings actions remain intact.

### Verification and preview provenance

- Strict SDK-independent C++17 header syntax checks and focused production-header tests pass. `tests/kenny_effects_check.cpp` and tests/README.md make the math, input, clipping and buffer-stability checks reproducible with the supplied ImGui core; no SDK substitutes are used.
- The expanded local `.verification/stage5_check.cpp` fixture extracts the unchanged real main.cpp panel statements and original configuration declarations, loads original embedded fonts, and observes native ImGui item registration. All earlier checkbox/slider/range/navigation/appearance/drag/close/scroll checks pass at five viewports and both spacing modes; all 37 call sites and the entire main.cpp remain byte-identical to 457a6f5.
- Rapid real category targets at varied 30/60/120 Hz remain finite/bounded and preserve feature snapshots. Tests distinguish inactive slider artwork from immediate actual values, verify 120 hidden frames submit no menu geometry/callbacks/clock updates, and check reopen recovery.
- Focused tests cover frame-rate-independent interpolation, invalid/large timing, 2,000 rapid targets, cache pressure over 9,999 IDs, native floating-toggle hitbox/release/disabled input, stale/hidden-control recovery, every actual generated vertex in 500 atmosphere samples/five scales, and stable warmed effect allocations/vertex/index capacities over 1,000 frames. Observed maximum effect geometry is 2,425 vertices / 10,584 indices. This is a host bound/stability result, not a mobile FPS claim.
- Actual indexed UI triangles/atlas are CPU rasterized into 21 PNGs in `previews/stage5/`: all seven panels at 1920×872 and 640×360, plus seven Player samples at visible clock 2–8 seconds with fixed configuration. All major/small captures and later samples were visually inspected; corrected corner defects are absent in the final files. Native small-viewport vertical clipping is intentional scrolling; horizontal labels/items remain within their columns.
- Offline index.html embeds all 21 exact PNGs with panel/viewport selection, download link and one-second captured-sample playback. It displays actual images; it does not recreate the application UI. 23 embedded data URIs match their PNG bytes, all PNGs pass CRC/decode/dimension checks, viewer selection/play-pause works under Node DOM emulation, and the 24-entry ZIP passes integrity checks. Stage 2/3/4 image hashes remain unchanged. Metadata records source/image hashes and implementation commit.

### Stage 6 handoff and limits

The SDK is intentionally excluded and the Android NDK/device/GPU environment is unavailable. No native build, overlay/touch/keyboard runtime, device blending/AA/appearance or FPS was verified. Host previews use illustrative test values on a neutral backdrop; they omit the game, floating toggle and platform backend, and may differ from actual GPU output. One-second sample playback shows changing real renderer lights/points, not full-speed native interaction animation. Guest Reset remains bound to original ResetLogin but was not invoked. Session-only appearance preferences and original embedded font macro warnings remain unchanged.

Next stage, only after user instruction: **Stage 6 — Final Source Audit, Android Build Validation, and Visual Verification**. Restore the original SDK/compatible NDK, audit all bindings/source integration, build the real Android component, verify device inputs/overlay/GPU/performance and compare against cached references. Do not restart earlier stages or invent SDK replacements. Stage 5 stops at its focused checkpoint.


## Stage 5.5 design audit — Crimson Eclipse

Review of the actual Stage 5 Player, Style and Settings renders and cached reference frames identifies a hierarchy problem: broad identical red blooms tint the header and body evenly; uniformly dim particles provide little focal variation; repeated red rims/section strokes and a bright static underline compete with controls. The text-only brand has no signature, and the sparse panels expose the flat shared background. The existing window proportions, navigation and native controls are sound and will be retained.

Art direction: near-black glass with burgundy corner light, an off-center soft eclipse silhouette in lower negative space, a restrained graphite navigation shelf, a custom primitive-drawn K/eclipse mark and two-level wordmark. Use neutral inactive borders, pearl/rose selected text, a softer traveling indicator, shaded circular controls, slender graduated slider fills and fading dividers. Keep the compact grouped content; improve material/lighting hierarchy instead of adding fake options. Replace 48 identical movers with 40 points split into fixed stars, micro-embers and rare sparkles, plus occasional clipped edge glints. Add a genuine session-only reduced-motion preference that freezes ambient motion, removes glints/drifting particles, and makes menu transitions immediate.

Matched baseline: seven verified actual-code Stage 5 PNGs at 1920×872 and visible animation time 2 seconds are preserved under previews/stage5_5/before-*.png, with original renderer/source hashes and commit provenance. Reuse the same capture harness/configuration for the after images.


## Stage 5.5 — completed Crimson Eclipse implementation

The change is a material/hierarchy refinement of the same reference-shaped menu. Window measurements, primary/secondary routing, fonts/atlas, grouped feature statements and native item hitboxes are retained. No SDK/gameplay/build/input integration changed. Inactive borders now use graphite/neutral rose-gray; restrained pearl/rose text marks selection while crimson remains concentrated in checked controls, active track fills and atmospheric light. The previous broad red wash and three perimeter rings are replaced with localized illumination and one delicate inward rim.

### Identity, surfaces and motion

- `KennyIdentity.h` draws an original K stem/branches within a partial eclipse arc using bounded native primitives. A fitted KennyPvtHax wordmark and small CRIMSON ECLIPSE descriptor occupy the existing 220-scaled-pixel brand slot. The descriptor reuses the existing smaller atlas font; no font/texture resource is added. The existing invisible drag handle, close control and compact header layout remain.
- `KennyPaint.h` provides a 32-direction cached shaded disc (33 vertices / 96 indices) and two-part fading seam. The atlas white pixel and normal ImGui buffers are reused. Reserve-before-indexing respects renderer vertex offsets; there are no per-frame heap containers, real-time blur or new resources.
- The existing 24×24 rounded mesh now renders near-black burgundy material, a graphite header shelf, quieter secondary band, slowly drifting crown light, off-center shadowed corona in lower negative space, and a faint opposing light. Lighting centers/intensity are calculated once per visible draw, not for each of 625 mesh vertices. Different slow frequencies produce gentle coordinated variation. The transparent child no longer interrupts the light field with a rectangular wash/footer strip.
- The curated budget is **40 points**, down from 48: 24 stationary faint stars, 12 slowly drifting micro-embers, 4 rare smooth sparkling points. Every halo and antialias fringe is checked against the rounded shell. A short fading glint travels along the straight top edge during a two-second window in a 17-second cycle. No point/physics collections or new textures are created.
- The visible-only double clock no longer globally resets at 4,096 seconds; analytic periodic motions use double arithmetic to avoid a visible reset jump. Same-frame advancement is idempotent, hidden frames do no work/catch-up, and reopening retains the existing restrained atmosphere reveal. Draw uses actual ImGui window dimensions for precise rounded containment.
- Primary emphasis and secondary pills ease with rate 15 (about 200 ms to 95%); the thin fading selected seam preserves bounded original position interpolation. Hover surfaces remain dark. Shaded circular checkboxes keep their native geometry and crisp white tick with faint depth; rate 22 is about 136 ms to 95%. Thin crimson slider fills graduate toward the handle; handles receive a soft material highlight. Numeric values and active edits update immediately. Externally changed inactive slider artwork may ease independently.
- Section separators fade into graphite and short rose emphasis rather than enclosing every control in a red border. Compact column layout/vertical rhythm are retained; localized lower lighting gives sparse panels depth without fabricated settings or large decorative objects.

### Genuine reduced-motion preference

Style now has Surface / Layout / Motion groups, responsively wrapping at smaller widths. The native Full / Reduced choice is session-only presentation state, default **Full**, alongside the unchanged 97% opacity / Standard spacing defaults. Reduced freezes lighting time at the current frame, draws only 24 stationary stars, omits drifting/sparkling points and edge glints, and snaps menu transitions immediately. A scoped reduction guard restores outside-menu animation state, including nested scopes. Switching back resumes visible time without catch-up. Reset appearance restores all three defaults while leaving every original feature value unchanged. No configuration keys or storage interfaces were added or changed. At 640×360 the wrapped Motion group is reached by existing content scrolling.

### Verification and actual-render evidence

- Strict C++17 production-header syntax and focused effect tests pass with `-Wall -Wextra -Werror`; real unchanged ImGui core is used. Focused tests exercise native floating-toggle hitbox/release/disabled behavior, time handling/frame-rate agreement, fixed cache pressure, 2,000 rapid targets, hidden/reduced/idempotent advancement, nested scopes, long-running continuity, 1,000 full/reduced rounded geometry samples at five scales and 1,000 warmed effect frames with stable capacities/active allocation counts.
- Maximum observed atmosphere geometry is **1,961 vertices / 8,928 indices**, reduced from Stage 5's 2,425 / 10,584. Visual cache remains 192 entries / 3,072 bytes. These are host bounds/stability measurements, not Android FPS claims.
- Rebuilt and executed `.verification/stage5_5_check.cpp` with real production headers, exact extracted main.cpp statements/original SDK-independent declarations, bundled fonts/core and native ImGui item hooks. All original native checkbox/slider/range/keyboard/numeric-entry checks, five primary categories, remembered secondary tabs, real appearance actions, scrolling, dragging, close/reopen, feature isolation, balanced stacks and five viewport checks pass. All 30 original checkbox sites are toggled/restored through their labels at 640×360; all 37 exact original binding/range/format call sites and the entire main.cpp remain byte-identical to 4eaedda.
- Actual seven-panel menu allocations and draw-buffer capacities remain stable over 1,000 route-switching frames after warmup. This extends the focused atmosphere-only allocation check.
- Added native Full/Reduced interaction at 1920 and after scrolling at 640, clock freeze/resume, immediate selected positions, reduction-scope restoration, reset/close/reopen preservation and unchanged original feature snapshots. Rapid actual category targets at 30/60/120 Hz and 120 hidden frames remain correct. Original configuration declarations, build files, branding and SDK integrations are unchanged. Guest Reset remains bound to ResetLogin but its destructive/platform callback is not invoked.
- Baseline headers were read into an ignored snapshot using `git show 4eaedda:path`; the working tree/HEAD was never switched or reverted. A fresh baseline harness/render reproduces **all seven Stage 5 PNGs byte-for-byte**. All seven candidate original-feature snapshots match baseline; both use 1920×872, visible time 2 s, 97% opacity / Standard spacing / Full atmosphere. Original Stage 2–5 PNG hashes remain unchanged.
- Visually inspected all seven large and seven small candidate panels, matched baseline, and full/reduced/later atmosphere samples against cached reference geometry and hierarchy. Fixed the first candidate's tiny descriptor and rectangular child wash before final capture. All seven before/after pixel draw bounds match; no new horizontal overlap or rounded cutoff found. Small-viewport lower controls remain scrollable, including Motion.
- `previews/stage5_5/` has **30 actual PNGs**: seven baseline, fourteen candidate panel/viewport, eight Full Player time samples (2–8/16 s), one Reduced sample (6 s). Each passes signature, chunk CRC, RGBA/dimension, integrity and full-decode checks. Time samples differ in real atmosphere pixels with feature values held fixed.
- Self-contained index.html embeds all 30 exact PNGs and provides seven matched before/after wipes, individual PNG downloads, two viewport choices, Full/Reduced samples and captured playback. All 34 embedded image/download URIs are byte-exact; selection, wipes at 0/50/100%, play/pause and hidden-tab stop pass Node DOM emulation. The 34-entry ZIP passes CRC checks. This is an image viewer, not a substitute UI. Actual Codex/browser rendering is not asserted; download/open the HTML locally if the Codex PNG viewer shows “No image”.

Provenance: production C++ menu/components and unchanged real feature statements/configuration, real ImGui core/embedded fonts, host test state, CPU rasterization of emitted indexed draw vertices and font atlas. No artificial/AI screenshot, replacement framework, fabricated SDK or game/device capture. Preview metadata records source/image hashes, matched state and commit. Lighting is represented by native translucent geometry, not real blur/refraction.

Reproduction while local ignored files remain: `python3 .verification/stage5_5_fixture.py`; compile `.verification/stage5_5_check.cpp` and `jni/imgui/{imgui,imgui_draw,imgui_widgets,imgui_tables}.cpp` with C++17, `-O0 -g -DIMGUI_ENABLE_TEST_ENGINE -I jni -I .verification`; run `timeout 60s .verification/stage5_5_check`; rasterize the final `.draw` files with `.verification/stage5_5_rasterize.py` and its matching atlas; run `.verification/stage5_5_package.py` and `node .verification/stage5_5_viewer_check.js`. The baseline uses `.verification/stage5_5_baseline_headers` first in include paths, `.verification/stage5_5_before_check.cpp`, and its separate atlas/rasterizer. Reproducible tracked effect-test commands remain in tests/README.md. Do not run old candidate harnesses against newer headers or overwrite retained old previews.

### Limits and handoff

SDK/NDK/device remain unavailable; no Android compilation/linking, overlay/touch/soft-keyboard runtime, GPU blending/AA or device performance was verified. CPU host captures omit game/platform/floating-toggle rendering; GPU output may differ. Captured playback is one actual PNG per second, not full-speed motion or a device FPS recording. Original embedded-font macro warnings remain untouched. Appearance preferences remain session-only. Checkpoints preserve selective tracked source boundaries; local generated outputs are ignored and no binary/dependency/secret/unrelated files are committed.

Stage 5.5 stops here. **Next: Stage 6 — Final Source Audit, Android Build Validation, and Visual Verification, only after user instruction.** Restore the user's original SDK and compatible NDK for the real native build; inspect actual device/GPU/input/performance and compare cached references before final acceptance. Never regenerate the SDK or restart previous stages.


## Stage 5.6 / Phase A — Living Crimson Aurora & Interactive Starfield

### Visual audit and art direction

Reviewed af8a337 production components, the actual Stage 5.5 Player capture and cached reference frame 24. The window, horizontal navigation, compact columns and control proportions already follow the reference; isolated crown/corona blooms and faint points make negative space appear static. Phase A replaces that background on **Visual → Player ESP only** with coherent flowing curtains and an interactive seeded sky. Existing branding, window proportions, spacing, control artwork and all other panel materials remain.

Three independently advected translucent curtain meshes use smooth multiscale hash noise rather than repeated sine strips or radial blooms. Unequal lower hems, skewed folds, fine vertical rays, graded upward falloff and broad left/right composition masks produce overlapping ruby/burgundy/scarlet depth. Graphite header/secondary shelves and quiet near-black gaps preserve hierarchy. After inspecting the first candidate, softened the initially prominent lower bright bands and increased vertical filament variation. Native atlas-white triangles provide all lighting; there is no texture generation, real blur or shader dependency.

### Interaction, timing and clipping

- The budget remains **40 stars**, with deterministic hash-seeded nonuniform positions, varied radii/brightness, slow continuous home drift, twinkling and four occasional shimmer points. There are no wraps, respawns or random per-frame seeds.
- Native background input is resolved after all widgets, using two reused draw-list channels to paint the selected route's atmosphere underneath them in the same frame. Aurora routing is determined after navigation, preventing a one-frame spill onto another panel. All six non-Player matched renders are pixel-identical to af8a337 through the same CPU rasterizer.
- Only a press begun on unoccupied Player **content** may initiate a background gesture. Native hovered/active widgets, disabled items, scrollbar/popup ownership, header/close/navigation and outside-origin gestures take priority. Leaving content bounds cancels the gesture until release. No input event, feature variable or overlay capture flag is written by the effect.
- Player content has native `NoMove`: an empty-content press focuses the existing child without automatically moving the entire menu. **Use the unchanged header to drag the window.** Other panels retain their original empty-space behavior. This deliberate content gesture distinction enables attraction without competing with dragging or adding an invisible input widget.
- Distance-weighted attraction, a surviving home spring, damped bounded velocity and smoothed visual pointer position create inertia without teleportation. Release keeps positions/velocities continuous and restores ambient spread. Local lighting response/distortion multiplies the existing curtain field; it is not a stand-alone radial aurora substitute.
- Physics uses a retained fixed-step accumulator at 120 Hz, maximum 12 substeps for a visible frame; finite delta is clamped to 0…100 ms. Visible double time is continuous, same-frame advancement is idempotent, inactive/hidden gaps do not catch up. Full/Reduced uses the existing preference: Reduced freezes the curtain/stars, disables attraction and clears local response; other panel motion behavior is unchanged.
- Every ribbon vertex projects into an inset convex rounded shell, so its triangles cannot escape rounded corners. Star/halo/AA containment is conservative, with all 40 stars remaining drawable in tested bounds. Rectangular scissoring supplements rounded geometry containment.

### Verification and artifacts

Strict production-header syntax and the focused effect test compile with C++17 / `-Wall -Wextra -Werror`. Existing effect regressions also pass unchanged. The new tracked SDK-independent extractor asserts all 37 original binding sites and uses the actual source panel statements/configuration. Native seven-panel tests cover all original checkboxes/ranges/conditional/shared bindings, numeric entry, callbacks' access, five categories, secondary memory, scrolling, appearance actions, header dragging, close/reopen, five viewport sizes and balanced stacks. Destructive/platform ResetLogin is intentionally never invoked by the host test.

Phase A native input tests pass first-press blank-content attraction and first-press checkbox priority without hover warmup; hold/drag/release dispersion; unchanged feature snapshots and window position during background touch; header dragging; outside-origin/exit cancellation; non-Player isolation and Reduced freeze/resume. Focused tests cover 20,000 variable-dt edge/drag steps, deterministic initialization, 30/60/120 Hz agreement, attraction/release/home recovery, malformed time, continuous long-session noise, 600 rounded geometry samples and 1,000 warmed native-allocation frames. The full real seven-panel suite also passes 1,000 warmed route-switching allocation/capacity frames.

Maximum observed new atmosphere geometry: **7,882 vertices / 41,628 indices** versus Stage 5.5's 1,961 / 8,928. New fixed state is **992 bytes**; three bounded 96×18 curtain meshes reuse native draw buffers and one fixed column array on the stack. The existing 192-entry visual cache is unchanged. These are host observations, not Android FPS/power measurements; profile the additional geometry on-device before expanding beyond Phase A.

`previews/stage5_6/` contains 15 PNGs: actual idle aurora at 0/2/3/6/10 s, idle stars, held center-background touch, dragged touch, initial/+2/+10 s release, Reduced, retained af8a337 baseline, exact-paste before/after comparison and eight-state high-resolution contact sheet. All native captures are 1920×872 with matched original feature state and session defaults. Captions are outside the captured UI. Inspected the timed/touch/release comparison, all required states, the 640×360 scrolling render and representative decoded animation frames; no new label/rounded-boundary artifact was found.

The approximately 12-second MP4 contains **145 consecutive actual renderer frames at 12 fps**, with 60 Hz host input / 120 Hz bounded physics: 0–4 s idle, 4–6 s held touch, 6–8 s dragged right, 8–12 s released. This is continuous output, not playback of unrelated static states; cadence is an export choice, not Android FPS. It fully decodes successfully. The self-contained HTML embeds all exact PNG/video bytes with individual downloads, and the 19-entry ZIP passes integrity checks. The original before draw-data/atlas is retained from af8a337; the faster C++ CPU rasterizer agrees with the earlier Python baseline within one 8-bit channel level. Every non-Player before/after render through the same new rasterizer is byte-identical.

Reproduction: `tests/README.md`; tracked extractor, native menu regression suite, focused physics/geometry checks, capture executable, CPU rasterizer and packager. Provenance JSON records current UI/core/font/draw-data/image/video hashes and baseline source hashes/feature state. Original Stage 5.5 captures and private GitHub exports remain unchanged. New Phase A exports have **not** been uploaded: the previous authorization covered only nine Stage 5.5 PNGs.

### Remaining limitations / stop point

The real main.cpp, configuration declarations, build files, native gameplay/SDK integrations and all 37 original bindings/ranges are unchanged from af8a337. SDK/NDK/device remain unavailable. Host mouse input exercises the existing ImGui path, but Android touch/overlay/backend, actual GPU blending/AA, native compilation/linking and device FPS/thermal/power require later testing. Appearance preferences remain session-only; no fabricated SDK headers, resources, gameplay features or permissions were introduced. Original embedded-font macro warnings remain untouched.

**Stop after Stage 5.6 Phase A. Next action: user inspects the PNGs/MP4 and directs any Phase A refinement or subsequent phase. Do not begin Phase B or Stage 6 automatically.**


## Stage 5.6 / Phase B — Custom theme system

### Scope and appearance

Continued directly from 58cbf6c without extracting, reverting or replacing the original architecture. The approved aurora composition/forces/damping/seeds remain. Style now contains three equal, rounded, native theme cards with restrained burgundy selection, small descriptive text, existing motion-cache feedback and a keyboard-focus outline. All three fit at 640×360; the content child scrolls independently of navigation. Existing opacity / Standard–Compact spacing / Full–Reduced controls retain their IDs and ranges. Settings' Reset appearance now restores the entire UI preference set, including default Aurora; Center window is unchanged.

Aurora is routed after native widgets on all seven screens, using the existing two draw channels, input ownership checks and rounded mesh. Its default intensity and activity are 100%; stars and touch attraction are enabled. Controls change curtain alpha (0–100), star visibility, background touch permission and ambient particle/twinkle clock speed (0–100). Zero activity holds star positions and twinkling while curtains continue; hidden stars skip star physics/drawing. A separate particle clock is the only integration change to default motion. At default settings, 1,800 steps produce exactly equal time/response/positions/velocities to the approved renderer; emitted draw vertices/UVs/colors/indices also match byte-for-byte. No curtain formula or physical coefficient was redesigned.

Only empty, hovered content accepts attraction. Native checkbox, slider, table, scrollbar, popup, disabled item, navigation and header ownership takes priority. The header remains the drag area in Aurora; non-atmospheric themes retain native empty-content dragging. No IO capture flags, game callbacks, configuration variables or overlay transparency controls were changed.

Classic paints only static graphite/burgundy rounded material separation. It does not call Aurora initialization/Advance/Draw or an artwork provider. Anime paints the same safe dark surface until supplied artwork is available, with an explicit missing-artwork explanation in Style. No anime drawing, voice, sound system, launcher, custom logo replacement or key-entry UI was fabricated or implemented. The existing identity is retained.

### Appearance persistence

The active source has **no feature configuration save/load system** to extend (Stage 1 audit unchanged). `KennyAppearanceStore.h` therefore owns a separate, versioned, UI-only file:

`<ANativeActivity.internalDataPath>/kennypvthax-appearance-v1.conf`

main.cpp passes the existing activity's private path; no package rename, external storage, SDK dependency or Android permission was added. Configuration is loaded once into the menu's presentation state. Preferences comprise selected theme, opacity, compact rows, reduced motion, aurora intensity, particle activity, star visibility, touch attraction, artwork dimming and artwork Cover/Contain. All default values remain compatible with the previous UI; there was no persisted appearance format to migrate.

Changed preferences save after native adjustment release, Reset, or menu hiding. Equal values perform no I/O; pending drags do not write every frame. A bounded text schema validates version, enum/booleans, field count, trailing data and finite numbers; numeric values are clamped. Writes stage a unique 0600 private file, flush/fsync/close, and atomically rename. A failed write is reported and does not retry every frame. Unavailable/read-error/corrupt storage falls back safely to session preferences with a visible status. No existing feature keys, files, defaults or bindings are read or written. ResetLogin's original destructive/platform behavior remains; the host never executes it.

The on-device path, lifecycle and I/O latency still require Android testing. Host tests exercise genuine filesystem writes and independent fresh Store instances reading the resulting file. No Android restart verification is claimed.

### User-asset integration contract

`KennyThemeBackground.h` accepts renderer-owned `ArtworkFrame { texture, width, height }` through:

- `state.artwork.SetStatic(frame)` for an already-uploaded still image.
- `state.artwork.SetProvider(callback, user)` for a future frame decoder/cache. Callback signature: `bool(void*, double visibleTime, bool motionAllowed, ArtworkFrame&)`.
- `state.artwork.Clear()` **before** the owner releases/replaces a texture or the graphics context is lost. Ownership remains with the asset module; this header creates/releases no GL textures.

Registration, callbacks, texture upload and Clear must occur on the render thread. Invalid/missing frames produce the dark fallback. Providers are called at most once per active Anime frame; they must return a cached frame without blocking. Other themes and hidden menus do not call them. Reduced resolves an initial frame then holds it; inactive gaps do not advance elapsed time. Context loss must invalidate the owner's handles and Clear before rendering resumes; actual GL lifecycle testing awaits user assets/device access.

The real draw path submits textured rounded mesh vertices to existing ImGui/GLES texture commands. Cover crops UVs; Contain letterboxes; dimming preserves foreground contrast (35–95%). These Style controls appear only when a valid user asset is registered. They are persisted even when the current asset is missing. No file loader/decoder or artwork is supplied yet, because the user will provide assets later. Tests use diagnostic texture handles only for native geometry/provider verification, never as screenshot artwork.

### Verification and previews

- Source extractor asserts all **37 exact original binding/range/format statements** and the **complete feature-panel/callback body** are unchanged from 58cbf6c. Helper/definition.h, build files and SDK/game integrations remain unchanged; main.cpp adds only private UI-store initialization/flush outside the callback.
- Real native menu suite retains checkbox/slider/keyboard/numeric-entry/range/conditional/shared-binding tests, five primary categories, secondary memory, original appearance actions, header dragging, close/reopen, scroll and five landscape viewport checks.
- Phase B adds 90 native theme-card switches, same-frame background routing, all seven Aurora routes, actual intensity endpoints/geometry reduction, frozen zero-activity stars, hidden-star physics pause, touch-disable ownership, provider inactivity/Reduced hold, and original checkbox access under all three themes at 640×360. Warmed allocation/capacity checks cycle all seven routes and all themes over 1,000 frames.
- Strict C++17 production header syntax, appearance/store/asset tests, existing effects and approved aurora regressions run without fabricated SDK files. Host storage tests cover all preference/theme round-trips, Reset, corrupt/version/nonfinite/trailing data, bounds, 0600 writes, unavailable/write-failure handling and no idle rewrites.
- Actual host captures use production C++ UI headers, exact extracted feature statements, original embedded fonts and bundled ImGui. The CPU rasterizer consumes actual draw triangles/atlas. **They are not Android captures or a separate UI simulation.** Anime previews intentionally contain no artwork.
- `previews/phase_b/` contains 13 individual captures (seven Aurora panels, scrolled Aurora preferences, Anime and Classic Player/Style, 640×360 Style), two labeled high-resolution contact sheets, source/state/image-hash provenance, a self-contained HTML viewer, README and 18-entry ZIP. Viewers and sheets retain the actual captures; only external sheet captions are added. All seven Aurora panels, three theme states, scrolled controls and small cards were inspected.
- SDK/NDK/device remain unavailable: full Android native build, app-private storage in the real process, touch mapping, asset GL lifecycle, GPU blend fidelity, FPS/power/thermal and save latency are unverified. Existing embedded-font macro warnings are unchanged. Effects remain bounded at 40 stars / three original curtains; full mobile performance must be profiled before release.

**Stop after Phase B. Next action: user reviews the three themes, supplies actual artwork when ready, and explicitly directs Phase C or later validation.**

## Phase C — Checkpoint C1 (10 October 2026)

C1 extends approved Phase B (`5fa7574`). It preserves the Aurora engine, all three themes, reference layout and the complete original feature callback. No C2 voice pack, recording, artwork, final logo, key input or authentication is implemented.

### Launcher and presentation lifecycle

`KennyLauncher.h` owns a small native ImGui window and its InvisibleButton. The existing K monogram is shared through `KennyIdentity::Emblem`; its header geometry is unchanged. The launcher is 48–80 pixels depending on viewport scale, initially at (20,20), clamped to the viewport. Classic has restrained graphite edging; Aurora/Anime have a muted burgundy treatment. It renders no aurora, starfield, texture allocation or background audio while closed.

Native release activates a tap. Movement beyond ImGui's drag threshold repositions the launcher, suppresses opening on release and retains its position in the current session. Native activation/focus and the exact visible square bound the hit area. Window dragging, original input hooks and viewport/overlay routing remain unchanged.

`State::Request` reports real open/close transitions and preserves menu routing/position. A bounded exponential alpha transition uses existing frame timing (~220 ms), with immediate Reduced-motion targets. Functional input is available immediately on opening. During closure the root AND content child have NoInputs, and native disabled scopes prevent activation. The hidden menu submits no panels/effects; only the launcher is drawn. Close produces its own single lifecycle event, rather than generic button feedback.

Future logo integration: on the render thread call `launcher.logo.Set({texture,width,height})` with an externally owned, uploaded transparent RGBA texture. Draw uses fit/contain with the original aspect ratio and full UVs. Invalid/missing geometry safely uses the existing K. Call `launcher.logo.Clear()` BEFORE releasing/replacing the texture or losing its GL context; the asset owner manages upload/deletion. No texture/file loader, final logo or owned GL resource is fabricated in C1.

### Audio events and profiles

`KennyAudio.h` provides these shared names:

- Used now: `menu_open`, `menu_close`, `checkbox_on`, `checkbox_off`, `button_click`, `primary_navigation`, `secondary_navigation`, `theme_changed`.
- Reserved and unused until real key integration: `key_focused`, `key_pasted`, `key_submitted`, `key_accepted`, `key_rejected`.

A scoped dispatcher surrounds real native menu widgets. Changed checkbox values, successful action buttons, changed choices/theme cards and actual navigation changes emit events; drawing, hovering, slider updates, physics and redundant selection do not. Menu lifecycle calls are outside that scope. No original callback is replaced or delayed; Guest Reset still uses its original platform callback and is never invoked in host tests.

Classic uses short crisp digital/mechanical PCM envelopes; Aurora uses softer, lower tones and gentle signature glides. Both are original lightweight synthesis, prepared once, without downloaded/copyrighted sounds or invented voices. Follow theme selects Classic for Classic and the optional soft UI effects for Aurora/Anime; explicit soft/crisp overrides are functional. Anime has no voice playback yet.

Settings adds UI sounds, master volume (0–100%, default 35%), and Follow theme / Aurora soft / Classic crisp profile. Native controls are disabled with an honest status if backend initialization is unavailable. The selector has a minimum 36-pixel hit height. Reset appearance includes default audio preferences. Existing shared appearance controls stay in Style.

### Backend, resource budgets and persistence

No pre-existing UI audio backend was present. `KennyAndroidAudio.h` uses Android OpenSL ES (API 21 compatible), linked through the platform `-lOpenSLES`; no external dependency/permission is added. It owns one engine/output mix/PCM player, a two-block 256-sample buffer queue at 48 kHz mono 16-bit little-endian, and the portable mixer. It does not change media volume, request audio focus or modify the background game's audio objects.

The bank is fixed at 2 profiles × 13 events × 9,600 int16 samples (~500 KB); actual clips last 28–150 ms. The mixer has four fixed voices and a 32-slot SPSC ring (31 pending commands). Saturation drops excess feedback safely. Rendering/submission performs no allocation, file I/O, synthesis or locks. Master gain is clamped/finite and smoothly applied; muting increments an epoch so pending/active sounds cannot return after unmute. Same-event throttling is 55 ms; ordinary event spacing is at least 22 ms, while distinct menu lifecycle events stay responsive. Backward/nonfinite event time is handled.

Initialization is attempted once, safely reports OpenSL failure, and does not repeat expensive work each frame or tap. The player stops after ~125 ms of silence; Pump reuses existing buffers/objects for queued input. Shutdown stops and destroys the player before mix/engine and bank lifetime ends. These platform calls and their callback lifecycle still require Android build/device validation; host tests do NOT prove OpenSL playback or latency.

The existing app-private file remains `<ANativeActivity.internalDataPath>/kennypvthax-appearance-v1.conf`. Schema 2 appends `uiSounds`, `uiVolume`, `soundProfile` while reading the real schema 1 unchanged and defaulting only new fields. Original ten appearance preferences and feature settings are retained. Bounded parsing, normalization, unique atomic 0600 saves, deferred drag writes, no idle rewrites and visible failure/session fallback continue. No configuration secret or feature persistence is added.

C1 has no runtime audio-asset directory or file decoder: the supported playable format is generated PCM. Host review WAVs contain the actual mixer's 48 kHz / 16-bit / mono samples. Event-to-file mappings, installed pack directories, file-format decoding, random variations and voice controls remain C2; no nonfunctional pack selector is exposed.

### Verification and evidence

- Exact 37 binding/range/format sites and full original callback preserved; input/gameplay/native code outside the UI block byte-identical to Phase B. Approved Aurora/default physics and draw geometry remain exact versus 58cbf6c.
- Existing real seven-panel suite passes navigation, all original controls, numeric/keyboard/drag behavior, themes, small-viewports, scrolling, header dragging, actions, allocation/capacity checks. Strict portable production headers and focused audio/store/aurora/effects builds pass.
- `kenny_audio_check.cpp` exercises actual deterministic PCM bank/mixer, four voices/31 commands, malformed input, volume/mute epochs, profile resolution, throttling, scoped events, absent host backend, 20,000 allocation-free dispatch/render iterations and 50,000 concurrent producer submissions.
- `kenny_c1_check.cpp` uses actual production launcher/menu/native input and the real portable mixer: outside/drag/tap, five viewports, route/position retention, fade/Reduced, closing input isolation, actual widget/navigation/theme events, native selector/volume/mute, slider/background/passive silence, invalid/Clear logo references and 120 repeated cycles. ImGui retires stale popup/table buffers (105 → 98 active allocations), then remains at 98; no growing allocations. Original feature snapshot is restored unchanged.
- Store tests exercise all audio fields, real v1 migration, schema 2 restart, corrupt/nonfinite/profile/boolean/trailing rejection and all retained filesystem behaviors.
- `previews/phase_c1/` contains 10 valid PNGs (native 1920×872 captures, 640×360 settings, enlarged native launcher crops), two genuine mixer WAVs, self-contained offline image/audio viewer, source/hash provenance and a 15-entry ZIP. The explicitly labeled PCM-test settings screenshot exercises the actual portable mixer, not an Android player; ordinary host screenshots correctly show the unavailable backend. No fake renderer, artwork, voices or Android capture.
- Android native compilation/linking, OpenSL device output/latency/cleanup, overlay touch, real private-path restart, GL texture lifecycle and Android FPS remain unverified because SDK/NDK/device are unavailable. Original embedded-font macro warnings are pre-existing and unchanged.

STOP at C1. After explicit C1 approval, implement C2 voice-pack infrastructure; do not start it or Stage 6 automatically.


## Classic — Electric Starfield experiment (14 October 2026)

The attached screen recording shows thin braided, branching connections with
brief traveling energy and bright white pinpoints. The old Classic surface was
quiet and flat. The upgrade uses a coherent perimeter network and lower-space
connections, not a dashboard or playback of the reference. Near-black/crimson
surfaces retain hierarchy; violet is unnecessary. Tapered red/white cores,
companion strands and local traveling highlights create depth without a
full-screen lightning storm. Stars remain sparse, deterministic and bounded.

Actual native captures initially exposed overly faint cores and a clipped
visible combo label. The final presentation adds a few coherent braids and
clearer junctions, and puts Star Density above a full-width hidden-label selector.
The existing audio Settings remain in their original location, with the new
Classic controls below them. Background geometry stays behind native controls
and within rounded bounds. No layout or control redesign accompanies this work.

Local/global Reduced motion holds the current scene and removes pulses. Classic
simulation is isolated from the unchanged approved Aurora and Anime routes.
Matched baseline/new Aurora and Anime pixels are checked by the preview package.
See CLASSIC_ELECTRIC_STARFIELD.md and final build verification for actual tests,
measurements, assets and runtime limitations. The working binary/startup/blank
bypass correction and private audio recovery remain intact. No production publish.
