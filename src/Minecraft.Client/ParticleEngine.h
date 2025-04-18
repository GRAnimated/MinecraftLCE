#pragma once

class Level;
class Textures;

class ParticleEngine {
public:
    ParticleEngine(Level* lvl, Textures* textures);

    unsigned char padding[0x250];
};