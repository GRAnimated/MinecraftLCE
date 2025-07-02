#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "net/minecraft/client/model/ModelPartsSkinned.h"
#include "net/minecraft/world/Random.h"

class Entity;
class LivingEntity;
class TexOffs;
class SKIN_BOX;
class ModelPart;
class _SkinAdjustments {};

class Model {
public:
    Model();

    virtual ~Model();
    virtual void render(std::shared_ptr<Entity>&, float, float, float, float, float, float, bool);
    virtual void setupAnim(float, float, float, float, float, float, std::shared_ptr<Entity>,
                           _SkinAdjustments);
    virtual void prepareMobModel(std::shared_ptr<LivingEntity>&, float, float, float);
    virtual ModelPart* getRandomModelPart(Random random);
    virtual ModelPart* AddOrRetrievePart(SKIN_BOX*, unsigned int);
    virtual void copyPropertiesFrom(Model* source);
    virtual void clearAllOffsets();
    virtual void SetSkinAdjustments(_SkinAdjustments);
    virtual std::wstring getName();

    float mAttackTime;
    bool mRiding;
    std::vector<ModelPart*> mModelParts;
    bool mIsYoung;
    std::unordered_map<std::wstring, TexOffs*> mTexOffs;
    int mTexWidth;
    int mTexHeight;
    ModelPartsSkinned mModelPartsSkinned;
    bool byte88;
};