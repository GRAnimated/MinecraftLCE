#include "net/minecraft/world/level/storage/light/SparseLightStorage.h"

#include "NX/Platform.h"
#include <cstdlib>
#include <cstring>

void sparseLightMemSet(void*, int, std::size_t);

namespace {
const unsigned long long PointerMask = 0x0000ffffffffffffULL;
}

void SparseLightStorage::setLight(int x, int y, int z, int value) {
    unsigned char* indices;
    unsigned char* data;
    getBuffers(&indices, &data);
    signed char index = indices[y];
    if (index < 0) {
        if (value == 0 && index == -128)
            return;
        if (value == 15 && index == -127)
            return;
        {
            std::vector<int> layers;
            layers.push_back(y);
            expandLayers(layers);
        }
        getBuffers(&indices, &data);
        index = indices[y];
    }
    int xz = x * 16 + z;
    int half = xz / 2;
    int shift = (xz & 1) << 2;
    int mask = 0xf0 >> shift;
    int offset = static_cast<unsigned char>(index) * 128 + half;
    data[offset] = (mask & data[offset]) | (value << shift);
}

void SparseLightStorage::setFullBright() {
    unsigned char* buffer = allocate(128);
#pragma clang loop unroll(disable)
    for (long long i = 0; i != 128; i += 4)
        *reinterpret_cast<unsigned int*>(buffer + i) = 0x81818181;
    replace(reinterpret_cast<unsigned long long>(buffer) & PointerMask);
}

int SparseLightStorage::setDataRegion(arrayWithLength<unsigned char> source, int x0, int y0, int z0, int x1,
                                      int y1, int z1, int offset) {
    int height = y1 - y0;
    int first = y0 & ~1;
    int pairs = height / 2;
    {
        std::vector<int> layers;
        layers.reserve(pairs * 2);
        for (int i = 0, y = first; i < pairs; ++i, y += 2) {
            int layer = y;
            layers.push_back(layer);
            layers.push_back(layer + 1);
        }
        expandLayers(layers);
    }
    unsigned char* begin = source.m_data + offset;
    unsigned char* cursor = begin;
    for (; x0 < x1; ++x0) {
        for (int z = z0; z < z1; ++z) {
            long long i;
            int y = first;
            for (i = 0; static_cast<int>(i) < pairs; ++i, y += 2) {
                setLight(x0, y, z, cursor[i] & 15);
                setLight(x0, y + 1, z, cursor[i] >> 4);
            }
            cursor += i;
        }
    }
    return cursor - begin;
}

int SparseLightStorage::getDataRegion(arrayWithLength<unsigned char> output, int x0, int y0, int z0, int x1,
                                      int y1, int z1, int offset) {
    unsigned char* begin = output.m_data + offset;
    unsigned char* cursor = begin;
    if (x0 < x1) {
        int height = y1 - y0;
        int first = y0 & ~1;
        int pairs = height / 2;
        for (; x0 < x1; ++x0) {
            for (int z = z0; z < z1; ++z) {
                long long i;
                int y = first;
                for (i = 0; static_cast<int>(i) < pairs; ++i, y += 2) {
                    cursor[i] = getLight(x0, y, z);
                    cursor[i] |= getLight(x0, y + 1, z) << 4;
                }
                cursor += i;
            }
        }
    }
    return cursor - begin;
}
