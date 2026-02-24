#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"

#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"
#include "net/minecraft/client/renderer/MemoryTracker.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/vertex/Tesselator.h"
#include <cfloat>
#include <cstddef>

void BufferBuilder::Bounds::initBounds() {
    m_bounds[0] = FLT_MAX;
    m_bounds[1] = FLT_MAX;
    m_bounds[2] = FLT_MAX;
    m_bounds[3] = -FLT_MAX;
    m_bounds[4] = -FLT_MAX;
    m_bounds[5] = -FLT_MAX;
}

void BufferBuilder::Bounds::addBounds(BufferBuilder::Bounds& other) {
    if (other.m_bounds[0] < m_bounds[0])
        m_bounds[0] = other.m_bounds[0];
    if (other.m_bounds[1] < m_bounds[1])
        m_bounds[1] = other.m_bounds[1];
    if (other.m_bounds[2] < m_bounds[2])
        m_bounds[2] = other.m_bounds[2];
    if (other.m_bounds[3] > m_bounds[3])
        m_bounds[3] = other.m_bounds[3];
    if (other.m_bounds[4] > m_bounds[4])
        m_bounds[4] = other.m_bounds[4];
    if (other.m_bounds[5] > m_bounds[5])
        m_bounds[5] = other.m_bounds[5];
}

void BufferBuilder::Bounds::addVert(float x, float y, float z) {
    if (x < m_bounds[0])
        m_bounds[0] = x;
    if (y < m_bounds[1])
        m_bounds[1] = y;
    if (z < m_bounds[2])
        m_bounds[2] = z;
    if (x > m_bounds[3])
        m_bounds[3] = x;
    if (y > m_bounds[4])
        m_bounds[4] = y;
    if (z > m_bounds[5])
        m_bounds[5] = z;
}

// NON_MATCHING probably some ordering thing, i have no idea
BufferBuilder::BufferBuilder(int bufSize) {
    m_hasColor = false;
    m_hasTex = false;
    m_byte26 = false;
    m_hasNormal = false;
    m_bufferIndex = 0;
    m_dword3c = 0;
    m_noColor = false;
    m_hasBegun = false;
    m_byte6e = false;
    m_hasBoneIndex = false;
    m_texV = 0;
    m_texU = 0;
    m_vertexCount = 0;
    m_packedColor = 0;
    m_primitiveMode = (C4JRender::ePrimitiveType)0;
    m_bucket = 0;
    m_useCompactVerts = false;
    m_useProjectedTex = false;
    m_isMipmapEnabled = true;
    m_dword30 = 0;
    m_vertType = (C4JRender::eVertexType)0;
    m_bufferSize = bufSize;
    m_xo = 0;
    m_yo = 0;
    m_zo = 0;
    m_dword54 = 0;
    m_dword58 = 0;
    m_dword5c = 0;
    m_packedNormal = 0;
    m_boneIndex = 0;

    m_vertexData = new arrayWithLength<int>(bufSize, true);
    m_field8 = new arrayWithLength<uchar>((0 > bufSize ? bufSize + 7 : bufSize) >> 3, true);

    m_byte6e = BufferBuilder::VBO_MODE;
    if (BufferBuilder::VBO_MODE) {
        m_field70 = MemoryTracker::createIntBuffer(m_field7c);
        sub_710063830c();
    }

    m_byte39 = false;
}

// NON_MATCHING just random to make other things match
void BufferBuilder::sub_710063830c() {
    asm volatile("" ::: "memory");
}

void BufferBuilder::clear() {
    m_vertexCount = 0;
    m_bufferIndex = 0;
    m_dword3c = 0;
}

void BufferBuilder::begin(int type) {
    m_hasBegun = true;
    clear();
    m_primitiveMode = (C4JRender::ePrimitiveType)type;
    m_hasColor = false;
    m_hasTex = false;
    m_byte26 = 0;
    m_hasNormal = false;
    m_noColor = false;
    m_hasBoneIndex = false;
}

void BufferBuilder::begin() {
    begin(C4JRender::ePrimitiveType::eViewportType_Quad);
    m_bounds.initBounds();
}

void BufferBuilder::normal(float x, float y, float z) {
    m_hasNormal = true;
    uint8_t nx = (uint8_t)(x * 127.0f) & 0xFF;
    uint8_t ny = (uint8_t)(y * 127.0f) & 0xFF;
    uint8_t nz = (uint8_t)(z * 127.0f) & 0xFF;
    m_packedNormal = (nx) | ((ny) << 8) | ((nz) << 16);
}

void BufferBuilder::tex(float u, float v) {
    m_hasTex = true;
    m_texU = u;
    m_texV = v;
}

void BufferBuilder::finaliseShaders() {
    m_dword30 = 0;
    m_vertType = (C4JRender::eVertexType)0;
    if (m_primitiveMode == 3 && BufferBuilder::TRIANGLE_MODE) {
        if (m_hasBoneIndex) {
            this->m_vertType = (C4JRender::eVertexType)8;
        } else if (this->m_useCompactVerts) {
            this->m_vertType = (C4JRender::eVertexType)1;
        }

        if (this->m_useProjectedTex)
            this->m_dword30 = 4;
    } else {
        if (m_useCompactVerts) {
            m_vertType = (C4JRender::eVertexType)1;
        } else if (m_hasBoneIndex) {
            m_vertType = (C4JRender::eVertexType)8;
        } else if (m_useProjectedTex) {
            m_dword30 = 4;
            m_vertType = (C4JRender::eVertexType)3;
        }
    }
}

void BufferBuilder::end() {
    m_hasBegun = false;
    if (!m_byte39)
        finaliseShaders();

    if (m_vertexCount >= 1) {
        if (!m_hasColor) {
            int* p = m_vertexData->m_data + 5;
            for (int i = 0; i < this->m_vertexCount; i++) {
                *p = 0xFFFFFFFF;
                p += 8;
            }
        }

        if (this->m_primitiveMode == 3 && BufferBuilder::TRIANGLE_MODE) {
            Renderer::sInstance->DrawVertices((C4JRender::ePrimitiveType)0, m_vertexCount,
                                              m_vertexData->m_data, this->m_vertType,
                                              (Renderer::ePixelShaderType)this->m_dword30, nullptr);
        } else {
            if (this->m_useCompactVerts) {
                Renderer::sInstance->DrawVertices(
                    this->m_primitiveMode, m_vertexCount, m_vertexData->m_data, this->m_vertType,
                    (Renderer::ePixelShaderType)this->m_dword30, m_field8->m_data);
            } else {
                Renderer::sInstance->DrawVertices(this->m_primitiveMode, m_vertexCount, m_vertexData->m_data,
                                                  this->m_vertType,
                                                  (Renderer::ePixelShaderType)this->m_dword30, nullptr);
            }
        }

        GlStateManager::disableClientState(0);
        if (m_hasTex)
            GlStateManager::disableClientState(0);
        if (m_hasColor)
            GlStateManager::disableClientState(0);
        if (m_hasNormal)
            GlStateManager::disableClientState(0);
    }

    clear();
}

// NON_MATCHING i have no idea, i'm tired of this function
void BufferBuilder::vertexNoBounds(float x, float y, float z) {
    m_vertexCount++;
    float finalTexU = !m_isMipmapEnabled ? m_texU + 1.0f : m_texU;

    if (!m_useCompactVerts) {
        if ((m_vertexCount & 3) == 0 && m_primitiveMode == 3 && BufferBuilder::TRIANGLE_MODE) {
            if (m_hasTex) {
                m_vertexData->m_data[(int)(m_bufferIndex + 3)]
                    = m_vertexData->m_data[(int)(m_bufferIndex - 21)];
                m_vertexData->m_data[(int)(m_bufferIndex + 4)]
                    = m_vertexData->m_data[(int)(m_bufferIndex - 20)];
            }

            if (m_hasColor) {
                m_vertexData->m_data[(int)(m_bufferIndex + 5)]
                    = m_vertexData->m_data[(int)(m_bufferIndex - 19)];
            }

            int* ptr = m_vertexData->m_data + (int)m_bufferIndex;
            *ptr = *(ptr - 24);
            m_vertexData->m_data[(int)(m_bufferIndex + 1)] = m_vertexData->m_data[(int)(m_bufferIndex - 23)];
            m_vertexData->m_data[(int)(m_bufferIndex + 2)] = m_vertexData->m_data[(int)(m_bufferIndex - 22)];

            m_vertexCount++;
            m_bufferIndex += 8;

            if (m_hasTex) {
                m_vertexData->m_data[(int)(m_bufferIndex + 11)]
                    = m_vertexData->m_data[(int)(m_bufferIndex - 5)];
                m_vertexData->m_data[(int)(m_bufferIndex + 4)]
                    = m_vertexData->m_data[(int)(m_bufferIndex - 12)];
            }
            if (m_hasColor) {
                m_vertexData->m_data[(int)(m_bufferIndex + 5)]
                    = m_vertexData->m_data[(int)(m_bufferIndex - 11)];
            }

            ptr = m_vertexData->m_data + (int)m_bufferIndex;
            *ptr = *(ptr - 16);
            m_vertexData->m_data[(int)(m_bufferIndex + 1)] = m_vertexData->m_data[(int)(m_bufferIndex - 15)];
            m_vertexData->m_data[(int)(m_bufferIndex + 2)] = m_vertexData->m_data[(int)(m_bufferIndex - 14)];

            m_vertexCount++;
            m_bufferIndex += 8;
        }

        if (m_hasTex) {
            float* data = (float*)m_vertexData->m_data;
            int idx = m_bufferIndex;
            data[idx + 3] = finalTexU;
            data[idx + 4] = m_texV;
        }

        if (m_hasColor) {
            m_vertexData->m_data[(int)m_bufferIndex + 5] = m_packedColor;
        }

        if (m_hasNormal) {
            m_vertexData->m_data[(int)m_bufferIndex + 6] = m_packedNormal;
        }

        if (m_hasBoneIndex) {
            m_vertexData->m_data[(int)m_bufferIndex + 7] = (int)m_boneIndex;
        }

        int col = m_byte26 ? *(int*)(&m_dword1c) : 0xFE00FE00;
        m_vertexData->m_data[(int)m_bufferIndex + 7] = col;

        float* data = (float*)m_vertexData->m_data + (int)m_bufferIndex;
        int idx = (int)m_bufferIndex;
        data[0] = m_xo + x;
        data[1] = m_yo + y;
        data[2] = m_zo + z;

        m_bufferIndex += 8;
        m_vertexCount++;

        if ((m_vertexCount & 3) == 0 && (int)m_bufferIndex >= (m_bufferSize - 32)) {
            end();
            m_hasBegun = true;
        }
    } else {
        short* vertexPtr = (short*)(m_vertexData->m_data + ((int)m_bufferIndex));
        int color = m_packedColor;

        vertexPtr[0] = ((m_xo + x) * 1024.0f);
        vertexPtr[1] = ((m_yo + y) * 1024.0f);
        vertexPtr[2] = ((m_zo + z) * 1024.0f);

        vertexPtr[3]
            = (((color >> 16) & 0xF800) | ((color >> 13) & 0x07E0) | ((color >> 11) & 0x001F)) + 0x8000;

        vertexPtr[4] = (finalTexU * 8192.0f);
        vertexPtr[5] = (m_texV * 8192.0f);

        vertexPtr[6] = (m_short1c << 8) | m_short1e;
        vertexPtr[7] = (short)(-m_dword54);

        m_bufferIndex += 4;
        m_vertexCount++;

        if ((m_vertexCount & 3) == 0) {
            if ((int)m_bufferIndex > 0x3FFEF || (int)m_bufferIndex >= (m_bufferSize - 16)) {
                end();
                m_hasBegun = true;
            }
        }

        if ((m_vertexCount & 3) == 0) {
            int paddingValue = m_bucket;
            if (paddingValue == 0) {
                m_bucket = 0;
            }
            uchar* pack = m_field8->m_data;

            int vertIndex = m_vertexCount;
            if ((int)vertIndex < 0) {
                vertIndex += 3;
            }
            pack[(vertIndex >> 2) - 1] = (char)paddingValue;
            m_bucket = 0;
        }
    }
}

void BufferBuilder::vertex(float x, float y, float z) {
    m_bounds.addVert(m_xo + x, m_yo + y, m_zo + z);
    vertexNoBounds(x, y, z);
}

void BufferBuilder::vertexUV(float x, float y, float z, float u, float v) {
    tex(u, v);
    vertex(x, y, z);
}

void BufferBuilder::useCompactVertices(bool value) {
    m_useCompactVerts = value & 1;
}

void BufferBuilder::useProjectedTexture(bool value) {
    m_useProjectedTex = value & 1;
}

void BufferBuilder::tex2(int value) {
    m_byte26 = 1;
    m_dword1c = value;
}

void BufferBuilder::color(int r, int g, int b, int a) {
    if (m_noColor == false) {
        if (r > 0xFE)
            r = 0xFF;
        if (g > 0xFE)
            g = 0xFF;
        if (b > 0xFE)
            b = 0xFF;
        if (a > 0xFE)
            a = 0xFF;

        if (a < 1)
            a = 0;
        if (r < 1)
            r = 0;
        if (g < 1)
            g = 0;
        if (b < 1)
            b = 0;

        m_hasColor = true;
        m_packedColor = r << 24 | g << 16 | b << 8 | a;
    }
}

void BufferBuilder::color(int r, int g, int b) {
    color(r, g, b, 0xFF);
}

void BufferBuilder::color(float r, float g, float b) {
    int ri = r * 255.0f;
    int gi = g * 255.0f;
    int bi = b * 255.0f;
    color(ri, gi, bi);
}

void BufferBuilder::color(float r, float g, float b, float a) {
    int ri = r * 255.0f;
    int gi = g * 255.0f;
    int bi = b * 255.0f;
    int ai = a * 255.0f;
    color(ri, gi, bi, ai);
}

void BufferBuilder::boneIndex(int index) {
    m_hasBoneIndex = true;
    m_boneIndex = index;
}

void BufferBuilder::vertexUVSkinned(float x, float y, float z, float u, float v, int index) {
    tex(u, v);
    boneIndex(index);
    vertex(x, y, z);
}

void BufferBuilder::color(int rgb) {
    color(rgb >> 16 & 0xff, rgb >> 8 & 0xff, rgb & 0xff);
}

void BufferBuilder::color(int rgb, int alpha) {
    color(rgb >> 16 & 0xff, rgb >> 8 & 0xff, rgb & 0xff, alpha);
}

void BufferBuilder::noColor() {
    m_noColor = true;
}

void BufferBuilder::offset(float xo, float yo, float zo) {
    m_xo = xo;
    m_yo = yo;
    m_zo = zo;
    m_dword54 = xo;
    m_dword58 = yo;
    m_dword5c = zo;
}

void BufferBuilder::addOffset(float xo, float yo, float zo) {
    m_xo += xo;
    m_yo += yo;
    m_zo += zo;
}

bool BufferBuilder::setMipmapEnable(bool value) {
    bool old = m_isMipmapEnabled;
    m_isMipmapEnabled = value;
    return old;
}

void BufferBuilder::bucket(int value) {
    m_bucket = value;
}

int BufferBuilder::hasMaxVertices() {
    return 0;
}

void BufferBuilder::setVertexFormat(const VertexFormat*) {}

void BufferBuilder::blockRainQuad(float x1, float y1, float z1, float u1, float v1, float x2, float y2,
                                  float z2, float u2, float v2, float x3, float y3, float z3, float u3,
                                  float v3, float x4, float y4, float z4, float u4, float v4, float r1,
                                  float g1, float b1, float a1, float r2, float g2, float b2, float a2,
                                  int texture) {
    float stack_u4 = u4;
    float stack_v4 = v4;
    float stack_u3 = u3;
    float stack_v3 = v3;
    float stack_u2 = u2;
    float stack_v2 = v2;
    float stack_u1 = u1;
    float stack_v1 = v1;
    float stack_x1 = x1;
    float stack_r2 = r2;
    float stack_g2 = g2;
    float stack_b2 = b2;
    float stack_a2 = a2;

    m_byte26 = true;
    m_hasColor = true;
    m_hasTex = true;

    float* vertexPtr = (float*)&m_vertexData->m_data[(int)m_bufferIndex];

    m_dword3c += 4;
    m_bufferIndex += 32;
    m_vertexCount += 4;

    const float colorScale = 255.0f;

    int packedColor1 = ((int)(r1 * colorScale) << 24) | ((int)(g1 * colorScale) << 16)
                       | ((int)(b1 * colorScale) << 8) | (int)(a1 * colorScale);

    m_bounds.addVert(m_xo + x1, m_yo + y1, m_zo + z1);
    vertexPtr[0] = m_xo + x1;
    vertexPtr[1] = m_yo + y1;
    vertexPtr[2] = m_zo + z1;
    vertexPtr[3] = stack_u1;
    vertexPtr[4] = stack_v1;
    *(int*)&vertexPtr[5] = packedColor1;
    *(int*)&vertexPtr[7] = texture;

    m_bounds.addVert(m_xo + x2, m_yo + y2, m_zo + z2);
    vertexPtr[8] = m_xo + x2;
    vertexPtr[9] = m_yo + y2;
    vertexPtr[10] = m_zo + z2;
    vertexPtr[11] = stack_u2;
    vertexPtr[12] = stack_v2;
    *(int*)&vertexPtr[13] = packedColor1;
    *(int*)&vertexPtr[15] = texture;

    int packedColor2 = ((int)(stack_r2 * colorScale) << 24) | ((int)(stack_g2 * colorScale) << 16)
                       | ((int)(stack_b2 * colorScale) << 8) | (int)(stack_a2 * colorScale);

    m_bounds.addVert(m_xo + x3, m_yo + y3, m_zo + z3);
    vertexPtr[16] = m_xo + x3;
    vertexPtr[17] = m_yo + y3;
    vertexPtr[18] = m_zo + z3;
    vertexPtr[19] = stack_u3;
    vertexPtr[20] = stack_v3;
    *(int*)&vertexPtr[21] = packedColor2;
    *(int*)&vertexPtr[23] = texture;

    m_bounds.addVert(m_xo + x4, m_yo + y4, m_zo + z4);
    vertexPtr[24] = m_xo + x4;
    vertexPtr[25] = m_yo + y4;
    vertexPtr[26] = m_zo + z4;
    vertexPtr[27] = stack_u4;
    vertexPtr[28] = stack_v4;
    *(int*)&vertexPtr[29] = packedColor2;
    *(int*)&vertexPtr[31] = texture;

    if ((m_vertexCount & 3) == 0 && (int)m_bufferIndex >= m_bufferSize - 0x20) {
        end();
        m_hasBegun = 1;
    }
}
