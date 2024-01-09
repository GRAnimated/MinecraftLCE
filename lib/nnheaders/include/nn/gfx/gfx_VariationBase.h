#pragma once

namespace nn::gfx {

template <typename TType, typename TVersion>
class ApiVariation {};

template <int T>
class ApiType {
    static const int value = T;
};

template <int T>
class ApiVersion {
    static const int value = T;
};

}  // namespace nn::gfx
