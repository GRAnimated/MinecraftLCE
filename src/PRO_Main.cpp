#include <new>

#include "nn/os/os_MutexTypes.h"
#include "Minecraft.Client/CInput.h"
#include "Minecraft.Client/Compression.h"
#include "Minecraft.Client/renderer/Renderer.h"
#include "nn/fs.h"
#include "nn/nifm.h"
#include "nn/oe.h"
#include "nn/os.h"
#include "nn/time.h"

static nn::oe::PerformanceMode PERFORMANCE_MODE;
static nn::os::MessageQueueType* MESSAGE_QUEUE;
static u64* MESSAGE_QUEUE_BUFFER;
static nn::os::MutexType* MAIN_MUTEX;

void InitializeCriticalSection(nn::os::MutexType* mutex) {
    nn::os::InitializeMutex(mutex, 1LL, 0LL);
    nn::os::LockMutex(mutex);
    nn::os::UnlockMutex(mutex);
}

void sub_7100607FBC(nn::os::MutexType* mutex) {
    InitializeCriticalSection(mutex);
}

// NON_MATCHING: Incomplete
extern "C" void nnMain() {
    sub_7100607FBC(MAIN_MUTEX);
    nn::oe::SetPerformanceConfiguration(nn::oe::PerformanceMode_Normal, 0x20004);
    PERFORMANCE_MODE = nn::oe::GetPerformanceMode();
    nn::oe::SetPerformanceModeChangedNotificationEnabled(true);
    nn::oe::SetFocusHandlingMode(0);
    nn::oe::SetResumeNotificationEnabled(true);
    // nullsub_833();
    nn::nifm::Initialize();
    nn::time::Initialize();
    nn::oe::Initialize();

    size_t cacheSize;
    nn::fs::QueryMountRomCacheSize(&cacheSize);
    void* cache = operator new[](cacheSize, std::nothrow_t());
    nn::fs::MountRom("GAME", cache, cacheSize);
    nn::os::InitializeMessageQueue(MESSAGE_QUEUE, MESSAGE_QUEUE_BUFFER, 3);

    // v9 = InitializeCriticalSection(&stru_71017C1830);
    // sub_71007E0F98(v9);

    Compression::CreateNewThreadStorage();
    Renderer::sInstance->Initialise();
    // CProfile::sInstance->Initialise();
    CInput::sInstance->Initialise(1, 61, 23);

    // ...
}
