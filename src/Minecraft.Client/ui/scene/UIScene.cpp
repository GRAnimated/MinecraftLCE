#include "Minecraft.Client/ui/scene/UIScene.h"
#include <string>

// It's matching but... some of those variable inits should be moved to header
UIScene::UIScene(int padID, UILayer* uiLayer){
    this->mPadID = padID;
    this->qword30 = 0LL;
    this->mFuiFile = 0LL;
    this->mFocusRelated = 0;
    this->mHideLowerScenes = 0;
    this->byte_e9 = 0;
    this->mHidden = 0;
    this->bool_ad = 0;
    this->mVisible = 1;
    this->byte_96 = 0;
    this->mControlFocus = -1;
    this->mControlChildFocus = 0;
    this->mOpacity = 1.0;
    this->mIsInitializedMovie = 0;
    this->byte_ea = 1;
    this->dwordF8 = 0;
    this->mUILayer = uiLayer;
    this->mBackScene = 0LL;
    this->mCallbackUniqueId = 0LL;
    this->wstring_8 = L"";
    this->bool_28 = 0;
}
