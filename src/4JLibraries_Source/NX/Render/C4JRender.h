#pragma once

#include "arm_neon.h"

class _XSOCIAL_PREVIEWIMAGE;
class ImageFileBuffer;
class D3DXIMAGE_INFO;

class C4JRender {
public:
    C4JRender();

    enum eVertexType {};
    enum ePrimitiveType {
        eViewportType_Quad = 3, // not sure
    };
    enum ePixelShaderType {};
    enum eTextureFormat {};
    enum eViewportType {
        eViewportType_None = 0,
        eViewportType_Top = 1,
        eViewportType_Bottom = 2,
        eViewportType_Left = 3,
        eViewportType_Right = 4,
        eViewportType_TopLeft = 5,
        eViewportType_TopRight = 6,
        eViewportType_BottomLeft = 7,
        eViewportType_BottomRight = 8,
        eViewportType_Full = 9
    };

    virtual void Tick() = 0;
    virtual void UpdateGamma(unsigned short) = 0;
    virtual void MatrixMode(int) = 0;
    virtual void MatrixSetIdentity() = 0;
    virtual void MatrixTranslate(float, float, float) = 0;
    virtual void MatrixRotate(float, float, float, float) = 0;
    virtual void MatrixScale(float, float, float) = 0;
    virtual void MatrixPerspective(float, float, float, float) = 0;
    virtual void MatrixOrthogonal(float, float, float, float, float, float) = 0;
    virtual void MatrixPop() = 0;
    virtual void MatrixPush() = 0;
    virtual float32x4_t MatrixMult(float*) = 0;
    virtual void MatrixGet(int) = 0;
    virtual void Set_matrixDirty() = 0;
    virtual void Initialise() = 0;
    virtual void InitialiseContext() = 0;
    virtual void StartFrame() = 0;
    virtual void vtbl_7101130608_func_17() = 0;
    virtual void vtbl_7101130608_func_18() = 0;
    virtual void vtbl_7101130608_func_19() = 0;
    virtual void Present() = 0;
    virtual void Clear(int) = 0;
    virtual void SetClearColour(const float*) = 0;
    virtual void vtbl_7101130608_func_23() = 0;
    virtual bool IsWidescreen() = 0;
    virtual bool IsHiDef() = 0;
    virtual void vtbl_7101130608_func_26() = 0;
    virtual void CaptureThumbnail(ImageFileBuffer*) = 0;
    virtual void CaptureScreen(ImageFileBuffer*, _XSOCIAL_PREVIEWIMAGE*) = 0;
    virtual void BeginConditionalSurvey(int) = 0;
    virtual void EndConditionalSurvey() = 0;
    virtual void BeginConditionalRendering(int) = 0;
    virtual void EndConditionalRendering() = 0;
    virtual void BeginOrderIndependentAlpha() = 0;
    virtual void EndOrderIndependentAlpha() = 0;
    virtual void vtbl_7101130608_func_35() = 0;
    virtual void vtbl_7101130608_func_36() = 0;
    virtual void DrawVertices(C4JRender::ePrimitiveType, int, void*, C4JRender::eVertexType,
                              C4JRender::ePixelShaderType, unsigned char*)
        = 0;
    virtual void CBuffLockStaticCreations() = 0;
    virtual void CBuffCreate(int) = 0;
    virtual void CBuffDelete(int, int) = 0;
    virtual void CBuffStart(int, bool) = 0;
    virtual void CBuffClear(int) = 0;
    virtual void CBuffSize(int) = 0;
    virtual void CBuffEnd() = 0;
    virtual void CBuffCall(int, bool, unsigned char) = 0;
    virtual void CBuffTick() = 0;
    virtual void CBuffDeferredModeStart() = 0;
    virtual void CBuffDeferredModeEnd() = 0;
    virtual int GetMaxTextures() = 0;
    virtual int TextureCreate() = 0;
    virtual void TextureFree(int) = 0;
    virtual void TextureBind(int) = 0;
    virtual void TextureBind(int, int) = 0;
    virtual void TextureBindMask(int) = 0;
    virtual void TextureBindVertex(int) = 0;
    virtual void TextureSetTextureLevels(int) = 0;
    virtual void TextureGetTextureLevels() = 0;
    virtual void TextureData(int, int, void*, int, C4JRender::eTextureFormat) = 0;
    virtual void TextureDataUpdate(int, int, int, int, void*, int) = 0;
    virtual void TextureSetParam(int, int) = 0;
    virtual void TextureDynamicUpdateStart() = 0;
    virtual void TextureDynamicUpdateEnd() = 0;
    virtual void LoadTextureData(const char*, D3DXIMAGE_INFO*, int**) = 0;
    virtual void LoadTextureData(unsigned char*, unsigned int, D3DXIMAGE_INFO*, int**) = 0;
    virtual void vtbl_7101130608_func_65() = 0;
    virtual void vtbl_7101130608_func_66() = 0;
    virtual void vtbl_7101130608_func_67() = 0;
    virtual void StateSetColour(float, float, float, float) = 0;
    virtual void StateSetColourAdd(float, float, float, float) = 0;
    virtual void StateSetTexColour(int, float, float, float, float) = 0;
    virtual void StateSetDepthMask(bool) = 0;
    virtual void StateSetBlendEnable(bool) = 0;
    virtual void StateSetBlendFunc(int, int) = 0;
    virtual void StateSetBlendFactor(unsigned int) = 0;
    virtual void StateSetAlphaFunc(int, float) = 0;
    virtual void StateSetDepthFunc(int) = 0;
    virtual void StateSetFaceCull(bool) = 0;
    virtual void StateSetFaceCullCW(bool) = 0;
    virtual void StateSetLineWidth(float) = 0;
    virtual void StateSetWriteEnable(bool, bool, bool, bool) = 0;
    virtual void StateSetDepthTestEnable(bool) = 0;
    virtual void StateSetAlphaTestEnable(bool) = 0;
    virtual void StateSetDepthSlopeAndBias(float, float) = 0;
    virtual void StateSetFogEnable(bool) = 0;
    virtual void StateSetFogMode(int) = 0;
    virtual void StateSetFogNearDistance(float) = 0;
    virtual void StateSetFogFarDistance(float) = 0;
    virtual void StateSetFogDensity(float) = 0;
    virtual void StateSetFogColour(float, float, float) = 0;
    virtual void StateSetLightingEnable(bool) = 0;
    virtual void StateSetVertexTextureUV(float, float) = 0;
    virtual void StateSetTextureScaleUI(float, float, float, float) = 0;
    virtual void StateSetScalingGridUI(float, float, float, float, float, float, float, float, float, float)
        = 0;
    virtual void StateSetLightColour(int, float, float, float) = 0;
    virtual void StateSetLightAmbientColour(float, float, float) = 0;
    virtual void StateSetLightDirection(int, float, float, float) = 0;
    virtual void StateSetLightEnable(int, bool) = 0;
    virtual void StateSetViewport(C4JRender::eViewportType) = 0;
    virtual void StateGetScissorRect(unsigned int&, unsigned int&, unsigned int&, unsigned int&) = 0;
    virtual void StateSetScissorRect(unsigned int, unsigned int, unsigned int, unsigned int) = 0;
    virtual void StateSetEnableViewportClipPlanes(bool) = 0;
    virtual void StateSetTexGenCol(int, float, float, float, float, bool) = 0;
    virtual void StateSetStencil(int, unsigned char, unsigned char, unsigned char) = 0;
    virtual void StateSetForceLOD(int) = 0;
    virtual void StateSetLerpColour(float, float, float, float) = 0;
    virtual void SetLayeredColour(int, float, float, float) = 0;
    virtual void SetLayeredParam(int, int, float, float) = 0;
    virtual void SetLayeredTextureSize(int, int) = 0;
    virtual void StateSetBoneMatrixData(int) = 0;
    virtual void StateSetBoneMatrixNull(int) = 0;
    virtual void GetNumCommandBufferVertsDrawnLastFrame() = 0;
    virtual void GetNumVertsInCommandBuffer(int) = 0;
    virtual void BeginEvent(const wchar_t*) = 0;
    virtual void EndEvent() = 0;
};
