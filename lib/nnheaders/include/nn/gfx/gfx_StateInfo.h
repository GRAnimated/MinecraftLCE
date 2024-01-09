#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_StateInfoData.h>

namespace nn::gfx {

class MultisampleStateInfo : public detail::DataContainer<MultisampleStateInfoData> {
public:
    MultisampleStateInfo() {}

    void SetDefault();

    void SetSampleCount(int count) { sampleCount = count; }
    void SetSampleMask(int mask) { sampleMask = mask; }
    void SetAlphaToCoverageEnabled(bool alpha) { flag.SetBit(Flag_AlphaToCoverageEnable, alpha); }

    bool IsAlphaToCoverageEnabled() const { return flag.GetBit(Flag_AlphaToCoverageEnable); }
    int GetSampleCount() const { return sampleCount; }
    int GetSampleMask() const { return sampleMask; }
};

class RasterizerStateInfo : public detail::DataContainer<RasterizerStateInfoData> {
public:
    RasterizerStateInfo() {}

    void SetDefault();

    void SetFillMode(FillMode fill) { fillMode = fill; }
    void SetFrontFace(FrontFace face) { frontFace = face; }
    void SetCullMode(CullMode cull) { cullMode = cull; }
    void SetPrimitiveTopologyType(PrimitiveTopologyType type) { primitiveTopologyType = type; }
    void SetRasterEnabled(bool b) { flag.SetBit(Flag_RasterDisable, !b); }
    void SetMultisampleEnabled(bool b) { flag.SetBit(Flag_MultisampleEnable, b); }
    void SetDepthClipEnabled(bool b) { flag.SetBit(Flag_DepthClipDisable, !b); }
    void SetScissorEnabled(bool b) { flag.SetBit(Flag_ScissorEnable, b); }
    void SetSlopeScaledDepthBias(float bias) { slopeScaledDepthBias = bias; }
    void SetDepthBias(int bias) { depthBias = bias; }
    void SetDepthBiasClamp(float clamp) { depthBiasClamp = clamp; }

    void SetConservativeRasterizationMode(ConservativeRasterizationMode mode) {
        conservativeRasterizationMode = mode;
    }

    MultisampleStateInfo& EditMultisampleStateInfo() {
        return nn::gfx::DataToAccessor(multisample);
    }

    FillMode GetFillMode() const { return static_cast<FillMode>(fillMode); }
    FrontFace GetFrontFace() const { return static_cast<FrontFace>(frontFace); }
    CullMode GetCullMode() const { return static_cast<CullMode>(cullMode); }

    PrimitiveTopologyType GetPrimitiveTopologyType() const {
        return static_cast<PrimitiveTopologyType>(primitiveTopologyType);
    }

    bool IsRasterEnabled() const { return !flag.GetBit(Flag_RasterDisable); }
    bool IsMultisampleEnabled() const { return flag.GetBit(Flag_MultisampleEnable); }
    bool IsDepthClipEnabled() const { return !flag.GetBit(Flag_DepthClipDisable); }
    bool IsScissorEnabled() const { return flag.GetBit(Flag_ScissorEnable); }
    float GetSlopeScaledDepthBias() const { return slopeScaledDepthBias; }
    int GetDepthBias() const { return depthBias; }
    float GetDepthBiasClamp() const { return depthBiasClamp; }

    ConservativeRasterizationMode GetConservativeRasterizationMode() const {
        return static_cast<ConservativeRasterizationMode>(conservativeRasterizationMode);
    }

    const MultisampleStateInfo& GetMultisampleStateInfo() const {
        return nn::gfx::DataToAccessor(multisample);
    }
};

class BlendTargetStateInfo : public detail::DataContainer<BlendTargetStateInfoData> {
public:
    BlendTargetStateInfo();
    void SetDefault();

    void SetBlendEnabled(bool b) { flag.SetBit(Flag_BlendEnable, b); }
    void SetSourceColorBlendFactor(BlendFactor factor) { sourceColorBlendFactor = factor; }

    void SetDestinationColorBlendFactor(BlendFactor factor) {
        destinationColorBlendFactor = factor;
    }

    void SetColorBlendFunction(BlendFunction function) { colorBlendFunction = function; }
    void SetSourceAlphaBlendFactor(BlendFactor factor) { sourceAlphaBlendFactor = factor; }

    void SetDestinationAlphaBlendFactor(BlendFactor factor) {
        destinationAlphaBlendFactor = factor;
    }

    void SetAlphaBlendFunction(BlendFunction function) { alphaBlendFunction = function; }
    void SetChannelMask(int mask) { channelMask = mask; }

    bool IsBlendEnabled() const { return flag.GetBit(Flag_BlendEnable); }

    BlendFactor GetSourceColorBlendFactor() const {
        return static_cast<BlendFactor>(sourceColorBlendFactor);
    }

    BlendFactor GetDestinationColorBlendFactor() const {
        return static_cast<BlendFactor>(destinationColorBlendFactor);
    }

    BlendFunction GetColorBlendFunction() const {
        return static_cast<BlendFunction>(colorBlendFunction);
    }

    BlendFactor GetSourceAlphaBlendFactor() const {
        return static_cast<BlendFactor>(sourceAlphaBlendFactor);
    }

    BlendFactor GetDestinationAlphaBlendFactor() const {
        return static_cast<BlendFactor>(destinationAlphaBlendFactor);
    }

    BlendFunction GetAlphaBlendFunction() const {
        return static_cast<BlendFunction>(alphaBlendFunction);
    }

    int GetChannelMask() const { return channelMask; }
};

class BlendStateInfo : public detail::DataContainer<BlendStateInfoData> {
public:
    BlendStateInfo() {}

    void SetDefault();

    void SetLogicOperation(LogicOperation op) { logicOperation = op; }
    void SetAlphaToCoverageEnabled(bool b) { flag.SetBit(Flag_AlphaToCoverageEnable, b); }
    void SetDualSourceBlendEnabled(bool b) { flag.SetBit(Flag_DualSourceBlendEnable, b); }
    void SetIndependentBlendEnabled(bool b) { flag.SetBit(Flag_IndependentBlendEnable, b); }
    void SetLogicOperationEnabled(bool b) { flag.SetBit(Flag_LogicOperationEnable, b); }

    void SetBlendConstant(float r, float g, float b, float alpha) {
        blendConstant[0] = r;
        blendConstant[1] = g;
        blendConstant[2] = b;
        blendConstant[3] = alpha;
    }

    void SetBlendTargetStateInfoArray(const BlendTargetStateInfo* p, int c) {
        blendTargetCount = c;
        pBlendTargetArray.ptr = p->ToData();
    }

    int GetBlendTargetCount() const { return blendTargetCount; }
    LogicOperation GetLogicOperation() const { return static_cast<LogicOperation>(logicOperation); }
    bool IsAlphaToCoverageEnabled() const { return flag.GetBit(Flag_AlphaToCoverageEnable); }
    bool IsDualSourceBlendEnabled() const { return flag.GetBit(Flag_DualSourceBlendEnable); }
    bool IsIndependentBlendEnabled() const { return flag.GetBit(Flag_IndependentBlendEnable); }
    bool IsLogicOperationEnabled() const { return flag.GetBit(Flag_LogicOperationEnable); }
    float GetBlendConstant(ColorChannel channel) const { return blendConstant[channel]; }

    const BlendTargetStateInfo* GetBlendTargetStateInfoArray() const {
        return nn::gfx::DataToAccessor(pBlendTargetArray.ptr);
    }
};

class StencilStateInfo : public detail::DataContainer<StencilStateInfoData> {
public:
    StencilStateInfo() {}

    void SetDefault();

    void SetStencilFailOperation(StencilOperation op) { stencilFailOperation = op; }
    void SetDepthFailOperation(StencilOperation op) { depthFailOperation = op; }
    void SetDepthPassOperation(StencilOperation op) { depthPassOperation = op; }
    void SetComparisonFunction(ComparisonFunction function) { comparisonFunction = function; }
    void SetStencilRef(int ref) { stencilRef = ref; }

    StencilOperation GetStencilFailOperation() const {
        return static_cast<StencilOperation>(stencilFailOperation);
    }

    StencilOperation GetDepthFailOperation() const {
        return static_cast<StencilOperation>(depthFailOperation);
    }

    StencilOperation GetDepthPassOperation() const {
        return static_cast<StencilOperation>(depthPassOperation);
    }

    ComparisonFunction GetComparisonFunction() const {
        return static_cast<ComparisonFunction>(comparisonFunction);
    }

    int GetStencilRef() const { return stencilRef; }
};

class DepthStencilStateInfo : public detail::DataContainer<DepthStencilStateInfoData> {
public:
    DepthStencilStateInfo() {}

    void SetDefault();

    void SetDepthComparisonFunction(ComparisonFunction function) {
        depthComparisonFunction = function;
    }

    void SetDepthTestEnabled(bool b) { flag.SetBit(Flag_DepthTestEnable, b); }
    void SetDepthWriteEnabled(bool b) { flag.SetBit(Flag_DepthWriteEnable, b); }
    void SetStencilTestEnabled(bool b) { flag.SetBit(Flag_StencilTestEnable, b); }
    void SetDepthBoundsTestEnabled(bool b) { flag.SetBit(Flag_DepthBoundsTestEnable, b); }
    void SetStencilReadMask(int mask) { stencilReadMask = mask; }
    void SetStencilWriteMask(int mask) { stencilWriteMask = mask; }
    StencilStateInfo& EditFrontStencilStateInfo() { return nn::gfx::DataToAccessor(frontStencil); }
    StencilStateInfo& EditBackStencilStateInfo() { return nn::gfx::DataToAccessor(backStencil); }

    ComparisonFunction GetDepthComparisonFunction() const {
        return static_cast<ComparisonFunction>(depthComparisonFunction);
    }

    bool IsDepthTestEnabled() const { return flag.GetBit(Flag_DepthTestEnable); }
    bool IsDepthWriteEnabled() const { return flag.GetBit(Flag_DepthWriteEnable); }
    bool IsStencilTestEnabled() const { return flag.GetBit(Flag_StencilTestEnable); }
    bool IsDepthBoundsTestEnabled() const { return flag.GetBit(Flag_DepthBoundsTestEnable); }
    int GetStencilReadMask() const { return stencilReadMask; }
    int GetStencilWriteMask() const { return stencilWriteMask; }

    const StencilStateInfo& GetFrontStencilStateInfo() const {
        return nn::gfx::DataToAccessor(frontStencil);
    }

    const StencilStateInfo& GetBackStencilStateInfo() const {
        return nn::gfx::DataToAccessor(backStencil);
    }
};

class ColorTargetStateInfo : public detail::DataContainer<ColorTargetStateInfoData> {
public:
    ColorTargetStateInfo() {}

    void SetDefault();

    void SetFormat(ImageFormat value) { format = value; }
    ImageFormat GetFormat() const { return static_cast<ImageFormat>(format); }
};

class RenderTargetStateInfo : public detail::DataContainer<RenderTargetStateInfoData> {
public:
    RenderTargetStateInfo() {}

    void SetDefault();

    void SetDepthStencilFormat(ImageFormat value) { depthStencilFormat = value; }
    void SetColorTargetStateInfoArray(const ColorTargetStateInfo* pColorTargetStateInfoArray,
                                      int colorTargetStateCount) {
        pColorTargetStateArray.ptr = pColorTargetStateInfoArray->ToData();
        colorTargetCount = colorTargetStateCount;
    }

    ImageFormat GetDepthStencilFormat() const {
        return static_cast<ImageFormat>(depthStencilFormat);
    }

    int GetColorTargetCount() const { return colorTargetCount; }

    const ColorTargetStateInfo* GetColorTargetStateInfoArray() const {
        return nn::gfx::DataToAccessor(pColorTargetStateArray.ptr);
    }
};

class VertexAttributeStateInfo : public detail::DataContainer<VertexAttributeStateInfoData> {
public:
    VertexAttributeStateInfo() {}

    void SetDefault();

    void SetSemanticIndex(int i) { semanticIndex = i; }
    void SetShaderSlot(int s) { shaderSlot = s; }
    void SetBufferIndex(int i) { bufferIndex = i; }
    void SetOffset(ptrdiff_t o) { offset = o; }
    void SetFormat(AttributeFormat f) { format = f; }
    void SetNamePtr(const char* n) { pName = n; }

    int GetSemanticIndex() const { return semanticIndex; }
    int GetShaderSlot() const { return shaderSlot; }
    int GetBufferIndex() const { return bufferIndex; }
    ptrdiff_t GetOffset() const { return offset; }
    AttributeFormat GetFormat() const { return static_cast<AttributeFormat>(format); }
    const char* GetNamePtr() const { return pName; }
};

class VertexBufferStateInfo : public detail::DataContainer<VertexBufferStateInfoData> {
public:
    VertexBufferStateInfo() {}

    void SetDefault();

    void SetStride(ptrdiff_t s) { stride = s; }
    void SetDivisor(int d) { divisor = d; }

    ptrdiff_t GetStride() const { return stride; }
    int GetDivisor() const { return divisor; }
};

class VertexStateInfo : public detail::DataContainer<VertexStateInfoData> {
public:
    VertexStateInfo() {}

    void SetDefault();

    void SetVertexAttributeStateInfoArray(const VertexAttributeStateInfo* p, int c) {
        attributeCount = c;
        pAttributeArray.ptr = p->ToData();
    }

    void SetVertexBufferStateInfoArray(const VertexBufferStateInfo* p, int c) {
        bufferCount = c;
        pBufferArray.ptr = p->ToData();
    }

    int GetVertexAttributeCount() const { return attributeCount; }
    int GetVertexBufferCount() const { return bufferCount; }

    const VertexAttributeStateInfo* GetVertexAttributeStateInfoArray() const {
        return nn::gfx::DataToAccessor(pAttributeArray.ptr);
    }

    const VertexBufferStateInfo* GetVertexBufferStateInfoArray() const {
        return nn::gfx::DataToAccessor(pBufferArray.ptr);
    }
};

class TessellationStateInfo : public detail::DataContainer<TessellationStateInfoData> {
public:
    TessellationStateInfo() {}

    void SetDefault();

    void SetPatchControlPointCount(int c) { patchControlPointCount = c; }

    int GetPatchControlPointCount() const { return patchControlPointCount; }
};

class ViewportStateInfo : public detail::DataContainer<ViewportStateInfoData> {
public:
    ViewportStateInfo() {}

    void SetDefault();

    void SetOriginX(float value) { originX = value; }
    void SetOriginY(float value) { originY = value; }
    void SetWidth(float value) { width = value; }
    void SetHeight(float value) { height = value; }
    void SetMinDepth(float value) { depthRange.minDepth = value; }
    void SetMaxDepth(float value) { depthRange.maxDepth = value; }

    float GetOriginX() const { return originX; }
    float GetOriginY() const { return originY; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }
    float GetMinDepth() const { return depthRange.minDepth; }
    float GetMaxDepth() const { return depthRange.maxDepth; }
};

class ScissorStateInfo : public detail::DataContainer<ScissorStateInfoData> {
public:
    ScissorStateInfo() {}

    void SetDefault();

    void SetOriginX(int value) { originX = value; }
    void SetOriginY(int value) { originY = value; }
    void SetWidth(int value) { width = value; }
    void SetHeight(int value) { height = value; }

    int GetOriginX() const { return originX; }
    int GetOriginY() const { return originY; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
};

class ViewportScissorStateInfo : public detail::DataContainer<ViewportScissorStateInfoData> {
public:
    ViewportScissorStateInfo() {}

    void SetDefault();

    void SetScissorEnabled(bool value) { flag.SetBit(Flag_ScissorEnable, value); }

    void SetViewportStateInfoArray(const ViewportStateInfo* pViewportStateInfoArray,
                                   int viewportStateCount) {
        pViewportArray.ptr = pViewportStateInfoArray->ToData();
        viewportCount = viewportStateCount;
    }

    void SetScissorStateInfoArray(const ScissorStateInfo* pScissorStateInfoArray,
                                  int scissorStateCount) {
        pScissorArray.ptr = pScissorStateInfoArray->ToData();
        scissorCount = scissorStateCount;
    }

    bool IsScissorEnabled() const { return flag.GetBit(Flag_ScissorEnable); }
    int GetViewportCount() const { return viewportCount; }
    int GetScissorCount() const { return scissorCount; }

    const ViewportStateInfo* GetViewportStateInfoArray() const {
        return nn::gfx::DataToAccessor(pViewportArray.ptr);
    }

    const ScissorStateInfo* GetScissorStateInfoArray() const {
        return nn::gfx::DataToAccessor(pScissorArray.ptr);
    }
};

}  // namespace nn::gfx