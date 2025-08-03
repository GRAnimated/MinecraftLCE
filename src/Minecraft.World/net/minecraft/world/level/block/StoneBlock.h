#pragma once

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <string>

class StoneBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static inline Variant* STONE;
        static inline Variant* GRANITE;
        static inline Variant* SMOOTH_GRANITE;
        static inline Variant* DIORITE;
        static inline Variant* SMOOTH_DIORITE;
        static inline Variant* ANDESITE;
        static inline Variant* SMOOTH_ANDESITE;

        static inline Variant* VARIANTS[7];

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const MaterialColor* materialColor, const std::wstring& name, int name_id,
                int desc_id, const std::wstring& textureName, bool natural) {
            this->mData = data;
            this->mName = name;
            this->mMaterialColor = materialColor;
            this->mName_id = name_id;
            this->mDesc_id = desc_id;
            this->mTextureName = textureName;
            this->mNatural = natural;
        }

        void registerIcons(IconRegister* iconReg) {
            this->mTexture = iconReg->registerIcon(this->mTextureName);
        }

        int getData() { return this->mData; }
        std::wstring getName() { return this->mName; }
        int getNameId() { return this->mName_id; }
        int getDescriptionId() { return this->mDesc_id; }
        const MaterialColor* getMaterialColor() { return this->mMaterialColor; }
        bool isNatural() { return this->mNatural; }
        TextureAtlasSprite* getTexture() { return this->mTexture; }

        std::wstring toString() const override { return this->mName; }
        std::wstring getSerializedName() const override { return this->mName; }

        int mData;
        std::wstring mName;
        int mName_id;
        int mDesc_id;
        const MaterialColor* mMaterialColor;
        bool mNatural;
        std::wstring mTextureName;
        TextureAtlasSprite* mTexture;
    };

    StoneBlock();

    static void blockStaticCtor();

    static inline EnumProperty<Variant*>* VARIANT;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);

    const MaterialColor* getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                     const BlockPos& pos) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    std::wstring getName() override;
    Item* getResource(const BlockState* blockState, Random*, int) override;
};
