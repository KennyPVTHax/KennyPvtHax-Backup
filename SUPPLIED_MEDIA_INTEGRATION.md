# Supplied Rias media integration

## Baseline / runtime boundary

Owner-confirmed working full baseline: 793458200ab8906179af0c63d0b0cb1648b7dafa.
This work continues the existing full UI at c0dec2689a303d4770ed01342bcaab9fc39eef0c
on ui/supplied-rias-media. It does not use the recovery-only branch.
Helper/bypass.h stays blank. main.cpp, constructor/loading/hooks/input/EGL/ImGui,
SDK, gameplay, audio engine, texture bridge, launcher architecture and Aurora are
unchanged. All 37 original bindings/ranges remain intact.

## Supplied files / exact mapping

| Original uploaded name | Runtime PCM file | Trigger |
|---|---|---|
| bullet.ogg | voice/user_bullet.wav | Enable bullet track OFF → ON |
| aim.ogg | voice/user_aim.wav | Enable aimbot OFF → ON |
| aimoff.ogg | voice/user_aimoff.wav | Enable aimbot ON → OFF |
| extrafeatures.ogg | voice/user_extrafeatures.wav | Open Extra features section; user explicitly confirmed |
| images (3).jpg (attachment stored as 5-images-3-.jpg) | character.png | Anime character cutout after authorized background removal |

bt.ogg and btoff.ogg were not supplied. bullet.ogg is the actual Bullet ON source;
there is no supplied Bullet OFF recording. No separate KennyPvtHax launcher logo
was supplied; retain the K emblem. The character image is not repurposed as a logo.
The original files are preserved unchanged in the private bundle's originals/.
The inventory records attachment filenames, SHA-256, sizes, codec/sample rate,
duration/channels, dimensions, alpha and intended event. See SUPPLIED_MEDIA_MANIFEST.json.

The named recordings are user-supplied for this private integration. Speaker
identity and a public redistribution license are not independently asserted.
No user recording/artwork is committed or uploaded to the public repository.
Only code, event/path metadata and reports are published. Anilxkenny is untouched.

## Conversion / transparency

The existing engine accepts local PCM WAV, not Vorbis. Offline ffmpeg conversion
uses mono 48kHz signed 16-bit WAV and preserves decoded sample timing, natural
pitch and duration (within one resampled sample of original container duration).
Decoded source peaks exceed 1.0 for all four files, so constant attenuation brings
peaks to 0.95; no normalization that amplifies, trimming, tempo change or runtime
decoder dependency is introduced. The exact measured gains are in the inventory.
Files remain within the existing four-second/1MiB bounds and 32MiB decoded cache.

The supplied JPEG is 1035×1280 RGB, with no alpha and a white background. The user
explicitly approved a pixel-preserving Python mask. The original RGB pixels are
unchanged; only alpha removes connected white background and manually inspected
white gaps between hair strands. Interior white clothing is retained. The output
is RGBA8 noninterlaced PNG with actual 0–255 alpha, same dimensions/aspect ratio.
JPEG edge softness remains inherent to the original; this is not enhanced artwork.
A redrawn image-editor candidate was rejected and is excluded from all deliverables.

Reproduce privately (ffmpeg/ffprobe and Pillow required on the host only):

```sh
python3 tools/remove_white_background.py YOUR_JPEG character.png \
  --seed 774,382 --seed 725,417 --seed 820,560 --seed 177,566 \
  --seed 855,646 --seed 636,692 --seed 279,781 --seed 477,818 --seed 436,709
python3 tools/prepare_supplied_rias.py --media-dir YOUR_ATTACHMENT_DIRECTORY \
  --output .verification/user-media --character character.png
```

The seeds apply only to this specific 1035×1280 image; do not reuse them blindly
on another picture. No substitute audio, logo or artwork is generated.

## Event routing / playback

New character events append aim_enabled, aim_disabled, bullet_track_disabled and
extra_features_navigation without changing old event IDs. Routing is centralized
in the existing character registry. Checkbox dispatch requires the native widget
reported a real edit AND oldState != newState. No events are produced by passive
frames or configuration loading. Extra features triggers only on successful
navigation into that section, including restoring its remembered subtab by a
primary Misc click; a repeated click on the already-selected section is silent.

The selected character and voice pack determine recordings. The supplied pack
contains exactly four mappings. Missing events fall back to existing C1 UI tones;
no supplied dialogue is borrowed for unrelated controls. The existing separately
named Cici Fyre alternative keeps its established generic mappings. New explicit
per-event cooldown timestamps are bounded; existing duration-based global speech
cooldown and the single recording channel prevent overlap. Very rapid toggles
update settings immediately but suppress overlapping speech rather than queueing
stale announcements. UI/character mute, voice volume, Control voice feedback and
leaving Anime retain precedence. No player/audio initialization or file reads occur
in control rendering or the real-time audio callback.

Existing Settings already contains character/pack selectors, voice enable/volume,
artwork visibility and character launcher preferences. Choose "Rias / supplied
event clips" after installing the pack. Saved valid pack selections are preserved,
so an existing Cici selection is not silently replaced. No test button or duplicate
settings window was needed. Transparent contain/clip, texture cleanup/recreation
and the K fallback all use existing approved systems.

## Install the private pack — required in addition to the native library

The .so does not embed these media. Native-only compilation cannot add APK assets.
The private bundle's assets/anime/index.json and assets/anime/highschool_dxd_rias/
can be placed in the original authorized Android host's APK assets, using the
existing StageAPK interface. Alternatively, install the same tree beneath the
native activity's actual internalDataPath:

    INTERNAL_DATA_PATH/assets/anime/highschool_dxd_rias/manifest.json
    INTERNAL_DATA_PATH/assets/anime/highschool_dxd_rias/character.png
    INTERNAL_DATA_PATH/assets/anime/highschool_dxd_rias/voice/user_*.wav

The bundle includes the unchanged approved Cici alternatives too. Do not install
originals/ or the source JPEG as runtime files. StageAPK intentionally preserves
existing app-private files; if an older manifest is present, back it up and update
only that character's manifest through the authorized host installer. Do not clear
app data or remove appearance preferences. Do not change the working native
loader. Registry loading is cached once, so restart after initial media installation.

For a debuggable host, adb run-as may provide authorized access. Confirm that its
relative files/ directory equals the activity's internalDataPath first; otherwise
adjust it. Example template (not device-tested here):

```sh
adb shell run-as YOUR_HOST_PACKAGE mkdir -p files/assets/anime/highschool_dxd_rias/voice
adb exec-out run-as YOUR_HOST_PACKAGE cat files/assets/anime/highschool_dxd_rias/manifest.json > previous-character-manifest.json
adb shell -T "run-as YOUR_HOST_PACKAGE sh -c 'cat > files/assets/anime/highschool_dxd_rias/manifest.json'" < assets/anime/highschool_dxd_rias/manifest.json
```

Stream character.png and the voice files similarly to their respective paths.
If run-as is denied on the non-debuggable host, use its authorized local asset
installer/APK packaging; this project supplies no Java/Kotlin host packaging.
Do not grant broad storage permissions or bypass Android access controls.

## Verification and next device test

Run `python3 tests/run_ui_regressions.py --sanitizers --user-media .verification/user-media`.
The supplied test uses genuine ImGui clicks and actual decoded supplied PCM to
verify exact clip pointers and once-only state transitions. Host upload callbacks
and CPU rasterization validate alpha/composition, not real Android GPU playback.
Full ARM64 builds use the unchanged NDK 25.2.9519653 and libAnoy.so module.
Detailed final results and artifact checksum are recorded in the verification file.

Install the exact matching library plus the private media pack, select Anime/Rias/
supplied event clips, and test Aim ON/OFF, Bullet ON/OFF, Extra navigation, idle
frames, mute/volume, restart persistence, artwork visibility, drag/open-close and
Classic/Aurora. Confirm no startup regression with KennyPvtHax logcat milestones.
Do not promote this experimental build or update kenny.json until device-tested.

## Final verification checkpoint

Compiled source: `2a54a41b6ee7de42bf91a34437e66a499e599323`. Full ARM64 run
https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38422703802 succeeded
with unchanged NDK `25.2.9519653`; artifact `11826799895`.
Actual downloaded ZIP: CRC/exact two entries, ELF64/AArch64, source/isolation/NDK
metadata, and matching runtime hash verified.
Library SHA-256: `e2fc6995a2741cd51f385c5b54a420eb168c0b6c51ffa1c0bbb9ab6787ca2b3f`.
ZIP SHA-256: `7ddeaef30f88ab5c18ac574879a34c7537faa6743c015d548c28811f9b59ed6b`.
Build ID: `e38cca0d9be6285cec43e7370e2faf3e4b61e784`.

All twelve host ASan/UBSan suites PASS: menu, launcher, audio, theme, Aurora,
effects, characters, media, diagnostics, fonts, continuation, supplied media.
Exact 37 binding/range checks PASS. Protected runtime paths and existing source
SDK/build configuration match the working full baseline. The supplied test
uses actual user WAV samples and real native control clicks, verifies all four
event mappings, rapid-toggle suppression, idle/unrelated/missing-event silence,
selected-character isolation and 50 theme changes. PNG loader alpha, cached upload,
visibility and K fallback PASS. Existing suites cover persistence, dragging,
close/reopen, scrolling, viewport fit, corruption, resource reuse and allocation
stability. No additional Android playback/GPU/runtime evidence is claimed.

Five actual texture-aware C++/ImGui CPU captures are under previews/supplied-media/;
Anime player/Settings screenshots and checkerboard alpha cutout visually inspected.
Contact sheet/offline viewer included in private preview bundle. New host serializer
embeds the real RGBA texture; it does not paint a mock character onto a screenshot.

Private media bundle: KennyPvtHax-Supplied-Rias-Private-Media.zip, 19 files,
2079652 bytes; SHA-256 `4c261812a836c0c026bfba37cd5996cc7c6b69ac39d218e891d7b1b4c2a70782`.
ZIP CRC, each byte-exact original and each converted runtime digest match inventory.
Rejected image-editor redraw, caches and build outputs are excluded. User media
remain private; neither Git history nor public artifacts contain them.

The final checkpoint updates documentation only. Runtime sources/assets metadata
remain identical to the compiled commit above. Next: owner installs the exact .so
AND private media pack, selects Rias / supplied event clips, and device-tests before
any production promotion. No Anilxkenny/kenny.json update occurred.
