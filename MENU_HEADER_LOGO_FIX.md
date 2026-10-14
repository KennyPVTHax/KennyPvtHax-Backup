# Menu header photo logo

User reports that the previously delivered full UI/audio work on Android. This
fix starts from d37eb87 / compiled runtime 49e56a7 and changes only presentation.
The menu header previously called its own K emblem. It now borrows the same
cached supplied circular photo texture as the launcher. No new decoder, texture
owner, upload, asset, preference, startup initialization or input mechanism.

`KennyIdentity::Photo` shares the existing fixed circular image geometry between
header and launcher. Header wordmark, scale, spacing, dragging hitbox and close
control are unchanged. K is only a missing/disabled-media fallback. The menu
reference is reset with existing context-loss cleanup, before texture clearing.
Audio resources, event mappings, controls, movie, themes and SDK remain unchanged.

Verification: all 16 existing ASan/UBSan suites pass; original 37 binding/range/
callback fixture and startup audit pass. Actual embedded-resource header test
checks the photo draw command, bounded geometry, texture-stack restoration and
missing-photo fallback. Real ImGui capture uses actual supplied media and passes
existing navigation/drag/tap/visibility tests. Native build metadata and private
ZIP hashes are recorded in the final HEADER_LOGO_BUILD_VERIFICATION.json.
Host movie previews use FFmpeg-decoded actual frames, not Android GPU evidence.

Main promotion is not a simple fast-forward: source main is 6ef4ec6, containing
two owner changes to Helper/bypass.h and Lua_Buffer.cpp absent from the tested
source. A normal merge would pull in their extra startup/patch/suppression code.
Restoring the tested source would overwrite those two revisions. The earlier
new.txt explicitly says not to overwrite the manually pushed files. A concrete
promotion review can preserve all history and restore exactly those two files,
but that conflict must be resolved before altering main. Neither revision is
silently integrated or overwritten.

Production publishing also retains the earlier explicit new.txt gate requiring
verified public-media redistribution rights and the configured release workflow.
Anilxkenny is public; supplied assets in the .so remain extractable. Rights and
loader comparator are unverified; the publishing secret could not be inspected.
No token values are read/printed. No live JSON changes or public binary uploads.
