#pragma once

#include <nn/gfx/gfx_Enum.h>
#include <nn/util.h>

namespace nn::gfx::util {

enum PrimitiveShapeFormat {
    PrimitiveShapeFormat_Pos = 0x1,
    PrimitiveShapeFormat_Normal = 0x2,
    PrimitiveShapeFormat_Uv = 0x4,
    PrimitiveShapeFormat_Default = 0x7
};

class PrimitiveShape {
    NN_NO_COPY(PrimitiveShape);

public:
    virtual ~PrimitiveShape();
    void* GetIndexBuffer() const;
    void* GetVertexBuffer() const;
    size_t GetStride() const;
    size_t GetVertexBufferSize() const;
    size_t GetIndexBufferSize() const;
    PrimitiveShapeFormat GetVertexFormat() const;
    PrimitiveTopology GetPrimitiveTopology() const;
    size_t GetIndexBufferAlignment() const;
    IndexFormat GetIndexBufferFormat() const;
    int GetVertexCount() const;
    int GetIndexCount() const;
    void Calculate(void*, size_t, void*, size_t);

protected:
    PrimitiveShape(PrimitiveShapeFormat, PrimitiveTopology);

    virtual void CalculateImpl(void*, size_t, void*, size_t) = 0;
    void SetVertexBuffer(void*);
    void SetIndexBuffer(void*);
    void SetVertexBufferSize(size_t);
    void SetIndexBufferSize(size_t);
    void SetVertexCount(int);
    void SetIndexCount(int);

private:
    void* m_pIndexBuffer;
    void* m_pVertexBuffer;
    PrimitiveShapeFormat m_VertexFormat;
    IndexFormat m_IndexBufferFormat;
    PrimitiveTopology m_PrimitiveTopology;
    int m_VertexCount;
    int m_IndexCount;
    size_t m_VertexBufferSize;
    size_t m_IndexBufferSize;
};

class SphereShape : public PrimitiveShape {
    NN_NO_COPY(SphereShape);

public:
    SphereShape(PrimitiveShapeFormat, PrimitiveTopology, int, int);

    virtual ~SphereShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    void CalculateImpl(void*, size_t, void*, size_t);

private:
    template <typename T>
    void CalculateIndexBuffer();

    void* CalculateVertexBuffer();

    int m_SliceCount;
    int m_StackCount;
};

class CircleShape : public PrimitiveShape {
public:
    CircleShape(PrimitiveShapeFormat, PrimitiveTopology, int);
    virtual ~CircleShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();

    int m_SliceCount;
};

class CubeShape : public PrimitiveShape {
public:
    CubeShape(PrimitiveShapeFormat, PrimitiveTopology);
    virtual ~CubeShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

    enum CubeVertex { CubeVertexCount_Wired = 8, CubeVertexCount_Solid = 24 };
    enum CubeIndex { CubeIndexCount_Wired = 48, CubeIndexCount_Solid = 36 };

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();
};

class QuadShape : public PrimitiveShape {
public:
    QuadShape(PrimitiveShapeFormat, PrimitiveTopology);
    virtual ~QuadShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

    enum QuadVertex { QuadVertexCount = 4 };

    enum QuadIndex { QuadIndexCount_Wired = 5, QuadIndexCountt_Solid = 6 };

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();
};

class HemiSphereShape : public PrimitiveShape {
public:
    HemiSphereShape(PrimitiveShapeFormat, PrimitiveTopology, int);
    virtual ~HemiSphereShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();

    int m_SliceCount;
};

class PipeShape : public PrimitiveShape {
public:
    PipeShape(PrimitiveShapeFormat, PrimitiveTopology, int);
    virtual ~PipeShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();

    int m_SliceCount;
};

class CylinderShape : public PrimitiveShape {
public:
    CylinderShape(PrimitiveShapeFormat, PrimitiveTopology, int);
    virtual ~CylinderShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();

    int m_SliceCount;
};

class ConeShape : public PrimitiveShape {
public:
    ConeShape(PrimitiveShapeFormat, PrimitiveTopology, int);
    virtual ~ConeShape();

protected:
    int CalculateVertexCount();
    int CalculateIndexCount();
    virtual void CalculateImpl(void*, size_t, void*, size_t);

private:
    void* CalculateVertexBuffer();

    template <typename T>
    void CalculateIndexBuffer();

    int m_SliceCount;
};

}  // namespace nn::gfx::util