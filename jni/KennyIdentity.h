#pragma once
#include "ClaudeTheme.h"

namespace KennyIdentity {
inline void Draw(ImDrawList* draw, ImVec2 origin, float padding, float width,
                 float height, float scale) {
    const float mark=38*scale, gap=12*scale;
    const ImVec2 center(origin.x+padding+mark*0.5f,origin.y+height*0.5f);
    KennyPaint::Disc(draw,center,mark*0.48f,Claude::Hex(0x321C27),Claude::Hex(0x0B090D));
    draw->AddCircle(center,mark*0.49f,ImGui::GetColorU32(Claude::Hex(0x94717D,0.32f)),32,1);
    draw->PathArcTo(center,mark*0.49f,-2.2f,0.25f,18);
    draw->PathStroke(ImGui::GetColorU32(Claude::Hex(0xE78695,0.85f)),false,std::max(1.0f,1.4f*scale));
    const ImVec2 stem(center.x-6*scale,center.y-10*scale);
    const ImU32 ink=ImGui::GetColorU32(Claude::Dark::textPrimary);
    const float stroke=std::max(1.3f,2*scale);
    draw->AddLine(stem,ImVec2(stem.x,center.y+10*scale),ink,stroke);
    draw->AddLine(ImVec2(stem.x+1*scale,center.y),ImVec2(center.x+8*scale,center.y-10*scale),ink,stroke);
    draw->AddLine(ImVec2(stem.x+1*scale,center.y),ImVec2(center.x+8*scale,center.y+10*scale),
                  ImGui::GetColorU32(Claude::Dark::selectedInk),stroke);
    const float x=origin.x+padding+mark+gap;
    ImFont* font=ImGui::GetFont();
    const float available=width-mark-gap-4*scale;
    const float natural=font->CalcTextSizeA(29*scale,FLT_MAX,0,"KennyPvtHax").x;
    const float titleSize=29*scale*std::min(1.0f,available/natural);
    // Reuse the existing smaller atlas font for crisp descriptor text rather
    // than shrinking the large menu font to a barely readable size.
    ImFont* tagFont=ImGui::GetIO().FontDefault;
    if(!tagFont)tagFont=ImGui::GetIO().Fonts->Fonts[0];
    const float tagSize=std::max(9.0f,14.0f*scale), spacing=4*scale;
    const float y=origin.y+(height-titleSize-tagSize-spacing)*0.5f;
    draw->AddText(font,titleSize,ImVec2(x,y),ink,"Kenny");
    const float first=font->CalcTextSizeA(titleSize,FLT_MAX,0,"Kenny").x;
    draw->AddText(font,titleSize,ImVec2(x+first,y),ImGui::GetColorU32(Claude::Dark::selectedInk),"PvtHax");
    draw->AddText(tagFont,tagSize,ImVec2(x,y+titleSize+spacing),
                  ImGui::GetColorU32(Claude::Hex(0xBCAAB0)),"CRIMSON ECLIPSE");
}
} // namespace KennyIdentity
