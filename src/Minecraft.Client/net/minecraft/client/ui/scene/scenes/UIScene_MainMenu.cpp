#include "NX/Render/RendererCore.h"
#include "UIScene_MainMenu.h"
#include "com/mojang/blaze3d/platform/GlStateManager.h"
#include "fui/fuiFile.h"
#include "fui/node/FJ_FuiNode.h"
#include "java/io/BufferedReader.h"
#include "java/io/ByteArrayInputStream.h"
#include "java/io/InputStreamReader.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/gui/Font.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/client/ui/scene/UILayer.h"
#include "net/minecraft/client/ui/screen/ScreenSizeCalculator.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/core/profile/CProfile.h"
#include "net/minecraft/sounds/SoundEvent.h"
#include "net/minecraft/util/Mth.h"
#include "net/minecraft/world/entity/Entity.h"

#include <string>

UIScene_MainMenu::UIScene_MainMenu(int a1, void* a2, UILayer* layer) : UIScene(a1, layer) {
    Entity::fjDebugCheckSmallIdLeaks();
    gConsoleUIController.setUnk2(false);
    this->initialiseMovie();
    layer->addComponent(a1, EUIComponent_Panorama, nullptr);
    layer->addComponent(a1, EUIComponent_Logo, nullptr);

    this->_530 = 0;
    this->_4e8 = false;

    this->mButtons[0].init(UIString(StringIDs::PlayGame), 0);
    this->mButtons[1].init(UIString(StringIDs::MiniGames), 1);
    this->mButtons[2].init(UIString(StringIDs::Leaderboards), 2);
    this->mButtons[3].init(UIString(StringIDs::Achievements), 3);
    this->mButtons[4].init(UIString(StringIDs::HelpOptions), 4);

    if (CProfile::sInstance->IsFullVersion()) {
        this->mShowUnlockFullGame = false;
        this->mButtons[5].init(UIString(StringIDs::MinecraftStore), 5);  // show Minecraft Store
    } else {
        this->mShowUnlockFullGame = true;
        this->mButtons[5].init(UIString(StringIDs::UnlockFullGame_2), 5);  // show Unlock full game
    }

    this->mButtons[6].init(UIString(StringIDs::ExitGame), 6);
    this->mButtons[7].init(UIString(StringIDs::DownloadLatestVersionOfMinecraftForFree), 7);

    this->handleReload();
    this->doHorizontalResizeCheck();

    this->mSplashText = L"Default Text";

    std::wstring filename = L"splashes.txt";
    if (CConsoleMinecraftApp::sInstance.hasArchiveFile(filename, false)) {
        arrayWithLength<unsigned char> file = CConsoleMinecraftApp::sInstance.getArchiveFile(filename, false);
        ByteArrayInputStream bais = ByteArrayInputStream(file);
        InputStreamReader isr = InputStreamReader(&bais);
        BufferedReader br = BufferedReader(&isr);

        std::wstring line = L"";
        while (!(line = br.readLine()).empty()) {
            line = trimString(line);

            if (!line.empty())
                mSplashes.push_back(line);
        }

        br.close();
    }

    this->_4e8 = false;
    this->_4ea = false;
    this->_4eb = false;
    this->_4ec = false;

    CConsoleMinecraftApp::sInstance.setLevelGenerationOptions(nullptr);
    Minecraft::GetInstance()->SetupMiniGameInstance(MiniGameDef::GetCustomGameModeById(NORMAL_WORLD, true),
                                                    0);
    CGameNetworkManager::sInstance.ResetLeavingGame();
    gConsoleUIController.TouchBoxRebuild(this);
    gConsoleUIController.ResetSelectedItem();
}

bool UIScene_MainMenu::mapElementsAndNames() {
    UIScene::mapElementsAndNames();

    fuiRenderNode* root = this->getFuiFile()->getRootNode();

    this->mButtons[0].setupControl(this, root, "Button1");
    this->mUIControls.push_back(&this->mButtons[0]);

    this->mButtons[1].setupControl(this, root, "Button2");
    this->mUIControls.push_back(&this->mButtons[1]);

    this->mButtons[2].setupControl(this, root, "Button3");
    this->mUIControls.push_back(&this->mButtons[2]);

    this->mButtons[3].setupControl(this, root, "Button4");
    this->mUIControls.push_back(&this->mButtons[3]);

    this->mButtons[4].setupControl(this, root, "Button5");
    this->mUIControls.push_back(&this->mButtons[4]);

    this->mButtons[5].setupControl(this, root, "Button6");
    this->mUIControls.push_back(&this->mButtons[5]);

    this->mButtons[6].setupControl(this, root, "Button7");
    this->mUIControls.push_back(&this->mButtons[6]);

    this->mButtons[7].setupControl(this, root, "ButtonUpsell");
    this->mUIControls.push_back(&this->mButtons[7]);

    this->mTimer.setupControl(this, root, "Timer");
    this->mUIControls.push_back(&this->mTimer);

    return true;
}

void UIScene_MainMenu::handleUnlockFullVersion() {
    // sets the button title to Minecraft Store
    mButtons[5].setLabel(UIString(StringIDs::MinecraftStore), true, false);
}

void UIScene_MainMenu::customDraw(const char* string, fuiRect* rect) {
    if (!strcmp(string, "Splash"))
        customDrawSplash(rect);
}

void UIScene_MainMenu::handleReload() {
    this->removeControl(&this->mButtons[2], false);
    this->removeControl(&this->mButtons[6], false);
}

void UIScene_MainMenu::updateComponents() {
    this->mUILayer->showComponent(this->mPadID, EUIComponent_Panorama, true);
    this->mUILayer->showComponent(this->mPadID, EUIComponent_Logo, true);
}

// NON_MATCHING | Score: 4720 (lower is better)
// Dunno what inWorldMenu is, and it's missing the atomic bullshit that comes at the bottom which isn't even
// present on Wii U
void UIScene_MainMenu::tick() {
    UIScene::tick();
    if (ConsoleUIController::sCurrentScene != EUIScene_HowToPlay
        && !CConsoleMinecraftApp::sInstance.GetTMSAction(this->mPadID)) {
        int lockedProfile = CProfile::sInstance->GetLockedProfile();
        if (CConsoleMinecraftApp::sInstance.getSomething()) {
            void* inWorldMenu = (void*)(ConsoleUIController::sCurrentScene == EUIScene_LoadCreateJoinMenu
                                        && this->_4eb);  // ????

            gConsoleUIController.NavigateToScene(lockedProfile, ConsoleUIController::sCurrentScene,
                                                 inWorldMenu, static_cast<EUILayer>(6),
                                                 static_cast<EUIGroup>(6));

            ConsoleUIController::sCurrentScene = EUIScene_HowToPlay;
        }
    }
    if (this->mShowUnlockFullGame != false && CProfile::sInstance->IsFullVersion()) {
        this->mShowUnlockFullGame = false;
        mButtons[5].setLabel(UIString(StringIDs::MinecraftStore), true, false);
    }
    // insert atomic bomb here
}

void UIScene_MainMenu::customDrawSplash(fuiRect* rect) {
    const Minecraft* minecraft = Minecraft::GetInstance();

    ScreenSizeCalculator calc
        = ScreenSizeCalculator(minecraft->mOptions, minecraft->mDisplayWidth, minecraft->mDisplayHeight, -1);

    this->mWidth = minecraft->mDisplayWidth;
    this->mScaledWidth = calc.mScaledWidth;
    this->mHeight = minecraft->mDisplayHeight;
    this->mScaledHeight = calc.mScaledHeight;

    Renderer::sInstance->TextureBindVertex(-1);

    Font* font = minecraft->mFont;

    GlStateManager::disableCull();
    GlStateManager::disableDepthTest();
    GlStateManager::pushMatrix();

    const float x = rect->maxX - rect->minX;
    const float y = rect->maxY - rect->minY;
    GlStateManager::translatef(x * 0.5f, y, 0.0f);

    GlStateManager::rotatef(-17.0, 0.0, 0.0, 1.0);

    long time = System::processTimeInMilliSecs();
    float t = (time % 1000) / 1000.0f;
    float v13 = Mth::sin(t * Mth::PI + t * Mth::PI);
    v13 = Mth::abs(v13 * 0.1f);
    v13 = ((1.8f - v13) * (this->mWidth / this->mScaledWidth)) * 100.0f;

    int width = font->width(this->mSplashText);
    float scale = v13 / (width + 32);
    GlStateManager::scalef(scale, scale, scale);

    int splashWidth = 0 - font->width(this->mSplashText);

    font->drawShadow(mSplashText, splashWidth / 2, 0xfffffff8, 0xffffff00);
    GlStateManager::popMatrix();
    GlStateManager::disableRescaleNormal();
    GlStateManager::enableDepthTest();
}

bool UIScene_MainMenu::hasFocus(int i) {
    return this->mFocusRelated;
}
