#include "net/minecraft/client/model/Model.h"

Model::Model() {
    this->m_riding = false;
    this->m_isYoung = true;
    this->m_texWidth = 64;
    this->m_texHeight = 32;
    this->m_byte88 = 0;
}

Model::~Model() {}

void Model::render(std::shared_ptr<Entity>&, float, float, float, float, float, float, bool) {}
void Model::setupAnim(float, float, float, float, float, float, std::shared_ptr<Entity>, _SkinAdjustments) {}
void Model::prepareMobModel(std::shared_ptr<LivingEntity>&, float, float, float) {}

ModelPart* Model::getRandomModelPart(Random random) {
    return this->m_modelParts.at(random.nextInt(this->m_modelParts.size()));
}

ModelPart* Model::AddOrRetrievePart(SKIN_BOX*, unsigned int) {
    return nullptr;
}

void Model::copyPropertiesFrom(Model* source) {
    this->m_attackTime = source->m_attackTime;
    this->m_riding = source->m_riding;
    this->m_isYoung = source->m_isYoung;
    this->m_byte88 = source->m_byte88;
}

void Model::clearAllOffsets() {}
void Model::SetSkinAdjustments(_SkinAdjustments) {}

std::wstring Model::getName() {
    return L"";
}
