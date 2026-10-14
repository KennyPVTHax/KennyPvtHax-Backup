> Current media/build status: [MEDIA_COMPLETION.md](MEDIA_COMPLETION.md).
> Owner-authorized assets are now committed; the default build embeds them.
> Private-only build statements below describe the earlier checkpoint.

# Private embedded-media integration

Status: **NOT PUBLISHED**. This is a presentation-only integration on
`release/embedded-media-integration`, starting from
`739a2de1ed4710df39a23ac67bab3b680b1bd594` (runtime `1a944d4`). The owner-confirmed
full-UI checkpoint is `2a54a41`, following the blank-header startup correction
at `7934582`. Electric Classic, Aurora, audio diagnostics and the existing Android
video decoder are retained. The previous verified 1a944d4 library/ZIP remain in
`/workspace/shared/downloads/` for rollback.

## Deliberately excluded manual revisions

Source main was checked at `6ef4ec63920bc8be54e2b8d6fcffaf0ceccf056e`.
The requested `bypass.h` revision `bd0eb5c40480312b3db20d9a5a92379a00fa0ded`
adds a native constructor, startup thread, executable library patches and hooks.
The requested Lua revision includes anti-cheat/telemetry/crash-report suppression
and changes native offsets. Those mechanisms were inspected but **not integrated
or activated**. Existing main and these two files were not overwritten. This build
is explicitly not the requested combination of those manual revisions.

| File | Retained SHA-256 | Requested revision SHA-256 (not integrated) |
|---|---|---|
| jni/Helper/bypass.h | 01ba4719c80b6fe911b091a7c05124b64eeece964e09c058ef8f9805daca546b | 3878915f22b76253336e641e2be91429a268aae380fa6788162127407b7a8ce1 |
| jni/Lua_Buffer.cpp | b92231b93b6de973ba3f86dc4b708d1295e9b1ce92741875eac55a8165bfbebb | 35914bd5008f841876167dc75ebf10fa925c25f9e33a46f51a0831ec09f09bf9 |

## Resources and runtime behavior

`tools/prepare_embedded_media.py` accepts the verified private bundle SHA-256
`1ee9216403aa13f2d99266cb22b3491e4c115945293a2054b516a568bc1248fe`
and the actual 1260x1280 circular-logo JPEG. It writes private binary inputs,
`payload.S` with `.incbin` read-only resources, a constexpr lookup table in
`resources.cpp`, and an inventory. Different assembly/C++ basenames prevent an
NDK object-name collision found during preliminary validation. No giant C++
byte literals, runtime downloads, global dynamic resource initialization, or
media uploads are used. Generated assets stay in ignored `.verification/`.

Sixteen resources include the original 10,113,470-byte MP4, actual still frame,
1032x1032 circular alpha logo, original prepared transparent character PNG,
manifests/index, the four prepared user WAVs and five existing CC0 alternative
WAVs. Original OGGs remain byte-for-byte in the unchanged private source bundle.
The launcher crop is `(99,107,1131,1139)` with a circular alpha mask; RGB pixels
are preserved. Native circular fan geometry fills the existing launcher circle,
without inset square/frame/padding. Touch, dragging and visibility logic are
unchanged. K remains the missing-texture fallback.

PNG/WAV bytes decode through the existing bounded decoders directly from linked
memory (temporary bounded decoder vectors only at configuration). The existing
registry/mixer/event router, mute/volume/cooldown and Test Voice remain. New or
missing preferences choose the available supplied event pack; an existing valid
CC0 pack selection is preserved. Mappings are unchanged:

| Original | Existing runtime resource | Genuine user transition |
|---|---|---|
| bullet.ogg | voice/user_bullet.wav | Bullet Track OFF -> ON |
| aim.ogg | voice/user_aim.wav | Aim OFF -> ON |
| aimoff.ogg | voice/user_aimoff.wav | Aim ON -> OFF |
| extrafeatures.ogg | voice/user_extrafeatures.wav | Open Extra features |

No Bullet OFF recording was supplied. No unrelated event gains a user recording.
Voices are loaded independently of external pack installation; actual Android
OpenSL speaker output still requires device testing.

API 21 MediaExtractor consumes a file descriptor. Only the embedded MP4 is
lazily extracted by a bounded worker to
`<activity.internalDataPath>/kenny-media-cache/<video-sha256>.mp4` when Anime
becomes visible. No external media installation/storage permission is required.
It checks regular-file size and SHA-256, writes a private unique temporary file,
fsyncs, atomically renames, and verifies before returning a read-only FD. Existing
valid cache bytes are reused; corruption is replaced. It never deletes unrelated
files, diagnostics or preferences. Interrupted temporary files cannot become
valid cache entries; old orphan temps are not automatically deleted. Cache/decoder
failures preserve the actual still-frame/menu fallback. All GL ownership,
MediaCodec pacing, muted audio, looping, pause and context handling remain with
the existing backend. No media work was added to the native constructor.

Default video composition has no foreground Rias cutout. Video OFF can use the
existing character-art visibility preference as a static background fallback;
the source artwork remains registered for future customization. Controls remain
on top; no layout redesign or feature binding changes.

## Reproduce a private build

Use the real source SDK and Android NDK **25.2.9519653 (r25c)**. Private media must
not be committed or sent to public Actions artifacts without distribution rights.

```bash
python3 tools/prepare_embedded_media.py \
  --bundle /private/KennyPvtHax-Private-Video-Logo-Media.zip \
  --logo /private/IMG_20261014_163955_385.jpg \
  --output .verification/embedded-media
# Source repository root; isolated clean output paths:
$NDK/ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk \
  NDK_APPLICATION_MK=jni/Application.mk \
  NDK_OUT=.verification/embedded-final/obj \
  NDK_LIBS_OUT=.verification/embedded-final/libs \
  KPH_MEDIA_DIR="$PWD/.verification/embedded-media" \
  KPH_DIAGNOSTICS=1 KPH_BUILD_ID="$(git rev-parse HEAD)" -j2
python3 tools/verify_embedded_library.py \
  --library .verification/embedded-final/libs/arm64-v8a/libAnoy.so \
  --media .verification/embedded-media --output .verification/embedded-final/verification.json
python3 tests/run_ui_regressions.py --sanitizers \
  --user-media .verification/user-media \
  --presentation-media .verification/anime-video-logo/private \
  --embedded-media .verification/embedded-media --label embedded-regressions
```

The native module remains `Anoy`; package exactly one byte-identical root
`libloader.so` in `KennyPvtHax-<full-source-commit>-ARM64.zip`. Record both hashes.
The final build report supplies the actual source commit, build ID, dependencies,
file sizes, hashes and exact per-resource ELF byte verification.

## Verification and limitations

Preliminary 15 existing ASan/UBSan suites passed, including original 37 complete
binding/range/callback statements, startup gates and exact approved Aurora
physics/geometry. Focused embedded tests pass real resource loading, default and
saved pack selection, mute/cooldown/theme isolation, alpha, lazy cache, corruption
recovery and unwritable-path fallback. Actual ImGui captures use linked artwork,
logo and prepared voices; host video frames are decoded offline via FFmpeg.
They are **not Android MediaCodec/GPU/speaker/device performance evidence**.
Final native build and post-polish checks are recorded separately after completion.

## Production gates and rollback

Anilxkenny is public. Linked media are extractable from a .so; private-use approval
is not public redistribution permission. Rights for supplied video/logo/artwork/
recordings remain unestablished. No production upload or live JSON change occurs.
The loader reference is checked read-only for the sole root `libloader.so` entry.
Normal CLI write access does not establish Actions secret readiness. The source
repo currently exposes only `build-native.yml`; a prepared pipeline contract in
`/workspace/kenny-loader-pipeline` still has unverified loader version comparison
and device-milestone gates. These gates are not bypassed. No new version is guessed.

For a later authorized deployment, use the configured gated release workflow and
its `ANILXKENNY_PUBLISH_TOKEN`, after comparator/device/media checks. Atomically
commit immutable ZIP plus only `drm`, `drm_name`, `drm_verion` for package
`com.pubg.imobile`; reconcile branch advances without force. Keep older ZIPs.
Rollback restores the previous verified three-field tuple without deleting ZIPs
or altering unrelated JSON. Because this task does not publish, the live tuple
remains untouched and no production rollback is currently needed.
