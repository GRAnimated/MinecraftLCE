#include "System.h"
#include "nn/os/os_Mutex.h"
#include <nn/time.h>

void InitializeCriticalSection(nn::os::MutexType* mutex) {
    nn::os::InitializeMutex(mutex, 1, 0);
    nn::os::LockMutex(mutex);
    nn::os::UnlockMutex(mutex);
}

long System::currentRealTimeMillis() {
    nn::time::PosixTime t;  // they left uninitialized
    nn::time::StandardUserSystemClock::GetCurrentTime(&t);
    return t.time;
}

long System::currentUnixEpochTimeSeconds() {
    return currentRealTimeMillis() / 1000;
}

long System::processTimeInSeconds() {
    return processTime(MILLISECONDS) / 1000;
}

long System::processTimeInMilliSecs() {
    return processTime(MILLISECONDS);
}

long System::processTimeInNanoSecs() {
    return processTime(NANOSECONDS);
}

void System::ReverseSHORT(short* shart) {
    const short lb = *shart;

    *reinterpret_cast<unsigned char*>(shart) = *shart >> 8;
    *(reinterpret_cast<unsigned char*>(shart) + 1) = lb;
}

void System::ReverseUSHORT(unsigned short* shart) {
    const unsigned short lb = *shart;

    *reinterpret_cast<unsigned char*>(shart) = *shart >> 8;
    *(reinterpret_cast<unsigned char*>(shart) + 1) = lb;
}
void System::ReverseINT(int* v) {
    const int lb = *v;

    *reinterpret_cast<unsigned char*>(v) = *v >> 24;
    *(reinterpret_cast<unsigned char*>(v) + 1) = lb >> 16;
    *(reinterpret_cast<unsigned char*>(v) + 2) = lb >> 8;
    *(reinterpret_cast<unsigned char*>(v) + 3) = lb;
}

void System::ReverseULONG(unsigned int* v) {
    const unsigned int lb = *v;

    *reinterpret_cast<unsigned char*>(v) = *v >> 24;
    *(reinterpret_cast<unsigned char*>(v) + 1) = lb >> 16;
    *(reinterpret_cast<unsigned char*>(v) + 2) = lb >> 8;
    *(reinterpret_cast<unsigned char*>(v) + 3) = lb;
}


// NON_MATCHING | Score 260 (lower is better)
// Not sure but this (along with the others) probably uses some compiler intrinsic
// I had to arrange this using odd then even
void System::ReverseULONGLONG(unsigned long long* v) {
    const unsigned long long lb = *v;

    *reinterpret_cast<unsigned char*>(v) = *v >> 56;
    *(reinterpret_cast<unsigned char*>(v) + 1) = lb >> 48;
    *(reinterpret_cast<unsigned char*>(v) + 3) = lb >> 32;
    *(reinterpret_cast<unsigned char*>(v) + 5) = lb >> 16;
    *(reinterpret_cast<unsigned char*>(v) + 7) = lb;
    *(reinterpret_cast<unsigned char*>(v) + 2) = lb >> 40;
    *(reinterpret_cast<unsigned char*>(v) + 4) = lb >> 24;
    *(reinterpret_cast<unsigned char*>(v) + 6) = lb >> 8;
}

void System::ReverseCHAR16A(char16_t* str, int len) {
    for (int i = 0; i < len; i++)
        System::ReverseUSHORT(reinterpret_cast<unsigned short*>(str + i));
}


