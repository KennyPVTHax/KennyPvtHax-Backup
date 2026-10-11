# Complete private source export

Application HEAD: `3436f472ad222590392875ac9b3588c61285dd51`.
Every tracked application source file matches HEAD byte-for-byte. Required original untracked sources, Helper/Login.h, third-party headers/sources/fonts and all 40 original static libraries are included.
Export-only documentation additions: ANDROID_BUILD_INSTRUCTIONS.md and the export section in CODEX_PROGRESS.md. Git HEAD/history is unchanged.
Original jni/SDK/ is intentionally absent; restore it before native compilation. No APK project has been invented. See ANDROID_BUILD_INSTRUCTIONS.md.
Private runtime recordings and references are in the separate media archive. Extract both archives to the same parent.
export_support contains only genuine host test source fixtures, not SDK stubs or native build dependencies. No compiled test outputs/caches are included.
Existing third-party notices are preserved. Inclusion for your existing private project is not a new blanket license or authorization to publish third-party code/assets.
