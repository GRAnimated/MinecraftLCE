#pragma once

#include <nvn/nvn_Cpp.h>
#include <nvn/nvn_CppFuncPtrBase.h>

namespace nvn {

inline void DeviceBuilder::SetDefaults() {
    pfncpp_nvnDeviceBuilderSetDefaults(this);
}

inline void DeviceBuilder::SetFlags(DeviceFlagBits flags) {
    pfncpp_nvnDeviceBuilderSetFlags(this, flags);
}

inline DeviceFlagBits DeviceBuilder::GetFlags() const {
    return pfncpp_nvnDeviceBuilderGetFlags(this);
}

inline NVNboolean Device::Initialize(const DeviceBuilder* builder) {
    return pfncpp_nvnDeviceInitialize(this, builder);
}

inline void Device::Finalize() {
    pfncpp_nvnDeviceFinalize(this);
}

inline void Device::SetDebugLabel(const char* label) {
    pfncpp_nvnDeviceSetDebugLabel(this, label);
}

inline GenericFuncPtrFunc Device::GetProcAddress(const char* s) const {
    return pfncpp_nvnDeviceGetProcAddress(this, s);
}

inline void Device::GetInteger(DeviceInfo pname, int* v) const {
    pfncpp_nvnDeviceGetInteger(this, pname, v);
}

inline uint64_t Device::GetCurrentTimestampInNanoseconds() const {
    return pfncpp_nvnDeviceGetCurrentTimestampInNanoseconds(this);
}

inline void Device::SetIntermediateShaderCache(int i) {
    pfncpp_nvnDeviceSetIntermediateShaderCache(this, i);
}

inline TextureHandle Device::GetTextureHandle(int textureID, int samplerID) const {
    return pfncpp_nvnDeviceGetTextureHandle(this, textureID, samplerID);
}

inline TextureHandle Device::GetTexelFetchHandle(int textureID) const {
    return pfncpp_nvnDeviceGetTexelFetchHandle(this, textureID);
}

inline ImageHandle Device::GetImageHandle(int textureID) const {
    return pfncpp_nvnDeviceGetImageHandle(this, textureID);
}

inline void Device::InstallDebugCallback(const DebugCallbackFunc callback, void* callbackData,
                                         NVNboolean enable) {
    pfncpp_nvnDeviceInstallDebugCallback(this, callback, callbackData, enable);
}

inline NVNdebugDomainId Device::GenerateDebugDomainId(const char* s) const {
    return pfncpp_nvnDeviceGenerateDebugDomainId(this, s);
}

inline void Device::SetWindowOriginMode(WindowOriginMode windowOriginMode) {
    pfncpp_nvnDeviceSetWindowOriginMode(this, windowOriginMode);
}

inline void Device::SetDepthMode(DepthMode depthMode) {
    pfncpp_nvnDeviceSetDepthMode(this, depthMode);
}

inline NVNboolean Device::RegisterFastClearColor(const float* color, Format format) {
    return pfncpp_nvnDeviceRegisterFastClearColor(this, color, format);
}

inline NVNboolean Device::RegisterFastClearColori(const int* color, Format format) {
    return pfncpp_nvnDeviceRegisterFastClearColori(this, color, format);
}

inline NVNboolean Device::RegisterFastClearColorui(const uint32_t* color, Format format) {
    return pfncpp_nvnDeviceRegisterFastClearColorui(this, color, format);
}

inline NVNboolean Device::RegisterFastClearDepth(float f) {
    return pfncpp_nvnDeviceRegisterFastClearDepth(this, f);
}

inline WindowOriginMode Device::GetWindowOriginMode() const {
    return pfncpp_nvnDeviceGetWindowOriginMode(this);
}

inline DepthMode Device::GetDepthMode() const {
    return pfncpp_nvnDeviceGetDepthMode(this);
}

inline uint64_t Device::GetTimestampInNanoseconds(const CounterData* counterData) const {
    return pfncpp_nvnDeviceGetTimestampInNanoseconds(this, counterData);
}

inline void Device::ApplyDeferredFinalizes(int i) {
    pfncpp_nvnDeviceApplyDeferredFinalizes(this, i);
}

inline void Device::FinalizeCommandHandle(CommandHandle handles) {
    pfncpp_nvnDeviceFinalizeCommandHandle(this, handles);
}

inline void Device::WalkDebugDatabase(DebugObjectType debugObjectType,
                                      WalkDebugDatabaseCallbackFunc callback,
                                      void* callbackData) const {
    pfncpp_nvnDeviceWalkDebugDatabase(this, debugObjectType, callback, callbackData);
}

inline SeparateTextureHandle Device::GetSeparateTextureHandle(int textureID) const {
    return pfncpp_nvnDeviceGetSeparateTextureHandle(this, textureID);
}

inline SeparateTextureHandle Device::getSeparateTextureHandle(int textureID) const {
    return pfncpp_nvnDeviceGetSeparateTextureHandle(this, textureID);
}

inline SeparateSamplerHandle Device::GetSeparateSamplerHandle(int samplerID) const {
    return pfncpp_nvnDeviceGetSeparateSamplerHandle(this, samplerID);
}

inline SeparateSamplerHandle Device::getSeparateSamplerHandle(int samplerID) const {
    return pfncpp_nvnDeviceGetSeparateSamplerHandle(this, samplerID);
}

inline NVNboolean Device::IsExternalDebuggerAttached() const {
    return pfncpp_nvnDeviceIsExternalDebuggerAttached(this);
}

inline QueueBuilder& QueueBuilder::SetDevice(Device* device) {
    pfncpp_nvnQueueBuilderSetDevice(this, device);
    return *this;
}

inline QueueBuilder& QueueBuilder::SetDefaults() {
    pfncpp_nvnQueueBuilderSetDefaults(this);
    return *this;
}

inline QueueBuilder& QueueBuilder::SetFlags(QueueFlags flags) {
    pfncpp_nvnQueueBuilderSetFlags(this, flags);
    return *this;
}

inline QueueBuilder& QueueBuilder::SetCommandMemorySize(size_t size) {
    pfncpp_nvnQueueBuilderSetCommandMemorySize(this, size);
    return *this;
}

inline QueueBuilder& QueueBuilder::SetComputeMemorySize(size_t size) {
    pfncpp_nvnQueueBuilderSetComputeMemorySize(this, size);
    return *this;
}

inline QueueBuilder& QueueBuilder::SetControlMemorySize(size_t size) {
    pfncpp_nvnQueueBuilderSetControlMemorySize(this, size);
    return *this;
}

inline size_t QueueBuilder::GetQueueMemorySize() const {
    return pfncpp_nvnQueueBuilderGetQueueMemorySize(this);
}

inline QueueBuilder& QueueBuilder::SetQueueMemory(void* memory, size_t size) {
    pfncpp_nvnQueueBuilderSetQueueMemory(this, memory, size);
    return *this;
}

inline QueueBuilder& QueueBuilder::SetCommandFlushThreshold(size_t size) {
    pfncpp_nvnQueueBuilderSetCommandFlushThreshold(this, size);
    return *this;
}

/* variables don't exist
inline QueueBuilder& QueueBuilder::SetQueuePriority(const QueuePriority queuePriority) {
    pfncpp_nvnQueueBuilderSetQueuePriority(this, queuePriority);
    return *this;
}

inline QueuePriority QueueBuilder::GetQueuePriority() const {
    return pfncpp_nvnQueueBuilderGetQueuePriority(this);
}
*/

inline const Device* QueueBuilder::GetDevice() const {
    return pfncpp_nvnQueueBuilderGetDevice(this);
}

inline int QueueBuilder::GetFlags() const {
    return pfncpp_nvnQueueBuilderGetFlags(this);
}

inline NVNboolean QueueBuilder::GetCommandMemorySize(int* i) const {
    return pfncpp_nvnQueueBuilderGetCommandMemorySize(this, i);
}

inline NVNboolean QueueBuilder::GetComputeMemorySize(int* i) const {
    return pfncpp_nvnQueueBuilderGetComputeMemorySize(this, i);
}

inline NVNboolean QueueBuilder::GetControlMemorySize(int* i) const {
    return pfncpp_nvnQueueBuilderGetControlMemorySize(this, i);
}

inline NVNboolean QueueBuilder::GetCommandFlushThreshold(int* i) const {
    return pfncpp_nvnQueueBuilderGetCommandFlushThreshold(this, i);
}

inline int QueueBuilder::GetMemorySize() const {
    return pfncpp_nvnQueueBuilderGetMemorySize(this);
}

inline void* QueueBuilder::GetMemory() const {
    return pfncpp_nvnQueueBuilderGetMemory(this);
}

inline QueueGetErrorResult Queue::GetError(QueueErrorInfo* info) {
    return pfncpp_nvnQueueGetError(this, info);
}

inline size_t Queue::GetTotalCommandMemoryUsed() {
    return pfncpp_nvnQueueGetTotalCommandMemoryUsed(this);
}

inline size_t Queue::GetTotalControlMemoryUsed() {
    return pfncpp_nvnQueueGetTotalControlMemoryUsed(this);
}

inline size_t Queue::GetTotalComputeMemoryUsed() {
    return pfncpp_nvnQueueGetTotalComputeMemoryUsed(this);
}

inline void Queue::ResetMemoryUsageCounts() {
    pfncpp_nvnQueueResetMemoryUsageCounts(this);
}

inline NVNboolean Queue::Initialize(const QueueBuilder* builder) {
    return pfncpp_nvnQueueInitialize(this, builder);
}

inline void Queue::Finalize() {
    pfncpp_nvnQueueFinalize(this);
}

inline void Queue::SetDebugLabel(const char* label) {
    pfncpp_nvnQueueSetDebugLabel(this, label);
}

inline void Queue::SubmitCommands(int numCommands, const CommandHandle* handles) {
    pfncpp_nvnQueueSubmitCommands(this, numCommands, handles);
}

inline void Queue::Flush() {
    pfncpp_nvnQueueFlush(this);
}

inline void Queue::Finish() {
    pfncpp_nvnQueueFinish(this);
}

inline void Queue::PresentTexture(Window* window, int textureIndex) {
    pfncpp_nvnQueuePresentTexture(this, window, textureIndex);
}

inline QueueAcquireTextureResult Queue::AcquireTexture(Window* window, int* textureIndex) {
    return pfncpp_nvnQueueAcquireTexture(this, window, textureIndex);
}

inline void Queue::FenceSync(Sync* sync, SyncCondition condition, SyncFlagBits flags) {
    pfncpp_nvnQueueFenceSync(this, sync, condition, flags);
}

inline NVNboolean Queue::WaitSync(const Sync* sync) {
    return pfncpp_nvnQueueWaitSync(this, sync);
}

inline NVNboolean CommandBuffer::Initialize(Device* device) {
    return pfncpp_nvnCommandBufferInitialize(this, device);
}

inline void CommandBuffer::Finalize() {
    pfncpp_nvnCommandBufferFinalize(this);
}

inline void CommandBuffer::SetDebugLabel(const char* label) {
    pfncpp_nvnCommandBufferSetDebugLabel(this, label);
}

inline void CommandBuffer::SetMemoryCallback(CommandBufferMemoryCallbackFunc callback) {
    pfncpp_nvnCommandBufferSetMemoryCallback(this, callback);
}

inline void CommandBuffer::SetMemoryCallbackData(void* callbackData) {
    pfncpp_nvnCommandBufferSetMemoryCallbackData(this, callbackData);
}

inline void CommandBuffer::AddCommandMemory(const MemoryPool* pool, ptrdiff_t offset, size_t size) {
    pfncpp_nvnCommandBufferAddCommandMemory(this, pool, offset, size);
}

inline void CommandBuffer::AddControlMemory(void* memory, size_t size) {
    pfncpp_nvnCommandBufferAddControlMemory(this, memory, size);
}

inline size_t CommandBuffer::GetCommandMemorySize() const {
    return pfncpp_nvnCommandBufferGetCommandMemorySize(this);
}

inline size_t CommandBuffer::GetCommandMemoryUsed() const {
    return pfncpp_nvnCommandBufferGetCommandMemoryUsed(this);
}

inline size_t CommandBuffer::GetCommandMemoryFree() const {
    return pfncpp_nvnCommandBufferGetCommandMemoryFree(this);
}

inline size_t CommandBuffer::GetControlMemorySize() const {
    return pfncpp_nvnCommandBufferGetControlMemorySize(this);
}

inline size_t CommandBuffer::GetControlMemoryUsed() const {
    return pfncpp_nvnCommandBufferGetControlMemoryUsed(this);
}

inline size_t CommandBuffer::GetControlMemoryFree() const {
    return pfncpp_nvnCommandBufferGetControlMemoryFree(this);
}

inline void CommandBuffer::BeginRecording() {
    pfncpp_nvnCommandBufferBeginRecording(this);
}

inline CommandHandle CommandBuffer::EndRecording() {
    return pfncpp_nvnCommandBufferEndRecording(this);
}

inline void CommandBuffer::CallCommands(int numCommands, const CommandHandle* handles) {
    pfncpp_nvnCommandBufferCallCommands(this, numCommands, handles);
}

inline void CommandBuffer::CopyCommands(int numCommands, const CommandHandle* handles) {
    pfncpp_nvnCommandBufferCopyCommands(this, numCommands, handles);
}

inline void CommandBuffer::BindBlendState(const BlendState* blend) {
    pfncpp_nvnCommandBufferBindBlendState(this, blend);
}

inline void CommandBuffer::BindChannelMaskState(const ChannelMaskState* channelMask) {
    pfncpp_nvnCommandBufferBindChannelMaskState(this, channelMask);
}

inline void CommandBuffer::BindColorState(const ColorState* color) {
    pfncpp_nvnCommandBufferBindColorState(this, color);
}

inline void CommandBuffer::BindMultisampleState(const MultisampleState* multisample) {
    pfncpp_nvnCommandBufferBindMultisampleState(this, multisample);
}

inline void CommandBuffer::BindPolygonState(const PolygonState* polygon) {
    pfncpp_nvnCommandBufferBindPolygonState(this, polygon);
}

inline void CommandBuffer::BindDepthStencilState(const DepthStencilState* depthStencil) {
    pfncpp_nvnCommandBufferBindDepthStencilState(this, depthStencil);
}

inline void CommandBuffer::BindVertexAttribState(int numAttribs, const VertexAttribState* attribs) {
    pfncpp_nvnCommandBufferBindVertexAttribState(this, numAttribs, attribs);
}

inline void CommandBuffer::BindVertexStreamState(int numStreams, const VertexStreamState* streams) {
    pfncpp_nvnCommandBufferBindVertexStreamState(this, numStreams, streams);
}

inline void CommandBuffer::BindProgram(const Program* program, ShaderStageBits stages) {
    pfncpp_nvnCommandBufferBindProgram(this, program, stages);
}

inline void CommandBuffer::BindVertexBuffer(int index, BufferAddress buffer, size_t size) {
    pfncpp_nvnCommandBufferBindVertexBuffer(this, index, buffer, size);
}

inline void CommandBuffer::BindVertexBuffers(int first, int count, const BufferRange* buffers) {
    pfncpp_nvnCommandBufferBindVertexBuffers(this, first, count, buffers);
}

inline void CommandBuffer::BindUniformBuffer(ShaderStage stage, int index, BufferAddress buffer,
                                             size_t size) {
    pfncpp_nvnCommandBufferBindUniformBuffer(this, stage, index, buffer, size);
}

inline void CommandBuffer::BindUniformBuffers(ShaderStage stage, int first, int count,
                                              const BufferRange* buffers) {
    pfncpp_nvnCommandBufferBindUniformBuffers(this, stage, first, count, buffers);
}

inline void CommandBuffer::BindTransformFeedbackBuffer(int index, BufferAddress buffer,
                                                       size_t size) {
    pfncpp_nvnCommandBufferBindTransformFeedbackBuffer(this, index, buffer, size);
}

inline void CommandBuffer::BindTransformFeedbackBuffers(int first, int count,
                                                        const BufferRange* buffers) {
    pfncpp_nvnCommandBufferBindTransformFeedbackBuffers(this, first, count, buffers);
}

inline void CommandBuffer::BindStorageBuffer(ShaderStage stage, int index, BufferAddress buffer,
                                             size_t size) {
    pfncpp_nvnCommandBufferBindStorageBuffer(this, stage, index, buffer, size);
}

inline void CommandBuffer::BindStorageBuffers(ShaderStage stage, int first, int count,
                                              const BufferRange* buffers) {
    pfncpp_nvnCommandBufferBindStorageBuffers(this, stage, first, count, buffers);
}

inline void CommandBuffer::BindTexture(ShaderStage stage, int index, TextureHandle texture) {
    pfncpp_nvnCommandBufferBindTexture(this, stage, index, texture);
}

inline void CommandBuffer::BindTextures(ShaderStage stage, int first, int count,
                                        const TextureHandle* textures) {
    pfncpp_nvnCommandBufferBindTextures(this, stage, first, count, textures);
}

inline void CommandBuffer::BindImage(ShaderStage stage, int index, ImageHandle image) {
    pfncpp_nvnCommandBufferBindImage(this, stage, index, image);
}

inline void CommandBuffer::BindImages(ShaderStage stage, int first, int count,
                                      const ImageHandle* images) {
    pfncpp_nvnCommandBufferBindImages(this, stage, first, count, images);
}

inline void CommandBuffer::SetPatchSize(int i) {
    pfncpp_nvnCommandBufferSetPatchSize(this, i);
}

inline void CommandBuffer::SetInnerTessellationLevels(const float* f) {
    pfncpp_nvnCommandBufferSetInnerTessellationLevels(this, f);
}

inline void CommandBuffer::SetOuterTessellationLevels(const float* f) {
    pfncpp_nvnCommandBufferSetOuterTessellationLevels(this, f);
}

inline void CommandBuffer::SetPrimitiveRestart(NVNboolean b, int i) {
    pfncpp_nvnCommandBufferSetPrimitiveRestart(this, b, i);
}

inline void CommandBuffer::BeginTransformFeedback(BufferAddress buffer) {
    pfncpp_nvnCommandBufferBeginTransformFeedback(this, buffer);
}

inline void CommandBuffer::EndTransformFeedback(BufferAddress buffer) {
    pfncpp_nvnCommandBufferEndTransformFeedback(this, buffer);
}

inline void CommandBuffer::PauseTransformFeedback(BufferAddress buffer) {
    pfncpp_nvnCommandBufferPauseTransformFeedback(this, buffer);
}

inline void CommandBuffer::ResumeTransformFeedback(BufferAddress buffer) {
    pfncpp_nvnCommandBufferResumeTransformFeedback(this, buffer);
}

inline void CommandBuffer::DrawTransformFeedback(DrawPrimitive mode, BufferAddress buffer) {
    pfncpp_nvnCommandBufferDrawTransformFeedback(this, mode, buffer);
}

inline void CommandBuffer::DrawArrays(DrawPrimitive mode, int first, int count) {
    pfncpp_nvnCommandBufferDrawArrays(this, mode, first, count);
}

inline void CommandBuffer::DrawElements(DrawPrimitive mode, IndexType type, int count,
                                        BufferAddress indexBuffer) {
    pfncpp_nvnCommandBufferDrawElements(this, mode, type, count, indexBuffer);
}

inline void CommandBuffer::DrawElementsBaseVertex(DrawPrimitive mode, IndexType type, int count,
                                                  BufferAddress indexBuffer, int baseVertex) {
    pfncpp_nvnCommandBufferDrawElementsBaseVertex(this, mode, type, count, indexBuffer, baseVertex);
}

inline void CommandBuffer::DrawArraysInstanced(DrawPrimitive mode, int first, int count,
                                               int baseInstance, int instanceCount) {
    pfncpp_nvnCommandBufferDrawArraysInstanced(this, mode, first, count, baseInstance,
                                               instanceCount);
}

inline void CommandBuffer::DrawElementsInstanced(DrawPrimitive mode, IndexType type, int count,
                                                 BufferAddress indexBuffer, int baseVertex,
                                                 int baseInstance, int instanceCount) {
    pfncpp_nvnCommandBufferDrawElementsInstanced(this, mode, type, count, indexBuffer, baseVertex,
                                                 baseInstance, instanceCount);
}

inline void CommandBuffer::DrawArraysIndirect(DrawPrimitive mode, BufferAddress buffer) {
    pfncpp_nvnCommandBufferDrawArraysIndirect(this, mode, buffer);
}

inline void CommandBuffer::DrawElementsIndirect(DrawPrimitive mode, IndexType type,
                                                BufferAddress buffer1, BufferAddress buffer2) {
    pfncpp_nvnCommandBufferDrawElementsIndirect(this, mode, type, buffer1, buffer2);
}

inline void CommandBuffer::MultiDrawArraysIndirectCount(DrawPrimitive mode, BufferAddress buffer1,
                                                        BufferAddress buffer2, int i, ptrdiff_t o) {
    pfncpp_nvnCommandBufferMultiDrawArraysIndirectCount(this, mode, buffer1, buffer2, i, o);
}

inline void CommandBuffer::MultiDrawElementsIndirectCount(DrawPrimitive mode, IndexType type,
                                                          BufferAddress buffer1,
                                                          BufferAddress buffer2,
                                                          BufferAddress buffer3, int i,
                                                          ptrdiff_t o) {
    pfncpp_nvnCommandBufferMultiDrawElementsIndirectCount(this, mode, type, buffer1, buffer2,
                                                          buffer3, i, o);
}

inline void CommandBuffer::ClearColor(int index, const float* color, ClearColorMask mask) {
    pfncpp_nvnCommandBufferClearColor(this, index, color, mask);
}

inline void CommandBuffer::ClearColori(int index, const int* color, ClearColorMask mask) {
    pfncpp_nvnCommandBufferClearColori(this, index, color, mask);
}

inline void CommandBuffer::ClearColorui(int index, const uint32_t* color, ClearColorMask mask) {
    pfncpp_nvnCommandBufferClearColorui(this, index, color, mask);
}

inline void CommandBuffer::ClearDepthStencil(float depthValue, NVNboolean depthMask,
                                             int stencilValue, int stencilMask) {
    pfncpp_nvnCommandBufferClearDepthStencil(this, depthValue, depthMask, stencilValue,
                                             stencilMask);
}

inline void CommandBuffer::DispatchCompute(int groupsX, int groupsY, int groupsZ) {
    pfncpp_nvnCommandBufferDispatchCompute(this, groupsX, groupsY, groupsZ);
}

inline void CommandBuffer::DispatchComputeIndirect(BufferAddress buffer) {
    pfncpp_nvnCommandBufferDispatchComputeIndirect(this, buffer);
}

inline void CommandBuffer::SetViewport(int x, int y, int w, int h) {
    pfncpp_nvnCommandBufferSetViewport(this, x, y, w, h);
}

inline void CommandBuffer::SetViewports(int first, int count, const float* ranges) {
    pfncpp_nvnCommandBufferSetViewports(this, first, count, ranges);
}

inline void CommandBuffer::SetViewportSwizzles(int first, int count,
                                               const ViewportSwizzle* swizzles) {
    pfncpp_nvnCommandBufferSetViewportSwizzles(this, first, count, swizzles);
}

inline void CommandBuffer::SetScissor(int x, int y, int w, int h) {
    pfncpp_nvnCommandBufferSetScissor(this, x, y, w, h);
}

inline void CommandBuffer::SetScissors(int first, int count, const int* rects) {
    pfncpp_nvnCommandBufferSetScissors(this, first, count, rects);
}

inline void CommandBuffer::SetDepthRange(float n, float f) {
    pfncpp_nvnCommandBufferSetDepthRange(this, n, f);
}

inline void CommandBuffer::SetDepthBounds(NVNboolean enable, float n, float f) {
    pfncpp_nvnCommandBufferSetDepthBounds(this, enable, n, f);
}

inline void CommandBuffer::SetDepthRanges(int first, int count, const float* ranges) {
    pfncpp_nvnCommandBufferSetDepthRanges(this, first, count, ranges);
}

inline void CommandBuffer::SetTiledCacheAction(TiledCacheAction action) {
    pfncpp_nvnCommandBufferSetTiledCacheAction(this, action);
}

inline void CommandBuffer::SetTiledCacheTileSize(int w, int h) {
    pfncpp_nvnCommandBufferSetTiledCacheTileSize(this, w, h);
}

inline void CommandBuffer::BindSeparateTexture(ShaderStage stage, int i,
                                               SeparateTextureHandle handle) {
    pfncpp_nvnCommandBufferBindSeparateTexture(this, stage, i, handle);
}

inline void CommandBuffer::bindSeparateTexture(ShaderStage stage, int i,
                                               SeparateTextureHandle handle) {
    pfncpp_nvnCommandBufferBindSeparateTexture(this, stage, i, handle);
}

inline void CommandBuffer::BindSeparateSampler(ShaderStage stage, int i,
                                               SeparateSamplerHandle handle) {
    pfncpp_nvnCommandBufferBindSeparateSampler(this, stage, i, handle);
}

inline void CommandBuffer::bindSeparateSampler(ShaderStage stage, int i,
                                               SeparateSamplerHandle handle) {
    pfncpp_nvnCommandBufferBindSeparateSampler(this, stage, i, handle);
}

inline void CommandBuffer::BindSeparateTextures(ShaderStage stage, int i1, int i2,
                                                const SeparateTextureHandle* handle) {
    pfncpp_nvnCommandBufferBindSeparateTextures(this, stage, i1, i2, handle);
}

inline void CommandBuffer::BindSeparateSamplers(ShaderStage stage, int i1, int i2,
                                                const SeparateSamplerHandle* handle) {
    pfncpp_nvnCommandBufferBindSeparateSamplers(this, stage, i1, i2, handle);
}

inline void CommandBuffer::SetStencilValueMask(Face faces, int mask) {
    pfncpp_nvnCommandBufferSetStencilValueMask(this, faces, mask);
}

inline void CommandBuffer::SetStencilMask(Face faces, int mask) {
    pfncpp_nvnCommandBufferSetStencilMask(this, faces, mask);
}

inline void CommandBuffer::SetStencilRef(Face faces, int ref) {
    pfncpp_nvnCommandBufferSetStencilRef(this, faces, ref);
}

inline void CommandBuffer::SetBlendColor(const float* blendColor) {
    pfncpp_nvnCommandBufferSetBlendColor(this, blendColor);
}

inline void CommandBuffer::SetPointSize(float pointSize) {
    pfncpp_nvnCommandBufferSetPointSize(this, pointSize);
}

inline void CommandBuffer::SetLineWidth(float lineWidth) {
    pfncpp_nvnCommandBufferSetLineWidth(this, lineWidth);
}

inline void CommandBuffer::SetPolygonOffsetClamp(float factor, float units, float clamp) {
    pfncpp_nvnCommandBufferSetPolygonOffsetClamp(this, factor, units, clamp);
}

inline void CommandBuffer::SetAlphaRef(float ref) {
    pfncpp_nvnCommandBufferSetAlphaRef(this, ref);
}

inline void CommandBuffer::SetSampleMask(int mask) {
    pfncpp_nvnCommandBufferSetSampleMask(this, mask);
}

inline void CommandBuffer::SetRasterizerDiscard(NVNboolean discard) {
    pfncpp_nvnCommandBufferSetRasterizerDiscard(this, discard);
}

inline void CommandBuffer::SetDepthClamp(NVNboolean clamp) {
    pfncpp_nvnCommandBufferSetDepthClamp(this, clamp);
}

inline void CommandBuffer::SetConservativeRasterEnable(NVNboolean enable) {
    pfncpp_nvnCommandBufferSetConservativeRasterEnable(this, enable);
}

inline void CommandBuffer::SetConservativeRasterDilate(float f) {
    pfncpp_nvnCommandBufferSetConservativeRasterDilate(this, f);
}

inline void CommandBuffer::SetSubpixelPrecisionBias(int i1, int i2) {
    pfncpp_nvnCommandBufferSetSubpixelPrecisionBias(this, i1, i2);
}

inline void CommandBuffer::CopyBufferToTexture(BufferAddress buffer, const Texture* dstTexture,
                                               const TextureView* dstView,
                                               const CopyRegion* dstRegion, CopyFlags flags) {
    pfncpp_nvnCommandBufferCopyBufferToTexture(this, buffer, dstTexture, dstView, dstRegion, flags);
}

inline void CommandBuffer::CopyTextureToBuffer(const Texture* srcTexture,
                                               const TextureView* srcView,
                                               const CopyRegion* srcRegion, BufferAddress buffer,
                                               CopyFlags flags) {
    pfncpp_nvnCommandBufferCopyTextureToBuffer(this, srcTexture, srcView, srcRegion, buffer, flags);
}

inline void CommandBuffer::CopyTextureToTexture(const Texture* srcTexture,
                                                const TextureView* srcView,
                                                const CopyRegion* srcRegion,
                                                const Texture* dstTexture,
                                                const TextureView* dstView,
                                                const CopyRegion* dstRegion, CopyFlags flags) {
    pfncpp_nvnCommandBufferCopyTextureToTexture(this, srcTexture, srcView, srcRegion, dstTexture,
                                                dstView, dstRegion, flags);
}

inline void CommandBuffer::CopyBufferToBuffer(BufferAddress src, BufferAddress dst, size_t size,
                                              CopyFlags flags) {
    pfncpp_nvnCommandBufferCopyBufferToBuffer(this, src, dst, size, flags);
}

inline void CommandBuffer::ClearBuffer(BufferAddress buffer, size_t size, uint32_t i) {
    pfncpp_nvnCommandBufferClearBuffer(this, buffer, size, i);
}

inline void CommandBuffer::ClearTexture(const Texture* dstTexture, const TextureView* dstView,
                                        const CopyRegion* dstRegion, const float* color,
                                        ClearColorMask mask) {
    pfncpp_nvnCommandBufferClearTexture(this, dstTexture, dstView, dstRegion, color, mask);
}

inline void CommandBuffer::ClearTexturei(const Texture* dstTexture, const TextureView* dstView,
                                         const CopyRegion* dstRegion, const int* color,
                                         ClearColorMask mask) {
    pfncpp_nvnCommandBufferClearTexturei(this, dstTexture, dstView, dstRegion, color, mask);
}

inline void CommandBuffer::ClearTextureui(const Texture* dstTexture, const TextureView* dstView,
                                          const CopyRegion* dstRegion, const uint32_t* color,
                                          ClearColorMask mask) {
    pfncpp_nvnCommandBufferClearTextureui(this, dstTexture, dstView, dstRegion, color, mask);
}

inline void CommandBuffer::UpdateUniformBuffer(BufferAddress buffer, size_t size, ptrdiff_t o,
                                               size_t s, const void* p) {
    pfncpp_nvnCommandBufferUpdateUniformBuffer(this, buffer, size, o, s, p);
}

inline void CommandBuffer::ReportCounter(CounterType counter, BufferAddress buffer) {
    pfncpp_nvnCommandBufferReportCounter(this, counter, buffer);
}

inline void CommandBuffer::ResetCounter(CounterType counter) {
    pfncpp_nvnCommandBufferResetCounter(this, counter);
}

inline void CommandBuffer::ReportValue(uint32_t value, BufferAddress buffer) {
    pfncpp_nvnCommandBufferReportValue(this, value, buffer);
}

inline void CommandBuffer::SetRenderEnable(NVNboolean enable) {
    pfncpp_nvnCommandBufferSetRenderEnable(this, enable);
}

inline void CommandBuffer::SetRenderEnableConditional(ConditionalRenderMode mode,
                                                      BufferAddress addr) {
    pfncpp_nvnCommandBufferSetRenderEnableConditional(this, mode, addr);
}

inline void CommandBuffer::SetRenderTargets(int numColors, const Texture* const* colors,
                                            const TextureView* const* colorViews,
                                            const Texture* depthStencil,
                                            const TextureView* depthStencilView) {
    pfncpp_nvnCommandBufferSetRenderTargets(this, numColors, colors, colorViews, depthStencil,
                                            depthStencilView);
}

inline void CommandBuffer::DiscardColor(int i) {
    pfncpp_nvnCommandBufferDiscardColor(this, i);
}

inline void CommandBuffer::DiscardDepthStencil() {
    pfncpp_nvnCommandBufferDiscardDepthStencil(this);
}

inline void CommandBuffer::Downsample(const Texture* texture1, const Texture* texture2) {
    pfncpp_nvnCommandBufferDownsample(this, texture1, texture2);
}

inline void CommandBuffer::TiledDownsample(const Texture* texture1, const Texture* texture2) {
    pfncpp_nvnCommandBufferTiledDownsample(this, texture1, texture2);
}

inline void CommandBuffer::DownsampleTextureView(const Texture* texture1, const TextureView* view1,
                                                 const Texture* texture2,
                                                 const TextureView* view2) {
    pfncpp_nvnCommandBufferDownsampleTextureView(this, texture1, view1, texture2, view2);
}

inline void CommandBuffer::TiledDownsampleTextureView(const Texture* texture1,
                                                      const TextureView* view1,
                                                      const Texture* texture2,
                                                      const TextureView* view2) {
    pfncpp_nvnCommandBufferTiledDownsampleTextureView(this, texture1, view1, texture2, view2);
}

inline void CommandBuffer::Barrier(BarrierBits barrier) {
    pfncpp_nvnCommandBufferBarrier(this, barrier);
}

inline void CommandBuffer::WaitSync(const Sync* sync) {
    pfncpp_nvnCommandBufferWaitSync(this, sync);
}

inline void CommandBuffer::FenceSync(Sync* sync, SyncCondition condition, SyncFlagBits fence) {
    pfncpp_nvnCommandBufferFenceSync(this, sync, condition, fence);
}

inline void CommandBuffer::SetTexturePool(const TexturePool* pool) {
    pfncpp_nvnCommandBufferSetTexturePool(this, pool);
}

inline void CommandBuffer::SetSamplerPool(const SamplerPool* pool) {
    pfncpp_nvnCommandBufferSetSamplerPool(this, pool);
}

inline void CommandBuffer::SetShaderScratchMemory(const MemoryPool* pool, ptrdiff_t offset,
                                                  size_t size) {
    pfncpp_nvnCommandBufferSetShaderScratchMemory(this, pool, offset, size);
}

inline void CommandBuffer::SaveZCullData(BufferAddress addr, size_t size) {
    pfncpp_nvnCommandBufferSaveZCullData(this, addr, size);
}

inline void CommandBuffer::RestoreZCullData(BufferAddress addr, size_t size) {
    pfncpp_nvnCommandBufferRestoreZCullData(this, addr, size);
}

inline void CommandBuffer::SetCopyRowStride(ptrdiff_t stride) {
    pfncpp_nvnCommandBufferSetCopyRowStride(this, stride);
}

inline void CommandBuffer::SetCopyImageStride(ptrdiff_t stride) {
    pfncpp_nvnCommandBufferSetCopyImageStride(this, stride);
}

inline ptrdiff_t CommandBuffer::GetCopyRowStride() const {
    return pfncpp_nvnCommandBufferGetCopyRowStride(this);
}

inline ptrdiff_t CommandBuffer::GetCopyImageStride() const {
    return pfncpp_nvnCommandBufferGetCopyImageStride(this);
}

inline void CommandBuffer::DrawTexture(TextureHandle handle, const DrawTextureRegion* region1,
                                       const DrawTextureRegion* region2) {
    pfncpp_nvnCommandBufferDrawTexture(this, handle, region1, region2);
}

inline void CommandBuffer::SetProgramSubroutines(Program* program, ShaderStage stage, const int i1,
                                                 const int i2, const int* i3) {
    pfncpp_nvnCommandBufferSetProgramSubroutines(this, program, stage, i1, i2, i3);
}

inline void CommandBuffer::BindCoverageModulationTable(const float* f) {
    pfncpp_nvnCommandBufferBindCoverageModulationTable(this, f);
}

inline void CommandBuffer::ResolveDepthBuffer() {
    pfncpp_nvnCommandBufferResolveDepthBuffer(this);
}

inline void CommandBuffer::SetColorReductionEnable(NVNboolean enable) {
    pfncpp_nvnCommandBufferSetColorReductionEnable(this, enable);
}

inline void CommandBuffer::SetColorReductionThresholds(FormatClass format, int i1, int i2) {
    pfncpp_nvnCommandBufferSetColorReductionThresholds(this, format, i1, i2);
}

inline void CommandBuffer::PushDebugGroupStatic(uint32_t i, const char* description) {
    pfncpp_nvnCommandBufferPushDebugGroupStatic(this, i, description);
}

inline void CommandBuffer::PushDebugGroupDynamic(uint32_t i, const char* description) {
    pfncpp_nvnCommandBufferPushDebugGroupDynamic(this, i, description);
}

inline void CommandBuffer::PushDebugGroup(const char* description) {
    pfncpp_nvnCommandBufferPushDebugGroup(this, description);
}

inline void CommandBuffer::PopDebugGroup() {
    pfncpp_nvnCommandBufferPopDebugGroup(this);
}

inline void CommandBuffer::PopDebugGroupId(uint32_t i) {
    pfncpp_nvnCommandBufferPopDebugGroupId(this, i);
}

inline void CommandBuffer::InsertDebugMarkerStatic(uint32_t i, const char* description) {
    pfncpp_nvnCommandBufferInsertDebugMarkerStatic(this, i, description);
}

inline void CommandBuffer::InsertDebugMarkerDynamic(uint32_t i, const char* description) {
    pfncpp_nvnCommandBufferInsertDebugMarkerDynamic(this, i, description);
}

inline void CommandBuffer::InsertDebugMarker(const char* description) {
    pfncpp_nvnCommandBufferInsertDebugMarker(this, description);
}

inline CommandBufferMemoryCallbackFunc CommandBuffer::GetMemoryCallback() const {
    return pfncpp_nvnCommandBufferGetMemoryCallback(this);
}

inline void* CommandBuffer::GetMemoryCallbackData() const {
    return pfncpp_nvnCommandBufferGetMemoryCallbackData(this);
}

inline NVNboolean CommandBuffer::IsRecording() const {
    return pfncpp_nvnCommandBufferIsRecording(this);
}

inline void CommandBuffer::WaitEvent(const Event* event, EventWaitMode mode, uint32_t i) {
    pfncpp_nvnCommandBufferWaitEvent(this, event, mode, i);
}

inline void CommandBuffer::SignalEvent(const Event* event, EventSignalMode mode,
                                       EventSignalLocation location, EventSignalFlags flags,
                                       uint32_t i) {
    pfncpp_nvnCommandBufferSignalEvent(this, event, mode, location, flags, i);
}

inline void CommandBuffer::SetStencilCullCriteria(StencilFunc func, int i1, int i2) {
    pfncpp_nvnCommandBufferSetStencilCullCriteria(this, func, i1, i2);
}

inline BlendState& BlendState::SetDefaults() {
    pfncpp_nvnBlendStateSetDefaults(this);
    return *this;
}

inline BlendState& BlendState::SetBlendTarget(int target) {
    pfncpp_nvnBlendStateSetBlendTarget(this, target);
    return *this;
}

inline BlendState& BlendState::SetBlendFunc(BlendFunc srcFunc, BlendFunc dstFunc,
                                            BlendFunc srcFuncAlpha, BlendFunc dstFuncAlpha) {
    pfncpp_nvnBlendStateSetBlendFunc(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
    return *this;
}

inline BlendState& BlendState::SetBlendEquation(BlendEquation modeRGB, BlendEquation modeAlpha) {
    pfncpp_nvnBlendStateSetBlendEquation(this, modeRGB, modeAlpha);
    return *this;
}

inline BlendState& BlendState::SetAdvancedMode(BlendAdvancedMode mode) {
    pfncpp_nvnBlendStateSetAdvancedMode(this, mode);
    return *this;
}

inline BlendState& BlendState::SetAdvancedOverlap(BlendAdvancedOverlap overlap) {
    pfncpp_nvnBlendStateSetAdvancedOverlap(this, overlap);
    return *this;
}

inline BlendState& BlendState::SetAdvancedPremultipliedSrc(NVNboolean b) {
    pfncpp_nvnBlendStateSetAdvancedPremultipliedSrc(this, b);
    return *this;
}

inline BlendState& BlendState::SetAdvancedNormalizedDst(NVNboolean b) {
    pfncpp_nvnBlendStateSetAdvancedNormalizedDst(this, b);
    return *this;
}

inline int BlendState::GetBlendTarget() const {
    return pfncpp_nvnBlendStateGetBlendTarget(this);
}

inline void BlendState::GetBlendFunc(BlendFunc* srcFunc, BlendFunc* dstFunc,
                                     BlendFunc* srcFuncAlpha, BlendFunc* dstFuncAlpha) const {
    pfncpp_nvnBlendStateGetBlendFunc(this, srcFunc, dstFunc, srcFuncAlpha, dstFuncAlpha);
}

inline void BlendState::GetBlendEquation(BlendEquation* modeRGB, BlendEquation* modeAlpha) const {
    pfncpp_nvnBlendStateGetBlendEquation(this, modeRGB, modeAlpha);
}

inline BlendAdvancedMode BlendState::GetAdvancedMode() const {
    return pfncpp_nvnBlendStateGetAdvancedMode(this);
}

inline BlendAdvancedOverlap BlendState::GetAdvancedOverlap() const {
    return pfncpp_nvnBlendStateGetAdvancedOverlap(this);
}

inline NVNboolean BlendState::GetAdvancedPremultipliedSrc() const {
    return pfncpp_nvnBlendStateGetAdvancedPremultipliedSrc(this);
}

inline NVNboolean BlendState::GetAdvancedNormalizedDst() const {
    return pfncpp_nvnBlendStateGetAdvancedNormalizedDst(this);
}

inline ChannelMaskState& ChannelMaskState::SetDefaults() {
    pfncpp_nvnChannelMaskStateSetDefaults(this);
    return *this;
}

inline ChannelMaskState& ChannelMaskState::SetChannelMask(int index, NVNboolean r, NVNboolean g,
                                                          NVNboolean b, NVNboolean a) {
    pfncpp_nvnChannelMaskStateSetChannelMask(this, index, r, g, b, a);
    return *this;
}

inline void ChannelMaskState::GetChannelMask(int index, NVNboolean* r, NVNboolean* g, NVNboolean* b,
                                             NVNboolean* a) const {
    pfncpp_nvnChannelMaskStateGetChannelMask(this, index, r, g, b, a);
}

inline ColorState& ColorState::SetDefaults() {
    pfncpp_nvnColorStateSetDefaults(this);
    return *this;
}

inline ColorState& ColorState::SetBlendEnable(int index, NVNboolean enable) {
    pfncpp_nvnColorStateSetBlendEnable(this, index, enable);
    return *this;
}

inline ColorState& ColorState::SetLogicOp(LogicOp logicOp) {
    pfncpp_nvnColorStateSetLogicOp(this, logicOp);
    return *this;
}

inline ColorState& ColorState::SetAlphaTest(AlphaFunc alphaFunc) {
    pfncpp_nvnColorStateSetAlphaTest(this, alphaFunc);
    return *this;
}

inline NVNboolean ColorState::GetBlendEnable(int index) const {
    return pfncpp_nvnColorStateGetBlendEnable(this, index);
}

inline LogicOp ColorState::GetLogicOp() const {
    return pfncpp_nvnColorStateGetLogicOp(this);
}

inline AlphaFunc ColorState::GetAlphaTest() const {
    return pfncpp_nvnColorStateGetAlphaTest(this);
}

inline DepthStencilState& DepthStencilState::SetDefaults() {
    pfncpp_nvnDepthStencilStateSetDefaults(this);
    return *this;
}

inline DepthStencilState& DepthStencilState::SetDepthTestEnable(NVNboolean enable) {
    pfncpp_nvnDepthStencilStateSetDepthTestEnable(this, enable);
    return *this;
}

inline DepthStencilState& DepthStencilState::SetDepthWriteEnable(NVNboolean enable) {
    pfncpp_nvnDepthStencilStateSetDepthWriteEnable(this, enable);
    return *this;
}

inline DepthStencilState& DepthStencilState::SetDepthFunc(DepthFunc func) {
    pfncpp_nvnDepthStencilStateSetDepthFunc(this, func);
    return *this;
}

inline DepthStencilState& DepthStencilState::SetStencilTestEnable(NVNboolean enable) {
    pfncpp_nvnDepthStencilStateSetStencilTestEnable(this, enable);
    return *this;
}

inline DepthStencilState& DepthStencilState::SetStencilFunc(Face faces, StencilFunc func) {
    pfncpp_nvnDepthStencilStateSetStencilFunc(this, faces, func);
    return *this;
}

inline DepthStencilState& DepthStencilState::SetStencilOp(Face faces, StencilOp fail,
                                                          StencilOp depthFail,
                                                          StencilOp depthPass) {
    pfncpp_nvnDepthStencilStateSetStencilOp(this, faces, fail, depthFail, depthPass);
    return *this;
}

inline NVNboolean DepthStencilState::GetDepthTestEnable() const {
    return pfncpp_nvnDepthStencilStateGetDepthTestEnable(this);
}

inline NVNboolean DepthStencilState::GetDepthWriteEnable() const {
    return pfncpp_nvnDepthStencilStateGetDepthWriteEnable(this);
}

inline DepthFunc DepthStencilState::GetDepthFunc() const {
    return pfncpp_nvnDepthStencilStateGetDepthFunc(this);
}

inline NVNboolean DepthStencilState::GetStencilTestEnable() const {
    return pfncpp_nvnDepthStencilStateGetStencilTestEnable(this);
}

inline StencilFunc DepthStencilState::GetStencilFunc(Face faces) const {
    return pfncpp_nvnDepthStencilStateGetStencilFunc(this, faces);
}

inline void DepthStencilState::GetStencilOp(Face faces, StencilOp* fail, StencilOp* depthFail,
                                            StencilOp* depthPass) const {
    pfncpp_nvnDepthStencilStateGetStencilOp(this, faces, fail, depthFail, depthPass);
}

inline MultisampleState& MultisampleState::SetDefaults() {
    pfncpp_nvnMultisampleStateSetDefaults(this);
    return *this;
}

inline MultisampleState& MultisampleState::SetMultisampleEnable(NVNboolean enable) {
    pfncpp_nvnMultisampleStateSetMultisampleEnable(this, enable);
    return *this;
}

inline MultisampleState& MultisampleState::SetSamples(int samples) {
    pfncpp_nvnMultisampleStateSetSamples(this, samples);
    return *this;
}

inline MultisampleState& MultisampleState::SetAlphaToCoverageEnable(NVNboolean enable) {
    pfncpp_nvnMultisampleStateSetAlphaToCoverageEnable(this, enable);
    return *this;
}

inline MultisampleState& MultisampleState::SetAlphaToCoverageDither(NVNboolean enable) {
    pfncpp_nvnMultisampleStateSetAlphaToCoverageDither(this, enable);
    return *this;
}

inline NVNboolean MultisampleState::GetMultisampleEnable() const {
    return pfncpp_nvnMultisampleStateGetMultisampleEnable(this);
}

inline int MultisampleState::GetSamples() const {
    return pfncpp_nvnMultisampleStateGetSamples(this);
}

inline NVNboolean MultisampleState::GetAlphaToCoverageEnable() const {
    return pfncpp_nvnMultisampleStateGetAlphaToCoverageEnable(this);
}

inline NVNboolean MultisampleState::GetAlphaToCoverageDither() const {
    return pfncpp_nvnMultisampleStateGetAlphaToCoverageDither(this);
}

inline MultisampleState& MultisampleState::SetRasterSamples(int samples) {
    pfncpp_nvnMultisampleStateSetRasterSamples(this, samples);
    return *this;
}

inline int MultisampleState::GetRasterSamples() {
    return pfncpp_nvnMultisampleStateGetRasterSamples(this);
}

inline MultisampleState& MultisampleState::SetCoverageModulationMode(CoverageModulationMode mode) {
    pfncpp_nvnMultisampleStateSetCoverageModulationMode(this, mode);
    return *this;
}

inline CoverageModulationMode MultisampleState::GetCoverageModulationMode() const {
    return pfncpp_nvnMultisampleStateGetCoverageModulationMode(this);
}

inline MultisampleState& MultisampleState::SetCoverageToColorEnable(NVNboolean enable) {
    pfncpp_nvnMultisampleStateSetCoverageToColorEnable(this, enable);
    return *this;
}

inline NVNboolean MultisampleState::GetCoverageToColorEnable() const {
    return pfncpp_nvnMultisampleStateGetCoverageToColorEnable(this);
}

inline MultisampleState& MultisampleState::SetCoverageToColorOutput(int i) {
    pfncpp_nvnMultisampleStateSetCoverageToColorOutput(this, i);
    return *this;
}

inline int MultisampleState::GetCoverageToColorOutput() const {
    return pfncpp_nvnMultisampleStateGetCoverageToColorOutput(this);
}

inline MultisampleState& MultisampleState::SetSampleLocationsEnable(NVNboolean enable) {
    pfncpp_nvnMultisampleStateSetSampleLocationsEnable(this, enable);
    return *this;
}

inline NVNboolean MultisampleState::GetSampleLocationsEnable() const {
    return pfncpp_nvnMultisampleStateGetSampleLocationsEnable(this);
}

inline void MultisampleState::GetSampleLocationsGrid(int* w, int* h) {
    pfncpp_nvnMultisampleStateGetSampleLocationsGrid(this, w, h);
}

inline MultisampleState& MultisampleState::SetSampleLocationsGridEnable(NVNboolean enable) {
    pfncpp_nvnMultisampleStateSetSampleLocationsGridEnable(this, enable);
    return *this;
}

inline NVNboolean MultisampleState::GetSampleLocationsGridEnable() const {
    return pfncpp_nvnMultisampleStateGetSampleLocationsGridEnable(this);
}

inline MultisampleState& MultisampleState::SetSampleLocations(int i1, int i2, const float* f) {
    pfncpp_nvnMultisampleStateSetSampleLocations(this, i1, i2, f);
    return *this;
}

inline PolygonState& PolygonState::SetDefaults() {
    pfncpp_nvnPolygonStateSetDefaults(this);
    return *this;
}

inline PolygonState& PolygonState::SetCullFace(Face face) {
    pfncpp_nvnPolygonStateSetCullFace(this, face);
    return *this;
}

inline PolygonState& PolygonState::SetFrontFace(FrontFace face) {
    pfncpp_nvnPolygonStateSetFrontFace(this, face);
    return *this;
}

inline PolygonState& PolygonState::SetPolygonMode(PolygonMode polygonMode) {
    pfncpp_nvnPolygonStateSetPolygonMode(this, polygonMode);
    return *this;
}

inline PolygonState& PolygonState::SetPolygonOffsetEnables(PolygonOffsetEnable enables) {
    pfncpp_nvnPolygonStateSetPolygonOffsetEnables(this, enables);
    return *this;
}

inline Face PolygonState::GetCullFace() const {
    return pfncpp_nvnPolygonStateGetCullFace(this);
}

inline FrontFace PolygonState::GetFrontFace() const {
    return pfncpp_nvnPolygonStateGetFrontFace(this);
}

inline PolygonMode PolygonState::GetPolygonMode() const {
    return pfncpp_nvnPolygonStateGetPolygonMode(this);
}

inline PolygonOffsetEnable PolygonState::GetPolygonOffsetEnables() const {
    return pfncpp_nvnPolygonStateGetPolygonOffsetEnables(this);
}

inline VertexAttribState& VertexAttribState::SetDefaults() {
    pfncpp_nvnVertexAttribStateSetDefaults(this);
    return *this;
}

inline VertexAttribState& VertexAttribState::SetFormat(Format format, ptrdiff_t relativeOffset) {
    pfncpp_nvnVertexAttribStateSetFormat(this, format, relativeOffset);
    return *this;
}

inline VertexAttribState& VertexAttribState::SetStreamIndex(int streamIndex) {
    pfncpp_nvnVertexAttribStateSetStreamIndex(this, streamIndex);
    return *this;
}

inline void VertexAttribState::GetFormat(Format* format, ptrdiff_t* relativeOffset) const {
    pfncpp_nvnVertexAttribStateGetFormat(this, format, relativeOffset);
}

inline int VertexAttribState::GetStreamIndex() const {
    return pfncpp_nvnVertexAttribStateGetStreamIndex(this);
}

inline VertexStreamState& VertexStreamState::SetDefaults() {
    pfncpp_nvnVertexStreamStateSetDefaults(this);
    return *this;
}

inline VertexStreamState& VertexStreamState::SetStride(ptrdiff_t stride) {
    pfncpp_nvnVertexStreamStateSetStride(this, stride);
    return *this;
}

inline VertexStreamState& VertexStreamState::SetDivisor(int divisor) {
    pfncpp_nvnVertexStreamStateSetDivisor(this, divisor);
    return *this;
}

inline ptrdiff_t VertexStreamState::GetStride() const {
    return pfncpp_nvnVertexStreamStateGetStride(this);
}

inline int VertexStreamState::GetDivisor() const {
    return pfncpp_nvnVertexStreamStateGetDivisor(this);
}

inline NVNboolean Program::Initialize(Device* device) {
    return pfncpp_nvnProgramInitialize(this, device);
}

inline void Program::Finalize() {
    pfncpp_nvnProgramFinalize(this);
}

inline void Program::SetDebugLabel(const char* label) {
    pfncpp_nvnProgramSetDebugLabel(this, label);
}

inline NVNboolean Program::SetShaders(int count, const ShaderData* stageData) {
    return pfncpp_nvnProgramSetShaders(this, count, stageData);
}

/*
inline NVNboolean Program::SetShadersExt(int, const ShaderDataExt*) {
    pfncpp_nvnProgramSetShadersExt(this);
}

inline void Program::SetSampleShading(SampleShadingMode) {
    pfncpp_nvnProgramSetSampleShading(this);
}
*/

inline NVNboolean Program::SetSubroutineLinkage(int i, const NVNsubroutineLinkageMapPtr* ptr) {
    return pfncpp_nvnProgramSetSubroutineLinkage(this, i, ptr);
}

inline MemoryPoolBuilder& MemoryPoolBuilder::SetDevice(Device* device) {
    pfncpp_nvnMemoryPoolBuilderSetDevice(this, device);
    return *this;
}

inline MemoryPoolBuilder& MemoryPoolBuilder::SetDefaults() {
    pfncpp_nvnMemoryPoolBuilderSetDefaults(this);
    return *this;
}

inline MemoryPoolBuilder& MemoryPoolBuilder::SetStorage(void* memory, size_t size) {
    pfncpp_nvnMemoryPoolBuilderSetStorage(this, memory, size);
    return *this;
}

inline MemoryPoolBuilder& MemoryPoolBuilder::SetFlags(MemoryPoolFlags flags) {
    pfncpp_nvnMemoryPoolBuilderSetFlags(this, flags);
    return *this;
}

inline const Device* MemoryPoolBuilder::GetDevice() const {
    return pfncpp_nvnMemoryPoolBuilderGetDevice(this);
}

inline void* MemoryPoolBuilder::GetMemory() const {
    return pfncpp_nvnMemoryPoolBuilderGetMemory(this);
}

inline size_t MemoryPoolBuilder::GetSize() const {
    return pfncpp_nvnMemoryPoolBuilderGetSize(this);
}

inline MemoryPoolFlags MemoryPoolBuilder::GetFlags() const {
    return pfncpp_nvnMemoryPoolBuilderGetFlags(this);
}

inline NVNboolean MemoryPool::Initialize(const MemoryPoolBuilder* builder) {
    return pfncpp_nvnMemoryPoolInitialize(this, builder);
}

inline void MemoryPool::SetDebugLabel(const char* label) {
    pfncpp_nvnMemoryPoolSetDebugLabel(this, label);
}

inline void MemoryPool::Finalize() {
    pfncpp_nvnMemoryPoolFinalize(this);
}

inline void* MemoryPool::Map() const {
    return pfncpp_nvnMemoryPoolMap(this);
}

inline void MemoryPool::FlushMappedRange(ptrdiff_t offset, size_t size) const {
    pfncpp_nvnMemoryPoolFlushMappedRange(this, offset, size);
}

inline void MemoryPool::InvalidateMappedRange(ptrdiff_t offset, size_t size) const {
    pfncpp_nvnMemoryPoolInvalidateMappedRange(this, offset, size);
}

inline BufferAddress MemoryPool::GetBufferAddress() const {
    return pfncpp_nvnMemoryPoolGetBufferAddress(this);
}

inline NVNboolean MemoryPool::MapVirtual(int numRequests, const MappingRequest* requests) {
    return pfncpp_nvnMemoryPoolMapVirtual(this, numRequests, requests);
}

inline size_t MemoryPool::GetSize() const {
    return pfncpp_nvnMemoryPoolGetSize(this);
}

inline MemoryPoolFlags MemoryPool::GetFlags() const {
    return pfncpp_nvnMemoryPoolGetFlags(this);
}

inline NVNboolean TexturePool::Initialize(const MemoryPool* memoryPool, ptrdiff_t offset,
                                          int numDescriptors) {
    return pfncpp_nvnTexturePoolInitialize(this, memoryPool, offset, numDescriptors);
}

inline void TexturePool::SetDebugLabel(const char* label) {
    pfncpp_nvnTexturePoolSetDebugLabel(this, label);
}

inline void TexturePool::Finalize() {
    pfncpp_nvnTexturePoolFinalize(this);
}

inline void TexturePool::RegisterTexture(int id, const Texture* texture,
                                         const TextureView* view) const {
    pfncpp_nvnTexturePoolRegisterTexture(this, id, texture, view);
}

inline void TexturePool::RegisterImage(int id, const Texture* texture,
                                       const TextureView* view) const {
    pfncpp_nvnTexturePoolRegisterImage(this, id, texture, view);
}

inline const MemoryPool* TexturePool::GetMemoryPool() const {
    return pfncpp_nvnTexturePoolGetMemoryPool(this);
}

inline ptrdiff_t TexturePool::GetMemoryOffset() const {
    return pfncpp_nvnTexturePoolGetMemoryOffset(this);
}

inline int TexturePool::GetSize() const {
    return pfncpp_nvnTexturePoolGetSize(this);
}

inline NVNboolean SamplerPool::Initialize(const MemoryPool* memoryPool, ptrdiff_t offset,
                                          int numDescriptors) {
    return pfncpp_nvnSamplerPoolInitialize(this, memoryPool, offset, numDescriptors);
}

inline void SamplerPool::SetDebugLabel(const char* label) {
    pfncpp_nvnSamplerPoolSetDebugLabel(this, label);
}

inline void SamplerPool::Finalize() {
    pfncpp_nvnSamplerPoolFinalize(this);
}

inline void SamplerPool::RegisterSampler(int id, const Sampler* sampler) const {
    pfncpp_nvnSamplerPoolRegisterSampler(this, id, sampler);
}

inline void SamplerPool::RegisterSamplerBuilder(int id, const SamplerBuilder* builder) const {
    pfncpp_nvnSamplerPoolRegisterSamplerBuilder(this, id, builder);
}

inline const MemoryPool* SamplerPool::GetMemoryPool() const {
    return pfncpp_nvnSamplerPoolGetMemoryPool(this);
}

inline ptrdiff_t SamplerPool::GetMemoryOffset() const {
    return pfncpp_nvnSamplerPoolGetMemoryOffset(this);
}

inline int SamplerPool::GetSize() const {
    return pfncpp_nvnSamplerPoolGetSize(this);
}

inline BufferBuilder& BufferBuilder::SetDevice(Device* device) {
    pfncpp_nvnBufferBuilderSetDevice(this, device);
    return *this;
}

inline BufferBuilder& BufferBuilder::SetDefaults() {
    pfncpp_nvnBufferBuilderSetDefaults(this);
    return *this;
}

inline BufferBuilder& BufferBuilder::SetStorage(MemoryPool* pool, ptrdiff_t offset, size_t size) {
    pfncpp_nvnBufferBuilderSetStorage(this, pool, offset, size);
    return *this;
}

inline const Device* BufferBuilder::GetDevice() const {
    return pfncpp_nvnBufferBuilderGetDevice(this);
}

inline MemoryPool* BufferBuilder::GetMemoryPool() const {
    return pfncpp_nvnBufferBuilderGetMemoryPool(this);
}

inline ptrdiff_t BufferBuilder::GetMemoryOffset() const {
    return pfncpp_nvnBufferBuilderGetMemoryOffset(this);
}

inline size_t BufferBuilder::GetSize() const {
    return pfncpp_nvnBufferBuilderGetSize(this);
}

inline NVNboolean Buffer::Initialize(const BufferBuilder* builder) {
    return pfncpp_nvnBufferInitialize(this, builder);
}

inline void Buffer::SetDebugLabel(const char* label) {
    pfncpp_nvnBufferSetDebugLabel(this, label);
}

inline void Buffer::Finalize() {
    pfncpp_nvnBufferFinalize(this);
}

inline void* Buffer::Map() const {
    return pfncpp_nvnBufferMap(this);
}

inline BufferAddress Buffer::GetAddress() const {
    return pfncpp_nvnBufferGetAddress(this);
}

inline void Buffer::FlushMappedRange(ptrdiff_t offset, size_t size) const {
    pfncpp_nvnBufferFlushMappedRange(this, offset, size);
}

inline void Buffer::InvalidateMappedRange(ptrdiff_t offset, size_t size) const {
    pfncpp_nvnBufferInvalidateMappedRange(this, offset, size);
}

inline MemoryPool* Buffer::GetMemoryPool() const {
    return pfncpp_nvnBufferGetMemoryPool(this);
}

inline ptrdiff_t Buffer::GetMemoryOffset() const {
    return pfncpp_nvnBufferGetMemoryOffset(this);
}

inline size_t Buffer::GetSize() const {
    return pfncpp_nvnBufferGetSize(this);
}

inline uint64_t Buffer::GetDebugID() const {
    return pfncpp_nvnBufferGetDebugID(this);
}

inline NVNboolean Texture::Initialize(const TextureBuilder* builder) {
    return pfncpp_nvnTextureInitialize(this, builder);
}

inline size_t Texture::GetZCullStorageSize() const {
    return pfncpp_nvnTextureGetZCullStorageSize(this);
}

inline void Texture::Finalize() {
    pfncpp_nvnTextureFinalize(this);
}

inline void Texture::SetDebugLabel(const char* label) {
    pfncpp_nvnTextureSetDebugLabel(this, label);
}

inline NVNstorageClass Texture::GetStorageClass() const {
    return pfncpp_nvnTextureGetStorageClass(this);
}

inline ptrdiff_t Texture::GetViewOffset(const TextureView* view) const {
    return pfncpp_nvnTextureGetViewOffset(this, view);
}

inline TextureFlags Texture::GetFlags() const {
    return pfncpp_nvnTextureGetFlags(this);
}

inline TextureTarget Texture::GetTarget() const {
    return pfncpp_nvnTextureGetTarget(this);
}

inline int Texture::GetWidth() const {
    return pfncpp_nvnTextureGetWidth(this);
}

inline int Texture::GetHeight() const {
    return pfncpp_nvnTextureGetHeight(this);
}

inline int Texture::GetDepth() const {
    return pfncpp_nvnTextureGetDepth(this);
}

inline int Texture::GetLevels() const {
    return pfncpp_nvnTextureGetLevels(this);
}

inline Format Texture::GetFormat() const {
    return pfncpp_nvnTextureGetFormat(this);
}

inline int Texture::GetSamples() const {
    return pfncpp_nvnTextureGetSamples(this);
}

inline void Texture::GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b,
                                TextureSwizzle* a) const {
    pfncpp_nvnTextureGetSwizzle(this, r, g, b, a);
}

inline TextureDepthStencilMode Texture::GetDepthStencilMode() const {
    return pfncpp_nvnTextureGetDepthStencilMode(this);
}

inline ptrdiff_t Texture::GetStride() const {
    return pfncpp_nvnTextureGetStride(this);
}

inline TextureAddress Texture::GetTextureAddress() const {
    return pfncpp_nvnTextureGetTextureAddress(this);
}

inline void Texture::GetSparseTileLayout(TextureSparseTileLayout* layout) const {
    pfncpp_nvnTextureGetSparseTileLayout(this, layout);
}

inline void Texture::WriteTexels(const TextureView* view, const CopyRegion* region,
                                 const void* p) const {
    pfncpp_nvnTextureWriteTexels(this, view, region, p);
}

inline void Texture::WriteTexelsStrided(const TextureView* view, const CopyRegion* region,
                                        const void* p, ptrdiff_t o1, ptrdiff_t o2) const {
    pfncpp_nvnTextureWriteTexelsStrided(this, view, region, p, o1, o2);
}

inline void Texture::ReadTexels(const TextureView* view, const CopyRegion* region, void* p) const {
    pfncpp_nvnTextureReadTexels(this, view, region, p);
}

inline void Texture::ReadTexelsStrided(const TextureView* view, const CopyRegion* region, void* p,
                                       ptrdiff_t o1, ptrdiff_t o2) const {
    pfncpp_nvnTextureReadTexelsStrided(this, view, region, p, o1, o2);
}

inline void Texture::FlushTexels(const TextureView* view, const CopyRegion* region) const {
    pfncpp_nvnTextureFlushTexels(this, view, region);
}

inline void Texture::InvalidateTexels(const TextureView* view, const CopyRegion* region) const {
    pfncpp_nvnTextureInvalidateTexels(this, view, region);
}

inline MemoryPool* Texture::GetMemoryPool() const {
    return pfncpp_nvnTextureGetMemoryPool(this);
}

inline ptrdiff_t Texture::GetMemoryOffset() const {
    return pfncpp_nvnTextureGetMemoryOffset(this);
}

inline int Texture::GetStorageSize() const {
    return pfncpp_nvnTextureGetStorageSize(this);
}

inline NVNboolean Texture::Compare(const Texture* texture) const {
    return pfncpp_nvnTextureCompare(this, texture);
}

inline uint64_t Texture::GetDebugID() const {
    return pfncpp_nvnTextureGetDebugID(this);
}

/*
inline RawStorageClass Texture::GetRawStorageClass() const {
    return pfncpp_nvnTextureGetRawStorageClass(this);
}
*/

inline TextureBuilder& TextureBuilder::SetDevice(Device* device) {
    pfncpp_nvnTextureBuilderSetDevice(this, device);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetDefaults() {
    pfncpp_nvnTextureBuilderSetDefaults(this);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetFlags(TextureFlags flags) {
    pfncpp_nvnTextureBuilderSetFlags(this, flags);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetTarget(TextureTarget target) {
    pfncpp_nvnTextureBuilderSetTarget(this, target);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetWidth(int width) {
    pfncpp_nvnTextureBuilderSetWidth(this, width);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetHeight(int height) {
    pfncpp_nvnTextureBuilderSetHeight(this, height);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetDepth(int depth) {
    pfncpp_nvnTextureBuilderSetDepth(this, depth);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetSize1D(int size) {
    pfncpp_nvnTextureBuilderSetSize1D(this, size);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetSize2D(int width, int height) {
    pfncpp_nvnTextureBuilderSetSize2D(this, width, height);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetSize3D(int width, int height, int depth) {
    pfncpp_nvnTextureBuilderSetSize3D(this, width, height, depth);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetLevels(int numLevels) {
    pfncpp_nvnTextureBuilderSetLevels(this, numLevels);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetFormat(Format format) {
    pfncpp_nvnTextureBuilderSetFormat(this, format);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetSamples(int samples) {
    pfncpp_nvnTextureBuilderSetSamples(this, samples);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetSwizzle(TextureSwizzle r, TextureSwizzle g,
                                                  TextureSwizzle b, TextureSwizzle a) {
    pfncpp_nvnTextureBuilderSetSwizzle(this, r, g, b, a);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetDepthStencilMode(TextureDepthStencilMode mode) {
    pfncpp_nvnTextureBuilderSetDepthStencilMode(this, mode);
    return *this;
}

inline size_t TextureBuilder::GetStorageSize() const {
    return pfncpp_nvnTextureBuilderGetStorageSize(this);
}

inline size_t TextureBuilder::GetStorageAlignment() const {
    return pfncpp_nvnTextureBuilderGetStorageAlignment(this);
}

inline TextureBuilder& TextureBuilder::SetStorage(MemoryPool* pool, ptrdiff_t offset) {
    pfncpp_nvnTextureBuilderSetStorage(this, pool, offset);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetPackagedTextureData(const void* data) {
    pfncpp_nvnTextureBuilderSetPackagedTextureData(this, data);
    return *this;
}

inline TextureBuilder&
TextureBuilder::SetPackagedTextureLayout(const PackagedTextureLayout* layout) {
    pfncpp_nvnTextureBuilderSetPackagedTextureLayout(this, layout);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetStride(ptrdiff_t stride) {
    pfncpp_nvnTextureBuilderSetStride(this, stride);
    return *this;
}

inline TextureBuilder& TextureBuilder::SetGLTextureName(uint32_t name) {
    pfncpp_nvnTextureBuilderSetGLTextureName(this, name);
    return *this;
}

inline NVNstorageClass TextureBuilder::GetStorageClass() const {
    return pfncpp_nvnTextureBuilderGetStorageClass(this);
}

inline const Device* TextureBuilder::GetDevice() const {
    return pfncpp_nvnTextureBuilderGetDevice(this);
}

inline TextureFlags TextureBuilder::GetFlags() const {
    return pfncpp_nvnTextureBuilderGetFlags(this);
}

inline TextureTarget TextureBuilder::GetTarget() const {
    return pfncpp_nvnTextureBuilderGetTarget(this);
}

inline int TextureBuilder::GetWidth() const {
    return pfncpp_nvnTextureBuilderGetWidth(this);
}

inline int TextureBuilder::GetHeight() const {
    return pfncpp_nvnTextureBuilderGetHeight(this);
}

inline int TextureBuilder::GetDepth() const {
    return pfncpp_nvnTextureBuilderGetDepth(this);
}

inline int TextureBuilder::GetLevels() const {
    return pfncpp_nvnTextureBuilderGetLevels(this);
}

inline Format TextureBuilder::GetFormat() const {
    return pfncpp_nvnTextureBuilderGetFormat(this);
}

inline int TextureBuilder::GetSamples() const {
    return pfncpp_nvnTextureBuilderGetSamples(this);
}

inline void TextureBuilder::GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b,
                                       TextureSwizzle* a) const {
    pfncpp_nvnTextureBuilderGetSwizzle(this, r, g, b, a);
}

inline TextureDepthStencilMode TextureBuilder::GetDepthStencilMode() const {
    return pfncpp_nvnTextureBuilderGetDepthStencilMode(this);
}

inline const void* TextureBuilder::GetPackagedTextureData() const {
    return pfncpp_nvnTextureBuilderGetPackagedTextureData(this);
}

inline NVNboolean TextureBuilder::GetPackagedTextureLayout(PackagedTextureLayout* layout) const {
    return pfncpp_nvnTextureBuilderGetPackagedTextureLayout(this, layout);
}

inline ptrdiff_t TextureBuilder::GetStride() const {
    return pfncpp_nvnTextureBuilderGetStride(this);
}

inline void TextureBuilder::GetSparseTileLayout(TextureSparseTileLayout* layout) const {
    pfncpp_nvnTextureBuilderGetSparseTileLayout(this, layout);
}

inline uint32_t TextureBuilder::GetGLTextureName() const {
    return pfncpp_nvnTextureBuilderGetGLTextureName(this);
}

inline size_t TextureBuilder::GetZCullStorageSize() const {
    return pfncpp_nvnTextureBuilderGetZCullStorageSize(this);
}

inline MemoryPool* TextureBuilder::GetMemoryPool() const {
    return pfncpp_nvnTextureBuilderGetMemoryPool(this);
}

inline ptrdiff_t TextureBuilder::GetMemoryOffset() const {
    return pfncpp_nvnTextureBuilderGetMemoryOffset(this);
}

/*
inline RawStorageClass TextureBuilder::GetRawStorageClass() const {
    return pfncpp_nvnTextureBuilderGetRawStorageClass(this);
}
*/

inline TextureView& TextureView::SetDefaults() {
    pfncpp_nvnTextureViewSetDefaults(this);
    return *this;
}

inline TextureView& TextureView::SetLevels(int baseLevel, int numLevels) {
    pfncpp_nvnTextureViewSetLevels(this, baseLevel, numLevels);
    return *this;
}

inline TextureView& TextureView::SetLayers(int minLayer, int numLayers) {
    pfncpp_nvnTextureViewSetLayers(this, minLayer, numLayers);
    return *this;
}

inline TextureView& TextureView::SetFormat(Format format) {
    pfncpp_nvnTextureViewSetFormat(this, format);
    return *this;
}

inline TextureView& TextureView::SetSwizzle(TextureSwizzle r, TextureSwizzle g, TextureSwizzle b,
                                            TextureSwizzle a) {
    pfncpp_nvnTextureViewSetSwizzle(this, r, g, b, a);
    return *this;
}

inline TextureView& TextureView::SetDepthStencilMode(TextureDepthStencilMode mode) {
    pfncpp_nvnTextureViewSetDepthStencilMode(this, mode);
    return *this;
}

inline TextureView& TextureView::SetTarget(TextureTarget target) {
    pfncpp_nvnTextureViewSetTarget(this, target);
    return *this;
}

inline NVNboolean TextureView::GetLevels(int* baseLevel, int* numLevels) const {
    return pfncpp_nvnTextureViewGetLevels(this, baseLevel, numLevels);
}

inline NVNboolean TextureView::GetLayers(int* minLayer, int* numLayers) const {
    return pfncpp_nvnTextureViewGetLayers(this, minLayer, numLayers);
}

inline NVNboolean TextureView::GetFormat(Format* format) const {
    return pfncpp_nvnTextureViewGetFormat(this, format);
}

inline NVNboolean TextureView::GetSwizzle(TextureSwizzle* r, TextureSwizzle* g, TextureSwizzle* b,
                                          TextureSwizzle* a) const {
    return pfncpp_nvnTextureViewGetSwizzle(this, r, g, b, a);
}

inline NVNboolean TextureView::GetDepthStencilMode(TextureDepthStencilMode* mode) const {
    return pfncpp_nvnTextureViewGetDepthStencilMode(this, mode);
}

inline NVNboolean TextureView::GetTarget(TextureTarget* target) const {
    return pfncpp_nvnTextureViewGetTarget(this, target);
}

inline NVNboolean TextureView::Compare(const TextureView* view) const {
    return pfncpp_nvnTextureViewCompare(this, view);
}

inline SamplerBuilder& SamplerBuilder::SetDevice(Device* device) {
    pfncpp_nvnSamplerBuilderSetDevice(this, device);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetDefaults() {
    pfncpp_nvnSamplerBuilderSetDefaults(this);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetMinMagFilter(MinFilter min, MagFilter mag) {
    pfncpp_nvnSamplerBuilderSetMinMagFilter(this, min, mag);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetWrapMode(WrapMode s, WrapMode t, WrapMode r) {
    pfncpp_nvnSamplerBuilderSetWrapMode(this, s, t, r);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetLodClamp(float min, float max) {
    pfncpp_nvnSamplerBuilderSetLodClamp(this, min, max);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetLodBias(float bias) {
    pfncpp_nvnSamplerBuilderSetLodBias(this, bias);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetCompare(CompareMode mode, CompareFunc func) {
    pfncpp_nvnSamplerBuilderSetCompare(this, mode, func);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetBorderColor(const float* borderColor) {
    pfncpp_nvnSamplerBuilderSetBorderColor(this, borderColor);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetBorderColori(const int* borderColor) {
    pfncpp_nvnSamplerBuilderSetBorderColori(this, borderColor);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetBorderColorui(const uint32_t* borderColor) {
    pfncpp_nvnSamplerBuilderSetBorderColorui(this, borderColor);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetMaxAnisotropy(float maxAniso) {
    pfncpp_nvnSamplerBuilderSetMaxAnisotropy(this, maxAniso);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetReductionFilter(SamplerReduction filter) {
    pfncpp_nvnSamplerBuilderSetReductionFilter(this, filter);
    return *this;
}

inline SamplerBuilder& SamplerBuilder::SetLodSnap(float f) {
    pfncpp_nvnSamplerBuilderSetLodSnap(this, f);
    return *this;
}

inline const Device* SamplerBuilder::GetDevice() const {
    return pfncpp_nvnSamplerBuilderGetDevice(this);
}

inline void SamplerBuilder::GetMinMagFilter(MinFilter* min, MagFilter* mag) const {
    pfncpp_nvnSamplerBuilderGetMinMagFilter(this, min, mag);
}

inline void SamplerBuilder::GetWrapMode(WrapMode* s, WrapMode* t, WrapMode* r) const {
    pfncpp_nvnSamplerBuilderGetWrapMode(this, s, t, r);
}

inline void SamplerBuilder::GetLodClamp(float* min, float* max) const {
    pfncpp_nvnSamplerBuilderGetLodClamp(this, min, max);
}

inline float SamplerBuilder::GetLodBias() const {
    return pfncpp_nvnSamplerBuilderGetLodBias(this);
}

inline void SamplerBuilder::GetCompare(CompareMode* mode, CompareFunc* func) const {
    pfncpp_nvnSamplerBuilderGetCompare(this, mode, func);
}

inline void SamplerBuilder::GetBorderColor(float* borderColor) const {
    pfncpp_nvnSamplerBuilderGetBorderColor(this, borderColor);
}

inline void SamplerBuilder::GetBorderColori(int* borderColor) const {
    pfncpp_nvnSamplerBuilderGetBorderColori(this, borderColor);
}

inline void SamplerBuilder::GetBorderColorui(uint32_t* borderColor) const {
    pfncpp_nvnSamplerBuilderGetBorderColorui(this, borderColor);
}

inline float SamplerBuilder::GetMaxAnisotropy() const {
    return pfncpp_nvnSamplerBuilderGetMaxAnisotropy(this);
}

inline SamplerReduction SamplerBuilder::GetReductionFilter() const {
    return pfncpp_nvnSamplerBuilderGetReductionFilter(this);
}

inline float SamplerBuilder::GetLodSnap() const {
    return pfncpp_nvnSamplerBuilderGetLodSnap(this);
}

inline NVNboolean Sampler::Initialize(const SamplerBuilder* builder) {
    return pfncpp_nvnSamplerInitialize(this, builder);
}

inline void Sampler::Finalize() {
    pfncpp_nvnSamplerFinalize(this);
}

inline void Sampler::SetDebugLabel(const char* label) {
    pfncpp_nvnSamplerSetDebugLabel(this, label);
}

inline void Sampler::GetMinMagFilter(MinFilter* min, MagFilter* mag) const {
    pfncpp_nvnSamplerGetMinMagFilter(this, min, mag);
}

inline void Sampler::GetWrapMode(WrapMode* s, WrapMode* t, WrapMode* r) const {
    pfncpp_nvnSamplerGetWrapMode(this, s, t, r);
}

inline void Sampler::GetLodClamp(float* min, float* max) const {
    pfncpp_nvnSamplerGetLodClamp(this, min, max);
}

inline float Sampler::GetLodBias() const {
    return pfncpp_nvnSamplerGetLodBias(this);
}

inline void Sampler::GetCompare(CompareMode* mode, CompareFunc* func) const {
    pfncpp_nvnSamplerGetCompare(this, mode, func);
}

inline void Sampler::GetBorderColor(float* borderColor) const {
    pfncpp_nvnSamplerGetBorderColor(this, borderColor);
}

inline void Sampler::GetBorderColori(int* borderColor) const {
    pfncpp_nvnSamplerGetBorderColori(this, borderColor);
}

inline void Sampler::GetBorderColorui(uint32_t* borderColor) const {
    pfncpp_nvnSamplerGetBorderColorui(this, borderColor);
}

inline float Sampler::GetMaxAnisotropy() const {
    return pfncpp_nvnSamplerGetMaxAnisotropy(this);
}

inline SamplerReduction Sampler::GetReductionFilter() const {
    return pfncpp_nvnSamplerGetReductionFilter(this);
}

inline NVNboolean Sampler::Compare(const Sampler* sampler) const {
    return pfncpp_nvnSamplerCompare(this, sampler);
}

inline uint64_t Sampler::GetDebugID() const {
    return pfncpp_nvnSamplerGetDebugID(this);
}

inline NVNboolean Sync::Initialize(Device* device) {
    return pfncpp_nvnSyncInitialize(this, device);
}

inline void Sync::Finalize() {
    pfncpp_nvnSyncFinalize(this);
}

inline void Sync::SetDebugLabel(const char* label) {
    pfncpp_nvnSyncSetDebugLabel(this, label);
}

inline SyncWaitResult Sync::Wait(uint64_t timeoutNs) const {
    return pfncpp_nvnSyncWait(this, timeoutNs);
}

inline NVNboolean Window::Initialize(const WindowBuilder* builder) {
    return pfncpp_nvnWindowInitialize(this, builder);
}

inline void Window::Finalize() {
    pfncpp_nvnWindowFinalize(this);
}

inline void Window::SetDebugLabel(const char* label) {
    pfncpp_nvnWindowSetDebugLabel(this, label);
}

inline WindowAcquireTextureResult Window::AcquireTexture(Sync* textureAvailableSync,
                                                         int* textureIndex) {
    return pfncpp_nvnWindowAcquireTexture(this, textureAvailableSync, textureIndex);
}

inline NVNnativeWindow Window::GetNativeWindow() const {
    return pfncpp_nvnWindowGetNativeWindow(this);
}

inline int Window::GetPresentInterval() const {
    return pfncpp_nvnWindowGetPresentInterval(this);
}

inline void Window::SetPresentInterval(int presentInterval) {
    pfncpp_nvnWindowSetPresentInterval(this, presentInterval);
}

inline void Window::SetCrop(int x, int y, int w, int h) {
    pfncpp_nvnWindowSetCrop(this, x, y, w, h);
}

inline void Window::GetCrop(Rectangle* rectangle) const {
    pfncpp_nvnWindowGetCrop(this, rectangle);
}

inline WindowBuilder& WindowBuilder::SetDevice(Device* device) {
    pfncpp_nvnWindowBuilderSetDevice(this, device);
    return *this;
}

inline WindowBuilder& WindowBuilder::SetDefaults() {
    pfncpp_nvnWindowBuilderSetDefaults(this);
    return *this;
}

inline WindowBuilder& WindowBuilder::SetNativeWindow(NVNnativeWindow nativeWindow) {
    pfncpp_nvnWindowBuilderSetNativeWindow(this, nativeWindow);
    return *this;
}

inline WindowBuilder& WindowBuilder::SetTextures(int numTextures, Texture* const* textures) {
    pfncpp_nvnWindowBuilderSetTextures(this, numTextures, textures);
    return *this;
}

inline WindowBuilder& WindowBuilder::SetPresentInterval(int presentInterval) {
    pfncpp_nvnWindowBuilderSetPresentInterval(this, presentInterval);
    return *this;
}

inline const Device* WindowBuilder::GetDevice() const {
    return pfncpp_nvnWindowBuilderGetDevice(this);
}

inline int WindowBuilder::GetNumTextures() const {
    return pfncpp_nvnWindowBuilderGetNumTextures(this);
}

inline const Texture* WindowBuilder::GetTexture(int i) const {
    return pfncpp_nvnWindowBuilderGetTexture(this, i);
}

inline NVNnativeWindow WindowBuilder::GetNativeWindow() const {
    return pfncpp_nvnWindowBuilderGetNativeWindow(this);
}

inline int WindowBuilder::GetPresentInterval() const {
    return pfncpp_nvnWindowBuilderGetPresentInterval(this);
}

inline EventBuilder& EventBuilder::SetDefaults() {
    pfncpp_nvnEventBuilderSetDefaults(this);
    return *this;
}

inline EventBuilder& EventBuilder::SetStorage(const MemoryPool* pool, int64_t size) {
    pfncpp_nvnEventBuilderSetStorage(this, pool, size);
    return *this;
}

inline const MemoryPool* EventBuilder::GetStorage(int64_t* i) const {
    return pfncpp_nvnEventBuilderGetStorage(this, i);
}

inline NVNboolean Event::Initialize(const EventBuilder* builder) {
    return pfncpp_nvnEventInitialize(this, builder);
}

inline void Event::Finalize() {
    pfncpp_nvnEventFinalize(this);
}

inline uint32_t Event::GetValue() const {
    return pfncpp_nvnEventGetValue(this);
}

inline void Event::Signal(EventSignalMode mode, uint32_t i) {
    pfncpp_nvnEventSignal(this, mode, i);
}

}  // namespace nvn