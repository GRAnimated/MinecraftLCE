#pragma once

#include <memory>

#include "Minecraft.World/level/block/RenderShape.h"
#include "Minecraft.World/level/block/boxed/TypedBoxed.h"
#include "Minecraft.World/level/block/state/BlockBehaviours.h"
#include "Minecraft.World/level/block/state/BlockProperties.h"

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

class BlockState : public BlockProperties, public BlockBehaviours {
public:
    virtual Material* getMaterial() const = 0;
    virtual bool isSolid() const = 0;
    virtual bool isValidSpawn(std::shared_ptr<Entity>) const = 0;
    virtual void getLightBlock() const = 0;
    virtual void getLightEmission() const = 0;
    virtual bool isTranslucent() const = 0;
    virtual void doesPropagate() const = 0;
    virtual MaterialColor* getMapColor(LevelSource*, BlockPos const&) = 0;
    virtual void rotate(Rotation*) const = 0;
    virtual void mirror(Mirror*) const = 0;
    virtual bool isCubeShaped() const = 0;
    virtual void hasCustomBreakingProgress() const = 0;
    virtual RenderShape getRenderShape() const = 0;
    virtual void getLightColor(LevelSource*, BlockPos const&) const = 0;
    virtual float getShadeBrightness() const = 0;
    virtual bool isSolidBlockingCube() const = 0;
    virtual bool isSolidBlockingCubeAndNotSignalSource() const = 0;
    virtual bool isSignalSource() const = 0;
    virtual void getSignal(LevelSource*, BlockPos const&, Direction const*) const = 0;
    virtual void hasAnalogOutputSignal() const = 0;
    virtual void getAnalogOutputSignal(Level*, BlockPos const&) const = 0;
    virtual void getDestroySpeed(Level*, BlockPos const&) const = 0;
    virtual void getDestroyProgress(std::shared_ptr<Player>, Level*, BlockPos const&) const = 0;
    virtual void getDirectSignal(LevelSource*, BlockPos const&, Direction const*) const = 0;
    virtual void getPistonPushReaction() const = 0;
    virtual const BlockState* fillVirtualBlockStateProperties(LevelSource*, BlockPos const&) const = 0;
    virtual void getOutlineAABB(Level*, BlockPos const&) const = 0;
    virtual bool shouldRenderFace(LevelSource*, BlockPos const&, Direction const*) const = 0;
    virtual bool isSolidRender() const = 0;
    virtual AABB* getClipAABB(LevelSource*, BlockPos const&) const = 0;
    virtual void addCollissionAABBs(Level*, BlockPos const&, AABB const*, std::vector<AABB*>*,
                                    std::shared_ptr<Entity>, bool) const = 0;
    virtual AABB* getShape(LevelSource*, BlockPos const&) const = 0;
    virtual void clip(Level*, BlockPos const&, Vec3*, Vec3*) const = 0;
    virtual bool isTopSolidBlocking() const = 0;
    virtual void getOffset(LevelSource*, BlockPos const&) const = 0;
    virtual bool isViewBlocking() const = 0;
    virtual int getBlockFaceShape(LevelSource*, BlockPos const&, Direction const*) const = 0;
    virtual void getProperties() const = 0;
    virtual void hasProperty(Property const*) const = 0;
    virtual Boxed* getBoxedValue(Property const*) const = 0;
    virtual const BlockState* setBoxedValue(Property const*, Boxed*) const = 0;
    virtual void cycle(Property const*) const = 0;
    virtual void getValues() const = 0;
    virtual Block* getBlock() const = 0;
    virtual void toString() const = 0;
    virtual void equals(BlockState const*) = 0;
    virtual void hashCode() const = 0;
    virtual void triggerEvent(Level*, BlockPos const&, int, int) const = 0;
    virtual void neighborChanged(Level*, BlockPos const&, Block*, BlockPos const&) const = 0;

    // NON_MATCHING: Decomp is using add sp, 0x8 instead of mov sp
    template <typename T>
    const BlockState* setValue(Property* property, T value) const {
        TypedBoxed<T> boxed(&value);
        return setBoxedValue(property, &boxed);
    }

    template <typename T>
    T getValue(Property* property) const {
        TypedBoxed<T>* typedBoxed = (TypedBoxed<T>*)getBoxedValue(property);
        TypedBoxed<T>* type = typedBoxed->tryGetType();
        return *type->getValue();
    }
};
