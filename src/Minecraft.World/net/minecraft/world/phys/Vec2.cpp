#include "net/minecraft/world/phys/Vec2.h"

DEFINE_THREAD_STORAGE(phys::Vec2, 1024)

phys::Vec2* phys::Vec2::newTemp(float x, float y) {
    ThreadStorage* storage = static_cast<ThreadStorage*>(TlsGetValue(sThreadStorageIndex));
    Vec2* result = &storage->m_storage[storage->m_unk];
    result->m_x = x;
    result->m_y = y;
    storage->m_unk = (storage->m_unk + 1) & 0x3ff;
    return result;
}
