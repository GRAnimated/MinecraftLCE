#include "net/minecraft/client/ui/scene/scenes/UIScene_DeathMenu.h"

#include "fui/fuiFile.h"
#include "fui/fuiRenderNode.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/CTelemetryManager.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/eGameHostOption.h"
#include "net/minecraft/client/gui/Gui.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/tutorial/Tutorial.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIString.h"
#include "net/minecraft/client/ui/scene/scenes/UIScene_PauseMenu.h"
#include "net/minecraft/world/entity/player/MultiplayerLocalPlayer.h"
#include "net/minecraft/world/entity/player/Player.h"
#include "net/minecraft/world/level/gamemode/ClientMasterGameMode.h"
#include "net/minecraft/world/level/gamemode/MultiPlayerGameMode.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

#include <memory>
#include <string>

// NON_MATCHING: I don't have a damn clue, logic should be the same though
UIScene_DeathMenu::UIScene_DeathMenu(int padID, void* a2, UILayer* uiLayer) : UIScene(padID, uiLayer) {
    this->initialiseMovie();

    if (CConsoleMinecraftApp::sInstance.GetGameHostOption((eGameHostOption)0x1Fu)) {
        this->byte10C = true;
        this->mExitGameButton.setVisible(false);
        this->mRespawnButton.setVisible(false);
        if (Minecraft::InMiniGame(EMiniGameId::GLIDE, true))
            this->addTimer(0, 1000);
        else
            this->addTimer(0, 2000);
    } else {
        this->byte10C = false;
        this->mExitGameButton.init(L10N::GetString(StringIDs::ExitGame), 1);
        this->mRespawnButton.init(L10N::GetString(StringIDs::Respawn), 0);
        this->mExitGameButton.setEnable(false, true);
        this->mRespawnButton.setEnable(false, true);
        this->addTimer(1, 1000);
    }

    if (Minecraft::InMiniGame(EMiniGameId::GLIDE, true))
        this->mTitleLabel.setLabel(L10N::GetString(StringIDs::YouCrashed), false, false);
    else
        this->mTitleLabel.setLabel(L10N::GetString(StringIDs::YouDied), false, false);

    Minecraft* mc = Minecraft::GetInstance();
    Gui* gui = Minecraft::GetInstance()->mGui;
    this->mDeathMessageLabel.setLabel(Minecraft::InMiniGame(EMiniGameId::TUMBLE, true)
                                              || Minecraft::InMiniGame(EMiniGameId::GLIDE, true) ?
                                          L"" :
                                          gui->sub_71005806DC(padID),
                                      false, false);
    this->bool10D = false;
    this->bool10E = false;
    std::wstring dupeczka = L"";
    if (Minecraft::InMiniGame(EMiniGameId::NORMAL_WORLD, true)) {
        if (Minecraft::GetInstance()->GetMiniGame()->GetLivesPerRound()) {
            std::shared_ptr<MultiplayerLocalPlayer> player = Minecraft::GetInstance()->mLocalPlayers[padID];
            if (!player->isSpectator()) {
                dupeczka = gui->sub_710054BD68(padID);
            }
        }
    }
    this->mExtraMessageLabel.setLabel(dupeczka, false, false);

    Minecraft* wtf = Minecraft::GetInstance();  // wtf is wrong with 4J
    if (mc) {
        if (wtf->mGameModes[padID]) {
            Tutorial* tutorial = Minecraft::GetInstance()->mGameModes[padID]->getTutorial();
            if (tutorial)
                tutorial->showTutorialPopup(false);
        }
    }
}

std::wstring UIScene_DeathMenu::getMoviePath() {
    if (CConsoleMinecraftApp::sInstance.GetLocalPlayerCount() >= 2)
        return L"DeathMenuSplit";
    else
        return L"DeathMenu";
}

bool UIScene_DeathMenu::mapElementsAndNames() {
    fuiRenderNode* node = this->getFuiFile()->getRootNode();

    this->mRespawnButton.setupControl(this, node, "Respawn");
    this->mUIControls.push_back(&this->mRespawnButton);

    this->mExitGameButton.setupControl(this, node, "ExitGame");
    this->mUIControls.push_back(&this->mExitGameButton);

    this->mTitleLabel.setupControl(this, node, "Title");
    this->mUIControls.push_back(&this->mTitleLabel);

    this->mDeathMessageLabel.setupControl(this, node, "DeathMessage");
    this->mUIControls.push_back(&this->mDeathMessageLabel);

    this->mExtraMessageLabel.setupControl(this, node, "ExtraMessage");
    this->mUIControls.push_back(&this->mExtraMessageLabel);

    return true;
}

UIScene_DeathMenu::~UIScene_DeathMenu() {
    Minecraft* mc = Minecraft::GetInstance();
    ClientMasterGameMode* cmgm = mc->GetClientMasterGameMode();
    if (cmgm && cmgm->IsRoundRestarting() && this->hasTimer(0))
        this->handleTimerComplete(0);

    if (mc) {
        if (mc->mGameModes[this->mPadID]) {
            Tutorial* tutorial = Minecraft::GetInstance()->mGameModes[this->mPadID]->getTutorial();
            if (tutorial)
                tutorial->showTutorialPopup(true);
        }
    }
}

EUIScene UIScene_DeathMenu::getSceneType() {
    return EUIScene::EUIScene_DeathMenu;
}

void UIScene_DeathMenu::tick() {
    UIScene::tick();
}

void UIScene_DeathMenu::updateTooltips() {
    if (CConsoleMinecraftApp::sInstance.GetGameHostOption((eGameHostOption)0x1F)) {
        gConsoleUIController.SetTooltips(this->mPadID, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                         -1, -1, 0, 0);
    } else {
        gConsoleUIController.SetTooltips(this->mPadID, StringIDs::Select, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                         -1, -1, -1, -1, -1, -1, 0, 0);
    }
}

void UIScene_DeathMenu::handleTimerComplete(int timerId) {
    if (timerId != 1) {
        if (timerId)
            return;
        CConsoleMinecraftApp::sInstance.SetAction(this->mPadID, (eXuiAction)6, nullptr);
        this->killTimer(0);
    }

    this->mExitGameButton.setEnable(true, true);
    this->mRespawnButton.setEnable(true, true);
}

void UIScene_DeathMenu::handleInput(int a2, int a3, bool a4, bool a5, bool a6, bool& wasHandled) {
    if (this->byte10C)
        return;

    gConsoleUIController.AnimateKeyPress(this->mPadID, a3, a4, a5, a6);
    if (a3 == 21) {
        wasHandled = true;
    }

    if (a3 == 4 || a3 == 5 || a3 == 20) {
        this->sendInputToMovie(a3, false, a5, false);
        wasHandled = true;
        return;
    }
}

void UIScene_DeathMenu::handlePress(int elementId, int pressType) {
    if (elementId == 0) {
        this->byte10C = true;
        CConsoleMinecraftApp::sInstance.SetAction(this->mPadID, (eXuiAction)6, nullptr);
    }
    if (elementId == 1) {
        CTelemetryManager::sInstance->RecordLevelExit(this->mPadID, (ESen_LevelExitStatus)3);
        UIScene_PauseMenu::OpenExitGameDialog(
            this->mPadID, this->GetCallbackUniqueId(), UIScene_PauseMenu::ExitGameDialogReturned,
            UIScene_PauseMenu::ExitGameSaveDialogReturned, (EOpenExitGameDialog)0);
    }
}
