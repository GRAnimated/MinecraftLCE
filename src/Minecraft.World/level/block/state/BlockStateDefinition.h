#pragma once

#include "Minecraft.World/level/block/state/BlockState.h"
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
        void getLightBlock() const override;
        void getLightEmission() const override;
        bool isTranslucent() const override;
        void doesPropagate() const override;
        MaterialColor* getMapColor(LevelSource*, BlockPos const&) override;
        void rotate(Rotation*) const override;
        void mirror(Mirror*) const override;
        bool isCubeShaped() const override;
        void hasCustomBreakingProgress() const override;
        RenderShape getRenderShape() const override;
        void getLightColor(LevelSource*, BlockPos const&) const override;
        float getShadeBrightness() const override;
        bool isSolidBlockingCube() const override;
        bool isSolidBlockingCubeAndNotSignalSource() const override;
        bool isSignalSource() const override;
        void getSignal(LevelSource*, BlockPos const&, Direction const*) const override;
        void hasAnalogOutputSignal() const override;
        void getAnalogOutputSignal(Level*, BlockPos const&) const override;
        void getDestroySpeed(Level*, BlockPos const&) const override;
        void getDestroyProgress(std::shared_ptr<Player>, Level*, BlockPos const&) const override;
        void getDirectSignal(LevelSource*, BlockPos const&, Direction const*) const override;
        void getPistonPushReaction() const override;
        const BlockState* fillVirtualBlockStateProperties(LevelSource*, BlockPos const&) const override;
        void getOutlineAABB(Level*, BlockPos const&) const override;
        bool shouldRenderFace(LevelSource*, BlockPos const&, Direction const*) const override;
        bool isSolidRender() const override;
        AABB* getClipAABB(LevelSource*, BlockPos const&) const override;
        void addCollissionAABBs(Level*, BlockPos const&, AABB const*, std::vector<AABB*>*,
                                std::shared_ptr<Entity>, bool) const override;
        AABB* getShape(LevelSource*, BlockPos const&) const override;
        void clip(Level*, BlockPos const&, Vec3*, Vec3*) const override;
        bool isTopSolidBlocking() const override;
        void getOffset(LevelSource*, BlockPos const&) const override;
        bool isViewBlocking() const override;
        int getBlockFaceShape(LevelSource*, BlockPos const&, Direction const*) const override;
        void getProperties() const override;
        void hasProperty(Property const*) const override;
        Boxed* getBoxedValue(Property const*) const override;
        const BlockState* setBoxedValue(Property const*, Boxed*) const override;
        void cycle(Property const*) const override;
        void getValues() const override;
        Block* getBlock() const override;
        void toString() const override;
        void equals(BlockState const*) override;
        void hashCode() const override;
        void triggerEvent(Level*, BlockPos const&, int, int) const override;
        void neighborChanged(Level*, BlockPos const&, Block*, BlockPos const&) const override;
    };

    BlockStateDefinition(Block* block);

    // NON_MATCHING
    template <typename T>
    BlockStateDefinition(Block* block, T* properties) {
        // std::vector<const Property*> propertiesVec{properties...};
        // _init(block, propertiesVec.data(), propertiesVec.size());
        _init(block, properties, sizeof(properties));
    }

    void _init(Block* block, Property const** properties, unsigned int damage);

    Block* getBlock();
    const BlockState* any();

private:
    char filler[0x40];
};
