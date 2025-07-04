#pragma once

#include "nn/os/os_MutexTypes.h"
#include "Minecraft.Client/renderer/C4JRender.h"
#include "nn/vi.h"
#include "nvn/nvn.h"
#include <cstddef>
#include <cstdint>
#include <unordered_map>

class _XSOCIAL_PREVIEWIMAGE;
class ImageFileBuffer;
class D3DXIMAGE_INFO;
class class_71007B7E78;

class SomeData {  // this is probably class but who knows...
public:
    SomeData();

    void* data[29];
};

class Renderer : public C4JRender {
public:
    class Context {
    public:
        Context(Renderer*, bool);

        char filler[0x1F30];
    };

    Renderer();

    static Renderer* sInstance;

private:
    static Renderer* psInstance;

public:
    size_t sub_7100799078(int wchichOne, size_t size,
                          size_t alignment);  // gotta decomp it then figure out name for that, it's some
                                              // offset "generator" shit
    void sub_7100796C74();                    // setup some texture stuff
    NVNmemoryPool* getNVNMemoryPoolByIndex(unsigned int index) { return &this->mNVNmemoryPool[index]; }
    void SetupMemoryPools();  // guessed name
    void InitialiseContext(bool);
    void LoadShaders();
    void SetupShaders();
    void Initialise(bool);

    virtual void Tick();
    virtual void UpdateGamma(unsigned short);
    virtual void MatrixMode(int);
    virtual void MatrixSetIdentity();
    virtual void MatrixTranslate(float, float, float);
    virtual void MatrixRotate(float, float, float, float);
    virtual void MatrixScale(float, float, float);
    virtual void MatrixPerspective(float, float, float, float);
    virtual void MatrixOrthogonal(float, float, float, float, float, float);
    virtual void MatrixPop();
    virtual void MatrixPush();
    virtual void MatrixMult(float*);
    virtual void MatrixGet(int);
    virtual void Set_matrixDirty();
    // unused params were probably used in Xbox One
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
    virtual void GetMaxTextures();
    virtual int TextureCreate();
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

    char gap8[16];
    NVNdevice* mNVNdevice;
    nn::vi::Display* mDisplay;
    nn::vi::Layer* mLayer;
    void* mWindow;
    NVNqueue mNVNqueue;
    void* mQueueMemory;
    NVNsync mNVNsync[3];
    NVNwindow* mNVNwindow;
    NVNwindowBuilder mNVNwindowBuilder;
    NVNcommandBuffer mNVNcommandBuffer;
    size_t qword21E8;
    int dword21F0;
    char gap21F4[4];
    void* qword21F8;
    int RESERVED_TEXTURE_DESCRIPTORS;
    int RESERVED_SAMPLER_DESCRIPTORS;
    int HD_RESERVED_TEXTURE_DESCRIPTORS;  // those don't have to be HD, it's just guessing
    int HD_RESERVED_SAMPLER_DESCRIPTORS;
    NVNtexturePool mNVNtexturePool;
    NVNsamplerPool mNVNsamplerPool;
    int dword2250;
    char gap2254[772];
    NVNbuffer mNVNbuffer;
    NVNbufferAddress mNVNbufferAddr;
    float* mBufferMap;
    size_t qword2598;
    void* qword25A0;
    int dword25A8;
    int dword25AC;
    NVNbuffer mNVNbuffer2;
    NVNbufferAddress mNVNbufferAddr2;
    void* mBufferMap2;
    size_t qword25F0;
    void* qword25F8;
    int dword2600;
    int dword2604;
    NVNbuffer mNVNbuffer3;
    NVNbufferAddress mNVNbufferAddr3;
    void* mBufferMap3;
    size_t qword2648;
    void* qword2650;
    int dword2658;
    int dword265C;
    NVNtextureBuilder mNVNtextureBuilder;
    void* qword26E0;
    void* qword26E8;
    void* qword26F0;
    void* qword26F8;
    void* qword2700;
    char gap2708[32];
    size_t mRGBA8__TextureStorageSize;  // it seems that nvn names ptrs storage
    size_t mRGBA8__TextureStorageAlignment;
    size_t mDEPTH24_STENCIL8__TextureStorageSize;
    size_t mDEPTH24_STENCIL8__HDTextureStorageSize;
    size_t mDEPTH24_STENCIL8__TextureStorageAlignment;
    size_t mDEPTH24_STENCIL8__HDTextureStorageAlignment;
    void* qword2758;
    void* qword2760;
    size_t mRGBA16F__TextureStorageSize;
    size_t mRGBA16F__HDTextureStorageSize;
    size_t mRGBA16F__TextureStorageAlignment;
    size_t mRGBA16F__HDTextureStorageAlignment;
    char gap2788[16];
    void* qword2798;
    void* qword27A0;
    void* qword27A8;
    void* qword27B0;
    void* qword27B8;
    void* qword27C0;
    size_t mTextureStorageSizes[6];
    size_t mTextureStorageAlignments[6];
    size_t mIdkReally[6];
    char gap2858[48];
    NVNbuffer
        mBuffers[2];  // it could be that one is FHD one is HD, but until ik that let's keep them in array
    int dword28E8;
    int dword28EC;
    NVNprogram* shaders1;
    NVNprogram* shaders2;
    NVNprogram* shaders3;
    NVNprogram* shaders4;
    NVNprogram* shaders5;
    NVNprogram* shaders6;
    NVNprogram* shaders7;
    NVNprogram* shaders8;
    NVNprogram* shaders9;
    NVNprogram* shaders10;
    NVNprogram* shaders11;
    NVNprogram* shaders12;
    NVNprogram* shaders13;
    NVNprogram* shaders14;
    char gap2960[48];
    int mTextureID_1;
    uint16_t word2994;
    int dword2998;
    char byte299C;
    nn::os::MutexType mMutex1;
    int dword29C0;
    int dword29C4;
    char gap29C8[4];
    char byte29CC;
    SomeData someData[1024];
    int mTextureSizesFirst[2];
    int mTextureSizesSecond[2];
    // int mFHDTexture2DWidth;
    // int mFHDTexture2DHeight;
    // int mHDTexture2DWidth;
    // int mHDTexture2DHeight;
    bool bool3C9E0;
    int dword3C9E4;
    void* mSomethingTexturePtrs[7];
    int elo1;
    int elo2;
    std::unordered_map<int, int> map;  // as for now it's impossible to track down complete type
    NVNmemoryPool mNVNmemoryPool[3];
    void* mPoolMemory;
    void* mPoolMemory2;
    void* mPoolMemory3;
    void* mIdk;
    void* mIdk2;
    void* mIdk3;
    class_71007B7E78* class_71007B7E78_1;
    void* qword3CD88;
    void* qword3CD90;
    void* qword3CD98;
    nn::os::MutexType mMutex2;
    size_t qword3CDC0;
    size_t qword3CDC8;
    nn::os::MutexType mMutex3;
    class_71007B7E78* class_71007B7E78_2;
    char gap3CDF8[8];
    uint16_t word3CE00;
    uint16_t fill;
    char char3CE04;
    char gap3CE05[63];
    char char3CE44;
    char gap3CE45[15];
    char char3CE54;
    char gap3CE55[15];
    char char3CE64;
    char gap3CE65[15];
    char char3CE74;
    char gap3CE75[15];
    char char3CE84;
    char gap3CE85[15];
    char byte3CE94;
    char char3CE95;
    char gap3CE96[2];
    char dupa;
    char gap3cE99[108];
    char char3CF05;
    char gap3CF06[2];
    char cipa;
    char gap3CF09[12];
    char byte3CF15;
    char fillaaaa[2];
    bool bool3CF18;
    int elo;
    int elo22;
};
