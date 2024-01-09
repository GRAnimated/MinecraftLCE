/**
 * @file util.h
 * @brief Helper functions for OS functionality.
 */

#pragma once

#include <cstdarg>
#include <nn/types.h>

namespace nn {
namespace util {

enum CharacterEncodingResult { Success, BadLength, InvalidFormat };

CharacterEncodingResult PickOutCharacterFromUtf8String(char*, char const** str);
CharacterEncodingResult ConvertCharacterUtf8ToUtf32(u32* dest, char const* src);
CharacterEncodingResult ConvertStringUtf16NativeToUtf8(char*, s32, u16 const*, s32);
CharacterEncodingResult ConvertStringUtf8ToUtf16Native(u16*, s32, char const*, s32);

s32 SNPrintf(char* s, ulong n, const char* format, ...);
s32 VSNPrintf(char* s, ulong n, const char* format, va_list arg);

void ReferSymbol(const void*);
}  // namespace util
}  // namespace nn

#ifndef NN_SDK_MAJOR
#define NN_SDK_MAJOR 0
#define NN_SDK_MINOR 0
#define NN_SDK_PATCH 0
#endif

#ifndef NN_WARE_MAJOR
#define NN_WARE_MAJOR 0
#define NN_WARE_MINOR 0
#define NN_WARE_PATCH 0
#endif

#ifndef NN_SDK_TYPE
#define NN_SDK_TYPE "Release"
#endif

#ifndef NN_MAKE_VER
#define NN_MAKE_VER(major, minor, patch) ((major << 16) | (minor << 8) | (patch))

#define NN_SDK_VER NN_MAKE_VER(NN_SDK_MAJOR, NN_SDK_MINOR, NN_SDK_PATCH)
#define NN_WARE_VER NN_MAKE_VER(NN_WARE_MAJOR, NN_WARE_MINOR, NN_WARE_PATCH)

#define NN_STRINGIFY1(s) #s
#define NN_STRINGIFY(s) NN_STRINGIFY1(s)

#define NN_SDK_BUILD_STR                                                                           \
    "-" NN_STRINGIFY(NN_SDK_MAJOR) "_" NN_STRINGIFY(NN_SDK_MINOR) "_" NN_STRINGIFY(                \
        NN_SDK_PATCH) "-" NN_SDK_TYPE
#endif

#define NN_MIDDLEWARE(var, company, name)                                                          \
    static const char var[] __attribute__((section(".api_info"))) = "SDK MW+" company "+" name

// todo: move/rename with more info
#define NN_NO_COPY(CLASS)                                                                          \
    CLASS(const CLASS&) = delete;                                                                  \
    CLASS& operator=(const CLASS&) = delete

#define NN_NO_MOVE(CLASS)                                                                          \
    CLASS(CLASS&&) = delete;                                                                       \
    CLASS& operator=(CLASS&&) = delete

namespace nn::detail {

[[noreturn]] void UnexpectedDefaultImpl(const char*, const char*, int);

}  // namespace nn::detail

// todo: ifdef to support debug functionality?
#define NN_UNEXPECTED_DEFAULT nn::detail::UnexpectedDefaultImpl("", "", 0)
