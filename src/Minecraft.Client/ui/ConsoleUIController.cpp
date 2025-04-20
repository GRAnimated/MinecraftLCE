#include "types.h"
#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/ui/ConsoleUIController.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.Core/System.h"
#include <string>

// NON_MATCHING: not finished
ConsoleUIController::ConsoleUIController() {
    qword_71017BE950 = nullptr;
    this->qword8 = 0LL;
    this->qword13570 = 0LL;
    this->byte13598 = 0;
    this->byte418 = 0;
    this->qword420 = 0LL;
    this->qword428 = 0LL;
    this->qword430 = 0LL;
    this->qword438 = 0LL;
    this->qword410 = 0LL;
    this->byte419 = 1;
    InitializeCriticalSection(&mMutex4);
    this->mScreenWidth = 1280.0f;
    this->mScreenHeight = 720.0f;
    this->byte41A = 0;
    this->byte3E0 = 0;
    this->qword13420 = 0LL;
    this->qword13428 = 0LL;
    this->qword13430 = 0LL;
    this->qword13438 = 0LL;
    this->qword13440 = 0LL;
    this->qword13448 = 0LL;
    this->qword13450 = 0LL;
    this->qword13458 = 0LL;
    this->qword13460 = 0LL;
    this->qword13468 = 0LL;
    this->qword13470 = 0LL;
    this->qword13478 = 0LL;
    this->qword13480 = 0LL;
    this->qword13488 = 0LL;
    this->qword13490 = 0LL;
    this->qword13498 = 0LL;
    this->qword134A0 = 0LL;
    this->qword134A8 = 0LL;
    this->qword134B0 = 0LL;
    this->qword134B8 = 0LL;
    this->qword134C0 = 0LL;
    this->qword134C8 = 0LL;

    this->byte134E8 = 0;
    this->byte134E9 = 0;
    this->byte134EA = 0;
    this->byte134EB = 0;
    this->byte134EC = 0;
    this->dword134F0 = 0;
    this->dword134F8 = 0;
    this->byte134FC = 0;
    this->cipa = 0;
    this->dword1359C = 0;
    this->qword135A0 = 0LL;
    InitializeCriticalSection(&this->mMutex1);
    InitializeCriticalSection(&this->mMutex2);
    InitializeCriticalSection(&this->mMutex6);
    InitializeCriticalSection(&this->mMutex5);
    InitializeCriticalSection(&this->mMutex3);
    this->byte1356C = 0;
    this->byte1340C = 0;
    this->byte13418 = 0;
    this->qword13410 = 0LL;
    this->qword13600 = 0LL;

    this->dword440 = 0;
}

arrayWithLength<uchar> ConsoleUIController::getMovieData(std::wstring const& name) {
    long v4 = System::processTimeInMilliSecs() + 60000;

    if (auto search = mCachedMovieDatas.find(name); search != mCachedMovieDatas.end()) {
        search->second.time = v4;
        return search->second;
    } else {
        arrayWithLength<uchar> cipa = CConsoleMinecraftApp::sInstance.getArchiveFile(name, false);
        _CachedMovieData temp;
        temp.data = cipa.data;
        temp.length = cipa.length;
        temp.time = v4;
        mCachedMovieDatas[name] = temp;
        return cipa;
    }
}