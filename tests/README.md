# SDK-independent Stage 5 checks

Run from the repository root with the bundled ImGui sources and a C++17 host compiler:

```sh
g++ -std=c++17 -O1 -Wall -Wextra -Werror -I jni tests/kenny_effects_check.cpp jni/imgui/imgui.cpp jni/imgui/imgui_draw.cpp jni/imgui/imgui_widgets.cpp jni/imgui/imgui_tables.cpp -o /tmp/kenny_effects_check
timeout 30s /tmp/kenny_effects_check
```

Keep assertions enabled. This exercises production animation/effect code and actual ImGui draw vertices. It checks the floating-toggle wrapper's unchanged hitbox/native release/disabled behavior, interpolation across frame rates, rapid target switching, hidden-frame recovery, fixed cache capacity, rounded clipping including halos/fringes, and stable warmed geometry allocations. It neither compiles the SDK-dependent Android application nor proves device FPS, GPU appearance, or platform input behavior.

The broader local interaction harness under `.verification/stage5_*` extracts the unchanged real panel statements/configuration declarations and tests all original bindings, navigation, native input, appearance actions, scrolling and viewports. Its captures feed the CPU rasterizer; generated output remains ignored.
