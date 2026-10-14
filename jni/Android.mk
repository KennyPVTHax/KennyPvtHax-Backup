LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libdobby
LOCAL_SRC_FILES := Dobby/libraries/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/Dobby/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcurl
LOCAL_SRC_FILES := curl/curl-android-$(TARGET_ARCH_ABI)/lib/libcurl.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/curl/include
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libssl
LOCAL_SRC_FILES := curl/openssl-android-$(TARGET_ARCH_ABI)/lib/libssl.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcrypto
LOCAL_SRC_FILES := curl/openssl-android-$(TARGET_ARCH_ABI)/lib/libcrypto.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := shadowhook
LOCAL_SRC_FILES := shadowhook/libshadowhook.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/shadowhook/
include $(PREBUILT_STATIC_LIBRARY)


PREBUILT_DIR := prebuilt/fuck

include $(CLEAR_VARS)
LOCAL_MODULE := tools
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Tools.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := KittyMemory
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/KittyMemory.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := MemoryPatch
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/MemoryPatch.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := MemoryBackup
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/MemoryBackup.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := KittyUtils
LOCAL_SRC_FILES := $(PREBUILT_DIR)/KittyMemory/KittyUtils.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := hde64
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/hde64.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SubstrateHook
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/SubstrateHook.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SubstrateDebug
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/SubstrateDebug.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := SubstratePosixMemory
LOCAL_SRC_FILES := $(PREBUILT_DIR)/Substrate/SubstratePosixMemory.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := base64
LOCAL_SRC_FILES := $(PREBUILT_DIR)/base64/base64.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ElfImg
LOCAL_SRC_FILES := $(PREBUILT_DIR)/ElfImg.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := fake_dlfcn
LOCAL_SRC_FILES := $(PREBUILT_DIR)/fake_dlfcn.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := android_native_app_glue
LOCAL_SRC_FILES := $(PREBUILT_DIR)/android_native_app_glue.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := plthook_elf
LOCAL_SRC_FILES := $(PREBUILT_DIR)/plthook_elf.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := And64InlineHook
LOCAL_SRC_FILES := $(PREBUILT_DIR)/And64InlineHook/And64InlineHook.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := Anoy
                   
LOCAL_CFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE := arm

LOCAL_C_INCLUDES += $(LOCAL_PATH)/curl/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/curl/openssl-android-$(TARGET_ARCH_ABI)/include

LOCAL_SRC_FILES :=  main.cpp \
        SDK/PUBGM_Basic.cpp \
        SDK/PUBGM_Basic_functions.cpp \
        SDK/PUBGM_CoreUObject_functions.cpp \
        SDK/PUBGM_Engine_functions.cpp \
        SDK/PUBGM_ShadowTrackerExtra_functions.cpp \
        SDK/PUBGM_Client_functions.cpp \
        ImguiPP.cpp \
        imgui/imgui.cpp    \
        imgui/imgui_draw.cpp\
        imgui/imgui_demo.cpp \
        imgui/imgui_tables.cpp \
        imgui/imgui_widgets.cpp \
        imgui/backends/imgui_impl_android.cpp \
        imgui/backends/imgui_impl_opengl3.cpp \

LOCAL_CPP_FEATURES := exceptions

# Diagnostic builds keep matching unstripped obj/ symbols locally. ndk-build
# still installs a stripped release library at libs/arm64-v8a/libAnoy.so.
ifeq ($(KPH_DIAGNOSTICS),1)
LOCAL_CPPFLAGS := $(filter-out -s,$(LOCAL_CPPFLAGS)) -g -fno-omit-frame-pointer
LOCAL_LDFLAGS := -Wl,--gc-sections -llog
endif
ifneq ($(KPH_BUILD_ID),)
LOCAL_CPPFLAGS += -DKPH_BUILD_ID=\"$(KPH_BUILD_ID)\"
endif
ifeq ($(KPH_ISOLATION),no_audio)
LOCAL_CPPFLAGS += -DKPH_DIAGNOSTIC_NO_AUDIO=1
endif
ifeq ($(KPH_ISOLATION),no_artwork)
LOCAL_CPPFLAGS += -DKPH_DIAGNOSTIC_NO_ARTWORK=1
endif
ifeq ($(KPH_ISOLATION),no_preferences)
LOCAL_CPPFLAGS += -DKPH_DIAGNOSTIC_NO_PREFERENCES=1
endif
ifeq ($(KPH_ISOLATION),classic)
LOCAL_CPPFLAGS += -DKPH_DIAGNOSTIC_CLASSIC=1
endif
ifeq ($(KPH_ISOLATION),no_menu)
LOCAL_CPPFLAGS += -DKPH_DIAGNOSTIC_NO_MENU=1
endif

LOCAL_LDLIBS := -llog -landroid -lOpenSLES -lEGL -lGLESv2 -lGLESv3 -lGLESv1_CM -lz -lmediandk

LOCAL_STATIC_LIBRARIES := libdobby libcurl libssl libcrypto And64InlineHook ElfImg fake_dlfcn android_native_app_glue plthook_elf tools base64 SubstrateDebug SubstrateHook hde64 SubstratePosixMemory KittyMemory MemoryPatch MemoryBackup KittyUtils shadowhook

include $(BUILD_SHARED_LIBRARY)
