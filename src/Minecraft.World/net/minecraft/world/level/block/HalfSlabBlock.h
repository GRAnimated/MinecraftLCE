#pragma once

#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

class HalfSlabBlock : public Block {
public:
    class Half : public StringRepresentable {
    public:
        static Half* TOP;
        static Half* BOTTOM;

        static Half* VARIANTS[2];  // let's leave it as variants, as halfs sounds lame

        static Half* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Half*)) - 1 ? 0 : data];
        }

        Half(const std::wstring& name) { this->m_name = name; }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        std::wstring m_name;
    };

    static inline EnumProperty<Half*>* VARIANT;
    static inline Predicates<Half*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Half*>::ConstantPredicate(true);
    static const AABB* topShape;
    static const AABB* bottomShape;

    static void blockStaticCtor();
    static bool isHalfSlab(Block*);
    static bool isHalfSlab(const BlockState* state);

    HalfSlabBlock(Material*);
    HalfSlabBlock(Material*, const MaterialColor*);
    void _init();

    bool isTopSolidBlocking(const BlockState* state) override;
    void DerivedInit() override;
    bool isCubeShaped(const BlockState*) override;
    bool isPathfindable(LevelSource*, const BlockPos&) override;
    const AABB* getShape(const BlockState*, LevelSource*, const BlockPos&) override;
    bool shouldRenderFace(const BlockState*, LevelSource*, const BlockPos&, const Direction*) override;
    int getBlockFaceShape(LevelSource*, const BlockState*, const BlockPos&, const Direction*) override;
    bool isSolidRender(const BlockState*) const override;
    int getResourceCount(Random*) override;
    const BlockState* getStateForPlacement(Level*, const BlockPos&, const Direction*, float, float, float,
                                           int, std::__1::shared_ptr<LivingEntity>) override;
    bool isSilkTouchable() override;
    virtual std::wstring getAuxName(int aux) = 0;
    virtual bool isFullSize() const = 0;
    virtual Property* getTypeProperty() = 0;
    virtual Boxed* getTypeForItem() = 0;
};
