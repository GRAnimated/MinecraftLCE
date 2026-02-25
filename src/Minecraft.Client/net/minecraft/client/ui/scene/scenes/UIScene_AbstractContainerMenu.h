#pragma once

#include "net/minecraft/client/ui/html/HtmlString.h"
#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Cursor.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Label.h"
#include "net/minecraft/client/ui/scene/control/UIControl_SlotList.h"
#include "net/minecraft/client/ui/scene/scenes/IUIScene_AbstractContainerMenu.h"
#include "types.h"

class AbstractContainerMenu;
class _UIVec2D;

class UIScene_AbstractContainerMenu : public UIScene, virtual public IUIScene_AbstractContainerMenu {
public:
    UIScene_AbstractContainerMenu(int padID, UILayer* layer);

    bool mapElementsAndNames() override;
    void tick() override;
    void updateTooltips() override;
    void render(int, int, C4JRender::eViewportType) override;
    void customDraw(const char*, fuiRect*) override;
    void handleInput(int, int, bool, bool, bool, bool&) override;
    void handleDestroy() override;

    int getPad() override;  // 4J reordered that shit, and even funnier thing is that making it override here
                            // does place it in different place in VTable
    void PlatformInitialize(bool, int, int) override;
    void InitDataAssociations(int, AbstractContainerMenu*, int) override;
    bool doesSectionTreeHaveFocus(IUIScene_AbstractContainerMenu::ESceneSection) override;
    void setSectionFocus(IUIScene_AbstractContainerMenu::ESceneSection, int) override;
    void setFocusToPointer(int) override;
    void SetPointerText(std::vector<HtmlString>*, bool) override;
    not_null_ptr<ItemInstance> getSlotItem(IUIScene_AbstractContainerMenu::ESceneSection, int) override;
    Slot* getSlot(IUIScene_AbstractContainerMenu::ESceneSection, int) override;
    bool isSlotEmpty(IUIScene_AbstractContainerMenu::ESceneSection, int) override;
    void adjustPointerForSafeZone() override;
    virtual UIControl_SlotList* getSection(IUIScene_AbstractContainerMenu::ESceneSection);
    virtual int GetBaseSlotCount();

    int m_fill;                      // 8
    ESceneSection m_focusedSection;  // 12
    bool m_byte110;                  // 17
    int m_dword114;
    int m_dword118;
    UIControl m_mainPanel;  // 288
    UIControl_SlotList m_hotbarList;
    UIControl_SlotList m_inventoryList;
    UIControl_Cursor m_cursor;
    UIControl_Label m_inventoryLabel;
    UIControl_Label m_uicontrolLabel330;
    UIControl m_backgroundPanel;
};
