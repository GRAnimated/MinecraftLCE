#include "System.h"
#include "nn/os/os_Mutex.h"

void InitializeCriticalSection(nn::os::MutexType* mutex) {
    nn::os::InitializeMutex(mutex, 1, 0);
    nn::os::LockMutex(mutex);
    nn::os::UnlockMutex(mutex);
}
