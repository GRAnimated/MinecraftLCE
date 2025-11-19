#pragma once

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include "net/minecraft/world/level/LevelListener.h"
#include "types.h"
#include <memory>

class Camera {
public:
    static void getBlockAt(Level*, std::shared_ptr<Entity>, float);
    static void getCameraBlockPos(std::shared_ptr<LivingEntity>, double);
    static void getCameraPos(std::shared_ptr<Entity>, double);
    static void prepare(std::shared_ptr<Player>, bool);
    static void UpdatePlayerOffsets(std::shared_ptr<Player>);

    static float getRotationX();
    static float getRotationXZ();
    static float getRotationZ();
    static float getRotationYZ();
    static float getRotationXY();

    static float ROTATION_X;
    static float ROTATION_XZ;
    static float ROTATION_Z;
    static float ROTATION_YZ;
    static float ROTATION_XY;
};
