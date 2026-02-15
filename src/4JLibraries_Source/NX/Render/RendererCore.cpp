#include "NX/Render/RendererCore.h"

#include "NX/Platform.h"
#include "NX/Render/UnknownRendererClasses.h"
#include "nn/diag.h"
#include "nn/os/os_MutexTypes.h"
#include "nn/vi.h"
#include "nv.h"
#include "nvn/nvn.h"
#include "nvn/nvn_FuncPtrBase.h"
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
    this->m_filler[0] = a2;
}

Renderer::Renderer() : C4JRender() {
    this->m_qword3CD88 = nullptr;
    this->m_qword3CD90 = nullptr;
    this->m_qword3CD98 = nullptr;

    Renderer::sInstance = this;
}

// NON_MATCHING: inline the tls offset getter, could be some compiler flag
void Renderer::InitialiseContext(bool idk) {
    sContext = new Renderer::Context(this, idk);
}

void Renderer::SetupMemoryPools() {
    NVNmemoryPoolBuilder builder;
    nvnMemoryPoolBuilderSetDefaults(&builder);
    nvnMemoryPoolBuilderSetDevice(&builder, this->m_nvNdevice);

    nvnMemoryPoolBuilderSetFlags(&builder,
                                 NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED | NVN_MEMORY_POOL_FLAGS_GPU_CACHED);
    this->m_poolMemory = memalign(0x1000, 0x20000000);
    nvnMemoryPoolBuilderSetStorage(&builder, this->m_poolMemory, 0x20000000);
    nvnMemoryPoolInitialize(&this->m_nvNmemoryPool[0], &builder);
    this->m_idk = 0;  // have no idea what are those

    nvnMemoryPoolBuilderSetFlags(&builder, NVN_MEMORY_POOL_FLAGS_CPU_NO_ACCESS
                                               | NVN_MEMORY_POOL_FLAGS_GPU_CACHED
                                               | NVN_MEMORY_POOL_FLAGS_COMPRESSIBLE);
    this->m_poolMemory2 = memalign(0x1000, 0x4000000);
    nvnMemoryPoolBuilderSetStorage(&builder, this->m_poolMemory2, 0x4000000);
    nvnMemoryPoolInitialize(&this->m_nvNmemoryPool[1], &builder);
    this->m_idk2 = 0;

    nvnMemoryPoolBuilderSetFlags(&builder, NVN_MEMORY_POOL_FLAGS_SHADER_CODE
                                               | NVN_MEMORY_POOL_FLAGS_GPU_CACHED
                                               | NVN_MEMORY_POOL_FLAGS_CPU_UNCACHED);
    this->m_poolMemory3 = memalign(0x1000, 0x100000);
    nvnMemoryPoolBuilderSetStorage(&builder, this->m_poolMemory3, 0x100000);
    nvnMemoryPoolInitialize(&this->m_nvNmemoryPool[2], &builder);
    this->m_idk3 = 0;
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

    nn::Result result = nn::vi::OpenDefaultDisplay(&this->m_display);
    if (!result.IsSuccess())
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    this->m_dword28E8 = 1;
    this->m_dword28Ec = 1;
    this->m_textureSizesFirst[0] = 1920;
    this->m_textureSizesFirst[1] = 1280;
    this->m_textureSizesSecond[0] = 1080;
    this->m_textureSizesSecond[1] = 720;

    result = nn::vi::CreateLayer(&this->m_layer, this->m_display);
    if (!result.IsSuccess())
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    result = nn::vi::SetLayerScalingMode(this->m_layer, nn::vi::FitLayer);
    if (!result.IsSuccess())
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    result = nn::vi::GetNativeWindow(&this->m_window, this->m_layer);
    pfnc_nvnDeviceGetProcAddress
        = (PFNNVNDEVICEGETPROCADDRESSPROC)nvnBootstrapLoader("nvnDeviceGetProcAddress");
    nvnLoadCProcs(nullptr, pfnc_nvnDeviceGetProcAddress);

    NVNdeviceBuilder deviceBuilder;
    nvnDeviceBuilderSetDefaults(&deviceBuilder);
    nvnDeviceBuilderSetFlags(&deviceBuilder, 0);  // same as here

    this->m_nvNdevice = (NVNdevice*)operator new(0x3000);  // hmmm
    nvnDeviceInitialize(this->m_nvNdevice, &deviceBuilder);
    nvnLoadCProcs(this->m_nvNdevice, pfnc_nvnDeviceGetProcAddress);

    int API_MAJOR_VERSION, API_MINOR_VERSION;
    nvnDeviceGetInteger(nullptr, NVN_DEVICE_INFO_API_MAJOR_VERSION, &API_MAJOR_VERSION);
    nvnDeviceGetInteger(nullptr, NVN_DEVICE_INFO_API_MINOR_VERSION, &API_MINOR_VERSION);

    nvnDeviceSetWindowOriginMode(this->m_nvNdevice,
                                 NVN_WINDOW_ORIGIN_MODE_UPPER_LEFT);  // this is not how call looks iirc,
                                                                      // after tools/check I will confirm

    nvnSyncInitialize(&this->m_nvNsync[0], this->m_nvNdevice);
    nvnSyncInitialize(&this->m_nvNsync[1], this->m_nvNdevice);
    nvnSyncInitialize(&this->m_nvNsync[2], this->m_nvNdevice);

    SetupMemoryPools();

    NVNqueueBuilder queueBuilder1;
    nvnQueueBuilderSetDevice(&queueBuilder1, this->m_nvNdevice);
    nvnQueueBuilderSetDefaults(&queueBuilder1);
    nvnQueueBuilderSetComputeMemorySize(&queueBuilder1, 0);

    int QUEUE_COMMAND_MEMORY_MIN_SIZE = 0;
    nvnDeviceGetInteger(this->m_nvNdevice, NVN_DEVICE_INFO_QUEUE_COMMAND_MEMORY_MIN_SIZE,
                        &QUEUE_COMMAND_MEMORY_MIN_SIZE);
    nvnQueueBuilderSetCommandMemorySize(&queueBuilder1, QUEUE_COMMAND_MEMORY_MIN_SIZE);
    nvnQueueBuilderSetCommandFlushThreshold(&queueBuilder1, QUEUE_COMMAND_MEMORY_MIN_SIZE);
    size_t queueMemorySize = nvnQueueBuilderGetQueueMemorySize(&queueBuilder1);
    if ((queueMemorySize & 0xFFF) != 0)
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);
    this->m_queueMemory = memalign(0x1000, queueMemorySize);
    nvnQueueBuilderSetQueueMemory(&queueBuilder1, this->m_queueMemory, queueMemorySize);
    if (!nvnQueueInitialize(&this->m_nvNqueue, &queueBuilder1))
        nn::diag::detail::OnAssertionFailure((nn::diag::AssertionType)2, "", "", "", 0);

    nvnCommandBufferInitialize(&this->m_nvNcommandBuffer, this->m_nvNdevice);
    this->m_qword21E8 = this->sub_7100799078(0, 0x400000, 4);
    this->m_qword21F8 = memalign(8, 0x800);
    this->m_dword21F0 = 0;

    nvnTextureBuilderSetDevice(&this->m_nvNtextureBuilder, this->m_nvNdevice);
    nvnTextureBuilderSetDefaults(&this->m_nvNtextureBuilder);
    nvnTextureBuilderSetFlags(&this->m_nvNtextureBuilder,
                              NVN_TEXTURE_FLAGS_COMPRESSIBLE | NVN_TEXTURE_FLAGS_DISPLAY);
    nvnTextureBuilderSetSize2D(&this->m_nvNtextureBuilder, this->m_textureSizesFirst[0],
                               this->m_textureSizesSecond[0]);
    nvnTextureBuilderSetTarget(&this->m_nvNtextureBuilder, NVN_TEXTURE_TARGET_2D);
    nvnTextureBuilderSetFormat(&this->m_nvNtextureBuilder, NVN_FORMAT_RGBA8);
    this->m_rgbA8TextureStorageSize = nvnTextureBuilderGetStorageSize(&this->m_nvNtextureBuilder);
    this->m_rgbA8TextureStorageAlignment = nvnTextureBuilderGetStorageAlignment(&this->m_nvNtextureBuilder);

    nvnTextureBuilderSetDefaults(&this->m_nvNtextureBuilder);
    nvnTextureBuilderSetFlags(&this->m_nvNtextureBuilder, NVN_TEXTURE_FLAGS_COMPRESSIBLE);
    nvnTextureBuilderSetTarget(&this->m_nvNtextureBuilder, NVN_TEXTURE_TARGET_2D);
    nvnTextureBuilderSetFormat(&this->m_nvNtextureBuilder, NVN_FORMAT_DEPTH24_STENCIL8);
    nvnTextureBuilderSetSize2D(&this->m_nvNtextureBuilder, this->m_textureSizesFirst[0],
                               this->m_textureSizesSecond[0]);
    this->m_deptH24StenciL8TextureStorageSize = nvnTextureBuilderGetStorageSize(&this->m_nvNtextureBuilder);
    this->m_deptH24StenciL8TextureStorageAlignment
        = nvnTextureBuilderGetStorageAlignment(&this->m_nvNtextureBuilder);

    nvnTextureBuilderSetSize2D(&this->m_nvNtextureBuilder, this->m_textureSizesFirst[1],
                               this->m_textureSizesSecond[1]);
    this->m_deptH24StenciL8HdTextureStorageSize = nvnTextureBuilderGetStorageSize(&this->m_nvNtextureBuilder);
    this->m_deptH24StenciL8HdTextureStorageAlignment = this->sub_7100799078(
        1, 3 * this->m_rgbA8TextureStorageSize + this->m_deptH24StenciL8TextureStorageSize,
        this->m_rgbA8TextureStorageAlignment);

    nvnTextureBuilderSetFormat(&this->m_nvNtextureBuilder, NVN_FORMAT_RGBA16F);
    nvnTextureBuilderSetSize2D(&this->m_nvNtextureBuilder, this->m_textureSizesFirst[0],
                               this->m_textureSizesSecond[0]);
    this->m_rgbA16FTextureStorageSize = nvnTextureBuilderGetStorageSize(&this->m_nvNtextureBuilder);
    this->m_rgbA16FTextureStorageAlignment = nvnTextureBuilderGetStorageAlignment(&this->m_nvNtextureBuilder);

    nvnTextureBuilderSetSize2D(&this->m_nvNtextureBuilder, this->m_textureSizesFirst[1],
                               this->m_textureSizesSecond[1]);
    this->m_rgbA16FHdTextureStorageSize = nvnTextureBuilderGetStorageSize(&this->m_nvNtextureBuilder);
    this->m_rgbA16FHdTextureStorageAlignment
        = this->sub_7100799078(1, this->m_rgbA16FTextureStorageSize, this->m_rgbA16FTextureStorageAlignment);

    nvnTextureBuilderSetFormat(&this->m_nvNtextureBuilder, NVN_FORMAT_RGBA8);

    for (int i = 0; i < 6; i++) {
        nvnTextureBuilderSetSize2D(&this->m_nvNtextureBuilder, textureWidths[i], textureHeights[i]);
        this->m_textureStorageSizes[i] = nvnTextureBuilderGetStorageSize(&this->m_nvNtextureBuilder);
        this->m_textureStorageAlignments[i]
            = nvnTextureBuilderGetStorageAlignment(&this->m_nvNtextureBuilder);

        if (i == 1) {
            this->m_idkReally[i] = this->m_idkReally[0];
            continue;
        }

        this->m_idkReally[i]
            = this->sub_7100799078(1, this->m_textureStorageSizes[i], this->m_textureStorageAlignments[i]);
    }

    NVNbufferBuilder bufferBuilder1;
    nvnBufferBuilderSetDevice(&bufferBuilder1, this->m_nvNdevice);
    nvnBufferBuilderSetDefaults(&bufferBuilder1);

    size_t offset = this->sub_7100799078(0, 0x4000, 1);
    nvnBufferBuilderSetStorage(&bufferBuilder1, this->getNVNMemoryPoolByIndex(0), offset, 0x4000);
    nvnBufferInitialize(&this->m_buffers[0], &bufferBuilder1);

    offset = this->sub_7100799078(0, (4 * textureWidths[0] * textureHeights[0]), 1);
    nvnBufferBuilderSetStorage(&bufferBuilder1, this->getNVNMemoryPoolByIndex(0), offset,
                               4 * textureWidths[0] * textureHeights[0]);
    nvnBufferInitialize(&this->m_buffers[1], &bufferBuilder1);

    nvnDeviceGetInteger(this->m_nvNdevice, NVN_DEVICE_INFO_RESERVED_TEXTURE_DESCRIPTORS,
                        &this->m_reservedTextureDescriptors);
    nvnDeviceGetInteger(this->m_nvNdevice, NVN_DEVICE_INFO_RESERVED_SAMPLER_DESCRIPTORS,
                        &this->m_reservedSamplerDescriptors);

    int HD_TYPE = this->m_reservedTextureDescriptors + 1035;  // why????
    int HD_TYPE_1 = this->m_reservedSamplerDescriptors + 64;

    this->m_dword2250 = 0;
    this->m_hdReservedTextureDescriptors = HD_TYPE;
    this->m_hdReservedSamplerDescriptors = HD_TYPE_1;

    int DESCRIPTOR_SIZE;
    nvnDeviceGetInteger(this->m_nvNdevice, NVN_DEVICE_INFO_TEXTURE_DESCRIPTOR_SIZE, &DESCRIPTOR_SIZE);
    offset = this->sub_7100799078(0, DESCRIPTOR_SIZE * this->m_hdReservedTextureDescriptors, DESCRIPTOR_SIZE);
    nvnTexturePoolInitialize(&this->m_nvNtexturePool, getNVNMemoryPoolByIndex(0), offset,
                             this->m_hdReservedTextureDescriptors);

    nvnDeviceGetInteger(this->m_nvNdevice, NVN_DEVICE_INFO_SAMPLER_DESCRIPTOR_SIZE, &DESCRIPTOR_SIZE);
    offset = this->sub_7100799078(0, DESCRIPTOR_SIZE * this->m_hdReservedSamplerDescriptors, DESCRIPTOR_SIZE);
    nvnSamplerPoolInitialize(&this->m_nvNsamplerPool, getNVNMemoryPoolByIndex(0), offset,
                             this->m_hdReservedSamplerDescriptors);

    this->m_qword26E0 = 0;
    this->m_qword26E8 = 0;
    this->m_qword26F0 = 0;
    this->m_qword26F8 = 0;
    this->m_qword2700 = 0;
    this->m_nvNwindow = nullptr;
    this->m_qword2758 = 0;
    this->m_qword2760 = 0;
    this->m_qword2798 = 0;
    this->m_qword27A0 = 0;
    this->m_qword27A8 = 0;
    this->m_qword27B0 = 0;
    this->m_qword27B8 = 0;
    this->m_qword27C0 = 0;

    nvnWindowBuilderSetDefaults(&this->m_nvNwindowBuilder);
    nvnWindowBuilderSetDevice(&this->m_nvNwindowBuilder, this->m_nvNdevice);
    nvnWindowBuilderSetNativeWindow(&this->m_nvNwindowBuilder, this->m_window);

    this->sub_7100796C74();

    this->m_qword2598 = this->sub_7100799078(0, 0x4000000, 0x100);

    NVNbufferBuilder bufferBuilder;
    nvnBufferBuilderSetDefaults(&bufferBuilder);
    nvnBufferBuilderSetDevice(&bufferBuilder, this->m_nvNdevice);
    nvnBufferBuilderSetStorage(&bufferBuilder, getNVNMemoryPoolByIndex(0), this->m_qword2598, 0x4000000);
    nvnBufferInitialize(&this->m_nvNbuffer, &bufferBuilder);

    this->m_qword25A0 = (void*)256;
    this->m_dword25A8 = 0;
    this->m_bufferMap = (float*)nvnBufferMap(&this->m_nvNbuffer);
    this->m_nvNbufferAddr = nvnBufferGetAddress(&this->m_nvNbuffer);

    mat4x4& matrix1 = *reinterpret_cast<mat4x4*>(this->m_bufferMap);
    memset(matrix1, 0, sizeof(matrix1));
    matrix1[0][0] = 1.0f;
    matrix1[1][1] = 1.0f;
    matrix1[2][2] = 1.0f;
    matrix1[3][3] = 1.0f;

    mat4x4& matrix2 = *reinterpret_cast<mat4x4*>(this->m_bufferMap + 0x800000);
    memset(matrix2, 0, sizeof(matrix2));
    matrix2[0][0] = 1.0f;
    matrix2[1][1] = 1.0f;
    matrix2[2][2] = 1.0f;
    matrix2[3][3] = 1.0f;

    this->m_qword25F0 = this->sub_7100799078(0, 0xA00000, 4);
    nvnBufferBuilderSetStorage(&bufferBuilder, getNVNMemoryPoolByIndex(0), this->m_qword25F0, 0xA00000);
    nvnBufferInitialize(&this->m_nvNbuffer2, &bufferBuilder);
    this->m_qword25F8 = 0LL;
    this->m_dword2600 = 0;
    this->m_bufferMap2 = nvnBufferMap(&this->m_nvNbuffer2);
    this->m_nvNbufferAddr2 = nvnBufferGetAddress(&this->m_nvNbuffer2);

    this->m_qword2648 = this->sub_7100799078(0, 0x800000, 16);
    nvnBufferBuilderSetStorage(&bufferBuilder, getNVNMemoryPoolByIndex(0), this->m_qword2648, 0x800000);
    nvnBufferInitialize(&this->m_nvNbuffer3, &bufferBuilder);
    this->m_qword2650 = 0LL;
    this->m_dword2658 = 0;
    this->m_bufferMap3 = (void*)nvnBufferMap(&this->m_nvNbuffer3);
    this->m_nvNbufferAddr3 = nvnBufferGetAddress(&this->m_nvNbuffer3);

    this->InitialiseContext(true);

    this->m_somethingTexturePtrs[0] = (void*)operator new[](0x1000000uLL);
    this->m_somethingTexturePtrs[1] = (void*)operator new[](0x1F400uLL);
    this->m_somethingTexturePtrs[2] = (void*)operator new[](0xFA000uLL);
    this->m_somethingTexturePtrs[3] = (void*)operator new[](0xFA00uLL);
    this->m_somethingTexturePtrs[4] = (void*)operator new[](0x3E80uLL);
    this->m_somethingTexturePtrs[5] = (void*)operator new[](0xFA00uLL);
    this->m_somethingTexturePtrs[6] = (void*)operator new[](0x3E80uLL);
    memset(this->m_somethingTexturePtrs[0], 255, 0x1000000uLL);
    memset(this->m_somethingTexturePtrs[1], 0, 0x1F400uLL);
    memset(this->m_somethingTexturePtrs[3], 0, 0xFA00uLL);
    memset(this->m_somethingTexturePtrs[5], 0, 0xFA00uLL);
    memset(this->m_somethingTexturePtrs[4], 0, 0x3E80uLL);
    memset(this->m_somethingTexturePtrs[6], 0, 0x3E80uLL);
    // COULD BE THAT THIS MISSMATCHES, ORDER OF MEMSETS

    this->m_elo1 = 0;
    this->m_elo2 = 0;
    this->m_word3CE00 = 0;

    this->m_qword3CdC0 = psInstance->sub_7100799078(0, 0x8000000, 4);
    this->m_class71007B7E781 = new class_71007B7E78(this->m_qword3CdC0, 0x8000000);

    this->m_qword3CdC8 = psInstance->sub_7100799078(0, 0x8000000, 1024);
    this->m_class71007B7E782 = new class_71007B7E78(this->m_qword3CdC8, 0x8000000);

    this->LoadShaders();
    this->SetupShaders();

    float colour[4] = {};
    this->SetClearColour(colour);

    memset(this->m_someData, 0, sizeof(this->m_someData));

    nn::os::InitializeMutex(&this->m_mutex1, 1, 0);
    nn::os::InitializeMutex(&someRendererMutex, 1, 0);
    nn::os::InitializeMutex(&this->m_mutex2, 1, 0);
    nn::os::InitializeMutex(&this->m_mutex3, 1, 0);

    this->m_textureId1 = this->TextureCreate();  // could be that this is done as arg for below
    this->TextureBind(this->m_textureId1);

    char someString[1024];
    memset(someString, 255, sizeof(someString));
    this->TextureData(16, 16, someString, 0, (C4JRender::eTextureFormat)0);

    this->m_gammaIntensity = 0x2AAA;
    this->m_dword2998 = 0;
    this->m_byte299C = 0;

    this->m_bool3C9E0 = 1;
    this->m_dword3C9E4 = 0;

    this->StateSetVertexTextureUV(0.0f, 0.0f);
    this->StateSetTextureScaleUI(1.0f, 1.0f, 0.0f, 0.0f);
    this->StateSetLerpColour(0.0f, 0.0f, 0.0f, 0.0f);
    this->StateSetFogColour(0.0f, 0.0f, 0.0f);
    this->StateSetFogEnable(false);

    int src[4] = {0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000};
    memcpy(&this->m_char3CE04, src, 0x10);
    memset(&this->m_char3CE44, 0, 0x10);
    memcpy(&this->m_char3CE54, src, 0x10);
    memcpy(&this->m_char3CE64, src, 0x10);
    memcpy(&this->m_char3CE74, src, 0x10);
    memcpy(&this->m_char3CE84, src, 0x10);
    this->m_byte3CE94 = 1;
    memset(&this->m_dupa, 0, 0x70);
    memset(&this->m_cipa, 0, 0x10);

    this->m_bool3CF18 = 1;

    this->StateSetVertexTextureUV(0.0f, 0.0f);
    this->m_dword29C0 = -1;
    this->m_dword29C4 = -1;
    this->m_byte29Cc = 0;
    this->m_elo = 0;
    this->m_elo22 = 0;

    nvnWindowSetCrop(this->m_nvNwindow, 0, 0, m_textureSizesFirst[this->m_dword28E8],
                     m_textureSizesSecond[this->m_dword28E8]);
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
    this->m_gammaIntensity = gamma;
}
