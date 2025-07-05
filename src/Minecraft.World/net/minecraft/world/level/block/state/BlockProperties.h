#pragma once

#include "net/minecraft/world/level/block/RenderShape.h"
#include "net/minecraft/world/level/block/boxed/TypedBoxed.h"
#include "net/minecraft/world/level/block/state/BlockBehaviours.h"

class Entity;
class BlockPos;
class LevelSource;
class Rotation;
class Mirror;
class Level;
class Direction;
class Property;
class Vec3;
class Boxed;
class Block;
class Player;
class AABB;
class Material;
class MaterialColor;
class BlockState;

class BlockProperties {
public:
    virtual Material* getMaterial() const = 0;
    virtual bool isSolid() const = 0;
    virtual bool isValidSpawn(std::shared_ptr<Entity>) const = 0;
    virtual int getLightBlock() const = 0;
    virtual void getLightEmission() const = 0;
    virtual bool isTranslucent() const = 0;
    virtual bool doesPropagate() const = 0;
    virtual MaterialColor* getMapColor(LevelSource*, const BlockPos&) = 0;
    virtual void rotate(Rotation*) const = 0;
    virtual void mirror(Mirror*) const = 0;
    virtual bool isCubeShaped() const = 0;
    virtual void hasCustomBreakingProgress() const = 0;
    virtual RenderShape getRenderShape() const = 0;
    virtual void getLightColor(LevelSource*, const BlockPos&) const = 0;
    virtual float getShadeBrightness() const = 0;
    virtual bool isSolidBlockingCube() const = 0;
    virtual bool isSolidBlockingCubeAndNotSignalSource() const = 0;
    virtual bool isSignalSource() const = 0;
    virtual void getSignal(LevelSource*, const BlockPos&, const Direction*) const = 0;
    virtual void hasAnalogOutputSignal() const = 0;
    virtual void getAnalogOutputSignal(Level*, const BlockPos&) const = 0;
    virtual float getDestroySpeed(Level*, const BlockPos&) const = 0;
    virtual void getDestroyProgress(std::shared_ptr<Player>, Level*, const BlockPos&) const = 0;
    virtual int getDirectSignal(LevelSource*, const BlockPos&, const Direction*) const = 0;
    virtual void getPistonPushReaction() const = 0;
    virtual const BlockState* fillVirtualBlockStateProperties(LevelSource*, const BlockPos&) const = 0;
    virtual void getOutlineAABB(Level*, const BlockPos&) const = 0;
    virtual bool shouldRenderFace(LevelSource*, const BlockPos&, const Direction*) const = 0;
    virtual bool isSolidRender() const = 0;
    virtual AABB* getClipAABB(LevelSource*, const BlockPos&) const = 0;
    virtual void addCollissionAABBs(Level*, const BlockPos&, AABB const*, std::vector<AABB*>*,
                                    std::shared_ptr<Entity>, bool) const
        = 0;
    virtual AABB* getShape(LevelSource*, const BlockPos&) const = 0;
    virtual void clip(Level*, const BlockPos&, Vec3*, Vec3*) const = 0;
    virtual bool isTopSolidBlocking() const = 0;
    virtual void getOffset(LevelSource*, const BlockPos&) const = 0;
    virtual bool isViewBlocking() const = 0;
    virtual int getBlockFaceShape(LevelSource*, const BlockPos&, const Direction*) const = 0;
};
