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
    this->byte89 = false;
    this->mLeftWing = new ModelPartSkin(this, 22, 0);
    this->mLeftWing->addBox(-10.0f, 0.0f, 0.0f, 10, 20, 2, 1.0f);

    this->mRightWing = new ModelPartSkin(this, 22, 0);
    this->mRightWing->mMirror = true;
    this->mRightWing->addBox(0.0f, 0.0f, 0.0f, 10, 20, 2, 1.0f);

    this->mLeftWing->mXPos = 5.0f;
    this->mLeftWing->mXRot = Mth::RAD * 15.0f;
    this->mLeftWing->mYPos = 0.0f;
    this->mLeftWing->mYRot = 0.0f;
    this->mLeftWing->mZRot = Mth::RAD * -15.0f;

    this->mRightWing->mXPos = -this->mLeftWing->mXPos;
    this->mRightWing->mXRot = this->mLeftWing->mXRot;
    this->mRightWing->mYPos = this->mLeftWing->mYPos;
    this->mRightWing->mYRot = -this->mLeftWing->mYRot;
    this->mRightWing->mZRot = -this->mLeftWing->mZRot;

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
        this->mLeftWing->render(scale, callList, false);
        this->mRightWing->render(scale, callList, false);
        GlStateManager::popMatrix();
    } else {
        this->mLeftWing->render(scale, callList, false);
        this->mRightWing->render(scale, callList, false);
    }
    this->callSkinnedDrawlist();
}