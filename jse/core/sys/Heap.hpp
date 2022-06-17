#ifndef JSE_HEAP_H
#define JSE_HEAP_H
//#undef new
//#undef delete

#include "core/io/Logger.hpp"

#define __jse_align16(x) (((x) + 15) & ~15)

namespace jse {
    namespace core {
        namespace sys {
            void* Mem_Alloc16(const size_t size);
            void Mem_Free16(void* ptr);
            void* Mem_ClearedAlloc(const size_t size);

            inline void* Mem_Alloc(const size_t size) { return Mem_Alloc16(size); }
            inline void Mem_Free(void* ptr) { Mem_Free16(ptr); }
        }
    }
}
/*
void* operator new(size_t s)
{
    return jse::Mem_Alloc(s);
}

void operator delete(void* p) noexcept
{
    jse::Mem_Free(p);
}

void* operator new[](size_t s)
{
    return jse::Mem_Alloc(s);
}

void operator delete[](void* p) noexcept
{
    jse::Mem_Free(p);
}
*/
#endif
