#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"

class SandStoneBlock : public Block {
public:
    class Variant : public StringRepresentable {
    public:
        static Variant* DEFAULT;
        static Variant* CHISELED;
        static Variant* SMOOTH;
        static Variant* VARIANTS[3];  // waste of memory...

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, unsigned int loc_id) {
            this->m_data = data;
            this->m_name = name;
            this->m_nameId = loc_id;
        }

        int getData() { return this->m_data; }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        int m_data;  // I would have named it id but they use data over and over again
        std::wstring m_name;
        unsigned int m_nameId;
    };

    SandStoneBlock();

    static void blockStaticCtor();

    static EnumProperty<Variant*>* TYPE;
    static inline Predicates<Variant*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<Variant*>::ConstantPredicate(true);
    static std::wstring VARIANT_TEXTURE_NAMES[3];
    static std::wstring SANDSTONE_TOP;
    static std::wstring SANDSTONE_BOTTOM;

    MaterialColor* getMapColor(const BlockState*, LevelSource*, const BlockPos&) override;
    const BlockState* getBlockState(int) override;
    int convertBlockStateToLegacyData(const BlockState*) override;
    int getSpawnResourcesAuxValue(const BlockState*) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTexture(const Direction*, const BlockState*) override;
    BlockStateDefinition* createBlockStateDefinition() override;

    TextureAtlasSprite* m_variantsTextures[3];
    TextureAtlasSprite* m_topTexture;
    TextureAtlasSprite* m_bottomTexture;
};
