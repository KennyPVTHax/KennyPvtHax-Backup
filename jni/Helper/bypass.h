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



__int64 sub_2625E0()
{
 return 0LL;
}
__int64 sub_25D0B4()
{
 return 0LL;
}


void *AntiSemx(void *)
{
    LOGI("SankeXd");
    do 
    { 
        sleep(1); 
    } 
    while (!isLibraryLoaded(targetLibName));
    
    PATCH_LIB("libUE4.so", "0x6826CF0", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x68A34B8", "C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x68A3888", "C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x72116B4", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x743E9A0", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x7AD66F0", "00 00 80 D2 C0 03 5F D6");
    
    
    //PATCH_LIB("libUE4.so", "0x6D1C890", "00 00 80 D2 C0 03 5F D6");
    //PATCH_LIB("libUE4.so", "0x6F89048", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x78F3BAC", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x78F73B0", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x7952A74", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x7FA8300", "00 00 80 D2 C0 03 5F D6");
  //  PATCH_LIB("libUE4.so", "0xCC8E630", "00 00 80 D2 C0 03 5F D6");
  //  PATCH_LIB("libUE4.so", "0xCC8E660", "00 00 80 D2 C0 03 5F D6");
//    PATCH_LIB("libUE4.so", "0xCC8E9E0", "00 00 80 D2 C0 03 5F D6");
    PATCH_LIB("libUE4.so", "0x78E7010", "1F 20 03 D5");
   // PATCH_LIB("libUE4.so", "0x7F2E984", "00 00 80 D2 C0 03 5F D6");
   
    PATCH_LIB("libhdmpve.so", "0x1D8FE8", "C0 03 5F D6");//bot
    PATCH_LIB("libhdmpve.so","0x1082D8","00 00 80 D2 C0 03 5F D6");
    HOOK_LIB_NO_ORIG("libhdmpve.so","0x2625E0",sub_2625E0);
    HOOK_LIB_NO_ORIG("libhdmpve.so","0x25D0B4",sub_25D0B4);
    return NULL;
}

__attribute__((constructor))
void lib_main() 
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, AntiSemx, NULL);
}
