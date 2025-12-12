#pragma once

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/Direction.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/BooleanProperty.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "types.h"

class DirtBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* DIRT;
        static Variant* COARSE;
        static Variant* PODZOL;

        static Variant* VARIANTS[3];

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        // NON_MATCHING: idk
        Variant(int data, const std::wstring& name, int nameId, int descriptionId,
                const MaterialColor* materialColor, const std::wstring& texName, const std::wstring& sideTex,
                const std::wstring& topTex) {
            this->mData = data;
            this->mName = name;
            this->mNameId = nameId;
            this->mDescriptionId = descriptionId;
            this->mMaterialColor = materialColor;
            this->mTextureName = texName;
            this->mSideTextureName = sideTex;
            this->mTopTextureName = topTex;
            this->mTexture = nullptr;
            this->mTopTexture = nullptr;
            this->mSideTexture = nullptr;
        }

        int getData() { return this->mData; }
        const MaterialColor* getMaterialColor() { return this->mMaterialColor; }
        int getNameId() { return this->mNameId; }
        int getDescriptionId() { return this->mDescriptionId; }
        TextureAtlasSprite* getTexture(const Direction* dir) {
            TextureAtlasSprite* ret = this->mTopTexture;
            if (!ret || dir != Direction::UP) {
                ret = this->mSideTexture;
                if (!ret || dir == Direction::UP || dir == Direction::DOWN) {
                    ret = this->mTexture;
                }
            }
            return ret;
        }
        void registerIcons(IconRegister* iconReg) {
            this->mTexture = iconReg->registerIcon(this->mTextureName);

            if (!mTopTextureName.empty())
                this->mTopTexture = iconReg->registerIcon(this->mTopTextureName);

            if (!mSideTextureName.empty())
                this->mSideTexture = iconReg->registerIcon(this->mSideTextureName);
        }

        std::wstring toString() const override { return this->mName; }
        std::wstring getSerializedName() const override { return this->mName; }

        // I do not guarantee that those var names regarding textures are near correct...
        int mData;
        std::wstring mName;
        int mNameId;
        int mDescriptionId;
        const MaterialColor* mMaterialColor;
        std::wstring mTextureName;
        std::wstring mTopTextureName;
        std::wstring mSideTextureName;
        TextureAtlasSprite* mTexture;
        TextureAtlasSprite* mTopTexture;
        TextureAtlasSprite* mSideTexture;
    };

    static inline EnumProperty<Variant*>* VARIANT;
    static inline BooleanProperty* SNOWY;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);

    DirtBlock();

    static void blockStaticCtor();

    int GetInteractTooltip(const BlockTooltipDataHolder&) override;
    const MaterialColor* getMapColor(const BlockState*, LevelSource*, const BlockPos&) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    const BlockState* fillVirtualBlockStateProperties(const BlockState*, LevelSource*,
                                                      const BlockPos&) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    not_null_ptr<ItemInstance> getCloneItemInstance(Level*, const BlockPos&, const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
};
