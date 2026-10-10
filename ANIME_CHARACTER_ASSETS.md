# Anime character integration — Phase C2

Initial pack: **Rias Gremory**, **High School DxD**, ID `highschool_dxd_rias`.
Parent checkpoint: `c5e9ef0`. This is a private, offline integration. No media or
source has been published or pushed.

## Actual asset status

**No permitted Rias artwork, launcher image or voice recording was acquired.**
The character is selectable, but is not installed. The application shows that
status, retains the K launcher and C1 UI tones, and disables unavailable asset
controls. The previews show these actual states. No unrelated artwork, generated
character image, episode dialogue, cloned voice or diagnostic test media is
presented as Rias.

Search candidates, source URLs, available usage statements and rejection reasons
are recorded in [ASSET_SOURCES.md](assets/anime/highschool_dxd_rias/ASSET_SOURCES.md).
The sources examined did not establish permission for the requested PNG/voice
integration. Private use is not treated as permission. Supply artwork and
recordings with creator/source/license information that permits the intended
use. Retain that information in the manifest's `sources` and asset notes.

## Pack layout and installation

```text
assets/anime/
  index.json
  highschool_dxd_rias/
    manifest.json
    ASSET_SOURCES.md
    character.png           # missing
    launcher.png            # missing
    voice/
      launcher_open.wav     # all eleven mapped recordings are missing
      ...
```

The checked-in schema-1 manifest contains the real registry definition and
expected filenames. Its existence alone does not mark media installed. Status
is derived from successful bounded decodes, not manifest claims. Artwork,
launcher and voices can be installed independently; partial packs use fallbacks.
Only packs with at least one successfully decoded clip appear in the voice-pack
selector. Texture status is reported separately from successful CPU decoding.

Android reads `<activity.internalDataPath>/assets/anime/<character-id>/`.
Optionally package the workspace `assets/anime/` tree as APK assets under
`anime/`. `KennyCharacterGL.h::StageAPK` reads `anime/index.json` through the
existing activity AssetManager once, and stages only validated local manifests,
PNG and WAV paths into app-private directories (0700; new files 0600). Existing
files are preserved. There is no complete APK project in this upload; configure
that packaging in the original app project. Staging is Android-only and remains
uncompiled/unverified here. Failed writes are removed when detected; abrupt
process termination can leave an invalid file, which the loader rejects. Replace
invalid private files deliberately before retrying. No runtime network access,
external-storage permissions or SDK replacement is involved.

The registry loads once at initialization. Restart after installing/replacing
media; live reload is intentionally unavailable so cached recordings cannot be
freed while the C1 callback uses them. Theme/character/voice preference changes
apply immediately to already loaded packs.

## Supported formats and bounds

- Artwork/launcher: **noninterlaced, 8-bit RGBA PNG**. CRC, chunk structure,
  exact zlib stream, row filters and dimensions are checked. Original straight
  alpha is preserved byte for byte; no matte is added. Images must contain
  visible pixels and actual transparency. Fully opaque/empty images are rejected.
- Each PNG: at most 8 MiB encoded, 4096 pixels per side and 2,097,152 pixels total
  (8 MiB decoded RGBA). Export palette/RGB/interlaced PNGs to RGBA before use.
  **WebP is not supported** by this native source's available codecs.
- Voice: **RIFF/WAV PCM16**, mono or stereo, 8–48 kHz, 10 ms–4 seconds, at most
  1 MiB encoded. Validated clips are downmixed/resampled once to mono 48 kHz for
  the existing C1 mixer. MP3/OGG/compressed WAV are unsupported and safely ignored.
- At most eight characters, four decoded packs per character and three variants
  per event. Total retained decoded artwork/PCM is limited to 32 MiB; optional
  APK staging also has a 32 MiB source-media budget. Decode scratch memory is
  temporary and independently bounded. Over-budget assets use fallbacks.
- Local paths are bounded lowercase relative paths, at most four components;
  absolute paths, dot-prefixed components, traversal, symlinks, nonregular files,
  percent encodings and malformed formats are rejected. Manifest files are
  limited to 32 KiB and JSON depth 12. APK prefixes consume path components too;
  the supplied `voice/event.wav` layout fits both loaders.

## Rendering and launcher ownership

`KennyCharacters::Registry` owns cached CPU images and texture references.
`KennyCharacterGL.h` provides real GLES3 upload/delete callbacks, preserving
texture binding/unpack alignment. Upload is attempted once per asset/context,
not every frame. The existing ImGui backend already uses straight-alpha blending.
This branch requires Android/GPU verification.

Character artwork uses full-image aspect-fit in the right content region, behind
controls, with the existing dim preference. Insets/clipping keep it inside the
rounded menu without cropping the face/hair or adding a background rectangle.
The C1 launcher receives the selected character texture only in Anime mode when
the user preference and valid texture permit it. Otherwise it uses K. Its drag,
touch boundaries, transitions and open/close event path are unchanged.

Clear `launcher.logo` before clearing/deleting registry textures. Call
`ClearTextures()` with a live owning GL context for deletion, or
`ClearTextures(true)` after context loss to discard obsolete handles without
deleting names in a new context. The native integration detects EGL context
changes. It does not change the original activity lifecycle; teardown/device
resource behavior remains unverified.

## Voice events and C1 integration

| Character event | Existing trigger / status |
| --- | --- |
| `launcher_open` | Successful C1 menu-open event |
| `launcher_close` | Successful C1 menu-close event |
| `menu_navigation` | Changed primary or secondary navigation |
| `feature_enabled` | Successful checkbox enable |
| `feature_disabled` | Successful checkbox disable |
| `bullet_track_enabled` | Existing Enable bullet track checkbox enable |
| `confirmation` | Successful C1 button/choice action |
| `login_success` | Reserved KeyAccepted event, currently unused |
| `login_failure` | Reserved KeyRejected event, currently unused |
| `skins_enabled` | Explicit integration hook only; no new trigger |
| `error` | Explicit integration hook only; no new trigger |

The manifest references `voice/<event>.wav` for every row. No listed recording
exists yet. Variants are arrays of up to three approved local filenames.
`Registry::Emit` supplies explicit hooks for future existing actions without
fabricating login, skins, errors or validation behavior.

The C1 OpenSL ES player and bounded SPSC queue remain the only playback backend.
Its four original effect voices are retained; one exclusive character channel
prevents overlapping voice clips. Cached immutable PCM is referenced without
I/O, allocation, decoding or player creation on taps/callbacks. The registry must
outlive the player. Voice cooldown is the larger of 700 ms or clip duration plus
120 ms; mapped events during cooldown are suppressed. Seeded variation avoids
consecutive repetition when multiple clips exist. Missing mappings fall back to
C1 tones. Passive frames, sliders and Aurora interaction remain silent.

Global UI mute/zero volume takes precedence. Character gain is independently
controlled and multiplied by UI master gain. Turning voices off, switching
away from Anime or changing character/pack invalidates active/queued character
playback through the existing mixer/epoch mechanism. Original UI effect voices
remain available. No host test is represented as Android playback.

## Settings and compatible persistence

Anime-only controls extend the existing Settings page: character selection,
series/load status, artwork status, optional character launcher, installed pack
selection, voice enable/volume and missing-file/backend feedback. Unavailable
media/playback controls are disabled. Selectors retain minimum 36-pixel touch
height and scrolling. The Style dim control appears when artwork can render.

Appearance schema **3**, at the same existing private filename, appends selected
character ID, pack ID, artwork reference, voice enabled/volume and launcher
preference. Schemas 1 and 2 preserve all prior theme/layout/audio values and
default the new fields. Invalid C2 tails preserve valid earlier fields. Unknown
characters/packs fall back safely; values are normalized. Existing atomic 0600
saves and deferred edits remain. Feature configuration storage is untouched.

## Adding a future character

1. Obtain permitted artwork/optional launcher/recordings; document permission.
2. Add a local directory with a lowercase token ID and schema-1 manifest using
   the existing Rias manifest as a format example. Set name/series, relative PNG
   references and voice-pack arrays with event-to-WAV mappings.
3. Add the ID to `assets/anime/index.json` for optional APK staging, or install
   the pack under the private character root. The registry also scans that root.
4. Restart and inspect decoded/texture/audio status before declaring installed.

No per-character changes to UI/control code are needed. Only Rias is an initial
production character; a generic test registry entry is diagnostic, not another
anime pack. Media are Git-ignored and private. Do not upload asset-bearing
previews or recordings to any preview repository without explicit authorization.

## Host evidence and limits

Passed strict portable C++ checks; exact 37 binding/range/body extraction;
existing menu/theme/Aurora/effect/C1 launcher/audio regressions; C2 byte-exact PNG
alpha and corruption/truncation/opaque rejection; safe path/symlink/FIFO tests;
WAV format/downmix/resample; registry extension; cached texture lifecycle
interface; voice routing/variation/cooldown/mute/volume; 500 switches; 10,000
allocation-free cached dispatch/mix iterations; genuine private-store migration
and restart; aspect-fit UV/geometry; native missing-asset selector interaction.
Diagnostic test images/tones exist only under ignored `.verification/` and never
serve as Rias media or screenshot artwork.

`previews/phase_c2/` contains eight actual production C++/ImGui host screenshots,
two genuine C1 baseline screenshots, a contact sheet, comparison, offline viewer,
hash provenance and ZIP. Classic comparison is pixel-identical; Aurora differs
by one 8-bit channel level at one header pixel. Previews were inspected, including
640×360 scrolling and the K fallback. They are CPU-rasterized native draw data,
not a standalone mockup, generated artwork or Android captures.

The intentionally omitted SDK and unavailable NDK/device block Android native
compilation/linking, APK staging, activity-private restart, OpenSL ES playback,
GLES alpha/texture lifetime, real touch and device performance testing. No Android
audio/GPU/FPS claim is made. Actual Rias transparency/voice playback must also be
verified after permitted media are installed. Stop after C2.
