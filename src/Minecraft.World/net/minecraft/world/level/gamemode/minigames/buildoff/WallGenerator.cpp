#include "net/minecraft/world/level/gamemode/minigames/buildoff/WallGenerator.h"

// WallGenerator::WallGenerator(Random random, std::vector<AABB*>* walls, std::vector<AABB*>*) :
// MapGenerator(random) {}

WallGenerator::~WallGenerator() {
    for (auto it = this->m_walls.begin(); it != this->m_walls.end(); it++) {
        delete *it;
    }
}

// void WallGenerator::StartGeneration(Level* level) {}

const AABB* WallGenerator::GetSpawnArea() const {
    if (m_wallsAreas.size() == 0)
        return nullptr;

    return *m_wallsAreas.begin();
}

void WallGenerator::CleanUp(Level* level) {}

const AABB* WallGenerator::GetLayerBB(unsigned int) {
    return nullptr;
}

unsigned int WallGenerator::GetNumberOfLayers() {
    return 0;
}

void WallGenerator::GetLayerExtents(unsigned int, float* min, float* max) {}
