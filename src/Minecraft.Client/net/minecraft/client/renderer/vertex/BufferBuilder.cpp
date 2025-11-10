#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/vertex/BufferBuilder.h"
#include "net/minecraft/client/renderer/vertex/Tesselator.h"
#include <cstddef>


// TODO: figure those out
bool globalEnableFlag;
bool DAT_71017c2159;


// TODO: implement, this is an hack to match stuff
void* MemoryTracker::createIntBuffer(int size) {
#ifdef MATCHING_HACK
    asm volatile("" ::: "memory");
#endif
    return (void*)(long)size;  // yea i know. this is a stub anyway lol
}

// idk why those float numbers (maybe default hex values) but this gets it to 100%
void BufferBuilder::Bounds::initBounds() {
    bounds[0] = 3.4028235e+38;
    bounds[1] = 3.4028235e+38;
    bounds[2] = 3.4028235e+38;
    bounds[3] = -3.4028235e+38;
    bounds[4] = -3.4028235e+38;
    bounds[5] = -3.4028235e+38;
}

void BufferBuilder::Bounds::addBounds(BufferBuilder::Bounds& other) {
    if (other.bounds[0] < bounds[0])
        bounds[0] = other.bounds[0];
    if (other.bounds[1] < bounds[1])
        bounds[1] = other.bounds[1];
    if (other.bounds[2] < bounds[2])
        bounds[2] = other.bounds[2];
    if (other.bounds[3] > bounds[3])
        bounds[3] = other.bounds[3];
    if (other.bounds[4] > bounds[4])
        bounds[4] = other.bounds[4];
    if (other.bounds[5] > bounds[5])
        bounds[5] = other.bounds[5];
}

void BufferBuilder::Bounds::addVert(float x, float y, float z) {
    if (x < bounds[0])
        bounds[0] = x;
    if (y < bounds[1])
        bounds[1] = y;
    if (z < bounds[2])
        bounds[2] = z;
    if (x > bounds[3])
        bounds[3] = x;
    if (y > bounds[4])
        bounds[4] = y;
    if (z > bounds[5])
        bounds[5] = z;
}

BufferBuilder::BufferBuilder(int bufSize) {
    mHasColor = false;
    mHasTex = false;
    byte_26 = false;
    mHasNormal = false;
    mBufferIndex = 0;
    dword_3c = 0;
    mNoColor = false;
    mHasBegun = false;
    byte_6e = false;
    mHasBoneIndex = false;
    mTexV = 0;
    mTexU = 0;
    mVertexCount = 0;
    mPackedColor = 0;
    mPrimitiveMode = (C4JRender::ePrimitiveType)0;
    mBucket = 0;
    mUseCompactVerts = false;
    mUseProjectedTex = false;
    mIsMipmapEnabled = true;
    dword_30 = 0;
    mVertType = (C4JRender::eVertexType)0;
    mBufferSize = bufSize;
    mXo = 0;
    mYo = 0;
    mZo = 0;
    dword_54 = 0;
    dword_58 = 0;
    dword_5c = 0;
    mPackedNormal = 0;
    mBoneIndex = 0;


    mVertexData = new arrayWithLength<int>(bufSize, true);
    field_8 = new arrayWithLength<uchar>((0 > bufSize ? bufSize + 7 : bufSize) >> 3, true);

    byte_6e = DAT_71017c2159;
    if (DAT_71017c2159) {
        field_70 = MemoryTracker::createIntBuffer(field_7c);
        sub_710063830c();
    }


    byte_39 = false;
}

void BufferBuilder::sub_710063830c() {
#ifdef MATCHING_HACK 
    asm volatile("" ::: "memory");
#endif
}

void BufferBuilder::clear() {
    mVertexCount = 0;
    mBufferIndex = 0;
    dword_3c = 0;
}

void BufferBuilder::begin(int type) {
    mHasBegun = true;
    clear();
    mPrimitiveMode = (C4JRender::ePrimitiveType)type;
    mHasColor = false;
    mHasTex = false;
    byte_26 = 0;
    mHasNormal = false;
    mNoColor = false;
    mHasBoneIndex = false;
}

void BufferBuilder::begin() {
    begin(C4JRender::ePrimitiveType::eViewportType_Quad);
    mBounds.initBounds();
}

void BufferBuilder::normal(float x, float y, float z) {
    mHasNormal = true;
    uint8_t nx = (uint8_t)(x * 127.0f) & 0xFF;
    uint8_t ny = (uint8_t)(y * 127.0f) & 0xFF;
    uint8_t nz = (uint8_t)(z * 127.0f) & 0xFF;
    mPackedNormal = (nx) | ((ny) << 8) | ((nz) << 16);
}

void BufferBuilder::tex(float u, float v) {
    mHasTex = true;
    mTexU = u;
    mTexV = v;
}

void BufferBuilder::finaliseShaders() {
    dword_30 = 0;
    mVertType = (C4JRender::eVertexType)0;
    if (mPrimitiveMode == 3 && globalEnableFlag) {
        if (mHasBoneIndex) {
            this->mVertType = (C4JRender::eVertexType)8;
        } else if (this->mUseCompactVerts) {
            this->mVertType = (C4JRender::eVertexType)1;
        }
        
        if (this->mUseProjectedTex)
            this->dword_30 = 4;
    } else {
        if (mUseCompactVerts) {
            mVertType = (C4JRender::eVertexType)1;
        } else if (mHasBoneIndex) {
            mVertType = (C4JRender::eVertexType)8;
        } else if (mUseProjectedTex) {
            dword_30 = 4;
            mVertType = (C4JRender::eVertexType)3;
        }
    }
}

void BufferBuilder::end() {
    mHasBegun = false;
    if (!byte_39)
        finaliseShaders();

    if (mVertexCount >= 1) {
        if (!mHasColor) {
            int* p = mVertexData->data + 5;
            for (int i = 0; i < this->mVertexCount; i++) {
                *p = 0xFFFFFFFF;
                p += 8;
            }
        }
    
        if (this->mPrimitiveMode == 3 && globalEnableFlag) {
            Renderer::sInstance->DrawVertices((C4JRender::ePrimitiveType)0, mVertexCount, mVertexData->data,
                                              this->mVertType, (Renderer::ePixelShaderType)this->dword_30,
                                              nullptr);
        } else {
            if (this->mUseCompactVerts) {
                Renderer::sInstance->DrawVertices(this->mPrimitiveMode, mVertexCount, mVertexData->data,
                                                  this->mVertType, (Renderer::ePixelShaderType)this->dword_30,
                                                  field_8->data);
            } else {
                Renderer::sInstance->DrawVertices(this->mPrimitiveMode, mVertexCount, mVertexData->data,
                                                  this->mVertType, (Renderer::ePixelShaderType)this->dword_30,
                                                  nullptr);
            }
        }  
        
        GlStateManager::disableClientState(0);
        if (mHasTex)
            GlStateManager::disableClientState(0);
        if (mHasColor)
            GlStateManager::disableClientState(0);
        if (mHasNormal)
            GlStateManager::disableClientState(0);
    }

    clear();
}

void BufferBuilder::vertexNoBounds(float x, float y, float z) {
    mVertexCount++;
    float finalTexU = !mIsMipmapEnabled ? mTexU + 1.0f : mTexU;

    if (!mUseCompactVerts) {
        
        if ((mVertexCount & 3) == 0 && mPrimitiveMode == 3 && globalEnableFlag) {

            if (mHasTex) {
                mVertexData->data[(int)(mBufferIndex + 3)] = mVertexData->data[(int)(mBufferIndex - 21)];
                mVertexData->data[(int)(mBufferIndex + 4)] = mVertexData->data[(int)(mBufferIndex - 20)];
            }
            
            if (mHasColor) {
                mVertexData->data[(int)(mBufferIndex + 5)] = mVertexData->data[(int)(mBufferIndex - 19)];
            }

          
            int* ptr = mVertexData->data + (int)mBufferIndex;
            *ptr = *(ptr - 24);
            mVertexData->data[(int)(mBufferIndex + 1)] = mVertexData->data[(int)(mBufferIndex - 23)];
            mVertexData->data[(int)(mBufferIndex + 2)] = mVertexData->data[(int)(mBufferIndex - 22)];
            
            mVertexCount++;
            mBufferIndex += 8;

            
            if (mHasTex) {
                mVertexData->data[(int)(mBufferIndex + 11)] = mVertexData->data[(int)(mBufferIndex - 5)];
                mVertexData->data[(int)(mBufferIndex + 4)] = mVertexData->data[(int)(mBufferIndex - 12)];
            }
            if (mHasColor) {
                mVertexData->data[(int)(mBufferIndex + 5)] = mVertexData->data[(int)(mBufferIndex - 11)];
            }

            
            ptr = mVertexData->data + (int)mBufferIndex;
            *ptr = *(ptr - 16);
            mVertexData->data[(int)(mBufferIndex + 1)] = mVertexData->data[(int)(mBufferIndex - 15)];
            mVertexData->data[(int)(mBufferIndex + 2)] = mVertexData->data[(int)(mBufferIndex - 14)];
            
            mVertexCount++;
            mBufferIndex += 8;
        }

        if (mHasTex) {
            float* data = (float*)mVertexData->data;
            int idx = mBufferIndex;
            data[idx + 3] = finalTexU;
            data[idx + 4] = mTexV;
        }

        if (mHasColor) {
            mVertexData->data[(int)mBufferIndex + 5] = mPackedColor;
        }

        if (mHasNormal) {
            mVertexData->data[(int)mBufferIndex + 6] = mPackedNormal;
        }

        if (mHasBoneIndex) {
            mVertexData->data[(int)mBufferIndex + 7] = (int)mBoneIndex;
        }
       
        int col = byte_26 ? *(int*)(&dword_1c) : 0xFE00FE00;
        mVertexData->data[(int)mBufferIndex + 7] = col;
        
        float* data = (float*)mVertexData->data + (int)mBufferIndex;
        int idx = (int)mBufferIndex;
        data[0] = mXo + x;
        data[1] = mYo + y;
        data[2] = mZo + z;

        mBufferIndex += 8;
        mVertexCount++;
        

        if ((mVertexCount & 3) == 0 && (int)mBufferIndex >= (mBufferSize - 32)) {
            end();
            mHasBegun = true;
        }
    } else {
        short* vertexPtr = (short*)(mVertexData->data + ((int)mBufferIndex));
        int color = mPackedColor;

        vertexPtr[0] = ((mXo + x) * 1024.0f);
        vertexPtr[1] = ((mYo + y) * 1024.0f);
        vertexPtr[2] = ((mZo + z) * 1024.0f);

        vertexPtr[3]
            = (((color >> 16) & 0xF800) | ((color >> 13) & 0x07E0) | ((color >> 11) & 0x001F)) + 0x8000;

        vertexPtr[4] = (finalTexU * 8192.0f);
        vertexPtr[5] = (mTexV * 8192.0f);

        vertexPtr[6] = (short_1c << 8) | short_1e;
        vertexPtr[7] = (short)(-dword_54);
        
        mBufferIndex += 4;
        mVertexCount++;

        if ((mVertexCount & 3) == 0) {
            if ((int)mBufferIndex > 0x3FFEF || (int)mBufferIndex >= (mBufferSize - 16)) {
                end();
                mHasBegun = true;
            }
        }

        if ((mVertexCount & 3) == 0) {
            int paddingValue = mBucket;
            if (paddingValue == 0) {
                mBucket = 0;
            }
            uchar* pack = field_8->data;
            
            int vertIndex = mVertexCount;
            if ((int)vertIndex < 0) {
                vertIndex += 3;
            }
            pack[(vertIndex >> 2) - 1] = (char)paddingValue;
            mBucket = 0;
        }
    }
}


void BufferBuilder::vertex(float x, float y, float z) {
    mBounds.addVert(mXo + x, mYo + y, mZo + z);
    vertexNoBounds(x, y, z);
}


void BufferBuilder::vertexUV(float x, float y, float z, float u, float v) {
    tex(u, v);
    vertex(x, y, z);
}


void BufferBuilder::useCompactVertices(bool value) {
    mUseCompactVerts = value & 1;
}


void BufferBuilder::useProjectedTexture(bool value) {
    mUseProjectedTex = value & 1;
}


void BufferBuilder::tex2(int value) {
    byte_26 = 1;
    dword_1c = value;
}


void BufferBuilder::color(int r, int g, int b, int a) {
    if (mNoColor == false) {
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

        mHasColor = true;
        mPackedColor = r << 24 | g << 16 | b << 8 | a;        
    }
}

void BufferBuilder::color(int r, int g, int b) {
    color(r, g, b, 0xFF);
}

void BufferBuilder::color(float r, float g, float b) {
    int ri = static_cast<int>(r * 255.0f);
    int gi = static_cast<int>(g * 255.0f);
    int bi = static_cast<int>(b * 255.0f);
    
    color(ri, gi, bi);
}

void BufferBuilder::color(float r, float g, float b, float a) {
    int ri = static_cast<int>(r * 255.0f);
    int gi = static_cast<int>(g * 255.0f);
    int bi = static_cast<int>(b * 255.0f);
    int ai = static_cast<int>(a * 255.0f);

    color(ri, gi, bi, ai);
}

void BufferBuilder::boneIndex(int index) {
    mHasBoneIndex = true;
    mBoneIndex = index;
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
    mNoColor = true;
}

void BufferBuilder::offset(float xo, float yo, float zo) {
    mXo = xo;
    mYo = yo;
    mZo = zo;
    dword_54 = xo;
    dword_58 = yo;
    dword_5c = zo;
}

void BufferBuilder::addOffset(float xo, float yo, float zo) {
    mXo += xo;
    mYo += yo;
    mZo += zo;
}

bool BufferBuilder::setMipmapEnable(bool value) {
    bool old = mIsMipmapEnabled;
    mIsMipmapEnabled = value;
    return old;
}

void BufferBuilder::bucket(int value) {
    mBucket = value;
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
    
    byte_26 = true;
    mHasColor = true;
    mHasTex = true;
    
    float* vertexPtr = (float*)&mVertexData->data[(int)mBufferIndex];
    
    dword_3c += 4;
    mBufferIndex += 32;
    mVertexCount += 4;
    
    const float colorScale = 255.0f;

    int packedColor1 = ((int)(r1 * colorScale) << 24) | ((int)(g1 * colorScale) << 16)
                       | ((int)(b1 * colorScale) << 8) | (int)(a1 * colorScale);
    
    mBounds.addVert(mXo + x1, mYo + y1, mZo + z1);
    vertexPtr[0] = mXo + x1;
    vertexPtr[1] = mYo + y1;
    vertexPtr[2] = mZo + z1;
    vertexPtr[3] = stack_u1;
    vertexPtr[4] = stack_v1;
    *(int*)&vertexPtr[5] = packedColor1;
    *(int*)&vertexPtr[7] = texture;
    
    mBounds.addVert(mXo + x2, mYo + y2, mZo + z2);
    vertexPtr[8] = mXo + x2;
    vertexPtr[9] = mYo + y2;
    vertexPtr[10] = mZo + z2;
    vertexPtr[11] = stack_u2;
    vertexPtr[12] = stack_v2;
    *(int*)&vertexPtr[13] = packedColor1;
    *(int*)&vertexPtr[15] = texture;
    
    int packedColor2 = ((int)(stack_r2 * colorScale) << 24) | ((int)(stack_g2 * colorScale) << 16)
                       | ((int)(stack_b2 * colorScale) << 8) | (int)(stack_a2 * colorScale);

    mBounds.addVert(mXo + x3, mYo + y3, mZo + z3);
    vertexPtr[16] = mXo + x3;
    vertexPtr[17] = mYo + y3;
    vertexPtr[18] = mZo + z3;
    vertexPtr[19] = stack_u3;
    vertexPtr[20] = stack_v3;
    *(int*)&vertexPtr[21] = packedColor2;
    *(int*)&vertexPtr[23] = texture;

    mBounds.addVert(mXo + x4, mYo + y4, mZo + z4);
    vertexPtr[24] = mXo + x4;
    vertexPtr[25] = mYo + y4;
    vertexPtr[26] = mZo + z4;
    vertexPtr[27] = stack_u4;
    vertexPtr[28] = stack_v4;
    *(int*)&vertexPtr[29] = packedColor2;
    *(int*)&vertexPtr[31] = texture;

    if ((mVertexCount & 3) == 0 && (int)mBufferIndex >= mBufferSize - 0x20) {
        end();
        mHasBegun = 1;
    }
}
