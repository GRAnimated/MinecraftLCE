#include "net/minecraft/client/model/Model.h"

Model::Model() {
    this->mRiding = false;
    this->mIsYoung = true;
    this->mTexWidth = 64;
    this->mTexHeight = 32;
    this->byte88 = 0;
}

Model::~Model() {}

void Model::render(std::shared_ptr<Entity>&, float, float, float, float, float, float, bool) {}
void Model::setupAnim(float, float, float, float, float, float, std::shared_ptr<Entity>, _SkinAdjustments) {}
void Model::prepareMobModel(std::shared_ptr<LivingEntity>&, float, float, float) {}

ModelPart* Model::getRandomModelPart(Random random) {
    return this->mModelParts.at(random.nextInt(this->mModelParts.size()));
}

ModelPart* Model::AddOrRetrievePart(SKIN_BOX*, unsigned int) {
    return nullptr;
}

void Model::copyPropertiesFrom(Model* source) {
    this->mAttackTime = source->mAttackTime;
    this->mRiding = source->mRiding;
    this->mIsYoung = source->mIsYoung;
    this->byte88 = source->byte88;
}

void Model::clearAllOffsets() {}
void Model::SetSkinAdjustments(_SkinAdjustments) {}

std::wstring Model::getName() {
    return L"";
}
