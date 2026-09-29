#include "net/minecraft/client/model/ModelDefinition.h"
#include "net/minecraft/client/model/geom/ModelPartSkin.h"
#include "net/minecraft/client/model/models/ElytraModel.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/eINSTANCEOF.h"
#include "net/minecraft/world/entity/Entity.h"
#include "net/minecraft/world/entity/LivingEntity.h"
#include <cmath>
#include <memory>

ElytraModel::ElytraModel(const ModelDefinition&) : Model() {
    this->m_byte89 = false;
    this->m_mLeftWing = new ModelPartSkin(this, 22, 0);
    this->m_mLeftWing->addBox(-10.0f, 0.0f, 0.0f, 10, 20, 2, 1.0f);

    this->m_mRightWing = new ModelPartSkin(this, 22, 0);
    this->m_mRightWing->m_mirror = true;
    this->m_mRightWing->addBox(0.0f, 0.0f, 0.0f, 10, 20, 2, 1.0f);

    this->m_mLeftWing->m_xPos = 5.0f;
    this->m_mLeftWing->m_xRot = Mth::RAD * 15.0f;
    this->m_mLeftWing->m_yPos = 0.0f;
    this->m_mLeftWing->m_yRot = 0.0f;
    this->m_mLeftWing->m_zRot = Mth::RAD * -15.0f;

    this->m_mRightWing->m_xPos = -this->m_mLeftWing->m_xPos;
    this->m_mRightWing->m_xRot = this->m_mLeftWing->m_xRot;
    this->m_mRightWing->m_yPos = this->m_mLeftWing->m_yPos;
    this->m_mRightWing->m_yRot = -this->m_mLeftWing->m_yRot;
    this->m_mRightWing->m_zRot = -this->m_mLeftWing->m_zRot;

    this->compileSkinnedDrawlist();
}

void ElytraModel::render(std::shared_ptr<Entity>& entity, float, float, float, float, float, float scale,
                         bool callList) {
    GlStateManager::disableRescaleNormal();
    GlStateManager::disableCull();
    if (Entity::instanceof(entity, eLivingEntity)
        && std::static_pointer_cast<LivingEntity>(entity)->isBaby()) {
        GlStateManager::pushMatrix();
        GlStateManager::scalef(0.5F, 0.5F, 0.5F);
        GlStateManager::translatef(0.0F, 1.5F, -0.1F);
        this->m_mLeftWing->render(scale, callList, false);
        this->m_mRightWing->render(scale, callList, false);
        GlStateManager::popMatrix();
    } else {
        this->m_mLeftWing->render(scale, callList, false);
        this->m_mRightWing->render(scale, callList, false);
    }
    this->callSkinnedDrawlist();
}