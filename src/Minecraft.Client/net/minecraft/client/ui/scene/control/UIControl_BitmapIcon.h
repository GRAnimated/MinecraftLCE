#include "net/minecraft/client/ui/scene/control/UIControl.h"
class UIControl_BitmapIcon : public UIControl {
public:
    UIControl_BitmapIcon();

    ~UIControl_BitmapIcon() override;
    bool setupControl(UIScene*, fuiRenderNode*, const std::string&) override;
    void tick() override;
    void ReInit() override;

    std::wstring mTextureName;
};