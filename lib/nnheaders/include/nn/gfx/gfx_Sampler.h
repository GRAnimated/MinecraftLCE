#pragma once

#include <nn/gfx/detail/gfx_Sampler-api.nvn.8.h>
#include <nn/gfx/gfx_Common.h>

namespace nn::gfx {

template <class TTarget>
class TSampler : public detail::SamplerImpl<TTarget> {
    NN_NO_COPY(TSampler);

public:
    typedef SamplerInfo InfoType;

    TSampler();
    void Initialize(TDevice<TTarget>*, const InfoType&);
    void Finalize(TDevice<TTarget>*);
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx