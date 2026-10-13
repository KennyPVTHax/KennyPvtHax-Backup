# Automated loader deployment

Source: KennyPVTHax/KennyPvtHax-Backup, production ref release/android.
Destination: KennyPVTHax/Anilxkenny, branch main, manifest kenny.json.
Pipeline preparation branch: ci/loader-publish. No live manifest change is part
of the initial dry-run. Source native code/SDK/build flags remain unchanged.

## Verified loader package contract

Retrieved original test2.zip from the destination repository. CRC passes;
SHA256 298238ef0deade50970f3b14be2ecbe9df5ffb5cfa725d07fb0b794f4b19c2d1.
Its sole entry is root **libloader.so** (case-sensitive). New packages contain
exactly that entry. Source output/module remains libs/arm64-v8a/libAnoy.so/Anoy.
Only the packaged copy is renamed. Package filenames use the complete 40-character
source commit: kph-<commit>-arm64.zip. Existing archives never overwrite.

## Current deployment gates — not a claim of production activation

1. Loader comparison code is unavailable. Both repositories lack the implementation
   that reads drm_verion; ZIP entry names do not establish version semantics.
   Current manifest string is 0.2. tools/loader_contract.json deliberately has an
   UNVERIFIED/unconfigured policy. A decimal-step implementation is available
   and tested as a candidate only; it must not be selected without loader evidence.
2. Recovery Stage 1 is awaiting the owner's device result. Do not promote this
   untested milestone merely because CI/native compile passes.
3. Listing source Action secrets returned HTTP 403, so this integration cannot
   verify whether ANILXKENNY_PUBLISH_TOKEN exists. No token is requested in chat.

The push release/android trigger is implemented, but publication fails closed
until compatibility/device gates are explicitly established. The dedicated
ci/loader-publish push is always a test/build/package-only dry-run. main, other
branches, forks and pull requests cannot publish. Production publish is also
blocked unless event/repository/ref match inside the publisher itself.
No release/android branch is created/promoted by this task.

## One-time setup after evidence is available

Inspect actual loader source: record the file/revision/expression comparing
versions and whether downgrade rollback is honored. Confirm a supported monotonic
scheme (numeric decimal comparison can use decimal-step; string/semver comparison
may require another tested policy). Do not infer comparison from 0.2 alone.
Set verified/scheme/step/evidence only after confirmation and corresponding tests.
Mark initial_device_milestone_approved only after the user verifies recovery.
These are one-time setup gates, not approval prompts after each successful build.

Create a fine-grained PAT selecting **only Anilxkenny**: Contents read/write and
Metadata read, with bounded expiry. Add it to the SOURCE repository's Actions
secrets as ANILXKENNY_PUBLISH_TOKEN. Do not put the token in Git, URLs, artifacts,
logs or chat. If organization rules require authorization, approve the token there.
Build/test/package jobs receive no destination token. Only the guarded publishing
step does. Destination Git uses temporary GIT_ASKPASS, clears other token/helper
sources and captures Git errors without credential output.

Protect release/android before enabling publication: require reviewed PRs, restrict
updates to release maintainers, forbid force pushes/deletion, require relevant CI
checks, and retain administrative enforcement where appropriate. Use the actual
repository settings/ruleset UI; this task does not claim an unconfigured protection
rule exists. Device-tested promotion is a maintainer decision, never a CI inference.
The publisher also requires GitHub to report release/android as protected; a
missing protection stops production even if the compatibility gates are edited.
No per-deployment environment approval is needed after a tested milestone is merged.
If only one maintainer exists, select an owner-controlled promotion policy suitable
for that account instead of inventing an unavailable second approver.

After confirming gates and protection, promote the pipeline and **device-tested**
source milestone to release/android. Do not automatically merge the preparation
branch into main/release/android. Subsequent successful release branch pushes
execute test → build → package → publish without manual ZIP or manifest editing.

## Workflow and atomic publication

.github/workflows/build-and-publish-loader.yml uses separate dependent jobs,
immutable action references and existing NDK 25.2.9519653/arm64-v8a configuration.
Tests include original-source preservation/37 bindings, UI sanitizers and offline
publisher regression. Build verifies real ELF; packaging compares extracted SO
bytes against native output, exact entry list, CRC and SHA256.

Production publication and rollback share a concurrency group with
cancel-in-progress:false. Older runs are rejected if release/android no longer
matches their source SHA. The source head is checked before each reconciliation
and immediately before push. Cross-repository refs cannot form a distributed atomic
transaction; serialization prevents an old job overwriting a newer publication,
and the final source-head check narrows the promotion race. Source updates after
that check can briefly leave the previous valid release until their newer run ends.

The token clones only destination main. Exactly ZIP + kenny.json are staged in
one commit. No source/SDK/media/symbols enter that repository. Match the target
by package com.pubg.imobile, preserve drm_verion spelling, and change only its
three requested fields semantically. Full-commit ZIP filenames are immutable.
No force push: up to five fetch/reset/recalculate attempts reconcile destination
advancement. Reset affects only a disposable publication checkout. Previous ZIPs
are retained. Retry of an already-active tool-created release is idempotent; original compile
timestamps can change rebuilt bytes, so the already-published verified archive
is retained and both rebuilt and installed hashes are reported; replay
of a historical ZIP after rollback is refused. Verification checks destination
ancestry, committed JSON fields and exact committed archive bytes/hash/ELF.

Raw manifest URL remains branch/main compatible. Verification uses the destination
commit URL to avoid cache ambiguity; any later independent manual edit can change
live main and is outside a single publication's transaction.

## Dry-run

Push ci/loader-publish to run the initial isolated dry-run. The publish job is
skipped. Once the workflow is installed on the repository's default branch for
GitHub workflow_dispatch registration, dispatch with dry_run:true for recovery;
workflow_dispatch never grants unrelated branches publication rights.
Output artifact loader-package-<sourceSHA> contains verified ZIP and release.json.
Summary records source SHA/run/NDK/library digest/internal name/ZIP digest. A
successful production summary additionally records destination commit, manifest
version/raw URL and result. No private symbols or device crash reports upload.

Local unit regression:

    python3 tests/loader_release_check.py

Local packaging (genuine compiled library only):

    python3 tools/loader_release.py package --binary libs/arm64-v8a/libAnoy.so \
      --commit FULL_SOURCE_SHA --run ACTIONS_RUN_ID --bundle deployment

Tests use clearly labeled ELF format fixtures and an actual local bare Git remote;
they do not represent Android runtime testing or live destination publication.

## Manual rollback and cache behavior

Select workflow_dispatch on release/android with dry_run:false and the full
previous DESTINATION commit in rollback_destination_commit. Same production gates,
token and concurrency group apply. Previous manifest/archive are verified in Git
history and current archive bytes must match. Only drm/drm_name/drm_verion are
restored; unrelated current manifest fields survive. No archive is deleted.

IMPORTANT: if the loader accepts only greater versions, a lower restored version
may not trigger a client download. That behavior must be established from loader
source before production activation. Do not claim server rollback guarantees
client rollback, clear arbitrary app data, or add loading bypasses. Adapt the
rollback policy only after confirmed comparison/cache behavior and device tests.

## Failure recovery and token rotation

Failed mandatory jobs never publish. Missing/expired/insufficient token, unverified
policy, stale source SHA, manifest ambiguity, ZIP collision or failed integrity
checks stop publication. Failed push retries reconcile from the remote head.
A process ending before push leaves live destination untouched; a process ending
after a successful atomic push may be rerun to verify/idempotently report success.
Publication verification failure must be investigated using destination commit and
artifact checksums, not by force-pushing or replacing an existing ZIP.

Rotate by creating a new minimal fine-grained PAT, replacing the same source
secret, testing controlled dispatch and revoking the old token after success.
A missing secret cannot be created from an unknown token; the owner supplies it
through GitHub settings. Device crashes remain a separate Android issue: revert
through the verified rollback mechanism and retain previous ZIPs/checksums.

Release ruleset read access succeeded, but creating the requested source branch
protections returned HTTP 403 (Resource not accessible by integration). No rule
was applied; repository administrator setup remains required.

For the candidate numeric policy, later releases advance beyond the highest
tool-recorded manifest version in destination commit subjects, not just the live
manifest after rollback. Legacy version high-water values must be reviewed when
confirming the initial policy. History inspection is bounded and fails closed
at its migration limit; no extra manifest fields or destination ledger are added.
