#include "net/minecraft/world/entity/HumanoidArm.h"

const HumanoidArm* HumanoidArm::LEFT = new HumanoidArm();
const HumanoidArm* HumanoidArm::RIGHT = new HumanoidArm();

const HumanoidArm* HumanoidArm::getOpposite() const {
    return this == LEFT ? RIGHT : LEFT;
}
