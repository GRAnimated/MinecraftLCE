#pragma once

#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_PipelineData-api.nvn.8.h>

namespace nn::gfx {

class GraphicsPipelineInfo;
class ComputePipelineInfo;

namespace detail {

template <>
class PipelineImpl<ApiVariationNvn8> : public DataContainer<PipelineImplData<ApiVariationNvn8>> {
    NN_NO_COPY(PipelineImpl);

public:
    typedef GraphicsPipelineInfo GraphicsInfoType;
    typedef ComputePipelineInfo ComputeInfoType;

    static size_t GetRequiredMemorySize(const GraphicsInfoType&);
    static size_t GetRequiredMemorySize(const ComputeInfoType&);

    PipelineImpl();
    ~PipelineImpl();
    void SetMemory(void*, size_t);
    void* GetMemory();
    const void* GetMemory() const;
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const GraphicsInfoType&);
    void Initialize(DeviceImpl<ApiVariationNvn8>*, const ComputeInfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
};

}  // namespace detail

}  // namespace nn::gfx