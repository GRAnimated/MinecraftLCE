#pragma once

#include "nn/os/os_MutexTypes.h"

// TODO: Find location
void InitializeCriticalSection(nn::os::MutexType* mutexType);

namespace System {
long processTimeInMilliSecs();
long processTimeInNanoSecs();
}  // namespace System
