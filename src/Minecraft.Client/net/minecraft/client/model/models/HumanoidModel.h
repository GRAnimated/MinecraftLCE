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

    ModelPart* m_mHeadPart;
    ModelPart* m_mHatPart;
    ModelPart* m_mBodyPart;
    ModelPart* m_mRightArmPart;
    ModelPart* m_mLeftArmPart;
    ModelPart* m_mRightLegPart;
    ModelPart* m_mLeftLegPart;
    ModelPart* m_mRightItemPart;
    ModelPart* m_mLeftItemPart;
    char m_gapD8[8];
    bool m_flag1;
    bool m_flag2;
    bool m_flag3;
    int m_dwordE4;
    int m_dwordE8;
    _SkinAdjustments m_mSkinAdjustments;
    float m_float13C;
    bool m_mSlim;
    EquipmentSlot* m_mEquipSlot;  // Equipment slot of what?
};