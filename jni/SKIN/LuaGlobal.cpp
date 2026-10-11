#pragma once
#include <cstring>
#include <android/log.h>


#define LOG_TAG "Sanke"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

// Includes moved to main.cpp to avoid duplication
namespace Lua
{
    int (*luaL_loadbufferx_Ptr)(void* L, const char* buff, size_t size, const char* name, const char* mode);
    int (*lua_pcall_Ptr)(void* L, int nargs, int nresults, int errfunc);
    int64_t (*sub_BA003F8_Ptr)(int a1);
    const char* (*lua_tostring_Ptr)(void* L, int index);

    void* GetLuaState()
    {
        if (sub_BA003F8_Ptr)
        {
            for (int i = 0; i < 16; i++)
            {
                int64_t result = sub_BA003F8_Ptr(i);
                if (result)
                {
                    void* L = *(void**)(result + 80);
                    if (L)
                    {
                        return L;
                    }
                }
            }
        }
        return nullptr;
    }
    
    //DIE

    bool ExecuteLuaScript(void* L, const char* script, const char* name)
{
    if (!L || !luaL_loadbufferx_Ptr || !lua_pcall_Ptr) return false;

    int load_result = luaL_loadbufferx_Ptr(L, script, strlen(script), name, "t");
    if (load_result != 0)
    {
        if (lua_tostring_Ptr)
        {
            const char* err = lua_tostring_Ptr(L, -1);
            LOGE("[Lua] Load error in %s: %s", name, err ? err : "(no message)");
        }
        else
        {
            LOGE("[Lua] Load error in %s (no message)", name);
        }
        return false;
    }

    int exec_result = lua_pcall_Ptr(L, 0, 0, 0);
    if (exec_result != 0)
    {
        if (lua_tostring_Ptr)
        {
            const char* err = lua_tostring_Ptr(L, -1);
            LOGE("[Lua] Runtime error in %s: %s", name, err ? err : "(no message)");
        }
        else
        {
            LOGE("[Lua] Runtime error in %s (no message)", name);
        }
        return false;
    }

    LOGI("[Lua] Executed script: %s", name);
    return true;
}
    void Initialize()
    {
        static bool initialized = false;
        if (initialized) return;
        if (!luaL_loadbufferx_Ptr || !lua_pcall_Ptr)
        {
            LOGE("[Lua] Lua function pointers not initialized");
            return;
        }        
        initialized = true;
        LOGI("[Lua] Initializing Lua injection system");
        LOGI("[Lua] Initialization complete");
    }
}
