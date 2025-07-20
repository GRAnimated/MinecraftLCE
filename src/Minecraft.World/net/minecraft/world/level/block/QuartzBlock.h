#pragma once

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <string>

class QuartzBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* DEFAULT;
        static Variant* CHISELED;
        static Variant* LINES_Y;
        static Variant* LINES_X;
        static Variant* LINES_Z;

        static Variant* VARIANTS[5];

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, const std::wstring& textureName) {
            this->mData = data;
            this->mName = name;
            this->mTextureName = textureName;
        }

        int getData() { return this->mData; }
        std::wstring getName() { return this->mName; }

        std::wstring toString() const override { return this->mTextureName; }
        std::wstring getSerializedName() const override { return this->mName; }

        int mData;
        std::wstring mName;
        std::wstring mTextureName;
    };

    static std::wstring TEXTURE_NAME_TOP;           // L"top"
    static std::wstring TEXTURE_NAME_CHISELED_TOP;  // L"chiseled_top"
    static std::wstring TEXTURE_NAME_LINES_TOP;     // L"lines_top"
    static std::wstring TEXTURE_NAME_BOTTOM;        // L"bottom"
    static std::wstring TEXTURE_NAMES[5];

    QuartzBlock();

    static void blockStaticCtor();

    static inline EnumProperty<Variant*>* VARIANT;
    static const inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);

    const MaterialColor* getMapColor(const BlockState* blockState, LevelSource* levelSource,
                                     const BlockPos& pos) override;
    const BlockState* getBlockState(int) override;
    const BlockState* rotate(const BlockState* blockState, Rotation*) override;
    RenderShape getRenderShape(const BlockState* blockState) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;
    not_null_ptr<ItemInstance> getSilkTouchItemInstance(const BlockState* blockState) override;
    const BlockState* getStateForPlacement(Level* level, const BlockPos& pos, const Direction* direction,
                                           float, float, float, int, std::shared_ptr<LivingEntity>) override;

    TextureAtlasSprite* mTextures[5];
    TextureAtlasSprite* mTextureChiseledTop;
    TextureAtlasSprite* mTextureLinesTop;
    TextureAtlasSprite* mTextureTop;
    TextureAtlasSprite* mTextureBottom;
};
