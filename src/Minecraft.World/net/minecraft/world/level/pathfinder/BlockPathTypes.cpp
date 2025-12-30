#include "net/minecraft/world/level/pathfinder/BlockPathTypes.h"

const BlockPathTypes* BlockPathTypes::BLOCKED = new BlockPathTypes(0, -1.0f);
const BlockPathTypes* BlockPathTypes::OPEN = new BlockPathTypes(1, 0.0f);
const BlockPathTypes* BlockPathTypes::WALKABLE = new BlockPathTypes(2, 0.0f);
const BlockPathTypes* BlockPathTypes::TRAPDOR = new BlockPathTypes(3, 0.0f);
const BlockPathTypes* BlockPathTypes::FENCE = new BlockPathTypes(4, -1.0f);
const BlockPathTypes* BlockPathTypes::LAVA = new BlockPathTypes(5, -1.0f);
const BlockPathTypes* BlockPathTypes::WATER = new BlockPathTypes(6, 8.0f);
const BlockPathTypes* BlockPathTypes::RAIL = new BlockPathTypes(7, 0.0f);
const BlockPathTypes* BlockPathTypes::DANGER_FIRE = new BlockPathTypes(8, 8.0f);
const BlockPathTypes* BlockPathTypes::DAMAGE_FIRE = new BlockPathTypes(9, 16.0f);
const BlockPathTypes* BlockPathTypes::DANGER_CACTUS = new BlockPathTypes(10, 8.0f);
const BlockPathTypes* BlockPathTypes::DAMAGE_CACTUS = new BlockPathTypes(11, -1.0f);
const BlockPathTypes* BlockPathTypes::DANGER_OTHER = new BlockPathTypes(12, 8.0f);
const BlockPathTypes* BlockPathTypes::DAMAGE_OTHER = new BlockPathTypes(13, -1.0f);
const BlockPathTypes* BlockPathTypes::DOOR_OPEN = new BlockPathTypes(14, 0.0f);
const BlockPathTypes* BlockPathTypes::DOOR_WOOD_CLOSED = new BlockPathTypes(15, -1.0f);
const BlockPathTypes* BlockPathTypes::DOOR_IRON_CLOSED = new BlockPathTypes(16, -1.0f);
