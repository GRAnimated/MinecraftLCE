#pragma once

#include "nn/os/os_MutexTypes.h"
#include <string>

// TODO: Find location
void InitializeCriticalSection(nn::os::MutexType* mutexType);
// TODO: Find location
template <typename T>
std::wstring _toString(T type) {
    // std::wstringstream ss;
    // ss << type;
    // return ss.str();
}

namespace System {
long processTimeInMilliSecs();
long processTimeInNanoSecs();
}  // namespace System
