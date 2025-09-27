#pragma once

class IntCache {
public:
    static void CreateNewThreadStorage();

    class ThreadStorage {};

    static void Reset();
};
