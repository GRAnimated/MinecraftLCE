#pragma once

#include <string>

class Minecraft {
    Minecraft(class Component*, class Canvas*, class MinecraftApplet*, int, int, bool);
    void run();
    inline void init();
    static inline void currentTimeMillis();
    static void start(const std::wstring& str1, const std::wstring& str2);
    static void startAndConnectTo(const std::wstring& arg1, const std::wstring& arg2, const std::wstring& arg3);
};