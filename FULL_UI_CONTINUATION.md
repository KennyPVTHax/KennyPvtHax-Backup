# Working full UI continuation

## Baseline and recovery boundary

Working source: `793458200ab8906179af0c63d0b0cb1648b7dafa` on main.
Owner confirms this full build runs on Android; Actions run 38407512326 succeeded.
The last commit emptied `jni/Helper/bypass.h`. That empty file is preserved.
This establishes the removed component; it does not independently establish a
symbolized crash root cause. This branch is `ui/full-theme-continuation`, not the
stripped-down recovery branch. The baseline commit remains the rollback point.

The native constructor, input callbacks, EGL/ImGui initialization, diagnostic
infrastructure, OpenSL engine, GL asset bridge, SDK, offsets and gameplay code
are unchanged. No removed component is restored. No loader publication occurs.

## Existing inventory

- Complete crimson menu, five primary categories, seven feature panels, circular
  checkboxes/sliders, compact grouping and all 37 original binding/range sites.
- Aurora default: approved procedural curtains, bounded seeded stars, touch
  attraction/release, reduced motion and pause while hidden.
- Classic: minimal crimson surfaces; Anime: local transparent character layer.
- Existing K launcher, drag/boundaries/open-close transitions and texture fallback.
- Existing app-private appearance storage, Settings and Style controls.
- Existing bounded local character registry (8 characters/4 packs/3 variations),
  PNG alpha decoding, aspect fit, texture callbacks and character launcher support.
- Existing C1 tone profiles/OpenSL engine and C2 recording mixer, global mute,
  independent character volume, single voice channel and duration-based cooldown.
- Rias definition is present. Actual installed audio: five CC0 Cici Fyre English
  alternative clips, seven mappings; these are not authentic Rias recordings.
  Real Rias artwork and launcher PNG remain absent. No new artwork/voices acquired.
  Unverified uploaded OGGs remain excluded and unmapped.

## Incremental presentation changes

The existing Anime Settings section now offers Show character artwork and Control
voice feedback. Visibility affects only character cutout draw submission; launcher
selection remains independent. Turning off control voices retains normal C1 tones,
menu greetings and navigation. Global mute/character mute still take precedence.

Private appearance schema 4 adds two boolean preferences, retaining the same
app-private filename, defaults and migration from schemas 1–3. Malformed new tails
retain valid earlier settings. Saves still occur only after completed adjustments.

Optional manifest event names `theme_switch` and `settings_navigation` are appended
without renumbering existing events. Theme-change dispatch uses a real successful
existing theme interaction. Settings navigation carries a presentation-only label;
when no specific clip is installed it uses the existing menu_navigation mapping.
A missing theme_switch mapping falls back to existing C1 tones. Existing approved
media and mappings are byte-identical. Add permitted PCM WAV clips to those keys
in an existing character voice pack when available. The registry remains generic;
future Akeno integration requires an authorized pack, not scattered UI changes.
Login success/failure remain unused integration points until real login exists.

## Device test

Install only the exact artifact for this branch through the working native host.
Keep the baseline library available for rollback. Verify startup/K launcher, then
all three themes, drag/open-close, five categories and small-screen scrolling.
In Anime Settings toggle visibility/control feedback, mute and volume; restart to
verify saved preferences. Missing images must leave the K fallback; absent voice
mappings must never block interaction. Confirm Aurora behavior remains unchanged.
Collect KennyPvtHax logcat checkpoints for any failure. Do not promote this branch
or update Anilxkenny/kenny.json before the owner confirms this device test.

Host CPU-rasterized ImGui captures and portable PCM tests are not Android GPU or
OpenSL playback verification. No new Android performance or runtime claim is made.

## Verified continuation artifact

Code/build commit: db93cc85f522f8595a9331194bfb81ffe3de6681.
Actions: https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38411971919
Result SUCCESS, full presentation, unchanged NDK 25.2.9519653.
Artifact 11823146526: KennyPvtHax-ARM64-SO. Actual ZIP CRC/two-entry contents,
ELF64 AArch64 and matching embedded build metadata verified after download.
Library SHA256: 4cd93f9c099f2881f6087fb8ef367e18f51195f3cc4549b27c0c61713c73fb04
ZIP SHA256: c707d54b3b84c32a77ecbce626d39150c0a22ad6fc9d8d878150a775f2e10929
BuildID: fc3f77558c7a52228ccf0d309bfec9f227bbe8de.

All ten existing host suites passed with AddressSanitizer/UndefinedBehaviorSanitizer:
menu, launcher, audio, theme, Aurora, effects, characters, media, diagnostics, fonts.
New continuation sanitizer test and actual C3 ImGui capture interactions passed.
Exact 37 binding/range/callback checks and protected runtime/media comparisons pass.
Existing menu tests cover native interactions, navigation, drag/close/reopen,
small viewport scrolling, warm allocation stability and repeated theme switches.
Existing character tests cover 10,000 allocation-free cached dispatch/mix cycles.
A new test initially advanced event time without draining the simulated audio
clock; corrected the test, without changing the working single-voice mixer.

Actual CPU-rasterized native ImGui PNGs and offline viewer are generated under
previews/full-continuation/. Anime Settings and Aurora captures visually inspected.
No synthetic artwork, Android GPU screenshot or authentic Rias voice claim.
The subsequent verification checkpoint changes only documentation, test timing
and generated-preview ignore rules; application sources match the built commit.
Next: owner tests this artifact on Android before any production promotion.
