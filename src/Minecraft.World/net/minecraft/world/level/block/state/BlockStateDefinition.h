#pragma once

#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/block/state/AbstractProperty.h"
#include "net/minecraft/world/level/block/state/BlockState.h"
#include <vector>

class Block;
class BlockState;

class BlockStateDefinition {
public:
    class BlockStateImpl : public BlockState {
    public:
        Material* getMaterial() const override;
        bool isSolid() const override;
        bool isValidSpawn(std::shared_ptr<Entity>) const override;
        int getLightBlock() const override;
        void getLightEmission() const override;
        bool isTranslucent() const override;
        bool doesPropagate() const override;
        MaterialColor* getMapColor(LevelSource*, const BlockPos&) override;
        void rotate(Rotation*) const override;
        void mirror(Mirror*) const override;
        bool isCubeShaped() const override;
        void hasCustomBreakingProgress() const override;
        RenderShape getRenderShape() const override;
        void getLightColor(LevelSource*, const BlockPos&) const override;
        float getShadeBrightness() const override;
        bool isSolidBlockingCube() const override;
        bool isSolidBlockingCubeAndNotSignalSource() const override;
        bool isSignalSource() const override;
        void getSignal(LevelSource*, const BlockPos&, const Direction*) const override;
        void hasAnalogOutputSignal() const override;
        void getAnalogOutputSignal(Level*, const BlockPos&) const override;
        float getDestroySpeed(Level*, const BlockPos&) const override;
        void getDestroyProgress(std::shared_ptr<Player>, Level*, const BlockPos&) const override;
        int getDirectSignal(LevelSource*, const BlockPos&, const Direction*) const override;
        void getPistonPushReaction() const override;
        const BlockState* fillVirtualBlockStateProperties(LevelSource*, const BlockPos&) const override;
        void getOutlineAABB(Level*, const BlockPos&) const override;
        bool shouldRenderFace(LevelSource*, const BlockPos&, const Direction*) const override;
        bool isSolidRender() const override;
        AABB* getClipAABB(LevelSource*, const BlockPos&) const override;
        void addCollissionAABBs(Level*, const BlockPos&, AABB const*, std::vector<AABB*>*,
                                std::shared_ptr<Entity>, bool) const override;
        AABB* getShape(LevelSource*, const BlockPos&) const override;
        void clip(Level*, const BlockPos&, Vec3*, Vec3*) const override;
        bool isTopSolidBlocking() const override;
        void getOffset(LevelSource*, const BlockPos&) const override;
        bool isViewBlocking() const override;
        int getBlockFaceShape(LevelSource*, const BlockPos&, const Direction*) const override;
        void getProperties() const override;
        void hasProperty(const Property*) const override;
        Boxed* getBoxedValue(const Property*) const override;
        const BlockState* setBoxedValue(const Property*, Boxed*) const override;
        void cycle(const Property*) const override;
        void getValues() const override;
        Block* getBlock() const override;
        void toString() const override;
        void equals(const BlockState*) override;
        void hashCode() const override;
        void triggerEvent(Level*, const BlockPos&, int, int) const override;
        void neighborChanged(Level*, const BlockPos&, Block*, const BlockPos&) const override;
    };
    BlockStateDefinition(Block* block);

    template <int N>
    BlockStateDefinition(Block* block, const Property* (&properties_array)[N]) {
        _init(block, properties_array, N);
    }

    void _init(Block* block, const Property** properties, unsigned int propertiesCount);

    Block* getBlock();
    const BlockState* any();
    const BlockState* getPossibleBlockStates();

private:
    Block* mBlock;
    std::vector<const Property*> mProperties;
    arrayWithLength<const BlockState*> mStates;
    char filler[24];
};
