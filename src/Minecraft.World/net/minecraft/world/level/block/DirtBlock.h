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

        // NON_MATCHING: reg swap, idk
        Variant(int data, const std::wstring& name, int nameId, int descriptionId,
                const MaterialColor* materialColor, const std::wstring& texName, const std::wstring& sideTex,
                const std::wstring& topTex) {
            this->m_data = data;
            this->m_name = name;
            this->m_nameId = nameId;
            this->m_descriptionId = descriptionId;
            this->m_materialColor = materialColor;
            this->m_textureName = texName;
            this->m_sideTextureName = sideTex;
            this->m_topTextureName = topTex;
            this->m_texture = nullptr;
            this->m_topTexture = nullptr;
            this->m_sideTexture = nullptr;
        }

        int getData() { return this->m_data; }
        const MaterialColor* getMaterialColor() { return this->m_materialColor; }
        int getNameId() { return this->m_nameId; }
        int getDescriptionId() { return this->m_descriptionId; }
        TextureAtlasSprite* getTexture(const Direction* dir) {
            TextureAtlasSprite* ret = this->m_topTexture;
            if (!ret || dir != Direction::UP) {
                ret = this->m_sideTexture;
                if (!ret || dir == Direction::UP || dir == Direction::DOWN) {
                    ret = this->m_texture;
                }
            }
            return ret;
        }
        void registerIcons(IconRegister* iconReg) {
            this->m_texture = iconReg->registerIcon(this->m_textureName);

            if (!m_topTextureName.empty())
                this->m_topTexture = iconReg->registerIcon(this->m_topTextureName);

            if (!m_sideTextureName.empty())
                this->m_sideTexture = iconReg->registerIcon(this->m_sideTextureName);
        }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        // I do not guarantee that those var names regarding textures are near correct...
        int m_data;
        std::wstring m_name;
        int m_nameId;
        int m_descriptionId;
        const MaterialColor* m_materialColor;
        std::wstring m_textureName;
        std::wstring m_topTextureName;
        std::wstring m_sideTextureName;
        TextureAtlasSprite* m_texture;
        TextureAtlasSprite* m_topTexture;
        TextureAtlasSprite* m_sideTexture;
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
