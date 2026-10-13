# Audio recovery — Checkpoint A

## Confirmed evidence

The owner confirms the 2a54a41 full UI runs but **only the .so was installed**.
The supplied private media pack was not installed. That library does not embed the
recordings: the required WAV files and character manifest are therefore absent
from its Android runtime unless independently supplied by the host. This explains
the missing supplied dialogue; it does not prove Android OpenSL or speaker delivery.

Before edits, checked-out 5261a1e application/asset/build bytes matched compiled
2a54a41. Downloaded reference libAnoy.so SHA-256:
e2fc6995a2741cd51f385c5b54a420eb168c0b6c51ffa1c0bbb9ab6787ca2b3f.
No phone binary/logs/ADB endpoint was available for an independent on-device digest
or filesystem check. The exact reference comes from the user's working-build report.

The actual Android host/installer source is not in this repository. Bundled ImGui
example Activity source is third-party demonstration code, not the host. No fake
import button, guessed private path, new permission, hook or startup change is added.

## Diagnostic test and interpretation

Existing Anime Settings now provides a selectable configured event and **Test Voice**.
It directly tries the selected character/pack/event recording. It never edits an
original feature or plays a generic button tone that could disguise a missing voice.

Results distinguish missing engine, disabled UI/character audio, zero UI/voice
volume, wrong theme/character/pack, missing/corrupt recording, queue-full, cooldown
and accepted recording. A cooldown is explicitly unsuccessful for the new test.
A queued recording is **not reported as audible**. Subsequent mixer-start and new
OpenSL callback counters are used only as transport evidence. Speaker playback
still requires listening on the phone.

Select Anime → Settings → Rias → **Rias / supplied event clips**, enable UI sounds,
character voice and control voice feedback, with nonzero UI/voice volume. Test each
of aim_enabled, aim_disabled, bullet_track_enabled, extra_features_navigation.
Then test actual feature transitions; no settings changes are made by Test Voice.
Check Android MEDIA volume/output device too; this code does not hijack audio focus,
change the game's sound resources or override device routing/mute.

## Diagnostics

Events retain the existing KennyPvtHax logcat tag and persistent KPH-040 records:
AUDIO_ENGINE_INITIALIZED/FAILED; MEDIA_DIRECTORY_FOUND/MISSING;
CHARACTER_MANIFEST_LOADED/FAILED; VOICE_PACK_SELECTED; VOICE_FILE_LOADED/MISSING;
VOICE_DECODE_FAILED; VOICE_EVENT_RECEIVED/SUPPRESSED/UNMAPPED; VOICE_SUBMITTED;
AUDIO_QUEUE_FAILED; PLAYBACK_STARTED/FAILED; AUDIO_CALLBACK_OBSERVED.

Suppression reasons identify disabled sounds/voice/control feedback, zero volumes,
wrong theme/character/pack, missing clip, cooldown or unavailable engine. Only
relative event identities and registered pack IDs are reported, never private paths,
credentials, memory addresses or other personal files. Diagnostics are bounded to
96 audio records per thread/30 seconds and the existing 64KiB private report limit.
Passive rendering does not emit events or write diagnostic files.

The real-time OpenSL callback updates atomic counters/failure flags only. It never
logs, writes files, allocates or takes logger locks. The render owner drains only
one callback-observed edge per playback burst and any failure edge. Failed callback
enqueue, queue clear and SetPlayState errors are now reported and fail optional
audio gracefully; these errors had no adequate transport evidence previously.
Engine creation order/resources, native startup/main.cpp/input/EGL/SDK and the
intentionally blank Helper/bypass.h remain unchanged. No speakers test is inferred
from host PCM or ARM64 compilation.

## Install the private package without path guessing

The new private package contains an INSTALLATION_INDEX.json with SHA-256 and size
for **all 12 runtime files**: four supplied WAVs, five unchanged approved alternative
WAVs, character PNG, character manifest and Anime index. Original OGG/JPEG files
are preserved separately; conversions/cutout are reused unchanged, not redone.
The package and user media are not published in GitHub or the loader ZIP.

The host integrator must perform the following in the **NativeActivity's owning
process**, using that activity's `internalDataPath` (the framework NativeActivity
uses its own files directory). A separate loader app's private directory is not
a substitute for the game's/native activity's directory.

1. Use an authorized SAF document picker/local package input in the real host.
   Open the selected ZIP stream without broad storage permission or network download.
2. Compare the whole ZIP SHA-256 to the delivered checkpoint manifest. Validate
   bounded entry counts/sizes, reject duplicate/absolute/traversing/symlink paths,
   validate the package schema and each indexed file's length/hash. Check PCM WAV
   limits and PNG dimensions/alpha. Stage only indexed runtime files; do not install
   originals or accept unindexed runtime entries.
3. Create a private 0700 staging directory on the same filesystem as the activity's
   `assets/anime/`. Write 0600 files, fsync and validate all required supplied mappings.
   Preserve appearance settings and other character directories.
4. Back up only the old highschool_dxd_rias directory to a private dot-prefixed
   backup. Rename the complete verified new directory into place; rollback the backup
   if the final rename fails. Sync directory metadata. Never delete existing evidence
   or clear application data. Interrupted staging must not become an installed pack.
5. Final runtime paths are `ACTIVITY.internalDataPath/assets/anime/highschool_dxd_rias/`
   with manifest.json, character.png and voice/user_*.wav. Report installed hashes/
   counts from the host. The existing StageAPK path intentionally preserves old
   manifests, so bundling a new APK alone does not replace an outdated private pack.
6. Restart the owning application after committing the pack. The registry caches
   immutable recordings once; hot reload is deliberately not added while callbacks
   may hold clip pointers. On restart, the new diagnostics confirm path access,
   manifest validation, each decode, selected pack and OpenSL status.

This is the exact integration contract, not a claim that an unavailable host has
been modified or that files were installed on the phone. Supply the real host/
installer source to implement the SAF import action there. For a debuggable host,
authorized `adb run-as` may instead stream validated files to the exact directory;
if run-as is denied, do not bypass Android storage controls or guess another path.

Offline validation/reproduction (Pillow installed on the host, no new Android dependency):

```sh
python3 tools/validate_private_media_package.py KennyPvtHax-Audio-Recovery-Private-Media.zip --stage verified-staging
```

The native .so diagnostic archive is separate and contains **libloader.so at root**;
it remains byte-identical to the built libAnoy.so. This is only a deployment alias,
not a renamed NDK module or changed loading interface. No Anilxkenny publication.

## Collect on-device evidence

```sh
adb logcat -v threadtime -s KennyPvtHax > kph-audio-checkpoint-a.log
```

Start capture before launch. The existing private report remains at:
`ACTIVITY.internalDataPath/KennyPvtHax/CrashReports/startup-report.txt`.
Retrieve through the authorized host diagnostics export or debuggable run-as as
already documented in KENNY_ANDROID_CRASH_DIAGNOSTICS.md; Documents export still
requires the actual host's SAF/MediaStore implementation. Sharing is opt-in.

Interpretation:
- MEDIA_DIRECTORY_MISSING / missing user files: import package into the owning
  activity, restart, and select supplied pack.
- ENGINE_FAILED: record the exact OpenSL stage/result; do not assume assets caused it.
- RECEIVED then SUPPRESSED/UNMAPPED: correct the explicitly reported preference,
  pack/file or cooldown condition.
- SUBMITTED without PLAYBACK_STARTED: investigate enqueue/player failure logs.
- PLAYBACK_STARTED without CALLBACK_OBSERVED: capture Android audio service errors.
- New recording mixed and callbacks observed but silent: verify media volume/output
  routing and device audio service evidence. It remains a speaker/output diagnosis.

## Later checkpoints — not implemented in A

The supplied logo is actually a 1280×1280 RGB JPEG, not an alpha PNG. The Rias JPEG
is byte-identical to the previous source; the authorized existing cutout is reused.
No logo replacement or internal menu redesign is performed in this checkpoint.

animebg.zip is invalid: 1,216,572 actual bytes, but its videoplayback.webm entry
declares 21,136,156 uncompressed / 21,139,378 compressed bytes and fails ZIP integrity.
No complete valid video can be established; codec/resolution/duration/playback are
unverified. Preserve the original and provide the complete video/archive for B.
No static image or generated frame sequence is substituted for video playback.

After A passes the owner's device test, B can audit MediaCodec/host-decoded-frame
integration on the existing EGL owner, bounded asynchronous buffers, muted video,
loop/pause/context loss and a still fallback. C then integrates the actual logo
through the existing launcher, handling its real format/alpha. Neither stage starts
before the required verification; no production release or kenny.json change.
