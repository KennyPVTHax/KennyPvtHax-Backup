# Full UI main integration build report

Compiled source: `70fe24fbf99e117659c06f825d981ac435103892`.
Initial remote main: `812315b89d88ecb59e253554793fb3a73bd34e08`.
Confirmed embedded baseline: `49e56a7ea335bbf235284131f9c8bfb6cba2c98f`.
Rollback tag: `backup/main-before-full-ui-verification-20261014`.

Subsequent commits record these results and correct CI history checkout for
historical regression fixtures; application/native source and private build
configuration remain identical to the compiled source commit.

Clean native compilation/linking: **PASS**, NDK 25.2.9519653, arm64-v8a, API 21+,
module Anoy. Output `libs/arm64-v8a/libAnoy.so` (21,081,312 bytes).
Library SHA-256: `283d225e36763c6bb5d2a8a4e8661920f2e5d8d9aa1ba6ff1ff05dd5c8deeb7b`.
ELF Build ID: `779c220555b31becb98aafd8389d89dac9635f0c`.
All 16 genuine embedded resources match input size/SHA-256 and actual ELF bytes.

Private package: `KennyPvtHax-70fe24fbf99e117659c06f825d981ac435103892-ARM64.zip`.
ZIP SHA-256: `ab47206ced95d789e77ee1c52d7014a7e0972714183288ac1312597cffb671a5`.
Size: 16,553,615 bytes. Sole root entry `libloader.so`;
CRC/extraction/byte equality with native output: **PASS**.
Private artifact directory: `/workspace/shared/downloads/kenny-main-integration-private/`.
Symbols remain private under the isolated native build output; no public upload.

Host checks: all 16 ASan/UBSan suites PASS, original 37 binding/range/callback
fixture PASS, startup main source audit PASS, actual presentation packing and
incoming-mode restoration PASS. Cases were rebuilt against unchanged, previously
verified bundled ImGui sanitizer objects; native output was compiled from an
empty isolated output tree, not reused. 40 original static libraries and 2,391
original SDK files are present. Owner native-file hashes remain exact.
Limited credential/private-key pattern scan and diff whitespace check PASS.

Main's owner-native revisions differ from the device-tested 49e56a7 library.
They are retained as requested, neither modified nor extended here. Host tests
and successful compilation do not prove their runtime compatibility. Android
startup, OpenSL audio, MediaCodec/GPU, real touch and performance need device tests.

Public source includes integration tools/manifests and five existing CC0 clips;
private supplied media are not added to Git or public artifacts. Public Actions
builds the source with safe external-media fallbacks, not this embedded binary.
No live loader JSON/release changes. See MAIN_INTEGRATION.md for reproduction.

## Public CI verification

[Run 38583806540](https://github.com/KennyPVTHax/KennyPvtHax-Backup/actions/runs/38583806540) **SUCCESS** for source
`4959326190a270d9b75f6968abfacd31a3a0f9e5`: 12 public-source ASan/UBSan suites and native ARM64 build.
The initial shallow-checkout failure was corrected by fetching preserved history.
Downloaded artifact 11904209193 matches its GitHub SHA-256 digest; ZIP CRC
and actual ELF/source ID verified. Public library SHA-256: `07c09f43146c790bf4d23b4b21f54b57baddf6db0555e43e07c2b053be437c2d`.
This 7,195,376-byte public binary does not contain the supplied private media,
verified against the actual movie/logo/artwork/user WAV payloads. Use the private
embedded artifact above to test the full media experience. Android device testing
is still required. No live Anilxkenny changes.
