#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "types.h"

class MonsterEggBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* STONE;
        static Variant* COBBLESTONE;
        static Variant* STONE_BRICK;
        static Variant* MOSSY_BRICK;
        static Variant* CRACKED_BRICK;
        static Variant* CHISELED_BRICK;

        static Variant* VARIANTS[6];

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, int translationKey) {
            this->mData = data;
            this->mName = name;
            this->mTranslationKey = translationKey;
        }

        int getData() { return this->mData; }
        int getTranslationKey() { return this->mTranslationKey; }

        std::wstring toString() const override { return this->mName; }
        std::wstring getSerializedName() const override { return this->mName; }

        int mData;
        std::wstring mName;
        int mTranslationKey;
    };

    static inline EnumProperty<Variant*>* VARIANT;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);

    MonsterEggBlock();

    static void blockStaticCtor();

    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getResourceCount(Random*) override;
    void spawnResources(Level*, const BlockPos&, const BlockState*, float, int) override;
    not_null_ptr<ItemInstance> getSilkTouchItemInstance(const BlockState*) override;
    not_null_ptr<ItemInstance> getCloneItemInstance(Level*, const BlockPos&, const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
};
