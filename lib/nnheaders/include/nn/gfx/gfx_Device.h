#pragma once

#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/detail/gfx_RequiredMemory.h>
#include <nn/util.h>

namespace nn::gfx {

class DeviceInfo;

template <class TTarget>
class TDevice : public detail::DeviceImpl<TTarget>,
                private detail::RequiredMemory<detail::DeviceImpl<TTarget>> {
    NN_NO_COPY(TDevice);

public:
    typedef DeviceInfo InfoType;

    static size_t GetRequiredMemorySize(const InfoType&);

    TDevice();
    void Initialize(const InfoType&);
    void Finalize();
    void SetUserPtr(void*);
    void* GetUserPtr();
    const void* GetUserPtr() const;
};

}  // namespace nn::gfx