#pragma once

#include <nvn/nvn_FuncPtrBase.h>

#ifdef __cplusplus
extern "C" {
#endif

static inline void nvnDeviceBuilderSetDefaults(NVNdeviceBuilder* builder) {
    pfnc_nvnDeviceBuilderSetDefaults(builder);
}

static inline void nvnDeviceBuilderSetFlags(NVNdeviceBuilder* builder, int flags) {
    pfnc_nvnDeviceBuilderSetFlags(builder, flags);
}

static inline NVNboolean nvnDeviceInitialize(NVNdevice* device, const NVNdeviceBuilder* builder) {
    return pfnc_nvnDeviceInitialize(device, builder);
}

static inline void nvnDeviceFinalize(NVNdevice* device) {
    pfnc_nvnDeviceFinalize(device);
}

static inline void nvnDeviceSetDebugLabel(NVNdevice* device, const char* label) {
    pfnc_nvnDeviceSetDebugLabel(device, label);
}

static inline PFNNVNGENERICFUNCPTRPROC nvnDeviceGetProcAddress(const NVNdevice* device,
                                                               const char* s) {
    return pfnc_nvnDeviceGetProcAddress(device, s);
}

static inline void nvnDeviceGetInteger(const NVNdevice* device, NVNdeviceInfo pname, int* v) {
    pfnc_nvnDeviceGetInteger(device, pname, v);
}

static inline uint64_t nvnDeviceGetCurrentTimestampInNanoseconds(const NVNdevice* device) {
    return pfnc_nvnDeviceGetCurrentTimestampInNanoseconds(device);
}

static inline void nvnDeviceSetIntermediateShaderCache(NVNdevice* device, int i) {
    pfnc_nvnDeviceSetIntermediateShaderCache(device, i);
}

static inline NVNtextureHandle nvnDeviceGetTextureHandle(const NVNdevice* device, int textureID,
                                                         int samplerID) {
    return pfnc_nvnDeviceGetTextureHandle(device, textureID, samplerID);
}

static inline NVNtextureHandle nvnDeviceGetTexelFetchHandle(const NVNdevice* device,
                                                            int textureID) {
    return pfnc_nvnDeviceGetTexelFetchHandle(device, textureID);
}

static inline NVNimageHandle nvnDeviceGetImageHandle(const NVNdevice* device, int textureID) {
    return pfnc_nvnDeviceGetImageHandle(device, textureID);
}

static inline void nvnDeviceInstallDebugCallback(NVNdevice* device,
                                                 const PFNNVNDEBUGCALLBACKPROC callback,
                                                 void* callbackData, NVNboolean enable) {
    pfnc_nvnDeviceInstallDebugCallback(device, callback, callbackData, enable);
}

static inline NVNdebugDomainId nvnDeviceGenerateDebugDomainId(const NVNdevice* device,
                                                              const char* s) {
    return pfnc_nvnDeviceGenerateDebugDomainId(device, s);
}

static inline void nvnDeviceSetWindowOriginMode(NVNdevice* device,
                                                NVNwindowOriginMode windowOriginMode) {
    pfnc_nvnDeviceSetWindowOriginMode(device, windowOriginMode);
}

static inline void nvnDeviceSetDepthMode(NVNdevice* device, NVNdepthMode depthMode) {
    pfnc_nvnDeviceSetDepthMode(device, depthMode);
}

static inline NVNboolean nvnDeviceRegisterFastClearColor(NVNdevice* device, const float* color,
                                                         NVNformat format) {
    return pfnc_nvnDeviceRegisterFastClearColor(device, color, format);
}

static inline NVNboolean nvnDeviceRegisterFastClearColori(NVNdevice* device, const int* color,
                                                          NVNformat format) {
    return pfnc_nvnDeviceRegisterFastClearColori(device, color, format);
}

static inline NVNboolean nvnDeviceRegisterFastClearColorui(NVNdevice* device, const uint32_t* color,
                                                           NVNformat format) {
    return pfnc_nvnDeviceRegisterFastClearColorui(device, color, format);
}

static inline NVNboolean nvnDeviceRegisterFastClearDepth(NVNdevice* device, float f) {
    return pfnc_nvnDeviceRegisterFastClearDepth(device, f);
}

static inline NVNwindowOriginMode nvnDeviceGetWindowOriginMode(const NVNdevice* device) {
    return pfnc_nvnDeviceGetWindowOriginMode(device);
}

static inline NVNdepthMode nvnDeviceGetDepthMode(const NVNdevice* device) {
    return pfnc_nvnDeviceGetDepthMode(device);
}

static inline uint64_t nvnDeviceGetTimestampInNanoseconds(const NVNdevice* device,
                                                          const NVNcounterData* counterData) {
    return pfnc_nvnDeviceGetTimestampInNanoseconds(device, counterData);
}

static inline void nvnDeviceApplyDeferredFinalizes(NVNdevice* device, int i) {
    pfnc_nvnDeviceApplyDeferredFinalizes(device, i);
}

static inline void nvnDeviceFinalizeCommandHandle(NVNdevice* device, NVNcommandHandle handles) {
    pfnc_nvnDeviceFinalizeCommandHandle(device, handles);
}

static inline void nvnDeviceWalkDebugDatabase(const NVNdevice* device,
                                              NVNdebugObjectType debugObjectType,
                                              PFNNVNWALKDEBUGDATABASECALLBACKPROC callback,
                                              void* callbackData) {
    pfnc_nvnDeviceWalkDebugDatabase(device, debugObjectType, callback, callbackData);
}

static inline NVNseparateTextureHandle nvnDeviceGetSeparateTextureHandle(const NVNdevice* device,
                                                                         int textureID) {
    return pfnc_nvnDeviceGetSeparateTextureHandle(device, textureID);
}

static inline NVNseparateSamplerHandle nvnDeviceGetSeparateSamplerHandle(const NVNdevice* device,
                                                                         int textureID) {
    return pfnc_nvnDeviceGetSeparateSamplerHandle(device, textureID);
}

static inline NVNboolean nvnDeviceIsExternalDebuggerAttached(const NVNdevice* device) {
    return pfnc_nvnDeviceIsExternalDebuggerAttached(device);
}

static inline NVNqueueGetErrorResult nvnQueueGetError(NVNqueue* queue, NVNqueueErrorInfo* info) {
    return pfnc_nvnQueueGetError(queue, info);
}

static inline size_t nvnQueueGetTotalCommandMemoryUsed(NVNqueue* queue) {
    return pfnc_nvnQueueGetTotalCommandMemoryUsed(queue);
}

static inline size_t nvnQueueGetTotalControlMemoryUsed(NVNqueue* queue) {
    return pfnc_nvnQueueGetTotalControlMemoryUsed(queue);
}

static inline size_t nvnQueueGetTotalComputeMemoryUsed(NVNqueue* queue) {
    return pfnc_nvnQueueGetTotalComputeMemoryUsed(queue);
}

static inline void nvnQueueResetMemoryUsageCounts(NVNqueue* queue) {
    pfnc_nvnQueueResetMemoryUsageCounts(queue);
}

static inline void nvnQueueBuilderSetDevice(NVNqueueBuilder* builder, NVNdevice* device) {
    pfnc_nvnQueueBuilderSetDevice(builder, device);
}

static inline void nvnQueueBuilderSetDefaults(NVNqueueBuilder* builder) {
    pfnc_nvnQueueBuilderSetDefaults(builder);
}

static inline void nvnQueueBuilderSetFlags(NVNqueueBuilder* builder, int flags) {
    pfnc_nvnQueueBuilderSetFlags(builder, flags);
}

static inline void nvnQueueBuilderSetCommandMemorySize(NVNqueueBuilder* builder, size_t size) {
    pfnc_nvnQueueBuilderSetCommandMemorySize(builder, size);
}

static inline void nvnQueueBuilderSetComputeMemorySize(NVNqueueBuilder* builder, size_t size) {
    pfnc_nvnQueueBuilderSetComputeMemorySize(builder, size);
}

static inline void nvnQueueBuilderSetControlMemorySize(NVNqueueBuilder* builder, size_t size) {
    pfnc_nvnQueueBuilderSetControlMemorySize(builder, size);
}

static inline size_t nvnQueueBuilderGetQueueMemorySize(const NVNqueueBuilder* builder) {
    return pfnc_nvnQueueBuilderGetQueueMemorySize(builder);
}

static inline void nvnQueueBuilderSetQueueMemory(NVNqueueBuilder* builder, void* memory,
                                                 size_t size) {
    pfnc_nvnQueueBuilderSetQueueMemory(builder, memory, size);
}

static inline void nvnQueueBuilderSetCommandFlushThreshold(NVNqueueBuilder* builder, size_t size) {
    pfnc_nvnQueueBuilderSetCommandFlushThreshold(builder, size);
}

static inline NVNboolean nvnQueueInitialize(NVNqueue* queue, const NVNqueueBuilder* builder) {
    return pfnc_nvnQueueInitialize(queue, builder);
}

static inline void nvnQueueFinalize(NVNqueue* queue) {
    pfnc_nvnQueueFinalize(queue);
}

static inline void nvnQueueSetDebugLabel(NVNqueue* queue, const char* label) {
    pfnc_nvnQueueSetDebugLabel(queue, label);
}

static inline void nvnQueueSubmitCommands(NVNqueue* queue, int numCommands,
                                          const NVNcommandHandle* handles) {
    pfnc_nvnQueueSubmitCommands(queue, numCommands, handles);
}

static inline void nvnQueueFlush(NVNqueue* queue) {
    pfnc_nvnQueueFlush(queue);
}

static inline void nvnQueueFinish(NVNqueue* queue) {
    pfnc_nvnQueueFinish(queue);
}

static inline void nvnQueuePresentTexture(NVNqueue* queue, NVNwindow* window, int textureIndex) {
    pfnc_nvnQueuePresentTexture(queue, window, textureIndex);
}

static inline NVNqueueAcquireTextureResult
nvnQueueAcquireTexture(NVNqueue* queue, NVNwindow* window, int* textureIndex) {
    return pfnc_nvnQueueAcquireTexture(queue, window, textureIndex);
}

static inline void nvnWindowBuilderSetDevice(NVNwindowBuilder* builder, NVNdevice* device) {
    pfnc_nvnWindowBuilderSetDevice(builder, device);
}

static inline void nvnWindowBuilderSetDefaults(NVNwindowBuilder* builder) {
    pfnc_nvnWindowBuilderSetDefaults(builder);
}

static inline void nvnWindowBuilderSetNativeWindow(NVNwindowBuilder* builder,
                                                   NVNnativeWindow nativeWindow) {
    pfnc_nvnWindowBuilderSetNativeWindow(builder, nativeWindow);
}

static inline void nvnWindowBuilderSetTextures(NVNwindowBuilder* builder, int numTextures,
                                               NVNtexture* const* textures) {
    pfnc_nvnWindowBuilderSetTextures(builder, numTextures, textures);
}

static inline void nvnWindowBuilderSetPresentInterval(NVNwindowBuilder* builder,
                                                      int presentInterval) {
    pfnc_nvnWindowBuilderSetPresentInterval(builder, presentInterval);
}

static inline NVNnativeWindow nvnWindowBuilderGetNativeWindow(const NVNwindowBuilder* builder) {
    return pfnc_nvnWindowBuilderGetNativeWindow(builder);
}

static inline int nvnWindowBuilderGetPresentInterval(const NVNwindowBuilder* builder) {
    return pfnc_nvnWindowBuilderGetPresentInterval(builder);
}

static inline NVNboolean nvnWindowInitialize(NVNwindow* window, const NVNwindowBuilder* builder) {
    return pfnc_nvnWindowInitialize(window, builder);
}

static inline void nvnWindowFinalize(NVNwindow* window) {
    pfnc_nvnWindowFinalize(window);
}

static inline void nvnWindowSetDebugLabel(NVNwindow* window, const char* label) {
    pfnc_nvnWindowSetDebugLabel(window, label);
}

static inline NVNwindowAcquireTextureResult
nvnWindowAcquireTexture(NVNwindow* window, NVNsync* textureAvailableSync, int* textureIndex) {
    return pfnc_nvnWindowAcquireTexture(window, textureAvailableSync, textureIndex);
}

static inline NVNnativeWindow nvnWindowGetNativeWindow(const NVNwindow* window) {
    return pfnc_nvnWindowGetNativeWindow(window);
}

static inline int nvnWindowGetPresentInterval(const NVNwindow* window) {
    return pfnc_nvnWindowGetPresentInterval(window);
}

static inline void nvnWindowSetPresentInterval(NVNwindow* window, int presentInterval) {
    pfnc_nvnWindowSetPresentInterval(window, presentInterval);
}

static inline void nvnWindowSetCrop(NVNwindow* window, int x, int y, int w, int h) {
    pfnc_nvnWindowSetCrop(window, x, y, w, h);
}

static inline void nvnWindowGetCrop(const NVNwindow* window, NVNrectangle* rectangle) {
    pfnc_nvnWindowGetCrop(window, rectangle);
}

static inline NVNboolean nvnProgramInitialize(NVNprogram* program, NVNdevice* device) {
    return pfnc_nvnProgramInitialize(program, device);
}

static inline void nvnProgramFinalize(NVNprogram* program) {
    pfnc_nvnProgramFinalize(program);
}

static inline void nvnProgramSetDebugLabel(NVNprogram* program, const char* label) {
    pfnc_nvnProgramSetDebugLabel(program, label);
}

static inline NVNboolean nvnProgramSetShaders(NVNprogram* program, int count,
                                              const NVNshaderData* stageData) {
    return pfnc_nvnProgramSetShaders(program, count, stageData);
}

static inline void nvnMemoryPoolBuilderSetDevice(NVNmemoryPoolBuilder* builder, NVNdevice* device) {
    pfnc_nvnMemoryPoolBuilderSetDevice(builder, device);
}

static inline void nvnMemoryPoolBuilderSetDefaults(NVNmemoryPoolBuilder* builder) {
    pfnc_nvnMemoryPoolBuilderSetDefaults(builder);
}

static inline void nvnMemoryPoolBuilderSetStorage(NVNmemoryPoolBuilder* builder, void* memory,
                                                  size_t size) {
    pfnc_nvnMemoryPoolBuilderSetStorage(builder, memory, size);
}

static inline void nvnMemoryPoolBuilderSetFlags(NVNmemoryPoolBuilder* builder, int flags) {
    pfnc_nvnMemoryPoolBuilderSetFlags(builder, flags);
}

static inline void nvnMemoryPoolBuilderGetMemory(const NVNmemoryPoolBuilder* builder) {
    pfnc_nvnMemoryPoolBuilderGetMemory(builder);
}

static inline size_t nvnMemoryPoolBuilderGetSize(const NVNmemoryPoolBuilder* builder) {
    return pfnc_nvnMemoryPoolBuilderGetSize(builder);
}

static inline NVNmemoryPoolFlags nvnMemoryPoolBuilderGetFlags(const NVNmemoryPoolBuilder* builder) {
    return pfnc_nvnMemoryPoolBuilderGetFlags(builder);
}

static inline NVNboolean nvnMemoryPoolInitialize(NVNmemoryPool* pool,
                                                 const NVNmemoryPoolBuilder* builder) {
    return pfnc_nvnMemoryPoolInitialize(pool, builder);
}

static inline void nvnMemoryPoolSetDebugLabel(NVNmemoryPool* pool, const char* label) {
    pfnc_nvnMemoryPoolSetDebugLabel(pool, label);
}

static inline void nvnMemoryPoolFinalize(NVNmemoryPool* pool) {
    pfnc_nvnMemoryPoolFinalize(pool);
}

static inline void* nvnMemoryPoolMap(const NVNmemoryPool* pool) {
    return pfnc_nvnMemoryPoolMap(pool);
}

static inline void nvnMemoryPoolFlushMappedRange(const NVNmemoryPool* pool, ptrdiff_t offset,
                                                 size_t size) {
    pfnc_nvnMemoryPoolFlushMappedRange(pool, offset, size);
}

static inline void nvnMemoryPoolInvalidateMappedRange(const NVNmemoryPool* pool, ptrdiff_t offset,
                                                      size_t size) {
    pfnc_nvnMemoryPoolInvalidateMappedRange(pool, offset, size);
}

static inline NVNbufferAddress nvnMemoryPoolGetBufferAddress(const NVNmemoryPool* pool) {
    return pfnc_nvnMemoryPoolGetBufferAddress(pool);
}

static inline NVNboolean nvnMemoryPoolMapVirtual(NVNmemoryPool* pool, int numRequests,
                                                 const NVNmappingRequest* requests) {
    return pfnc_nvnMemoryPoolMapVirtual(pool, numRequests, requests);
}

static inline size_t nvnMemoryPoolGetSize(const NVNmemoryPool* pool) {
    return pfnc_nvnMemoryPoolGetSize(pool);
}

static inline NVNmemoryPoolFlags nvnMemoryPoolGetFlags(const NVNmemoryPool* pool) {
    return pfnc_nvnMemoryPoolGetFlags(pool);
}

static inline NVNboolean nvnTexturePoolInitialize(NVNtexturePool* texturePool,
                                                  const NVNmemoryPool* memoryPool, ptrdiff_t offset,
                                                  int numDescriptors) {
    return pfnc_nvnTexturePoolInitialize(texturePool, memoryPool, offset, numDescriptors);
}

static inline void nvnTexturePoolSetDebugLabel(NVNtexturePool* pool, const char* label) {
    pfnc_nvnTexturePoolSetDebugLabel(pool, label);
}

static inline void nvnTexturePoolFinalize(NVNtexturePool* pool) {
    pfnc_nvnTexturePoolFinalize(pool);
}

static inline void nvnTexturePoolRegisterTexture(const NVNtexturePool* pool, int id,
                                                 const NVNtexture* texture,
                                                 const NVNtextureView* view) {
    pfnc_nvnTexturePoolRegisterTexture(pool, id, texture, view);
}

static inline void nvnTexturePoolRegisterImage(const NVNtexturePool* pool, int id,
                                               const NVNtexture* texture,
                                               const NVNtextureView* view) {
    pfnc_nvnTexturePoolRegisterImage(pool, id, texture, view);
}

static inline const NVNmemoryPool* nvnTexturePoolGetMemoryPool(const NVNtexturePool* pool) {
    return pfnc_nvnTexturePoolGetMemoryPool(pool);
}

static inline ptrdiff_t nvnTexturePoolGetMemoryOffset(const NVNtexturePool* pool) {
    return pfnc_nvnTexturePoolGetMemoryOffset(pool);
}

static inline int nvnTexturePoolGetSize(const NVNtexturePool* pool) {
    return pfnc_nvnTexturePoolGetSize(pool);
}

static inline NVNboolean nvnSamplerPoolInitialize(NVNsamplerPool* samplerPool,
                                                  const NVNmemoryPool* memoryPool, ptrdiff_t offset,
                                                  int numDescriptors) {
    return pfnc_nvnSamplerPoolInitialize(samplerPool, memoryPool, offset, numDescriptors);
}

static inline void nvnSamplerPoolSetDebugLabel(NVNsamplerPool* pool, const char* label) {
    pfnc_nvnSamplerPoolSetDebugLabel(pool, label);
}

static inline void nvnSamplerPoolFinalize(NVNsamplerPool* pool) {
    pfnc_nvnSamplerPoolFinalize(pool);
}

static inline void nvnSamplerPoolRegisterSampler(const NVNsamplerPool* pool, int id,
                                                 const NVNsampler* sampler) {
    pfnc_nvnSamplerPoolRegisterSampler(pool, id, sampler);
}

static inline void nvnSamplerPoolRegisterSamplerBuilder(const NVNsamplerPool* pool, int id,
                                                        const NVNsamplerBuilder* builder) {
    pfnc_nvnSamplerPoolRegisterSamplerBuilder(pool, id, builder);
}

static inline const NVNmemoryPool* nvnSamplerPoolGetMemoryPool(const NVNsamplerPool* pool) {
    return pfnc_nvnSamplerPoolGetMemoryPool(pool);
}

static inline ptrdiff_t nvnSamplerPoolGetMemoryOffset(const NVNsamplerPool* pool) {
    return pfnc_nvnSamplerPoolGetMemoryOffset(pool);
}

static inline int nvnSamplerPoolGetSize(const NVNsamplerPool* pool) {
    return pfnc_nvnSamplerPoolGetSize(pool);
}

static inline void nvnBufferBuilderSetDevice(NVNbufferBuilder* builder, NVNdevice* device) {
    pfnc_nvnBufferBuilderSetDevice(builder, device);
}

static inline void nvnBufferBuilderSetDefaults(NVNbufferBuilder* builder) {
    pfnc_nvnBufferBuilderSetDefaults(builder);
}

static inline void nvnBufferBuilderSetStorage(NVNbufferBuilder* builder, NVNmemoryPool* pool,
                                              ptrdiff_t offset, size_t size) {
    pfnc_nvnBufferBuilderSetStorage(builder, pool, offset, size);
}

static inline NVNmemoryPool nvnBufferBuilderGetMemoryPool(const NVNbufferBuilder* builder) {
    return pfnc_nvnBufferBuilderGetMemoryPool(builder);
}

static inline ptrdiff_t nvnBufferBuilderGetMemoryOffset(const NVNbufferBuilder* builder) {
    return pfnc_nvnBufferBuilderGetMemoryOffset(builder);
}

static inline size_t nvnBufferBuilderGetSize(const NVNbufferBuilder* builder) {
    return pfnc_nvnBufferBuilderGetSize(builder);
}

static inline NVNboolean nvnBufferInitialize(NVNbuffer* buffer, const NVNbufferBuilder* builder) {
    return pfnc_nvnBufferInitialize(buffer, builder);
}

static inline void nvnBufferSetDebugLabel(NVNbuffer* buffer, const char* label) {
    pfnc_nvnBufferSetDebugLabel(buffer, label);
}

static inline void nvnBufferFinalize(NVNbuffer* buffer) {
    pfnc_nvnBufferFinalize(buffer);
}

static inline void* nvnBufferMap(const NVNbuffer* buffer) {
    return pfnc_nvnBufferMap(buffer);
}

static inline NVNbufferAddress nvnBufferGetAddress(const NVNbuffer* buffer) {
    return pfnc_nvnBufferGetAddress(buffer);
}

static inline void nvnBufferFlushMappedRange(const NVNbuffer* buffer, ptrdiff_t offset,
                                             size_t size) {
    pfnc_nvnBufferFlushMappedRange(buffer, offset, size);
}

static inline void nvnBufferInvalidateMappedRange(const NVNbuffer* buffer, ptrdiff_t offset,
                                                  size_t size) {
    pfnc_nvnBufferInvalidateMappedRange(buffer, offset, size);
}

static inline NVNmemoryPool* nvnBufferGetMemoryPool(const NVNbuffer* buffer) {
    return pfnc_nvnBufferGetMemoryPool(buffer);
}

static inline ptrdiff_t nvnBufferGetMemoryOffset(const NVNbuffer* buffer) {
    return pfnc_nvnBufferGetMemoryOffset(buffer);
}

static inline size_t nvnBufferGetSize(const NVNbuffer* buffer) {
    return pfnc_nvnBufferGetSize(buffer);
}

static inline uint64_t nvnBufferGetDebugID(const NVNbuffer* buffer) {
    return pfnc_nvnBufferGetDebugID(buffer);
}

static inline void nvnTextureBuilderSetDevice(NVNtextureBuilder* builder, NVNdevice* device) {
    pfnc_nvnTextureBuilderSetDevice(builder, device);
}

static inline void nvnTextureBuilderSetDefaults(NVNtextureBuilder* builder) {
    pfnc_nvnTextureBuilderSetDefaults(builder);
}

static inline void nvnTextureBuilderSetFlags(NVNtextureBuilder* builder, int flags) {
    pfnc_nvnTextureBuilderSetFlags(builder, flags);
}

static inline void nvnTextureBuilderSetTarget(NVNtextureBuilder* builder, NVNtextureTarget target) {
    pfnc_nvnTextureBuilderSetTarget(builder, target);
}

static inline void nvnTextureBuilderSetWidth(NVNtextureBuilder* builder, int width) {
    pfnc_nvnTextureBuilderSetWidth(builder, width);
}

static inline void nvnTextureBuilderSetHeight(NVNtextureBuilder* builder, int height) {
    pfnc_nvnTextureBuilderSetHeight(builder, height);
}

static inline void nvnTextureBuilderSetDepth(NVNtextureBuilder* builder, int depth) {
    pfnc_nvnTextureBuilderSetDepth(builder, depth);
}

static inline void nvnTextureBuilderSetSize1D(NVNtextureBuilder* builder, int size) {
    pfnc_nvnTextureBuilderSetSize1D(builder, size);
}

static inline void nvnTextureBuilderSetSize2D(NVNtextureBuilder* builder, int width, int height) {
    pfnc_nvnTextureBuilderSetSize2D(builder, width, height);
}

static inline void nvnTextureBuilderSetSize3D(NVNtextureBuilder* builder, int width, int height,
                                              int depth) {
    pfnc_nvnTextureBuilderSetSize3D(builder, width, height, depth);
}

static inline void nvnTextureBuilderSetLevels(NVNtextureBuilder* builder, int numLevels) {
    pfnc_nvnTextureBuilderSetLevels(builder, numLevels);
}

static inline void nvnTextureBuilderSetFormat(NVNtextureBuilder* builder, NVNformat format) {
    pfnc_nvnTextureBuilderSetFormat(builder, format);
}

static inline void nvnTextureBuilderSetSamples(NVNtextureBuilder* builder, int samples) {
    pfnc_nvnTextureBuilderSetSamples(builder, samples);
}

static inline void nvnTextureBuilderSetSwizzle(NVNtextureBuilder* builder, NVNtextureSwizzle r,
                                               NVNtextureSwizzle g, NVNtextureSwizzle b,
                                               NVNtextureSwizzle a) {
    pfnc_nvnTextureBuilderSetSwizzle(builder, r, g, b, a);
}

static inline void nvnTextureBuilderSetDepthStencilMode(NVNtextureBuilder* builder,
                                                        NVNtextureDepthStencilMode mode) {
    pfnc_nvnTextureBuilderSetDepthStencilMode(builder, mode);
}

static inline size_t nvnTextureBuilderGetStorageSize(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetStorageSize(builder);
}

static inline size_t nvnTextureBuilderGetStorageAlignment(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetStorageAlignment(builder);
}

static inline void nvnTextureBuilderSetStorage(NVNtextureBuilder* builder, NVNmemoryPool* pool,
                                               ptrdiff_t offset) {
    pfnc_nvnTextureBuilderSetStorage(builder, pool, offset);
}

static inline void nvnTextureBuilderSetPackagedTextureData(NVNtextureBuilder* builder,
                                                           const void* data) {
    pfnc_nvnTextureBuilderSetPackagedTextureData(builder, data);
}

static inline void
nvnTextureBuilderSetPackagedTextureLayout(NVNtextureBuilder* builder,
                                          const NVNpackagedTextureLayout* layout) {
    pfnc_nvnTextureBuilderSetPackagedTextureLayout(builder, layout);
}

static inline void nvnTextureBuilderSetStride(NVNtextureBuilder* builder, ptrdiff_t stride) {
    pfnc_nvnTextureBuilderSetStride(builder, stride);
}

static inline void nvnTextureBuilderSetGLTextureName(NVNtextureBuilder* builder, uint32_t name) {
    pfnc_nvnTextureBuilderSetGLTextureName(builder, name);
}

static inline NVNstorageClass nvnTextureBuilderGetStorageClass(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetStorageClass(builder);
}

static inline NVNtextureFlags nvnTextureBuilderGetFlags(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetFlags(builder);
}

static inline NVNtextureTarget nvnTextureBuilderGetTarget(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetTarget(builder);
}

static inline int nvnTextureBuilderGetWidth(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetWidth(builder);
}

static inline int nvnTextureBuilderGetHeight(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetHeight(builder);
}

static inline int nvnTextureBuilderGetDepth(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetDepth(builder);
}

static inline int nvnTextureBuilderGetLevels(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetLevels(builder);
}

static inline NVNformat nvnTextureBuilderGetFormat(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetFormat(builder);
}

static inline int nvnTextureBuilderGetSamples(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetSamples(builder);
}

static inline void nvnTextureBuilderGetSwizzle(const NVNtextureBuilder* builder,
                                               NVNtextureSwizzle* r, NVNtextureSwizzle* g,
                                               NVNtextureSwizzle* b, NVNtextureSwizzle* a) {
    pfnc_nvnTextureBuilderGetSwizzle(builder, r, g, b, a);
}

static inline NVNtextureDepthStencilMode
nvnTextureBuilderGetDepthStencilMode(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetDepthStencilMode(builder);
}

static inline const void*
nvnTextureBuilderGetPackagedTextureData(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetPackagedTextureData(builder);
}

static inline ptrdiff_t nvnTextureBuilderGetStride(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetStride(builder);
}

static inline void nvnTextureBuilderGetSparseTileLayout(const NVNtextureBuilder* builder,
                                                        NVNtextureSparseTileLayout* layout) {
    pfnc_nvnTextureBuilderGetSparseTileLayout(builder, layout);
}

static inline uint32_t nvnTextureBuilderGetGLTextureName(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetGLTextureName(builder);
}

static inline size_t nvnTextureBuilderGetZCullStorageSize(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetZCullStorageSize(builder);
}

static inline NVNmemoryPool nvnTextureBuilderGetMemoryPool(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetMemoryPool(builder);
}

static inline ptrdiff_t nvnTextureBuilderGetMemoryOffset(const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureBuilderGetMemoryOffset(builder);
}

static inline void nvnTextureViewSetDefaults(NVNtextureView* view) {
    pfnc_nvnTextureViewSetDefaults(view);
}

static inline void nvnTextureViewSetLevels(NVNtextureView* view, int baseLevel, int numLevels) {
    pfnc_nvnTextureViewSetLevels(view, baseLevel, numLevels);
}

static inline void nvnTextureViewSetLayers(NVNtextureView* view, int minLayer, int numLayers) {
    pfnc_nvnTextureViewSetLayers(view, minLayer, numLayers);
}

static inline void nvnTextureViewSetFormat(NVNtextureView* view, NVNformat format) {
    pfnc_nvnTextureViewSetFormat(view, format);
}

static inline void nvnTextureViewSetSwizzle(NVNtextureView* view, NVNtextureSwizzle r,
                                            NVNtextureSwizzle g, NVNtextureSwizzle b,
                                            NVNtextureSwizzle a) {
    pfnc_nvnTextureViewSetSwizzle(view, r, g, b, a);
}

static inline void nvnTextureViewSetDepthStencilMode(NVNtextureView* view,
                                                     NVNtextureDepthStencilMode mode) {
    pfnc_nvnTextureViewSetDepthStencilMode(view, mode);
}

static inline void nvnTextureViewSetTarget(NVNtextureView* view, NVNtextureTarget target) {
    pfnc_nvnTextureViewSetTarget(view, target);
}

static inline NVNboolean nvnTextureViewGetLevels(const NVNtextureView* view, int* baseLevel,
                                                 int* numLevels) {
    return pfnc_nvnTextureViewGetLevels(view, baseLevel, numLevels);
}

static inline NVNboolean nvnTextureViewGetLayers(const NVNtextureView* view, int* minLayer,
                                                 int* numLayers) {
    return pfnc_nvnTextureViewGetLayers(view, minLayer, numLayers);
}

static inline NVNboolean nvnTextureViewGetFormat(const NVNtextureView* view, NVNformat* format) {
    return pfnc_nvnTextureViewGetFormat(view, format);
}

static inline NVNboolean nvnTextureViewGetSwizzle(const NVNtextureView* view, NVNtextureSwizzle* r,
                                                  NVNtextureSwizzle* g, NVNtextureSwizzle* b,
                                                  NVNtextureSwizzle* a) {
    return pfnc_nvnTextureViewGetSwizzle(view, r, g, b, a);
}

static inline NVNboolean nvnTextureViewGetDepthStencilMode(const NVNtextureView* view,
                                                           NVNtextureDepthStencilMode* mode) {
    return pfnc_nvnTextureViewGetDepthStencilMode(view, mode);
}

static inline NVNboolean nvnTextureViewGetTarget(const NVNtextureView* view,
                                                 NVNtextureTarget* target) {
    return pfnc_nvnTextureViewGetTarget(view, target);
}

static inline NVNboolean nvnTextureViewCompare(const NVNtextureView* view1,
                                               const NVNtextureView* view2) {
    return pfnc_nvnTextureViewCompare(view1, view2);
}

static inline NVNboolean nvnTextureInitialize(NVNtexture* texture,
                                              const NVNtextureBuilder* builder) {
    return pfnc_nvnTextureInitialize(texture, builder);
}

static inline size_t nvnTextureGetZCullStorageSize(const NVNtexture* texture) {
    return pfnc_nvnTextureGetZCullStorageSize(texture);
}

static inline void nvnTextureFinalize(NVNtexture* texture) {
    pfnc_nvnTextureFinalize(texture);
}

static inline void nvnTextureSetDebugLabel(NVNtexture* texture, const char* label) {
    pfnc_nvnTextureSetDebugLabel(texture, label);
}

static inline NVNstorageClass nvnTextureGetStorageClass(const NVNtexture* texture) {
    return pfnc_nvnTextureGetStorageClass(texture);
}

static inline ptrdiff_t nvnTextureGetViewOffset(const NVNtexture* texture,
                                                const NVNtextureView* view) {
    return pfnc_nvnTextureGetViewOffset(texture, view);
}

static inline NVNtextureFlags nvnTextureGetFlags(const NVNtexture* texture) {
    return pfnc_nvnTextureGetFlags(texture);
}

static inline NVNtextureTarget nvnTextureGetTarget(const NVNtexture* texture) {
    return pfnc_nvnTextureGetTarget(texture);
}

static inline int nvnTextureGetWidth(const NVNtexture* texture) {
    return pfnc_nvnTextureGetWidth(texture);
}

static inline int nvnTextureGetHeight(const NVNtexture* texture) {
    return pfnc_nvnTextureGetHeight(texture);
}

static inline int nvnTextureGetDepth(const NVNtexture* texture) {
    return pfnc_nvnTextureGetDepth(texture);
}

static inline int nvnTextureGetLevels(const NVNtexture* texture) {
    return pfnc_nvnTextureGetLevels(texture);
}

static inline NVNformat nvnTextureGetFormat(const NVNtexture* texture) {
    return pfnc_nvnTextureGetFormat(texture);
}

static inline int nvnTextureGetSamples(const NVNtexture* texture) {
    return pfnc_nvnTextureGetSamples(texture);
}

static inline void nvnTextureGetSwizzle(const NVNtexture* texture, NVNtextureSwizzle* r,
                                        NVNtextureSwizzle* g, NVNtextureSwizzle* b,
                                        NVNtextureSwizzle* a) {
    pfnc_nvnTextureGetSwizzle(texture, r, g, b, a);
}

static inline NVNtextureDepthStencilMode nvnTextureGetDepthStencilMode(const NVNtexture* texture) {
    return pfnc_nvnTextureGetDepthStencilMode(texture);
}

static inline ptrdiff_t nvnTextureGetStride(const NVNtexture* texture) {
    return pfnc_nvnTextureGetStride(texture);
}

static inline NVNtextureAddress nvnTextureGetTextureAddress(const NVNtexture* texture) {
    return pfnc_nvnTextureGetTextureAddress(texture);
}

static inline void nvnTextureGetSparseTileLayout(const NVNtexture* texture,
                                                 NVNtextureSparseTileLayout* layout) {
    pfnc_nvnTextureGetSparseTileLayout(texture, layout);
}

static inline void nvnTextureWriteTexels(const NVNtexture* texture, const NVNtextureView* view,
                                         const NVNcopyRegion* region, const void* p) {
    pfnc_nvnTextureWriteTexels(texture, view, region, p);
}

static inline void nvnTextureWriteTexelsStrided(const NVNtexture* texture,
                                                const NVNtextureView* view,
                                                const NVNcopyRegion* region, const void* p,
                                                ptrdiff_t o1, ptrdiff_t o2) {
    pfnc_nvnTextureWriteTexelsStrided(texture, view, region, p, o1, o2);
}

static inline void nvnTextureReadTexels(const NVNtexture* texture, const NVNtextureView* view,
                                        const NVNcopyRegion* region, void* p) {
    pfnc_nvnTextureReadTexels(texture, view, region, p);
}

static inline void nvnTextureReadTexelsStrided(const NVNtexture* texture,
                                               const NVNtextureView* view,
                                               const NVNcopyRegion* region, void* p, ptrdiff_t o1,
                                               ptrdiff_t o2) {
    pfnc_nvnTextureReadTexelsStrided(texture, view, region, p, o1, o2);
}

static inline void nvnTextureFlushTexels(const NVNtexture* texture, const NVNtextureView* view,
                                         const NVNcopyRegion* region) {
    pfnc_nvnTextureFlushTexels(texture, view, region);
}

static inline void nvnTextureInvalidateTexels(const NVNtexture* texture, const NVNtextureView* view,
                                              const NVNcopyRegion* region) {
    pfnc_nvnTextureInvalidateTexels(texture, view, region);
}

static inline NVNmemoryPool nvnTextureGetMemoryPool(const NVNtexture* texture) {
    return pfnc_nvnTextureGetMemoryPool(texture);
}

static inline ptrdiff_t nvnTextureGetMemoryOffset(const NVNtexture* texture) {
    return pfnc_nvnTextureGetMemoryOffset(texture);
}

static inline int nvnTextureGetStorageSize(const NVNtexture* texture) {
    return pfnc_nvnTextureGetStorageSize(texture);
}

static inline NVNboolean nvnTextureCompare(const NVNtexture* texture1, const NVNtexture* texture2) {
    return pfnc_nvnTextureCompare(texture1, texture2);
}

static inline uint64_t nvnTextureGetDebugID(const NVNtexture* texture) {
    return pfnc_nvnTextureGetDebugID(texture);
}

static inline void nvnSamplerBuilderSetDevice(NVNsamplerBuilder* builder, NVNdevice* device) {
    pfnc_nvnSamplerBuilderSetDevice(builder, device);
}

static inline void nvnSamplerBuilderSetDefaults(NVNsamplerBuilder* builder) {
    pfnc_nvnSamplerBuilderSetDefaults(builder);
}

static inline void nvnSamplerBuilderSetMinMagFilter(NVNsamplerBuilder* builder, NVNminFilter min,
                                                    NVNmagFilter mag) {
    pfnc_nvnSamplerBuilderSetMinMagFilter(builder, min, mag);
}

static inline void nvnSamplerBuilderSetWrapMode(NVNsamplerBuilder* builder, NVNwrapMode s,
                                                NVNwrapMode t, NVNwrapMode r) {
    pfnc_nvnSamplerBuilderSetWrapMode(builder, s, t, r);
}

static inline void nvnSamplerBuilderSetLodClamp(NVNsamplerBuilder* builder, float min, float max) {
    pfnc_nvnSamplerBuilderSetLodClamp(builder, min, max);
}

static inline void nvnSamplerBuilderSetLodBias(NVNsamplerBuilder* builder, float bias) {
    pfnc_nvnSamplerBuilderSetLodBias(builder, bias);
}

static inline void nvnSamplerBuilderSetCompare(NVNsamplerBuilder* builder, NVNcompareMode mode,
                                               NVNcompareFunc func) {
    pfnc_nvnSamplerBuilderSetCompare(builder, mode, func);
}

static inline void nvnSamplerBuilderSetBorderColor(NVNsamplerBuilder* builder,
                                                   const float* borderColor) {
    pfnc_nvnSamplerBuilderSetBorderColor(builder, borderColor);
}

static inline void nvnSamplerBuilderSetBorderColori(NVNsamplerBuilder* builder,
                                                    const int* borderColor) {
    pfnc_nvnSamplerBuilderSetBorderColori(builder, borderColor);
}

static inline void nvnSamplerBuilderSetBorderColorui(NVNsamplerBuilder* builder,
                                                     const uint32_t* borderColor) {
    pfnc_nvnSamplerBuilderSetBorderColorui(builder, borderColor);
}

static inline void nvnSamplerBuilderSetMaxAnisotropy(NVNsamplerBuilder* builder, float maxAniso) {
    pfnc_nvnSamplerBuilderSetMaxAnisotropy(builder, maxAniso);
}

static inline void nvnSamplerBuilderSetReductionFilter(NVNsamplerBuilder* builder,
                                                       NVNsamplerReduction filter) {
    pfnc_nvnSamplerBuilderSetReductionFilter(builder, filter);
}

static inline void nvnSamplerBuilderSetLodSnap(NVNsamplerBuilder* builder, float f) {
    pfnc_nvnSamplerBuilderSetLodSnap(builder, f);
}

static inline void nvnSamplerBuilderGetMinMagFilter(const NVNsamplerBuilder* builder,
                                                    NVNminFilter* min, NVNmagFilter* mag) {
    pfnc_nvnSamplerBuilderGetMinMagFilter(builder, min, mag);
}

static inline void nvnSamplerBuilderGetWrapMode(const NVNsamplerBuilder* builder, NVNwrapMode* s,
                                                NVNwrapMode* t, NVNwrapMode* r) {
    pfnc_nvnSamplerBuilderGetWrapMode(builder, s, t, r);
}

static inline void nvnSamplerBuilderGetLodClamp(const NVNsamplerBuilder* builder, float* min,
                                                float* max) {
    pfnc_nvnSamplerBuilderGetLodClamp(builder, min, max);
}

static inline float nvnSamplerBuilderGetLodBias(const NVNsamplerBuilder* builder) {
    return pfnc_nvnSamplerBuilderGetLodBias(builder);
}

static inline void nvnSamplerBuilderGetCompare(const NVNsamplerBuilder* builder,
                                               NVNcompareMode* mode, NVNcompareFunc* func) {
    pfnc_nvnSamplerBuilderGetCompare(builder, mode, func);
}

static inline void nvnSamplerBuilderGetBorderColor(const NVNsamplerBuilder* builder,
                                                   float* borderColor) {
    pfnc_nvnSamplerBuilderGetBorderColor(builder, borderColor);
}

static inline void nvnSamplerBuilderGetBorderColori(const NVNsamplerBuilder* builder,
                                                    int* borderColor) {
    pfnc_nvnSamplerBuilderGetBorderColori(builder, borderColor);
}

static inline void nvnSamplerBuilderGetBorderColorui(const NVNsamplerBuilder* builder,
                                                     uint32_t* borderColor) {
    pfnc_nvnSamplerBuilderGetBorderColorui(builder, borderColor);
}

static inline float nvnSamplerBuilderGetMaxAnisotropy(const NVNsamplerBuilder* builder) {
    return pfnc_nvnSamplerBuilderGetMaxAnisotropy(builder);
}

static inline NVNsamplerReduction
nvnSamplerBuilderGetReductionFilter(const NVNsamplerBuilder* builder) {
    return pfnc_nvnSamplerBuilderGetReductionFilter(builder);
}

static inline float nvnSamplerBuilderGetLodSnap(const NVNsamplerBuilder* builder) {
    return pfnc_nvnSamplerBuilderGetLodSnap(builder);
}

static inline NVNboolean nvnSamplerInitialize(NVNsampler* sampler,
                                              const NVNsamplerBuilder* builder) {
    return pfnc_nvnSamplerInitialize(sampler, builder);
}

static inline void nvnSamplerFinalize(NVNsampler* sampler) {
    pfnc_nvnSamplerFinalize(sampler);
}

static inline void nvnSamplerSetDebugLabel(NVNsampler* sampler, const char* label) {
    pfnc_nvnSamplerSetDebugLabel(sampler, label);
}

static inline void nvnSamplerGetMinMagFilter(const NVNsampler* sampler, NVNminFilter* min,
                                             NVNmagFilter* mag) {
    pfnc_nvnSamplerGetMinMagFilter(sampler, min, mag);
}

static inline void nvnSamplerGetWrapMode(const NVNsampler* sampler, NVNwrapMode* s, NVNwrapMode* t,
                                         NVNwrapMode* r) {
    pfnc_nvnSamplerGetWrapMode(sampler, s, t, r);
}

static inline void nvnSamplerGetLodClamp(const NVNsampler* sampler, float* min, float* max) {
    pfnc_nvnSamplerGetLodClamp(sampler, min, max);
}

static inline float nvnSamplerGetLodBias(const NVNsampler* sampler) {
    return pfnc_nvnSamplerGetLodBias(sampler);
}

static inline void nvnSamplerGetCompare(const NVNsampler* sampler, NVNcompareMode* mode,
                                        NVNcompareFunc* func) {
    pfnc_nvnSamplerGetCompare(sampler, mode, func);
}

static inline void nvnSamplerGetBorderColor(const NVNsampler* sampler, float* borderColor) {
    pfnc_nvnSamplerGetBorderColor(sampler, borderColor);
}

static inline void nvnSamplerGetBorderColori(const NVNsampler* sampler, int* borderColor) {
    pfnc_nvnSamplerGetBorderColori(sampler, borderColor);
}

static inline void nvnSamplerGetBorderColorui(const NVNsampler* sampler, uint32_t* borderColor) {
    pfnc_nvnSamplerGetBorderColorui(sampler, borderColor);
}

static inline float nvnSamplerGetMaxAnisotropy(const NVNsampler* sampler) {
    return pfnc_nvnSamplerGetMaxAnisotropy(sampler);
}

static inline NVNsamplerReduction nvnSamplerGetReductionFilter(const NVNsampler* sampler) {
    return pfnc_nvnSamplerGetReductionFilter(sampler);
}

static inline NVNboolean nvnSamplerCompare(const NVNsampler* sampler1, const NVNsampler* sampler2) {
    return pfnc_nvnSamplerCompare(sampler1, sampler2);
}

static inline uint64_t nvnSamplerGetDebugID(const NVNsampler* sampler) {
    return pfnc_nvnSamplerGetDebugID(sampler);
}

static inline void nvnBlendStateSetDefaults(NVNblendState* blend) {
    pfnc_nvnBlendStateSetDefaults(blend);
}

static inline void nvnBlendStateSetBlendTarget(NVNblendState* blend, int target) {
    pfnc_nvnBlendStateSetBlendTarget(blend, target);
}

static inline void nvnBlendStateSetBlendFunc(NVNblendState* blend, NVNblendFunc srcFunc,
                                             NVNblendFunc dstFunc, NVNblendFunc srcFuncAlpha,
                                             NVNblendFunc dstFuncAlpha) {
    pfnc_nvnBlendStateSetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
}

static inline void nvnBlendStateSetBlendEquation(NVNblendState* blend, NVNblendEquation modeRGB,
                                                 NVNblendEquation modeAlpha) {
    pfnc_nvnBlendStateSetBlendEquation(blend, modeRGB, modeAlpha);
}

static inline void nvnBlendStateSetAdvancedMode(NVNblendState* blend, NVNblendAdvancedMode mode) {
    pfnc_nvnBlendStateSetAdvancedMode(blend, mode);
}

static inline void nvnBlendStateSetAdvancedOverlap(NVNblendState* blend,
                                                   NVNblendAdvancedOverlap overlap) {
    pfnc_nvnBlendStateSetAdvancedOverlap(blend, overlap);
}

static inline void nvnBlendStateSetAdvancedPremultipliedSrc(NVNblendState* blend, NVNboolean b) {
    pfnc_nvnBlendStateSetAdvancedPremultipliedSrc(blend, b);
}

static inline void nvnBlendStateSetAdvancedNormalizedDst(NVNblendState* blend, NVNboolean b) {
    pfnc_nvnBlendStateSetAdvancedNormalizedDst(blend, b);
}

static inline int nvnBlendStateGetBlendTarget(const NVNblendState* blend) {
    return pfnc_nvnBlendStateGetBlendTarget(blend);
}

static inline void nvnBlendStateGetBlendFunc(const NVNblendState* blend, NVNblendFunc* srcFunc,
                                             NVNblendFunc* dstFunc, NVNblendFunc* srcFuncAlpha,
                                             NVNblendFunc* dstFuncAlpha) {
    pfnc_nvnBlendStateGetBlendFunc(blend, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
}

static inline void nvnBlendStateGetBlendEquation(const NVNblendState* blend,
                                                 NVNblendEquation* modeRGB,
                                                 NVNblendEquation* modeAlpha) {
    pfnc_nvnBlendStateGetBlendEquation(blend, modeRGB, modeAlpha);
}

static inline NVNblendAdvancedMode nvnBlendStateGetAdvancedMode(const NVNblendState* blend) {
    return pfnc_nvnBlendStateGetAdvancedMode(blend);
}

static inline NVNblendAdvancedOverlap nvnBlendStateGetAdvancedOverlap(const NVNblendState* blend) {
    return pfnc_nvnBlendStateGetAdvancedOverlap(blend);
}

static inline NVNboolean nvnBlendStateGetAdvancedPremultipliedSrc(const NVNblendState* blend) {
    return pfnc_nvnBlendStateGetAdvancedPremultipliedSrc(blend);
}

static inline NVNboolean nvnBlendStateGetAdvancedNormalizedDst(const NVNblendState* blend) {
    return pfnc_nvnBlendStateGetAdvancedNormalizedDst(blend);
}

static inline void nvnColorStateSetDefaults(NVNcolorState* color) {
    pfnc_nvnColorStateSetDefaults(color);
}

static inline void nvnColorStateSetBlendEnable(NVNcolorState* color, int index, NVNboolean enable) {
    pfnc_nvnColorStateSetBlendEnable(color, index, enable);
}

static inline void nvnColorStateSetLogicOp(NVNcolorState* color, NVNlogicOp logicOp) {
    pfnc_nvnColorStateSetLogicOp(color, logicOp);
}

static inline void nvnColorStateSetAlphaTest(NVNcolorState* color, NVNalphaFunc alphaFunc) {
    pfnc_nvnColorStateSetAlphaTest(color, alphaFunc);
}

static inline NVNboolean nvnColorStateGetBlendEnable(const NVNcolorState* color, int index) {
    return pfnc_nvnColorStateGetBlendEnable(color, index);
}

static inline NVNlogicOp nvnColorStateGetLogicOp(const NVNcolorState* color) {
    return pfnc_nvnColorStateGetLogicOp(color);
}

static inline NVNalphaFunc nvnColorStateGetAlphaTest(const NVNcolorState* color) {
    return pfnc_nvnColorStateGetAlphaTest(color);
}

static inline void nvnChannelMaskStateSetDefaults(NVNchannelMaskState* channelMask) {
    pfnc_nvnChannelMaskStateSetDefaults(channelMask);
}

static inline void nvnChannelMaskStateSetChannelMask(NVNchannelMaskState* channelMask, int index,
                                                     NVNboolean r, NVNboolean g, NVNboolean b,
                                                     NVNboolean a) {
    pfnc_nvnChannelMaskStateSetChannelMask(channelMask, index, r, g, b, a);
}

static inline void nvnChannelMaskStateGetChannelMask(const NVNchannelMaskState* channelMask,
                                                     int index, NVNboolean* r, NVNboolean* g,
                                                     NVNboolean* b, NVNboolean* a) {
    pfnc_nvnChannelMaskStateGetChannelMask(channelMask, index, r, g, b, a);
}

static inline void nvnMultisampleStateSetDefaults(NVNmultisampleState* multisample) {
    pfnc_nvnMultisampleStateSetDefaults(multisample);
}

static inline void nvnMultisampleStateSetMultisampleEnable(NVNmultisampleState* multisample,
                                                           NVNboolean enable) {
    pfnc_nvnMultisampleStateSetMultisampleEnable(multisample, enable);
}

static inline void nvnMultisampleStateSetSamples(NVNmultisampleState* multisample, int samples) {
    pfnc_nvnMultisampleStateSetSamples(multisample, samples);
}

static inline void nvnMultisampleStateSetAlphaToCoverageEnable(NVNmultisampleState* multisample,
                                                               NVNboolean enable) {
    pfnc_nvnMultisampleStateSetAlphaToCoverageEnable(multisample, enable);
}

static inline void nvnMultisampleStateSetAlphaToCoverageDither(NVNmultisampleState* multisample,
                                                               NVNboolean enable) {
    pfnc_nvnMultisampleStateSetAlphaToCoverageDither(multisample, enable);
}

static inline NVNboolean
nvnMultisampleStateGetMultisampleEnable(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetMultisampleEnable(multisample);
}

static inline int nvnMultisampleStateGetSamples(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetSamples(multisample);
}

static inline NVNboolean
nvnMultisampleStateGetAlphaToCoverageEnable(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetAlphaToCoverageEnable(multisample);
}

static inline NVNboolean
nvnMultisampleStateGetAlphaToCoverageDither(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetAlphaToCoverageDither(multisample);
}

static inline void nvnMultisampleStateSetRasterSamples(NVNmultisampleState* multisample,
                                                       int samples) {
    pfnc_nvnMultisampleStateSetRasterSamples(multisample, samples);
}

static inline int nvnMultisampleStateGetRasterSamples(NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetRasterSamples(multisample);
}

static inline void nvnMultisampleStateSetCoverageModulationMode(NVNmultisampleState* multisample,
                                                                NVNcoverageModulationMode mode) {
    pfnc_nvnMultisampleStateSetCoverageModulationMode(multisample, mode);
}

static inline NVNcoverageModulationMode
nvnMultisampleStateGetCoverageModulationMode(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetCoverageModulationMode(multisample);
}

static inline void nvnMultisampleStateSetCoverageToColorEnable(NVNmultisampleState* multisample,
                                                               NVNboolean enable) {
    pfnc_nvnMultisampleStateSetCoverageToColorEnable(multisample, enable);
}

static inline NVNboolean
nvnMultisampleStateGetCoverageToColorEnable(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetCoverageToColorEnable(multisample);
}

static inline void nvnMultisampleStateSetCoverageToColorOutput(NVNmultisampleState* multisample,
                                                               int i) {
    pfnc_nvnMultisampleStateSetCoverageToColorOutput(multisample, i);
}

static inline int
nvnMultisampleStateGetCoverageToColorOutput(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetCoverageToColorOutput(multisample);
}

static inline void nvnMultisampleStateSetSampleLocationsEnable(NVNmultisampleState* multisample,
                                                               NVNboolean enable) {
    pfnc_nvnMultisampleStateSetSampleLocationsEnable(multisample, enable);
}

static inline NVNboolean
nvnMultisampleStateGetSampleLocationsEnable(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetSampleLocationsEnable(multisample);
}

static inline void nvnMultisampleStateGetSampleLocationsGrid(NVNmultisampleState* multisample,
                                                             int* w, int* h) {
    pfnc_nvnMultisampleStateGetSampleLocationsGrid(multisample, w, h);
}

static inline void nvnMultisampleStateSetSampleLocationsGridEnable(NVNmultisampleState* multisample,
                                                                   NVNboolean enable) {
    pfnc_nvnMultisampleStateSetSampleLocationsGridEnable(multisample, enable);
}

static inline NVNboolean
nvnMultisampleStateGetSampleLocationsGridEnable(const NVNmultisampleState* multisample) {
    return pfnc_nvnMultisampleStateGetSampleLocationsGridEnable(multisample);
}

static inline void nvnMultisampleStateSetSampleLocations(NVNmultisampleState* multisample, int i1,
                                                         int i2, const float* f) {
    pfnc_nvnMultisampleStateSetSampleLocations(multisample, i1, i2, f);
}

static inline void nvnPolygonStateSetDefaults(NVNpolygonState* polygon) {
    pfnc_nvnPolygonStateSetDefaults(polygon);
}

static inline void nvnPolygonStateSetCullFace(NVNpolygonState* polygon, NVNface face) {
    pfnc_nvnPolygonStateSetCullFace(polygon, face);
}

static inline void nvnPolygonStateSetFrontFace(NVNpolygonState* polygon, NVNfrontFace face) {
    pfnc_nvnPolygonStateSetFrontFace(polygon, face);
}

static inline void nvnPolygonStateSetPolygonMode(NVNpolygonState* polygon,
                                                 NVNpolygonMode polygonMode) {
    pfnc_nvnPolygonStateSetPolygonMode(polygon, polygonMode);
}

static inline void nvnPolygonStateSetPolygonOffsetEnables(NVNpolygonState* polygon, int enables) {
    pfnc_nvnPolygonStateSetPolygonOffsetEnables(polygon, enables);
}

static inline NVNface nvnPolygonStateGetCullFace(const NVNpolygonState* polygon) {
    return pfnc_nvnPolygonStateGetCullFace(polygon);
}

static inline NVNfrontFace nvnPolygonStateGetFrontFace(const NVNpolygonState* polygon) {
    return pfnc_nvnPolygonStateGetFrontFace(polygon);
}

static inline NVNpolygonMode nvnPolygonStateGetPolygonMode(const NVNpolygonState* polygon) {
    return pfnc_nvnPolygonStateGetPolygonMode(polygon);
}

static inline NVNpolygonOffsetEnable
nvnPolygonStateGetPolygonOffsetEnables(const NVNpolygonState* polygon) {
    return pfnc_nvnPolygonStateGetPolygonOffsetEnables(polygon);
}

static inline void nvnDepthStencilStateSetDefaults(NVNdepthStencilState* depthStencil) {
    pfnc_nvnDepthStencilStateSetDefaults(depthStencil);
}

static inline void nvnDepthStencilStateSetDepthTestEnable(NVNdepthStencilState* depthStencil,
                                                          NVNboolean enable) {
    pfnc_nvnDepthStencilStateSetDepthTestEnable(depthStencil, enable);
}

static inline void nvnDepthStencilStateSetDepthWriteEnable(NVNdepthStencilState* depthStencil,
                                                           NVNboolean enable) {
    pfnc_nvnDepthStencilStateSetDepthWriteEnable(depthStencil, enable);
}

static inline void nvnDepthStencilStateSetDepthFunc(NVNdepthStencilState* depthStencil,
                                                    NVNdepthFunc func) {
    pfnc_nvnDepthStencilStateSetDepthFunc(depthStencil, func);
}

static inline void nvnDepthStencilStateSetStencilTestEnable(NVNdepthStencilState* depthStencil,
                                                            NVNboolean enable) {
    pfnc_nvnDepthStencilStateSetStencilTestEnable(depthStencil, enable);
}

static inline void nvnDepthStencilStateSetStencilFunc(NVNdepthStencilState* depthStencil,
                                                      NVNface faces, NVNstencilFunc func) {
    pfnc_nvnDepthStencilStateSetStencilFunc(depthStencil, faces, func);
}

static inline void nvnDepthStencilStateSetStencilOp(NVNdepthStencilState* depthStencil,
                                                    NVNface faces, NVNstencilOp fail,
                                                    NVNstencilOp depthFail,
                                                    NVNstencilOp depthPass) {
    pfnc_nvnDepthStencilStateSetStencilOp(depthStencil, faces, fail, depthFail, depthPass);
}

static inline NVNboolean
nvnDepthStencilStateGetDepthTestEnable(const NVNdepthStencilState* depthStencil) {
    return pfnc_nvnDepthStencilStateGetDepthTestEnable(depthStencil);
}

static inline NVNboolean
nvnDepthStencilStateGetDepthWriteEnable(const NVNdepthStencilState* depthStencil) {
    return pfnc_nvnDepthStencilStateGetDepthWriteEnable(depthStencil);
}

static inline NVNdepthFunc
nvnDepthStencilStateGetDepthFunc(const NVNdepthStencilState* depthStencil) {
    return pfnc_nvnDepthStencilStateGetDepthFunc(depthStencil);
}

static inline NVNboolean
nvnDepthStencilStateGetStencilTestEnable(const NVNdepthStencilState* depthStencil) {
    return pfnc_nvnDepthStencilStateGetStencilTestEnable(depthStencil);
}

static inline NVNstencilFunc
nvnDepthStencilStateGetStencilFunc(const NVNdepthStencilState* depthStencil, NVNface faces) {
    return pfnc_nvnDepthStencilStateGetStencilFunc(depthStencil, faces);
}

static inline void nvnDepthStencilStateGetStencilOp(const NVNdepthStencilState* depthStencil,
                                                    NVNface faces, NVNstencilOp* fail,
                                                    NVNstencilOp* depthFail,
                                                    NVNstencilOp* depthPass) {
    pfnc_nvnDepthStencilStateGetStencilOp(depthStencil, faces, fail, depthFail, depthPass);
}

static inline void nvnVertexAttribStateSetDefaults(NVNvertexAttribState* attrib) {
    pfnc_nvnVertexAttribStateSetDefaults(attrib);
}

static inline void nvnVertexAttribStateSetFormat(NVNvertexAttribState* attrib, NVNformat format,
                                                 ptrdiff_t relativeOffset) {
    pfnc_nvnVertexAttribStateSetFormat(attrib, format, relativeOffset);
}

static inline void nvnVertexAttribStateSetStreamIndex(NVNvertexAttribState* attrib,
                                                      int streamIndex) {
    pfnc_nvnVertexAttribStateSetStreamIndex(attrib, streamIndex);
}

static inline void nvnVertexAttribStateGetFormat(const NVNvertexAttribState* attrib,
                                                 NVNformat* format, ptrdiff_t* relativeOffset) {
    pfnc_nvnVertexAttribStateGetFormat(attrib, format, relativeOffset);
}

static inline int nvnVertexAttribStateGetStreamIndex(const NVNvertexAttribState* attrib) {
    return pfnc_nvnVertexAttribStateGetStreamIndex(attrib);
}

static inline void nvnVertexStreamStateSetDefaults(NVNvertexStreamState* stream) {
    pfnc_nvnVertexStreamStateSetDefaults(stream);
}

static inline void nvnVertexStreamStateSetStride(NVNvertexStreamState* stream, ptrdiff_t stride) {
    pfnc_nvnVertexStreamStateSetStride(stream, stride);
}

static inline void nvnVertexStreamStateSetDivisor(NVNvertexStreamState* stream, int divisor) {
    pfnc_nvnVertexStreamStateSetDivisor(stream, divisor);
}

static inline ptrdiff_t nvnVertexStreamStateGetStride(const NVNvertexStreamState* stream) {
    return pfnc_nvnVertexStreamStateGetStride(stream);
}

static inline int nvnVertexStreamStateGetDivisor(const NVNvertexStreamState* stream) {
    return pfnc_nvnVertexStreamStateGetDivisor(stream);
}

static inline NVNboolean nvnCommandBufferInitialize(NVNcommandBuffer* cmdBuf, NVNdevice* device) {
    return pfnc_nvnCommandBufferInitialize(cmdBuf, device);
}

static inline void nvnCommandBufferFinalize(NVNcommandBuffer* cmdBuf) {
    pfnc_nvnCommandBufferFinalize(cmdBuf);
}

static inline void nvnCommandBufferSetDebugLabel(NVNcommandBuffer* cmdBuf, const char* label) {
    pfnc_nvnCommandBufferSetDebugLabel(cmdBuf, label);
}

static inline void
nvnCommandBufferSetMemoryCallback(NVNcommandBuffer* cmdBuf,
                                  PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC callback) {
    pfnc_nvnCommandBufferSetMemoryCallback(cmdBuf, callback);
}

static inline void nvnCommandBufferSetMemoryCallbackData(NVNcommandBuffer* cmdBuf,
                                                         void* callbackData) {
    pfnc_nvnCommandBufferSetMemoryCallbackData(cmdBuf, callbackData);
}

static inline void nvnCommandBufferAddCommandMemory(NVNcommandBuffer* cmdBuf,
                                                    const NVNmemoryPool* pool, ptrdiff_t offset,
                                                    size_t size) {
    pfnc_nvnCommandBufferAddCommandMemory(cmdBuf, pool, offset, size);
}

static inline void nvnCommandBufferAddControlMemory(NVNcommandBuffer* cmdBuf, void* memory,
                                                    size_t size) {
    pfnc_nvnCommandBufferAddControlMemory(cmdBuf, memory, size);
}

static inline size_t nvnCommandBufferGetCommandMemorySize(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetCommandMemorySize(cmdBuf);
}

static inline size_t nvnCommandBufferGetCommandMemoryUsed(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetCommandMemoryUsed(cmdBuf);
}

static inline size_t nvnCommandBufferGetCommandMemoryFree(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetCommandMemoryFree(cmdBuf);
}

static inline size_t nvnCommandBufferGetControlMemorySize(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetControlMemorySize(cmdBuf);
}

static inline size_t nvnCommandBufferGetControlMemoryUsed(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetControlMemoryUsed(cmdBuf);
}

static inline size_t nvnCommandBufferGetControlMemoryFree(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetControlMemoryFree(cmdBuf);
}

static inline void nvnCommandBufferBeginRecording(NVNcommandBuffer* cmdBuf) {
    pfnc_nvnCommandBufferBeginRecording(cmdBuf);
}

static inline NVNcommandHandle nvnCommandBufferEndRecording(NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferEndRecording(cmdBuf);
}

static inline void nvnCommandBufferCallCommands(NVNcommandBuffer* cmdBuf, int numCommands,
                                                const NVNcommandHandle* handles) {
    pfnc_nvnCommandBufferCallCommands(cmdBuf, numCommands, handles);
}

static inline void nvnCommandBufferCopyCommands(NVNcommandBuffer* cmdBuf, int numCommands,
                                                const NVNcommandHandle* handles) {
    pfnc_nvnCommandBufferCopyCommands(cmdBuf, numCommands, handles);
}

static inline void nvnCommandBufferBindBlendState(NVNcommandBuffer* cmdBuf,
                                                  const NVNblendState* blend) {
    pfnc_nvnCommandBufferBindBlendState(cmdBuf, blend);
}

static inline void nvnCommandBufferBindChannelMaskState(NVNcommandBuffer* cmdBuf,
                                                        const NVNchannelMaskState* channelMask) {
    pfnc_nvnCommandBufferBindChannelMaskState(cmdBuf, channelMask);
}

static inline void nvnCommandBufferBindColorState(NVNcommandBuffer* cmdBuf,
                                                  const NVNcolorState* color) {
    pfnc_nvnCommandBufferBindColorState(cmdBuf, color);
}

static inline void nvnCommandBufferBindMultisampleState(NVNcommandBuffer* cmdBuf,
                                                        const NVNmultisampleState* multisample) {
    pfnc_nvnCommandBufferBindMultisampleState(cmdBuf, multisample);
}

static inline void nvnCommandBufferBindPolygonState(NVNcommandBuffer* cmdBuf,
                                                    const NVNpolygonState* polygon) {
    pfnc_nvnCommandBufferBindPolygonState(cmdBuf, polygon);
}

static inline void nvnCommandBufferBindDepthStencilState(NVNcommandBuffer* cmdBuf,
                                                         const NVNdepthStencilState* depthStencil) {
    pfnc_nvnCommandBufferBindDepthStencilState(cmdBuf, depthStencil);
}

static inline void nvnCommandBufferBindVertexAttribState(NVNcommandBuffer* cmdBuf, int numAttribs,
                                                         const NVNvertexAttribState* attribs) {
    pfnc_nvnCommandBufferBindVertexAttribState(cmdBuf, numAttribs, attribs);
}

static inline void nvnCommandBufferBindVertexStreamState(NVNcommandBuffer* cmdBuf, int numStreams,
                                                         const NVNvertexStreamState* streams) {
    pfnc_nvnCommandBufferBindVertexStreamState(cmdBuf, numStreams, streams);
}

static inline void nvnCommandBufferBindProgram(NVNcommandBuffer* cmdBuf, const NVNprogram* program,
                                               int stages) {
    pfnc_nvnCommandBufferBindProgram(cmdBuf, program, stages);
}

static inline void nvnCommandBufferBindVertexBuffer(NVNcommandBuffer* cmdBuf, int index,
                                                    NVNbufferAddress buffer, size_t size) {
    pfnc_nvnCommandBufferBindVertexBuffer(cmdBuf, index, buffer, size);
}

static inline void nvnCommandBufferBindVertexBuffers(NVNcommandBuffer* cmdBuf, int first, int count,
                                                     const NVNbufferRange* buffers) {
    pfnc_nvnCommandBufferBindVertexBuffers(cmdBuf, first, count, buffers);
}

static inline void nvnCommandBufferBindUniformBuffer(NVNcommandBuffer* cmdBuf, NVNshaderStage stage,
                                                     int index, NVNbufferAddress buffer,
                                                     size_t size) {
    pfnc_nvnCommandBufferBindUniformBuffer(cmdBuf, stage, index, buffer, size);
}

static inline void nvnCommandBufferBindUniformBuffers(NVNcommandBuffer* cmdBuf,
                                                      NVNshaderStage stage, int first, int count,
                                                      const NVNbufferRange* buffers) {
    pfnc_nvnCommandBufferBindUniformBuffers(cmdBuf, stage, first, count, buffers);
}

static inline void nvnCommandBufferBindTransformFeedbackBuffer(NVNcommandBuffer* cmdBuf, int index,
                                                               NVNbufferAddress buffer,
                                                               size_t size) {
    pfnc_nvnCommandBufferBindTransformFeedbackBuffer(cmdBuf, index, buffer, size);
}

static inline void nvnCommandBufferBindTransformFeedbackBuffers(NVNcommandBuffer* cmdBuf, int first,
                                                                int count,
                                                                const NVNbufferRange* buffers) {
    pfnc_nvnCommandBufferBindTransformFeedbackBuffers(cmdBuf, first, count, buffers);
}

static inline void nvnCommandBufferBindStorageBuffer(NVNcommandBuffer* cmdBuf, NVNshaderStage stage,
                                                     int index, NVNbufferAddress buffer,
                                                     size_t size) {
    pfnc_nvnCommandBufferBindStorageBuffer(cmdBuf, stage, index, buffer, size);
}

static inline void nvnCommandBufferBindStorageBuffers(NVNcommandBuffer* cmdBuf,
                                                      NVNshaderStage stage, int first, int count,
                                                      const NVNbufferRange* buffers) {
    pfnc_nvnCommandBufferBindStorageBuffers(cmdBuf, stage, first, count, buffers);
}

static inline void nvnCommandBufferBindTexture(NVNcommandBuffer* cmdBuf, NVNshaderStage stage,
                                               int index, NVNtextureHandle texture) {
    pfnc_nvnCommandBufferBindTexture(cmdBuf, stage, index, texture);
}

static inline void nvnCommandBufferBindTextures(NVNcommandBuffer* cmdBuf, NVNshaderStage stage,
                                                int first, int count,
                                                const NVNtextureHandle* textures) {
    pfnc_nvnCommandBufferBindTextures(cmdBuf, stage, first, count, textures);
}

static inline void nvnCommandBufferBindImage(NVNcommandBuffer* cmdBuf, NVNshaderStage stage,
                                             int index, NVNimageHandle image) {
    pfnc_nvnCommandBufferBindImage(cmdBuf, stage, index, image);
}

static inline void nvnCommandBufferBindImages(NVNcommandBuffer* cmdBuf, NVNshaderStage stage,
                                              int first, int count, const NVNimageHandle* images) {
    pfnc_nvnCommandBufferBindImages(cmdBuf, stage, first, count, images);
}

static inline void nvnCommandBufferSetPatchSize(NVNcommandBuffer* cmdBuf, int i) {
    pfnc_nvnCommandBufferSetPatchSize(cmdBuf, i);
}

static inline void nvnCommandBufferSetInnerTessellationLevels(NVNcommandBuffer* cmdBuf,
                                                              const float* f) {
    pfnc_nvnCommandBufferSetInnerTessellationLevels(cmdBuf, f);
}

static inline void nvnCommandBufferSetOuterTessellationLevels(NVNcommandBuffer* cmdBuf,
                                                              const float* f) {
    pfnc_nvnCommandBufferSetOuterTessellationLevels(cmdBuf, f);
}

static inline void nvnCommandBufferSetPrimitiveRestart(NVNcommandBuffer* cmdBuf, NVNboolean b,
                                                       int i) {
    pfnc_nvnCommandBufferSetPrimitiveRestart(cmdBuf, b, i);
}

static inline void nvnCommandBufferBeginTransformFeedback(NVNcommandBuffer* cmdBuf,
                                                          NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferBeginTransformFeedback(cmdBuf, buffer);
}

static inline void nvnCommandBufferEndTransformFeedback(NVNcommandBuffer* cmdBuf,
                                                        NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferEndTransformFeedback(cmdBuf, buffer);
}

static inline void nvnCommandBufferPauseTransformFeedback(NVNcommandBuffer* cmdBuf,
                                                          NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferPauseTransformFeedback(cmdBuf, buffer);
}

static inline void nvnCommandBufferResumeTransformFeedback(NVNcommandBuffer* cmdBuf,
                                                           NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferResumeTransformFeedback(cmdBuf, buffer);
}

static inline void nvnCommandBufferDrawTransformFeedback(NVNcommandBuffer* cmdBuf,
                                                         NVNdrawPrimitive mode,
                                                         NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferDrawTransformFeedback(cmdBuf, mode, buffer);
}

static inline void nvnCommandBufferDrawArrays(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode,
                                              int first, int count) {
    pfnc_nvnCommandBufferDrawArrays(cmdBuf, mode, first, count);
}

static inline void nvnCommandBufferDrawElements(NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode,
                                                NVNindexType type, int count,
                                                NVNbufferAddress indexBuffer) {
    pfnc_nvnCommandBufferDrawElements(cmdBuf, mode, type, count, indexBuffer);
}

static inline void nvnCommandBufferDrawElementsBaseVertex(NVNcommandBuffer* cmdBuf,
                                                          NVNdrawPrimitive mode, NVNindexType type,
                                                          int count, NVNbufferAddress indexBuffer,
                                                          int baseVertex) {
    pfnc_nvnCommandBufferDrawElementsBaseVertex(cmdBuf, mode, type, count, indexBuffer, baseVertex);
}

static inline void nvnCommandBufferDrawArraysInstanced(NVNcommandBuffer* cmdBuf,
                                                       NVNdrawPrimitive mode, int first, int count,
                                                       int baseInstance, int instanceCount) {
    pfnc_nvnCommandBufferDrawArraysInstanced(cmdBuf, mode, first, count, baseInstance,
                                             instanceCount);
}

static inline void nvnCommandBufferDrawElementsInstanced(NVNcommandBuffer* cmdBuf,
                                                         NVNdrawPrimitive mode, NVNindexType type,
                                                         int count, NVNbufferAddress indexBuffer,
                                                         int baseVertex, int baseInstance,
                                                         int instanceCount) {
    pfnc_nvnCommandBufferDrawElementsInstanced(cmdBuf, mode, type, count, indexBuffer, baseVertex,
                                               baseInstance, instanceCount);
}

static inline void nvnCommandBufferDrawArraysIndirect(NVNcommandBuffer* cmdBuf,
                                                      NVNdrawPrimitive mode,
                                                      NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferDrawArraysIndirect(cmdBuf, mode, buffer);
}

static inline void nvnCommandBufferDrawElementsIndirect(NVNcommandBuffer* cmdBuf,
                                                        NVNdrawPrimitive mode, NVNindexType type,
                                                        NVNbufferAddress buffer1,
                                                        NVNbufferAddress buffer2) {
    pfnc_nvnCommandBufferDrawElementsIndirect(cmdBuf, mode, type, buffer1, buffer2);
}

static inline void nvnCommandBufferMultiDrawArraysIndirectCount(NVNcommandBuffer* cmdBuf,
                                                                NVNdrawPrimitive mode,
                                                                NVNbufferAddress buffer1,
                                                                NVNbufferAddress buffer2, int i,
                                                                ptrdiff_t o) {
    pfnc_nvnCommandBufferMultiDrawArraysIndirectCount(cmdBuf, mode, buffer1, buffer2, i, o);
}

static inline void nvnCommandBufferMultiDrawElementsIndirectCount(
    NVNcommandBuffer* cmdBuf, NVNdrawPrimitive mode, NVNindexType type, NVNbufferAddress buffer1,
    NVNbufferAddress buffer2, NVNbufferAddress buffer3, int i, ptrdiff_t o) {
    pfnc_nvnCommandBufferMultiDrawElementsIndirectCount(cmdBuf, mode, type, buffer1, buffer2,
                                                        buffer3, i, o);
}

static inline void nvnCommandBufferClearColor(NVNcommandBuffer* cmdBuf, int index,
                                              const float* color, int mask) {
    pfnc_nvnCommandBufferClearColor(cmdBuf, index, color, mask);
}

static inline void nvnCommandBufferClearColori(NVNcommandBuffer* cmdBuf, int index,
                                               const int* color, int mask) {
    pfnc_nvnCommandBufferClearColori(cmdBuf, index, color, mask);
}

static inline void nvnCommandBufferClearColorui(NVNcommandBuffer* cmdBuf, int index,
                                                const uint32_t* color, int mask) {
    pfnc_nvnCommandBufferClearColorui(cmdBuf, index, color, mask);
}

static inline void nvnCommandBufferClearDepthStencil(NVNcommandBuffer* cmdBuf, float depthValue,
                                                     NVNboolean depthMask, int stencilValue,
                                                     int stencilMask) {
    pfnc_nvnCommandBufferClearDepthStencil(cmdBuf, depthValue, depthMask, stencilValue,
                                           stencilMask);
}

static inline void nvnCommandBufferDispatchCompute(NVNcommandBuffer* cmdBuf, int groupsX,
                                                   int groupsY, int groupsZ) {
    pfnc_nvnCommandBufferDispatchCompute(cmdBuf, groupsX, groupsY, groupsZ);
}

static inline void nvnCommandBufferDispatchComputeIndirect(NVNcommandBuffer* cmdBuf,
                                                           NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferDispatchComputeIndirect(cmdBuf, buffer);
}

static inline void nvnCommandBufferSetViewport(NVNcommandBuffer* cmdBuf, int x, int y, int w,
                                               int h) {
    pfnc_nvnCommandBufferSetViewport(cmdBuf, x, y, w, h);
}

static inline void nvnCommandBufferSetViewports(NVNcommandBuffer* cmdBuf, int first, int count,
                                                const float* ranges) {
    pfnc_nvnCommandBufferSetViewports(cmdBuf, first, count, ranges);
}

static inline void nvnCommandBufferSetViewportSwizzles(NVNcommandBuffer* cmdBuf, int first,
                                                       int count,
                                                       const NVNviewportSwizzle* swizzles) {
    pfnc_nvnCommandBufferSetViewportSwizzles(cmdBuf, first, count, swizzles);
}

static inline void nvnCommandBufferSetScissor(NVNcommandBuffer* cmdBuf, int x, int y, int w,
                                              int h) {
    pfnc_nvnCommandBufferSetScissor(cmdBuf, x, y, w, h);
}

static inline void nvnCommandBufferSetScissors(NVNcommandBuffer* cmdBuf, int first, int count,
                                               const int* rects) {
    pfnc_nvnCommandBufferSetScissors(cmdBuf, first, count, rects);
}

static inline void nvnCommandBufferSetDepthRange(NVNcommandBuffer* cmdBuf, float n, float f) {
    pfnc_nvnCommandBufferSetDepthRange(cmdBuf, n, f);
}

static inline void nvnCommandBufferSetDepthBounds(NVNcommandBuffer* cmdBuf, NVNboolean enable,
                                                  float n, float f) {
    pfnc_nvnCommandBufferSetDepthBounds(cmdBuf, enable, n, f);
}

static inline void nvnCommandBufferSetDepthRanges(NVNcommandBuffer* cmdBuf, int first, int count,
                                                  const float* ranges) {
    pfnc_nvnCommandBufferSetDepthRanges(cmdBuf, first, count, ranges);
}

static inline void nvnCommandBufferSetTiledCacheAction(NVNcommandBuffer* cmdBuf,
                                                       NVNtiledCacheAction action) {
    pfnc_nvnCommandBufferSetTiledCacheAction(cmdBuf, action);
}

static inline void nvnCommandBufferSetTiledCacheTileSize(NVNcommandBuffer* cmdBuf, int w, int h) {
    pfnc_nvnCommandBufferSetTiledCacheTileSize(cmdBuf, w, h);
}

static inline void nvnCommandBufferBindSeparateTexture(NVNcommandBuffer* cmdBuf,
                                                       NVNshaderStage stage, int i,
                                                       NVNseparateTextureHandle handle) {
    pfnc_nvnCommandBufferBindSeparateTexture(cmdBuf, stage, i, handle);
}

static inline void nvnCommandBufferBindSeparateSampler(NVNcommandBuffer* cmdBuf,
                                                       NVNshaderStage stage, int i,
                                                       NVNseparateSamplerHandle handle) {
    pfnc_nvnCommandBufferBindSeparateSampler(cmdBuf, stage, i, handle);
}

static inline void nvnCommandBufferBindSeparateTextures(NVNcommandBuffer* cmdBuf,
                                                        NVNshaderStage stage, int i1, int i2,
                                                        const NVNseparateTextureHandle* handle) {
    pfnc_nvnCommandBufferBindSeparateTextures(cmdBuf, stage, i1, i2, handle);
}

static inline void nvnCommandBufferBindSeparateSamplers(NVNcommandBuffer* cmdBuf,
                                                        NVNshaderStage stage, int i1, int i2,
                                                        const NVNseparateSamplerHandle* handle) {
    pfnc_nvnCommandBufferBindSeparateSamplers(cmdBuf, stage, i1, i2, handle);
}

static inline void nvnCommandBufferSetStencilValueMask(NVNcommandBuffer* cmdBuf, NVNface faces,
                                                       int mask) {
    pfnc_nvnCommandBufferSetStencilValueMask(cmdBuf, faces, mask);
}

static inline void nvnCommandBufferSetStencilMask(NVNcommandBuffer* cmdBuf, NVNface faces,
                                                  int mask) {
    pfnc_nvnCommandBufferSetStencilMask(cmdBuf, faces, mask);
}

static inline void nvnCommandBufferSetStencilRef(NVNcommandBuffer* cmdBuf, NVNface faces, int ref) {
    pfnc_nvnCommandBufferSetStencilRef(cmdBuf, faces, ref);
}

static inline void nvnCommandBufferSetBlendColor(NVNcommandBuffer* cmdBuf,
                                                 const float* blendColor) {
    pfnc_nvnCommandBufferSetBlendColor(cmdBuf, blendColor);
}

static inline void nvnCommandBufferSetPointSize(NVNcommandBuffer* cmdBuf, float pointSize) {
    pfnc_nvnCommandBufferSetPointSize(cmdBuf, pointSize);
}

static inline void nvnCommandBufferSetLineWidth(NVNcommandBuffer* cmdBuf, float lineWidth) {
    pfnc_nvnCommandBufferSetLineWidth(cmdBuf, lineWidth);
}

static inline void nvnCommandBufferSetPolygonOffsetClamp(NVNcommandBuffer* cmdBuf, float factor,
                                                         float units, float clamp) {
    pfnc_nvnCommandBufferSetPolygonOffsetClamp(cmdBuf, factor, units, clamp);
}

static inline void nvnCommandBufferSetAlphaRef(NVNcommandBuffer* cmdBuf, float ref) {
    pfnc_nvnCommandBufferSetAlphaRef(cmdBuf, ref);
}

static inline void nvnCommandBufferSetSampleMask(NVNcommandBuffer* cmdBuf, int mask) {
    pfnc_nvnCommandBufferSetSampleMask(cmdBuf, mask);
}

static inline void nvnCommandBufferSetRasterizerDiscard(NVNcommandBuffer* cmdBuf,
                                                        NVNboolean discard) {
    pfnc_nvnCommandBufferSetRasterizerDiscard(cmdBuf, discard);
}

static inline void nvnCommandBufferSetDepthClamp(NVNcommandBuffer* cmdBuf, NVNboolean clamp) {
    pfnc_nvnCommandBufferSetDepthClamp(cmdBuf, clamp);
}

static inline void nvnCommandBufferSetConservativeRasterEnable(NVNcommandBuffer* cmdBuf,
                                                               NVNboolean enable) {
    pfnc_nvnCommandBufferSetConservativeRasterEnable(cmdBuf, enable);
}

static inline void nvnCommandBufferSetConservativeRasterDilate(NVNcommandBuffer* cmdBuf, float f) {
    pfnc_nvnCommandBufferSetConservativeRasterDilate(cmdBuf, f);
}

static inline void nvnCommandBufferSetSubpixelPrecisionBias(NVNcommandBuffer* cmdBuf, int i1,
                                                            int i2) {
    pfnc_nvnCommandBufferSetSubpixelPrecisionBias(cmdBuf, i1, i2);
}

static inline void nvnCommandBufferCopyBufferToTexture(NVNcommandBuffer* cmdBuf,
                                                       NVNbufferAddress buffer,
                                                       const NVNtexture* dstTexture,
                                                       const NVNtextureView* dstView,
                                                       const NVNcopyRegion* dstRegion, int flags) {
    pfnc_nvnCommandBufferCopyBufferToTexture(cmdBuf, buffer, dstTexture, dstView, dstRegion, flags);
}

static inline void nvnCommandBufferCopyTextureToBuffer(NVNcommandBuffer* cmdBuf,
                                                       const NVNtexture* srcTexture,
                                                       const NVNtextureView* srcView,
                                                       const NVNcopyRegion* srcRegion,
                                                       NVNbufferAddress buffer, int flags) {
    pfnc_nvnCommandBufferCopyTextureToBuffer(cmdBuf, srcTexture, srcView, srcRegion, buffer, flags);
}

static inline void
nvnCommandBufferCopyTextureToTexture(NVNcommandBuffer* cmdBuf, const NVNtexture* srcTexture,
                                     const NVNtextureView* srcView, const NVNcopyRegion* srcRegion,
                                     const NVNtexture* dstTexture, const NVNtextureView* dstView,
                                     const NVNcopyRegion* dstRegion, int flags) {
    pfnc_nvnCommandBufferCopyTextureToTexture(cmdBuf, srcTexture, srcView, srcRegion, dstTexture,
                                              dstView, dstRegion, flags);
}

static inline void nvnCommandBufferCopyBufferToBuffer(NVNcommandBuffer* cmdBuf,
                                                      NVNbufferAddress src, NVNbufferAddress dst,
                                                      size_t size, int flags) {
    pfnc_nvnCommandBufferCopyBufferToBuffer(cmdBuf, src, dst, size, flags);
}

static inline void nvnCommandBufferClearBuffer(NVNcommandBuffer* cmdBuf, NVNbufferAddress buffer,
                                               size_t size, uint32_t i) {
    pfnc_nvnCommandBufferClearBuffer(cmdBuf, buffer, size, i);
}

static inline void nvnCommandBufferClearTexture(NVNcommandBuffer* cmdBuf,
                                                const NVNtexture* dstTexture,
                                                const NVNtextureView* dstView,
                                                const NVNcopyRegion* dstRegion, const float* color,
                                                int mask) {
    pfnc_nvnCommandBufferClearTexture(cmdBuf, dstTexture, dstView, dstRegion, color, mask);
}

static inline void nvnCommandBufferClearTexturei(NVNcommandBuffer* cmdBuf,
                                                 const NVNtexture* dstTexture,
                                                 const NVNtextureView* dstView,
                                                 const NVNcopyRegion* dstRegion, const int* color,
                                                 int mask) {
    pfnc_nvnCommandBufferClearTexturei(cmdBuf, dstTexture, dstView, dstRegion, color, mask);
}

static inline void nvnCommandBufferClearTextureui(NVNcommandBuffer* cmdBuf,
                                                  const NVNtexture* dstTexture,
                                                  const NVNtextureView* dstView,
                                                  const NVNcopyRegion* dstRegion,
                                                  const uint32_t* color, int mask) {
    pfnc_nvnCommandBufferClearTextureui(cmdBuf, dstTexture, dstView, dstRegion, color, mask);
}

static inline void nvnCommandBufferUpdateUniformBuffer(NVNcommandBuffer* cmdBuf,
                                                       NVNbufferAddress buffer, size_t size,
                                                       ptrdiff_t o, size_t s, const void* p) {
    pfnc_nvnCommandBufferUpdateUniformBuffer(cmdBuf, buffer, size, o, s, p);
}

static inline void nvnCommandBufferReportCounter(NVNcommandBuffer* cmdBuf, NVNcounterType counter,
                                                 NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferReportCounter(cmdBuf, counter, buffer);
}

static inline void nvnCommandBufferResetCounter(NVNcommandBuffer* cmdBuf, NVNcounterType counter) {
    pfnc_nvnCommandBufferResetCounter(cmdBuf, counter);
}

static inline void nvnCommandBufferReportValue(NVNcommandBuffer* cmdBuf, uint32_t value,
                                               NVNbufferAddress buffer) {
    pfnc_nvnCommandBufferReportValue(cmdBuf, value, buffer);
}

static inline void nvnCommandBufferSetRenderEnable(NVNcommandBuffer* cmdBuf, NVNboolean enable) {
    pfnc_nvnCommandBufferSetRenderEnable(cmdBuf, enable);
}

static inline void nvnCommandBufferSetRenderEnableConditional(NVNcommandBuffer* cmdBuf,
                                                              NVNconditionalRenderMode mode,
                                                              NVNbufferAddress addr) {
    pfnc_nvnCommandBufferSetRenderEnableConditional(cmdBuf, mode, addr);
}

static inline void nvnCommandBufferSetRenderTargets(NVNcommandBuffer* cmdBuf, int numColors,
                                                    const NVNtexture* const* colors,
                                                    const NVNtextureView* const* colorViews,
                                                    const NVNtexture* depthStencil,
                                                    const NVNtextureView* depthStencilView) {
    pfnc_nvnCommandBufferSetRenderTargets(cmdBuf, numColors, colors, colorViews, depthStencil,
                                          depthStencilView);
}

static inline void nvnCommandBufferDiscardColor(NVNcommandBuffer* cmdBuf, int i) {
    pfnc_nvnCommandBufferDiscardColor(cmdBuf, i);
}

static inline void nvnCommandBufferDiscardDepthStencil(NVNcommandBuffer* cmdBuf) {
    pfnc_nvnCommandBufferDiscardDepthStencil(cmdBuf);
}

static inline void nvnCommandBufferDownsample(NVNcommandBuffer* cmdBuf, const NVNtexture* src,
                                              const NVNtexture* dst) {
    pfnc_nvnCommandBufferDownsample(cmdBuf, src, dst);
}

static inline void nvnCommandBufferTiledDownsample(NVNcommandBuffer* cmdBuf,
                                                   const NVNtexture* texture1,
                                                   const NVNtexture* texture2) {
    pfnc_nvnCommandBufferTiledDownsample(cmdBuf, texture1, texture2);
}

static inline void nvnCommandBufferDownsampleTextureView(NVNcommandBuffer* cmdBuf,
                                                         const NVNtexture* texture1,
                                                         const NVNtextureView* view1,
                                                         const NVNtexture* texture2,
                                                         const NVNtextureView* view2) {
    pfnc_nvnCommandBufferDownsampleTextureView(cmdBuf, texture1, view1, texture2, view2);
}

static inline void nvnCommandBufferTiledDownsampleTextureView(NVNcommandBuffer* cmdBuf,
                                                              const NVNtexture* texture1,
                                                              const NVNtextureView* view1,
                                                              const NVNtexture* texture2,
                                                              const NVNtextureView* view2) {
    pfnc_nvnCommandBufferTiledDownsampleTextureView(cmdBuf, texture1, view1, texture2, view2);
}

static inline void nvnCommandBufferBarrier(NVNcommandBuffer* cmdBuf, int barrier) {
    pfnc_nvnCommandBufferBarrier(cmdBuf, barrier);
}

static inline void nvnCommandBufferWaitSync(NVNcommandBuffer* cmdBuf, const NVNsync* sync) {
    pfnc_nvnCommandBufferWaitSync(cmdBuf, sync);
}

static inline void nvnCommandBufferFenceSync(NVNcommandBuffer* cmdBuf, NVNsync* sync,
                                             NVNsyncCondition condition, int fence) {
    pfnc_nvnCommandBufferFenceSync(cmdBuf, sync, condition, fence);
}

static inline void nvnCommandBufferSetTexturePool(NVNcommandBuffer* cmdBuf,
                                                  const NVNtexturePool* pool) {
    pfnc_nvnCommandBufferSetTexturePool(cmdBuf, pool);
}

static inline void nvnCommandBufferSetSamplerPool(NVNcommandBuffer* cmdBuf,
                                                  const NVNsamplerPool* pool) {
    pfnc_nvnCommandBufferSetSamplerPool(cmdBuf, pool);
}

static inline void nvnCommandBufferSetShaderScratchMemory(NVNcommandBuffer* cmdBuf,
                                                          const NVNmemoryPool* pool,
                                                          ptrdiff_t offset, size_t size) {
    pfnc_nvnCommandBufferSetShaderScratchMemory(cmdBuf, pool, offset, size);
}

static inline void nvnCommandBufferSaveZCullData(NVNcommandBuffer* cmdBuf, NVNbufferAddress addr,
                                                 size_t size) {
    pfnc_nvnCommandBufferSaveZCullData(cmdBuf, addr, size);
}

static inline void nvnCommandBufferRestoreZCullData(NVNcommandBuffer* cmdBuf, NVNbufferAddress addr,
                                                    size_t size) {
    pfnc_nvnCommandBufferRestoreZCullData(cmdBuf, addr, size);
}

static inline void nvnCommandBufferSetCopyRowStride(NVNcommandBuffer* cmdBuf, ptrdiff_t stride) {
    pfnc_nvnCommandBufferSetCopyRowStride(cmdBuf, stride);
}

static inline void nvnCommandBufferSetCopyImageStride(NVNcommandBuffer* cmdBuf, ptrdiff_t stride) {
    pfnc_nvnCommandBufferSetCopyImageStride(cmdBuf, stride);
}

static inline ptrdiff_t nvnCommandBufferGetCopyRowStride(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetCopyRowStride(cmdBuf);
}

static inline ptrdiff_t nvnCommandBufferGetCopyImageStride(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetCopyImageStride(cmdBuf);
}

static inline void nvnCommandBufferDrawTexture(NVNcommandBuffer* cmdBuf, NVNtextureHandle handle,
                                               const NVNdrawTextureRegion* region1,
                                               const NVNdrawTextureRegion* region2) {
    pfnc_nvnCommandBufferDrawTexture(cmdBuf, handle, region1, region2);
}

static inline NVNboolean nvnProgramSetSubroutineLinkage(NVNprogram* program, int i,
                                                        const NVNsubroutineLinkageMapPtr* ptr) {
    return pfnc_nvnProgramSetSubroutineLinkage(program, i, ptr);
}

static inline void nvnCommandBufferSetProgramSubroutines(NVNcommandBuffer* cmdBuf,
                                                         NVNprogram* program, NVNshaderStage stage,
                                                         const int i1, const int i2,
                                                         const int* i3) {
    pfnc_nvnCommandBufferSetProgramSubroutines(cmdBuf, program, stage, i1, i2, i3);
}

static inline void nvnCommandBufferBindCoverageModulationTable(NVNcommandBuffer* cmdBuf,
                                                               const float* f) {
    pfnc_nvnCommandBufferBindCoverageModulationTable(cmdBuf, f);
}

static inline void nvnCommandBufferResolveDepthBuffer(NVNcommandBuffer* cmdBuf) {
    pfnc_nvnCommandBufferResolveDepthBuffer(cmdBuf);
}

static inline void nvnCommandBufferPushDebugGroupStatic(NVNcommandBuffer* cmdBuf, uint32_t i,
                                                        const char* description) {
    pfnc_nvnCommandBufferPushDebugGroupStatic(cmdBuf, i, description);
}

static inline void nvnCommandBufferPushDebugGroupDynamic(NVNcommandBuffer* cmdBuf, uint32_t i,
                                                         const char* description) {
    pfnc_nvnCommandBufferPushDebugGroupDynamic(cmdBuf, i, description);
}

static inline void nvnCommandBufferPushDebugGroup(NVNcommandBuffer* cmdBuf, uint32_t i,
                                                  const char* description) {
    pfnc_nvnCommandBufferPushDebugGroup(cmdBuf, i, description);
}

static inline void nvnCommandBufferPopDebugGroup(NVNcommandBuffer* cmdBuf) {
    pfnc_nvnCommandBufferPopDebugGroup(cmdBuf);
}

static inline void nvnCommandBufferPopDebugGroupId(NVNcommandBuffer* cmdBuf, uint32_t i) {
    pfnc_nvnCommandBufferPopDebugGroupId(cmdBuf, i);
}

static inline void nvnCommandBufferInsertDebugMarkerStatic(NVNcommandBuffer* cmdBuf, uint32_t i,
                                                           const char* description) {
    pfnc_nvnCommandBufferInsertDebugMarkerStatic(cmdBuf, i, description);
}

static inline void nvnCommandBufferInsertDebugMarkerDynamic(NVNcommandBuffer* cmdBuf, uint32_t i,
                                                            const char* description) {
    pfnc_nvnCommandBufferInsertDebugMarkerDynamic(cmdBuf, i, description);
}

static inline void nvnCommandBufferInsertDebugMarker(NVNcommandBuffer* cmdBuf,
                                                     const char* description) {
    pfnc_nvnCommandBufferInsertDebugMarker(cmdBuf, description);
}

static inline PFNNVNCOMMANDBUFFERMEMORYCALLBACKPROC
nvnCommandBufferGetMemoryCallback(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferGetMemoryCallback(cmdBuf);
}

static inline void nvnCommandBufferGetMemoryCallbackData(const NVNcommandBuffer* cmdBuf) {
    pfnc_nvnCommandBufferGetMemoryCallbackData(cmdBuf);
}

static inline NVNboolean nvnCommandBufferIsRecording(const NVNcommandBuffer* cmdBuf) {
    return pfnc_nvnCommandBufferIsRecording(cmdBuf);
}

static inline NVNboolean nvnSyncInitialize(NVNsync* sync, NVNdevice* device) {
    return pfnc_nvnSyncInitialize(sync, device);
}

static inline void nvnSyncFinalize(NVNsync* sync) {
    pfnc_nvnSyncFinalize(sync);
}

static inline void nvnSyncSetDebugLabel(NVNsync* sync, const char* label) {
    pfnc_nvnSyncSetDebugLabel(sync, label);
}

static inline void nvnQueueFenceSync(NVNqueue* queue, NVNsync* sync, NVNsyncCondition condition,
                                     int flags) {
    pfnc_nvnQueueFenceSync(queue, sync, condition, flags);
}

static inline NVNsyncWaitResult nvnSyncWait(const NVNsync* sync, uint64_t timeoutNs) {
    return pfnc_nvnSyncWait(sync, timeoutNs);
}

static inline NVNboolean nvnQueueWaitSync(NVNqueue* queue, const NVNsync* sync) {
    return pfnc_nvnQueueWaitSync(queue, sync);
}

static inline void nvnEventBuilderSetDefaults(NVNeventBuilder* builder) {
    pfnc_nvnEventBuilderSetDefaults(builder);
}

static inline void nvnEventBuilderSetStorage(NVNeventBuilder* builder, const NVNmemoryPool* pool,
                                             int64_t size) {
    pfnc_nvnEventBuilderSetStorage(builder, pool, size);
}

static inline NVNboolean nvnEventInitialize(NVNevent* event, const NVNeventBuilder* builder) {
    return pfnc_nvnEventInitialize(event, builder);
}

static inline void nvnEventFinalize(NVNevent* event) {
    pfnc_nvnEventFinalize(event);
}

static inline uint32_t nvnEventGetValue(const NVNevent* event) {
    return pfnc_nvnEventGetValue(event);
}

static inline void nvnEventSignal(NVNevent* event, NVNeventSignalMode mode, uint32_t i) {
    pfnc_nvnEventSignal(event, mode, i);
}

static inline void nvnCommandBufferWaitEvent(NVNcommandBuffer* cmdBuf, const NVNevent* event,
                                             NVNeventWaitMode mode, uint32_t i) {
    pfnc_nvnCommandBufferWaitEvent(cmdBuf, event, mode, i);
}

static inline void nvnCommandBufferSignalEvent(NVNcommandBuffer* cmdBuf, const NVNevent* event,
                                               NVNeventSignalMode mode,
                                               NVNeventSignalLocation location, int flags,
                                               uint32_t i) {
    pfnc_nvnCommandBufferSignalEvent(cmdBuf, event, mode, location, flags, i);
}

#ifdef __cplusplus
}
#endif