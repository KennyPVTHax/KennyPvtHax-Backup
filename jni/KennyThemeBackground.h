#pragma once
#include "KennyAurora.h"
#include "KennyThemePreferences.h"

namespace KennyThemeBackground {
struct ArtworkFrame {
    ImTextureID texture = nullptr;
    int width = 0, height = 0;
    bool Valid() const { return texture && width>0 && height>0 && width<=16384 && height<=16384; }
};
// The asset owner uploads/releases textures on the render thread. This layer
// never opens arbitrary files, fabricates art, or allocates GPU resources. A
// future animation decoder may supply cached frames through the same interface.
using FrameProvider = bool (*)(void* user, double visibleTime, bool motionAllowed, ArtworkFrame& frame);
struct Artwork {
    ArtworkFrame current;
    FrameProvider provider = nullptr;
    void* user = nullptr;
    double time = 0;
    int frame = -2;
    void SetStatic(ArtworkFrame value) { Clear(); if(value.Valid()) current=value; }
    void SetProvider(FrameProvider value, void* context) { Clear();provider=value;user=context; }
    // Call before releasing/replacing the owner's texture or losing GL context.
    void Clear() { current={};provider=nullptr;user=nullptr;time=0;frame=-2; }
    void Advance(int next, float dt, bool reduced) {
        if(next==frame) return;
        const bool resumed=next!=frame+1;
        if(!resumed && !reduced) time+=KennyMotion::Delta(dt);
        frame=next;
        // Reduced still resolves the initial frame, then holds that texture.
        if(provider && (!reduced || !current.Valid())) {
            ArtworkFrame supplied;
            if(provider(user,time,!reduced,supplied) && supplied.Valid()) current=supplied;
            else current={}; // Decoder failure never exposes a stale texture.
        }
    }
};
inline void Surface(ImDrawList* draw, ImVec2 origin, ImVec2 size, float radius,
                    float header, float content) {
    draw->PushClipRect(origin,ImVec2(origin.x+size.x,origin.y+size.y),true);
    const ImVec2 uv=ImGui::GetFontTexUvWhitePixel();
    draw->PrimReserve(KennyEffects::Columns*KennyEffects::Rows*6,
                      (KennyEffects::Columns+1)*(KennyEffects::Rows+1));
    const unsigned base=draw->_VtxCurrentIdx;
    for(int y=0;y<=KennyEffects::Rows;++y) for(int x=0;x<=KennyEffects::Columns;++x) {
        const ImVec2 p=KennyEffects::MeshPoint(x,y,size,radius);
        const ImVec4 c=Claude::Hex(p.y<header ? 0x20171E : p.y<content ? 0x100B0F : 0x120A10,.28f);
        draw->PrimWriteVtx(ImVec2(origin.x+p.x,origin.y+p.y),uv,ImGui::GetColorU32(c));
    }
    KennyAurora::GridIndices(draw,base,KennyEffects::Columns,KennyEffects::Rows);
    draw->PopClipRect();
}
inline void DrawArtwork(ImDrawList* draw, ImVec2 origin, ImVec2 size, float radius,
                        const ArtworkFrame& frame, const KennyAppearance::Preferences& p) {
    if(!frame.Valid()) return;
    // Cover crops UVs; Contain letterboxes. Both use bounded rounded geometry,
    // not a rectangular image whose corners escape the floating window.
    const float scale=p.artworkCover ? std::max(size.x/frame.width,size.y/frame.height) :
                                       std::min(size.x/frame.width,size.y/frame.height);
    const ImVec2 imageSize(frame.width*scale,frame.height*scale);
    const ImVec2 offset((size.x-imageSize.x)*.5f,(size.y-imageSize.y)*.5f);
    draw->PushClipRect(origin,ImVec2(origin.x+size.x,origin.y+size.y),true);
    draw->PushTextureID(frame.texture);
    draw->PrimReserve(KennyEffects::Columns*KennyEffects::Rows*6,
                      (KennyEffects::Columns+1)*(KennyEffects::Rows+1));
    const unsigned base=draw->_VtxCurrentIdx;
    for(int y=0;y<=KennyEffects::Rows;++y) for(int x=0;x<=KennyEffects::Columns;++x) {
        ImVec2 point;
        if(p.artworkCover) point=KennyEffects::MeshPoint(x,y,size,radius);
        else {
            point=ImVec2(offset.x+imageSize.x*x/KennyEffects::Columns,
                         offset.y+imageSize.y*y/KennyEffects::Rows);
            point=KennyAurora::Inside(point,size,radius);
        }
        const ImVec2 uv((point.x-offset.x)/imageSize.x,(point.y-offset.y)/imageSize.y);
        draw->PrimWriteVtx(ImVec2(origin.x+point.x,origin.y+point.y),uv,
                          ImGui::GetColorU32(ImVec4(1,1,1,1-p.artworkDim*.01f)));
    }
    KennyAurora::GridIndices(draw,base,KennyEffects::Columns,KennyEffects::Rows);
    draw->PopTextureID();draw->PopClipRect();
}
} // namespace KennyThemeBackground
