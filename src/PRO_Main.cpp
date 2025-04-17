#include <new>

#include "Minecraft.Client/C4JThreadImpl.h"
#include "Minecraft.Client/CInput.h"
#include "Minecraft.Client/Compression.h"
#include "Minecraft.Client/renderer/Renderer.h"
#include "Minecraft.Client/GameSettings.h"
#include "nn/fs.h"
#include "nn/nifm.h"
#include "nn/oe.h"
#include "nn/os.h"
#include "nn/time.h"
#include "Minecraft.Client/CProfile.h"

static nn::oe::PerformanceMode PERFORMANCE_MODE;
static nn::os::MessageQueueType* MESSAGE_QUEUE;
static u64* MESSAGE_QUEUE_BUFFER;
static nn::os::MutexType* MAIN_MUTEX;
static nn::os::MutexType* MAIN_MUTEX2;

void InitializeCriticalSection(nn::os::MutexType* mutex) {
    nn::os::InitializeMutex(mutex, 1, 0);
    nn::os::LockMutex(mutex);
    nn::os::UnlockMutex(mutex);
}

void sub_7100607FBC(){
    InitializeCriticalSection(MAIN_MUTEX);
}

void DefineActions(){
    GameSettings::SetDefaultActionMapping(0, 0, 2);
    GameSettings::SetDefaultActionMapping(0, 1, 12);
    GameSettings::SetDefaultActionMapping(0, 2, 11);
    GameSettings::SetDefaultActionMapping(0, 3, 10);
    GameSettings::SetDefaultActionMapping(0, 4, 9);
    GameSettings::SetDefaultActionMapping(0, 5, 4);
    GameSettings::SetDefaultActionMapping(0, 6, 1);
    GameSettings::SetDefaultActionMapping(0, 7, 13);
    GameSettings::SetDefaultActionMapping(0, 8, 3);
    GameSettings::SetDefaultActionMapping(0, 9, 14);
    GameSettings::SetDefaultActionMapping(0, 10, 5);
    GameSettings::SetDefaultActionMapping(0, 11, 6);
    GameSettings::SetDefaultActionMapping(0, 12, 7);
    GameSettings::SetDefaultActionMapping(0, 13, 8);
    GameSettings::SetDefaultActionMapping(0, 14, 0);
    GameSettings::SetDefaultActionMapping(0, 15, 0);
    GameSettings::SetDefaultActionMapping(0, 16, 10);
    GameSettings::SetDefaultActionMapping(0, 17, 9);
    GameSettings::SetDefaultActionMapping(0, 18, 11);
    GameSettings::SetDefaultActionMapping(0, 19, 1);
    GameSettings::SetDefaultActionMapping(0, 20, 3);
    GameSettings::SetDefaultActionMapping(0, 21, 1);
    GameSettings::SetDefaultActionMapping(0, 22, 3);
    GameSettings::SetDefaultActionMapping(0, 23, 1);
    GameSettings::SetDefaultActionMapping(0, 24, 4);
    GameSettings::SetDefaultActionMapping(1, 0, 9);
    GameSettings::SetDefaultActionMapping(1, 1, 11);
    GameSettings::SetDefaultActionMapping(1, 2, 12);
    GameSettings::SetDefaultActionMapping(1, 3, 5);
    GameSettings::SetDefaultActionMapping(1, 4, 6);
    GameSettings::SetDefaultActionMapping(1, 5, 4);
    GameSettings::SetDefaultActionMapping(1, 6, 1);
    GameSettings::SetDefaultActionMapping(1, 7, 14);
    GameSettings::SetDefaultActionMapping(1, 8, 3);
    GameSettings::SetDefaultActionMapping(1, 9, 10);
    GameSettings::SetDefaultActionMapping(1, 10, 5);
    GameSettings::SetDefaultActionMapping(1, 11, 6);
    GameSettings::SetDefaultActionMapping(1, 12, 7);
    GameSettings::SetDefaultActionMapping(1, 13, 8);
    GameSettings::SetDefaultActionMapping(1, 14, 0);
    GameSettings::SetDefaultActionMapping(1, 15, 0);
    GameSettings::SetDefaultActionMapping(1, 16, 6);
    GameSettings::SetDefaultActionMapping(1, 17, 6);
    GameSettings::SetDefaultActionMapping(1, 18, 12);
    GameSettings::SetDefaultActionMapping(1, 19, 1);
    GameSettings::SetDefaultActionMapping(1, 20, 3);
    GameSettings::SetDefaultActionMapping(1, 21, 1);
    GameSettings::SetDefaultActionMapping(1, 22, 3);
    GameSettings::SetDefaultActionMapping(1, 23, 1);
    GameSettings::SetDefaultActionMapping(1, 24, 4);
    GameSettings::SetDefaultActionMapping(2, 0, 12);
    GameSettings::SetDefaultActionMapping(2, 1, 11);
    GameSettings::SetDefaultActionMapping(2, 2, 2);
    GameSettings::SetDefaultActionMapping(2, 3, 5);
    GameSettings::SetDefaultActionMapping(2, 4, 6);
    GameSettings::SetDefaultActionMapping(2, 5, 4);
    GameSettings::SetDefaultActionMapping(2, 6, 1);
    GameSettings::SetDefaultActionMapping(2, 7, 10);
    GameSettings::SetDefaultActionMapping(2, 8, 3);
    GameSettings::SetDefaultActionMapping(2, 9, 14);
    GameSettings::SetDefaultActionMapping(2, 10, 5);
    GameSettings::SetDefaultActionMapping(2, 11, 6);
    GameSettings::SetDefaultActionMapping(2, 12, 7);
    GameSettings::SetDefaultActionMapping(2, 13, 8);
    GameSettings::SetDefaultActionMapping(2, 14, 0);
    GameSettings::SetDefaultActionMapping(2, 15, 0);
    GameSettings::SetDefaultActionMapping(2, 16, 5);
    GameSettings::SetDefaultActionMapping(2, 17, 6);
    GameSettings::SetDefaultActionMapping(2, 18, 2);
    GameSettings::SetDefaultActionMapping(2, 19, 1);
    GameSettings::SetDefaultActionMapping(2, 20, 3);
    GameSettings::SetDefaultActionMapping(2, 21, 1);
    GameSettings::SetDefaultActionMapping(2, 22, 3);
    GameSettings::SetDefaultActionMapping(2, 23, 1);
    GameSettings::SetDefaultActionMapping(2, 24, 4);

    for(int i = 0; i != 4; ++i){
        if(CInput::sInstance->IsCircleCrossSwapped()){
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 0, 1);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 20, 1);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 1, 2);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 21, 2);
        }else{
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 0, 2);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 20, 2);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 1, 1);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 21, 1);
        }
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 2, 4);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 3, 8);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 4, 0x200400);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 5, 0x100800);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 7, 0x9000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 6, 0x6000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 8, 0x800000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 9, 0x400000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 10, 64);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 11, 128);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 18, 16);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 19, 32);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 14, 0x20000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 15, 0x10000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 16, 0x80000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 17, 0x40000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 32, 2);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 24, 0x200000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 25, 0x100000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 26, 0x8000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 27, 0x4000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 28, 0x80000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 29, 0x40000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 30, 0x20000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 31, 0x10000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 33, 0x800000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 34, 0x400000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 36, 64);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 35, 128);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 37, 8);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 22, 16);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 38, 1);

        if(i){
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 39, 256);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 41, 512);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 12, 512);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 13, 256);
        }else{
            CInput::sInstance->SetGameControllerTypeJoypadMaps(0, 39, 2048);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(0, 41, 1024);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(0, 12, 1024);
            CInput::sInstance->SetGameControllerTypeJoypadMaps(0, 13, 2048);
        }

        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 40, 4);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 23, 0x20);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 42, 0x1000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 43, 0x2000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 44, 0x400);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 45, 0x800);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 57, 0x1000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 58, 0x2000);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 59, 0x400);
        CInput::sInstance->SetGameControllerTypeJoypadMaps(i, 60, 0x800);
    }
}

// NON_MATCHING: Incomplete
extern "C" void nnMain() {
    sub_7100607FBC();
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

    InitializeCriticalSection(MAIN_MUTEX2);
    C4JThreadImpl::SetMainThreadID();
    

    Compression::CreateNewThreadStorage();
    Renderer::sInstance->Initialise();
    CProfile::sInstance->AwardManagerOnCreate();
    CInput::sInstance->Initialise(1, 61, 23);

    
}
