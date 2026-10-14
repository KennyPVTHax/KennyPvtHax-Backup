# Embedded-media integration — final verification

**NOT PUBLISHED.** Private presentation build ready; device behavior remains unverified.

- Baseline: `739a2de1ed4710df39a23ac67bab3b680b1bd594` (runtime `1a944d4`); owner-working checkpoint `2a54a41`.
- Integration branch: `release/embedded-media-integration`.
- Compiled source: `49e56a7ea335bbf235284131f9c8bfb6cba2c98f`.
- Owner bypass/Lua evasion revisions were reviewed and deliberately not integrated. Blank working bypass and existing Lua were retained; their two hashes and requested hashes are in EMBEDDED_MEDIA_INTEGRATION.md.
- Startup/main/input/EGL/SDK, Aurora, electric Classic, existing Android video and audio engines are byte-identical to baseline.
- No foreground Rias cutout in default video mode. Circular logo fills launcher; static character artwork remains available when video is OFF.
- Prepared voices are unchanged; default supplied pack is internal. Saved available alternative-pack selection, mute, volume and cooldown remain.

## Build and package

- Genuine clean local Android NDK 25.2.9519653 build, original SDK/static dependencies; ELF64 AArch64, Android API 21, stripped native shared library (not APK).
- Build ID: `447da74019048de0f8e6ce60451e0eef6fcf437c`.
- libAnoy.so / internal libloader.so: **20,650,016 bytes**, SHA-256 `73843b8fcc29ac624d55f35c7d0fd126e255a85e7aa36f3d6cd4fc2879283340`.
- ZIP: `KennyPvtHax-49e56a7ea335bbf235284131f9c8bfb6cba2c98f-ARM64.zip`; **16,473,855 bytes**; SHA-256 `45bb0f8dae95e443d77dc07c010eb53630ad2b9997d1d63655af43413ae818bf`.
- ZIP CRC/extraction/root-only structure and exact compiled/extracted bytes PASS.
- Actual compiler dependency file confirms both retained source includes; Lua compiles once through main.cpp. Resource objects have no dynamic initializer; GNU stack is non-executable.
- Final library checked against all 16 resource payloads, including actual movie bytes. See FINAL_VERIFICATION.json for offsets/hashes/dependencies.
- No GitHub Actions run for this embedded build: local compilation avoided public distribution of private media. Previous 1a944d4 Actions build: https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38555323354

## Verification

- 16 ASan/UBSan suites PASS: menu, launcher, audio, theme, Aurora, effects, characters, media, diagnostics, fonts, continuation, electric, embedded, presentation, supplied, audio-recovery.
- Original 37 full configuration binding/range/callback fixture and startup source audit PASS.
- Embedded tests: four exact voice mappings, new/default and saved selection, mute/cooldown/theme isolation, memory PNG alpha, full circle geometry, lazy movie extraction, SHA cache reuse/corruption recovery, unwritable-storage fallback.
- Actual production ImGui capture tests: navigation, Settings toggle, existing drag/tap, 640 viewport, missing media, Reduced, feature state preserved. Linked private media used; host movie frames decoded by FFmpeg.
- Supplied logo RGB crop byte-for-byte preserved; prepared WAVs byte-for-byte preserved; original OGG files retained in the original private bundle.
- Introduced-content token/private-key scan PASS; no media or generated resource objects committed.
- Preliminary native build exposed same-basename resource object collision. Fixed with resources.cpp + payload.S; final build was clean and succeeded.

## Embedded inventory

| ID | Bytes | SHA-256 |
|---|---:|---|
| assets/anime/highschool_dxd_rias/character.png | 962077 | `8eeb6a3d13df41496823ec73773b59ecd13c6be58842cfe69f29b4db1222afc5` |
| assets/anime/highschool_dxd_rias/manifest.json | 3276 | `e9fe9b1a0addae7801c98571a35504c8ad146ca623928b0040355497ff2da0b6` |
| assets/anime/highschool_dxd_rias/voice/cici_hello.wav | 88718 | `de79185672eb973c67329bb42a24d7837d7a200ddc9030b22bc6748090530a5b` |
| assets/anime/highschool_dxd_rias/voice/cici_no_problem.wav | 99802 | `9a596c74ba05cc5844f1dbd430f5eb2885f2c3c4fb2c9ab453fac6610a94dee8` |
| assets/anime/highschool_dxd_rias/voice/cici_okay_happy.wav | 105960 | `fa05db02a1a82164f7c19a3e91f123e24fb9f52776a55b247aadcbe82adc0763` |
| assets/anime/highschool_dxd_rias/voice/cici_okay_normal.wav | 89950 | `8d90600aa3b8738616ff85669b2dd15cf9c35a37d0ef2624c53fe46287c88def` |
| assets/anime/highschool_dxd_rias/voice/cici_see_you_later.wav | 126896 | `16024ba571bb78b86230594aca317f52c4f819f59397ca82eb42970cf26aaabf` |
| assets/anime/highschool_dxd_rias/voice/user_aim.wav | 127226 | `c9965463ca327d4bbaf17ee9d83d2aff8e9bae04a76fa0b341780cda3043be32` |
| assets/anime/highschool_dxd_rias/voice/user_aimoff.wav | 329932 | `4df9d00684e7404180728c02b39a3159e0ed9c2ce0e8f75c04d5524024d2e177` |
| assets/anime/highschool_dxd_rias/voice/user_bullet.wav | 59208 | `3b53db65cecfca85c0a2ae528fffa346cc631496b25f569054a6dbcbca75dc7c` |
| assets/anime/highschool_dxd_rias/voice/user_extrafeatures.wav | 195160 | `90b3b366a5a79a95437a1e092677b27baa1989b68266a38ce07c4a9e62694205` |
| assets/anime/index.json | 50 | `ade2f265477efd8096bb0ad7f27d96da46bb1af4e02dd2f40df1eaa0989a6f5e` |
| assets/presentation/anime-background.mp4 | 10113470 | `9522dacd41adaf6ba5e33c1abc5347735d1ee969b6e3e1711b6b508b9eeacc60` |
| assets/presentation/anime-fallback.png | 389742 | `1e408f055d0e6408d18ba99b870743dc5fb3a7b62fe263971e7da7fa836f465e` |
| assets/presentation/launcher.png | 1188051 | `619524aab390dd3fa47a23817700888697b565d13f94ceee94bec03c6cdede6b` |
| assets/presentation/manifest.json | 115 | `f91f074e5f2b9772790fded86a7e614438d4c77db8cc9e60f13743e87781f45b` |

Original voice mapping: bullet.ogg -> Bullet ON; aim.ogg -> Aim ON; aimoff.ogg -> Aim OFF; extrafeatures.ogg -> open Extra features. No Bullet OFF clip or fabricated recording.

## Deployment gates / rollback

- Anilxkenny checked PUBLIC, main, authenticated CLI write access. Normal CLI access does not verify ANILXKENNY_PUBLISH_TOKEN.
- Inspected destination commit: `49acabca47ef7e6df645520a496609b5930579ea`.
- Existing live manifest remains `bypass.zip`, `drm_verion="0.7"`. No new destination commit, version or raw download URL exists for this build.
- Reference test2.zip verified sole root libloader.so, SHA-256 `298238ef0deade50970f3b14be2ecbe9df5ffb5cfa725d07fb0b794f4b19c2d1`.
- Public redistribution rights for supplied video/artwork/logo/recordings remain unverified; embedding makes those assets extractable.
- Loader comparator source is unavailable; no next-version scheme guessed. Secret API access is denied (403). Source exposes only manual build-native.yml; prepared release contract/device gates remain unresolved.
- Publishing workflow was not bypassed or enabled with unverified inputs. New embedded build is not promoted to release/android or main.
- Rollback: previous verified 1a944d4 library/ZIP retained unchanged in shared/downloads. Since this task has not deployed, current production requires no rollback. Future authorized manifest rollback restores only the saved drm/drm_name/drm_verion tuple atomically and retains ZIP history.

## First Android test

1. Use this exact private ZIP through the existing authorized loader; do not also install unrelated manual-revision binaries.
2. Start without an external private media pack. Verify actual circular logo opens/drags/closes as before.
3. Select Anime and Rias / supplied event clips; ensure UI sounds/character/control feedback enabled and both volumes nonzero.
4. Use Test Voice and inspect queued/engine/file diagnostics; verify audible output. Test Aim ON/OFF, Bullet ON and Extra navigation exactly once.
5. Open Anime: automatic cache -> actual video; test first-frame fallback, looping, hide/resume, Reduced, video OFF, context/lifecycle recovery.
6. Verify Classic Electric and Aurora, all controls/scrolling and preference restart. Observe actual device frame pacing and memory; no FPS claim is made here.
7. Do not promote until device evidence and all media/release permissions are established.

## Private downloads

ZIP, libAnoy.so, FINAL_VERIFICATION.json, EMBEDDED_ASSET_INVENTORY.json, before-after.png, native PNG previews, offline viewer and preview bundle are under `/workspace/shared/downloads/kenny-embedded-media-private/`.
No supported generic private artifact-upload tool is available in this session; workspace links are provided, but Android browser retrieval cannot be verified here. If downloads fail, export needs an explicitly authorized private destination; this binary must not be uploaded to the public loader repo as a workaround.

Source changes are enumerated in CODEX_PROGRESS.md and EMBEDDED_MEDIA_INTEGRATION.md. No further UI stages or production publishing were started.
