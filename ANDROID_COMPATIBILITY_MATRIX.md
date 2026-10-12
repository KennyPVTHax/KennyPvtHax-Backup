# Android compatibility matrix

Source reviewed on `audit/android-stability` against a4d7eea/c975a6d.
NDK remains **25.2.9519653 (r25c)**; APP_PLATFORM **android-21**;
APP_ABI **arm64-v8a**; native module/output **libAnoy.so**, not an APK.
The original SDK is present at jni/SDK/ and all 40 static libraries are retained.

| OS | API | Source/API observations | Required runtime evidence | Status |
|---|---:|---|---|---|
| Android 10 | 29 | Native APIs link above API 21; scoped storage applies to host configuration. | Genuine GLES3 owner, NativeActivity/input delivery, OpenSL output, private paths/SAF. | Not device-tested |
| Android 11 | 30 | Direct Documents writes cannot be assumed; host SAF/MediaStore FD bridge required. | Same plus app-private restart and authorized export. | Not device-tested |
| Android 12 | 31/32 | Activity/window replacement and surface lifecycle must be synchronized by the host. | Pause/resume, rotation, multipointer, graphics owner loss. | Not device-tested |
| Android 13 | 33 | Native-only module grants no broad storage or overlay permissions. | Original host packaging/permissions and audio device behavior. | Not device-tested |
| Android 14 | 34 | libinput is an internal interface; audit makes no interface-stability guarantee. | Existing AInputQueue delivery and all supported display sizes. | Not device-tested |
| Android 15 | 35 | 16 KiB page-size devices require additional ELF/host packaging validation. | PAGE_SIZE, load alignment/errors, input/graphics/audio tests. | Not device-tested |
| Android 16 | 36 | Same page-size and internal-integration uncertainty; link success is not compatibility certification. | Real API 36 device/emulator including 16 KiB configuration and host lifecycle. | Not device-tested |

## Graphics and input

The project deliberately requires a current **GLES3** context. Android/API level
and ARM64 alone do not prove that this host uses GLES3. Context absence, invalid
surface/zero dimensions and unusable backend defer UI. Secondary live contexts
retain the original owner. Context handle reuse/share groups, host thread migration,
window lifetime synchronization, GL out-of-memory and GLES sampler state remain
real-driver questions. Host Mesa tests use desktop OpenGL, not Android GLES.

Existing viewport fixtures cover 2340×1080, 1920×872, 1280×720, 960×540 and
640×360, with scaling, clipping, scrolling and constrained launcher/menu positions.
Host simulation covers 30/60/90/120 Hz. Test landscape resize, rotation while a
finger is down, screen insets/density and touch coordinate transforms on-device.
The primary-pointer adapter preserves one finger by ID; secondary fingers never
own/release that gesture. It forwards all original host input unchanged.

## 16 KiB evidence and next decision

The actual preserved c975a6d ELF has LOAD p_align **0x1000**, verified using
`readelf -l`. That is not evidence of 16 KiB support. Device page size, loader
compatibility mode and APK alignment/packaging must be checked together. Do not
change the active diagnostic artifact or upgrade NDK speculatively. After device
feedback, decide separately whether tested link alignment/host packaging changes
are required. See Android's guidance:
https://developer.android.com/guide/practices/page-sizes

## Audio/storage limitations

OpenSL ES is an existing lightweight backend (deprecated, not universally absent).
Actual callback stop/restart/destruction, output-device/rate behavior, latency and
host audio coexistence require Android tests. Host PCM synthesis is not playback.
No additional permissions, host focus requests or runtime network work are added.

Preferences/logs use private POSIX storage. Real regular-file/FIFO/symlink/failure
checks pass on Linux; Android SELinux/private-path durability requires testing.
Documents export is still **an integration interface**, not a working host feature.
The original Java/Kotlin host is absent. Use authorized SAF or MediaStore, pass
its FD to KennyPvtHaxDiagnosticsExportToFd, finalize the host transaction and
verify access. No direct shared-storage write or new broad permission is assumed.
