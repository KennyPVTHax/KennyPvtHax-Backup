#pragma once
// Include after the genuine GL headers/loader. Owns no context or heap resource.
// CPU uploads must not inherit a host PBO, padded rows, or skipped pixels.
namespace KennyGL {
// Khronos core enum values. The bundled desktop loader intentionally strips
// enums it previously did not use; these require no new GL entry points.
constexpr GLenum Alignment=0x0CF5,RowLength=0x0CF2,SkipRows=0x0CF3,SkipPixels=0x0CF4;
constexpr GLenum UnpackBinding=0x88EF,UnpackBuffer=0x88EC,MaximumTexture=0x0D33;
constexpr GLenum WrapS=0x2802,WrapT=0x2803,ClampEdge=0x812F;
struct UnpackScope {
    GLint alignment=4,rowLength=0,skipRows=0,skipPixels=0,buffer=0;
    bool extended=false;
    explicit UnpackScope(bool useExtended=true):extended(useExtended){
        glGetIntegerv(Alignment,&alignment);glPixelStorei(Alignment,1);
#if !defined(IMGUI_IMPL_OPENGL_ES2)
        if(extended){
            glGetIntegerv(RowLength,&rowLength);
            glGetIntegerv(SkipRows,&skipRows);glGetIntegerv(SkipPixels,&skipPixels);
            glPixelStorei(RowLength,0);glPixelStorei(SkipRows,0);glPixelStorei(SkipPixels,0);
        }
#endif
#if !defined(IMGUI_IMPL_OPENGL_ES2)
        if(extended){glGetIntegerv(UnpackBinding,&buffer);glBindBuffer(UnpackBuffer,0);}
#endif
    }
    ~UnpackScope(){
#if !defined(IMGUI_IMPL_OPENGL_ES2)
        if(extended)glBindBuffer(UnpackBuffer,GLuint(buffer));
#endif
#if !defined(IMGUI_IMPL_OPENGL_ES2)
        if(extended){glPixelStorei(RowLength,rowLength);glPixelStorei(SkipRows,skipRows);glPixelStorei(SkipPixels,skipPixels);}
#endif
        glPixelStorei(Alignment,alignment);
    }
    UnpackScope(const UnpackScope&)=delete;UnpackScope& operator=(const UnpackScope&)=delete;
};
// Caller supplies a valid owning context and bounded RGBA bytes. Failure never
// publishes a texture ID. Existing pending GL errors conservatively fail upload;
// GL error queues cannot be saved/restored like ordinary state.
inline GLuint UploadRGBA(const unsigned char* pixels,int width,int height,bool extended=true,bool clamp=false){
    if(!pixels||width<=0||height<=0)return 0;
    GLint maximum=0;glGetIntegerv(MaximumTexture,&maximum);if(maximum<=0||width>maximum||height>maximum)return 0;
    GLuint texture=0;glGenTextures(1,&texture);if(!texture)return 0;
    GLint binding=0;glGetIntegerv(GL_TEXTURE_BINDING_2D,&binding);
    bool ok=false;
    {
        UnpackScope unpack(extended);glBindTexture(GL_TEXTURE_2D,texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        if(clamp){glTexParameteri(GL_TEXTURE_2D,WrapS,ClampEdge);glTexParameteri(GL_TEXTURE_2D,WrapT,ClampEdge);}
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,pixels);
        ok=glGetError()==0;glBindTexture(GL_TEXTURE_2D,GLuint(binding));
    }
    if(!ok){glDeleteTextures(1,&texture);return 0;}return texture;
}
} // namespace KennyGL
