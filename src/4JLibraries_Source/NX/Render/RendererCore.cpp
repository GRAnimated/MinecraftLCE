#include "NX/Render/RendererCore.h"

#include "NX/Platform.h"
#include "NX/Render/UnknownRendererClasses.h"
#include "nn/diag.h"
#include "nn/os/os_MutexTypes.h"
#include "nn/vi.h"
#include "nv.h"
#include "nvn/nvn.h"
#include "nvn/nvn_FuncPtrBase.h"
#include "nvn/nvn_FuncPtrImpl.h"
#include "nvn/nvn_FuncPtrInline.h"
#include <arm_neon.h>
#include <array>
#include <cstdlib>
#include <cstring>

__thread Renderer::Context* sContext;
unsigned int textureWidths[6] = {1920, 1280, 512, 256, 128, 64};
unsigned int textureHeights[6] = {1080, 720, 512, 256, 128, 64};
nn::os::MutexType someRendererMutex;

Renderer::Context::Context(Renderer*, bool a2) {
    this->filler[0] = a2;
}

Renderer::Renderer() : C4JRender() {
    this->qword3CD88 = nullptr;
    this->qword3CD90 = nullptr;
    this->qword3CD98 = nullptr;

    Renderer::sInstance = this;
}

// NON_MATCHING: inline the tls offset getter, could be some compiler flag
void Renderer::InitialiseContext(bool idk) {
    sContext = new Renderer::Context(this, idk);
}

void Renderer::SetupMemoryPools() {
    NVNmemoryPoolBuilder builder;
    nvnMemoryPoolBuilderSetDefaults(&builder);
    nvnMemoryPoolBuilderSetDevice(&builder, this->mNVNdevice);

    nvnMemoryPoolBuilderSetFlags(&builder,
                                 NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED | NVN_MEMORY_POOL_FLAGS_GPU_CACHED);
    this->mPoolMemory = memalign(0x1000, 0x20000000);
    nvnMemoryPoolBuilderSetStorage(&builder, this->mPoolMemory, 0x20000000);
    nvnMemoryPoolInitialize(&this->mNVNmemoryPool[0], &builder);
    this->mIdk = 0;  // have no idea what are those

    nvnMemoryPoolBuilderSetFlags(&builder, NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS
                                               | NVN_MEMORY_POOL_FLAGS_GPU_CACHED
                                               | NVN_MEMORY_POOL_FLAGS_COMPRESSIBLE);
    this->mPoolMemory2 = memalign(0x1000, 0x4000000);
    nvnMemoryPoolBuilderSetStorage(&builder, this->mPoolMemory2, 0x4000000);
    nvnMemoryPoolInitialize(&this->mNVNmemoryPool[1], &builder);
    this->mIdk2 = 0;

    nvnMemoryPoolBuilderSetFlags(&builder, NVN_MEMORY_POOL_FLAGS_SHADER_CODE
                                               | NVN_MEMORY_POOL_FLAGS_GPU_CACHED
                                               | NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED);
    this->mPoolMemory3 = memalign(0x1000, 0x100000);
    nvnMemoryPoolBuilderSetStorage(&builder, this->mPoolMemory3, 0x100000);
    nvnMemoryPoolInitialize(&this->mNVNmemoryPool[2], &builder);
    this->mIdk3 = 0;
}

void Renderer::Initialise() {
    this->Initialise(0);
}

// thanks to Fuzzy2319 for spotting last 2 fixes
void Renderer::Initialise(bool) {
    nv::SetGraphicsAllocator(gfx_aligned_alloc, gfx_free, gfx_realloc, nullptr);
    nv::InitializeGraphics(malloc(0x800000), 0x800000);
    nv::SetGraphicsDevtoolsAllocator(gfx_aligned_alloc, gfx_free, gfx_realloc, nullptr);
    nn::vi::Initialize();

    nn::Result result = nn::vi::OpenDefaultDisplay(&this->mDisplay);
    if (!result.IsSuccess())
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    this->dword28E8 = 1;
    this->dword28EC = 1;
    this->mTextureSizesFirst[0] = 1920;
    this->mTextureSizesFirst[1] = 1280;
    this->mTextureSizesSecond[0] = 1080;
    this->mTextureSizesSecond[1] = 720;

    result = nn::vi::CreateLayer(&this->mLayer, this->mDisplay);
    if (!result.IsSuccess())
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    result = nn::vi::SetLayerScalingMode(this->mLayer, nn::vi::FitLayer);
    if (!result.IsSuccess())
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    result = nn::vi::GetNativeWindow(&this->mWindow, this->mLayer);
    pfnc_nvnDeviceGetProcAddress
        = (PFNNVNDEVICEGETPROCADDRESSPROC)nvnBootstrapLoader("nvnDeviceGetProcAddress");
    nvnLoadCProcs(nullptr, pfnc_nvnDeviceGetProcAddress);

    NVNdeviceBuilder deviceBuilder;
    nvnDeviceBuilderSetDefaults(&deviceBuilder);
    nvnDeviceBuilderSetFlags(&deviceBuilder, 0);  // same as here

    this->mNVNdevice = (NVNdevice*)operator new(0x3000);  // hmmm
    nvnDeviceInitialize(this->mNVNdevice, &deviceBuilder);
    nvnLoadCProcs(this->mNVNdevice, pfnc_nvnDeviceGetProcAddress);

    int API_MAJOR_VERSION, API_MINOR_VERSION;
    nvnDeviceGetInteger(nullptr, NVN_DEVICE_INFO_API_MAJOR_VERSION, &API_MAJOR_VERSION);
    nvnDeviceGetInteger(nullptr, NVN_DEVICE_INFO_API_MINOR_VERSION, &API_MINOR_VERSION);

    nvnDeviceSetWindowOriginMode(this->mNVNdevice,
                                 NVN_WINDOW_ORIGIN_MODE_UPPER_LEFT);  // this is not how call looks iirc,
                                                                      // after tools/check I will confirm

    nvnSyncInitialize(&this->mNVNsync[0], this->mNVNdevice);
    nvnSyncInitialize(&this->mNVNsync[1], this->mNVNdevice);
    nvnSyncInitialize(&this->mNVNsync[2], this->mNVNdevice);

    SetupMemoryPools();

    NVNqueueBuilder queueBuilder1;
    nvnQueueBuilderSetDevice(&queueBuilder1, this->mNVNdevice);
    nvnQueueBuilderSetDefaults(&queueBuilder1);
    nvnQueueBuilderSetComputeMemorySize(&queueBuilder1, 0);

    int QUEUE_COMMAND_MEMORY_MIN_SIZE = 0;
    nvnDeviceGetInteger(this->mNVNdevice, NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_MIN_SIZE,
                        &QUEUE_COMMAND_MEMORY_MIN_SIZE);
    nvnQueueBuilderSetCommandMemorySize(&queueBuilder1, QUEUE_COMMAND_MEMORY_MIN_SIZE);
    nvnQueueBuilderSetCommandFlushThreshold(&queueBuilder1, QUEUE_COMMAND_MEMORY_MIN_SIZE);
    size_t queueMemorySize = nvnQueueBuilderGetQueueMemorySize(&queueBuilder1);
    if ((queueMemorySize & 0xFFF) != 0)
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);
    this->mQueueMemory = memalign(0x1000, queueMemorySize);
    nvnQueueBuilderSetQueueMemory(&queueBuilder1, this->mQueueMemory, queueMemorySize);
    if (!nvnQueueInitialize(&this->mNVNqueue, &queueBuilder1))
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    nvnCommandBufferInitialize(&this->mNVNcommandBuffer, this->mNVNdevice);
    this->qword21E8 = this->sub_7100799078(0, 0x400000, 4);
    this->qword21F8 = memalign(8, 0x800);
    this->dword21F0 = 0;

    nvnTextureBuilderSetDevice(&this->mNVNtextureBuilder, this->mNVNdevice);
    nvnTextureBuilderSetDefaults(&this->mNVNtextureBuilder);
    nvnTextureBuilderSetFlags(&this->mNVNtextureBuilder,
                              NVN_TEXTURE_FLAGS_COMPRESSIBLE | NVN_TEXTURE_FLAGS_DISPLAY);
    nvnTextureBuilderSetSize2D(&this->mNVNtextureBuilder, this->mTextureSizesFirst[0],
                               this->mTextureSizesSecond[0]);
    nvnTextureBuilderSetTarget(&this->mNVNtextureBuilder, NVN_TEXTURE_TARGET_2D);
    nvnTextureBuilderSetFormat(&this->mNVNtextureBuilder, NVN_FORMAT_RGBA8);
    this->mRGBA8__TextureStorageSize = nvnTextureBuilderGetStorageSize(&this->mNVNtextureBuilder);
    this->mRGBA8__TextureStorageAlignment = nvnTextureBuilderGetStorageAlignment(&this->mNVNtextureBuilder);

    nvnTextureBuilderSetDefaults(&this->mNVNtextureBuilder);
    nvnTextureBuilderSetFlags(&this->mNVNtextureBuilder, NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    nvnTextureBuilderSetTarget(&this->mNVNtextureBuilder, NVN_TEXTURE_TARGET_2D);
    nvnTextureBuilderSetFormat(&this->mNVNtextureBuilder, NVN_FORMAT_DEPTH24_STENCIL8);
    nvnTextureBuilderSetSize2D(&this->mNVNtextureBuilder, this->mTextureSizesFirst[0],
                               this->mTextureSizesSecond[0]);
    this->mDEPTH24_STENCIL8__TextureStorageSize = nvnTextureBuilderGetStorageSize(&this->mNVNtextureBuilder);
    this->mDEPTH24_STENCIL8__TextureStorageAlignment
        = nvnTextureBuilderGetStorageAlignment(&this->mNVNtextureBuilder);

    nvnTextureBuilderSetSize2D(&this->mNVNtextureBuilder, this->mTextureSizesFirst[1],
                               this->mTextureSizesSecond[1]);
    this->mDEPTH24_STENCIL8__HDTextureStorageSize
        = nvnTextureBuilderGetStorageSize(&this->mNVNtextureBuilder);
    this->mDEPTH24_STENCIL8__HDTextureStorageAlignment = this->sub_7100799078(
        1, 3 * this->mRGBA8__TextureStorageSize + this->mDEPTH24_STENCIL8__TextureStorageSize,
        this->mRGBA8__TextureStorageAlignment);

    nvnTextureBuilderSetFormat(&this->mNVNtextureBuilder, NVN_FORMAT_RGBA16F);
    nvnTextureBuilderSetSize2D(&this->mNVNtextureBuilder, this->mTextureSizesFirst[0],
                               this->mTextureSizesSecond[0]);
    this->mRGBA16F__TextureStorageSize = nvnTextureBuilderGetStorageSize(&this->mNVNtextureBuilder);
    this->mRGBA16F__TextureStorageAlignment = nvnTextureBuilderGetStorageAlignment(&this->mNVNtextureBuilder);

    nvnTextureBuilderSetSize2D(&this->mNVNtextureBuilder, this->mTextureSizesFirst[1],
                               this->mTextureSizesSecond[1]);
    this->mRGBA16F__HDTextureStorageSize = nvnTextureBuilderGetStorageSize(&this->mNVNtextureBuilder);
    this->mRGBA16F__HDTextureStorageAlignment = this->sub_7100799078(1, this->mRGBA16F__TextureStorageSize,
                                                                     this->mRGBA16F__TextureStorageAlignment);

    nvnTextureBuilderSetFormat(&this->mNVNtextureBuilder, NVN_FORMAT_RGBA8);

    for (int i = 0; i < 6; i++) {
        nvnTextureBuilderSetSize2D(&this->mNVNtextureBuilder, textureWidths[i], textureHeights[i]);
        this->mTextureStorageSizes[i] = nvnTextureBuilderGetStorageSize(&this->mNVNtextureBuilder);
        this->mTextureStorageAlignments[i] = nvnTextureBuilderGetStorageAlignment(&this->mNVNtextureBuilder);

        if (i == 1) {
            this->mIdkReally[i] = this->mIdkReally[0];
            continue;
        }

        this->mIdkReally[i]
            = this->sub_7100799078(1, this->mTextureStorageSizes[i], this->mTextureStorageAlignments[i]);
    }

    NVNbufferBuilder bufferBuilder1;
    nvnBufferBuilderSetDevice(&bufferBuilder1, this->mNVNdevice);
    nvnBufferBuilderSetDefaults(&bufferBuilder1);

    size_t offset = this->sub_7100799078(0, 0x4000, 1);
    nvnBufferBuilderSetStorage(&bufferBuilder1, this->getNVNMemoryPoolByIndex(0), offset, 0x4000);
    nvnBufferInitialize(&this->mBuffers[0], &bufferBuilder1);

    offset = this->sub_7100799078(0, (4 * textureWidths[0] * textureHeights[0]), 1);
    nvnBufferBuilderSetStorage(&bufferBuilder1, this->getNVNMemoryPoolByIndex(0), offset,
                               4 * textureWidths[0] * textureHeights[0]);
    nvnBufferInitialize(&this->mBuffers[1], &bufferBuilder1);

    nvnDeviceGetInteger(this->mNVNdevice, NVN_DEVICE_INFO_RESERVED_TEXTURE_DESCRIPTORS,
                        &this->RESERVED_TEXTURE_DESCRIPTORS);
    nvnDeviceGetInteger(this->mNVNdevice, NVN_DEVICE_INFO_RESERVED_SAMPLER_DESCRIPTORS,
                        &this->RESERVED_SAMPLER_DESCRIPTORS);

    int HD_TYPE = this->RESERVED_TEXTURE_DESCRIPTORS + 1035;  // why????
    int HD_TYPE_1 = this->RESERVED_SAMPLER_DESCRIPTORS + 64;

    this->dword2250 = 0;
    this->HD_RESERVED_TEXTURE_DESCRIPTORS = HD_TYPE;
    this->HD_RESERVED_SAMPLER_DESCRIPTORS = HD_TYPE_1;

    int DESCRIPTOR_SIZE;
    nvnDeviceGetInteger(this->mNVNdevice, NVN_DEVICE_INFO_TEXTURE_DESCRIPTOR_SIZE, &DESCRIPTOR_SIZE);
    offset
        = this->sub_7100799078(0, DESCRIPTOR_SIZE * this->HD_RESERVED_TEXTURE_DESCRIPTORS, DESCRIPTOR_SIZE);
    nvnTexturePoolInitialize(&this->mNVNtexturePool, getNVNMemoryPoolByIndex(0), offset,
                             this->HD_RESERVED_TEXTURE_DESCRIPTORS);

    nvnDeviceGetInteger(this->mNVNdevice, NVN_DEVICE_INFO_SAMPLER_DESCRIPTOR_SIZE, &DESCRIPTOR_SIZE);
    offset
        = this->sub_7100799078(0, DESCRIPTOR_SIZE * this->HD_RESERVED_SAMPLER_DESCRIPTORS, DESCRIPTOR_SIZE);
    nvnSamplerPoolInitialize(&this->mNVNsamplerPool, getNVNMemoryPoolByIndex(0), offset,
                             this->HD_RESERVED_SAMPLER_DESCRIPTORS);

    this->qword26E0 = 0;
    this->qword26E8 = 0;
    this->qword26F0 = 0;
    this->qword26F8 = 0;
    this->qword2700 = 0;
    this->mNVNwindow = nullptr;
    this->qword2758 = 0;
    this->qword2760 = 0;
    this->qword2798 = 0;
    this->qword27A0 = 0;
    this->qword27A8 = 0;
    this->qword27B0 = 0;
    this->qword27B8 = 0;
    this->qword27C0 = 0;

    nvnWindowBuilderSetDefaults(&this->mNVNwindowBuilder);
    nvnWindowBuilderSetDevice(&this->mNVNwindowBuilder, this->mNVNdevice);
    nvnWindowBuilderSetNativeWindow(&this->mNVNwindowBuilder, this->mWindow);

    this->sub_7100796C74();

    this->qword2598 = this->sub_7100799078(0, 0x4000000, 0x100);

    NVNbufferBuilder bufferBuilder;
    nvnBufferBuilderSetDefaults(&bufferBuilder);
    nvnBufferBuilderSetDevice(&bufferBuilder, this->mNVNdevice);
    nvnBufferBuilderSetStorage(&bufferBuilder, getNVNMemoryPoolByIndex(0), this->qword2598, 0x4000000);
    nvnBufferInitialize(&this->mNVNbuffer, &bufferBuilder);

    this->qword25A0 = (void*)256;
    this->dword25A8 = 0;
    this->mBufferMap = (float*)nvnBufferMap(&this->mNVNbuffer);
    this->mNVNbufferAddr = nvnBufferGetAddress(&this->mNVNbuffer);

    mat4x4& matrix1 = *reinterpret_cast<mat4x4*>(this->mBufferMap);
    memset(matrix1, 0, sizeof(matrix1));
    matrix1[0][0] = 1.0f;
    matrix1[1][1] = 1.0f;
    matrix1[2][2] = 1.0f;
    matrix1[3][3] = 1.0f;

    mat4x4& matrix2 = *reinterpret_cast<mat4x4*>(this->mBufferMap + 0x800000);
    memset(matrix2, 0, sizeof(matrix2));
    matrix2[0][0] = 1.0f;
    matrix2[1][1] = 1.0f;
    matrix2[2][2] = 1.0f;
    matrix2[3][3] = 1.0f;

    this->qword25F0 = this->sub_7100799078(0, 0xA00000, 4);
    nvnBufferBuilderSetStorage(&bufferBuilder, getNVNMemoryPoolByIndex(0), this->qword25F0, 0xA00000);
    nvnBufferInitialize(&this->mNVNbuffer2, &bufferBuilder);
    this->qword25F8 = 0LL;
    this->dword2600 = 0;
    this->mBufferMap2 = nvnBufferMap(&this->mNVNbuffer2);
    this->mNVNbufferAddr2 = nvnBufferGetAddress(&this->mNVNbuffer2);

    this->qword2648 = this->sub_7100799078(0, 0x800000, 16);
    nvnBufferBuilderSetStorage(&bufferBuilder, getNVNMemoryPoolByIndex(0), this->qword2648, 0x800000);
    nvnBufferInitialize(&this->mNVNbuffer3, &bufferBuilder);
    this->qword2650 = 0LL;
    this->dword2658 = 0;
    this->mBufferMap3 = (void*)nvnBufferMap(&this->mNVNbuffer3);
    this->mNVNbufferAddr3 = nvnBufferGetAddress(&this->mNVNbuffer3);

    this->InitialiseContext(true);

    this->mSomethingTexturePtrs[0] = (void*)operator new[](0x1000000uLL);
    this->mSomethingTexturePtrs[1] = (void*)operator new[](0x1F400uLL);
    this->mSomethingTexturePtrs[2] = (void*)operator new[](0xFA000uLL);
    this->mSomethingTexturePtrs[3] = (void*)operator new[](0xFA00uLL);
    this->mSomethingTexturePtrs[4] = (void*)operator new[](0x3E80uLL);
    this->mSomethingTexturePtrs[5] = (void*)operator new[](0xFA00uLL);
    this->mSomethingTexturePtrs[6] = (void*)operator new[](0x3E80uLL);
    memset(this->mSomethingTexturePtrs[0], 255, 0x1000000uLL);
    memset(this->mSomethingTexturePtrs[1], 0, 0x1F400uLL);
    memset(this->mSomethingTexturePtrs[3], 0, 0xFA00uLL);
    memset(this->mSomethingTexturePtrs[5], 0, 0xFA00uLL);
    memset(this->mSomethingTexturePtrs[4], 0, 0x3E80uLL);
    memset(this->mSomethingTexturePtrs[6], 0, 0x3E80uLL);
    // COULD BE THAT THIS MISSMATCHES, ORDER OF MEMSETS

    this->elo1 = 0;
    this->elo2 = 0;
    this->word3CE00 = 0;

    this->qword3CDC0 = psInstance->sub_7100799078(0, 0x8000000, 4);
    this->class_71007B7E78_1 = new class_71007B7E78(this->qword3CDC0, 0x8000000);

    this->qword3CDC8 = psInstance->sub_7100799078(0, 0x8000000, 1024);
    this->class_71007B7E78_2 = new class_71007B7E78(this->qword3CDC8, 0x8000000);

    this->LoadShaders();
    this->SetupShaders();

    float colour[4] = {};
    this->SetClearColour(colour);

    memset(this->someData, 0, sizeof(this->someData));

    nn::os::InitializeMutex(&this->mMutex1, 1, 0);
    nn::os::InitializeMutex(&someRendererMutex, 1, 0);
    nn::os::InitializeMutex(&this->mMutex2, 1, 0);
    nn::os::InitializeMutex(&this->mMutex3, 1, 0);

    this->mTextureID_1 = this->TextureCreate();  // could be that this is done as arg for below
    this->TextureBind(this->mTextureID_1);

    char someString[1024];
    memset(someString, 255, sizeof(someString));
    this->TextureData(16, 16, someString, 0, (C4JRender::eTextureFormat)0);

    this->mGammaIntensity = 0x2AAA;
    this->dword2998 = 0;
    this->byte299C = 0;

    this->bool3C9E0 = 1;
    this->dword3C9E4 = 0;

    this->StateSetVertexTextureUV(0.0f, 0.0f);
    this->StateSetTextureScaleUI(1.0f, 1.0f, 0.0f, 0.0f);
    this->StateSetLerpColour(0.0f, 0.0f, 0.0f, 0.0f);
    this->StateSetFogColour(0.0f, 0.0f, 0.0f);
    this->StateSetFogEnable(false);

    int src[4] = {0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000};
    memcpy(&this->char3CE04, src, 0x10);
    memset(&this->char3CE44, 0, 0x10);
    memcpy(&this->char3CE54, src, 0x10);
    memcpy(&this->char3CE64, src, 0x10);
    memcpy(&this->char3CE74, src, 0x10);
    memcpy(&this->char3CE84, src, 0x10);
    this->byte3CE94 = 1;
    memset(&this->dupa, 0, 0x70);
    memset(&this->cipa, 0, 0x10);

    this->bool3CF18 = 1;

    this->StateSetVertexTextureUV(0.0f, 0.0f);
    this->dword29C0 = -1;
    this->dword29C4 = -1;
    this->byte29CC = 0;
    this->elo = 0;
    this->elo22 = 0;

    nvnWindowSetCrop(this->mNVNwindow, 0, 0, mTextureSizesFirst[this->dword28E8],
                     mTextureSizesSecond[this->dword28E8]);
}

void Renderer::InitialiseContext() {
    this->InitialiseContext(false);
}

void Renderer::vtbl_7101130608_func_19() {}
void Renderer::CaptureScreen(ImageFileBuffer* image_file_buffer,
                             _XSOCIAL_PREVIEWIMAGE* xsocial_previewimage) {}
void Renderer::BeginConditionalSurvey(int i) {}
void Renderer::EndConditionalSurvey() {}
void Renderer::BeginConditionalRendering(int i) {}
void Renderer::EndConditionalRendering() {}
void Renderer::TextureDynamicUpdateStart() {}
void Renderer::TextureDynamicUpdateEnd() {}
void Renderer::vtbl_7101130608_func_67() {}
void Renderer::StateSetLineWidth(float x) {}
void Renderer::StateSetEnableViewportClipPlanes(bool cond) {}
void Renderer::BeginEvent(const wchar_t* string) {}
void Renderer::EndEvent() {}

bool Renderer::IsWidescreen() {
    return true;
}

bool Renderer::IsHiDef() {
    return true;
}

int Renderer::GetMaxTextures() {
    return 1024;
}

void Renderer::Tick() {
    this->CBuffTick();
}

// this would mean that they've changed function MulWithStack
float32x4_t Renderer::MatrixMult(float* matrix) {
    return this->MultWithStack(*reinterpret_cast<MatrixStruct*>(matrix));
}

void Renderer::UpdateGamma(unsigned short gamma) {
    this->mGammaIntensity = gamma;
}
