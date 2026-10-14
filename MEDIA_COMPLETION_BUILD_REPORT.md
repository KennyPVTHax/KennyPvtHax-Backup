# Committed-media build verification

Clean local ARM64 source: `3e2467ba925eeb17c8438b65379a981215be6529`. NDK 25.2.9519653, API21+,
module Anoy, default committed-media generation (no KPH_MEDIA_DIR override).
Library bytes: 21,085,184; SHA-256 `7eee9c108d44ed59621f8e95fff33de78af06a3114ee35535b41dc794685ec9f`.
ELF Build ID: `6093514ea318d0e373a6dbd1b2d449b0fe50b054`. All 16 actual payloads/size/SHA-256 PASS.
No private ZIP/original-image paths are required to rebuild from the public clone.

All 16 ASan/UBSan suites PASS, 37 binding/range/startup/packing checks PASS, and
relocated generator/idempotence/missing/corrupt/symlink/traversal tests PASS.
Legacy partial-media and continuation tests explicitly select their own genuine
CC0 fixture/pack, independent of production ordering; runtime code is unchanged.
Empty media-variable override verified with the real NDK to preserve full embedding.

First CI full-library compilation passed, but report output failed because the
parent directory did not exist in the clean build job. The host verifier now
creates that directory; fresh-output local verification PASS. Final CI result
and downloaded artifact verification are recorded after the corrected run.

All 16 resources are committed; inventory and specific authorization are in
assets/embedded-media-inventory.json and assets/PUBLIC_MEDIA_AUTHORIZATION.md.
Payloads match the genuine reference build exactly; no reconversion or substitutes.
Authorization basis: owner explicitly asserts ownership and grants public
redistribution of supplied files; CiciFyre clips independently recorded CC0.
Actor/creator authenticity and rights-holder ownership are not independently
certified by these engineering checks.

Both manual native files and all UI/render/audio/video/input source remain
unchanged; only Android.mk build input generation changes. Device startup,
GPU/video/speaker/touch/performance still need Android evidence. No live loader
manifest or production archive is changed.

Verified local loader ZIP: `KennyPvtHax-3e2467ba925eeb17c8438b65379a981215be6529-ARM64.zip`; sole root libloader.so;
CRC/extraction/actual binary equality PASS. ZIP SHA-256:
`a56d8f99027497ce04a0dede39c7750e95e7fd98bdb765acf7c9b244bc73ea31`.

## Final complete-media CI result

SUCCESS: https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38589369556
Source: `6a253620f4e0441570543f166ae2eebba63ebefa`. All 16 host sanitizer suites
and native ARM64 compilation/payload verification PASS. Artifact 11908000598
downloaded through the authenticated GitHub integration; SHA-256 matches GitHub
digest, ZIP CRC/source metadata PASS, inventory matches repository, and every
resource's actual ELF bytes and offset match its source payload. No private
workspace/media bundle or runtime installation was used by the fresh CI checkout.

CI library: 21,087,152 bytes; SHA-256 `74bbe3aac7f9452c358e5211fbf46c1117d29d68246577586f1879829bc04c9b`.
CI artifact SHA-256: `7ed2751a58fad8667f7a857c5b42f0c9ec9e1b2599729e8919539292e98be9a7`.
This is the complete-media binary, not the earlier smaller fallback-only build.
Subsequent documentation commits do not change build/runtime/media source.
