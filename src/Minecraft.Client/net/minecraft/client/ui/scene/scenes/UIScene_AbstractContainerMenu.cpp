#include "net/minecraft/client/ui/scene/scenes/UIScene_AbstractContainerMenu.h"

#include "NX/Render/RendererCore.h"
#include "fui/fui.h"
#include "fui/fuiFile.h"
#include "fui/fuiRenderNode.h"
#include "fui/node/FJ_FuiNodeStage.h"
#include "fui/node/document/container/FJ_AbstractContainerDocument.h"
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
    this->m_focusedSection = ESceneSection_NONE;
    gConsoleUIController.OverrideSFX(this->m_padId, 0, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 20, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 2, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 3, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 11, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 10, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 7, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 6, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 4, 1);
    gConsoleUIController.OverrideSFX(this->m_padId, 5, 1);
    this->m_byte110 = false;
}

bool UIScene_AbstractContainerMenu::mapElementsAndNames() {
    fuiRenderNode* node = this->getFuiFile()->getRootNode();

    this->m_mainPanel.setupControl(this, node, "MainPanel");
    this->m_uiControls.push_back(&this->m_mainPanel);

    fuiRenderNode* mainPanelNode = this->m_mainPanel.getFuiRenderNode();

    this->m_backgroundPanel.setupControl(this, mainPanelNode, "BackgroundPanel");
    this->m_uiControls.push_back(&this->m_backgroundPanel);

    this->m_hotbarList.setupControl(this, mainPanelNode, "hotbarList");
    this->m_uiControls.push_back(&this->m_hotbarList);

    this->m_inventoryList.setupControl(this, mainPanelNode, "inventoryList");
    this->m_uiControls.push_back(&this->m_inventoryList);

    this->m_cursor.setupControl(this, mainPanelNode, "cursor");
    this->m_uiControls.push_back(&this->m_cursor);

    this->m_inventoryLabel.setupControl(this, mainPanelNode, "inventoryLabel");
    this->m_uiControls.push_back(&this->m_inventoryLabel);

    return true;
}

void UIScene_AbstractContainerMenu::tick() {
    UIScene::tick();
    this->onMouseTick();

    int width, height;
    this->m_uiLayer->getRenderDimension(width, height);
    if (width == 1280 && height == 480) {
        width = 640;
    }

    int ww = this->m_screenSize.m_x * ((float)width / this->m_stageWidth);
    int hh = this->m_screenSize.m_y * ((float)height / this->m_stageHeight);
    fui::sInstance->dispatchMouseMoveEvent(this->m_fuiFile, ww, hh);
}

void UIScene_AbstractContainerMenu::updateTooltips() {
    IUIScene_AbstractContainerMenu::UpdateTooltips();
}

// NON_MATCHING: logic should be the same
void UIScene_AbstractContainerMenu::render(int a, int b, C4JRender::eViewportType viewportType) {
    this->m_byteE9 = true;

    this->m_byteEa = this->m_byteEa || this->m_containerMenu->m_someValue;

    if (this->m_byteEa) {
        this->m_dwordF8 = this->GetBaseSlotCount();
        int slotsCount = this->m_containerMenu->getSlotsCount();
        for (int i = 0; i != slotsCount; i++) {
            if (this->m_containerMenu->getSlot(i)->hasItem()) {
                this->m_dwordF8++;
            }
        }
    }

    UIScene::render(a, b, viewportType);
    this->m_byteEa = false;
}

void UIScene_AbstractContainerMenu::customDraw(const char* renderNodeName, fuiRect* rect) {
    Minecraft* mc = Minecraft::GetInstance();
    if (!mc->m_localPlayers[this->m_padId] || !mc->m_gameModes[this->m_padId])
        return;

    not_null_ptr<ItemInstance> item = ItemInstance::EMPTY;
    int slotId = -1;

    if (strcmp(renderNodeName, "pointerIcon") == 0) {
        this->m_byteE9 = 0;
        Renderer::sInstance->Clear(1);
        item = this->m_containerMenu->GetQuickCraftItem(this->m_padId, -1);
        if (item->isEmpty()) {
            item = mc->m_localPlayers[this->m_padId]->m_inventory->getCarried();
        }
    } else {
        sscanf(renderNodeName, "slot_%d", &slotId);

        if (slotId != -1) {
            int baseSlotCount = this->GetBaseSlotCount();
            int slotCount = this->m_containerMenu->getSlotsCount();

            for (int i = 0; i != slotCount; i++) {
                Slot* slot = this->m_containerMenu->getSlot(i);
                slot->hasItem();  // wtf is that loop
            }

            Slot* slot = this->m_containerMenu->getSlot(slotId);
            item = this->m_containerMenu->GetQuickCraftItem(this->m_padId, slot->m_index);
            if (item->isEmpty()) {
                this->m_byteE9 = true;
                item = slot->getItem();
            } else {
                // Why temp bool?
                bool elo = IUIScene_AbstractContainerMenu::IsSameItemAs(
                    slot->getItem(), mc->m_localPlayers[this->m_padId]->m_inventory->getCarried());
                this->m_byteE9 = elo;
            }
        }
    }

    if (!item->isEmpty()) {
        this->customDrawSlotControlFui(rect, 0, item,
                                       this->m_containerMenu->isValidIngredient(item, slotId) ? 1.0f : 0.5f,
                                       item->getItem()->isFoil(item), true, false);
    }
}

void UIScene_AbstractContainerMenu::handleInput(int a2, int a3, bool a4, bool a5, bool a6, bool& wasHandled) {
    if (!this->m_byte110) {
        gConsoleUIController.AnimateKeyPress(this->m_padId, a3, a4, a5, a6);

        if (a5) {
            wasHandled = this->handleKeyDown(this->m_padId, a3, a4);
        }
    }
}

void UIScene_AbstractContainerMenu::handleDestroy() {
    // someone went really crazy with 10 ifs for the same thing
    // someone went really crazy with making temp Minecraft var to just not use it later
    Minecraft* mc = Minecraft::GetInstance();
    if (mc->m_gameModes[this->m_padId]) {
        MultiPlayerGameMode* mode = Minecraft::GetInstance()->m_gameModes[this->m_padId];
        if (mode) {
            Tutorial* tut = mode->getTutorial();
            if (tut) {
                tut->changeTutorialState(this->m_tutorialState, nullptr);
            }
        }
    }

    Player* player = (Player*)mc->m_localPlayers[this->m_padId].get();
    if (player && player->m_containerMenu->m_someValue == this->m_containerMenu->m_someValue) {
        player->closeContainer();
    }

    gConsoleUIController.OverrideSFX(this->m_padId, 0, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 20, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 2, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 3, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 11, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 10, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 7, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 6, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 4, 0);
    gConsoleUIController.OverrideSFX(this->m_padId, 5, 0);
}

int UIScene_AbstractContainerMenu::getPad() {
    return this->m_padId;
}

void UIScene_AbstractContainerMenu::PlatformInitialize(bool a2, int a3, int flags) {
    this->m_inventoryLabel.init(L10N::GetString(StringIDs::Inventory_2));
    if (this->m_controlsNeedUpdate) {
        ((FJ_AbstractContainerDocument*)this->m_fuiFile->getRootNode()->m_fuiNodeStage)->HideInventory();
        this->m_hotbarList.UpdateControl();
        this->m_backgroundPanel.UpdateControl();
    }

    if ((flags & 0x80000000) == 0) {
        if (!this->m_controlsNeedUpdate) {
            this->m_inventoryList.addSlots(flags, 27);
        }
        this->m_hotbarList.addSlots(flags + 27, 9);
    }

    // grabbing background panel values as that's what defines split screen shit
    float screenWidth = this->m_backgroundPanel.getWidth();
    float screenHeight = this->m_backgroundPanel.getHeight();
    float XPos = this->m_backgroundPanel.getXPos();
    float YPos = this->m_backgroundPanel.getYPos();
    this->m_dword20 = 0.0f;
    this->m_dword24 = 0.0f;
    this->m_screenPosX = XPos;
    this->m_screenPosXEnd = XPos + screenWidth;
    this->m_screenPosY = YPos;
    this->m_screenPosYEnd = YPos + screenHeight;

    this->m_dword30
        = CConsoleMinecraftApp::sInstance.GetLocalPlayerCount() >= 2 ? floorf(25.0f) : YPos - 50.0f;
    this->m_dword28 = XPos - 50.0f;
    this->m_dword2C = this->m_screenPosXEnd + 50.0f;
    this->m_dword34 = this->m_screenPosYEnd + 25.0f;
    _UIVec2D a, b, sectionPos;
    this->GetItemScreenData(this->m_sceneSection, 0, &a, &b);
    this->GetPositionOfSection(this->m_sceneSection, &sectionPos);
    _UIVec2D final(sectionPos);
    final += a;
    final.m_x += b.m_x / 2;
    final.m_y += b.m_y / 2;
    final.m_x -= this->m_dword20;
    final.m_y -= this->m_dword24;

    if (a2) {
        this->m_screenSize.m_x = this->m_screenSize.m_x * this->m_stageWidth / this->m_dword114;
        this->m_screenSize.m_y = this->m_screenSize.m_y * this->m_stageHeight / this->m_dword118;
    } else {
        this->m_screenSize = final;
    }
    this->m_dword114 = this->m_stageWidth;
    this->m_dword118 = this->m_stageHeight;

    int width, height;
    this->m_uiLayer->getRenderDimension(width, height);
    if (width == 1280 && height == 480) {
        width = 640;
    }

    int ww = this->m_screenSize.m_x * ((float)width / this->m_stageWidth);
    int hh = this->m_screenSize.m_y * ((float)height / this->m_stageHeight);
    fui::sInstance->dispatchMouseMoveEvent(this->m_fuiFile, ww, hh);
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

    if (this->m_focusedSection != ESceneSection_NONE) {
        UIControl_SlotList* sectionAfter = this->getSection(this->m_focusedSection);
        if (sectionAfter != sectionBefore && sectionAfter != nullptr)
            sectionAfter->setFocus(false);
    }

    this->m_focusedSection = section;
}

void UIScene_AbstractContainerMenu::setFocusToPointer(int) {
    if (this->m_focusedSection != ESceneSection_NONE) {
        UIControl_SlotList* section = this->getSection(this->m_focusedSection);
        if (section) {
            section->setFocus(false);
        }
    }
    this->m_focusedSection = ESceneSection_NONE;
}

void UIScene_AbstractContainerMenu::SetPointerText(std::vector<HtmlString>* text, bool a3) {
    this->m_cursor.setLabel(HtmlString::Compose(text), false, a3);
}

not_null_ptr<ItemInstance>
UIScene_AbstractContainerMenu::getSlotItem(IUIScene_AbstractContainerMenu::ESceneSection section,
                                           int slotId) {
    Slot* slot = this->m_containerMenu->getSlot(this->getSectionStartOffset(section) + slotId);

    if (!slot)
        return ItemInstance::EMPTY;

    return slot->getItem();
}

Slot* UIScene_AbstractContainerMenu::getSlot(IUIScene_AbstractContainerMenu::ESceneSection section,
                                             int slotId) {
    return this->m_containerMenu->getSlot(this->getSectionStartOffset(section) + slotId);
}

bool UIScene_AbstractContainerMenu::isSlotEmpty(IUIScene_AbstractContainerMenu::ESceneSection section,
                                                int slotId) {
    Slot* slot = this->m_containerMenu->getSlot(this->getSectionStartOffset(section) + slotId);

    return slot && !slot->hasItem();
}

void UIScene_AbstractContainerMenu::adjustPointerForSafeZone() {}

UIControl_SlotList* UIScene_AbstractContainerMenu::getSection(IUIScene_AbstractContainerMenu::ESceneSection) {
    return nullptr;
}

int UIScene_AbstractContainerMenu::GetBaseSlotCount() {
    return 0;
}
