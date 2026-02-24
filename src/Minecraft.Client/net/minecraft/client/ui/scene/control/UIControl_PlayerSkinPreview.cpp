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
    this->m_dword58 = 0;
    this->m_float5C = 1.0;
    this->m_float60 = 1.0;
    Minecraft* mc = Minecraft::GetInstance();
    ScreenSizeCalculator calc(mc->m_options, mc->m_displayWidth, mc->m_displayHeight, -1);
    this->m_mDisplayWidth = mc->m_displayWidth;
    this->m_mScaleWidth = calc.m_scaledWidth;
    this->m_mDisplayHeight = mc->m_displayHeight;
    this->m_mScaledHeight = calc.m_scaledHeight;
    this->m_mSkinCapePath = L"default";
    this->m_mTextureId = eTextureName_STEVE;
    this->m_mSkinTexturePath = L"";
    this->m_mModelYRotation = 0;
    this->m_dword104 = 0;
    this->m_mStartYRotation = 0;
    this->m_mTargetYRotation = 0;
    this->m_mArmSwingProgress = 0;
    this->m_bool120 = 0;
    this->m_bool121 = 0;
    this->m_bool140 = 0;
    this->m_bool141 = 0;
    this->m_bool142 = 0;
    this->m_bool143 = 0;
    this->m_mPlayerAnimation = 0;
    this->m_mSkinChangeFrame = 0;
    this->m_mIsChangingSkin = false;
    this->m_mAdditionalModelParts = nullptr;
    this->m_mModelYRotation = 0.0f;
    this->m_dword104 = 0;
    this->m_float118 = 0.0f;
    this->m_float11C = 0.0f;
}

UIControl_PlayerSkinPreview::~UIControl_PlayerSkinPreview() {}

void UIControl_PlayerSkinPreview::tick() {
    UIControl::tick();

    if (this->m_mIsChangingSkin) {
        this->m_mSkinChangeFrame++;
        this->m_mModelYRotation
            = this->m_mStartYRotation
              + ((this->m_mTargetYRotation - this->m_mStartYRotation) / 15) * (this->m_mSkinChangeFrame);
        return;
    }

    if (this->m_bool140)
        this->sub_710055F360();
    if (this->m_bool141)
        this->sub_710055F37C();
    if (this->m_bool142)
        this->sub_710055F398();
    if (this->m_bool143)
        this->sub_710055F3B4();

    if (this->m_bool120) {
        ++this->m_char122;
        if ((this->m_char122 & 3) != 0)
            return;

        if (this->m_mModelYRotation > 44) {
            this->m_bool121 = false;
        } else if (this->m_mModelYRotation < -44) {
            this->m_bool121 = true;
        }

        if (this->m_bool121) {
            this->sub_710055F398();
        } else {
            this->sub_710055F3B4();
        }
    }
}

void UIControl_PlayerSkinPreview::SetTexture(const std::wstring& skinTexPath, _TEXTURE_NAME texId) {
    this->m_mSkinTexturePath = skinTexPath;
    this->m_mTextureId = texId;

    _SkinAdjustments adj
        = Player::getSkinAdjustmentsById(CMinecraftApp::getSkinIdFromPath(this->m_mSkinTexturePath));
    char customSkinAnims = GameSettings::GetGameSettings(eGameSetting_CustomSkinAnimation);
    memcpy(&this->m_mSkinAdjustments, &adj, sizeof(this->m_mSkinAdjustments));

    if (!customSkinAnims && (adj.m_anim & 0x1F1F810) == 0)
        this->m_mSkinAdjustments.m_anim = 0;

    this->m_mAdditionalModelParts = CConsoleMinecraftApp::sInstance.GetAdditionalModelParts(
        CMinecraftApp::getSkinIdFromPath(this->m_mSkinTexturePath));
}

bool UIControl_PlayerSkinPreview::bindTexture(const std::wstring& texName, int texId) {
    Textures* texs = Minecraft::GetInstance()->m_textures;
    int tex = texs->loadMemTexture(texName, texId);
    if (tex < 0)
        return false;

    texs->bind(tex);
    return true;
}

// not sure if that's texPath and don't care about checking that
bool UIControl_PlayerSkinPreview::bindTexture(const std::wstring& texName, const std::wstring& texPath) {
    Textures* texs = Minecraft::GetInstance()->m_textures;
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
    model->m_attackTime = 0.0f;
    model->m_flag2 = false;
    model->setArmPose(HumanoidArm::RIGHT, (HumanoidModel::eArmPose)0);
    model->setArmPose(HumanoidArm::LEFT, (HumanoidModel::eArmPose)0);
    model->m_flag1 = false;
    model->m_flag3 = false;
    model->m_dwordE4 = 0;
    model->m_dwordE8 = 0;
    model->m_isYoung = false;
    model->m_riding = false;
    model->m_mHeadPart->m_xRot = 0.0f;
    memcpy(&model->m_mSkinAdjustments, &this->m_mSkinAdjustments, sizeof(this->m_mSkinAdjustments));
    if (!this->m_mIsChangingSkin) {
        if (this->m_mPlayerAnimation == 1) {
            model->m_flag1 = true;
            model->m_mHeadPart->m_yRot = 0.1f;
        } else if (this->m_mPlayerAnimation == 2) {
            model->setArmPose(HumanoidArm::RIGHT, (HumanoidModel::eArmPose)1);
            this->m_mArmSwingProgress++;
            if (this->m_mArmSwingProgress >= 18.0f)
                this->m_mArmSwingProgress = 0.0f;

            model->m_attackTime = this->m_mArmSwingProgress / 18.0f;
        }
    }
    int modelYRot = this->m_mModelYRotation;

    GlStateManager::translatef(a3, a4, a5);
    GlStateManager::rotatef(180.0f - modelYRot, 0.0f, 1.0f, 0.0f);
    GlStateManager::enableRescaleNormal();
    GlStateManager::scalef(-1.0f, -1.0f, -1.0f);
    GlStateManager::scalef(0.9375f, 0.9375f, 0.9375f);
    GlStateManager::translatef(0.0f, -1.5078f, 0.0f);
    // NOTE: go back to this if not matching, as this is simplifed af
    float prev118 = this->m_float118;
    this->m_float114 = prev118;

    float delta = prev118 + (0.1f - prev118) * 0.4f;
    this->m_float118 = delta;

    this->m_float11C += delta;

    float a = this->m_float11C - (1.0f - a7) * delta;
    float b = decomp_fmin1(prev118 + (delta - prev118) * a7, 1.0f);

    MemSect(31);
    this->bindTexture(this->m_mSkinTexturePath, this->m_mTextureId);
    MemSect(0);

    GlStateManager::enableAlphaTest();
    model->setAllVisible(true);
    std::shared_ptr<Entity> ent = nullptr;
    ((Model*)model)->render(ent, a, b, 0.0f, modelYRot - modelYRot, 0.0f, 0.0625f, true);

    if (this->bindTexture(this->m_mSkinCapePath, L"")) {
        GlStateManager::pushMatrix();
        GlStateManager::translatef(0.0f, 0.0f, 0.125f);
        float a = sinf(0.017453f);
        float b = -cosf(0.017453f) * 0.0f;  // what lmfao
        float c = a * 0.0f + b;
        b = b - a * 0.0f;
        float d = b * 100.0f;
        float e = decomp_fmax(c * 100.0f, 0.0f);
        GlStateManager::rotatef((model->m_flag2 == false ? 1.0f : 26.0f) + e * 0.5f + 6.0f, 1.0f, 0.0f, 0.0f);
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

    model->m_attackTime = 0;
    model->m_flag2 = false;
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

    if ((this->m_mSkinAdjustments.m_anim & 0x80000000) != 0) {
        GlStateManager::translatef(width * 0.5f, height - 250.0f - 3.5f, 50.0f);
    } else {
        GlStateManager::translatef(width * 0.5f, height - 3.5f, 50.0f);
    }

    float a = (width / (this->m_mDisplayWidth / this->m_mDisplayHeight));
    GlStateManager::scalef(-a, a, a);
    if ((this->m_mSkinAdjustments.m_anim & 0x80000000) == 0) {
        GlStateManager::rotatef(180.0f, 0.0f, 0.0f, 1.0f);
    }
    Lighting::turnOn();
    float angle = this->m_dword104;
    GlStateManager::rotatef(-angle, 1.0f, 0.0f, 0.0f);
    bool prevOption = mc->m_options->m_byte13c;
    mc->m_options->m_byte13c = true;

    EPlayerModelType modelType;
    if (!this->m_mSkinTexturePath.empty()) {
        _SkinAdjustments adj = CConsoleMinecraftApp::sInstance.GetSkinAdjustments(
            CMinecraftApp::getSkinIdFromPath(this->m_mSkinTexturePath));
        modelType = Player::GetModelTypeFromAnimBitmask(adj.m_anim);
    } else {
        modelType = Player::GetModelTypeFromTextureId(this->m_mTextureId);
    }

    EntityRenderer* entRenderer
        = Minecraft::GetInstance()->getEntityRenderDispatcher()->getPlayerRenderer(modelType);
    if (entRenderer) {
        // what's the point of checking size... btw took me hours to figure that out lmao
        if (this->m_mAdditionalModelParts) {
            if (this->m_mAdditionalModelParts->size() != 0) {
                for (auto it = this->m_mAdditionalModelParts->begin();
                     it != this->m_mAdditionalModelParts->end(); ++it) {
                    (*it)->m_visible = true;
                }
            }
        }

        this->render(entRenderer, 0.0, 0.0, 0.0, 1.0f, 1.0f);

        // what's the point of checking size... btw took me hours to figure that out lmao
        if (this->m_mAdditionalModelParts) {
            if (this->m_mAdditionalModelParts->size() != 0) {
                for (auto it = this->m_mAdditionalModelParts->begin();
                     it != this->m_mAdditionalModelParts->end(); ++it) {
                    (*it)->m_visible = false;
                }
            }
        }
    }

    mc->m_options->m_byte13c = prevOption;
    GlStateManager::popMatrix();
    Lighting::turnOff();
    GlStateManager::disableRescaleNormal();
}