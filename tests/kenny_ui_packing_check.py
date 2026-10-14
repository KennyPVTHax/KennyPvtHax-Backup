"""Presentation ABI regression; never includes or executes native owner hooks."""
from pathlib import Path
import subprocess

source = Path('jni/main.cpp').read_text()
start = source.index('#pragma pack(push, 8)')
end = source.index('#pragma pack(pop)', start) + len('#pragma pack(pop)')
block = source[start:end]
assert block.count('#pragma pack(push, 8)') == 1
assert block.count('#pragma pack(pop)') == 1
assert source.index('#include "Helper/bypass.h"') < start
assert end < source.index('#include "Lua_Buffer.cpp"')
out = Path('.verification/ui-packing')
out.mkdir(parents=True, exist_ok=True)
prelude = '''#include "KennyDiagnostics.h"
#include "KennyStartup.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <atomic>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
'''
body = '''
struct IncomingPacking { char first; int second; };
int main() {
 std::cout << sizeof(KennyAppearance::Preferences) << ' '
 << alignof(KennyAppearance::Preferences) << ' '
 << offsetof(KennyAppearance::Preferences, auroraIntensity) << ' '
 << sizeof(KennyAudio::Mixer) << ' ' << sizeof(KennyMenu::State) << ' '
 << sizeof(KennyPresentation::Assets) << '\\n';
 std::cerr << offsetof(IncomingPacking, second) << '\\n';
}
'''
layouts = []
for name, incoming in [('normal', ''), ('inherited', '#pragma pack(1)\n')]:
    cpp = out / (name + '.cpp')
    cpp.write_text(prelude + incoming + block + '\n' + body)
    exe = out / name
    subprocess.run(['g++', '-std=c++17', '-pthread', '-I', 'jni', str(cpp),
                    '-lz', '-o', str(exe)], check=True, timeout=120)
    result = subprocess.run([str(exe.resolve())], capture_output=True,
                            text=True, check=True, timeout=10)
    layouts.append(result.stdout.strip())
    assert int(result.stderr.strip()) == (4 if name == 'normal' else 1), 'incoming packing not restored'
assert layouts[0] == layouts[1], 'presentation ABI changed with incoming packing'
print('PASS actual presentation include block: normal/inherited packing identical; incoming native packing restored:', layouts[0])
