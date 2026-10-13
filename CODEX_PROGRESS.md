PROJECT: KennyPvtHax
CURRENT TASK: Isolated cross-repository loader release pipeline preparation.
BRANCH: ci/loader-publish; original Stage 1 native code unchanged.
COMPLETED: reference ZIP root libloader.so confirmed; immutable packaging, four
CI jobs, guarded token-only destination Git publication, atomic two-file commit,
source-head checks/concurrency/retries/idempotency, rollback and offline tests.
PENDING: genuine CI dry-run; loader version-comparison source; initial device
milestone approval; source secret access/configuration and release protection.
LIVE DESTINATION: kenny.json/test2.zip unchanged; no release branch promotion.
NEXT: finish dry-run and report prerequisites; never publish unverified policy.
---

PROJECT: KennyPvtHax

CURRENT STAGE:
Original-based recovery Stage 1 — built and verified; awaiting user Android test.
Branch: recovery/ui-only-stage1. Golden original checkpoint b73a33a/anony.zip.
User has already verified original startup/menu on Android; no original retest.

COMPLETED:
- Recovered and byte-verified 947 original files and genuine 2391-file SDK.
- Compared all original paths against modified main a4d7eea; seven paths differ.
- Original constructor/worker/hooks/input/EGL/ImGui/fonts/backends/toggle restored.
- Destructive FixGameCrash body intentionally stays disabled.
- Static crimson modern horizontal menu and KennyPvtHax display branding only.
- All 37 original bindings/ranges/conditions and Guest Reset callback retained.
- Optional audio/Aurora/Anime/persistence/new launcher absent, not merely muted.

MODIFIED APPLICATION FILES RELATIVE TO ORIGINAL:
jni/main.cpp (UI wrapper + one include + destructive routine no-op);
jni/ClaudeTheme.h (crimson static style); jni/KennyMenu.h (presentation only, new);
jni/Helper/definition.h and jni/Lua_Buffer.cpp (visible branding strings only).
Original dependencies/SDK are recovered unchanged, including build/backend files.

VERIFICATION:
PASS golden-source gates and local/CI ASan/UBSan UI host checks.
PASS native ARM64 build using unchanged NDK 25.2.9519653 (r25c).
Source commit 3ce538cdedb9422f608b23d5cee2b814878418a1.
Actions run 38362303903; artifact 11794839657.
Downloaded ZIP CRC/two entries/digest and actual ARM64 ELF verified; no OpenSLES
DT_NEEDED entry. libAnoy.so is 6565888 bytes.
SHA256 43de845910a452dfadb83865cd34189b7015088e8b324aeb674518e0c8efd165.
BuildID 264bcffa247ce6d25382373306ba62aadbb7dfe6.
Actual host draw-list previews inspected at previews/recovery-stage1/ (ignored).
No Android runtime success or crash cause claimed; original retest not requested.

NEXT ACTION:
Deliver exact Stage 1 libAnoy.so, source commit/checksum, then STOP for user device
result. No main merge and no Stage 2 until Stage 1 compatibility is confirmed.
