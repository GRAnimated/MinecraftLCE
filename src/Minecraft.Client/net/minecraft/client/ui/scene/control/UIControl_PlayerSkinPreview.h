#include "net/minecraft/client/model/geom/ModelPart.h"
#include "net/minecraft/client/renderer/texture/TextureName.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"

#include "net/minecraft/world/entity/SkinAdjustments.h"
#include <vector>

class EntityRenderer;
struct fuiRect;

class UIControl_PlayerSkinPreview : public UIControl {
public:
    enum ESkinPreviewFacing { FRONT, LEFT, RIGHT };
    UIControl_PlayerSkinPreview();

    ~UIControl_PlayerSkinPreview() override;
    void tick() override;

    bool bindTexture(const std::wstring&, int);
    bool bindTexture(const std::wstring&, const std::wstring&);
    void render(EntityRenderer*, double, double, double, float, float);
    void render(fuiRect*);
    void SetTexture(const std::wstring& skinTexPath, _TEXTURE_NAME texId);
    void SetFacing(UIControl_PlayerSkinPreview::ESkinPreviewFacing, bool);
    void sub_710055F360();
    void sub_710055F37C();
    void sub_710055F398();
    void sub_710055F3B4();

    int dword58;
    float float5C;
    float float60;
    std::wstring mSkinTexturePath;
    _TEXTURE_NAME mTextureId;
    std::wstring mSkinCapePath;
    _SkinAdjustments mSkinAdjustments;
    float mDisplayWidth;
    float mDisplayHeight;
    float mScaleWidth;
    float mScaledHeight;
    int mModelYRotation;
    int dword104;
    int mStartYRotation;
    int mTargetYRotation;
    float float110;
    float float114;
    float float118;
    float float11C;
    bool bool120;
    bool bool121;
    char char122;
    int mSkinChangeFrame;
    bool mIsChangingSkin;
    float mArmSwingProgress;
    int mPlayerAnimation;
    std::vector<ModelPart*>* mAdditionalModelParts;
    bool bool140;
    bool bool141;
    bool bool142;
    bool bool143;
};