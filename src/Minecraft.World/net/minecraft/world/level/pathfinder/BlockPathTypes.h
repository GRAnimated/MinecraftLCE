#pragma once

class BlockPathTypes {
public:
    static const BlockPathTypes* BLOCKED;
    static const BlockPathTypes* OPEN;
    static const BlockPathTypes* WALKABLE;
    static const BlockPathTypes* TRAPDOR;
    static const BlockPathTypes* FENCE;
    static const BlockPathTypes* LAVA;
    static const BlockPathTypes* WATER;
    static const BlockPathTypes* RAIL;
    static const BlockPathTypes* DANGER_FIRE;
    static const BlockPathTypes* DAMAGE_FIRE;
    static const BlockPathTypes* DANGER_CACTUS;
    static const BlockPathTypes* DAMAGE_CACTUS;
    static const BlockPathTypes* DANGER_OTHER;
    static const BlockPathTypes* DAMAGE_OTHER;
    static const BlockPathTypes* DOOR_OPEN;
    static const BlockPathTypes* DOOR_WOOD_CLOSED;
    static const BlockPathTypes* DOOR_IRON_CLOSED;

    BlockPathTypes(int ordinal, float maulus) {
        this->mOrdinal = ordinal;
        this->mMaulus = maulus;
    }

    int ordinal() const { return this->mOrdinal; }
    int getFlag() const { return 1 << this->mOrdinal; }
    float getMaulus() const { return this->mMaulus; }

    int mOrdinal;
    float mMaulus;
};
