#pragma once

// PUBGm BETA - 64bit (4.6.0) SDK by BangJO [Z] DM @isar_hackJO To Buy Tool SDK

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <codecvt>
#include <vector>
#include <cstdint>

namespace SDK
{
template<typename Fn>
		inline Fn GetVFunction(void *thiz, int idx)
		{
			auto VTable = *(void***)(void*)thiz;
			return (Fn)(VTable[idx]);
		}
		
		class UObject;
		
		class FUObjectItem
		{
			public:
			UObject* Object;
			int32_t Flags;
			int32_t ClusterIndex;
			int32_t SerialNumber;
			
			enum class ObjectFlags : int32_t
			{
				None = 0,
				Native = 1 << 25,
				Async = 1 << 26,
				AsyncLoading = 1 << 27,
				Unreachable = 1 << 28,
				PendingKill = 1 << 29,
				RootSet = 1 << 30,
				NoStrongReference = 1 << 31
			};
			inline bool IsUnreachable() const { return Flags & static_cast<int32_t>(ObjectFlags::Unreachable); }
			inline bool IsPendingKill() const { return Flags & static_cast<int32_t>(ObjectFlags::PendingKill); }
		};
		
		class TUObjectArray
		{
			public:
			inline int32_t Num() const { return NumElements; }
			inline UObject* GetByIndex(int32_t index) const { return Objects[index].Object; }
			inline FUObjectItem* GetItemByIndex(int32_t index) const { if (index < NumElements) { return &Objects[index]; }
			return nullptr;
		}
		
		private:
        FUObjectItem* Objects;
        int32_t MaxElements;
        int32_t NumElements;
    };

    class FUObjectArray
    {
		public:
        int32_t ObjFirstGCIndex;
        int32_t ObjLastNonGCIndex;
        int32_t MaxObjectsNotConsideredByGC;
        int32_t OpenForDisregardForGC;
        TUObjectArray ObjObjects;
    };

    template<class T>
    struct TArray
    {
        T* Data;
        int32_t Count;
        int32_t Max;

        inline TArray() : Data(nullptr), Count(0), Max(0) {}
        inline int Num() const { return Count; }
        inline T& operator[](int i) { return Data[i]; }
        inline const T& operator[](int i) const { return Data[i]; }
        inline bool IsValidIndex(int i) const { return i >= 0 && i < Count; }

        void Reserve(int32_t NewMax) {
            if (NewMax > Max) {
                T* NewData = (T*)malloc(NewMax * sizeof(T));
                if (Data) {
                    memcpy(NewData, Data, Count * sizeof(T));
                    free(Data);
                }
                Data = NewData;
                Max = NewMax;
            }
        }

        inline void Add(const T& Element) {
            if (Count >= Max) Reserve(Max == 0 ? 16 : Max * 2);
            Data[Count++] = Element;
        }
    };

    class FNameEntry
    {
		public:
        static const auto NAME_WIDE_MASK = 0x1;
        static const auto NAME_INDEX_SHIFT = 1;

        int32_t Index;
#if defined(__LP64__)
		char pad[0x8];
#else
		char pad[0x4];
#endif
        
        union {
            char AnsiName[1024];
            wchar_t WideName[1024];
        };

        inline const int32_t GetIndex() const { return Index >> NAME_INDEX_SHIFT; }
        inline bool IsWide() const { return Index & NAME_WIDE_MASK; }
        inline const char* GetAnsiName() const { return AnsiName; }
    };

    template<typename ElementType, int32_t MaxTotalElements, int32_t ElementsPerChunk>
    class TStaticIndirectArrayThreadSafeRead
    {
		public:
        inline size_t Num() const { return NumElements; }
        inline bool IsValidIndex(int32_t index) const { return index < NumElements && index >= 0; }
        inline ElementType const* const& operator[](int32_t index) const { return *GetItemPtr(index); }
		
		private:
        inline ElementType const* const* GetItemPtr(int32_t Index) const {
            int32_t ChunkIndex = Index / ElementsPerChunk;
            int32_t WithinChunkIndex = Index % ElementsPerChunk;
            return Chunks[ChunkIndex] + WithinChunkIndex;
        }

        ElementType** Chunks[(MaxTotalElements + ElementsPerChunk - 1) / ElementsPerChunk];
        int32_t NumElements;
        int32_t NumChunks;
    };

    using TNameEntryArray = TStaticIndirectArrayThreadSafeRead<FNameEntry, 2 * 1024 * 1024, 16384>;

    struct FName
    {
        int32_t ComparisonIndex;
        int32_t Number;

        static TNameEntryArray* GNames;
        static inline TNameEntryArray& GetNames() { return *GNames; }
        inline FName() : ComparisonIndex(0), Number(0) {}
        inline FName(int32_t i) : ComparisonIndex(i), Number(0) {}

        FName(const char* nameToFind) : ComparisonIndex(0), Number(0) {
            static std::unordered_map<std::string, int32_t> NameCache;
            
            auto it = NameCache.find(nameToFind);
            if (it != NameCache.end()) {
                ComparisonIndex = it->second;
                return;
            }

            for (int32_t i = 0; i < GetNames().Num(); ++i) {
                if (GetNames().IsValidIndex(i)) {
                    auto entry = GetNames()[i];
                    if (entry && strcmp(entry->GetAnsiName(), nameToFind) == 0) {
                        ComparisonIndex = i;
                        NameCache[nameToFind] = i;
                        return;
                    }
                }
            }
        }

        inline const char* GetName() const {
            if (GetNames().IsValidIndex(ComparisonIndex))
                return GetNames()[ComparisonIndex]->GetAnsiName();
            return "None";
        }
        inline bool operator==(const FName& other) const { return ComparisonIndex == other.ComparisonIndex; }
    };

    struct FString : private TArray<unsigned short>
    {
        inline FString()
        {
        }

        FString(const std::wstring s)
        {
            Max = Count = !s.empty() ? (s.length() * 2) + 1 : 0;
            if (Count)
            {
                Data = (unsigned short *)(s.data());
            }
        }

        FString(const wchar_t *s) : FString(std::wstring(s)) {
        }

        FString(const wchar_t *s, int len) : FString(std::wstring(s, s + len)) {
        }

        FString(const std::string s) {
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
            std::wstring ws = converter.from_bytes(s);

            Max = Count = !ws.empty() ? (ws.length() * 2) + 1 : 0;
            if (Count)
            {
                Data = (unsigned short *)(ws.data());
            }
        }

        FString(const char *s) : FString(std::string(s)) {
        }

        FString(const char *s, int len) : FString(std::string(s, s + len)) {
        }

        inline bool IsValid() const
        {
            return Data != nullptr;
        }

        inline const wchar_t* ToWString() const
        {
            wchar_t *output = new wchar_t[Count + 1];
            for (int i = 0; i < Count; i++) {
                const char16_t uc = Data[i];
                if (uc - 0xd800u >= 2048u) {
                    output[i] = uc;
                } else {
                    if ((uc & 0xfffffc00) == 0xd800 && (uc & 0xfffffc00) == 0xdc00)
                        output[i] = (uc << 10) + Data[i] - 0x35fdc00;
                    else
                        output[i] = L'?';
                }
            }

            output[Count] = 0;
            return output;
        }

        inline const char* ToString() const
        {
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
            return convert.to_bytes(std::u16string(Data, Data + Count)).c_str();
        }
    };
	
	template<class TEnum>
	class TEnumAsByte
	{
		public:
		inline TEnumAsByte() {}
		inline TEnumAsByte(TEnum _value) : value(static_cast<uint8_t>(_value)) {}
		explicit inline TEnumAsByte(int32_t _value) : value(static_cast<uint8_t>(_value)) {}
		explicit inline TEnumAsByte(uint8_t _value) : value(_value) {}
		inline operator TEnum() const { return (TEnum)value; }
		inline TEnum GetValue() const { return (TEnum)value; }
		private:
		uint8_t value;
	};
	
	class FScriptInterface
	{
		private:
        UObject* ObjectPointer;
        void* InterfacePointer;
		public:
        inline UObject* GetObject() const { return ObjectPointer; }
        inline UObject*& GetObjectRef() { return ObjectPointer; }
        inline void* GetInterface() const { return ObjectPointer != nullptr ? InterfacePointer : nullptr; }
    };

    template<class InterfaceType>
    class TScriptInterface : public FScriptInterface
	{
		public:
        inline InterfaceType* operator->() const { return (InterfaceType*)GetInterface(); }
        inline InterfaceType& operator*() const { return *((InterfaceType*)GetInterface()); }
        inline operator bool() const { return GetInterface() != nullptr; }
    };

    struct FWeakObjectPtr {
        int32_t ObjectIndex;
        int32_t ObjectSerialNumber;
        UObject* Get() const;
        inline bool SerialNumbersMatch(FUObjectItem* ObjectItem) const { return ObjectItem->SerialNumber == ObjectSerialNumber; }
        bool IsValid() const;
    };

    template<class T>
    struct TWeakObjectPtr : private FWeakObjectPtr {
        inline T* Get() const { return (T*)FWeakObjectPtr::Get(); }
        inline T* operator->() const { return Get(); }
    };

    struct FText
    {
        void* Data;
        void* SharedBuffer;
        uint32_t Flags;
        uint32_t Pad;
    };

    struct FScriptDelegate
    {
        void* Object;
        FName FunctionName;
    };

    struct FScriptMulticastDelegate
    {
        TArray<FScriptDelegate> InvocationList;
    };

	template<typename Key, typename Value>
	class TMap
	{
		private:
		struct FMapEntry 
		{
			Key   KeyData;
			Value ValueData;
		};
		TArray<FMapEntry> Data;
		void* HashIndices;
		int32_t HashSize;
		uint8_t RestPad[sizeof(void*) * 6 + 4]; 
		public:
		inline int Num() const { return Data.Num();}
		inline bool IsValid() const { return Data.Num() > 0; }
	};
	
	template<class T, class TBASE>
	class TAutoPointer : public TBASE
	{
		public:
		inline operator T*() const { return TBASE::Get(); }
		inline operator const T*() const { return (const T*)TBASE::Get(); }
		explicit inline operator bool() const { return TBASE::Get() != nullptr; }
	};
	
	template<class T>
	class TAutoWeakObjectPtr : public TAutoPointer<T, TWeakObjectPtr<T>> {};
	
	template<typename TObjectID>
	class TPersistentObjectPtr
	{
		public:
		FWeakObjectPtr WeakPtr;
		int32_t TagAtLastTest;
		TObjectID ObjectID;
	};
	
	struct FStringAssetReference_ {};
	class FAssetPtr : public TPersistentObjectPtr<FStringAssetReference_> {};
	template<typename ObjectType>
	class TAssetPtr : FAssetPtr {};
	struct FUniqueObjectGuid_ {};
	class FLazyObjectPtr : public TPersistentObjectPtr<FUniqueObjectGuid_> {};
	template<typename ObjectType>
	class TLazyObjectPtr : FLazyObjectPtr {};
}

