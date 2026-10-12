// Executed inside an actual Mesa OpenGL context supplied by the Python runner.
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_opengl3_loader.h"
#include "KennyGLUpload.h"
#include <cassert>
#include <array>
#include <cstdio>
static void HostState(GLuint texture,GLuint pbo){glBindTexture(GL_TEXTURE_2D,texture);glBindBuffer(KennyGL::UnpackBuffer,pbo);glPixelStorei(KennyGL::Alignment,8);glPixelStorei(KennyGL::RowLength,23);glPixelStorei(KennyGL::SkipRows,4);glPixelStorei(KennyGL::SkipPixels,6);}
static void Preserved(GLuint texture,GLuint pbo){GLint n;for(auto entry:{std::array<GLint,2>{GL_TEXTURE_BINDING_2D,GLint(texture)},{KennyGL::UnpackBinding,GLint(pbo)},{KennyGL::Alignment,8},{KennyGL::RowLength,23},{KennyGL::SkipRows,4},{KennyGL::SkipPixels,6}}){glGetIntegerv(GLenum(entry[0]),&n);assert(n==entry[1]);}}
extern "C" int KennyGLStabilityCheck(){
 assert(imgl3wInit()==0);ImGui::CreateContext();ImGui::GetIO().IniFilename=nullptr;assert(ImGui_ImplOpenGL3_Init("#version 130"));
 GLuint host=0,pbo=0;glGenTextures(1,&host);glGenBuffers(1,&pbo);HostState(host,pbo);glBufferData(KennyGL::UnpackBuffer,4,nullptr,GL_STREAM_DRAW);
 assert(glGetError()==0);assert(ImGui_ImplOpenGL3_CreateDeviceObjects());Preserved(host,pbo);
 const auto original=ImGui::GetIO().Fonts->TexID;assert(original);assert(ImGui_ImplOpenGL3_CreateFontsTexture());assert(original==ImGui::GetIO().Fonts->TexID);Preserved(host,pbo);
 const unsigned char pixels[16]={1,2,3,255,4,5,6,0,7,8,9,128,10,11,12,255};GLuint id=KennyGL::UploadRGBA(pixels,2,2,true,true);assert(id);Preserved(host,pbo);
 glBindTexture(GL_TEXTURE_2D,id);
 using ReadTexture=void (*)(GLenum,GLint,GLenum,GLenum,void*);
 auto read=reinterpret_cast<ReadTexture>(imgl3wGetProcAddress("glGetTexImage"));assert(read);
 std::array<unsigned char,16> result{};glPixelStorei(GL_PACK_ALIGNMENT,1);read(GL_TEXTURE_2D,0,GL_RGBA,GL_UNSIGNED_BYTE,result.data());
 for(unsigned i=0;i<16;++i)assert(result[i]==pixels[i]);glBindTexture(GL_TEXTURE_2D,host);
 assert(!KennyGL::UploadRGBA(pixels,100000,2));Preserved(host,pbo);
 for(int i=0;i<100;++i){ImGui_ImplOpenGL3_DestroyDeviceObjects();assert(ImGui_ImplOpenGL3_CreateDeviceObjects());Preserved(host,pbo);assert(glGetError()==0);}
 glDeleteTextures(1,&id);ImGui_ImplOpenGL3_Shutdown();Preserved(host,pbo);ImGui::DestroyContext();glBindBuffer(KennyGL::UnpackBuffer,0);glDeleteBuffers(1,&pbo);glDeleteTextures(1,&host);
 std::puts("PASS actual Mesa OpenGL: hostile PBO/row/skip/alignment isolation, state restoration, exact RGBA/alpha readback, failed upload, no duplicate font upload, 100 backend resource recreate/cleanup cycles. Not Android GLES.");return 0;
}
