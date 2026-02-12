#include "NX/Render/RendererCore.h"
#include "UIScene_MainMenu.h"
#include "fui/fuiFile.h"
#include "fui/node/FJ_FuiNode.h"
#include "java/io/BufferedReader.h"
#include "java/io/ByteArrayInputStream.h"
#include "java/io/InputStreamReader.h"
#include "net/minecraft/client/CGameNetworkManager.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/gui/Font.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
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
    gConsoleUIController.clearResolutionChangeDisableFlag(IUIController::FLAG_0);
    this->initialiseMovie();
    layer->addComponent(a1, EUIComponent_Panorama, nullptr);
    layer->addComponent(a1, EUIComponent_Logo, nullptr);

    this->m_530 = 0;
    this->m_4e8 = false;

    this->m_buttons[0].init(UIString(StringIDs::PlayGame), 0);
    this->m_buttons[1].init(UIString(StringIDs::MiniGames), 1);
    this->m_buttons[2].init(UIString(StringIDs::Leaderboards), 2);
    this->m_buttons[3].init(UIString(StringIDs::Achievements), 3);
    this->m_buttons[4].init(UIString(StringIDs::HelpOptions), 4);

    if (CProfile::sInstance->IsFullVersion()) {
        this->m_showUnlockFullGame = false;
        this->m_buttons[5].init(UIString(StringIDs::MinecraftStore), 5);  // show Minecraft Store
    } else {
        this->m_showUnlockFullGame = true;
        this->m_buttons[5].init(UIString(StringIDs::UnlockFullGame_2), 5);  // show Unlock full game
    }

    this->m_buttons[6].init(UIString(StringIDs::ExitGame), 6);
    this->m_buttons[7].init(UIString(StringIDs::DownloadLatestVersionOfMinecraftForFree), 7);

    this->handleReload();
    this->doHorizontalResizeCheck();

    this->m_splashText = L"Default Text";

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
                m_splashes.push_back(line);
        }

        br.close();
    }

    this->m_4e8 = false;
    this->m_4ea = false;
    this->m_4eb = false;
    this->m_4ec = false;

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

    this->m_buttons[0].setupControl(this, root, "Button1");
    this->m_uiControls.push_back(&this->m_buttons[0]);

    this->m_buttons[1].setupControl(this, root, "Button2");
    this->m_uiControls.push_back(&this->m_buttons[1]);

    this->m_buttons[2].setupControl(this, root, "Button3");
    this->m_uiControls.push_back(&this->m_buttons[2]);

    this->m_buttons[3].setupControl(this, root, "Button4");
    this->m_uiControls.push_back(&this->m_buttons[3]);

    this->m_buttons[4].setupControl(this, root, "Button5");
    this->m_uiControls.push_back(&this->m_buttons[4]);

    this->m_buttons[5].setupControl(this, root, "Button6");
    this->m_uiControls.push_back(&this->m_buttons[5]);

    this->m_buttons[6].setupControl(this, root, "Button7");
    this->m_uiControls.push_back(&this->m_buttons[6]);

    this->m_buttons[7].setupControl(this, root, "ButtonUpsell");
    this->m_uiControls.push_back(&this->m_buttons[7]);

    this->m_timer.setupControl(this, root, "Timer");
    this->m_uiControls.push_back(&this->m_timer);

    return true;
}

void UIScene_MainMenu::handleUnlockFullVersion() {
    // sets the button title to Minecraft Store
    m_buttons[5].setLabel(UIString(StringIDs::MinecraftStore), true, false);
}

void UIScene_MainMenu::customDraw(const char* string, fuiRect* rect) {
    if (!strcmp(string, "Splash"))
        customDrawSplash(rect);
}

void UIScene_MainMenu::handleReload() {
    this->removeControl(&this->m_buttons[2], false);
    this->removeControl(&this->m_buttons[6], false);
}

void UIScene_MainMenu::updateComponents() {
    this->m_uiLayer->showComponent(this->m_padId, EUIComponent_Panorama, true);
    this->m_uiLayer->showComponent(this->m_padId, EUIComponent_Logo, true);
}

// NON_MATCHING | Score: 4720 (lower is better)
// Dunno what inWorldMenu is, and it's missing the atomic bullshit that comes at the bottom which isn't even
// present on Wii U
void UIScene_MainMenu::tick() {
    UIScene::tick();
    if (ConsoleUIController::sCurrentScene != EUIScene_HowToPlay
        && !CConsoleMinecraftApp::sInstance.GetTMSAction(this->m_padId)) {
        int lockedProfile = CProfile::sInstance->GetLockedProfile();
        if (CConsoleMinecraftApp::sInstance.getSomething()) {
            void* inWorldMenu = (void*)(ConsoleUIController::sCurrentScene == EUIScene_LoadCreateJoinMenu
                                        && this->m_4eb);  // ????

            gConsoleUIController.NavigateToScene(lockedProfile, ConsoleUIController::sCurrentScene,
                                                 inWorldMenu, static_cast<EUILayer>(6),
                                                 static_cast<EUIGroup>(6));

            ConsoleUIController::sCurrentScene = EUIScene_HowToPlay;
        }
    }
    if (this->m_showUnlockFullGame != false && CProfile::sInstance->IsFullVersion()) {
        this->m_showUnlockFullGame = false;
        m_buttons[5].setLabel(UIString(StringIDs::MinecraftStore), true, false);
    }
    // insert atomic bomb here
}

void UIScene_MainMenu::customDrawSplash(fuiRect* rect) {
    const Minecraft* minecraft = Minecraft::GetInstance();

    ScreenSizeCalculator calc = ScreenSizeCalculator(minecraft->m_options, minecraft->m_displayWidth,
                                                     minecraft->m_displayHeight, -1);

    this->m_width = minecraft->m_displayWidth;
    this->m_scaledWidth = calc.m_scaledWidth;
    this->m_height = minecraft->m_displayHeight;
    this->m_scaledHeight = calc.m_scaledHeight;

    Renderer::sInstance->TextureBindVertex(-1);

    Font* font = minecraft->m_font;

    GlStateManager::disableCull();
    GlStateManager::disableDepthTest();
    GlStateManager::pushMatrix();

    const float x = rect->m_axX - rect->m_inX;
    const float y = rect->m_axY - rect->m_inY;
    GlStateManager::translatef(x * 0.5f, y, 0.0f);

    GlStateManager::rotatef(-17.0, 0.0, 0.0, 1.0);

    long time = System::processTimeInMilliSecs();
    float t = (time % 1000) / 1000.0f;
    float v13 = Mth::sin(t * Mth::PI + t * Mth::PI);
    v13 = Mth::abs(v13 * 0.1f);
    v13 = ((1.8f - v13) * (this->m_width / this->m_scaledWidth)) * 100.0f;

    int width = font->width(this->m_splashText);
    float scale = v13 / (width + 32);
    GlStateManager::scalef(scale, scale, scale);

    int splashWidth = 0 - font->width(this->m_splashText);

    font->drawShadow(m_splashText, splashWidth / 2, 0xfffffff8, 0xffffff00);
    GlStateManager::popMatrix();
    GlStateManager::disableRescaleNormal();
    GlStateManager::enableDepthTest();
}

bool UIScene_MainMenu::hasFocus(int i) {
    return this->m_focusRelated;
}
