#pragma once

#include "nn/g3d/ResSkeleton.h"

namespace nn::g3d {

// TODO
class SkeletonObj {
public:
    const ResSkeleton* GetRes() const { return m_Res; }

private:
    const ResSkeleton* m_Res;
    // TODO: the rest of the members
};

}  // namespace nn::g3d
