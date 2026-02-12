#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/world/level/block/RotatedPillarBlock.h"
#include <string>

class LogBlock : public RotatedPillarBlock {
public:
    class LogAxis : public StringRepresentable {
    public:
        static LogAxis* X;
        static LogAxis* Y;
        static LogAxis* Z;
        static LogAxis* NONE;

        static LogAxis* VALUES[4];

        static LogAxis* fromAxis(Direction::Axis* axis) {
            switch (axis->getId()) {
            case 0:
                return X;
            case 1:
                return Y;
            case 2:
                return Z;
            default:
                return NONE;
            }
        }

        LogAxis(const std::wstring& name) { this->m_name = name; }

        int getId() {
            if (this == VALUES[0])
                return 0;
            else if (this == VALUES[1])
                return 1;
            else if (this == VALUES[2])
                return 2;
            else
                return 3;
        }

        std::wstring toString() const override { return this->m_name; }
        std::wstring getSerializedName() const override { return this->m_name; }

        std::wstring m_name;
    };

    LogBlock();

    static EnumProperty<LogAxis*>*
        LOG_AXIS;  // both this and rotatedPillarBlock has the same name so named it this so no confusion
    static inline Predicates<LogAxis*>::ConstantPredicate*
        PREDICATE  // idk how to get same behaviour as 0x7100327C74
        = new Predicates<LogAxis*>::ConstantPredicate(true);
    static const unsigned int DESCRIPTION_IDS[6];
    static std::wstring LOG_VARIANTS[6];

    static void blockStaticCtor();

    const BlockState* rotate(const BlockState* state, Rotation*) override;
    void onRemove(Level*, const BlockPos&, const BlockState* state) override;
    const BlockState* getStateForPlacement(Level*, const BlockPos&, const Direction*, float, float, float,
                                           int, std::shared_ptr<LivingEntity>) override;
    unsigned int getDescriptionId(int) override;
    void registerIcons(IconRegister*) override;
    TextureAtlasSprite* getTypeTexture(const BlockState* state) override;
    TextureAtlasSprite* getTopTexture(const BlockState* state) override;
    Direction::Axis* getAxis(const BlockState* state) override;
    virtual int getWoodType(const BlockState* state) = 0;

    TextureAtlasSprite* m_typeTextures[6];
    TextureAtlasSprite* m_topTextures[6];
};
