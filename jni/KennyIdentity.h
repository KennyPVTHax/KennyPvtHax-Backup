#pragma once
#include "ClaudeTheme.h"
#include <cmath>

namespace KennyIdentity {
// Both header and launcher borrow the same cached texture; neither owns it.
inline bool Photo(ImDrawList* draw,ImVec2 center,float side,ImTextureID texture,int width,int height) {
    if(!texture||width<=0||height<=0||side<=0)return false;
    // Fixed fan geometry fills the existing circular identity mark.
    // Cover UVs preserve aspect ratio; no square frame or inset black disc.
    const float radius=side*.5f;
    const float u=width>height?float(height)/width:1.0f;
    const float v=height>width?float(width)/height:1.0f;
    const ImTextureID previous=draw->_CmdHeader.TextureId;
    if(previous!=texture)draw->PushTextureID(texture);
    constexpr int segments=64;draw->PrimReserve(segments*3,segments+1);
    const unsigned base=draw->_VtxCurrentIdx;
    draw->PrimWriteVtx(center,ImVec2(.5f,.5f),IM_COL32_WHITE);
    for(int i=0;i<segments;++i){const float a=6.28318530718f*i/segments;
        const float x=std::cos(a),y=std::sin(a);
        draw->PrimWriteVtx(ImVec2(center.x+x*radius,center.y+y*radius),ImVec2(.5f+x*u*.5f,.5f+y*v*.5f),IM_COL32_WHITE);}
    for(int i=0;i<segments;++i){draw->PrimWriteIdx(ImDrawIdx(base));draw->PrimWriteIdx(ImDrawIdx(base+1+i));draw->PrimWriteIdx(ImDrawIdx(base+1+(i+1)%segments));}
    if(previous!=texture)draw->PopTextureID();
    return true;
}

inline void Emblem(ImDrawList* draw,ImVec2 center,float scale) {
    const float mark=38*scale;
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
}
inline void Draw(ImDrawList* draw, ImVec2 origin, float padding, float width,
                 float height, float scale, ImTextureID logo=nullptr, int logoWidth=0, int logoHeight=0) {
    const float mark=38*scale, gap=12*scale;
    const ImVec2 center(origin.x+padding+mark*0.5f,origin.y+height*0.5f);
    if(!Photo(draw,center,mark,logo,logoWidth,logoHeight))Emblem(draw,center,scale);
    const ImU32 ink=ImGui::GetColorU32(Claude::Dark::textPrimary);
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
