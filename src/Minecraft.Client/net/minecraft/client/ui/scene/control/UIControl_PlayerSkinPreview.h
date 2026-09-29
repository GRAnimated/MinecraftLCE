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

    int m_dword58;
    float m_float5C;
    float m_float60;
    std::wstring m_mSkinTexturePath;
    _TEXTURE_NAME m_mTextureId;
    std::wstring m_mSkinCapePath;
    _SkinAdjustments m_mSkinAdjustments;
    float m_mDisplayWidth;
    float m_mDisplayHeight;
    float m_mScaleWidth;
    float m_mScaledHeight;
    int m_mModelYRotation;
    int m_dword104;
    int m_mStartYRotation;
    int m_mTargetYRotation;
    float m_float110;
    float m_float114;
    float m_float118;
    float m_float11C;
    bool m_bool120;
    bool m_bool121;
    char m_char122;
    int m_mSkinChangeFrame;
    bool m_mIsChangingSkin;
    float m_mArmSwingProgress;
    int m_mPlayerAnimation;
    std::vector<ModelPart*>* m_mAdditionalModelParts;
    bool m_bool140;
    bool m_bool141;
    bool m_bool142;
    bool m_bool143;
};