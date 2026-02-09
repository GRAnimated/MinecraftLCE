#pragma once

#include "net/minecraft/client/model/Model.h"
#include "net/minecraft/world/entity/EquipmentSlot.h"
#include "net/minecraft/world/entity/HumanoidArm.h"
#include "net/minecraft/world/entity/SkinAdjustments.h"

class HumanoidModel : public Model {
public:
    // TODO: fill in
    enum eArmPose {};

    HumanoidModel(const ModelDefinition&, float, float, int, int, bool, bool, bool);

    void _init(float, float, int, int, bool, bool, const ModelDefinition&, bool);

    virtual void render(HumanoidModel*, float, bool);  // ?
    virtual void setAllVisible(bool);
    virtual void translateToHandItem(float, const HumanoidArm*);
    virtual void setArmPose(const HumanoidArm*, HumanoidModel::eArmPose);
    virtual void setArmPose(std::shared_ptr<Entity>, HumanoidModel::eArmPose, bool);

    ModelPart* mHeadPart;
    ModelPart* mHatPart;
    ModelPart* mBodyPart;
    ModelPart* mRightArmPart;
    ModelPart* mLeftArmPart;
    ModelPart* mRightLegPart;
    ModelPart* mLeftLegPart;
    ModelPart* mRightItemPart;
    ModelPart* mLeftItemPart;
    char gapD8[8];
    bool flag1;
    bool flag2;
    bool flag3;
    int dwordE4;
    int dwordE8;
    _SkinAdjustments mSkinAdjustments;
    float float13C;
    bool mSlim;
    EquipmentSlot* mEquipSlot;  // Equipment slot of what?
};