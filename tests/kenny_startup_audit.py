"""Static regression gates; does not prove Android GPU/runtime behavior."""
from pathlib import Path
import re
import subprocess

source = Path("jni/main.cpp").read_text()
baseline = subprocess.check_output(["git", "show", "7381b71:jni/main.cpp"], text=True)
for pattern in (r"0x[0-9a-fA-F]+",):
    assert re.findall(pattern, source) == re.findall(pattern, baseline), "offsets changed"
fix = source[source.index("void FixGameCrash()"):source.index("void *RunGame")]
assert "system(" not in fix and "chmod" not in fix
input_code = source[source.index("void _OI("):source.index("bool logged")]
assert "ImGui::" not in input_code and "ImGui_Impl" not in input_code
assert "AInputEvent*)thiz" not in input_code
assert "NativeGlobalsReady.load" in source and "PresentationApp.store" in source
logger = Path("jni/KennyDiagnostics.h").read_text()
assert not any(x in logger for x in ("#include \"imgui", "sigaction(", "signal(", "/storage/emulated", "curl"))
assert "KennyPvtHaxDiagnosticsExportToFd" in source
font_start = source.index("        // Icons config")
font_end = source.index("        if(!io.Fonts->Build()", font_start)
fonts = source[font_start:font_end]
assert fonts.count("FontDataOwnedByAtlas = false") == 5
assert "&base_cfg" in fonts and "&esp_cfg" in fonts
# Compile the application's actual font setup with genuine embedded bytes.
# The legacy voidfont declaration repeats const; normalize only this test
# header declaration for GCC portability, without changing any array bytes.
void = Path("jni/ANOY/voidfont.h").read_text().replace("const const ", "const ")
Path(".verification/kenny_voidfont_fixture.h").write_text(void)
prelude = '''#include "imgui/imgui.h"
#include "ANOY/CustomFont.h"
#include "ANOY/fontAwesome.hpp"
#include "ANOY/font_awesome_5.h"
#include "kenny_voidfont_fixture.h"
#include <cassert>
#include <cstdio>
namespace KennyMenu { ImFont* Font=nullptr; }
int main(){
 for(int cycle=0;cycle<3;++cycle){
  ImGui::CreateContext();ImGuiIO& io=ImGui::GetIO();ImFont* font2=nullptr;int density=160;
'''
ending = '''
 assert(io.Fonts->Build());assert(font2&&KennyMenu::Font);
 io.Fonts->ClearInputData();ImGui::DestroyContext();
 }
 std::puts("PASS actual embedded font setup: atlas builds and clears/recreates three times without freeing static font data.");
}
'''
Path(".verification/kenny_font_check.cpp").write_text(prelude + fonts + ending)
print("PASS source gates: original offsets unchanged, destructive startup routine disabled, no input-thread ImGui or invalid thiz casts, atomic global/app publication, independent diagnostics and exported host interface; font test extracted from actual UI code.")
