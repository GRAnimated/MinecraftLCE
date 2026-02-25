#pragma once

#include "net/minecraft/world/level/gamemode/minigames/MapGenerator.h"

class WallGenerator : public MapGenerator {
public:
    class Wall {
    public:
        Wall(AABB* boundaries, bool, bool);
        ~Wall();

        AABB* m_boundaries;
        bool m_unk8;
        bool m_unk9;
    };

    WallGenerator(Random random, std::vector<AABB*>*, std::vector<AABB*>*);

    ~WallGenerator() override;
    void StartGeneration(Level*) override;
    const AABB* GetSpawnArea() const override;
    void CleanUp(Level*) override;
    const AABB* GetLayerBB(unsigned int) override;
    unsigned int GetNumberOfLayers() override;
    void GetLayerExtents(unsigned int, float*, float*) override;

    std::vector<AABB*> m_wallsAreas;
    std::vector<Wall*> m_walls;
    AABB* m_unkAabb;
};
