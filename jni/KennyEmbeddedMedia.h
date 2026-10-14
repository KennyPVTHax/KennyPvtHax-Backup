#pragma once
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <vector>
namespace KennyEmbedded {
struct Entry {const char* id;const uint8_t* data;size_t size;const char* sha256;};
#ifdef KPH_EMBEDDED_MEDIA
const Entry* Lookup(const char* id);
#else
inline const Entry* Lookup(const char*) {return nullptr;}
#endif
inline bool Read(const char* id,size_t limit,std::vector<uint8_t>& bytes) {
    const auto* e=Lookup(id);if(!e||!e->size||e->size>limit)return false;
    bytes.assign(e->data,e->data+e->size);return true;
}
}
