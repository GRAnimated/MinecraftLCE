#include <nn/gfx/util/gfx_PrimitiveShape.h>

#include <nn/types.h>
#include <nn/util/MathTypes.h>
#include <nn/util/util_Arithmetic.h>

// todo: most of these functions are still non-matching
// matching should be done using odyssey 1.2 as a base

namespace nn::gfx::util {

PrimitiveShape::PrimitiveShape(PrimitiveShapeFormat vertexFormat,
                               PrimitiveTopology primitiveTopology) {
    m_pIndexBuffer = nullptr;
    m_pVertexBuffer = nullptr;
    m_VertexFormat = vertexFormat;
    m_IndexBufferFormat = IndexFormat_Uint32;
    m_PrimitiveTopology = primitiveTopology;
    m_VertexCount = 0;
    m_IndexCount = 0;
    m_VertexBufferSize = 0;
    m_IndexBufferSize = 0;
}

PrimitiveShape::~PrimitiveShape() {}

void* PrimitiveShape::GetIndexBuffer() const {
    return m_pIndexBuffer;
}

void* PrimitiveShape::GetVertexBuffer() const {
    return m_pVertexBuffer;
}

size_t PrimitiveShape::GetStride() const {
    size_t stride = 0;
    if (m_VertexFormat & PrimitiveShapeFormat_Pos) {
        stride += 12;
    }
    if (m_VertexFormat & PrimitiveShapeFormat_Normal) {
        stride += 12;
    }
    if (m_VertexFormat & PrimitiveShapeFormat_Uv) {
        stride += 8;
    }

    return stride;
}

size_t PrimitiveShape::GetVertexBufferSize() const {
    return m_VertexBufferSize;
}

size_t PrimitiveShape::GetIndexBufferSize() const {
    return m_IndexBufferSize;
}

PrimitiveTopology PrimitiveShape::GetPrimitiveTopology() const {
    return m_PrimitiveTopology;
}

PrimitiveShapeFormat PrimitiveShape::GetVertexFormat() const {
    return m_VertexFormat;
}

IndexFormat PrimitiveShape::GetIndexBufferFormat() const {
    return m_IndexBufferFormat;
}

int PrimitiveShape::GetVertexCount() const {
    return m_VertexCount;
}

int PrimitiveShape::GetIndexCount() const {
    return m_IndexCount;
}

void PrimitiveShape::Calculate(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                               size_t indexSize) {
    CalculateImpl(pVertexMemory, vertexSize, pIndexMemory, indexSize);
}

void PrimitiveShape::SetVertexBuffer(void* pVertexBuffer) {
    m_pVertexBuffer = pVertexBuffer;
}

void PrimitiveShape::SetIndexBuffer(void* pIndexBuffer) {
    m_pIndexBuffer = pIndexBuffer;
}

void PrimitiveShape::SetVertexBufferSize(size_t vertexBufferSize) {
    m_VertexBufferSize = vertexBufferSize;
}

void PrimitiveShape::SetIndexBufferSize(size_t indexBufferSize) {
    m_IndexBufferSize = indexBufferSize;
}

void PrimitiveShape::SetVertexCount(int vertexCount) {
    m_VertexCount = vertexCount;
}

void PrimitiveShape::SetIndexCount(int indexCount) {
    if (indexCount <= 0xFF) {
        m_IndexBufferFormat = IndexFormat_Uint8;
        m_IndexCount = indexCount;
    } else if (indexCount <= 0xFFFF) {
        m_IndexBufferFormat = IndexFormat_Uint16;
        m_IndexCount = indexCount;
    } else {
        m_IndexBufferFormat = IndexFormat_Uint32;
        m_IndexCount = indexCount;
    }
}

SphereShape::SphereShape(PrimitiveShapeFormat vertexFormat, PrimitiveTopology primitiveTopology,
                         int sliceCount, int stackCount)
    : PrimitiveShape(vertexFormat, primitiveTopology) {
    m_SliceCount = sliceCount;
    m_StackCount = stackCount;

    SetVertexCount(CalculateVertexCount());
    SetIndexCount(CalculateIndexCount());

    const size_t stride = GetStride();
    SetVertexBufferSize(GetVertexCount() * stride);
    SetIndexBufferSize(GetIndexCount() * size_t(4));
}

SphereShape::~SphereShape() {}

int SphereShape::CalculateVertexCount() {
    int numVertices = (m_StackCount + 1) * (m_SliceCount + 1);
    return numVertices;
}

int SphereShape::CalculateIndexCount() {
    int numIndices = 0;
    PrimitiveTopology primitiveTopology = GetPrimitiveTopology();

    switch (primitiveTopology) {
    case PrimitiveTopology_LineList:
        numIndices = (2 * m_StackCount - 1) * (2 * m_SliceCount);
        break;

    case PrimitiveTopology_TriangleList: {
        int numFaces = (m_StackCount - 2) * (2 * m_SliceCount) + (2 * m_SliceCount);
        numIndices = numFaces * 3;
    } break;

    default:
        break;
    }

    return numIndices;
}

void* SphereShape::CalculateVertexBuffer() {
    return nullptr;
}

/*
    switch (primitiveTopology) {
    case PrimitiveTopology_LineList: {
    } break;
    case PrimitiveTopology_TriangleList: {
    } break;

    default:
        break;
    }
*/

template <typename T>
void SphereShape::CalculateIndexBuffer() {
    T* pIndexData = static_cast<T*>(GetIndexBuffer());
    int idx = 0;

    const PrimitiveTopology primitiveTopology = GetPrimitiveTopology();

    switch (primitiveTopology) {
    case PrimitiveTopology_LineList: {
        u32 numVertsPerStack = (m_SliceCount + 1);

        for (int idxSlice = 0; idxSlice < m_SliceCount; ++idxSlice) {
            u32 sliceStartVtxIdx = 0;
            for (int idxStack = 0; idxStack < m_StackCount; ++idxStack) {
                pIndexData[idx++] = sliceStartVtxIdx + idxSlice;
                pIndexData[idx++] = sliceStartVtxIdx + idxSlice + numVertsPerStack;
                sliceStartVtxIdx += numVertsPerStack;
            }
        }

        for (int idxStack = 1; idxStack < m_StackCount; ++idxStack) {
            u32 startStackVtxIdx = idxStack * numVertsPerStack;
            for (int idxSlice = 0; idxSlice < m_SliceCount; ++idxSlice) {
                pIndexData[idx++] = startStackVtxIdx + idxSlice;
                pIndexData[idx++] = startStackVtxIdx + idxSlice + 1;
            }
        }
    } break;

    case PrimitiveTopology_TriangleList: {
        int idxFace = 0;

        for (int idxSlice = 0; idxSlice < m_SliceCount; ++idxSlice) {
            pIndexData[(idxFace * 3) + 0] = idxSlice;
            pIndexData[(idxFace * 3) + 1] = idxSlice + m_SliceCount + 1;
            pIndexData[(idxFace * 3) + 2] = idxSlice + m_SliceCount + 2;
            ++idxFace;
        }

        int idxStack = 1;
        while (idxStack < (m_StackCount - 1)) {
            for (int idxSlice = 0; idxSlice < m_SliceCount; ++idxSlice) {
                pIndexData[(idxFace * 3) + 0] = idxSlice + idxStack * (m_SliceCount + 1);
                pIndexData[(idxFace * 3) + 1] =
                    idxSlice + idxStack * (m_SliceCount + 1) + m_SliceCount + 2;
                pIndexData[(idxFace * 3) + 2] = idxSlice + idxStack * (m_SliceCount + 1) + 1;
                ++idxFace;

                pIndexData[(idxFace * 3) + 0] = idxSlice + idxStack * (m_SliceCount + 1);
                pIndexData[(idxFace * 3) + 1] =
                    idxSlice + idxStack * (m_SliceCount + 1) + m_SliceCount + 1;
                pIndexData[(idxFace * 3) + 2] = idxSlice + idxStack * (m_SliceCount + 1);

                ++idxFace;
            }

            ++idxStack;
        }

        for (int idxSlice = 0; idxSlice < m_SliceCount; ++idxSlice) {
            pIndexData[(idxFace * 3) + 0] = idxSlice + idxStack * (m_SliceCount + 1);
            pIndexData[(idxFace * 3) + 1] =
                idxSlice + idxStack * (m_SliceCount + 1) + 1 + m_SliceCount;
            pIndexData[(idxFace * 3) + 2] = idxSlice + idxStack * (m_SliceCount + 1) + 1;
            ++idxFace;
        }
    } break;

    default:
        break;
    }
}

void SphereShape::CalculateImpl(void* pVertexMemory, [[maybe_unused]] size_t vertexSize,
                                void* pIndexMemory, [[maybe_unused]] size_t indexSize) {
    SetVertexBuffer(pVertexMemory);
    SetIndexBuffer(pIndexMemory);

    CalculateVertexBuffer();

    switch (GetIndexBufferFormat()) {
    case IndexFormat_Uint8:
        CalculateIndexBuffer<uint8_t>();
        break;

    case IndexFormat_Uint16:
        CalculateIndexBuffer<uint16_t>();
        break;

    case IndexFormat_Uint32:
        CalculateIndexBuffer<uint32_t>();
        break;

    default:
        NN_UNEXPECTED_DEFAULT;
        break;
    }
}

CircleShape::CircleShape(PrimitiveShapeFormat vertexFormat, PrimitiveTopology primitiveTopology,
                         int sliceCount)
    : PrimitiveShape(vertexFormat, primitiveTopology) {
    m_SliceCount = sliceCount;

    SetVertexCount(CalculateVertexCount());
    SetIndexCount(CalculateIndexCount());

    const size_t stride = GetStride();
    SetVertexBufferSize(stride * GetVertexCount());
    SetIndexBufferSize(sizeof(4) * GetIndexCount());
}

CircleShape::~CircleShape() {}

int CircleShape::CalculateVertexCount() {
    return m_SliceCount + 1;
}

int CircleShape::CalculateIndexCount() {
    switch (GetPrimitiveTopology()) {
    case PrimitiveTopology_LineStrip:
        return m_SliceCount + 1;

    case PrimitiveTopology_TriangleList:
        return 3 * m_SliceCount;

    default:
        return 0;
    }
}

void* CircleShape::CalculateVertexBuffer() {
    float* pVertexBuffer = static_cast<float*>(GetVertexBuffer());

    if (m_SliceCount > 0) {
        for (int idxSlice = 0; idxSlice < m_SliceCount; ++idxSlice) {
            float rad = nn::util::DegreeToRadian(360.0f) * idxSlice / m_SliceCount;
            float cosXY = nn::util::CosTable(nn::util::RadianToAngleIndex(rad));
            float sinXY = nn::util::SinTable(nn::util::RadianToAngleIndex(rad));

            if (GetVertexFormat() & PrimitiveShapeFormat_Pos) {
                *pVertexBuffer++ = cosXY;
                *pVertexBuffer++ = sinXY;
                *pVertexBuffer++ = 0.0f;
            }
            if (GetVertexFormat() & PrimitiveShapeFormat_Normal) {
                *pVertexBuffer++ = 0.0f;
                *pVertexBuffer++ = 0.0f;
                *pVertexBuffer++ = 1.0f;
            }
            if (GetVertexFormat() & PrimitiveShapeFormat_Uv) {
                *pVertexBuffer++ = cosXY * 0.5f + 0.5f;
                *pVertexBuffer++ = 1.0f - (sinXY * 0.5f + 0.5f);
            }
        }
    }

    if (GetVertexFormat() & PrimitiveShapeFormat_Pos) {
        *pVertexBuffer++ = 0.0f;
        *pVertexBuffer++ = 0.0f;
        *pVertexBuffer++ = 0.0f;
    }
    if (GetVertexFormat() & PrimitiveShapeFormat_Normal) {
        *pVertexBuffer++ = 0.0f;
        *pVertexBuffer++ = 0.0f;
        *pVertexBuffer++ = 1.0f;
    }
    if (GetVertexFormat() & PrimitiveShapeFormat_Uv) {
        *pVertexBuffer++ = 0.5f;
        *pVertexBuffer++ = 0.5f;
    }

    return pVertexBuffer;
}

/*
void CircleShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
*/

CubeShape::CubeShape(PrimitiveShapeFormat vertexFormat, PrimitiveTopology primitiveTopology)
    : PrimitiveShape(vertexFormat, primitiveTopology) {
    SetVertexCount(CalculateVertexCount());
    SetIndexCount(CalculateIndexCount());

    const size_t stride = GetStride();

    SetVertexBufferSize(GetVertexCount() * stride);
    SetIndexBufferSize(GetIndexCount() * size_t(4));
}

CubeShape::~CubeShape() {}

int CubeShape::CalculateVertexCount() {
    int numVertices = 0;

    PrimitiveTopology primitiveTopology = GetPrimitiveTopology();

    switch (primitiveTopology) {
    case PrimitiveTopology_LineList:
        numVertices = CubeVertexCount_Wired;
        break;

    case PrimitiveTopology_TriangleList:
        numVertices = CubeVertexCount_Solid;
        break;

    default:
        break;
    }

    return numVertices;
}

int CubeShape::CalculateIndexCount() {
    int numVertices = 0;

    PrimitiveTopology primitiveTopology = GetPrimitiveTopology();

    switch (primitiveTopology) {
    case PrimitiveTopology_LineList:
        numVertices = CubeIndexCount_Wired;
        break;

    case PrimitiveTopology_TriangleList:
        numVertices = CubeIndexCount_Solid;
        break;

    default:
        break;
    }

    return numVertices;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
void* CubeShape::CalculateVertexBuffer() {
    const nn::util::Float3 VertexPos[8] = {
        {1.0f, 1.0f, -1.0f}, {1.0f, -1.0f, -1.0f}, {-1.0f, -1.0f, -1.0f}, {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, 1.0f},  {1.0f, -1.0f, 1.0f},  {-1.0f, -1.0f, 1.0f},  {-1.0f, 1.0f, 1.0f},
    };

    const nn::util::Float3 VertexNormal[6] = {
        {0.0, 0.0, -1.0}, {-1.0, 0.0, 0.0}, {0.0, 0.0, 1.0},
        {1.0, 0.0, 0.0},  {0.0, -1.0, 0.0}, {0.0, 1.0, 0.0},
    };

    const nn::util::Float2 VertexUv[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 1.0f},
        {1.0f, 0.0f},
    };

    const uint32_t FaceTable[6][4] = {
        {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4}, {4, 5, 1, 0}, {1, 5, 6, 2}, {4, 0, 3, 7},
    };

    float* pVertexBuffer = static_cast<float*>(GetVertexBuffer());
    const PrimitiveTopology primitiveTopology = GetPrimitiveTopology();

    if (primitiveTopology == PrimitiveTopology_LineList) {
        int idx = 0;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = -0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer[idx++] = 0.5f;
        pVertexBuffer += idx;
        return pVertexBuffer;
    }

    for (int idxFace = 0; idxFace < 6; ++idxFace) {
        for (int idxCorner = 0; idxCorner < 4; ++idxCorner) {
            int idx = 0;

            switch (GetVertexFormat()) {
            case PrimitiveShapeFormat_Pos:
                pVertexBuffer[idx++] = VertexPos[FaceTable[idxFace][idxCorner]].x * 0.5f;
                pVertexBuffer[idx++] = VertexPos[FaceTable[idxFace][idxCorner]].y * 0.5f;
                pVertexBuffer[idx++] = VertexPos[FaceTable[idxFace][idxCorner]].z * 0.5f;
                break;

            case PrimitiveShapeFormat_Normal:
                pVertexBuffer[idx++] = VertexNormal[idxFace].x;
                pVertexBuffer[idx++] = VertexNormal[idxFace].y;
                pVertexBuffer[idx++] = VertexNormal[idxFace].z;
                break;

            case PrimitiveShapeFormat_Uv:
                pVertexBuffer[idx++] = VertexUv[idxCorner].x;
                pVertexBuffer[idx++] = VertexUv[idxCorner].y;
                break;

            default:
                break;
            }

            pVertexBuffer += idx;
        }
    }

    return pVertexBuffer;
}
#pragma GCC diagnostic pop

/*

template <typename T>
void CubeShape::CalculateIndexBuffer();
void CubeShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
void QuadShape::QuadShape(PrimitiveShapeFormat, PrimitiveTopology);
*/

QuadShape::~QuadShape() {}

/*
int QuadShape::CalculateVertexCount();
int QuadShape::CalculateIndexCount();
void* QuadShape::CalculateVertexBuffer();
void QuadShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
void HemiSphereShape::HemiSphereShape(PrimitiveShapeFormat, PrimitiveTopology, int);
*/

HemiSphereShape::~HemiSphereShape() {}

/*
int HemiSphereShape::CalculateVertexCount();
int HemiSphereShape::CalculateIndexCount();
void* HemiSphereShape::CalculateVertexBuffer();

template <typename T>
void HemiSphereShape::CalculateIndexBuffer();
void HemiSphereShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
void PipeShape::PipeShape(PrimitiveShapeFormat, PrimitiveTopology, int);
*/

PipeShape::~PipeShape() {}

/*
int PipeShape::CalculateVertexCount();
int PipeShape::CalculateIndexCount();
void* PipeShape::CalculateVertexBuffer();

template <typename T>
void PipeShape::CalculateIndexBuffer();
void PipeShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
void CylinderShape::CylinderShape(PrimitiveShapeFormat, PrimitiveTopology, int);
*/

CylinderShape::~CylinderShape() {}

/*
int CylinderShape::CalculateVertexCount();
int CylinderShape::CalculateIndexCount();
void* CylinderShape::CalculateVertexBuffer();
void CylinderShape::CalculateIndexBuffer();
void CylinderShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
void ConeShape::ConeShape(PrimitiveShapeFormat, PrimitiveTopology, int);
*/

ConeShape::~ConeShape() {}

/*
int ConeShape::CalculateVertexCount();
int ConeShape::CalculateIndexCount();
void* ConeShape::CalculateVertexBuffer();

template <typename T>
void ConeShape::CalculateIndexBuffer();
void ConeShape::CalculateImpl(void* pVertexMemory, size_t vertexSize, void* pIndexMemory,
                                size_t indexSize);
*/

}  // namespace nn::gfx::util