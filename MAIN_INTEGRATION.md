# Verified full UI integration into main

## Source and recovery

Remote main at the start of this task was
`812315b89d88ecb59e253554793fb3a73bd34e08`, the owner's merge of
`release/embedded-media-integration` (`b46adba`). It already contains the full
UI and header-photo change (`c2ed7e3`). The user-confirmed embedded baseline is
`49e56a7ea335bbf235284131f9c8bfb6cba2c98f`. Its library hash is
`73843b8fcc29ac624d55f35c7d0fd126e255a85e7aa36f3d6cd4fc2879283340`.
The original checkout and verified binaries are retained in the private workspace.

Recovery tag: `backup/main-before-full-ui-verification-20261014`. This preserves
the original main history; no force push or history rewrite is used. The known
working embedded source remains available at `49e56a7`.

The owner explicitly requested that main's manual files remain unchanged:

| File | SHA-256 retained |
| --- | --- |
| `jni/Helper/bypass.h` | `3878915f22b76253336e641e2be91429a268aae380fa6788162127407b7a8ce1` |
| `jni/Lua_Buffer.cpp` | `35914bd5008f841876167dc75ebf10fa925c25f9e33a46f51a0831ec09f09bf9` |

These revisions differ from the confirmed working embedded binary. Their native
behavior is not changed or extended in this task. A successful native compilation
does not establish startup safety or Android compatibility of this combination.

## Minimal compatibility correction

An earlier header leaves one-byte structure packing active. Without isolation,
the UI preferences changed from size 176/alignment 8/float offset 12 to size
158/alignment 1/float offset 10, and audio/menu structures changed too. The
presentation include block now uses `#pragma pack(push, 8)` / `pop`, matching
separately compiled ImGui and restoring the incoming packing mode before the
original Lua include. No owner file, native offset, constructor, hook, input,
EGL ownership, UI layout or feature algorithm is edited.

`tests/kenny_ui_packing_check.py` compiles the actual presentation include block
both normally and with incoming one-byte packing; it checks identical UI layouts
and restoration of the incoming mode. Existing regression suites also run.

## Media and public/private build distinction

Public Git contains all integration source, resource-generation tools, manifests,
40 original static libraries, the original SDK and five previously reviewed CC0
CiciFyre WAVs. The supplied logo, video, Rias artwork and four supplied recordings
have not been established as publicly redistributable and remain outside public
Git. Linked private media can be extracted from a binary, so public CI must not
upload the private embedded binary either.

The complete private build uses the unchanged prepared 16-resource pack and
`KPH_MEDIA_DIR`; see `EMBEDDED_MEDIA_INTEGRATION.md` for the exact generator,
verified input bundle hash, crop and asset paths. It is reproducible with those
private inputs. A public clone without them builds the same interface and its
safe external/missing-media fallbacks; it is **not a self-contained embedded
media build**. No genuine assets are replaced with placeholders.

Clean private native build from the project root (NDK r25c, 25.2.9519653):

```bash
NDK=/path/to/android-ndk-r25c
MEDIA=/private/prepared-embedded-media
"$NDK/ndk-build" NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk \
  NDK_APPLICATION_MK=jni/Application.mk \
  NDK_OUT=.verification/main-native/obj \
  NDK_LIBS_OUT=.verification/main-native/libs \
  KPH_MEDIA_DIR="$MEDIA" KPH_DIAGNOSTICS=1 \
  KPH_BUILD_ID="$(git rev-parse HEAD)" -j2
python3 tools/verify_embedded_library.py \
  --library .verification/main-native/libs/arm64-v8a/libAnoy.so \
  --media "$MEDIA" --output .verification/main-native/media-verification.json
```

Use empty output directories for a clean build. Output is an Android API 21+
ARM64 native `libAnoy.so`, not an APK. Private packaging aliases those exact
bytes to the sole ZIP entry `libloader.so`. No live loader manifest is changed.

## CI and remaining device checks

The manual native-build workflow now requires public-source ASan/UBSan UI tests
and the packing check before native compilation. Public CI explicitly reports
that private media are not embedded. Its unstripped symbols remain private or
encrypted through the existing workflow. Local complete-media tests additionally
verify the genuine assets and routing. Results and the exact compiled source/hash
are recorded in `MAIN_INTEGRATION_BUILD_VERIFICATION.json` after verification.

Device checks still required: startup with the unchanged owner native revisions,
all theme transitions, real OpenSL speaker output, MediaCodec looping/pause/resume,
GL texture context recovery, launcher/menu dragging and mobile performance.
Keep the existing device-tested library for rollback. Main-source publication
does not change `Anilxkenny/kenny.json` or assert a production release is tested.
