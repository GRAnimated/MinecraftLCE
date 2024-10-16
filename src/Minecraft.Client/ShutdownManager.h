#pragma once

class ShutdownManager {
public:
    enum EThreadId {
        _8 = 8,
        _9 = 9,
    };
    static bool HasStarted(ShutdownManager::EThreadId);
    static bool ShouldRun(ShutdownManager::EThreadId);
    static bool HasFinished(ShutdownManager::EThreadId);
};
