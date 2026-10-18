#pragma once

#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "net/minecraft/world/level/levelgen/feature/Feature.h"

class Block;

class OreFeature : public Feature {
public:
    OreFeature(const BlockState* state, int unk);
    OreFeature(const BlockState* state, int size, const Predicate<const Biome::LegacyBlockData&>* predicate);

    class NaturalStonePredicate : public Predicate<const Biome::LegacyBlockData&> {
    public:
        bool apply(const Biome::LegacyBlockData&) const override;
        ~NaturalStonePredicate() override;
    };

    using Feature::init;
    void init(const BlockState*, int, const Predicate<const Biome::LegacyBlockData&>*);

    bool place(Level* level, Random& random, const BlockPos& pos) override;

private:
    Biome::LegacyBlockData m_ore;
    int m_size;
    const Predicate<const Biome::LegacyBlockData&>* m_predicate;
};

static_assert(sizeof(OreFeature) == 0x20, "OreFeature layout must match the Switch object");
