#pragma once

#include <string>

class MinecartType {
public:
    std::wstring getName() const;
    static std::wstring NAMES[7];
    static MinecartType* RIDEABLE;
    static MinecartType* CHEST;
    static MinecartType* FURNACE;
    static MinecartType* TNT;
    static MinecartType* SPAWNER;
    static MinecartType* HOPPER;
    static MinecartType* COMMAND_BLOCK;
    int id;
};
