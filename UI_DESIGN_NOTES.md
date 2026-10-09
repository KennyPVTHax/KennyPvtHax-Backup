# KennyPvtHax — source map and reference design

Stage 1 inspection and Stage 2 implementation, 10 October 2026 (Asia/Calcutta). The original observations below remain the design specification. Completed Stage 2 changes and validation are recorded at the end; Stages 3–6 remain unimplemented.

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
4. **Stage 5:** add reusable application checkbox/slider/pill helpers with existing ImGui IDs, item registration, keyboard/mouse/touch behavior, and value updates. Draw bounded particles/glow through the menu's clipped draw list, with fixed storage and no new dependencies. Animations should be time-based and lightweight. Do not change global ESP/game colors when styling UI chrome.
5. **Stage 6:** compile using the real Android NDK and missing SDK once available, inspect the actual UI, and compare cached reference frames. Report static checks separately from device/build evidence.

## Baseline limitations

- No Android NDK / `ndk-build` is available in the current workspace. Host `g++`, Git, FFmpeg, and FFprobe are available.
- The supplied archive lacks the entire `jni/SDK/` directory, including `PUBGM_BangJO.hpp` required by `SDK.hpp` and six `.cpp` files explicitly listed in `Android.mk`. A complete native build cannot succeed from this upload alone.
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
