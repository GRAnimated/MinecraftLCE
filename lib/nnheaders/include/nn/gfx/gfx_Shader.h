#pragma once

#include <nn/gfx/detail/gfx_Shader-api.nvn.8.h>

namespace nn::gfx {

template <class TTarget>
class TShader : public detail::ShaderImpl<TTarget> {
    NN_NO_COPY(TShader);

public:
    typedef ShaderInfo InfoType;

    static size_t GetBinaryCodeAlignment(TDevice<TTarget>*);

    TShader();
    ShaderInitializeResult Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    int GetInterfaceSlot(ShaderStage, ShaderInterfaceType, const char*) const;
    void GetWorkGroupSize(int*, int*, int*) const;
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx