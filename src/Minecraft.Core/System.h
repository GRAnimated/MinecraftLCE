#pragma once

#include "nn/os/os_MutexTypes.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/level/biome/Biome.h"

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

    static void arraycopy(arrayWithLength<u8>, unsigned int, arrayWithLength<u8>*, unsigned int,
                          unsigned int);

    static void arraycopy(arrayWithLength<int>, unsigned int, arrayWithLength<int>*, unsigned int,
                          unsigned int);

    static void arraycopy(arrayWithLength<Biome*>, unsigned int, arrayWithLength<Biome*>*, unsigned int,
                          unsigned int);

    static void arraycopy(arrayWithLength<Node*>, unsigned int, arrayWithLength<Node*>*, unsigned int,
                          unsigned int);

    // template for arraycopy here

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
