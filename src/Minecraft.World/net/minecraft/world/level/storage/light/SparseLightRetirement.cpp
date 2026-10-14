#include "XLockFreeStack.h"
#include "net/minecraft/world/level/storage/light/SparseLightStorage.h"

// Inferred names for the globals at 0x71017a4410 and 0x71017a4418.
int SparseLightStorage::sRetirementSlot;
XLockFreeStack<unsigned char> SparseLightStorage::sRetired[3];

void SparseLightStorage::staticCtor() {
    sRetired[0].doSomething();
    sRetired[1].doSomething();
    sRetired[2].doSomething();
}

void SparseLightStorage::retire(unsigned char* buffer) {
    sRetired[sRetirementSlot].Push(buffer);
}

void SparseLightStorage::tick() {
    XLockFreeStack<unsigned char>* stack = &sRetired[(sRetirementSlot + 1) % 3];
    unsigned char* buffer;
    do {
        buffer = stack->Pop();
        freeBuffer(buffer, 0);
    } while (buffer);
    sRetirementSlot = (sRetirementSlot + 1) % 3;
}

#include "NX/Platform.h"
#include <cstdlib>
#include <cstring>

void sparseLightMemSet(void*, int, std::size_t);

void SparseLightStorage::expandLayers(std::vector<int>& layers) {
    for (;;) {
        unsigned long long packed = __atomic_load_n(&m_packed, __ATOMIC_SEQ_CST);
        unsigned char* old = reinterpret_cast<unsigned char*>(packed & 0x0000ffffffffffffULL);
        unsigned int oldCount = packed >> 48;
        unsigned long long newCount = oldCount;
        for (auto layer = layers.begin(); layer != layers.end();) {
            if (static_cast<signed char>(old[*layer]) >= 0) {
                layers.erase(layer);
            } else {
                ++layer;
                newCount = static_cast<unsigned int>(newCount) + 1;
            }
        }
        unsigned char* buffer = allocate(newCount * 128 + 128);
        XMemCpy(buffer, old, oldCount * 128 + 128);
        int slab = oldCount;
        for (auto layer = layers.begin(); layer != layers.end(); ++layer) {
            if (static_cast<signed char>(old[*layer]) < 0) {
                sparseLightMemSet(
                    reinterpret_cast<unsigned char (*)[128]>(buffer)[static_cast<unsigned char>(slab)] + 128,
                    old[*layer] == 0x81 ? 255 : 0, 128);
                buffer[*layer] = slab;
                ++slab;
            }
        }
        unsigned long long replacement
            = (reinterpret_cast<unsigned long long>(buffer) & 0x0000ffffffffffffULL)
              | (static_cast<unsigned long long>(newCount) << 48);
        if (__atomic_compare_exchange_n(&m_packed, &packed, replacement, true, __ATOMIC_SEQ_CST,
                                        __ATOMIC_SEQ_CST)) {
            retire(old);
            return;
        }
        // The original frees losing allocations directly, without subtracting accounting.
        std::free(buffer);
    }
}
