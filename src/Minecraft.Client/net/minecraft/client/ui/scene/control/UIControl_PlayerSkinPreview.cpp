#include "DecompUtils.h"
#include "NX/Platform.h"
#include "fui/fuiFile.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/GameSettings.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/Options.h"
#include "net/minecraft/client/model/models/HumanoidModel.h"
#include "net/minecraft/client/model/models/PlayerModel.h"
#include "net/minecraft/client/renderer/Lighting.h"
#include "net/minecraft/client/renderer/entity/EntityRenderDispatcher.h"
#include "net/minecraft/client/renderer/entity/EntityRenderer.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/texture/Textures.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/client/ui/scene/control/UIControl_PlayerSkinPreview.h"
#include "net/minecraft/client/ui/screen/ScreenSizeCalculator.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/entity/HumanoidArm.h"
#include "net/minecraft/world/entity/SkinAdjustments.h"
#include "net/minecraft/world/entity/player/Player.h"

#include <cstring>
#include <memory>

UIControl_PlayerSkinPreview::UIControl_PlayerSkinPreview() {
    this->setSettedUp(12);
    this->dword58 = 0;
    this->float5C = 1.0;
    this->float60 = 1.0;
    Minecraft* mc = Minecraft::GetInstance();
    ScreenSizeCalculator calc(mc->mOptions, mc->mDisplayWidth, mc->mDisplayHeight, -1);
    this->mDisplayWidth = mc->mDisplayWidth;
    this->mScaleWidth = calc.mScaledWidth;
    this->mDisplayHeight = mc->mDisplayHeight;
    this->mScaledHeight = calc.mScaledHeight;
    this->mSkinCapePath = L"default";
    this->mTextureId = eTextureName_STEVE;
    this->mSkinTexturePath = L"";
    this->mModelYRotation = 0;
    this->dword104 = 0;
    this->mStartYRotation = 0;
    this->mTargetYRotation = 0;
    this->mArmSwingProgress = 0;
    this->bool120 = 0;
    this->bool121 = 0;
    this->bool140 = 0;
    this->bool141 = 0;
    this->bool142 = 0;
    this->bool143 = 0;
    this->mPlayerAnimation = 0;
    this->mSkinChangeFrame = 0;
    this->mIsChangingSkin = false;
    this->mAdditionalModelParts = nullptr;
    this->mModelYRotation = 0.0f;
    this->dword104 = 0;
    this->float118 = 0.0f;
    this->float11C = 0.0f;
}

UIControl_PlayerSkinPreview::~UIControl_PlayerSkinPreview() {}

void UIControl_PlayerSkinPreview::tick() {
    UIControl::tick();

    if (this->mIsChangingSkin) {
        this->mSkinChangeFrame++;
        this->mModelYRotation
            = this->mStartYRotation
              + ((this->mTargetYRotation - this->mStartYRotation) / 15) * (this->mSkinChangeFrame);
        return;
    }

    if (this->bool140)
        this->sub_710055F360();
    if (this->bool141)
        this->sub_710055F37C();
    if (this->bool142)
        this->sub_710055F398();
    if (this->bool143)
        this->sub_710055F3B4();

    if (this->bool120) {
        ++this->char122;
        if ((this->char122 & 3) != 0)
            return;

        if (this->mModelYRotation > 44) {
            this->bool121 = false;
        } else if (this->mModelYRotation < -44) {
            this->bool121 = true;
        }

        if (this->bool121) {
            this->sub_710055F398();
        } else {
            this->sub_710055F3B4();
        }
    }
}

void UIControl_PlayerSkinPreview::SetTexture(const std::wstring& skinTexPath, _TEXTURE_NAME texId) {
    this->mSkinTexturePath = skinTexPath;
    this->mTextureId = texId;

    _SkinAdjustments adj
        = Player::getSkinAdjustmentsById(CMinecraftApp::getSkinIdFromPath(this->mSkinTexturePath));
    char customSkinAnims = GameSettings::GetGameSettings(eGameSetting_CustomSkinAnimation);
    memcpy(&this->mSkinAdjustments, &adj, sizeof(this->mSkinAdjustments));

    if (!customSkinAnims && (adj.mANIM & 0x1F1F810) == 0)
        this->mSkinAdjustments.mANIM = 0;

    this->mAdditionalModelParts = CConsoleMinecraftApp::sInstance.GetAdditionalModelParts(
        CMinecraftApp::getSkinIdFromPath(this->mSkinTexturePath));
}

bool UIControl_PlayerSkinPreview::bindTexture(const std::wstring& texName, int texId) {
    Textures* texs = Minecraft::GetInstance()->mTextures;
    int tex = texs->loadMemTexture(texName, texId);
    if (tex < 0)
        return false;

    texs->bind(tex);
    return true;
}

// not sure if that's texPath and don't care about checking that
bool UIControl_PlayerSkinPreview::bindTexture(const std::wstring& texName, const std::wstring& texPath) {
    Textures* texs = Minecraft::GetInstance()->mTextures;
    int tex = texs->loadMemTexture(texName, texPath);
    if (tex < 0)
        return false;

    texs->bind(tex);
    return true;
}

// NON_MATCHING: math math math, idk if functionality is the same
void UIControl_PlayerSkinPreview::render(EntityRenderer* entRenderer, double a3, double a4, double a5,
                                         float a8, float a7) {
    // args are probably posses, and some width hehight
    GlStateManager::pushMatrix();
    GlStateManager::disableCull();
    // or PlayerModel
    PlayerModel* model = (PlayerModel*)entRenderer->getModel();
    model->mAttackTime = 0.0f;
    model->flag2 = false;
    model->setArmPose(HumanoidArm::RIGHT, (HumanoidModel::eArmPose)0);
    model->setArmPose(HumanoidArm::LEFT, (HumanoidModel::eArmPose)0);
    model->flag1 = false;
    model->flag3 = false;
    model->dwordE4 = 0;
    model->dwordE8 = 0;
    model->mIsYoung = false;
    model->mRiding = false;
    model->mHeadPart->mYRot = 0.0f;
    model->mHeadPart->mYRot = 0.0f;
    memcpy(&model->mSkinAdjustments, &this->mSkinAdjustments, sizeof(this->mSkinAdjustments));
    if (!this->mIsChangingSkin) {
        if (this->mPlayerAnimation == 1) {
            model->flag1 = true;
            model->mHeadPart->mYRot = 0.1f;
        } else if (this->mPlayerAnimation == 2) {
            model->setArmPose(HumanoidArm::RIGHT, (HumanoidModel::eArmPose)1);
            this->mArmSwingProgress++;
            if (this->mArmSwingProgress >= 18.0f)
                this->mArmSwingProgress = 0.0f;

            model->mAttackTime = this->mArmSwingProgress / 18.0f;
        }
    }
    int modelYRot = this->mModelYRotation;

    GlStateManager::translatef(a3, a4, a5);
    GlStateManager::rotatef(180.0f - modelYRot, 0.0f, 1.0f, 0.0f);
    GlStateManager::enableRescaleNormal();
    GlStateManager::scalef(-1.0f, -1.0f, -1.0f);
    GlStateManager::scalef(0.9375f, 0.9375f, 0.9375f);
    GlStateManager::translatef(0.0f, -1.5078f, 0.0f);
    // NOTE: go back to this if not matching, as this is simplifed af
    float prev118 = this->float118;
    this->float114 = prev118;

    float delta = prev118 + (0.1f - prev118) * 0.4f;
    this->float118 = delta;

    this->float11C += delta;

    float a = this->float11C - (1.0f - a7) * delta;
    float b = decomp_fmin1(prev118 + (delta - prev118) * a7, 1.0f);

    MemSect(31);
    this->bindTexture(this->mSkinTexturePath, this->mTextureId);
    MemSect(0);

    GlStateManager::enableAlphaTest();
    model->setAllVisible(true);
    std::shared_ptr<Entity> ent = nullptr;
    ((Model*)model)->render(ent, a, b, 0.0f, modelYRot - modelYRot, 0.0f, 0.0625f, true);

    if (this->bindTexture(this->mSkinCapePath, L"")) {
        GlStateManager::pushMatrix();
        GlStateManager::translatef(0.0f, 0.0f, 0.125f);
        float a = sinf(0.017453f);
        float b = -cosf(0.017453f) * 0.0f;  // what lmfao
        float c = a * 0.0f + b;
        b = b - a * 0.0f;
        float d = b * 100.0f;
        float e = decomp_fmax(c * 100.0f, 0.0f);
        GlStateManager::rotatef((model->flag2 == false ? 1.0f : 26.0f) + e * 0.5f + 6.0f, 1.0f, 0.0f, 0.0f);
        GlStateManager::rotatef(d * 0.5f, 0.0f, 0.0f, 1.0f);
        GlStateManager::rotatef(d * -0.5f, 0.0f, 1.0f, 0.0f);
        GlStateManager::rotatef(180.0f, 0.0f, 1.0f, 0.0f);
        model->renderCloak(0.0625);  // 1.0f / 16.0f, idk which one represents better what 4J had on mind
        GlStateManager::popMatrix();
    }

    GlStateManager::disableRescaleNormal();
    GlStateManager::enableCull();
    GlStateManager::popMatrix();
    MemSect(31);
    // :(
    MemSect(0);

    model->mAttackTime = 0;
    model->flag2 = false;
    model->setArmPose(HumanoidArm::RIGHT, (HumanoidModel::eArmPose)0);
    model->setArmPose(HumanoidArm::LEFT, (HumanoidModel::eArmPose)0);
    model->clearAllOffsets();
}

void UIControl_PlayerSkinPreview::render(fuiRect* rect) {
    Minecraft* mc = Minecraft::GetInstance();
    GlStateManager::enableRescaleNormal();
    GlStateManager::enableColorMaterial();
    GlStateManager::pushMatrix();

    float width = rect->getWidth();
    float height = rect->getHeight();

    if ((this->mSkinAdjustments.mANIM & 0x80000000) != 0) {
        GlStateManager::translatef(width * 0.5f, height - 250.0f - 3.5f, 50.0f);
    } else {
        GlStateManager::translatef(width * 0.5f, height - 3.5f, 50.0f);
    }

    float a = (width / (this->mDisplayWidth / this->mDisplayHeight));
    GlStateManager::scalef(-a, a, a);
    if ((this->mSkinAdjustments.mANIM & 0x80000000) == 0) {
        GlStateManager::rotatef(180.0f, 0.0f, 0.0f, 1.0f);
    }
    Lighting::turnOn();
    float angle = this->dword104;
    GlStateManager::rotatef(-angle, 1.0f, 0.0f, 0.0f);
    bool prevOption = mc->mOptions->byte_13c;
    mc->mOptions->byte_13c = true;

    EPlayerModelType modelType;
    if (!this->mSkinTexturePath.empty()) {
        _SkinAdjustments adj = CConsoleMinecraftApp::sInstance.GetSkinAdjustments(
            CMinecraftApp::getSkinIdFromPath(this->mSkinTexturePath));
        modelType = Player::GetModelTypeFromAnimBitmask(adj.mANIM);
    } else {
        modelType = Player::GetModelTypeFromTextureId(this->mTextureId);
    }

    EntityRenderer* entRenderer
        = Minecraft::GetInstance()->getEntityRenderDispatcher()->getPlayerRenderer(modelType);
    if (entRenderer) {
        // what's the point of checking size... btw took me hours to figure that out lmao
        if (this->mAdditionalModelParts) {
            if (this->mAdditionalModelParts->size() != 0) {
                for (auto it = this->mAdditionalModelParts->begin(); it != this->mAdditionalModelParts->end();
                     ++it) {
                    (*it)->mVisible = true;
                }
            }
        }

        this->render(entRenderer, 0.0, 0.0, 0.0, 1.0f, 1.0f);

        // what's the point of checking size... btw took me hours to figure that out lmao
        if (this->mAdditionalModelParts) {
            if (this->mAdditionalModelParts->size() != 0) {
                for (auto it = this->mAdditionalModelParts->begin(); it != this->mAdditionalModelParts->end();
                     ++it) {
                    (*it)->mVisible = false;
                }
            }
        }
    }

    mc->mOptions->byte_13c = prevOption;
    GlStateManager::popMatrix();
    Lighting::turnOff();
    GlStateManager::disableRescaleNormal();
}