#include "net/minecraft/world/level/newbiome/layer/IntCache.h"

#include "NX/Platform.h"

unsigned int IntCache::sThreadStorageIndex = TlsAlloc();

namespace {
void freeArrays(std::vector<arrayWithLength<int>>& arrays) {
    for (const auto& array : arrays)
        delete[] array.m_data;
    arrays.clear();
}

IntCache::ThreadStorage* storage() {
    auto* result = static_cast<IntCache::ThreadStorage*>(TlsGetValue(IntCache::sThreadStorageIndex));
    return result;
}

void trimOne(std::vector<arrayWithLength<int>>& arrays) {
    if (!arrays.empty()) {
        delete[] arrays.back().m_data;
        arrays.pop_back();
    }
}
}  // namespace

IntCache::ThreadStorage::ThreadStorage() = default;

IntCache::ThreadStorage::~ThreadStorage() {
    freeArrays(m_freeSmall);
    freeArrays(m_activeSmall);
    freeArrays(m_freeLarge);
    freeArrays(m_activeLarge);
    freeArrays(m_retiredLarge);
}

void IntCache::CreateNewThreadStorage() {
    auto* current = new ThreadStorage();
    TlsSetValue(sThreadStorageIndex, current);
    current->m_maxSize = 256;
}

void IntCache::ReleaseThreadStorage() {
    auto* current = static_cast<ThreadStorage*>(TlsGetValue(sThreadStorageIndex));
    delete current;
}

arrayWithLength<int> IntCache::allocate(int size) {
    ThreadStorage* current = storage();
    const bool small = size <= 256;
    if (!small && size > current->m_maxSize) {
        current->m_maxSize = size;
        // Existing borrowers keep their views until releaseAll or Reset.
        current->m_retiredLarge.insert(current->m_retiredLarge.end(), current->m_freeLarge.begin(),
                                       current->m_freeLarge.end());
        current->m_retiredLarge.insert(current->m_retiredLarge.end(), current->m_activeLarge.begin(),
                                       current->m_activeLarge.end());
        current->m_freeLarge.clear();
        current->m_activeLarge.clear();
    }
    auto& free = small ? current->m_freeSmall : current->m_freeLarge;
    auto& active = small ? current->m_activeSmall : current->m_activeLarge;
    arrayWithLength<int> result;
    if (free.empty()) {
        result = arrayWithLength<int>(small ? 256 : current->m_maxSize, false);
    } else {
        result = free.back();
        free.pop_back();
    }
    active.push_back(result);
    return result;
}

void IntCache::releaseAll() {
    ThreadStorage* current = storage();
    freeArrays(current->m_retiredLarge);
    trimOne(current->m_freeLarge);
    trimOne(current->m_freeSmall);
    current->m_freeLarge.insert(current->m_freeLarge.end(), current->m_activeLarge.begin(),
                                current->m_activeLarge.end());
    current->m_freeSmall.insert(current->m_freeSmall.end(), current->m_activeSmall.begin(),
                                current->m_activeSmall.end());
    current->m_activeLarge.clear();
    current->m_activeSmall.clear();
}

void IntCache::Reset() {
    ThreadStorage* current = storage();
    current->m_maxSize = 256;
    freeArrays(current->m_activeLarge);
    freeArrays(current->m_freeLarge);
    freeArrays(current->m_activeSmall);
    freeArrays(current->m_freeSmall);
    freeArrays(current->m_retiredLarge);
}
