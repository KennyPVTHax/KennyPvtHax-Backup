
#define targetLibName oxorany("libhdmpve.so")
#define targetLibName oxorany("libanogs.so")
#define targetLibName oxorany("libUE4.so")
#define targetLibName oxorany("libTBlueData.so")

#define ARM64_SYSREG(reg0, reg1, reg2, reg3, op) (((reg0) & 0x1F) | (((reg1) & 0x1F) << 5) | (((reg2) & 0x7) << 10) | (((reg3) & 0xF) << 16) | (((op) & 0x7) << 20))

#ifdef __aarch64__
uint64_t _ReadStatusReg(uint64_t reg) {
    return 0;
}
#endif

char *Offset;

#define ARM64_SYSREG_S3_3_C13_C0_2 "S3_3_C13_C0_2"
#define _ReadStatusReg(reg) ({ uint64_t val; __asm__ volatile("mrs %0, " reg : "=r" (val)); val; })
#define READ_STATUS_REG() ({ uint64_t val; __asm__ volatile("mrs %0, S3_3_C13_C0_2" : "=r" (val)); val; })
#define ret_zero
#define _BYTE  uint8_t
#define _WORD  uint16_t
#define _DWORD uint32_t
#define _QWORD __int64
#define _OWORD uint64_t
#define _QWORD uint64_t
#define off_21DC28
#define _BOOL8 uint64_t
#include <dobby.h>
#define j_j__free
#define log_suspicious_activity
#define apply_cheat_penalty
#define check_memory_integrity
#define __OFSUB__
#define HIWORD
#define JUMPOUT
#define byte_4
#include <random>
#define _ReadStatusReg
#define BYTE5
#define BYTE4
#define __strncpy_chk
#define AnoSDKIoctlOld
#define LODWORD
#define aTERSIGStart
#define HIBYTE
#define BYTE6
#define Hook_Event
#define libanogs "libanogs.so"
#define LibUE4 "libUE4.so"
#define libc "nb/libc.so"
#define libEGL "nb/libEGL.so"
#define BYTE1
#define BYTE3
#define MEMORY_BASIC_INFORMATION mbi
#define BYTE2
#define ARM64_SYSREG
#define _WriteStatusReg
#define targetLibName oxorany("libTBlueData.so")
#define targetLibName oxorany("libRoosterNN.so")
#define targetLibName oxorany("libhdmpve.so")
#define targetLibName oxorany("libAntsVoice.so")
#define targetLibName oxorany("libanogs.so")
#define targetLibName oxorany("libUE4.so")
#define targetLibName oxorany("libanogs.so")
typedef long long int64; 
typedef short int16;
DWORD libanogsBase = 0;
DWORD libUE4Base = 0;
DWORD libanortBase = 0;
DWORD libcBase = 0;
DWORD OriginalStackCheck = 0;
DWORD LibcAlloc = 0;
DWORD libEgl_base = 0;
DWORD EglAlloc = 0;
DWORD libanogsAlloc = 0;
DWORD libUE4Alloc = 0;
DWORD libEGLAlloc = 0;
unsigned int libanogsSize  = 0;
unsigned int libUE4Size  = 0;
unsigned int libcSize = 0xC3000;
unsigned int libEglSize = 0x2000;
DWORD NewBase = 0;
#define HOOK
#define RAHUL(RET, NAME, ARGS) \
  RET(*o##NAME) ARGS; \
  RET h##NAME ARGS







__int64 sub_2625E0()
{
 return 0LL;
}
__int64 sub_25D0B4()
{
 return 0LL;
}


void * Preet(void *) {
LOGI("PREET THREAD RUNNING");
    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));
    #if defined(__aarch64__)
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
    #endif
    return NULL;
}



__attribute__((constructor))
void lib_main() 
{
    pthread_t ptid;
    pthread_create(&ptid, NULL, Preet, NULL);
}
