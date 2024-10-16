#pragma once

class Compression {
public:
    static void CreateNewThreadStorage();
    static void ReleaseThreadStorage();
};
