#pragma once

#include "net/minecraft/core/LocatableSource.h"
#include <memory>

class BlockEntity;
class BlockState;
class Entity;
class Material;

class BlockSource : public LocatableSource {
public:
    virtual const BlockState* getBlockState() = 0;
    virtual Material* getMaterial() = 0;
    virtual std::shared_ptr<BlockEntity> getEntity() = 0;
};
