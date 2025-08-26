#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "nn/os/os_MutexTypes.h"

#include <sstream>
#include <string>

class Node;

// TODO: Find location
void InitializeCriticalSection(nn::os::MutexType* mutexType);
void InitializeCriticalSectionAndSpinCount(nn::os::MutexType* mutexType, unsigned long spinCount);
// TODO: Find location
template <typename T>
const std::wstring _toString(T type) {
    std::wstringstream ss;
    ss << type;
    return ss.str();
}

std::wstring trimString(const std::wstring& str);

class System {
public:
    enum ETimeGranularity { MILLISECONDS, MICROSECONDS, NANOSECONDS };

    static long currentRealTimeMillis();
    static long currentUnixEpochTimeSeconds();

    static long processTimeInSeconds();
    static long processTimeInMilliSecs();
    static long processTimeInNanoSecs();
    static long processTimeInMicroSecs();
    static long processTime(System::ETimeGranularity);

    template <typename T>
    static void arraycopy(arrayWithLength<T> src, unsigned int srcOff, arrayWithLength<T>* dest,
                          unsigned int destOff, unsigned int size) {
        memcpy((*dest).data + destOff, src.data + srcOff, (uint64_t)size << 2);
    }

    /** Reverses an in-place Short value */
    static void ReverseSHORT(short* v);
    /** Reverses an in-place unsigned Short value */
    static void ReverseUSHORT(unsigned short* v);
    /** Reverses an in-place Integer value */
    static void ReverseINT(int* v);
    /** Reverses an in-place unsigned Long value */
    static void ReverseULONG(unsigned long* v);
    /** Reverses an in-place unsigned Integer value (despite it's name) */
    static void ReverseULONG(unsigned int* v);
    /** Reverses an in-place unsigned Long Long value */
    static void ReverseULONGLONG(unsigned long long* v);
    /** Reverses an in-place char16 string with the given length */
    static void ReverseCHAR16A(char16_t* str, int len);
};
