#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/core/StringRepresentable.h"
#include "net/minecraft/world/level/block/FallingBlock.h"
#include "net/minecraft/world/level/block/state/EnumProperty.h"
#include "net/minecraft/world/level/block/state/properties/AbstractProperty.h"
#include <string>

class SandBlock : public FallingBlock {
public:
    class Variant : public StringRepresentable {
    public:
        static inline Variant* DEFAULT;
        static inline Variant* RED;

        static inline Variant* VARIANTS[2];  // waste of memory..., why not store them in array already

        static Variant* byData(int data) {
            // make it easier to just copy paste in every class (I mean the sizeofs)
            return VARIANTS[data > (sizeof(VARIANTS) / sizeof(Variant*)) - 1 ? 0 : data];
        }

        Variant(int data, const std::wstring& name, int name_id, int desc_id,
                const MaterialColor* materialColor, int dustColor) {
            this->m_data = data;
            this->m_name = name;
            this->m_materialColor = materialColor;
            this->m_nameId = name_id;
            this->m_descId = desc_id;
            this->m_dustColor = dustColor;
        }

        int getData() { return this->m_data; }
        std::wstring getName() { return this->m_name; }
        const MaterialColor* getMaterialColor() { return this->m_materialColor; }
        int getDustColor() { return this->m_dustColor; }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        int m_data;
        std::wstring m_name;
        const MaterialColor* m_materialColor;
        int m_nameId;
        int m_descId;
        int m_dustColor;
    };

    SandBlock();

    static void blockStaticCtor();

    static EnumProperty<Variant*>* VARIANT;
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
    int getDustColor(const BlockState*) override;

    TextureAtlasSprite* m_variantsTextures[2];
};
