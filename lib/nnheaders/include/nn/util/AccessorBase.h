#pragma once

namespace nn::util {

template <typename T>
class AccessorBase : protected T {
public:
    using value_type = T;

    AccessorBase() = delete;

    T& ToData() { return *this; }
    const T& ToData() const { return *this; }
};

}  // namespace nn::util
