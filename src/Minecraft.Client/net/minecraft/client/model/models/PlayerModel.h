#pragma once

#include "net/minecraft/client/model/models/HumanoidModel.h"

// TODO: grab shit for this
enum EPlayerModelType {};

class PlayerModel : public HumanoidModel {
public:
    void renderCloak(float);

    void render(HumanoidModel*, float, bool) override;
    void setAllVisible(bool) override;
    void translateToHandItem(float, const HumanoidArm*) override;

    char fill[0x1E0 - 336];
};