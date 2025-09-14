#include "net/minecraft/util/HumanoidArm.h"

const HumanoidArm* HumanoidArm::LEFT = new HumanoidArm();
const HumanoidArm* HumanoidArm::RIGHT = new HumanoidArm();

const HumanoidArm* HumanoidArm::getOpposite() const {
    return this == LEFT ? RIGHT : LEFT;
}
