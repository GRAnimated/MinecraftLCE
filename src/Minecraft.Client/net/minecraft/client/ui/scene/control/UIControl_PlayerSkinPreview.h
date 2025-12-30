#include "net/minecraft/client/model/geom/ModelPart.h"
#include "net/minecraft/client/renderer/texture/TextureName.h"
#include "net/minecraft/client/ui/scene/control/UIControl.h"

#include "net/minecraft/world/entity/SkinAdjustments.h"
#include <vector>

class UIControl_PlayerSkinPreview : public UIControl {
public:
    enum ESkinPreviewFacing { FRONT, LEFT, RIGHT };
    UIControl_PlayerSkinPreview();

    ~UIControl_PlayerSkinPreview() override;
    void tick() override;

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
    std::wstring mSkinTextureName;
    _SkinAdjustments mSkinAdjustments;
    float mDisplayWidth;
    float mDisplayHeight;
    float mScaleWidth;
    float mScaledHeight;
    int dword100;
    int dword104;
    int dword108;
    int dowrd10C;
    void* qword110;
    void* qword118;
    bool bool120;
    bool bool121;
    char char122;
    int dword124;
    char byte128;
    int dword12C;
    int dword130;
    std::vector<ModelPart>* mAdditionalModelParts;
    bool bool140;
    bool bool141;
    bool bool142;
    bool bool143;
};