#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

class RedSandStoneBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* DEFAULT;
        static Variant* CHISELED;
        static Variant* SMOOTH;

        static Variant* VARIANTS[3];  // waste of memory..., why not store them in array already

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, unsigned int loc_id) {
            this->mData = data;
            this->mName = name;
            this->mName_id = loc_id;
        }

        int getData() { return this->mData; }

        std::wstring toString() const override { return this->mName; }
        std::wstring getSerializedName() const override { return this->mName; }

        int mData;  // I would have named it id but they use data over and over again
        std::wstring mName;
        unsigned int mName_id;
    };

    RedSandStoneBlock();

    static void blockStaticCtor();

    static EnumProperty<Variant*>* TYPE;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);
    static std::wstring RED_VARIANT_TEXTURE_NAMES[3];
    static std::wstring RED_SANDSTONE_TOP;
    static std::wstring RED_SANDSTONE_BOTTOM;

    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;

    TextureAtlasSprite* mVariantsTextures[3];
    TextureAtlasSprite* mTopTexture;
    TextureAtlasSprite* mBottomTexture;
};
