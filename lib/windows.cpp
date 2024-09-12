#include "windows.h"

#include <cstdlib>
#include <cstring>

// NON_MATCHING
void* XPhysicalAlloc(unsigned long a1, unsigned long a2, unsigned long a3, unsigned int a4) {
    return malloc(a1);
}

void XMemSet128(void* ptr, int a2, unsigned int a3) {
    memset(ptr, a2, a3);
}

void XPhysicalFree(void* ptr) {
    free(ptr);
}

void MemSect(int) {}
