#include "net/minecraft/world/level/levelgen/synth/ImprovedNoise.h"

#include "net/minecraft/world/Random.h"

#include <cmath>

double ImprovedNoise::GRAD_X[16]
    = {1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0};
double ImprovedNoise::GRAD_Y[16]
    = {1.0, 1.0, -1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0};
double ImprovedNoise::GRAD_Z[16]
    = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 0.0, 1.0, 0.0, -1.0};
double ImprovedNoise::GRAD_2D_X[16]
    = {1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, -1.0, 0.0};
double ImprovedNoise::GRAD_2D_Z[16]
    = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0, -1.0, 0.0, 1.0, 0.0, -1.0};

ImprovedNoise::ImprovedNoise(Random* random) {
    init(random);
}

ImprovedNoise::~ImprovedNoise() {
    if (m_permutations)
        delete[] m_permutations;
}

void ImprovedNoise::init(Random* random) {
    m_permutations = new int[512];
    m_x = random->nextDouble() * 256.0;
    m_y = random->nextDouble() * 256.0;
    m_z = random->nextDouble() * 256.0;

    for (int i = 0; i < 256; i++) {
        m_permutations[i] = i;
    }
    for (int i = 0; i < 256; i++) {
        int j = random->nextInt(256 - i) + i;
        int old = m_permutations[i];
        m_permutations[i] = m_permutations[j];
        m_permutations[j] = old;
        m_permutations[i + 256] = m_permutations[i];
    }
}

// name guessed
// NON_MATCHING | score: 8895 (lower is better)
double ImprovedNoise::getValue(double x, double y, double z) {
    x += m_x;
    y += m_y;
    z += m_z;

    int floorX = static_cast<int>(x);
    int floorY = static_cast<int>(y);
    int floorZ = static_cast<int>(z);
    if (x < floorX)
        --floorX;
    if (y < floorY)
        --floorY;
    if (z < floorZ)
        --floorZ;

    int cellX = floorX & 255;
    int cellY = floorY & 255;
    int cellZ = floorZ & 255;
    x -= floorX;
    y -= floorY;
    z -= floorZ;

    double fadeX = x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
    double fadeY = y * y * y * (y * (y * 6.0 - 15.0) + 10.0);
    double fadeZ = z * z * z * (z * (z * 6.0 - 15.0) + 10.0);

    int a = m_permutations[cellX] + cellY;
    int aa = m_permutations[a] + cellZ;
    int ab = m_permutations[a + 1] + cellZ;
    int b = m_permutations[cellX + 1] + cellY;
    int ba = m_permutations[b] + cellZ;
    int bb = m_permutations[b + 1] + cellZ;

    return lerp(fadeZ,
                lerp(fadeY,
                     lerp(fadeX, grad(m_permutations[aa], x, y, z), grad(m_permutations[ba], x - 1.0, y, z)),
                     lerp(fadeX, grad(m_permutations[ab], x, y - 1.0, z),
                          grad(m_permutations[bb], x - 1.0, y - 1.0, z))),
                lerp(fadeY,
                     lerp(fadeX, grad(m_permutations[aa + 1], x, y, z - 1.0),
                          grad(m_permutations[ba + 1], x - 1.0, y, z - 1.0)),
                     lerp(fadeX, grad(m_permutations[ab + 1], x, y - 1.0, z - 1.0),
                          grad(m_permutations[bb + 1], x - 1.0, y - 1.0, z - 1.0))));
}

// name guessed
double ImprovedNoise::lerp(double weight, double a, double b) {
    return a + weight * (b - a);
}

// name guessed
double ImprovedNoise::grad(int hash, double x, double y, double z) {
    int index = hash & 15;
    return GRAD_X[index] * x + GRAD_Y[index] * y + GRAD_Z[index] * z;
}

double ImprovedNoise::getValue(double x, double y) {
    return getValue(x, y, 0.0);
}

// NON_MATCHING | score: 37870 (lower is better)
void ImprovedNoise::add(arrayWithLength<double> noise, double posX, double posY, double posZ, int width,
                        int depth, int length, double scaleX, double scaleY, double scaleZ,
                        double amplitude) {
    double x = m_x + posX;
    double inverseAmplitude = 1.0 / amplitude;
    int index = 0;

    // The single-layer path samples X/Z and deliberately ignores the Y offset.
    if (depth == 1) {
        for (int ix = 0; ix < width; ix++) {
            double floorX = std::floor(x);
            x -= floorX;
            double fadeX = x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
            double z = m_z + posZ;
            for (int iz = 0; iz < length; iz++) {
                double floorZ = std::floor(z);
                z -= floorZ;
                int cellX = static_cast<int>(floorX) & 255;
                int cellZ = static_cast<int>(floorZ) & 255;
                int a = m_permutations[m_permutations[cellX]] + cellZ;
                int b = m_permutations[m_permutations[cellX + 1]] + cellZ;
                double near
                    = lerp(fadeX, grad(m_permutations[a], x, z), grad(m_permutations[b], x - 1.0, 0.0, z));
                double far = lerp(fadeX, grad(m_permutations[a + 1], x, 0.0, z - 1.0),
                                  grad(m_permutations[b + 1], x - 1.0, 0.0, z - 1.0));
                double fadeZ = z * z * z * (z * (z * 6.0 - 15.0) + 10.0);
                noise[index++] += lerp(fadeZ, near, far) * inverseAmplitude;
                z = floorZ + z + scaleZ;
            }
            x = floorX + x + scaleX;
        }
        return;
    }

    // The binary caches 64 Y samples for the multi-layer path.
    struct YSample {
        double offset;
        double fade;
        int cell;
    };
    YSample samples[64];
    bool firstColumn = true;
    int lastCellY = -1;
    double nearLow = 0.0;
    double nearHigh = 0.0;
    double farLow = 0.0;
    double farHigh = 0.0;

    for (int ix = 0; ix < width; ix++) {
        double floorX = std::floor(x);
        x -= floorX;
        int cellX = static_cast<int>(floorX) & 255;
        double fadeX = x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
        double z = m_z + posZ;

        for (int iz = 0; iz < length; iz++) {
            double floorZ = std::floor(z);
            z -= floorZ;
            int cellZ = static_cast<int>(floorZ) & 255;
            double fadeZ = z * z * z * (z * (z * 6.0 - 15.0) + 10.0);
            double y = m_y + posY;

            for (int iy = 0; iy < depth; iy++) {
                double floorY = 0.0;
                double fadeY;
                int cellY;
                if (firstColumn) {
                    floorY = std::floor(y);
                    y -= floorY;
                    fadeY = y * y * y * (y * (y * 6.0 - 15.0) + 10.0);
                    cellY = static_cast<int>(floorY) & 255;
                    samples[iy].offset = y;
                    samples[iy].fade = fadeY;
                    samples[iy].cell = cellY;
                } else {
                    y = samples[iy].offset;
                    fadeY = samples[iy].fade;
                    cellY = samples[iy].cell;
                }

                // Reuse the gradients within each Y lattice cell.
                if (iy == 0 || cellY != lastCellY) {
                    int a = m_permutations[cellX] + cellY;
                    int aa = m_permutations[a] + cellZ;
                    int ab = m_permutations[a + 1] + cellZ;
                    int b = m_permutations[cellX + 1] + cellY;
                    int ba = m_permutations[b] + cellZ;
                    int bb = m_permutations[b + 1] + cellZ;
                    nearLow = lerp(fadeX, grad(m_permutations[aa], x, y, z),
                                   grad(m_permutations[ba], x - 1.0, y, z));
                    nearHigh = lerp(fadeX, grad(m_permutations[ab], x, y - 1.0, z),
                                    grad(m_permutations[bb], x - 1.0, y - 1.0, z));
                    farLow = lerp(fadeX, grad(m_permutations[aa + 1], x, y, z - 1.0),
                                  grad(m_permutations[ba + 1], x - 1.0, y, z - 1.0));
                    farHigh = lerp(fadeX, grad(m_permutations[ab + 1], x, y - 1.0, z - 1.0),
                                   grad(m_permutations[bb + 1], x - 1.0, y - 1.0, z - 1.0));
                    lastCellY = cellY;
                }

                double near = lerp(fadeY, nearLow, nearHigh);
                double far = lerp(fadeY, farLow, farHigh);
                noise[index++] += lerp(fadeZ, near, far) * inverseAmplitude;
                if (firstColumn)
                    y = floorY + y + scaleY;
            }
            z = floorZ + z + scaleZ;
            firstColumn = false;
        }
        x = floorX + x + scaleX;
    }
}

// name guessed
double ImprovedNoise::grad(int hash, double x, double z) {
    int index = hash & 15;
    return GRAD_2D_X[index] * x + GRAD_2D_Z[index] * z;
}
