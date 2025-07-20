#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include "net/minecraft/world/level/material/MaterialColor.h"
#include <string>

class PlanksBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static inline Variant* OAK;
        static inline Variant* SPRUCE;
        static inline Variant* BIRCH;
        static inline Variant* JUNGLE;
        static inline Variant* ACACIA;
        static inline Variant* DARK_OAK;
        static inline Variant* VARIANTS[6];  // waste of memory...

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, unsigned int loc_id, const MaterialColor* materialColor) {
            this->mMaterialColor = materialColor;
            this->mData = data;
            this->mName = name;
            this->mName_id = loc_id;
        }

        int getData() { return this->mData; }
        const MaterialColor* getMaterialColor() { return this->mMaterialColor; }

        std::wstring toString() const override { return this->mName; }
        std::wstring getSerializedName() const override { return this->mName; }

        int mData;  // I would have named it id but they use data over and over again
        std::wstring mName;
        unsigned int mName_id;
        const MaterialColor* mMaterialColor;
    };

    PlanksBlock();

    static void blockStaticCtor();

    static inline EnumProperty<Variant*>* VARIANT;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);
    static std::wstring variantTextureNames[6];

    const MaterialColor* getMapColor(const BlockState*, LevelSource*, const BlockPos&) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    int getDescriptionId(int) override;

    TextureAtlasSprite* mVariantsTextures[6];
};
