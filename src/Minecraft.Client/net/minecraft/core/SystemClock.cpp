#include "net/minecraft/core/System.h"
#include <nn/os.h>
#include <nn/time.h>

// The bundled SDK header aliases Tick to u64. Bind the ABI-compatible
// eight-byte argument to the real SDK import's value-class mangled name.
extern nn::TimeSpan convertSystemTick(nn::os::Tick) asm("_ZN2nn2os17ConvertToTimeSpanENS0_4TickE");

JavaLong System::currentRealTimeMillis() {
    nn::time::PosixTime t;
    nn::time::StandardUserSystemClock::GetCurrentTime(&t);
    return t.time;
}

JavaLong System::currentUnixEpochTimeSeconds() {
    return currentRealTimeMillis() / 1000;
}

JavaLong System::processTime(ETimeGranularity granularity) {
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

JavaLong System::processTimeInSeconds() {
    return processTime(MILLISECONDS) / 1000;
}
JavaLong System::processTimeInMilliSecs() {
    return processTime(MILLISECONDS);
}
JavaLong System::processTimeInMicroSecs() {
    return processTime(MICROSECONDS);
}
JavaLong System::processTimeInNanoSecs() {
    return processTime(NANOSECONDS);
}
