#include "net/minecraft/client/Timer.h"

#include "DecompUtils.h"
#include "net/minecraft/core/System.h"

Timer::Timer(float tps) {
    m_timeScale = 1.0f;
    m_tickRemainder = 0.0f;
    m_lastTime = 0.0;
    m_ticks = 0;
    m_partialTick = 0.0f;
    m_syncAccumulator = 0;
    m_clockAdjustment = 1.0;
    m_ticksPerSecond = tps;
    m_lastClockMillis = System::processTimeInMilliSecs();
    m_lastSyncMillis = System::processTimeInMilliSecs();
}

// NON_MATCHING | score: 150 (lower is better)
void Timer::advanceTime() {
    long long clockMillis = System::processTimeInMilliSecs();
    long long clockDelta = clockMillis - m_lastClockMillis;
    long long syncMillis = System::processTimeInMilliSecs();
    double time = static_cast<double>(syncMillis) / 1000.0;

    if (clockDelta > 1000) {
        m_lastTime = time - 1000.0;
    } else if (clockDelta < 0) {
        m_lastTime = time;
    } else {
        m_syncAccumulator += clockDelta;
        if (m_syncAccumulator > 1000) {
            long long syncDelta = syncMillis - m_lastSyncMillis;
            m_lastSyncMillis = syncMillis;
            long long accumulatedMillis = m_syncAccumulator;
            m_syncAccumulator = 0;
            m_clockAdjustment += (static_cast<double>(accumulatedMillis) / static_cast<double>(syncDelta)
                                  - m_clockAdjustment)
                                 * static_cast<double>(0.2f);
        } else if (m_syncAccumulator < 0) {
            m_lastSyncMillis = syncMillis;
        }
    }

    double elapsed = (time - m_lastTime) * m_clockAdjustment;
    m_lastTime = time;
    elapsed = decomp_fmin64(decomp_fmax64(elapsed, 0.0), 1.0);
    float accumulated = static_cast<float>(static_cast<double>(m_tickRemainder)
                                           + static_cast<double>(m_ticksPerSecond)
                                                 * (static_cast<double>(m_timeScale) * elapsed));
    int ticks = static_cast<int>(accumulated);
    float remainder = accumulated - static_cast<float>(ticks);
    m_lastClockMillis = clockMillis;
    m_ticks = ticks;
    m_tickRemainder = remainder;
    if (m_ticks > 10)
        m_ticks = 10;
    m_partialTick = remainder;
}
