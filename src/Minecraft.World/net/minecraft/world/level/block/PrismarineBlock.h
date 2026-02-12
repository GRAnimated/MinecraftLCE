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
            this->m_data = data;
            this->m_name = name;
            this->m_nameId = nameId;
            this->m_descriptionId = descriptionId;
            this->m_textureName = textureName;
        }

        int getData() { return this->m_data; }
        TextureAtlasSprite* getTexture() { return this->m_texture; }
        int getNameId() { return this->m_nameId; }
        int getDescriptionId() { return this->m_descriptionId; }

        void registerIcons(IconRegister* iconReg) {
            this->m_texture = iconReg->registerIcon(this->m_textureName);
        }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        int m_data;
        std::wstring m_name;
        int m_nameId;
        int m_descriptionId;
        std::wstring m_textureName;
        TextureAtlasSprite* m_texture;
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
