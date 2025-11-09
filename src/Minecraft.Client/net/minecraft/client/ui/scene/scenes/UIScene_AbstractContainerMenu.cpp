#include "net/minecraft/client/ui/scene/scenes/UIScene_AbstractContainerMenu.h"

#include "NX/Render/RendererCore.h"
#include "fui/fui.h"
#include "fui/fuiFile.h"
#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_AbstractContainerDocument.h"
#include "fui/node/FJ_FuiNodeStage.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/Minecraft.h"
#include "net/minecraft/client/resources/L10N.h"
#include "net/minecraft/client/tutorial/Tutorial.h"
#include "net/minecraft/client/ui/ConsoleUIController.h"
#include "net/minecraft/client/ui/StringIDs.h"
#include "net/minecraft/client/ui/html/HtmlString.h"
#include "net/minecraft/client/ui/scene/UILayer.h"
#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"
#include "net/minecraft/client/ui/scene/scenes/IUIScene_AbstractContainerMenu.h"
#include "net/minecraft/world/entity/player/MultiplayerLocalPlayer.h"
#include "net/minecraft/world/inventory/AbstractContainerMenu.h"
#include "net/minecraft/world/inventory/Inventory.h"
#include "net/minecraft/world/inventory/Slot.h"
#include "net/minecraft/world/item/ItemInstance.h"
#include "net/minecraft/world/level/gamemode/MultiPlayerGameMode.h"
#include "types.h"
#include <cmath>
#include <cstdio>
#include <cstring>

UIScene_AbstractContainerMenu::UIScene_AbstractContainerMenu(int padID, UILayer* layer)
    : UIScene(padID, layer) {
    this->mFocusedSection = ESceneSection_NONE;
    gConsoleUIController.OverrideSFX(this->mPadID, 0, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 20, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 2, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 3, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 11, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 10, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 7, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 6, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 4, 1);
    gConsoleUIController.OverrideSFX(this->mPadID, 5, 1);
    this->byte110 = false;
}

bool UIScene_AbstractContainerMenu::mapElementsAndNames() {
    fuiRenderNode* node = this->getFuiFile()->getRootNode();

    this->mMainPanel.setupControl(this, node, "MainPanel");
    this->mUIControls.push_back(&this->mMainPanel);

    fuiRenderNode* mainPanelNode = this->mMainPanel.getFuiRenderNode();

    this->mBackgroundPanel.setupControl(this, mainPanelNode, "BackgroundPanel");
    this->mUIControls.push_back(&this->mBackgroundPanel);

    this->mHotbarList.setupControl(this, mainPanelNode, "hotbarList");
    this->mUIControls.push_back(&this->mHotbarList);

    this->mInventoryList.setupControl(this, mainPanelNode, "inventoryList");
    this->mUIControls.push_back(&this->mInventoryList);

    this->mCursor.setupControl(this, mainPanelNode, "cursor");
    this->mUIControls.push_back(&this->mCursor);

    this->mInventoryLabel.setupControl(this, mainPanelNode, "inventoryLabel");
    this->mUIControls.push_back(&this->mInventoryLabel);

    return true;
}

void UIScene_AbstractContainerMenu::tick() {
    UIScene::tick();
    this->onMouseTick();

    int width, height;
    this->mUILayer->getRenderDimension(width, height);
    if (width == 1280 && height == 480) {
        width = 640;
    }

    int ww = this->mScreenSize.x * ((float)width / this->mStageWidth);
    int hh = this->mScreenSize.y * ((float)height / this->mStageHeight);
    fui::sInstance->dispatchMouseMoveEvent(this->mFuiFile, ww, hh);
}

void UIScene_AbstractContainerMenu::updateTooltips() {
    IUIScene_AbstractContainerMenu::UpdateTooltips();
}

// NON_MATCHING: logic should be the same
void UIScene_AbstractContainerMenu::render(int a, int b, C4JRender::eViewportType viewportType) {
    this->byte_e9 = true;

    this->byte_ea = this->byte_ea || this->mContainerMenu->someValue;

    if (this->byte_ea) {
        this->dwordF8 = this->GetBaseSlotCount();
        int slotsCount = this->mContainerMenu->getSlotsCount();
        for (int i = 0; i != slotsCount; i++) {
            if (this->mContainerMenu->getSlot(i)->hasItem()) {
                this->dwordF8++;
            }
        }
    }

    UIScene::render(a, b, viewportType);
    this->byte_ea = false;
}

void UIScene_AbstractContainerMenu::customDraw(const char* renderNodeName, fuiRect* rect) {
    Minecraft* mc = Minecraft::GetInstance();
    if (!mc->mLocalPlayers[this->mPadID] || !mc->mGameModes[this->mPadID])
        return;

    not_null_ptr<ItemInstance> item = ItemInstance::EMPTY;
    int slotId = -1;

    if (strcmp(renderNodeName, "pointerIcon") == 0) {
        this->byte_e9 = 0;
        Renderer::sInstance->Clear(1);
        item = this->mContainerMenu->GetQuickCraftItem(this->mPadID, -1);
        if (item->isEmpty()) {
            item = mc->mLocalPlayers[this->mPadID]->mInventory->getCarried();
        }
    } else {
        sscanf(renderNodeName, "slot_%d", &slotId);

        if (slotId != -1) {
            int baseSlotCount = this->GetBaseSlotCount();
            int slotCount = this->mContainerMenu->getSlotsCount();

            for (int i = 0; i != slotCount; i++) {
                Slot* slot = this->mContainerMenu->getSlot(i);
                slot->hasItem();  // wtf is that loop
            }

            Slot* slot = this->mContainerMenu->getSlot(slotId);
            item = this->mContainerMenu->GetQuickCraftItem(this->mPadID, slot->mIndex);
            if (item->isEmpty()) {
                this->byte_e9 = true;
                item = slot->getItem();
            } else {
                // Why temp bool?
                bool elo = IUIScene_AbstractContainerMenu::IsSameItemAs(
                    slot->getItem(), mc->mLocalPlayers[this->mPadID]->mInventory->getCarried());
                this->byte_e9 = elo;
            }
        }
    }

    if (!item->isEmpty()) {
        this->customDrawSlotControlFui(rect, 0, item,
                                       this->mContainerMenu->isValidIngredient(item, slotId) ? 1.0f : 0.5f,
                                       item->getItem()->isFoil(item), true, false);
    }
}

void UIScene_AbstractContainerMenu::handleInput(int a2, int a3, bool a4, bool a5, bool a6, bool& wasHandled) {
    if (!this->byte110) {
        gConsoleUIController.AnimateKeyPress(this->mPadID, a3, a4, a5, a6);

        if (a5) {
            wasHandled = this->handleKeyDown(this->mPadID, a3, a4);
        }
    }
}

void UIScene_AbstractContainerMenu::handleDestroy() {
    // someone went really crazy with 10 ifs for the same thing
    // someone went really crazy with making temp Minecraft var to just not use it later
    Minecraft* mc = Minecraft::GetInstance();
    if (mc->mGameModes[this->mPadID]) {
        MultiPlayerGameMode* mode = Minecraft::GetInstance()->mGameModes[this->mPadID];
        if (mode) {
            Tutorial* tut = mode->getTutorial();
            if (tut) {
                tut->changeTutorialState(this->mTutorialState, nullptr);
            }
        }
    }

    Player* player = mc->mLocalPlayers[this->mPadID].get();
    if (player && player->mContainerMenu->someValue == this->mContainerMenu->someValue) {
        player->closeContainer();
    }

    gConsoleUIController.OverrideSFX(this->mPadID, 0, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 20, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 2, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 3, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 11, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 10, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 7, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 6, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 4, 0);
    gConsoleUIController.OverrideSFX(this->mPadID, 5, 0);
}

int UIScene_AbstractContainerMenu::getPad() {
    return this->mPadID;
}

void UIScene_AbstractContainerMenu::PlatformInitialize(bool a2, int a3, int flags) {
    this->mInventoryLabel.init(L10N::GetString(StringIDs::Inventory_2));
    if (this->mControlsNeedUpdate) {
        ((FJ_AbstractContainerDocument*)this->mFuiFile->getRootNode()->mFuiNodeStage)->HideInventory();
        this->mHotbarList.UpdateControl();
        this->mBackgroundPanel.UpdateControl();
    }

    if ((flags & 0x80000000) == 0) {
        if (!this->mControlsNeedUpdate) {
            this->mInventoryList.addSlots(flags, 27);
        }
        this->mHotbarList.addSlots(flags + 27, 9);
    }

    // grabbing background panel values as that's what defines split screen shit
    float screenWidth = this->mBackgroundPanel.getWidth();
    float screenHeight = this->mBackgroundPanel.getHeight();
    float XPos = this->mBackgroundPanel.getXPos();
    float YPos = this->mBackgroundPanel.getYPos();
    this->dword20 = 0.0f;
    this->dword24 = 0.0f;
    this->mScreenPosX = XPos;
    this->mScreenPosXEnd = XPos + screenWidth;
    this->mScreenPosY = YPos;
    this->mScreenPosYEnd = YPos + screenHeight;

    this->dword30 = CConsoleMinecraftApp::sInstance.GetLocalPlayerCount() >= 2 ? floorf(25.0f) : YPos - 50.0f;
    this->dword28 = XPos - 50.0f;
    this->dword2C = this->mScreenPosXEnd + 50.0f;
    this->dword34 = this->mScreenPosYEnd + 25.0f;
    _UIVec2D a, b, sectionPos;
    this->GetItemScreenData(this->mSceneSection, 0, &a, &b);
    this->GetPositionOfSection(this->mSceneSection, &sectionPos);
    _UIVec2D final(sectionPos);
    final += a;
    final.x += b.x / 2;
    final.y += b.y / 2;
    final.x -= this->dword20;
    final.y -= this->dword24;

    if (a2) {
        this->mScreenSize.x = this->mScreenSize.x * this->mStageWidth / this->dword114;
        this->mScreenSize.y = this->mScreenSize.y * this->mStageHeight / this->dword118;
    } else {
        this->mScreenSize = final;
    }
    this->dword114 = this->mStageWidth;
    this->dword118 = this->mStageHeight;

    int width, height;
    this->mUILayer->getRenderDimension(width, height);
    if (width == 1280 && height == 480) {
        width = 640;
    }

    int ww = this->mScreenSize.x * ((float)width / this->mStageWidth);
    int hh = this->mScreenSize.y * ((float)height / this->mStageHeight);
    fui::sInstance->dispatchMouseMoveEvent(this->mFuiFile, ww, hh);
}

void UIScene_AbstractContainerMenu::InitDataAssociations(int, AbstractContainerMenu*, int) {}

// NON_MATCHING: this function as is matches, but thunk of it doesn't as instead of call to this function it
// does "inline" and returns false directly that's why I suspect that there was some check with this but it
// got optimised as it was always false
bool UIScene_AbstractContainerMenu::doesSectionTreeHaveFocus(
    IUIScene_AbstractContainerMenu::ESceneSection a2) {
    return false;
}

void UIScene_AbstractContainerMenu::setSectionFocus(IUIScene_AbstractContainerMenu::ESceneSection section,
                                                    int) {
    UIControl_SlotList* sectionBefore = this->getSection(section);
    if (sectionBefore)
        sectionBefore->setFocus(true);

    if (this->mFocusedSection != ESceneSection_NONE) {
        UIControl_SlotList* sectionAfter = this->getSection(this->mFocusedSection);
        if (sectionAfter != sectionBefore && sectionAfter != nullptr)
            sectionAfter->setFocus(false);
    }

    this->mFocusedSection = section;
}

void UIScene_AbstractContainerMenu::setFocusToPointer(int) {
    if (this->mFocusedSection != ESceneSection_NONE) {
        UIControl_SlotList* section = this->getSection(this->mFocusedSection);
        if (section) {
            section->setFocus(false);
        }
    }
    this->mFocusedSection = ESceneSection_NONE;
}

void UIScene_AbstractContainerMenu::SetPointerText(std::vector<HtmlString>* text, bool a3) {
    this->mCursor.setLabel(HtmlString::Compose(text), false, a3);
}

not_null_ptr<ItemInstance>
UIScene_AbstractContainerMenu::getSlotItem(IUIScene_AbstractContainerMenu::ESceneSection section,
                                           int slotId) {
    Slot* slot = this->mContainerMenu->getSlot(this->getSectionStartOffset(section) + slotId);

    if (!slot)
        return ItemInstance::EMPTY;

    return slot->getItem();
}

Slot* UIScene_AbstractContainerMenu::getSlot(IUIScene_AbstractContainerMenu::ESceneSection section,
                                             int slotId) {
    return this->mContainerMenu->getSlot(this->getSectionStartOffset(section) + slotId);
}

bool UIScene_AbstractContainerMenu::isSlotEmpty(IUIScene_AbstractContainerMenu::ESceneSection section,
                                                int slotId) {
    Slot* slot = this->mContainerMenu->getSlot(this->getSectionStartOffset(section) + slotId);

    return slot && !slot->hasItem();
}

void UIScene_AbstractContainerMenu::adjustPointerForSafeZone() {}

UIControl_SlotList* UIScene_AbstractContainerMenu::getSection(IUIScene_AbstractContainerMenu::ESceneSection) {
    return nullptr;
}

int UIScene_AbstractContainerMenu::GetBaseSlotCount() {
    return 0;
}
