#include "net/minecraft/world/entity/mob/MinecartType.h"

std::wstring MinecartType::NAMES[7]
    = {L"MinecartRideable", L"MinecartChest",  L"MinecartFurnace",     L"MinecartTNT",
       L"MinecartSpawner",  L"MinecartHopper", L"MinecartCommandBlock"};
MinecartType* MinecartType::RIDEABLE = new MinecartType{0};
MinecartType* MinecartType::CHEST = new MinecartType{1};
MinecartType* MinecartType::FURNACE = new MinecartType{2};
MinecartType* MinecartType::TNT = new MinecartType{3};
MinecartType* MinecartType::SPAWNER = new MinecartType{4};
MinecartType* MinecartType::HOPPER = new MinecartType{5};
MinecartType* MinecartType::COMMAND_BLOCK = new MinecartType{6};

std::wstring MinecartType::getName() const {
    return NAMES[id];
}
