#pragma once

#include <string>

class BiomeProperties {
public:
    BiomeProperties(std::wstring const&);
    void depth(float);
    void downfall(float);
    void dry(void);
    void mutated(std::wstring const&);
    void scale(float);
    void snow(void);
    void temperature(float);
    void waterColor(int);
};