# Complete repository-based embedded media

Starting main: `1202b838acbbf71f586f69cb33c0a058c09f1d8d`.
The owner explicitly confirmed ownership and public redistribution permission for
all supplied logo, movie/still, character artwork and four named voice clips.
See `assets/PUBLIC_MEDIA_AUTHORIZATION.md` for specific provenance/authority and
`assets/embedded-media-inventory.json` for all 16 exact resource sizes/SHA-256.
The five separately reviewed CiciFyre alternatives retain their CC0 attribution.
This records owner assertions; it does not independently authenticate the actor,
creator, or a third-party rights-holder license. No additional unrelated media
is acquired or published.

## Exact assets, unchanged presentation

All 16 payloads (13 binary media files and 3 JSON metadata files) match the verified
embedded build byte-for-byte: 13,879,633 bytes total. Includes the 10,113,470-byte
1024x576/30fps/40.634830s H264 MP4, its existing PNG still, the 1032x1032 circular
alpha photo, the 1035x1280 transparent cutout, four already-prepared event WAVs,
five CC0 alternatives and the exact character/index/presentation metadata.
No reconversion, substitute media, recompression, event remapping or UI redesign.
Default video composition still has no unwanted foreground cutout; the registered
artwork remains available under the existing preference. Movie audio remains
muted by the existing engine. The old K remains only the existing failure fallback.

Mappings unchanged: user_bullet.wav -> Bullet OFF/ON; user_aim.wav -> Aim OFF/ON;
user_aimoff.wav -> Aim ON/OFF; user_extrafeatures.wav -> open Extra features.
No Bullet OFF recording is fabricated. Original OGGs remain unchanged locally;
only prepared runtime resources are necessary for a reproducible application build.
Their original hashes and conversion evidence remain in SUPPLIED_MEDIA_MANIFEST.json.

All existing UI/render/audio/video/input/native files are unchanged. Only native
build input selection in `jni/Android.mk` changes. The two manual native files
retain their exact hashes from the starting main; SDK and 37 original bindings
are unaffected.

## Reproduce from a normal clone

```bash
git clone https://github.com/KennyPVTHax/KennyPvtHax-Backup.git KennyPvtHax
cd KennyPvtHax
# Python 3.10+ and genuine Android NDK r25c (25.2.9519653):
/path/to/android-ndk-r25c/ndk-build \
  NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk \
  NDK_APPLICATION_MK=jni/Application.mk \
  KPH_DIAGNOSTICS=1 KPH_BUILD_ID="$(git rev-parse HEAD)" -j2
python3 tools/verify_embedded_library.py \
  --library libs/arm64-v8a/libAnoy.so --media .build/embedded-media \
  --output .verification/embedded-media-verification.json
```

`Android.mk` now automatically invokes `tools/generate_embedded_media.py`, reads
only committed `assets/` files and validates every pinned size/SHA-256. Missing or
modified required media fail the build rather than silently producing a smaller
fallback library. Generated assembly/table/inventory stay in ignored `.build/`;
no per-frame resource work or new runtime code is introduced. An explicit
`KPH_MEDIA_DIR` still supports existing prepared-resource builds, but is no longer
mandatory. The script's generated local paths derive from the current checkout;
none depend on a private workspace, original ZIP or source JPEG.

Output remains ARM64/API21+ `libs/arm64-v8a/libAnoy.so`, not an APK. All original
SDK/static dependencies are tracked. The source module is not renamed.

## Host and CI verification

```bash
python3 tools/generate_embedded_media.py --output .build/embedded-media
python3 tests/kenny_repository_media_check.py
python3 tests/run_ui_regressions.py --sanitizers \
  --user-media "$PWD" --presentation-media "$PWD" \
  --embedded-media "$PWD/.build/embedded-media" --label repository-media-regressions
```

The fixture now selects the diagnostic `default` pack by ID, rather than assuming
production pack order. The presentation check validates both the earlier opaque
photo and the actual approved circular RGBA logo. Neither change edits runtime UI.
The generator is tested from a relocated tree, including idempotent writes and
rejection of missing/corrupt/symlink/traversal inputs. Existing real embedded
registry/voice/cache/PNG/checksum tests and the 37-binding/source audits remain.

Public Actions now runs the complete 16-suite resource tests, generates the same
pack, builds it with NDK 25.2.9519653, and verifies every linked payload in the
actual stripped ELF before artifact upload. Artifact includes the library, build
metadata, inventory and resource-verification JSON. Private plaintext debug
symbols remain excluded/encrypted through the existing workflow.

Final executed results, source/build SHA, library checksum and CI run are recorded
in `MEDIA_COMPLETION_BUILD_VERIFICATION.json` after validation. Native compilation
and host tests do not establish real-device playback or runtime stability of the
owner's retained native revisions. No live Anilxkenny manifest or archive changes.
