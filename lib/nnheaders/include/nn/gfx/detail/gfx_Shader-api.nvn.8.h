#pragma once

#include <nn/gfx/detail/gfx_DataContainer.h>
#include <nn/gfx/gfx_Common.h>
#include <nn/gfx/gfx_Enum.h>
#include <nn/gfx/gfx_ShaderData-api.nvn.8.h>

namespace nn::gfx {
class ShaderInfo;

namespace detail {

template <>
class ShaderImpl<ApiVariationNvn8> : public DataContainer<ShaderImplData<ApiVariationNvn8>> {
    NN_NO_COPY(ShaderImpl);

public:
    typedef ShaderInfo InfoType;

    static size_t GetBinaryCodeAlignment(DeviceImpl<ApiVariationNvn8>*);

    ShaderImpl();
    ~ShaderImpl();
    ShaderInitializeResult Initialize(DeviceImpl<ApiVariationNvn8>*, const InfoType&);
    void Finalize(DeviceImpl<ApiVariationNvn8>*);
    int GetInterfaceSlot(ShaderStage, ShaderInterfaceType, const char*) const;
    void GetWorkGroupSize(int*, int*, int*) const;
};

}  // namespace detail
}  // namespace nn::gfx