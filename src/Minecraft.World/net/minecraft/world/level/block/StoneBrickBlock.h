#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include <string>

class StoneBrickBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* DEFAULT;
        static Variant* MOSSY;
        static Variant* CRACKED;
        static Variant* CHISELED;

        static Variant* VARIANTS[4];

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, int translationKey) {
            this->m_data = data;
            this->m_name = name;
            this->m_translationKey = translationKey;
        }

        int getData() { return this->m_data; }
        int getTranslationKey() { return this->m_translationKey; }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        int m_data;
        std::wstring m_name;
        int m_translationKey;
    };

    static std::wstring TEXTURE_NAMES[4];
    static int DEFAULT_DATA;
    static int MOSSY_DATA;
    static int CRACKED_DATA;
    static int CHISELED_DATA;
    static inline EnumProperty<Variant*>* VARIANT;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);

    StoneBrickBlock();

    static void blockStaticCtor();

    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    unsigned int getDescriptionId(int) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;

    TextureAtlasSprite* m_variantsTextures[4];
};
