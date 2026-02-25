#include "net/minecraft/world/level/storage/data/SparseDataStorage.h"

// NON_MATCHING | Difference: 1830
// The pseudocode is the same as CompressedBlockStorage, what's up with this?
void SparseDataStorage::tick() {
    unsigned int idx = (sStackLength + 1) % 3;
    XLockFreeStack<unsigned char>* stack = &sStack[idx];

    while (true) {
        unsigned char* p = stack->Pop();
        if (!p)
            break;

        free(p, 0);
    }

    sStackLength = idx;
}
