#pragma once

#include "nn/os/os_MutexTypes.h"
#include "Minecraft.World/ArrayWithLength.h"
#include <sstream>
#include <string>

// TODO: Find location
void InitializeCriticalSection(nn::os::MutexType* mutexType);
// TODO: Find location
template <typename T>
const std::wstring _toString(T type) {
    std::wstringstream ss;
    ss << type;
    return ss.str();
}

class System {
public:
    static long processTimeInMilliSecs();
    static long processTimeInNanoSecs();

    static void arraycopy(arrayWithLength<u8>, unsigned int, arrayWithLength<u8>*, unsigned int,
                          unsigned int);
};
