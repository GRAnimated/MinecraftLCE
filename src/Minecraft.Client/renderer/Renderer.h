#pragma once

#include "Minecraft.Client/renderer/C4JRender.h"
#include <arm_neon.h>

class _XSOCIAL_PREVIEWIMAGE;
class ImageFileBuffer;
class D3DXIMAGE_INFO;

class Renderer : public C4JRender {
public:
    Renderer();

    static Renderer* sInstance;

    virtual void Tick();
    virtual void UpdateGamma(unsigned short gamma);
    virtual void MatrixMode(int);
    virtual void MatrixSetIdentity();
    virtual void MatrixTranslate(float, float, float);
    virtual void MatrixRotate(float, float, float, float);
    virtual void MatrixScale(float, float, float);
    virtual void MatrixPerspective(float, float, float, float);
    virtual void MatrixOrthogonal(float, float, float, float, float, float);
    virtual void MatrixPop();
    virtual void MatrixPush();
    virtual float32x4_t MatrixMult(float *matrix);
    virtual void MatrixGet(int);
    virtual void Set_matrixDirty();
    virtual void Initialise();
    virtual void InitialiseContext();
    virtual void StartFrame();
    virtual void vtbl_7101130608_func_17();
    virtual void vtbl_7101130608_func_18();
    virtual void vtbl_7101130608_func_19();
    virtual void Present();
    virtual void Clear(int);
    virtual void SetClearColour(const float*);
    virtual void vtbl_7101130608_func_23();
    virtual bool IsWidescreen();
    virtual bool IsHiDef();
    virtual void vtbl_7101130608_func_26();
    virtual void CaptureThumbnail(ImageFileBuffer*);
    virtual void CaptureScreen(ImageFileBuffer*, _XSOCIAL_PREVIEWIMAGE*);
    virtual void BeginConditionalSurvey(int);
    virtual void EndConditionalSurvey();
    virtual void BeginConditionalRendering(int);
    virtual void EndConditionalRendering();
    virtual void BeginOrderIndependentAlpha();
    virtual void EndOrderIndependentAlpha();
    virtual void vtbl_7101130608_func_35();
    virtual void vtbl_7101130608_func_36();
    virtual void DrawVertices(C4JRender::ePrimitiveType, int, void*, C4JRender::eVertexType,
                              C4JRender::ePixelShaderType, unsigned char*);
    virtual void CBuffLockStaticCreations();
    virtual void CBuffCreate(int);
    virtual void CBuffDelete(int, int);
    virtual void CBuffStart(int, bool);
    virtual void CBuffClear(int);
    virtual void CBuffSize(int);
    virtual void CBuffEnd();
    virtual void CBuffCall(int, bool, unsigned char);
    virtual void CBuffTick();
    virtual void CBuffDeferredModeStart();
    virtual void CBuffDeferredModeEnd();
    virtual int GetMaxTextures();
    virtual void TextureCreate();
    virtual void TextureFree(int);
    virtual void TextureBind(int);
    virtual void TextureBind(int, int);
    virtual void TextureBindMask(int);
    virtual void TextureBindVertex(int);
    virtual void TextureSetTextureLevels(int);
    virtual void TextureGetTextureLevels();
    virtual void TextureData(int, int, void*, int, C4JRender::eTextureFormat);
    virtual void TextureDataUpdate(int, int, int, int, void*, int);
    virtual void TextureSetParam(int, int);
    virtual void TextureDynamicUpdateStart();
    virtual void TextureDynamicUpdateEnd();
    virtual void LoadTextureData(const char*, D3DXIMAGE_INFO*, int**);
    virtual void LoadTextureData(unsigned char*, unsigned int, D3DXIMAGE_INFO*, int**);
    virtual void vtbl_7101130608_func_65();
    virtual void vtbl_7101130608_func_66();
    virtual void vtbl_7101130608_func_67();
    virtual void StateSetColour(float, float, float, float);
    virtual void StateSetColourAdd(float, float, float, float);
    virtual void StateSetTexColour(int, float, float, float, float);
    virtual void StateSetDepthMask(bool);
    virtual void StateSetBlendEnable(bool);
    virtual void StateSetBlendFunc(int, int);
    virtual void StateSetBlendFactor(unsigned int);
    virtual void StateSetAlphaFunc(int, float);
    virtual void StateSetDepthFunc(int);
    virtual void StateSetFaceCull(bool);
    virtual void StateSetFaceCullCW(bool);
    virtual void StateSetLineWidth(float);
    virtual void StateSetWriteEnable(bool, bool, bool, bool);
    virtual void StateSetDepthTestEnable(bool);
    virtual void StateSetAlphaTestEnable(bool);
    virtual void StateSetDepthSlopeAndBias(float, float);
    virtual void StateSetFogEnable(bool);
    virtual void StateSetFogMode(int);
    virtual void StateSetFogNearDistance(float);
    virtual void StateSetFogFarDistance(float);
    virtual void StateSetFogDensity(float);
    virtual void StateSetFogColour(float, float, float);
    virtual void StateSetLightingEnable(bool);
    virtual void StateSetVertexTextureUV(float, float);
    virtual void StateSetTextureScaleUI(float, float, float, float);
    virtual void StateSetScalingGridUI(float, float, float, float, float, float, float, float, float, float);
    virtual void StateSetLightColour(int, float, float, float);
    virtual void StateSetLightAmbientColour(float, float, float);
    virtual void StateSetLightDirection(int, float, float, float);
    virtual void StateSetLightEnable(int, bool);
    virtual void StateSetViewport(C4JRender::eViewportType);
    virtual void StateGetScissorRect(unsigned int&, unsigned int&, unsigned int&, unsigned int&);
    virtual void StateSetScissorRect(unsigned int, unsigned int, unsigned int, unsigned int);
    virtual void StateSetEnableViewportClipPlanes(bool);
    virtual void StateSetTexGenCol(int, float, float, float, float, bool);
    virtual void StateSetStencil(int, unsigned char, unsigned char, unsigned char);
    virtual void StateSetForceLOD(int);
    virtual void StateSetLerpColour(float, float, float, float);
    virtual void SetLayeredColour(int, float, float, float);
    virtual void SetLayeredParam(int, int, float, float);
    virtual void SetLayeredTextureSize(int, int);
    virtual void StateSetBoneMatrixData(int);
    virtual void StateSetBoneMatrixNull(int);
    virtual void GetNumCommandBufferVertsDrawnLastFrame();
    virtual void GetNumVertsInCommandBuffer(int);
    virtual void BeginEvent(const wchar_t*);
    virtual void EndEvent();

    float32x4_t MultWithStack(float (*)[4]);

    // SIZE IS WRONG IM PRETTY SURE
    char unk[10636];
    unsigned short mGamma;
    char gap_29D8[237648];
    void* qword_3ca28;
    void* qword_3ca30;
    void* qword_3ca38;
    void* qword_3ca40;
    float dword_3ca48;
    char gap_3CA4C[828];
    void* qword_3cd88;
    void* qword_3cd90;
    void* qword_3cd98;
};
