#include "net/minecraft/client/model/Model.h"
#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/client/ui/scene/control/UIControl_BitmapIcon.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Label.h"
#include "net/minecraft/client/ui/scene/control/UIControl_MultiList.h"
#include "net/minecraft/client/ui/scene/control/UIControl_PlayerSkinPreview.h"
#include "net/minecraft/client/ui/scene/control/UIControl_Touch.h"
#include "net/minecraft/client/ui/scene/scenes/IUIScene_DlcSelectMenu.h"

class UIScene_SkinSelectMenu : public UIScene, public IUIScene_DlcSelectMenu {
public:
    UIScene_SkinSelectMenu();

    bool mapElementsAndNames() override;
    std::wstring getMoviePath() override;
    ~UIScene_SkinSelectMenu() override;
    EUIScene getSceneType() override;
    void tick() override;
    void updateTooltips() override;
    void updateComponents() override;
    void customDraw(const char*, fuiRect*) override;
    void handleInput(int, int, bool, bool, bool, bool&) override;
    void handleReload() override;
    void handlePress(int, int) override;
    void handleFocusChange(int, int) override;
    void handleAnimationEnd() override;
    void HandleDLCMountingComplete() override;
    void HandleDLCInstalled() override;
    void HandleDLCLicenseChange() override;
    void handleTouchInput(unsigned int, int, int, int, bool, bool, bool) override;

    UIControl_PlayerSkinPreview mSkinPreviews[7];
    UIControl_Label mSkinTitle1Control;
    UIControl_Label mSkinTitle2Control;
    UIControl_Label mPackNameControl;
    UIControl_Label mPackTypeControl;
    UIControl mIggyCharactersControl;
    UIControl mTimerControl;
    UIControl_Touch mTouchControl;
    UIControl_MultiList mSkinButtonList;
    UIControl_BitmapIcon mTexturePackIconControl;
    void* qwordE58;
    void* qwordE60;
    void* qwordE68;
    void* qwordE70;
    void* qwordE78;
    void* qwordE80;
    void* qwordE88;
    void* qwordE90;
    void* qwordE98;
    void* qwordEA0;
    int mSkinID;
    int mSelectedSkinID;
    std::wstring mSelectedSkinName;  // that's wrong for sure
    std::wstring mSkinName;
    std::wstring mSkinCapePath;
    std::vector<SKIN_BOX>* mAdditionalBoxes;
    uint16_t wordF00;
    char byteF02;
    char byteF03;
    char byteF04;
    uint16_t wordF05;
    uint16_t dwordF08;
    char gapF0C[5];
    char byteF11;
};