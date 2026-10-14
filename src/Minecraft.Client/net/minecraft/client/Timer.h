#pragma once

#include <cstddef>

class Timer {
public:
    Timer(float tps);
    void advanceTime();

    float m_ticksPerSecond;
    double m_lastTime;
    int m_ticks;
    float m_partialTick;
    float m_timeScale;
    float m_tickRemainder;
    long long m_lastClockMillis;
    long long m_lastSyncMillis;
    long long m_syncAccumulator;
    double m_clockAdjustment;
};

static_assert(sizeof(Timer) == 0x40, "Timer size");
static_assert(offsetof(Timer, m_lastTime) == 0x08, "Timer clock layout");
static_assert(offsetof(Timer, m_ticks) == 0x10, "Timer tick layout");
static_assert(offsetof(Timer, m_clockAdjustment) == 0x38, "Timer adjustment layout");
