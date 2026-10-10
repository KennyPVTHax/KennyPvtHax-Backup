#pragma once
#include <array>
#include <cmath>
#include "imgui/imgui.h"

// Small material primitives, sharing the font atlas white pixel. Geometry is
// bounded; circle directions are computed once, never allocated per frame.
namespace KennyPaint {
inline const std::array<ImVec2,32> circle = [] {
    std::array<ImVec2,32> points{};
    for(unsigned i=0;i<points.size();++i) {
        const float angle=i*6.283185307f/points.size();
        points[i]=ImVec2(std::cos(angle),std::sin(angle));
    }
    return points;
}();
inline ImVec4 Mix(ImVec4 a, ImVec4 b, float t) {
    return ImVec4(a.x+(b.x-a.x)*t,a.y+(b.y-a.y)*t,a.z+(b.z-a.z)*t,a.w+(b.w-a.w)*t);
}
inline void Disc(ImDrawList* draw, ImVec2 center, float radius, ImVec4 top, ImVec4 bottom) {
    draw->PrimReserve(96,33);
    const unsigned base=draw->_VtxCurrentIdx;
    const ImVec2 uv=ImGui::GetFontTexUvWhitePixel();
    draw->PrimWriteVtx(center,uv,ImGui::GetColorU32(Mix(top,bottom,0.5f)));
    for(const auto& p:circle)
        draw->PrimWriteVtx(ImVec2(center.x+p.x*radius,center.y+p.y*radius),uv,
                           ImGui::GetColorU32(Mix(top,bottom,(p.y+1)*0.5f)));
    for(unsigned i=0;i<32;++i) {
        draw->PrimWriteIdx(static_cast<ImDrawIdx>(base));
        draw->PrimWriteIdx(static_cast<ImDrawIdx>(base+1+i));
        draw->PrimWriteIdx(static_cast<ImDrawIdx>(base+1+(i+1)%32));
    }
}
// Faded ends prevent ornamental strokes from becoming another box/border.
inline void Seam(ImDrawList* draw, ImVec2 start, float width, ImVec4 color, float thickness=1) {
    if(width<=0)return;
    ImVec4 clear=color;clear.w=0;
    const float middle=start.x+width*0.5f;
    draw->AddRectFilledMultiColor(start,ImVec2(middle,start.y+thickness),
        ImGui::GetColorU32(clear),ImGui::GetColorU32(color),ImGui::GetColorU32(color),ImGui::GetColorU32(clear));
    draw->AddRectFilledMultiColor(ImVec2(middle,start.y),ImVec2(start.x+width,start.y+thickness),
        ImGui::GetColorU32(color),ImGui::GetColorU32(clear),ImGui::GetColorU32(clear),ImGui::GetColorU32(color));
}
} // namespace KennyPaint
