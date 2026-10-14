#include "net/minecraft/world/level/levelgen/synth/PerlinSimplexNoise.h"

#include "NX/Platform.h"
#include "net/minecraft/world/level/levelgen/synth/SimplexNoise.h"

PerlinSimplexNoise::PerlinSimplexNoise(Random* random, int maxOctaves) {
    init(random, maxOctaves);
}

void PerlinSimplexNoise::init(Random* random, int maxOctaves) {
    MemSect(3);
    m_maxOctaves = maxOctaves;
    m_noiseLevels = new SimplexNoise*[maxOctaves];
    for (int i = 0; i < maxOctaves; ++i)
        m_noiseLevels[i] = new SimplexNoise(random);
    MemSect(0);
}

PerlinSimplexNoise::~PerlinSimplexNoise() {
    for (int i = 0; i < m_maxOctaves; ++i)
        delete m_noiseLevels[i];
    delete[] m_noiseLevels;
}

double PerlinSimplexNoise::getValue(double x, double y) {
    double result = 0.0;
    double scale = 1.0;
    for (int i = 0; i < m_maxOctaves; ++i) {
        result += m_noiseLevels[i]->getValue(scale * x, scale * y) / scale;
        scale *= 0.5;
    }
    return result;
}

arrayWithLength<double> PerlinSimplexNoise::getRegion(arrayWithLength<double> output, double x, double y,
                                                      int width, int height, double scaleX, double scaleY,
                                                      double octaveScale) {
    return getRegion(output, x, y, width, height, scaleX, scaleY, octaveScale, 0.5);
}

arrayWithLength<double> PerlinSimplexNoise::getRegion(arrayWithLength<double> output, double x, double y,
                                                      int width, int height, double scaleX, double scaleY,
                                                      double octaveScale, double persistence) {
    if (output.m_data && static_cast<int>(output.m_length) >= width * height) {
        for (unsigned int i = 0; i < output.m_length; ++i)
            output[i] = 0.0;
    } else {
        delete[] output.m_data;
        output = arrayWithLength<double>(width * height, true);
    }
    double frequency = 1.0;
    double amplitudeScale = 1.0;
    for (int i = 0; i < m_maxOctaves; ++i) {
        m_noiseLevels[i]->add(output, x, y, width, height, (scaleX / 1.5) * frequency,
                              (scaleY / 1.5) * frequency, 0.55 / amplitudeScale);
        frequency *= octaveScale;
        amplitudeScale *= persistence;
    }
    return output;
}
