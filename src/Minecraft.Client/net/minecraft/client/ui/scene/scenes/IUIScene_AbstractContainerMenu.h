#pragma once

#include "net/minecraft/client/tutorial/Tutorial.h"
#include "net/minecraft/client/ui/html/HtmlString.h"
#include "types.h"

class ItemInstance;
class AbstractContainerMenu;
class Slot;
enum EToolTipItem {};
class _UIVec2D {
public:
    float x, y;

    _UIVec2D& operator+=(const _UIVec2D& b) {
        this->x += b.x;
        this->x += b.x;
        return *this;
    }
};

class IUIScene_AbstractContainerMenu {
public:
    enum ESceneSection { ESceneSection_NONE = -1 };
    enum ETapState {};

    void onMouseTick();
    void UpdateTooltips();
    bool IsSameItemAs(not_null_ptr<ItemInstance> a, not_null_ptr<ItemInstance> b);
    bool handleKeyDown(int, int, bool);

    virtual bool IsSectionSlotList(IUIScene_AbstractContainerMenu::ESceneSection);
    virtual bool CanHaveFocus(IUIScene_AbstractContainerMenu::ESceneSection);
    virtual bool IsVisible(IUIScene_AbstractContainerMenu::ESceneSection);
    virtual void getSectionColumns(IUIScene_AbstractContainerMenu::ESceneSection) = 0;
    virtual void getSectionRows(IUIScene_AbstractContainerMenu::ESceneSection) = 0;
    virtual void GetSectionAndSlotInDirection(IUIScene_AbstractContainerMenu::ESceneSection,
                                              IUIScene_AbstractContainerMenu::ETapState, int*, int*)
        = 0;
    virtual void GetPositionOfSection(IUIScene_AbstractContainerMenu::ESceneSection, _UIVec2D*) = 0;
    virtual void GetItemScreenData(IUIScene_AbstractContainerMenu::ESceneSection, int, _UIVec2D*, _UIVec2D*)
        = 0;
    virtual void PlatformInitialize(bool, int, int) = 0;
    virtual void InitDataAssociations(int, AbstractContainerMenu*, int) = 0;
    virtual void handleValidKeyPress(int, int, int);
    virtual void handleOutsideClicked(int, int, int);
    virtual void handleOtherClicked(int, IUIScene_AbstractContainerMenu::ESceneSection, int, bool);
    virtual void handleAdditionalKeyPress(int);
    virtual void handleSlotListClicked(IUIScene_AbstractContainerMenu::ESceneSection, int, int);
    virtual void handleTakeAll(int);
    virtual void handleSectionClick(IUIScene_AbstractContainerMenu::ESceneSection) = 0;
    virtual int getSectionStartOffset(IUIScene_AbstractContainerMenu::ESceneSection) = 0;
    virtual bool doesSectionTreeHaveFocus(IUIScene_AbstractContainerMenu::ESceneSection) = 0;
    virtual void setSectionFocus(IUIScene_AbstractContainerMenu::ESceneSection, int) = 0;
    virtual void setSectionSelectedSlot(IUIScene_AbstractContainerMenu::ESceneSection, int, int, bool) = 0;
    virtual void setFocusToPointer(int) = 0;
    virtual void SetPointerText(std::vector<HtmlString>*, bool) = 0;
    virtual void GetSectionHoverText(IUIScene_AbstractContainerMenu::ESceneSection);
    virtual not_null_ptr<ItemInstance> getSlotItem(IUIScene_AbstractContainerMenu::ESceneSection, int) = 0;
    virtual Slot* getSlot(IUIScene_AbstractContainerMenu::ESceneSection, int) = 0;
    virtual bool isSlotEmpty(IUIScene_AbstractContainerMenu::ESceneSection, int) = 0;
    virtual void adjustPointerForSafeZone() = 0;
    virtual void overrideTooltips(IUIScene_AbstractContainerMenu::ESceneSection, not_null_ptr<ItemInstance>,
                                  bool, bool, bool, int, EToolTipItem&, EToolTipItem&, EToolTipItem&,
                                  EToolTipItem&, EToolTipItem&, EToolTipItem&, EToolTipItem&);
    virtual ~IUIScene_AbstractContainerMenu();
    virtual int getPad() = 0;

    AbstractContainerMenu* mContainerMenu;
    bool idk;
    eTutorial_State mTutorialState;
    _UIVec2D mScreenSize;
    float dword20;
    float dword24;
    float dword28;
    float dword2C;
    float dword30;
    float dword34;
    float mScreenPosX;     // 0x38
    float mScreenPosXEnd;  // 0x3C
    float mScreenPosY;     // 0x40
    float mScreenPosYEnd;  // 0x44
    void* qword48;
    ESceneSection mSceneSection;
    char fill[92];
    bool mControlsNeedUpdate;  // 174
};
