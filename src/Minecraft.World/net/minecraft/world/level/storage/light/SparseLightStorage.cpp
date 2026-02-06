#include "net/minecraft/world/level/storage/light/SparseLightStorage.h"

// NON_MATCHING | Difference: 2475
// The pseudocode is the same as CompressedBlockStorage, what's up with this?
void SparseLightStorage::tick() {
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
