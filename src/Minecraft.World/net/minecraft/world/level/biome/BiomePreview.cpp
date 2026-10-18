#include "NX/Platform.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/world/level/biome/Biome.h"
#include "net/minecraft/world/level/biome/BiomeSource.h"
#include <cmath>

eMinecraftColour Biome::getPreviewColor() {
    return m_previewColor;
}

void BiomeSource::LayerOverrideSettings::UpdateBiomeMapPixelsInRegion(unsigned int* pixels, unsigned int x,
                                                                      unsigned int z, unsigned int width,
                                                                      unsigned int depth, bool& missing,
                                                                      bool unzoomed) {
    unsigned int scale = 1;
    int offsetX = 0;
    int offsetZ = 0;
    if (!unzoomed) {
        scale = static_cast<unsigned int>(std::pow(2.0, m_zoomLevel));
        if (isZoomed()) {
            int divisor = static_cast<int>(std::pow(2.0, m_zoomLevel + 1.0));
            offsetX = m_zoomX * m_field18 / divisor;
            offsetZ = m_zoomZ * m_field18 / divisor;
        }
    }
    int border = m_field18 - m_field18 / static_cast<int>(scale);
    int startZ = border + offsetZ + z / scale;
    unsigned int rows = depth / scale;
    ColourTable* colours = Minecraft::GetInstance()->getColourTable();
    int startX = border + offsetX + x / scale;
    unsigned int columns = width / scale;
    for (int row = startZ; row < static_cast<int>(startZ + rows); ++row) {
        for (unsigned int subRow = 0; subRow < scale; ++subRow) {
            unsigned int* target = pixels + x + m_imageWidth * (z + (row - startZ) * scale + subRow);
            for (int column = startX; column < static_cast<int>(startX + columns); ++column) {
                unsigned int index = getBiomeIndex(column, row);
                if (index < m_biomes.m_length) {
                    EnterCriticalSection(&m_mutexType);
                    unsigned int colour;
                    if (m_biomes.get(index) == nullptr) {
                        colour = 0;
                        missing = true;
                    } else {
                        colour = colours->getColour(m_biomes.get(index)->getPreviewColor());
                    }
                    LeaveCriticalSection(&m_mutexType);
                    colour |= 0xff000000;
                    for (unsigned int i = 0; i < scale; ++i)
                        *target++ = colour;
                }
            }
        }
    }
}
