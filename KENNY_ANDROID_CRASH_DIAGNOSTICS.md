# KennyPvtHax Android startup diagnostics

This is a diagnostic correction to the application at `7381b71`, whose Actions
run [38112660886](https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38112660886)
compiled successfully with **NDK 25.2.9519653 (r25c)**. A successful build did not
establish device stability. No device crash trace was provided; the actual
reported crash's root cause is **not established**.

## Corrected source defects and boundaries

- `_HAI` previously called `ImGui::GetIO()` without a context/readiness check,
  and input/render threads could mutate ImGui concurrently. Input callbacks now
  put bounded plain events into a mutex-protected queue; only the rendering
  thread applies them, with valid dimensions. Moves coalesce, press/release
  transitions span frames, and overflow cancels a potentially held button.
- `_OI` received `InputConsumer` / internal `MotionEvent` C++ instances, then
  incorrectly treated `thiz` as an `AInputEvent`. It now only forwards the existing
  original function; UI input comes from the existing `AInputQueue_getEvent`
  integration. Original registrations and offsets are unchanged. Test this
  actual game's queue delivery on-device; source inspection cannot prove it.
- Embedded base/icon/ESP font arrays had default heap ownership. Their atlas
  must not free static storage. All embedded inputs now use non-owning configs
  (this ImGui version copies those inputs internally). Real embedded atlas
  build/clear/context recreation passed ASan/UBSan on the host. This proves a
  lifetime defect was corrected, not that font freeing caused the startup crash.
- Window/configuration, current EGL display/draw surface/context and positive
  dimensions are checked before UI operations. GLES3 and backend/font failures
  defer UI, preserving original swap forwarding. Shader compile/link failures
  are now returned instead of ignored. Native lifecycle/GPU behavior needs a
  device test; non-null checks do not validate arbitrary game pointers.
- The renderer owns its ImGui context. A try-lock serializes UI render calls;
  secondary live EGL contexts are forwarded without creating more UI resources.
  When the old owner is no longer a valid EGL context it forgets old GL names
  without deleting names in the replacement namespace, then recreates resources. Navigation/launcher state
  and appearance remain. This GPU path has not been exercised on Android here.
- The constructor records diagnostics and checks thread creation. A constant-
  initialized atomic barrier delays the worker until this translation unit's
  dynamic C++ globals are initialized; the discovered app is atomically published
  to presentation code. It does not validate/change SDK offsets or loading.
- `FixGameCrash()` is a documented no-op. Automatic private-file deletion,
  chmod-based obstruction and crash-report suppression are removed. Original
  source remains in history. The existing manual Guest Reset callback is retained
  for binding compatibility: **do not invoke it during crash diagnosis**.
- Optional audio reports actual OpenSL initialization failures and remains
  unavailable safely after a failed attempt. Character staging/registry/texture
  checkpoints describe actual attempts and safe missing-asset fallbacks. No
  Aurora/Classic/Anime design or gameplay algorithm was changed.

## Logging architecture and privacy

`jni/KennyDiagnostics.h` depends only on libc/POSIX, pthreads, atomics and Android
logcat. It has no ImGui, GL, audio or asset dependency. The tag is **KennyPvtHax**.
Each line includes UTC time/milliseconds, KPH stage, severity, Linux TID, error
code and `ok=0/1`. An INFO `ok=0` "started" line identifies an in-progress step;
WARNING/ERROR identifies a failure or unavailable prerequisite. Error numbers
come from the corresponding errno/EGL/OpenSL operation where meaningful; 0 means
no specific code was available. No addresses, tokens, keys, preference contents,
raw memory, personal filenames, network transmission or automatic upload.

Before private storage exists, a **64 x 512-byte bounded ring** retains the most
recent milestones; logcat receives them immediately. When a valid activity
private directory exists, the ring is flushed to:

```text
<activity.internalDataPath>/KennyPvtHax/CrashReports/startup-report.txt
```

For a host supplying `Context.getFilesDir()` this is normally:

```text
/data/user/0/<package>/files/KennyPvtHax/CrashReports/startup-report.txt
```

The host may supply a different legitimate private directory; use that exact
root. Reports are 0600, directories 0700, no symlink following for opened roots/
files. The current report is capped at **64 KiB**. Three previous startups remain
as `startup-report.previous-1.txt` through `previous-3.txt`. A fixed pending file
is safely created/flushed before rotation; a pending file from interrupted setup
is retained as `startup-report.interrupted.txt`. Rotation never deletes ordinary
application data/preferences. A previous report is evidence of a previous run,
not a claim that a fatal signal occurred.

Each actual milestone is flushed with fsync; one-time markers do not repeatedly
write every frame. File write failures stop repeated persistent writes and leave
logcat available. There are **no fatal signal handlers**, allocation/locking in
signal context, changes to Android tombstones or crash-reporting suppression.
SIGSEGV/SIGABRT/SIGKILL, power loss or a crash before storage registration may
prevent a final write. Use logcat/tombstones alongside the last durable stage.
No timestamped fatal report or unwinding is fabricated.

## Checkpoint map

IDs describe stages; thread scheduling means they need not appear numerically
sorted. INFO completion and WARNING readiness messages can both appear once.

| ID | Meaning |
|---|---|
| 001 | Native constructor entered; includes exact build commit |
| 002 | pthread creation result |
| 003 | Startup thread entered |
| 004 | Application unavailable; presentation deferred |
| 005 | Native window/configuration readiness |
| 006 | EGL display/draw surface readiness |
| 007 | Current EGL context/GLES3 readiness |
| 008–009 | ImGui context creation start/result |
| 010–011 | Embedded fonts start/atlas result |
| 012–013 | Android/OpenGL backend start/result |
| 014 | Appearance load start/result or diagnostic skip |
| 015 | Character registry load start/result |
| 016 | APK staging start/result; actual registry validates assets |
| 017 | Optional audio start/result or isolation |
| 018 | Launcher initialization/draw reached |
| 019 | First ImGui frame start |
| 020 | First frame and GL draw submission completed |
| 021 | First menu draw completed, only after launcher is opened |
| 022 | Destructive startup routine disabled |
| 023 | Waiting for existing native runtime |
| 024 | Existing application context discovered |
| 025 | Waiting for existing SDK globals |
| 026 | C++ globals barrier passed |
| 027 | Private diagnostic storage setup result |
| 028 | EGL context changed; presentation resources recreated |
| 029 | Surface dimensions unavailable |
| 030 | Original swap forwarding unavailable |
| 031 | Combined application/window/EGL preconditions ready |
| 032 | Presentation-only isolation flags for this build |
| 033 | Later optional audio failure |
| 034 | Character texture/voice routing preparation start/result |
| 036–039 | Existing native integrations / Lua / item configuration boundaries |
| 040 | Secondary live EGL context skipped; original UI owner retained |

If the process dies before 027, app-private persistence may not have been
possible. Record logcat before launch; the host can register private storage
earlier with the interface below. A constructor may run before the host has any
available application context, so this module never assumes one there.

## Authorized Documents export: host integration required

**Documents export is not implemented/tested in an Android host here.** This repo
contains a native `.so`, not the host Java/Kotlin app. It does not directly write
`/storage/emulated/0/Documents/`, request broad storage access, or infer permissions.
The following real exported C symbols are available (default ELF visibility):

```cpp
extern "C" bool KennyPvtHaxDiagnosticsSetStorage(const char* privateDirectory);
extern "C" bool KennyPvtHaxDiagnosticsExportToFd(int destinationFd,
                                                unsigned previousReportIndex);
```

Host implementation in its existing settings/debug recovery screen:

1. After its original library load, register `context.getFilesDir().getAbsolutePath()`
   through a JNI bridge. An independent host bridge can resolve these two symbols
   using `dlsym(RTLD_DEFAULT, ...)` or the existing library handle. Do not introduce
   a different APK loader. JNI converts its UTF-8 directory to the first function
   and releases the string after the synchronous call.
2. For Android 10/API29+, insert into `MediaStore.Files.getContentUri("external")`
   with MIME `text/plain`, a timestamped DISPLAY_NAME, RELATIVE_PATH
   `Documents/KennyPvtHax/CrashReports/`, and IS_PENDING=1. Open a
   `ParcelFileDescriptor` in `"w"` mode and pass `getFd()` to the second function
   from a worker thread; 0 selects current, 1..3 selects previous. Close the PFD.
   On success clear IS_PENDING; on failure delete **only this newly created
   pending export**, preserving private reports. Handle SecurityException/IOException.
   This writes the host's own newly created MediaStore document; no broad storage
   permission is needed. Device/provider policy may still deny an operation.
3. Alternative for API19+ or a denied MediaStore operation: use
   `ACTION_CREATE_DOCUMENT`, MIME `text/plain`, and a suggested report filename.
   Let the user select Documents/that folder, then open the returned authorized
   URI's PFD and call the same FD interface. Do not convert content:// URIs into
   filesystem paths. Support cancellation. A user-authorized SAF folder grant
   can support later automatic exports by the **host**, with visible opt-in.
4. The native exporter snapshots/copies a bounded report and never owns/closes
   the destination FD, reads unrelated files or finalizes MediaStore transactions.
   It rejects an invalid FD or an FD referencing its own source report. Host
   recovery can invoke this after a failed run without opening any ImGui menu.

Use your existing host package/JNI bindings; none were invented or claimed built.
Until that host integration is added and tested, use app-private reports/logcat.

## First device run and retrieval

Use the diagnostic `.so` from the run linked in the final verification record,
not a different build. `build-info.txt` lists commit, NDK, isolation, both binary
hashes and ELF BuildIDs. The constructor logs its build SHA. Keep APK/loader
integration unchanged and replace only the matching arm64 library.

Before launch, on a computer with platform-tools/authorized USB debugging:

```sh
adb devices
adb logcat -b main -b system -b crash -v threadtime > kenny-first-run-logcat.txt
```

Start that command in a separate terminal, launch the app and wait for the crash,
then stop logcat with Ctrl-C. It deliberately starts before a PID exists. Obtain
focused copies without clearing earlier evidence:

```sh
adb logcat -d -v threadtime -s KennyPvtHax > kenny-startup-logcat.txt
adb logcat -b crash -d -v threadtime > kenny-native-crash.txt
```

The broad capture can contain unrelated sensitive host logs: review/redact it
before voluntarily sharing. No reports are uploaded automatically.

For **your own debuggable host package**, substitute its real package name:

```sh
adb shell run-as YOUR_PACKAGE cat files/KennyPvtHax/CrashReports/startup-report.txt > startup-report.txt
adb shell run-as YOUR_PACKAGE cat files/KennyPvtHax/CrashReports/startup-report.previous-1.txt > previous-startup-report.txt
```

These command forms are documented, **not device-tested here**. `run-as` fails for
ordinary non-debuggable game APKs. ADB cannot freely pull another app's private
directory. In that case use the authorized host export above, permitted platform
crash output/bugreport, or an authorized device debug environment. Do not add a
permission bypass, root exploit or suppress Android crash handling.

Compare the last completed stage with its following "started" entry and fatal
signal/exception. 023→024 implicates the original context discovery boundary;
010 without 011 narrows to font setup; 012 without 013 narrows to graphics;
017 start without result narrows to audio; 019 without 020 narrows to first-frame
work. An unavailable optional component's WARNING is not proof it caused a fatal
crash. 020 proves submission returned, not that the screen appeared; 021 is
expected only after a logo tap.

## Matching symbols and isolation builds

The existing Actions workflow keeps **NDK 25.2.9519653**, `arm64-v8a` and
`libAnoy.so`. Diagnostic make flags add debug info/frame pointers and remove
link-time stripping only for `KPH_DIAGNOSTICS=1`; ndk-build still installs the
stripped runtime library under `libs/`. Matching unstripped output is at
`obj/local/arm64-v8a/libAnoy.so`.

**The repository is public. Plaintext debug symbols are never uploaded.** To
retain a confidential Actions symbol backup, create an age key locally:

```sh
age-keygen -o kenny-symbols-private-key.txt
```

Keep that private key off GitHub. Put only its `age1...` public recipient into
repository Actions secret `KPH_SYMBOLS_AGE_RECIPIENT`. When configured, the
workflow encrypts matching symbols and build metadata with age and uploads only
`symbols.tar.gz.age`. Without that secret, no symbol artifact is uploaded and
runner-local symbols disappear after the job. Obtain symbols via a local build
or rerun with the secret configured; stripped `.so` alone is insufficient for
full line-level symbolization.

After a configured run, privately decrypt on your computer:

```sh
age -d -i kenny-symbols-private-key.txt -o symbols.tar.gz symbols.tar.gz.age
tar -xzf symbols.tar.gz
/path/to/ndk/ndk-stack -sym obj/local/arm64-v8a -dump kenny-native-crash.txt
```

Match BuildID/commit to the device library first. For a PC relative to
`libAnoy.so`, the same NDK's `llvm-addr2line -C -f -e
obj/local/arm64-v8a/libAnoy.so <RELATIVE_PC>` is another method; do not feed a raw
ASLR absolute address without the correct module/load mapping. Keep symbols,
crash captures and decrypted archives private. No trace or address is invented.

Workflow `isolation` input matrix (restart with each exact artifact):

| Input | Diagnostic change |
|---|---|
| full | All approved presentation/features enabled; start here |
| no_audio | Skip optional OpenSL initialization/playback |
| no_artwork | Skip character GPU uploads; safe K/background fallback |
| no_preferences | Session defaults; skip preference read/write |
| classic | Session Classic presentation; no preference persistence |
| no_menu | Keep startup/frame checkpoints; skip logo/menu draw |

None changes gameplay offsets/algorithms/native registrations. Only repeated
A/B device evidence can implicate an isolated component. Restore `full` to
restore normal presentation; isolation does not overwrite saved appearance.
Normal local command:

```sh
/path/to/ndk/ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk \
  NDK_APPLICATION_MK=jni/Application.mk KPH_DIAGNOSTICS=1 \
  KPH_BUILD_ID="$(git rev-parse HEAD)" KPH_ISOLATION=full -j2
```

## Verification and remaining evidence

Host checks executed: independent logger strict C++ compile, bounded buffer,
0600 files, symlink/unavailable/permission/write failures, concurrent writes,
safe rotation and stale pending preservation, SIGKILL-persistent checkpoints,
FD snapshot export, no repeated milestone writes, fixed input queue and
press/release recovery. Actual embedded font code passed ASan/UBSan across
three atlas build/clear/context recreations. Original 37 full binding/range/
callback statements and all offset literals remain identical to baseline.
Existing menu/C1/audio/theme/Aurora/effects/C2/C3 suites were rebuilt and passed,
including persistence, rapid switching, dragging/scrolling, warmed allocations,
PCM mute/volume/cooldown and approved Aurora physics/draw regression checks.

A diagnostic Actions build is dispatched after commit; its actual result and
artifact are reported in the verification update/final response, not inferred
from these host tests. No Android device test, new EGL context-loss test, real
OpenSL playback, actual host Documents export or tombstone analysis has occurred
here. Send the last startup stages and matching fatal trace from the next run to
establish the smallest evidence-based correction. Do not conclude "crash fixed"
from compilation alone.
