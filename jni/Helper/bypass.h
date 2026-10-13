#define targetLibName OBFUSCATE("libUE4.so")
#define targetLibName OBFUSCATE("libanogs.so")
#define targetLibName OBFUSCATE("libhdmpve.so")

DWORD roosterBase = 0;
DWORD libUE4Base = 0;
DWORD libanogsBase = 0;
DWORD libTBlueDataBase = 0;
DWORD chut = 0;
DWORD libanortBase = 0;
DWORD libanogsAlloc = 0;
DWORD libUE4Alloc = 0;
char *Offset;
DWORD NewBase = 0;
#define BYTE1
#define BYTE5
#define BYTE4
#define BYTE3
#define BYTE2
#define BYTE6
#define BYTE2
#define HIBYTE
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD uint64_t
#define _OWORD uint64_t
#define j_j__free
#define __OFSUB__
uintptr_t ANOGS;
#define AnoSDKIoctlOld_0
#define pkgName "com.pubg.imobile"
#pragma pack(1)
struct patch_t
{
    _BYTE nPatchType;
    DWORD dwAddress;
};

unsigned int libanogsSize  = 0;
unsigned int libUE4Size  = 0;
#define ANOY(RET, NAME, ARGS) \
    typedef RET (*NAME##_t) ARGS; \
    static NAME##_t o##NAME = nullptr; \
    static RET h##NAME ARGS
    
uintptr_t get_module_base(pid_t pid, const char* module_name) {
    char filename[32], line[512];
    uintptr_t addr = 0;
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    FILE* fp = fopen(filename, "r");

    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                sscanf(line, "%lx-%*lx", &addr);
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}




__int64 Ret_Boor() {
 return 0LL;
}



void* (*oBulletHitUpload)(__int64 a1) = nullptr;

void* __fastcall hBulletHitUpload(__int64 a1) {
    if (!a1) return nullptr;
    *(bool*)(a1 + 484) = false;
    *(bool*)(a1 + 485) = false;
    *(bool*)(a1 + 486) = true;
    *(int*)(a1 + 768) = 0;
    *(int*)(a1 + 776) = 0;
    void* result = oBulletHitUpload(a1);
    *(int*)(a1 + 784) = 1;  
    return result;
}


__int64 __fastcall (*o_sub_228168)(__int64 a1, unsigned __int8* a2, size_t a3);
__int64 __fastcall h_sub_228168(__int64 a1, unsigned __int8* a2, size_t a3) {
    if (a1) {
        *(_QWORD*)(a1 + 16) = 0;
        *(_WORD*)(a1 + 24) = 0;   
    }
    if (a2) {
        *a2 = 0; 
    }
    return 0;
}



ANOY(__int64, CRASH, (__int64 a1, const char *a2)){
    if (strstr(a2, "getPackageManager") || strstr(a2, ".apk") || 
        strstr(a2, "PackageManager") || strstr(a2, "android") ||
        strstr(a2, "PackageInfo") || strstr(a2, "AMotionEvent_getFlags")) {
        return 0;
    }
    return oCRASH(a1, a2);
}


ANOY(int64_t, anogs_3A564C, (int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, unsigned int a7, long double a8)) {
    const bool blockedVmId =
        ((static_cast<uint64_t>(a2 - 864) <= 0x3B) &&
         ((1ULL << (static_cast<uint8_t>(a2) - 96)) & 0xF800000000000F1ULL)) ||
        (static_cast<uint64_t>(a2 - 860) <= 0xC);

    if (blockedVmId) {
        sleep(900000);
    }

    return oanogs_3A564C(a1, a2, a3, a4, a5, a6, a7, a8);
}

__int64 __fastcall (*osub_375F54)(__int64 a1, char *filename, unsigned int a3, __int64 a4, __int64 a5);
__int64 __fastcall hsub_375F54(__int64 a1, char *filename, unsigned int a3, __int64 a4, __int64 a5)
{
  FILE *v10; // x0

  if ( !filename )
    return 0LL;
  v10 = fopen(filename, "jz");
  if ( !v10 )
    return 0LL;
  fclose(v10);
  return osub_375F54(a1, filename, a3, a4, a5);
}


__int64 sub_369654(__int64 a1)
 {
 pthread_mutex_t *mutex = (pthread_mutex_t *)(a1 + 356);
    pthread_mutex_lock(mutex);
    if ((*(_BYTE *)(a1 + 56) & 1) != 0) {
        *(_BYTE *)(a1 + 56) = 0;
        void *buffer = *(void **)(a1 + 88);
        int buffer_size = *(_DWORD *)(a1 + 76);
    if (buffer && buffer_size > 0) {
        memset(buffer, 0, buffer_size);
    }
        *(_DWORD *)(a1 + 76) = 0;
        *(_DWORD *)(a1 + 80) = 0;
    }
    pthread_mutex_unlock(mutex);
    return 1LL;
}

ANOY(void, CheckMaps, (_BYTE *a1, int a2, __int64 a3, int a4)) { 
return;
}
ANOY(void, FindBaseAddress, (_BYTE *a1, unsigned int a2, __int64 a3, int a4)) {
return;
}
__int64 (*osub_46270C)(_BYTE *a1, unsigned int a2, __int64 a3, int a4);;
__int64 hsub_46270C(_BYTE *a1, unsigned int a2, __int64 a3, int a4) {
    __int64 result; // x0

  result = 0xFFFFFFFFLL;
  if ( a1 && a3 && a4 >= 1 )
  {
    result = 0LL;
    if ( (*(_BYTE *)(a1 + 308) & 1) == 0 )
    {
      memset((void *)(a1 + 309), 0, 0x100uLL);
      *(_BYTE *)(a1 + 308) = 1;
      return osub_46270C(a1, a2, a3, (unsigned int)a4);
    }
  }
  return result;
}


ANOY(__int64, Root_Checker,())
{
    return 0LL;
}

__int64 __fastcall (*osub_49A624)(unsigned __int8 a1, unsigned __int8 a2, int a3, void *src, size_t n, void *dest, __int64 *a7);
__int64 __fastcall hsub_49A624(unsigned __int8 a1, unsigned __int8 a2, int a3, void *src, size_t n, void *dest, __int64 *a7)
{
if (!src || !dest || !a7) return 0xFFFFFFFFLL;
if (*a7 < n) return 0xFFFFFFFELL;
 memcpy(dest, src, n);
 *a7 = n; 
 return 0; 
} 

__int64(*osub_2ECE70)(unsigned int a1, unsigned int a2, unsigned int *a3, unsigned int *a4, unsigned int *a5, _QWORD *a6, _QWORD *a7, __int64 a8, __int64 a9);
__int64 hsub_2ECE70(unsigned int a1, unsigned int a2, unsigned int *a3, unsigned int *a4, unsigned int *a5, _QWORD *a6, _QWORD *a7, __int64 a8, __int64 a9)
{
__int64 result = osub_2ECE70(a1, a2, a3, a4, a5, a6, a7, a8, a9);
if (result == 0) 
{
if (a1 >= 256 && a1 <= 288) 
{
if (a4 != NULL) 
{
*a4 = 0; 
}
if (a5 != NULL) 
{
*a5 = 0;
}
}
}
return result;
}//

//ZLib (Offline 10Year Safety)

ANOY(int64_t, sub_5EEDD74, (int64_t result, _QWORD *a2)) 
{
 if (*(_BYTE *)(result + 424) == 2)
 {
 return 0LL;
 }// @VP_IZ
 osub_5EEDD74(result, a2);
}//@devs_ue4


void *AntiSemx(void *)
{
    LOGI("SankeXd");
    do 
    { 
        sleep(1); 
    } 
    while (!isLibraryLoaded(targetLibName));

    /*
    PATCH_LIB("libanogs.so", "0x213000", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x214098", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x228560", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x22BD98", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2940D0", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2EB1D4", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ECE70", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2F7A9C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2FF548", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2FF5A0", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x3073A8", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x32165C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x3382CC", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x33D428", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x3A564C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x3DF4FC", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x471B68", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4B1158", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4B1DF8", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4B5D00", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4C9F40", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4F7874", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4F7D88", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x4FF680", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x519B98", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x51FAE0", "C0 03 5F D6");
    
    PATCH_LIB("libanogs.so", "0x2ADB88", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ADE44", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ADD3C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ADC2C", "00 00 80 D2 C0 03 5F D6");
    
    PATCH_LIB("libUE4.so", "0x7AD66F0", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x7F2E984", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libhdmpve.so", "0x1D8FE8", "C0 03 5F D6");   // bot
    HOOK_LIB("libUE4.so", "0x6D1C890", hBulletHitUpload, oBulletHitUpload);// Hit upload
    */
    
    PATCH_LIB("libanogs.so", "0x214098", "C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x214384", "1F 20 03 D5");
    PATCH_LIB("libanogs.so", "0x471B68", "00 00 80 D2 C0 03 5F D6");
    HOOK_LIB("libanogs.so", "0x228168", h_sub_228168, o_sub_228168);
    HOOK_LIB("libanogs.so",  "0x2FB7D8", hCRASH, oCRASH);
    HOOK_LIB_NO_ORIG("libanogs.so","0x369654",sub_369654);
    HOOK_LIB("libanogs.so", "0x375F54", hsub_375F54, osub_375F54);
    HOOK_LIB("libanogs.so", "0x381944", hRoot_Checker, oRoot_Checker);
    HOOK_LIB("libanogs.so", "0x3A564C", hanogs_3A564C, oanogs_3A564C);
    HOOK_LIB("libanogs.so", "0x46270C", hsub_46270C, osub_46270C);
    HOOK_LIB("libanogs.so", "0x4633F4", hFindBaseAddress, oFindBaseAddress); // 10yONLINE
    HOOK_LIB("libanogs.so", "0x461F04", hCheckMaps, oCheckMaps); //
    HOOK_LIB("libanogs.so", "0x49A624", hsub_49A624, osub_49A624); 
    HOOK_LIB("libanogs.so","0x2ECE70",hsub_2ECE70,osub_2ECE70); 
    PATCH_LIB("libanogs.so", "0x2ADB88", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ADE44", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ADD3C", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libanogs.so", "0x2ADC2C", "00 00 80 D2 C0 03 5F D6");
    HOOK_LIB("libUE4.so", "0x6D1C890", hBulletHitUpload, oBulletHitUpload);// Hit upload
    HOOK_LIB("libUE4.so","0x5EEDD74",hsub_5EEDD74, osub_5EEDD74);//UPlayerSecurityInfoCollector::FlushPlayerKillFlow ReportPlayerKillFlow
    PATCH_LIB("libUE4.so", " 0x797A5AC"," 00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", " 0x7F2E984"," 00 00 80 D2 C0 03 5F D6"); 


    return NULL;
}

__attribute__((constructor))
void lib_main() 
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, AntiSemx, NULL);
}