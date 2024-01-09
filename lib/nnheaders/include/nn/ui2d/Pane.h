/**
 * @file Pane.h
 * @brief Base UI panel.
 */

#pragma once

#include <nn/font/font_Util.h>
#include <nn/types.h>

namespace nn::ui2d {
class AnimTransform;
class Layout;

class Pane {
public:
    NN_RUNTIME_TYPEINFO_BASE();

    Pane();
    Pane(const Pane&);

    virtual ~Pane();

    virtual s32 GetVertexColor(s32);
    virtual u8 GetColorElement(s32);
    virtual void SetColorElement(u32, u8);
    virtual u8 GetVertexColorElement(s32);
    virtual void SetVertexColorElement(u32, u8);
    virtual u32 GetMaterialCount() const;
    virtual u64* GetMaterial(s32) const;

    virtual void BindAnimation(AnimTransform*, bool, bool);
    virtual void UnbindAnimation(AnimTransform*, bool);

    void Initialize();
    void SetName(const char*);
    void SetUserData(const char*);
    void AppendChild(Pane*);
    void PrependChild(Pane*);
    void InsertChild(Pane*, Pane*);
    void RemoveChild(Pane*);
    void GetVertexPos() const;

    Pane* mParent;
    u64 _10;
    u64 _18;
    u64 _20;
    u64 _28;
    float mPositionX;
    float mPositionY;
    float mPositionZ;
    float mRotationX;
    float mRotationY;
    float mRotationZ;
    float mScaleX;
    float mScaleY;
    float mSizeX;
    float mSizeY;
    u8 mFlags;
    u8 mAlpha;
    u8 mAlphaInfluence;
    u8 mOriginFlags;
    u32 _5C;
    u64 _60;
    Layout* mLayout;
    u128 _70;
    u128 _80;
    u128 _90;
    u64 _A0;
    u64 _A8;
    void* mAnimExtUserData;
    char mPanelName[0x18];
    u8 _D0;
    char mUserData[8];
    u8 _D9;
    u16 _DA;
    u32 _DC;
};
}  // namespace nn::ui2d
