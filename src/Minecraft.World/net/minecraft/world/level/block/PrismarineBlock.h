#pragma once

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"

class PrismarineBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* ROUGH;
        static Variant* BRICKS;
        static Variant* DARK;

        static Variant* VARIANTS[3];

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, int nameId, int descriptionId,
                const std::wstring& textureName) {
            this->mData = data;
            this->mName = name;
            this->mNameId = nameId;
            this->mDescriptionId = descriptionId;
            this->mTextureName = textureName;
        }

        int getData() { return this->mData; }
        TextureAtlasSprite* getTexture() { return this->mTexture; }
        int getNameId() { return this->mNameId; }
        int getDescriptionId() { return this->mDescriptionId; }

        void registerIcons(IconRegister* iconReg) {
            this->mTexture = iconReg->registerIcon(this->mTextureName);
        }

        std::wstring toString() const override { return this->mName; }
        std::wstring getSerializedName() const override { return this->mName; }

        int mData;
        std::wstring mName;
        int mNameId;
        int mDescriptionId;
        std::wstring mTextureName;
        TextureAtlasSprite* mTexture;
    };

    static int ROUGH_DATA;
    static int BRICKS_DATA;
    static int DARK_DATA;
    static inline EnumProperty<Variant*>* VARIANT;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);

    PrismarineBlock();

    static void blockStaticCtor();

    const MaterialColor* getMapColor(const BlockState*, LevelSource*, const BlockPos&) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    std::wstring getName() override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
};
