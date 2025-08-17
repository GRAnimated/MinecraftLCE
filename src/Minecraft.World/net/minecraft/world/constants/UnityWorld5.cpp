#include "net/minecraft/client/resources/IdMap.h"
#include "net/minecraft/client/resources/MappedRegistry.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include "net/minecraft/world/item/enchantment/Enchantment.h"

MappedRegistry<ResourceLocation, Enchantment*>* sEnchantmentRegistry
    = new MappedRegistry<ResourceLocation, Enchantment*>;
