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
            this->m_data = data;
            this->m_name = name;
            this->m_materialColor = materialColor;
            this->m_nameId = name_id;
            this->m_descId = desc_id;
            this->m_textureName = textureName;
            this->m_natural = natural;
        }

        void registerIcons(IconRegister* iconReg) {
            this->m_texture = iconReg->registerIcon(this->m_textureName);
        }

        int getData() { return this->m_data; }
        std::wstring getName() { return this->m_name; }
        int getNameId() { return this->m_nameId; }
        int getDescriptionId() { return this->m_descId; }
        const MaterialColor* getMaterialColor() { return this->m_materialColor; }
        bool isNatural() { return this->m_natural; }
        TextureAtlasSprite* getTexture() { return this->m_texture; }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        int m_data;
        std::wstring m_name;
        int m_nameId;
        int m_descId;
        const MaterialColor* m_materialColor;
        bool m_natural;
        std::wstring m_textureName;
        TextureAtlasSprite* m_texture;
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
