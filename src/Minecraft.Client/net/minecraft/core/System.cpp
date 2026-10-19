#include "net/minecraft/core/System.h"

#include <cstdint>

#include <nn/os.h>
#include <nn/time.h>

#include "nn/os/os_Mutex.h"

void InitializeCriticalSection(nn::os::MutexType* mutex) {
    nn::os::InitializeMutex(mutex, 1, 0);
    nn::os::LockMutex(mutex);
    nn::os::UnlockMutex(mutex);
}

void InitializeCriticalSectionAndSpinCount(nn::os::MutexType* mutexType, unsigned long spinCount) {
    InitializeCriticalSection(mutexType);
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

// NON_MATCHING | score: 260 (lower is better)
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

/** The bundled SDK header aliases Tick to u64. Bind the ABI-compatible
 * eight-byte argument to the real SDK import's value-class mangled name.
 */
extern nn::TimeSpan convertSystemTick(nn::os::Tick) asm("_ZN2nn2os17ConvertToTimeSpanENS0_4TickE");

long System::currentRealTimeMillis() {
    nn::time::PosixTime t;
    nn::time::StandardUserSystemClock::GetCurrentTime(&t);
    return t.time;
}

long System::currentUnixEpochTimeSeconds() {
    return currentRealTimeMillis() / 1000;
}

long System::processTime(ETimeGranularity granularity) {
    const nn::os::Tick tick = nn::os::GetSystemTick();
    switch (granularity) {
    case NANOSECONDS:
        return convertSystemTick(tick).nanoseconds;
    case MICROSECONDS:
        return static_cast<long>(convertSystemTick(tick).nanoseconds) / 1000;
    case MILLISECONDS:
        return static_cast<long>(convertSystemTick(tick).nanoseconds) / 1000000;
    default:
        return 0;
    }
}

long System::processTimeInSeconds() {
    return processTime(MILLISECONDS) / 1000;
}
long System::processTimeInMilliSecs() {
    return processTime(MILLISECONDS);
}
long System::processTimeInMicroSecs() {
    return processTime(MICROSECONDS);
}
long System::processTimeInNanoSecs() {
    return processTime(NANOSECONDS);
}

/** This is the original position-dependent LCE hash, including 32-bit wraparound.
 */
// NON_MATCHING | score: 605 (lower is better)
size_t javaStringHashCode(const std::wstring& value) {
    std::uint32_t length = static_cast<std::uint32_t>(value.size());
    std::uint64_t last = length - 1;
    std::uint64_t index = 0;
    std::uint32_t remaining = last;
    std::uint32_t result = 0;
    if (length != 0)
        do {
            std::uint32_t character = static_cast<std::uint32_t>(value[index]);
            character = index >= last ? character : (character * 31u) ^ remaining;
            result += character;
            --remaining;
            ++index;
        } while (index != length);
    return result;
}
