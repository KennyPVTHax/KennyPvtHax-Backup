# KennyPvtHax

Complete C++/ImGui Android native project with the full Classic Electric
Starfield, Living Crimson Aurora, and Anime presentation systems. Includes
horizontal navigation, the circular photo launcher/header, appearance settings,
character/voice registry, optional Android audio and video, diagnostic logging,
and the original 37 feature bindings/ranges. This task preserves the existing
interface; it does not redesign it.

See [MAIN_INTEGRATION.md](MAIN_INTEGRATION.md) for the current integration,
owner-file hashes, rollback checkpoint, tests, build commands, and the distinction
between the public source build and the complete private embedded-media build.
Earlier build reports describe only their explicitly identified source commits.

## Clone and build

```bash
git clone https://github.com/KennyPVTHax/KennyPvtHax-Backup.git KennyPvtHax
cd KennyPvtHax
/path/to/android-ndk-r25c/ndk-build \
  NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk \
  NDK_APPLICATION_MK=jni/Application.mk -j2
```

Use **Android NDK 25.2.9519653 (r25c)**. `jni/Application.mk` targets
`arm64-v8a`, Android API 21+, and static libc++; the module uses C++17.
The owner's genuine original SDK is tracked at `jni/SDK/` (2,391 files).
All 40 supplied static libraries remain at their original paths.
No SDK stubs or replacement headers are used.

Output: **`libs/arm64-v8a/libAnoy.so`**. This is a native shared library, not an
APK. Integrate it through the existing original Android host/loader; no new
Gradle/Java packaging system is introduced. The module remains `Anoy` for
compatibility. System dependencies include log, android, OpenSL ES, EGL/GLES,
zlib and mediandk, as specified in `jni/Android.mk`.

## Embedded media and redistribution

The default complete **private** build links the genuine supplied circular
logo, Anime movie/still, character metadata and prepared voice recordings via
`KPH_MEDIA_DIR`. It needs no separate default runtime media installation; only
the existing private movie cache is created lazily. No foreground Rias cutout
is restored over the default video. See the exact input hashes, preparation
commands and resource contract in [EMBEDDED_MEDIA_INTEGRATION.md](EMBEDDED_MEDIA_INTEGRATION.md).

Public Git includes the complete integration source and tools, manifests, and
five previously reviewed **CC0 CiciFyre alternative** WAVs. These are not Rias
actor recordings; their provenance is in [RUNTIME_ASSET_LICENSES.md](RUNTIME_ASSET_LICENSES.md).
The supplied third-party video, photo/artwork and original recordings remain
private because public redistribution rights have not been verified. A public
clone or default public Actions artifact therefore uses optional external/media
fallbacks; it is **not a self-contained embedded media binary**. Private inputs
are necessary to reproduce that complete experience. No fake media are supplied.

Do not publish a binary linking private inputs merely because the repository is
public: its assets can be extracted. Original private media and rollback binaries
are retained outside Git. No Anilxkenny manifest or production archive is changed
by this source integration.

## Tests and CI

```bash
python3 tests/run_ui_regressions.py --sanitizers
```

Host tests require Python 3, Pillow, g++, zlib and OpenSSL development libraries.
Genuine-media tests additionally take `--user-media`, `--presentation-media` and
`--embedded-media` paths; see [MAIN_INTEGRATION.md](MAIN_INTEGRATION.md).
The manual GitHub Actions native workflow requires public-source sanitizer tests
before building with the same NDK. It never uploads plaintext private symbols or
the private embedded-media binary. The original SDK is unchanged.

Current source retains the owner's main versions of `Helper/bypass.h` and
`Lua_Buffer.cpp` byte-for-byte. These differ from the reported device-working
embedded baseline. The UI includes are isolated from inherited structure packing,
without changing those files or original native behavior. Host/native compilation
cannot prove this combination works on-device. Keep the original tested binary
for rollback and verify startup, touch/dragging, all themes, real audio/video,
GL context recovery and performance on Android before any production release.

Recovery tag: `backup/main-before-full-ui-verification-20261014`.
Known working embedded source: `49e56a7ea335bbf235284131f9c8bfb6cba2c98f`.

Build/device instructions: [ANDROID_BUILD_INSTRUCTIONS.md](ANDROID_BUILD_INSTRUCTIONS.md).
Diagnostics: [KENNY_ANDROID_CRASH_DIAGNOSTICS.md](KENNY_ANDROID_CRASH_DIAGNOSTICS.md).
Progress: [CODEX_PROGRESS.md](CODEX_PROGRESS.md).
Existing third-party notices remain intact; no blanket rights over character IP
or other third-party content are asserted.
