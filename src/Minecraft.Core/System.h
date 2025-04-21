#pragma once

#include "nn/os/os_MutexTypes.h"
#include <string>
#include <sstream>

// TODO: Find location
void InitializeCriticalSection(nn::os::MutexType* mutexType);
// TODO: Find location
template <typename T>
const std::wstring _toString(T type) {
    std::wstringstream ss;
    ss << type;
    return ss.str();
}

namespace System {
long processTimeInMilliSecs();
long processTimeInNanoSecs();
}  // namespace System

