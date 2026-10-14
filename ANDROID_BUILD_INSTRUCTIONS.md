# Latest private embedded-media build

Clean local Android NDK **25.2.9519653** ARM64 build verified for source
`49e56a7ea335bbf235284131f9c8bfb6cba2c98f`; all 16 linked media payloads and loader ZIP verified.
The original SDK is present and unchanged. This is a native `.so`, not an APK.
See [EMBEDDED_MEDIA_INTEGRATION.md](EMBEDDED_MEDIA_INTEGRATION.md) for explicit
private resource generation / KPH_MEDIA_DIR flags, and
[EMBEDDED_MEDIA_BUILD_REPORT.md](EMBEDDED_MEDIA_BUILD_REPORT.md) for hashes,
first-device tests and blocked production gates. This build requires no manually
installed default media pack: only movie cache storage is created automatically
in the owning application's private directory. Android video/audio/device behavior
remains unverified. No private media uploaded to public Actions or loader repo.

--- Historical build instructions ---

## Audio recovery checkpoint A

Continue the working full UI, not recovery stage 1. The library still builds as
libs/arm64-v8a/libAnoy.so with unchanged NDK 25.2.9519653. The diagnostic deployment
ZIP aliases it to libloader.so at archive root, without changing the NDK module.
User-supplied media remain separate/private and need an authorized import into the
actual NativeActivity's owning private directory; the .so alone does not install
them. Restart after import and select the supplied pack. See
AUDIO_RECOVERY_CHECKPOINT_A.md for verified build/checksums, host contract,
Test Voice, diagnostic retrieval and remaining device verification. Video/logo
checkpoints are deferred. No production loader manifest update.

# KennyPvtHax — first Android build

Export date: 11 October 2026 (Asia/Calcutta). Application checkpoint: `3436f47`.
No UI, theme, gameplay, licensing, native integration or SDK reference was changed
for this export. Build documentation is added without changing Git HEAD.

## Emergency startup diagnostic build

See [KENNY_ANDROID_CRASH_DIAGNOSTICS.md](KENNY_ANDROID_CRASH_DIAGNOSTICS.md)
for startup checkpoint logging, private report rotation, authorized host FD
export to Documents, ADB recovery and matching-symbol instructions. The latest
pre-fix Actions build at `7381b71` passed with NDK **25.2.9519653 (r25c)**; the
workflow retains that version for diagnostic builds. This is compilation evidence,
not proof of device stability. Older notes about the exact NDK being unknown
below describe the original export, before the workflow was supplied.

Private logs: `<activity.internalDataPath>/KennyPvtHax/CrashReports/`.
Documents export requires the original Android host's SAF/MediaStore bridge;
no broad storage permission or automatic external upload is added. A public
repository cannot hold plaintext private symbols: the workflow uploads them
only encrypted when `KPH_SYMBOLS_AGE_RECIPIENT` is configured. The normal native
filename remains `libs/arm64-v8a/libAnoy.so`.

Latest diagnostic ARM64 result: **success**, source `c975a6d`,
[run 38117222977](https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38117222977).
Use its matching runtime artifact and build metadata; native compilation and
host regressions passed, but device startup stability remains unverified.

## Current repository update — original SDK included

The owner has now supplied `SDK.zip`; its 2,391 original source/header files are
tracked unchanged under `jni/SDK/`. A current Git clone includes them, so no
separate SDK restoration is necessary. Archive/source hash and path validation
are recorded in `SDK_IMPORT_VALIDATION.json`. The instructions below about
restoring the omitted SDK describe the older standalone export ZIP only.

The Android NDK is still unavailable in the verification environment, and the
compatible NDK release remains unknown. Android compilation/linking, runtime
loading, GPU/audio behavior and device performance have not been verified.
Existing build scripts, internal library naming and application behavior remain
unchanged.

## What this project builds

`jni/Android.mk` uses `BUILD_SHARED_LIBRARY`, `LOCAL_MODULE := Anoy`.
The output is **`libAnoy.so`**, not a standalone APK. The internal module name is
preserved for compatibility; visible branding remains KennyPvtHax. Expected
ndk-build outputs: `libs/arm64-v8a/libAnoy.so` and the intermediate
`obj/local/arm64-v8a/libAnoy.so`.

There is no application-level Gradle/Java/AndroidManifest/APK packaging project
in the supplied root. Dear ImGui's Android example is third-party sample code,
not the KennyPvtHax application. Use your existing original application/loader
integration to package and load this library. Its constructor and runtime expect
the original native environment; loading it into an invented sample Activity
does not constitute a valid device test.

## Host and toolchain requirements

- Use a desktop host supported by the selected Android NDK distribution: Linux,
  macOS or Windows. The available verification host is Linux; Android/Termux
  on-phone compilation is not established by this project.
- Required: the NDK's `ndk-build`, Clang/Clang++, linker, archiver, C++ standard
  library and Android sysroot. The project requests **C++17** and `c++_static`.
- **Exact required NDK version is unknown.** No `ndkVersion`, `source.properties`,
  original toolchain record or project pin is present. Some bundled objects
  contain Clang 7.0.0/7.0.2 and Android build 4751641 tags; these establish legacy
  provenance, not a tested NDK release. Prefer the toolchain that built your
  original project, then validate compatibility. No version has been installed,
  upgraded or claimed successful here.
- `jni/Application.mk`: **arm64-v8a**, **android-21**, release optimization,
  static libc++, thin archives and PIE setting. These are configuration facts,
  not proof of API-21 device compatibility for the original runtime integrations.
- The NDK sysroot provides Android API headers/libraries for this native build.
  A separate Android SDK/Gradle installation is needed only by your original APK
  packaging workflow; its exact requirements are absent from this source upload.
  Android SDK **platform-tools/adb** is useful for device diagnostics. It is not
  a replacement for the omitted generated application SDK described below.

## Restore the original generated SDK — older source ZIP only

After extracting the source archive, restore your genuine original SDK to:

```text
KennyPvtHax/jni/SDK/
```

Do not create `jni/SDK/SDK/`. Keep exact case and relative paths. At minimum the
existing build references these files, plus their genuine dependent headers:

```text
jni/SDK/PUBGM_BangJO.hpp
jni/SDK/PUBGM_Basic.cpp
jni/SDK/PUBGM_Basic_functions.cpp
jni/SDK/PUBGM_CoreUObject_functions.cpp
jni/SDK/PUBGM_Engine_functions.cpp
jni/SDK/PUBGM_ShadowTrackerExtra_functions.cpp
jni/SDK/PUBGM_Client_functions.cpp
```

`jni/SDK.hpp` already includes `SDK/PUBGM_BangJO.hpp`; SDK C++ sources remain in
`Android.mk`. The old source ZIP omitted the SDK; the current Git repository
includes the owner-supplied original files. For an old ZIP, restore the complete
matching original SDK, not just the seven listed files.

## Native dependencies already included

All original application source and required untracked third-party files are
included with their directory layout. This includes `jni/Helper/Login.h`, native
integration helpers, Dear ImGui/backends, embedded fonts, curl/OpenSSL headers,
Dobby, shadowhook, Substrate, KittyMemory, base64 and the original prebuilts.
Public key material is not a private key; original runtime configuration remains.

The export retains **all 40 original `.a` libraries**, including unused ABI
variants, because they are supplied dependencies rather than temporary build
objects. All **20** libraries actively referenced for arm64-v8a exist, pass
archive parsing and contain AArch64 objects. Exact paths/machine checks are in
`BUILD_DEPENDENCIES.json`. ABI inspection does not establish link compatibility.

System linker dependencies from the unchanged makefile:
`log`, `android`, `OpenSLES`, `EGL`, `GLESv1_CM`, `GLESv2`, `GLESv3`, `z`;
static libc++ is selected separately by `Application.mk`. No extra audio/image
framework is required. The unavailable NDK still blocks native compilation here;
the original SDK is now included in the Git repository.

## Media restoration — separate private archive

Extract `KennyPvtHax-Private-Media.zip` into the **same parent directory** as the
source archive. Its `KennyPvtHax/assets/anime/highschool_dxd_rias/voice/` entries
merge with the source project's manifests without overwriting source code.

Five ready runtime recordings: `cici_hello.wav`, `cici_see_you_later.wav`,
`cici_okay_happy.wav`, `cici_okay_normal.wav`, `cici_no_problem.wav`.
They are CC0 Cici Fyre English alternatives, **not authentic Rias recordings**.
Bytes match the C3 installed derivatives exactly. Seven event mappings are in
the original current manifest. Classic/Aurora UI tones are synthesized by the
existing C1 engine and need no external audio files.

The media archive also retains all 57 original licensed Cici recordings and all
six original uploaded OGGs separately under `private-media-reference/`.
Those OGGs have unverified permissions/spoken content and are **unmapped**;
do not package that reference folder into your application. One exceeds the
existing four-second voice limit. No recording was shortened, recompressed,
renamed within its original reference group or silently embedded. Per-file
hashes/status appear in `PRIVATE_MEDIA_INVENTORY.json` and `PRIVATE_MEDIA_README.md`.
Rias character/launcher PNGs and original mapped voices remain absent.

To use the verified runtime pack in your existing APK workflow, place the
contents of the source project's `assets/anime/` under the APK asset prefix
**`anime/`**. For an existing conventional Android module this usually means
`<your-app-module>/src/main/assets/anime/`; use your real project's structure.
The native code stages `anime/index.json`, manifests and approved local files
once into `<activity.internalDataPath>/assets/anime/`. Existing private files are
preserved. Alternatively restore those files through your original app-private
installation workflow. A loose `assets/` folder beside the `.so` is not loaded
automatically. Registry media changes need restart; theme/preference switching
for loaded assets is immediate. Native staging has not been tested on Android.

## First build commands

From the current cloned `KennyPvtHax` root (or after restoring the SDK into an
older source ZIP checkout):

```sh
test -f jni/SDK/PUBGM_BangJO.hpp
test -f jni/SDK/PUBGM_Basic.cpp
"/path/to/your/android-ndk/ndk-build" \
  NDK_PROJECT_PATH=. \
  APP_BUILD_SCRIPT=jni/Android.mk \
  NDK_APPLICATION_MK=jni/Application.mk \
  -j2
```

The placeholder is your actual installed NDK path; no version is implied.
For an error-focused rebuild add `V=1` to show actual compiler/linker commands.
Windows Command Prompt, from the same project root:

```bat
"C:\path\to\android-ndk\ndk-build.cmd" NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk NDK_APPLICATION_MK=jni/Application.mk -j2
```

Then inspect `libs/arm64-v8a/libAnoy.so` using the selected NDK's `llvm-readelf`
or equivalent. It must be ELF64/AArch64. Integrate it through your existing
original app pipeline; this export supplies no invented APK/bootstrap system.

## Host verification and archive verification

Executed again for this export: 37 exact original bindings/ranges/formats and
callback extraction; native menu/launcher/audio/theme/persistence/Aurora/effects
regressions; C2 asset/voice tests; C3 real clip routing/preferences; uploaded and
licensed media integrity. Source unchanged versus the checkpoint, so existing
host binaries were reused for the regression suites. A fresh strict portable
header compile and strict C3 build were also run. These are **host checks**,
not Android build/playback/GPU/device tests.

`export_support/` contains only two small reproducibility headers: the actual
current panel/configuration test fixture and approved Aurora reference snapshot.
They are not SDK substitutes and are not part of `Android.mk`. They allow native
host menu tests to compile without exporting Git history. Generate local test
outputs under `.verification/`, and use `-I export_support` instead of the old
`-I .verification` for those two headers. Original scripts that call `git show`
still need the original history; do not expect them to work in a ZIP checkout.
The original diagnostic fixture generator does not require Git. See tests/README.md
for the remaining host suites and their limits.

On the export directory, verify hashes with:

```sh
sha256sum -c SHA256SUMS.txt
python3 VERIFY_EXPORT.py
```

The portable Python checker verifies both ZIP CRCs, every inventory byte/hash,
safe relative entries and the SDK absence. No absolute workspace path is used
as an archive entry. All source/required prebuilt files preserve original bytes;
only export documentation/support inventories are added. No Git objects,
credentials, local build objects, previews, model caches, logs or old `anony.zip`
are included. The credential scan found no high-confidence token/private-key
matches; this is a finite scan, not a claim that every arbitrary string is known.

## First device test

1. Use your original compatible app/loader and matching generated SDK/native
   runtime. Preserve existing app data before the first test. Do not invent a
   separate APK merely to load this library.
2. Check the device ABI with `adb shell getprop ro.product.cpu.abi` and API with
   `adb shell getprop ro.build.version.sdk`; use an arm64 environment. Install/run
   the APK through your original workflow, using platform-tools if needed.
3. Confirm the K launcher is bounded/draggable, opens/closes smoothly and retains
   the last tab. Test all five categories/seven panels, scrolling and viewport
   fit. Confirm existing values/ranges and no input capture outside the menu.
4. Check Aurora intensity/stars/touch response and Reduced motion; switch Classic
   and Anime repeatedly. Missing Rias artwork should use the dark surface/K
   fallback, not an opaque rectangle or fabricated image.
5. Check UI mute/master volume, theme profiles and the clearly labeled Cici Fyre
   pack/independent voice volume. Verify no sound on passive frames or slider
   dragging and no overlapping voices. Compare local installed asset hashes.
6. Restart the original application and confirm appearance/character preferences
   survive. The unchanged private filename is `kennypvthax-appearance-v1.conf`;
   current schema is 3. No live user configuration is included in the archive.
7. Inspect `adb logcat` locally for native crashes, EGL/asset errors or OpenSL
   failures. Device FPS, GPU alpha/context cleanup and playback require actual
   testing; no success is claimed here.

The original `ResetLogin` callback removes application data. It was not invoked
by host regression tests; avoid it during the initial UI smoke test unless you
intend that existing destructive action. This export does not alter it.

## Troubleshooting and current blockers

- Missing `SDK/...`: restore the complete original `jni/SDK/` with correct case;
  do not add stub headers or remove sources from the makefile.
- `ndk-build` absent: use your original compatible NDK. The exact release remains
  unknown; no Android compilation was attempted without the NDK.
- Prebuilt linker errors: compare AArch64, original NDK/libc++ provenance and
  required symbols; preserve original libraries before any separately authorized
  rebuilding. The legacy compiler tags do not guarantee current toolchain support.
- `libAnoy.so` built but no APK: expected; supply your existing packaging/runtime
  integration. The module/library filename is intentionally unchanged.
- Voice pack missing: ensure APK prefix `anime/` or the real app-private asset
  path, not an external source folder. Restart after installing media; existing
  staged files are not overwritten. Keep unverified OGG references separate.
- Artwork missing: expected. Authorized Rias transparent PNGs/original voice
  mappings are still absent; alternative clips are not represented as Rias.
- Unsupported new media: current decoder supports bounded RGBA PNG and PCM16 WAV,
  not WebP/OGG/MP3; do not silently truncate or replace recordings.
- NDK/API/ABI mismatch or native runtime crash: retain the first verbose compiler
  error/logcat backtrace for the next build task. No gameplay/SDK/backend changes
  were made to conceal errors. Native Android compilation/linking, GPU/audio,
  private storage/asset staging and device performance all remain unverified.

Stop after this export. The next task is restoring your original SDK and testing
the real Android build, not further UI/asset/key-entry development.
