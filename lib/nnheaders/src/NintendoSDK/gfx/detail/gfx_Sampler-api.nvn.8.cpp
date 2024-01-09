#include <nn/gfx/detail/gfx_Sampler-api.nvn.8.h>

#include <nn/gfx/detail/gfx_Device-api.nvn.8.h>
#include <nn/gfx/gfx_SamplerInfo.h>

#include "gfx_CommonHelper.h"
#include "gfx_NvnHelper.h"

namespace nn::gfx::detail {

SamplerImpl<ApiVariationNvn8>::SamplerImpl() {
    state = State_NotInitialized;
}

SamplerImpl<ApiVariationNvn8>::~SamplerImpl() {}

void SamplerImpl<ApiVariationNvn8>::Initialize(DeviceImpl<ApiVariationNvn8>* pDevice,
                                               const SamplerInfo& info) {
    static const float s_BorderColors[3][4] = {
        {1.0f, 1.0f, 1.0f, 1.0f},
        {0.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f},
    };

    static const NVNsamplerReduction s_ReductionTable[3] = {
        NVN_SAMPLER_REDUCTION_AVERAGE,
        NVN_SAMPLER_REDUCTION_MIN,
        NVN_SAMPLER_REDUCTION_MAX,
    };

    NVNsamplerBuilder builder;
    nvnSamplerBuilderSetDefaults(&builder);
    nvnSamplerBuilderSetDevice(&builder, pDevice->ToData()->pNvnDevice);

    nvnSamplerBuilderSetMinMagFilter(&builder, Nvn::GetMinFilter(info.GetFilterMode()),
                                     Nvn::GetMagFilter(info.GetFilterMode()));

    nvnSamplerBuilderSetWrapMode(&builder, Nvn::GetWrapMode(info.GetAddressU()),
                                 Nvn::GetWrapMode(info.GetAddressV()),
                                 Nvn::GetWrapMode(info.GetAddressW()));

    nvnSamplerBuilderSetLodClamp(&builder, info.GetMinLod(), info.GetMaxLod());
    nvnSamplerBuilderSetLodBias(&builder, info.GetLodBias());

    nvnSamplerBuilderSetCompare(&builder,
                                IsFilterModeComparison(info.GetFilterMode()) ?
                                    NVN_COMPARE_MODE_COMPARE_R_TO_TEXTURE :
                                    NVN_COMPARE_MODE_NONE,
                                Nvn::GetRComparisonFunction(info.GetComparisonFunction()));
    nvnSamplerBuilderSetBorderColor(&builder, s_BorderColors[info.GetBorderColorType()]);

    if (IsFilterModeAnisotropic(info.GetFilterMode())) {
        nvnSamplerBuilderSetMaxAnisotropy(&builder, info.GetMaxAnisotropy());
    }

    NVNsamplerReduction reductionMode = NVN_SAMPLER_REDUCTION_AVERAGE;
    if (pDevice->ToData()->supportedFeatures.GetBit(NvnDeviceFeature_SupportMinMaxFiltering)) {
        reductionMode = s_ReductionTable[(info.GetFilterMode() >> 8) & 3];
    }

    nvnSamplerBuilderSetReductionFilter(&builder, reductionMode);

    pNvnSampler = &nvnSampler;
    nvnSamplerInitialize(pNvnSampler, &builder);
    flags.SetBit(Flag_Shared, false);
    state = State_Initialized;
}

void SamplerImpl<ApiVariationNvn8>::Finalize(DeviceImpl<ApiVariationNvn8>*) {
    nvnSamplerFinalize(pNvnSampler);
    pNvnSampler = nullptr;
    state = State_NotInitialized;
}

}  // namespace nn::gfx::detail