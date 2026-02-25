#include "net/minecraft/world/level/newbiome/layer/BiomeCacheLayer.h"

#include "net/minecraft/world/level/newbiome/layer/IntCache.h"
#include <cmath>

BiomeCacheLayer::BiomeCacheLayer(long long seed, std::shared_ptr<Layer> parent, int xzSize,
                                 unsigned char biomeScale, int centreXChunk, int centreZChunk)
    : Layer((int)seed) {
    m_parent = parent;
    m_parentArea = {};
    m_worldSize = (int)((xzSize & 0xFFFFFFF) << 2);

    int pow = (int)std::pow(2, (double)biomeScale);
    int aa = (centreXChunk * pow) << 2;
    int bb = (centreZChunk * pow) << 2;
    m_xScale = aa - (int)(m_worldSize / 2);
    m_yScale = bb - (int)(m_worldSize / 2);
}

// NON_MATCHING | Score: 2939 (Lower is better)
arrayWithLength<int> BiomeCacheLayer::getArea(int x, int y, int width, int height) {
    m_parentArea = {static_cast<unsigned int>(m_worldSize * m_worldSize), true};
    arrayWithLength<int> parentArea = m_parent->getArea(m_xScale, m_yScale, m_worldSize, m_worldSize);

    for (int m = 0; m < m_parentArea.m_length; m++) {
        m_parentArea[m] = parentArea.get(m);
    }

    arrayWithLength<int> area = IntCache::allocate(width * height);

    int p = x - m_xScale;
    int o = y - m_yScale;
    for (int m = 0; m < height; m++) {
        for (int n = 0; n < width; n++) {
            int a = m_worldSize - 1;
            int b = m_worldSize - 1;

            if (p < a) {
                a = p;
            }

            if (m + o < b) {
                b = m + o;
            }

            area[n + m * width] = m_parentArea[(a & ~(a >> 31)) + (b & ~(b >> 31)) * m_worldSize];
        }
    }

    return area;
}
