# Reproducible host performance baseline

Baseline application: a4d7eea/c975a6d. After: audit branch b14eb6b.
Optimized g++ C++17 -O2, x86_64 Linux, actual production ImGui/menu/launcher,
embedded fonts and original panel code; fixture bookkeeping removed solely from
benchmark. 1920×872, 120 warm-up + 600 sampled frames per mode/rate. No sleeps,
GPU submission or vsync: Hz sets simulation delta, **not measured device FPS**.
Shared executor scheduling/parallel compilation affects these timings. Single
runs establish a baseline, not statistical speedup or mobile performance proof.

No Aurora formula, particle count, shader/geometry quality, approved layout or
three-theme rendering was changed. The audit applies reliability fixes rather
than claiming a rendering optimization unsupported by Android profiling.

## CPU/draw baseline versus after (milliseconds)

| Mode | Hz | Before mean / p95 / max | After mean / p95 / max | Vertices / indices | Draw commands | New ImGui allocations (600 frames, before/after) |
|---|---:|---|---|---|---:|---|
| aurora | 30 | 0.4909 / 0.6299 / 5.2021 | 0.5253 / 0.7106 / 4.8415 | 10175 / 47688 | 3 | 0 / 0 |
| aurora | 60 | 0.5009 / 0.6673 / 1.7032 | 0.5056 / 0.6993 / 2.9478 | 10175 / 47688 | 3 | 0 / 0 |
| aurora | 90 | 0.4938 / 0.6711 / 2.5070 | 0.5004 / 0.7391 / 2.6275 | 10175 / 47688 | 3 | 0 / 0 |
| aurora | 120 | 0.4686 / 0.6202 / 3.5174 | 0.4603 / 0.6079 / 1.1478 | 10175 / 47688 | 3 | 0 / 0 |
| classic | 30 | 0.0355 / 0.0463 / 0.1578 | 0.0403 / 0.0840 / 0.2575 | 2974 / 9672 | 3 | 0 / 0 |
| classic | 60 | 0.0361 / 0.0490 / 0.1516 | 0.0400 / 0.0831 / 0.2136 | 2974 / 9672 | 3 | 0 / 0 |
| classic | 90 | 0.0382 / 0.0771 / 0.1696 | 0.0395 / 0.0817 / 0.2964 | 2974 / 9672 | 3 | 0 / 0 |
| classic | 120 | 0.0381 / 0.0643 / 0.1708 | 0.0399 / 0.0806 / 0.2361 | 2974 / 9672 | 3 | 0 / 0 |
| anime_missing | 30 | 0.0378 / 0.0578 / 0.2265 | 0.0412 / 0.0928 / 0.2541 | 2974 / 9672 | 3 | 0 / 0 |
| anime_missing | 60 | 0.0375 / 0.0562 / 0.1406 | 0.0372 / 0.0585 / 0.1159 | 2974 / 9672 | 3 | 0 / 0 |
| anime_missing | 90 | 0.0389 / 0.0697 / 0.2422 | 0.0387 / 0.0781 / 0.1347 | 2974 / 9672 | 3 | 0 / 0 |
| anime_missing | 120 | 0.0385 / 0.0668 / 0.2813 | 0.0451 / 0.1105 / 0.3224 | 2974 / 9672 | 3 | 0 / 0 |
| aurora_reduced | 30 | 0.5021 / 0.8588 / 4.8593 | 0.4403 / 0.5582 / 1.4684 | 10159 / 47664 | 3 | 0 / 0 |
| aurora_reduced | 60 | 0.4792 / 0.6116 / 2.5498 | 0.4399 / 0.5698 / 1.1009 | 10159 / 47664 | 3 | 0 / 0 |
| aurora_reduced | 90 | 0.4658 / 0.5922 / 4.2249 | 0.4444 / 0.5541 / 0.9366 | 10159 / 47664 | 3 | 0 / 0 |
| aurora_reduced | 120 | 0.4440 / 0.5556 / 1.3316 | 0.4889 / 0.6805 / 3.6447 | 10159 / 47664 | 3 | 0 / 0 |
| launcher | 30 | 0.0044 / 0.0045 / 0.1438 | 0.0045 / 0.0045 / 0.0728 | 310 / 1002 | 1 | 0 / 0 |
| launcher | 60 | 0.0039 / 0.0039 / 0.0200 | 0.0045 / 0.0046 / 0.0548 | 310 / 1002 | 1 | 0 / 0 |
| launcher | 90 | 0.0045 / 0.0039 / 0.2181 | 0.0045 / 0.0051 / 0.1390 | 310 / 1002 | 1 | 0 / 0 |
| launcher | 120 | 0.0039 / 0.0039 / 0.0255 | 0.0048 / 0.0043 / 0.1149 | 310 / 1002 | 1 | 0 / 0 |

All before/after vertex/index/command counts match; warmed ImGui allocation calls
are zero and live counts stable. This measures ImGui allocator activity, not all
process malloc/caches or GPU memory. Existing audio/registry tests separately count
C++ allocations. Halo blending, GPU cost, battery, RSS drift and native startup
latency remain unmeasured on Android. Aurora state is 1,000 bytes; PCM bank 499,308
bytes. Font atlas RGBA CPU output is 16,777,216 bytes (not measured GPU residency).

## Startup components measured independently on the host

| Component | Before ms | After ms | Scope |
|---|---:|---:|---|
| Embedded CPU font/context setup | 38.9909 | 41.6630 | Host only |
| UI PCM bank synthesis | 4.2520 | 5.1351 | Host only |
| Private logger directory/initial durable report | 0.0568 | 0.1540 | Host only |
| 32 synchronous durable logger events | 0.1226 | 0.1741 | Host only |

The logger timings use this executor's /tmp filesystem; they do not predict an
Android flash-storage fsync stall. No asynchronous durability change was justified.
Reduced motion stops physics but still builds the visible atmospheric geometry;
its CPU cost is similar to full Aurora. Cache stationary geometry only after
profiling and clip/state-lifetime validation. The closed launcher is much cheaper
and does not advance Aurora. Keep the approved quality until mobile evidence.

## Reliability improvements measured with fault tests

| Condition | Baseline source behavior | Audit verification |
|---|---|---|
| Preference FIFO, no writer | blocking open can hang indefinitely | real child completes before two-second alarm |
| Interrupted/partial save | single transfer fails | retries complete full file; restart state matches |
| Temporary ENOSPC | same adjustment never retried | 1,000 early checks produce no extra writes; bounded later retry restores state |
| Host PBO/padded/skipped rows | uploads inherit foreign state | exact RGBA/alpha readback and all tracked unpack bindings restored in real Mesa |
| Fast keyboard down/up | both can drain in one frame | distinct frames; overflow resets held devices |

These demonstrate correctness/recovery, not a FPS improvement. Baseline failures
are proven by source conditions; not every hazard was executed against the device
or old binary. All measurements and tests are reproducible:

```sh
python3 tests/kenny_benchmark.py --label local
python3 tests/run_android_stability.py --label local --sanitizers
python3 tests/kenny_gl_stability.py
```

Raw benchmark JSON is retained in ANDROID_AUDIT_VERIFICATION.json. Use repeated
idle-machine paired runs and actual Android Perfetto/power data before claiming
speedups. The native constructor's runtime discovery, first GPU frame, OpenSL
initialization/latency and long-session device memory are still unknown.
