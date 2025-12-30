#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/GameSettings.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/client/ui/scene/control/UIControl_PlayerSkinPreview.h"
#include "net/minecraft/client/ui/screen/ScreenSizeCalculator.h"
#include "net/minecraft/world/entity/SkinAdjustments.h"
#include "net/minecraft/world/entity/player/Player.h"

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
    this->mSkinTextureName = L"default";
    this->mTextureId = eTextureName_STEVE;
    this->mSkinTexturePath = L"";
    this->dword100 = 0;
    this->dword104 = 0;
    this->dword108 = 0;
    this->dowrd10C = 0;
    this->dword12C = 0;
    this->bool120 = 0;
    this->bool121 = 0;
    this->bool140 = 0;
    this->bool141 = 0;
    this->bool142 = 0;
    this->bool143 = 0;
    this->dword130 = 0;
    this->dword124 = 0;
    this->byte128 = 0;
    this->mAdditionalModelParts = nullptr;
    this->qword110 = 0LL;
    this->qword118 = 0LL;
}

UIControl_PlayerSkinPreview::~UIControl_PlayerSkinPreview() {}

// NON_MATCHING: does the same thing, but doesn't match byte-for-byte..e.e
void UIControl_PlayerSkinPreview::tick() {
    UIControl::tick();

    if (this->byte128) {
        this->dword100 = this->dword108 + ((this->dowrd10C - this->dword108) / 15) * ++this->dword124;
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

    if (this->bool120 && ((this->char122++ & 3) == 0)) {
        int value = this->dword100;

        bool outsideRange = (value > 44 || value < -44);
        this->bool121 = outsideRange;

        if (this->bool121 || outsideRange)
            this->sub_710055F398();
        else
            this->sub_710055F3B4();
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