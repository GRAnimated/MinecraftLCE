#pragma once

class Level;
class Textures;

class ParticleEngine {
public:
    ParticleEngine(Level* level, Textures* textures);

    unsigned char size[0x250];
};
