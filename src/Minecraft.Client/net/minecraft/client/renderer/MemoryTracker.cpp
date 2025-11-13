#include "net/minecraft/client/renderer/MemoryTracker.h"

// NON_MATCHING implement, this is an hack to match stuff
void* MemoryTracker::createIntBuffer(int size) {
    return (void*)(long)size;  // yea i know. this is a stub anyway lol
}
