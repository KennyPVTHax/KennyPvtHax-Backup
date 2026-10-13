PROJECT: KennyPvtHax

CURRENT STAGE:
Original-based recovery Stage 1 — UI-only build preparation.
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
Source identity gates pass. Host sanitizer and genuine native Actions results will
be recorded after completion. No Android runtime success or crash cause claimed.

NEXT ACTION:
Deliver exact Stage 1 libAnoy.so, source commit/checksum, then STOP for user device
result. No main merge and no Stage 2 until Stage 1 compatibility is confirmed.
