#include "Minecraft.Client/resources/IdMap.h"
#include "Minecraft.Client/resources/MappedRegistry.h"
#include "Minecraft.Client/resources/ResourceLocation.h"
#include "Minecraft.World/enchantment/Enchantment.h"
MappedRegistry<ResourceLocation, Enchantment*>* sEnchantmentRegistry
    = new MappedRegistry<ResourceLocation, Enchantment*>;