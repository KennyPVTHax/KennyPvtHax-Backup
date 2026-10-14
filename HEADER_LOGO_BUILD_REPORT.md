# Verified menu-header logo build

The menu-header K icon now uses the same supplied cached photo as the floating
launcher. No audio, theme, asset, preference, gameplay binding, constructor,
native loading, input interception or renderer ownership changes.

Compiled source: `c2ed7e378aa8e84078db13fbdaa809eb7d811440`. Clean local NDK 25.2.9519653 ARM64 build, Android
API 21, original SDK and dependencies. All 16 ASan/UBSan suites pass; 37 original
binding/range/callback and startup source checks pass. Actual ImGui captures
verify header photo, navigation/drag/tap. All 16 embedded assets remain exact.
Header photo device display remains to be inspected; previous UI/audio success
is the owner's report.

Verified published baseline: Anilxkenny/main/media.zip, manifest version 0.8,
contains root libloader.so whose SHA-256 matches the prior 49e56a7 embedded build:
73843b8fcc29ac624d55f35c7d0fd126e255a85e7aa36f3d6cd4fc2879283340.
Main source meanwhile remains 6ef4ec6, with two different owner native files.

New library: 20650064 bytes. Build ID `293fc1db64b1c3843420b438cc46ea2bb2bc6707`.
Library SHA-256 `cacffe65534e8391b534ea11d8565198bd62ed1130f57f96f2b239480ab5b850`.
ZIP `KennyPvtHax-c2ed7e378aa8e84078db13fbdaa809eb7d811440-ARM64.zip`: 16474053 bytes.
ZIP SHA-256 `5609316b25241529d7facf86a4f2cea84af1d0b43e38e81222b5503734e88d1c`.
Only root libloader.so, byte-identical to compiled library; CRC/extraction passes.
Native module filename stays libAnoy.so.

**NOT PUBLISHED to Anilxkenny. Main has not been changed.**
Earlier new.txt explicitly forbids overwriting the manual bypass/Lua files.
An uncommitted normal merge review at /workspace/kenny-header-main-review keeps
both histories and exactly matches the tested fix, restoring the working blank
bypass and retained Lua. Source-choice question pending; no native revisions
silently overwritten or activated.

Earlier public-media rights, loader-comparator and configured publishing gates
remain unresolved; this task has not uploaded a binary or changed live JSON.
The live manifest was verified unchanged against THIS TASK's initial snapshot,
pointing to media.zip version 0.8 at f3cac944260a56ab32406424b9313ab2f8135425.
The previous task's historical snapshot was version 0.7; it was already outdated
at this task's start. No next version is guessed. No GitHub Actions embedded run:
actual native build performed locally.

Private downloads under /workspace/shared/downloads/kenny-header-logo-private/:
ZIP, libAnoy.so, HEADER_LOGO_BUILD_VERIFICATION.json, actual PNG previews,
before/after, offline viewer and preview bundle. Workspace phone access remains
unverified. Source fix pushed to release/embedded-media-integration; main/live
promotion pending. Prior binaries and all Git checkpoints preserved.
