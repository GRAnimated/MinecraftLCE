#pragma once

#include <memory>

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
    virtual void getProperties() const = 0;
    virtual void hasProperty(const Property*) const = 0;
    virtual Boxed* getBoxedValue(const Property*) const = 0;
    virtual const BlockState* setBoxedValue(const Property*, Boxed*) const = 0;
    virtual void cycle(const Property*) const = 0;
    virtual void getValues() const = 0;
    virtual Block* getBlock() const = 0;
    virtual void toString() const = 0;
    virtual void equals(const BlockState*) = 0;
    virtual void hashCode() const = 0;

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
