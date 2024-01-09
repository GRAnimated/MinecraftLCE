#pragma once

#include <nn/gfx/detail/gfx_RootSignature-api.common.h>
#include <nn/gfx/gfx_Common.h>

namespace nn::gfx::detail {
template <>
class RootSignatureImpl<ApiVariationNvn8> : public RootSignatureImplCommon<ApiVariationNvn8> {};
}  // namespace nn::gfx::detail