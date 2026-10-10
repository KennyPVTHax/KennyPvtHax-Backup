# C3 — acquisition, permissions and validation

Reviewed 10 October 2026, parent `6f300ae`. No source or third-party media has
been published or uploaded to GitHub. All 24 tracked `jni/` files are byte-identical
to C2. This checkpoint installs data using the existing registry, C1 mixer,
Settings and private appearance store; it does not redesign any UI or engine.

## Actual result

- Five real **Cici Fyre — English alternative** clips installed in the existing
  `highschool_dxd_rias` character directory. They are CC0 and explicitly **not
  Rias Gremory / Yoko Hikasa recordings**.
- Seven existing event mappings use those five clips. No login, skins or error
  trigger is invented. Four of eleven character event slots remain unmapped.
- Rias character artwork, launcher artwork and original voice pack remain
  uninstalled. The character reports partial status and retains the K launcher.
- All six user-uploaded OGGs are valid, unchanged originals. They remain outside
  the runtime pack, without guessed transcripts or event mappings.

Machine-readable provenance, source hashes, durations, conversions and status:
`assets/anime/highschool_dxd_rias/ASSET_VALIDATION.json`. Installation mappings:
`assets/anime/highschool_dxd_rias/manifest.json`.

## Artwork candidates and permission review

| Candidate | Advertised size / width:height | Permission and disposition |
| --- | --- | --- |
| [Hiclipart yzkdp](https://www.hiclipart.com/free-transparent-background-png-clipart-yzkdp) | 640 × 800 / 0.800 | Host lists noncommercial use; creator and underlying permission unverified. Not downloaded or installed. |
| [PNGWing pzcwe](https://www.pngwing.com/en/free-png-pzcwe) | 576 × 778 / 0.740 | Host lists noncommercial use; creator and underlying permission unverified. Not downloaded or installed. |
| [PNGWing nvfcl](https://www.pngwing.com/en/free-png-nvfcl) | 3920 × 6000 / 0.653 | Same permission limitation; advertised dimensions also exceed the current decoder's side/pixel limits. Not downloaded or installed. |

These sizes are **page metadata, not verified original image dimensions**.
[Hiclipart terms](https://www.hiclipart.com/terms-of-use) and
[PNGWing terms](https://www.pngwing.com/terms-of-use) describe community uploads
and do not establish the requested underlying rights-holder authorization.
No creator attribution was verified. Source restrictions were not bypassed.

No actual PNG bytes were acquired, so alpha, matte artifacts, sharpness and
character crop quality could not be compared. The inline white-background
reference is visual guidance only; its original file/alpha data is unavailable.
**No character or launcher image was selected.** An authorized RGBA original
is still needed. Existing loader limits: 4096 pixels per side, 2,097,152 pixels
total, noninterlaced 8-bit RGBA PNG with actual transparency. A permitted resized
derivative of the largest candidate would be necessary; none was made.

## Original Rias voice archive and user recordings

Candidate: [Sounds Resource — Rias Gremory](https://sounds.spriters-resource.com/mobile/senrankaguranewlink/asset/501255/),
from *Senran Kagura: New Link*, uploader Gacha Grabber; page performer attribution
Yoko Hikasa. Those page claims do not authenticate the six uploaded files.

The site's [terms](https://sounds.spriters-resource.com/page/tou/) describe
unpublished, noncommercial uses, but its [help](https://sounds.spriters-resource.com/page/help/)
states it does not own or license original resources. Rights-holder authorization
to embed these recordings remains unverified. The archive was not downloaded.
Permission and verified spoken content have been requested for user review;
no response is assumed. No protected dialogue extraction or access bypass occurred.

All six uploads are Ogg Vorbis, mono, 44.1 kHz. FFprobe inspected each stream;
FFmpeg fully decoded each with errors treated as failures. SHA-256 and byte counts
are in the validation JSON. Originals were neither converted nor truncated.

| Uploaded file | Duration | Runtime disposition |
| --- | --- | --- |
| `VOICE_ADV_PL125_16_001.ogg` | 2.032449 s | Unmapped, permission/transcript unresolved |
| `VOICE_ADV_PL125_01_001.ogg` | 0.616281 s | Unmapped, permission/transcript unresolved |
| `VOICE_SYS_PL125_11_03_002.ogg` | 3.436327 s | Unmapped, permission/transcript unresolved |
| `VOICE_ADV_PL125_03_001.ogg` | 0.589773 s | Unmapped, permission/transcript unresolved |
| `VOICE_SYS_PL125_02_02_002.ogg` | 8.162948 s | Additionally exceeds the existing four-second voice limit; not shortened |
| `VOICE_ADV_PL125_02_002.ogg` | 1.324807 s | Unmapped, permission/transcript unresolved |

The C2 runtime accepts bounded PCM16 WAV, not OGG. No Japanese transcript or
authenticity assertion was derived from filenames. Direct audio listening is
unavailable in this session; no human listening is claimed. The uploaded files
remain privately under `/workspace/attachments/`, outside the application assets.

## Licensed English alternative

Creator/source: [Cici Fyre — Free Voice Clips Pack, Mature Female](https://cicifyre.itch.io/free-voice-clips-pack-mature-female).
The creator explicitly supplies these recordings under
[CC0 1.0](https://creativecommons.org/publicdomain/zero/1.0/), permitting
commercial/noncommercial use; attribution is optional. Credit is nevertheless
recorded: **Voice clips by Cici Fyre**. These are English interface recordings,
not authentic Rias dialogue or a cloned character/actor voice.

Retrieved through the creator's normal free-download workflow. No login,
payment, CAPTCHA or download-restriction bypass was used. Original archive:
10,895,641 bytes; SHA-256:
`95a49656814102ec0abb1a69cd6d50c4756983053ef3a24d759e23a65627bd4b`.
ZIP CRC and bounded safe extraction passed. All **57 original WAVs** fully decode
and remain byte-identical to archive entries in private `.verification/c3-review/`.

Content was corroborated using the existing FFmpeg PocketSphinx filter and an
official temporary CMUSphinx English model: unconstrained full-language-model
recognition, without a prompt/grammar forcing expected words. Creator labels and
recognition agree on the five installed clips below. Recognition is machine
evidence, **not human audition**. `goodbye.wav` produced “good good” and
`alright.wav` produced “oh really”; both were excluded. `thanks_normal.wav` was
recognized as “thanks” but not needed. No model/package was added to the app.

| Installed file / recognized content | Duration | Existing events |
| --- | --- | --- |
| `cici_hello.wav` / “hello” | 0.923688 s | `launcher_open` |
| `cici_see_you_later.wav` / “see you later” | 1.321375 s | `launcher_close` |
| `cici_okay_normal.wav` / “okay” | 0.936521 s | `menu_navigation`, `feature_disabled` |
| `cici_okay_happy.wav` / “okay” | 1.103292 s | `feature_enabled`, `bullet_track_enabled` |
| `cici_no_problem.wav` / “no problem” | 1.039146 s | `confirmation` |

Original recordings are PCM32 float, stereo, 48 kHz. Runtime derivatives are
full-length PCM16 mono, 48 kHz for the unchanged C2 decoder/C1 mixer. Arithmetic
stereo downmix plus triangular dithering was used; no normalization, trimming,
speed, pitch or sample-rate change. Original and derivative frame counts agree;
per-sample error versus the arithmetic downmix is below two PCM16 quantization
units (measured maxima 1.445–1.488). Originals are retained, and the conversion
is disclosed rather than called lossless.

Runtime directory: `assets/anime/highschool_dxd_rias/voice/`.
Pack ID: `cici_fyre_mature_female`; selector name:
`Cici Fyre - English alternative`. The original `default` Rias manifest mappings
remain intact and unavailable until real files load. The registry chooses the
available alternative through its existing fallback; current appearance state
persists the selected pack/voice preference with existing schema 3. No settings
file or original feature state is overwritten.

## Private installation and handoff

All media, original ZIP, ASR models and previews are ignored by Git; the focused
checkpoint records only manifests/provenance, test code and documentation.
**A Git checkout alone will not contain the five recordings.** Preserve this
workspace's `assets/anime/highschool_dxd_rias/voice/` directory when transferring
the app. Package the assets using the existing documented C2 APK/private layout
in [ANIME_CHARACTER_ASSETS.md](ANIME_CHARACTER_ASSETS.md). Restart after media
installation because the current registry caches once; preference switching is
immediate for loaded packs. No runtime network fetching was added.

Original material is under `.verification/c3-review/cici-original/`, with the
original ZIP alongside it. Hashes and original-to-derived relative names are
recorded in `ASSET_VALIDATION.json`. Reproduction checks require those private
files plus the six uploads; see [tests/README.md](tests/README.md).
No asset-bearing image or recording has been sent to a preview repository.

## Executed host verification

- Exact 37 original binding/range/format statements and whole original panel
  callback preserved; all tracked application `jni/` files unchanged versus C2.
- Strict C++17/-Wall/-Wextra/-Werror C3 pack/mixer checks; five actual PCM clips,
  seven mappings, missing original pack/event, exclusive voice/cooldown, mute,
  independent volume, 100 theme cancellations and fresh-store pack persistence.
- Existing C2 loader/registry tests: diagnostic byte-exact alpha, malformed
  image/audio/path rejection, cache bounds, texture ownership, voice routing,
  500 switches, schema migration and 10,000 allocation-free cached iterations.
  Missing-pack tests now use an isolated empty root; diagnostic manifests exclude
  optional real packs. Assertions retain their original strictness.
- Existing native menu, C1 launcher/audio, appearance, Aurora and effects suites:
  navigation, all original controls, drag/close/reopen, 640 scrolling, theme
  switching, untouched physics, clipping, persistence and warmed allocations.
- Native C3 UI: actual alternative selector, enable/volume/global mute, 36-pixel
  small selector, unchanged feature snapshots and truthful unavailable-backend
  states. A right-edge test click was corrected to land inside the hitbox;
  application slider code was unchanged.
- Six original OGGs, 57 original WAVs and five derivative WAVs fully decode;
  archive/original checksums, full frame counts and quantization checks pass.
- Eleven PNGs verify and fully decode; nine actual native captures plus contact
  sheet/comparison. Aurora and Classic are **pixel-identical to C2** at matched
  1920 × 872 state. Contact sheet, Settings, 640 scrolling and K fallback inspected.
  Small combo labels use existing clipping; complete pack name is visible at full
  width and in the opened selector. No layout engine modification was necessary.
- Actual C1 mixer produces a playable ten-second WAV with full selected clips.
  Offline viewer, SHA-256 provenance and 15-entry private ZIP validate.

Evidence: `previews/phase_c3/`, especially `anime-voice.png`,
`host-pcm-test-settings.png`, `contact-sheet.png`, `non-regression.png`,
`cici-c1-mixer-demo.wav`, `index.html` and `kennypvthax-c3-previews.zip`.
Screenshots use actual application C++/ImGui draw data CPU-rasterized on the host.
The separate PCM-test screenshot is explicitly labeled as a host test sink;
normal previews correctly report the absent Android playback backend.

## Remaining limitations / next step

Rias image alpha/quality, launcher image and original voice content/permission
remain unverified. Obtain rights-holder permission and original RGBA files;
provide verified transcripts before mapping uploaded recordings. The longest
clip requires a deliberate separate decision, not automatic truncation.

Intentionally missing SDK, unavailable NDK/device: Android compile/link, APK
staging, activity-private restart, GLES alpha/resource lifecycle, OpenSL ES
playback, real touch and device performance remain unverified. Host PCM playback
is not proof of Android output. No Android FPS or installed-original-Rias claim.
Stop after C3; do not begin key-entry or Stage 6 automatically.
