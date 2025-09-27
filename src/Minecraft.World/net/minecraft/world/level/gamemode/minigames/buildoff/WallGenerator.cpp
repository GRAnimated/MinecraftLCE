#include "net/minecraft/world/level/gamemode/minigames/buildoff/WallGenerator.h"

// WallGenerator::WallGenerator(Random random, std::vector<AABB*>* walls, std::vector<AABB*>*) :
// MapGenerator(random) {}

WallGenerator::~WallGenerator() {
    for (auto it = this->mWalls.begin(); it != this->mWalls.end(); it++) {
        delete *it;
    }
}

// void WallGenerator::StartGeneration(Level* level) {}

const AABB* WallGenerator::GetSpawnArea() const {
    if (mWallsAreas.size() == 0)
        return nullptr;

    return *mWallsAreas.begin();
}

void WallGenerator::CleanUp(Level* level) {}

const AABB* WallGenerator::GetLayerBB(unsigned int) {
    return nullptr;
}

unsigned int WallGenerator::GetNumberOfLayers() {
    return 0;
}

void WallGenerator::GetLayerExtents(unsigned int, float* min, float* max) {}
