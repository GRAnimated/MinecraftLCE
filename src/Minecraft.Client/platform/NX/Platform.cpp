#include "Minecraft.Client/platform/NX/Platform.h"

#include "Platform.h"
#include <cstdlib>
#include <cstring>

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

void PIXBeginNamedEvent(float, const char*, ...) {}
void PIXEndNamedEvent() {}

void EnterCriticalSection(nn::os::MutexType* mutex) {
    nn::os::LockMutex(mutex);
}

void LeaveCriticalSection(nn::os::MutexType* mutex) {
    nn::os::UnlockMutex(mutex);
}

// XMemCompress/LZX Functions
// Stubbed on Nintendo Switch Edition
int XMemCreateCompressionContext(_XMEMCODEC_TYPE type, const void* param_2, unsigned int param_3,
                                 void** param_4) {
    return 0;
}

int XMemCreateDecompressionContext(_XMEMCODEC_TYPE type, const void* param_2, unsigned int param_3,
                                   void** param_4) {
    return 0;
}

void XMemDestroyCompressionContext(void* ctxt) {
    return;
}

void XMemDestroyDecompressionContext(void* ctxt) {
    return;
}
