#include "net/minecraft/world/level/levelgen/synth/SimplexNoise.h"

#include "net/minecraft/world/Random.h"

#include <cmath>

const int SimplexNoise::GRAD[12][3]
    = {{1, 1, 0},  {-1, 1, 0},  {1, -1, 0}, {-1, -1, 0}, {1, 0, 1},  {-1, 0, 1},
       {1, 0, -1}, {-1, 0, -1}, {0, 1, 1},  {0, -1, 1},  {0, 1, -1}, {0, -1, -1}};
double SimplexNoise::F2 = (std::sqrt(3.0) - 1.0) * 0.5;
double SimplexNoise::G2 = (3.0 - std::sqrt(3.0)) / 6.0;

SimplexNoise::SimplexNoise(Random* random) {
    init(random);
}

void SimplexNoise::init(Random* random) {
    m_permutations = new int[512];
    m_x = random->nextDouble() * 256.0;
    m_y = random->nextDouble() * 256.0;
    m_z = random->nextDouble() * 256.0;
    for (int i = 0; i < 256; ++i)
        m_permutations[i] = i;
    for (int i = 0; i < 256; ++i) {
        int j = random->nextInt(256 - i) + i;
        int old = m_permutations[i];
        m_permutations[i] = m_permutations[j];
        m_permutations[j] = old;
        m_permutations[i + 256] = m_permutations[i];
    }
}

SimplexNoise::~SimplexNoise() {
    if (m_permutations)
        delete[] m_permutations;
}

int SimplexNoise::fastFloor(double value) {
    // 0x71003222f0 subtracts at zero and negative integers too.
    return static_cast<int>(value) - !(value > 0.0);
}

double SimplexNoise::dot(const int* gradient, double x, double y) {
    return gradient[0] * x + gradient[1] * y;
}

// NON_MATCHING: verified separately by original/rebuilt ARM64 execution.
double SimplexNoise::getValue(double x, double y) {
    double n0 = 0.0;
    double n1 = 0.0;
    double n2 = 0.0;
    double skew = (x + y) * F2;
    int cellX = fastFloor(x + skew);
    int cellY = fastFloor(y + skew);
    double unskew = G2 * (cellX + cellY);
    double x0 = x - (cellX - unskew);
    double y0 = y - (cellY - unskew);
    int stepX = x0 > y0 ? 1 : 0;
    int stepY = x0 > y0 ? 0 : 1;
    double x1 = G2 + (x0 - stepX);
    double y1 = G2 + (y0 - stepY);
    double twiceG2 = G2 + G2;
    double x2 = twiceG2 + (x0 + -1.0);
    double y2 = twiceG2 + (y0 + -1.0);
    int ix = cellX & 255;
    int iy = cellY & 255;
    int hash1 = m_permutations[ix + stepX + m_permutations[iy + stepY]];
    int hash2 = m_permutations[ix + 1 + m_permutations[iy + 1]];
    double weight = (0.5 - x0 * x0) - y0 * y0;
    if (!(weight < 0.0)) {
        int gradient0 = m_permutations[ix + m_permutations[iy]] % 12;
        weight *= weight;
        n0 = weight * weight * dot(GRAD[gradient0], x0, y0);
    }
    weight = (0.5 - x1 * x1) - y1 * y1;
    if (!(weight < 0.0)) {
        weight *= weight;
        n1 = weight * weight * dot(GRAD[hash1 % 12], x1, y1);
    }
    weight = (0.5 - x2 * x2) - y2 * y2;
    if (!(weight < 0.0)) {
        weight *= weight;
        n2 = weight * weight * dot(GRAD[hash2 % 12], x2, y2);
    }
    return (n0 + n1 + n2) * 70.0;
}

// The Switch region routine contains its own sampler body. Keep that copy
// here so the original floor/dot call sequence and floating-point order survive.
void SimplexNoise::add(arrayWithLength<double> output, double x, double y, int width, int height,
                       double scaleX, double scaleY, double amplitude) {
    int index = 0;
    for (int row = 0; row < height; ++row) {
        double sampleY = (row + y) * scaleY + m_y;
        for (int column = 0; column < width; ++column) {
            double sampleX = (column + x) * scaleX + m_x;
            double x = sampleX;
            double y = sampleY;
            double n0 = 0.0;
            double n1 = 0.0;
            double n2 = 0.0;
            double skew = (x + y) * F2;
            int cellX = fastFloor(x + skew);
            int cellY = fastFloor(y + skew);
            double unskew = G2 * (cellX + cellY);
            double x0 = x - (cellX - unskew);
            double y0 = y - (cellY - unskew);
            int stepX = x0 > y0 ? 1 : 0;
            int stepY = x0 > y0 ? 0 : 1;
            double x1 = G2 + (x0 - stepX);
            double y1 = G2 + (y0 - stepY);
            double twiceG2 = G2 + G2;
            double x2 = twiceG2 + (x0 + -1.0);
            double y2 = twiceG2 + (y0 + -1.0);
            int ix = cellX & 255;
            int iy = cellY & 255;
            int gradient1 = m_permutations[ix + stepX + m_permutations[iy + stepY]] % 12;
            int gradient2 = m_permutations[ix + 1 + m_permutations[iy + 1]] % 12;
            double weight = (0.5 - x0 * x0) - y0 * y0;
            if (!(weight < 0.0)) {
                int gradient0 = m_permutations[ix + m_permutations[iy]] % 12;
                weight *= weight;
                n0 = weight * weight * dot(GRAD[gradient0], x0, y0);
            }
            weight = (0.5 - x1 * x1) - y1 * y1;
            if (!(weight < 0.0)) {
                weight *= weight;
                n1 = weight * weight * dot(GRAD[gradient1], x1, y1);
            }
            weight = (0.5 - x2 * x2) - y2 * y2;
            if (!(weight < 0.0)) {
                weight *= weight;
                n2 = weight * weight * dot(GRAD[gradient2], x2, y2);
            }
            output[index++] += (n0 + n1 + n2) * 70.0 * amplitude;
        }
    }
}
