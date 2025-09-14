#pragma once

class HumanoidArm {
public:
    static const HumanoidArm* LEFT;
    static const HumanoidArm* RIGHT;

    const HumanoidArm* getOpposite() const;
};