# Android stability test plan

Keep the ongoing **c975a6d** diagnostic test unchanged. Do not install this audit
branch build during that test unless the owner chooses to switch. No merge into
main is authorized. The repository is public: keep actual crash logs and plaintext
symbols off GitHub. Only synthetic host results and stripped runtime are artifacts.

## Reproducible host commands

From repository root, with C++17 g++, Python 3 standard library and zlib headers:

```sh
python3 tests/run_android_stability.py --label audit --sanitizers
python3 tests/kenny_gl_stability.py
python3 tests/kenny_benchmark.py --label local
```

Every subprocess has a deadline; two parallel compilations cap resource use.
ASan/UBSan retain assertions. Script outputs go to ignored .verification/.
The GL check requires existing libEGL.so.1/libGL.so.1 with Mesa surfaceless OpenGL;
it builds against the actual bundled ImGui GL loader/backend. It verifies exact
RGBA alpha readback, hostile unpack PBO/row/skip/alignment restoration, rejected
oversize upload and 100 backend recreate/cleanup cycles. It is not an Android
GPU, full EGL-owner-loss, or OpenSL test. No mocked SDK files are used.

Coverage includes exact 37 binding/range/format statements and original callback,
all five categories/seven panels, sliders/checks, reset/center appearance actions,
all three themes, viewport clipping/scrolling and original drag/open/close behavior.
Launcher stress has 100 warmed open/close cycles; character/theme tests include
500 switches and 10,000 cached iterations. Audio includes 20,000 allocation-free
PCM iterations/50,000 queue submissions, mute epochs and cooldown. Input includes
50,000 concurrent submissions, reordered primary pointer IDs, secondary release,
cancel/missing owner, press origins, key frame transitions and overflow Reset.

Storage fault injection uses real regular files/FIFOs/symlinks, syscall-level
short writes/EINTR/ENOSPC/fsync failure, interrupted staging and recovered storage.
Logger tests use actual fork/exec/SIGKILL, report rotation/cap, permissions,
concurrent writes, export FD errors and 20,000 idle once-checks. Font tests use
actual embedded arrays through build/clear/destruction. Corrupt PNG/WAV/JSON
fixtures are diagnostic bytes only, never installed character media.

## Separate branch native build

```sh
gh workflow run build-native.yml --repo KennyPVTHax/KennyPvtHax-Backup \
  --ref audit/android-stability -f isolation=full
```

The audit workflow uses NDK 25.2.9519653, checks SDK inputs/all 40 libraries,
compiles ARM64, verifies ELF/host exports/.debug_info and matching BuildIDs, and
runs host sanitizers. Its runtime artifact is **KennyPvtHax-Audit-ARM64-SO**.
No previous diagnostic artifact is replaced. Plain symbols never upload; encrypted
retention requires configured age public recipient, with private key held by owner.

Exact local native command, with the genuine installed NDK:

```sh
/path/to/android-ndk-r25c/ndk-build NDK_PROJECT_PATH=. \
  APP_BUILD_SCRIPT=jni/Android.mk NDK_APPLICATION_MK=jni/Application.mk \
  KPH_DIAGNOSTICS=1 KPH_BUILD_ID=YOUR_EXACT_COMMIT KPH_ISOLATION=full -j2
```

Output: libs/arm64-v8a/libAnoy.so. Matching unstripped symbols are
obj/local/arm64-v8a/libAnoy.so. This is not an APK; retain the original host loader.

## First device evidence — current diagnostic first

Start capture before launch (replace package with the actual host package):

```sh
timeout 60s adb logcat -b main -b system -b crash -v threadtime > kenny-logcat.txt
adb shell getprop ro.build.version.sdk
adb shell getconf PAGE_SIZE
adb shell wm size
adb shell wm density
```

Launch during the capture interval. Record the exact tested library SHA-256,
BuildID, code commit and last KPH checkpoint. KPH-020 means GL submission returned,
not verified visible output; KPH-021 occurs only after menu opening. Combine the
milestones with the genuine fatal signal/backtrace. Do not invent a stack trace or
attribute failure to Aurora/audio merely because their initialization was nearby.

App-private report: <activity.internalDataPath>/KennyPvtHax/CrashReports/.
For a debuggable original host, retrieval through authorized ADB can use:

```sh
adb exec-out run-as YOUR_HOST_PACKAGE cat \
  files/KennyPvtHax/CrashReports/startup-report.txt > startup-report.txt
```

The files/ prefix assumes the host registers getFilesDir(); verify its actual
internalDataPath. run-as does not work on arbitrary non-debuggable apps. Otherwise
use the original host's authorized SAF/MediaStore integration; do not bypass
storage restrictions. No retrieval/actual Documents export was tested here.

Symbolize with the **matching** unstripped library, never another run's binary:

```sh
/path/to/android-ndk-r25c/ndk-stack -sym obj/local/arm64-v8a -dump kenny-logcat.txt
```

## Device matrix after reviewing findings

1. Cold launch, no storage then valid storage; keep three previous reports.
2. 100 logo/menu cycles, rapid tap/drag and outside-origin gestures.
3. Two-finger press/release in both orders; cancel, resize and orientation change.
4. All 37 feature bindings/ranges unchanged; do not invoke manual Guest Reset.
5. Three themes, corrupted/missing optional media, private preferences restart.
6. Audio muted/unmuted, rapid theme/volume/character events, background/foreground,
   unavailable output device and callback shutdown/restart. Confirm no overlaps.
7. Actual EGL secondary owner/context loss and low-memory texture/font failure;
   confirm host GL state/rendering remains intact. GLES sampler test still needed.
8. Android 10–16, applicable 4 KiB/16 KiB devices, screen/density/refresh matrix.
9. On-device Perfetto CPU/GPU/frame timeline and power measurement before proposing
   Aurora caching/quality changes. Record instrumentation limitations for the host.
10. Correlate fatal evidence, apply the smallest further fix on the audit branch,
    then ask for merge review when device results justify it. No automatic merge.
