bool xeffecton = false;
double rainbowRatio = 0.0;

FLinearColor Rainbow(double& ratio, double step = 0.05)
{
static const FLinearColor colors[7] =
{
FLinearColor(1.0f, 0.0f, 0.0f, 1.0f), // Red
FLinearColor(1.0f, 1.0f, 0.0f, 1.0f), // Yellow
FLinearColor(0.0f, 1.0f, 0.0f, 1.0f), // Green
FLinearColor(0.0f, 1.0f, 1.0f, 1.0f), // Cyan
FLinearColor(0.0f, 0.0f, 1.0f, 1.0f), // Blue
FLinearColor(1.0f, 0.0f, 1.0f, 1.0f), // Magenta
FLinearColor(0.7f, 0.7f, 0.0f, 1.0f)  // Olive
};

int index1 = (int)ratio % 7;  
int index2 = (index1 + 1) % 7;  
float mix = ratio - (int)ratio;  

FLinearColor c1 = colors[index1];  
FLinearColor c2 = colors[index2];  

float r = c1.R + mix * (c2.R - c1.R);  
float g = c1.G + mix * (c2.G - c1.G);  
float b = c1.B + mix * (c2.B - c1.B);  
float a = c1.A + mix * (c2.A - c1.A);  

ratio += step;  
if (ratio >= 7.0) ratio = 0.0;  

return FLinearColor(r, g, b, a);

}

void TriggerHitEffect()
{
if (xeffecton || !Cheat::localController) return;

auto MyHUD = (ASurviveHUD*)Cheat::localController->MyHUD;  
if (!MyHUD) return;  

auto hitPerf = &MyHUD->HitPerform;  
uintptr_t base = *(uintptr_t*)(uintptr_t)hitPerf;  
if (!base) return;  

xeffecton = true;  

std::thread([]   
{  
    const int totalFrames = 50;  
    for (int i = 0; i < totalFrames; i++)   
    {  
        if (!Cheat::localController) break;  

        auto MyHUD = (ASurviveHUD*)Cheat::localController->MyHUD;  
        if (!MyHUD) break;  

        auto hitPerf = &MyHUD->HitPerform;  
        uintptr_t base = *(uintptr_t*)(uintptr_t)hitPerf;  
        if (!base) break;  

        FLinearColor color = Rainbow(rainbowRatio);  

        *(float*)(base + 0x10) = Cheat::Memory::Size;  
        *(float*)(base + 0x50) = Cheat::Memory::Size;  
        *(float*)(base + 0x90) = Cheat::Memory::Size;  
        *(float*)(base + 0xD0) = Cheat::Memory::Size;  

        MyHUD->SetHitPerformColor(EHitPerformColorType::EHitPerformColor_Head, color);  
        MyHUD->SetHitPerformColor(EHitPerformColorType::EHitPerformColor_Body, color);  

        std::this_thread::sleep_for(std::chrono::milliseconds(15));  
    }  
    xeffecton = false;  
}).detach();

}
