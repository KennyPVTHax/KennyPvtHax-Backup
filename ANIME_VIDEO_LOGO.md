# Supplied Anime video and photo launcher

Branch: `ui/anime-video-logo`, parent `1438e94`. This continues the existing full
UI and preserves the blank `jni/Helper/bypass.h`, startup, loading, hooks, input,
SDK, Aurora/electric Classic effects and existing voice mappings. Integration is
limited to optional presentation resources in the already-initialized render
block. No live Anilxkenny publication or manifest update is performed.

## Actual supplied media

- `VID_20261014_160407_167.mp4`: 10,113,470 bytes; 1024×576 H.264 High,
  yuv420p, 30 fps, 40.634830 seconds, with HE-AAC audio. The original MP4 is copied
  byte-for-byte. Runtime selects only its video track; its audio is never played.
- `IMG_20261013_203700_546.jpg`: 152,346 bytes; 1280×1280 RGB JPEG. It has **no
  transparency**. Offline conversion to non-interlaced 8-bit RGBA PNG preserves
  the decoded RGB pixels with alpha 255. No artwork generation, background
  removal, white matte, stretching or substitute logo is performed.
- `anime-fallback.png`: the actual first frame of the supplied movie, used only
  as an explicit still fallback and initial Reduced-motion image.

Exact original/runtime hashes, byte sizes and conversion notes accompany the
private package in `SUPPLIED_VIDEO_LOGO_MANIFEST.json`. Supplied files and previews
remain private/ignored; no artwork/video/audio bytes are committed to GitHub.

## Native video architecture

`KennyAndroidVideo.h` uses Android MediaExtractor/MediaCodec, a Java SurfaceTexture
and Surface created through the existing ANativeActivity's JVM, and an optional
one-worker decoder. No host Java class, replacement renderer, EGL context or new
hook is created. Android chooses its supported AVC decoder; hardware acceleration
and device performance are **not** independently verified here.

The SurfaceTexture is attached to the current renderer's external OES texture.
Decoded output is sampled with its actual transform matrix and blitted into a
cached normal 2D texture using a private FBO/shader/VAO. The existing ImGui image
layer consumes that texture. GL bindings, program, framebuffer/viewport, array/VAO,
active texture, masks and enable states touched by this pass are saved/restored.
Resources initialize only after existing GL/ImGui readiness, not in the native
constructor. GLSL/extension/JNI/decoder failures retain the still or dark fallback.

There is at most one pending decoded surface frame. Dequeue waits are bounded;
frame pacing uses presentation timestamps and monotonic time, dropping frames
more than 100 ms late. An input timestamp offset of 1 ms distinguishes the first
real buffer from SurfaceTexture's initial zero timestamp without changing speed.
Paused/inactive/hidden/off/Reduced states suspend the worker on a condition variable
rather than decoding or polling continuously. If rendering stops during app pause,
heartbeat loss suspends decoding; resumption rebases pacing without hidden-time
catch-up. A pending-frame stall with an active renderer fails safely. Decoder,
surface/global JNI references and GL names have explicit stop/cleanup and
context-loss handling through the existing resource invalidation point.

On EOS, extractor seek/codec flush restart the original movie; the last texture
remains visible until the next frame. The source is an edited montage, so its
last/first pictures are different: do not interpret this as a seamless content
loop or claim that Android looping has been tested. No resampling/re-encoding or
image-sequence replacement is used for the runtime movie.

The Anime background layer is below existing Rias artwork and all menu controls.
The existing Cover/Contain and artwork dimming preferences retain aspect ratio
and readable contrast. Settings adds only Anime Video Background ON/OFF and
truthful playback status. Off reveals the previous Anime presentation. Schema 6
appends its boolean while retaining all schema 1–5 preferences and feature values.
Reduced motion holds an already-presented movie frame, or uses the actual poster
when no movie frame exists. Native video has no connection to the audio engine.

## Photo launcher

The existing floating launcher's logo interface receives the supplied photo
texture in all themes. An explicitly selected available character launcher retains
its existing override. Missing/corrupt/unloadable photo uses the original K.
The image is fit within the existing bounded launcher, with subtle rounded image
corners and cached mipmaps for minification. Tap/drag/open/close/hitbox/DPI logic
is unchanged. Texture references clear before owner loss or deletion.

`KennyPresentationMedia.h` loads fixed manifest filenames via descriptor-relative
app-private opens. PNG dimension/format/file bounds are checked; opaque PNG is
allowed only for this presentation loader. Existing character PNG calls continue
requiring real transparency. Symlinks, FIFOs, traversal and malformed manifests
are rejected. Logo loads once; poster upload is lazy until Anime needs it. The
video file is bounded to 64 MiB, and decoded dimensions to 2,097,152 pixels.
Native status changes log under KPH-041/KennyPvtHax without per-frame logging,
private filenames/addresses or external report uploads.

## Installation — the .so alone is insufficient

The provided project is a native library, not the Android host APK. Installing
only libAnoy.so/libloader.so does **not** install a video/photo or the earlier
Rias recordings. There is no available source for the actual host's importer.
The supplied private ZIP contains `assets/presentation/`:

```
assets/presentation/manifest.json
assets/presentation/launcher.png
assets/presentation/anime-background.mp4
assets/presentation/anime-fallback.png
```

It also preserves the earlier private `assets/anime/` pack and originals, so the
existing voice/artwork installation can be performed together. No audio is
reconverted or remapped. Original OGG/JPEG/MP4 bytes are retained privately.

Use **one** authorized route:

1. In the actual host APK project, copy the private ZIP's `assets/presentation/*`
   into its `src/main/assets/presentation/` (and `assets/anime/*` into the matching
   APK assets directory). The owning activity's AssetManager must see those files.
   Native optional staging copies them into its private directory once, preserving
   existing files. Assets in an unrelated external loader APK are not visible to
   the game's NativeActivity unless that host explicitly transfers them.
2. The owning host's authorized importer installs the ZIP's `assets/*` under its
   genuine `ANativeActivity.internalDataPath`, preserving relative paths. Validate
   the private file inventory/hashes first; stage files in a sibling temporary
   directory, backup outdated assets and atomically rename within private storage.
   Restart the process after installation; this loader intentionally avoids idle
   disk polling. Do not copy the assets one directory too deep.

Expected runtime directory:
`<owning NativeActivity.internalDataPath>/assets/presentation/`.
Android NativeActivity normally obtains this from its app files directory; use
that actual activity value rather than guessing an unrelated package's path.
For a debuggable owner, `adb shell run-as <OWNER_PACKAGE>` can inspect `files/assets/`;
if run-as says the package is not debuggable, that route is unavailable. Do not
bypass private storage permissions. Use the authorized host importer/APK integration.
No external storage permission or runtime media download is added.

The package's inventory can be verified offline before host installation. Existing
APK staging deliberately preserves files; replacing old media requires the host's
safe backup/commit operation and process restart. Do not publish this pack,
previews or original recordings to public GitHub/Anilxkenny.

## Verification and device test

The 14 existing ASan/UBSan suites pass. The new real-media test checks actual PNG
RGB/alpha policy, corrupt PNG, lazy/cached uploads and cleanup, missing media,
symlink/FIFO/traversal/manifest rejection, clock rebasing, and schema 5→6 migration,
restart and malformed tail handling. Native ImGui capture uses the actual supplied
photo/video/Rias pixels, real controls, unchanged 37 feature snapshot, video toggle,
launcher tap/drag, Reduced/off/missing states and small viewport. Sources/SDK/blank
bypass/audio/Aurora/hooks/input/build workflow invariants are audited separately.

The host film preview is genuine supplied movie frames decoded by FFmpeg, passed
through production C++/ImGui draw geometry and CPU rasterized. It is **not** an
Android MediaCodec/GPU test. Runtime keeps the original 30 fps MP4; host review
video samples 49 successive frames at 12 fps with actual ImGui state. Exact video
integrity is verified by complete host decode without re-encoding runtime bytes.

Native ARM64 compile, artifact/hash and source commit are recorded after Actions
in `ANIME_VIDEO_LOGO_BUILD_VERIFICATION.json`. NDK remains 25.2.9519653, API 21,
arm64-v8a; `libAnoy.so` naming stays unchanged. Only `-lmediandk` is added for the
platform decoder. Optional loader ZIP has sole root `libloader.so`. No live push.

On Android: install the exact matching library **and** the private pack using the
owning host, restart, check the photo launcher in all themes, tap and drag it,
select Anime and turn video on. Check voice/artwork still behave as before. Test
40.6-second looping, close/reopen, theme switches, Reduced/off, background/foreground,
app pause/resume, context recreation, and frame pacing/CPU/GPU on the target phone.
Collect `adb logcat -s KennyPvtHax` and note KPH-041 statuses if playback falls back.
Unsupported codec/extension/texture/JNI/stall conditions are nonfatal. Actual
Android output, driver synchronization, loop smoothness and performance require
these device checks; no FPS or sound-playback claim is inferred from host tests.
