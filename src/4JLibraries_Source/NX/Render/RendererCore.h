#pragma once

#include "NX/Render/C4JRender.h"
#include "nn/os/os_MutexTypes.h"
#include "nn/vi.h"
#include "nvn/nvn.h"
#include <arm_neon.h>
#include <cstddef>
#include <cstdint>
#include <unordered_map>

class _XSOCIAL_PREVIEWIMAGE;
class ImageFileBuffer;
class D3DXIMAGE_INFO;
class class_71007B7E78;

typedef float mat4x4[4][4];  // this doesn't seem to exist on 4J base, but I think code will be a lot cleaner
// if we use it

struct MatrixStruct {
    float32x4_t m__[4];
};

class SomeData {  // this is probably class but who knows...
public:
    SomeData();

    void* m_data[29];
};

class Renderer : public C4JRender {
public:
    class Context {
    public:
        Context(Renderer*, bool);

        char m_filler[0x1F30];
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
    NVNmemoryPool* getNVNMemoryPoolByIndex(unsigned int index) { return &this->m_nvNmemoryPool[index]; }
    void SetupMemoryPools();  // guessed name
    void InitialiseContext(bool);
    void LoadShaders();
    void SetupShaders();
    void Initialise(bool);

    virtual void Tick();
    virtual void UpdateGamma(unsigned short gamma);
    // see OpenGL for more info (modes starts from 0 and ends in 2, they are in the same order as they are in
    // OpenGL)
    virtual void MatrixMode(int);
    virtual void MatrixSetIdentity();
    virtual void MatrixTranslate(float, float, float);
    virtual void MatrixRotate(float, float, float, float);
    virtual void MatrixScale(float, float, float);
    virtual void MatrixPerspective(float, float, float, float);
    virtual void MatrixOrthogonal(float, float, float, float, float, float);
    virtual void MatrixPop();
    virtual void MatrixPush();
    virtual float32x4_t MatrixMult(float* matrix);
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
    virtual int GetMaxTextures();
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

    static float32x4_t MultWithStack(
        MatrixStruct);  // MatrixStruct is made up by me, WiiU does seem to have everything
                        // completly different but they had to use float32x4_t so I think struct
                        // like this may have been used here, also it may have been literally the same as wiiU
                        // but just using float32x4_t (some arm optimized float crap)

    char m_gap8[16];
    NVNdevice* m_nvNdevice;
    nn::vi::Display* m_display;
    nn::vi::Layer* m_layer;
    void* m_window;
    NVNqueue m_nvNqueue;
    void* m_queueMemory;
    NVNsync m_nvNsync[3];
    NVNwindow* m_nvNwindow;
    NVNwindowBuilder m_nvNwindowBuilder;
    NVNcommandBuffer m_nvNcommandBuffer;
    size_t m_qword21E8;
    int m_dword21F0;
    char m_gap21F4[4];
    void* m_qword21F8;
    int m_reservedTextureDescriptors;
    int m_reservedSamplerDescriptors;
    int m_hdReservedTextureDescriptors;  // those don't have to be HD, it's just guessing
    int m_hdReservedSamplerDescriptors;
    NVNtexturePool m_nvNtexturePool;
    NVNsamplerPool m_nvNsamplerPool;
    int m_dword2250;
    char m_gap2254[772];
    NVNbuffer m_nvNbuffer;
    NVNbufferAddress m_nvNbufferAddr;
    float* m_bufferMap;
    size_t m_qword2598;
    void* m_qword25A0;
    int m_dword25A8;
    int m_dword25Ac;
    NVNbuffer m_nvNbuffer2;
    NVNbufferAddress m_nvNbufferAddr2;
    void* m_bufferMap2;
    size_t m_qword25F0;
    void* m_qword25F8;
    int m_dword2600;
    int m_dword2604;
    NVNbuffer m_nvNbuffer3;
    NVNbufferAddress m_nvNbufferAddr3;
    void* m_bufferMap3;
    size_t m_qword2648;
    void* m_qword2650;
    int m_dword2658;
    int m_dword265C;
    NVNtextureBuilder m_nvNtextureBuilder;
    void* m_qword26E0;
    void* m_qword26E8;
    void* m_qword26F0;
    void* m_qword26F8;
    void* m_qword2700;
    char m_gap2708[32];
    size_t m_rgbA8TextureStorageSize;  // it seems that nvn names ptrs storage
    size_t m_rgbA8TextureStorageAlignment;
    size_t m_deptH24StenciL8TextureStorageSize;
    size_t m_deptH24StenciL8HdTextureStorageSize;
    size_t m_deptH24StenciL8TextureStorageAlignment;
    size_t m_deptH24StenciL8HdTextureStorageAlignment;
    void* m_qword2758;
    void* m_qword2760;
    size_t m_rgbA16FTextureStorageSize;
    size_t m_rgbA16FHdTextureStorageSize;
    size_t m_rgbA16FTextureStorageAlignment;
    size_t m_rgbA16FHdTextureStorageAlignment;
    char m_gap2788[16];
    void* m_qword2798;
    void* m_qword27A0;
    void* m_qword27A8;
    void* m_qword27B0;
    void* m_qword27B8;
    void* m_qword27C0;
    size_t m_textureStorageSizes[6];
    size_t m_textureStorageAlignments[6];
    size_t m_idkReally[6];
    char m_gap2858[48];
    NVNbuffer
        m_buffers[2];  // it could be that one is FHD one is HD, but until ik that let's keep them in array
    int m_dword28E8;
    int m_dword28Ec;
    NVNprogram* m_shaders1;
    NVNprogram* m_shaders2;
    NVNprogram* m_shaders3;
    NVNprogram* m_shaders4;
    NVNprogram* m_shaders5;
    NVNprogram* m_shaders6;
    NVNprogram* m_shaders7;
    NVNprogram* m_shaders8;
    NVNprogram* m_shaders9;
    NVNprogram* m_shaders10;
    NVNprogram* m_shaders11;
    NVNprogram* m_shaders12;
    NVNprogram* m_shaders13;
    NVNprogram* m_shaders14;
    char m_gap2960[48];
    int m_textureId1;
    unsigned short m_gammaIntensity;
    int m_dword2998;
    char m_byte299C;
    nn::os::MutexType m_mutex1;
    int m_dword29C0;
    int m_dword29C4;
    char m_gap29C8[4];
    char m_byte29Cc;
    SomeData m_someData[1024];
    int m_textureSizesFirst[2];
    int m_textureSizesSecond[2];
    // int mFHDTexture2DWidth;
    // int mFHDTexture2DHeight;
    // int mHDTexture2DWidth;
    // int mHDTexture2DHeight;
    bool m_bool3C9E0;
    int m_dword3C9E4;
    void* m_somethingTexturePtrs[7];
    int m_elo1;
    int m_elo2;
    std::unordered_map<int, int> m_ap;  // as for now it's impossible to track down complete type
    NVNmemoryPool m_nvNmemoryPool[3];
    void* m_poolMemory;
    void* m_poolMemory2;
    void* m_poolMemory3;
    void* m_idk;
    void* m_idk2;
    void* m_idk3;
    class_71007B7E78* m_class71007B7E781;
    void* m_qword3CD88;
    void* m_qword3CD90;
    void* m_qword3CD98;
    nn::os::MutexType m_mutex2;
    size_t m_qword3CdC0;
    size_t m_qword3CdC8;
    nn::os::MutexType m_mutex3;
    class_71007B7E78* m_class71007B7E782;
    char m_gap3CdF8[8];
    uint16_t m_word3CE00;
    uint16_t m_fill;
    char m_char3CE04;
    char m_gap3CE05[63];
    char m_char3CE44;
    char m_gap3CE45[15];
    char m_char3CE54;
    char m_gap3CE55[15];
    char m_char3CE64;
    char m_gap3CE65[15];
    char m_char3CE74;
    char m_gap3CE75[15];
    char m_char3CE84;
    char m_gap3CE85[15];
    char m_byte3CE94;
    char m_char3CE95;
    char m_gap3CE96[2];
    char m_dupa;
    char m_gap3cE99[108];
    char m_char3CF05;
    char m_gap3CF06[2];
    char m_cipa;
    char m_gap3CF09[12];
    char m_byte3CF15;
    char m_fillaaaa[2];
    bool m_bool3CF18;
    int m_elo;
    int m_elo22;
};
