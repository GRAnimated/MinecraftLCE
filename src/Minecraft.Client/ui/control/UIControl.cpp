#include "Minecraft.Client/ui/control/UIControl.h"
#include "4J_Libraries_Source/fui/fuiRenderNode.h"

UIControl::UIControl(){
    this->mParentUIScene = nullptr;
    this->mOpacity = 1.0f;
    this->mName = "";
    this->mVisible = true;
    this->mBoolIdk = false;
    this->mIntIdk = 0;
    this->mFuiRenderNode = nullptr;
}

bool UIControl::setupControl(UIScene * parentUIScene, fuiRenderNode * renderNode, std::string const& name){
    this->mParentUIScene = parentUIScene;
    this->mName = name;
    this->mFuiRenderNode = renderNode->findNode(name.c_str());
    
    if(this->mFuiRenderNode){
        this->mPosX = this->mFuiRenderNode->getX();
        this->mPosY = this->mFuiRenderNode->getY();
        this->mWidth = this->mFuiRenderNode->getWidth();
        this->mHeight = this->mFuiRenderNode->getHeight();
    }

    return this->mFuiRenderNode != nullptr;
}

void UIControl::UpdateControl(){
    if(this->mFuiRenderNode){
        this->mPosX = this->mFuiRenderNode->getX();
        this->mPosY = this->mFuiRenderNode->getY();
        this->mWidth = this->mFuiRenderNode->getWidth();
        this->mHeight = this->mFuiRenderNode->getHeight();
    }
}

void UIControl::tick(){}

void UIControl::ReInit(){
    if(this->mFuiRenderNode){
        this->mFuiRenderNode->setAlpha(this->mOpacity);
        this->mFuiRenderNode->setVisibility(this->mVisible);
    }
}

void UIControl::setFocus(){}

bool UIControl::hasFocus(){
    return false;
}