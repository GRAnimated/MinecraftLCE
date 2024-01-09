/**
 * @file vi.h
 * @brief Visual interface implementation.
 */

#pragma once

#include <nn/os.h>
#include <nn/types.h>

namespace nn {
namespace vi {

enum LayerStack {
    Default = 0,
    Lcd = 1,
    Screenshot = 2,
    Recording = 3,
    LastFrame = 4,
    Arbitrary = 5,
    ApplicationForDebug = 6,
    Null = 10,
};

struct DisplayName {
    static constexpr u32 maxNameLen = 64;
    char data[maxNameLen];
};

struct DisplayInfo {
    DisplayName name;
    bool hasLayerLimit;
    s64 maxLayers;
    s64 maxWidth;
    s64 maxHeight;
};

// Needs to be >128 bits, nnsdk uses X8 (indirect result register)
struct IDisplayService {
    uintptr_t servicePtr;
    uintptr_t _x8[5];
};

typedef IDisplayService IManagerDisplayService;
typedef IDisplayService ISystemDisplayService;

class Display;
class Layer;
class NativeWindow;

struct LayerCreationSettings {
    LayerCreationSettings(void);
    LayerCreationSettings(s32 width, s32 height);
    s32 GetWidth(void) const;
    void SetWidth(s32 width);
    s32 GetHeight(void) const;
    void SetHeight(s32 height);
    void SetFullscreen(bool isFullscreen);
    bool IsFullscreen(void) const;
    void SetVisibility(bool isVisible);
    bool IsVisible(void) const;

private:
    s32 width;
    s32 height;

    union {
        u32 rawFlags;
        struct {
            bool fullScreen : 1;  // defaults to false
            bool visible : 1;     // defaults to true
        };
    };
};

enum ScalingMode { None, Exact, FitLayer, ScaleAndCrop, PreserveAspectRatio };

void Initialize();
void InitializeMinimum();
void Finalize();
void FinalizeMinimum();

IDisplayService GetService();
ISystemDisplayService GetSystemService();
IManagerDisplayService GetManagerService();

Result SetContentVisibility(bool visibility);
Result ListDisplays(nn::vi::DisplayInfo* outInfo, int count);
Result OpenDefaultDisplay(nn::vi::Display** outDisplay);
Result OpenDisplay(nn::vi::Display** outDisplay, const char* displayName);
Result CloseDisplay(nn::vi::Display* inDisplay);
Result GetDisplayVsyncEvent(nn::os::SystemEventType* outEvent, nn::vi::Display* inDisplay);
s32 GetZOrderCountMin(const nn::vi::Display* inDisplay);
s32 GetZOrderCountMax(const nn::vi::Display* inDisplay);
Result GetDisplayLogicalResolution(s32* width, s32* height, const nn::vi::Display* inDisplay);
Result GetDisplayResolution(s32* width, s32* height, const nn::vi::Display* inDisplay);
u64 GetDisplayIdWithValidation(const nn::vi::Display* inDisplay);
Result GetLatestFrameNumber(u64* pOutFrameNumber, const Layer* pLayer);

Result CreateLayer(nn::vi::Layer** outLayer, nn::vi::Display* inDisplay);
Result CreateLayer(nn::vi::Layer** outLayer, nn::vi::Display* inDisplay,
                   const nn::vi::LayerCreationSettings* inSettings);
Result CreateLayer(nn::vi::Layer** outLayer, nn::vi::Display* inDisplay, s32 width, s32 height);
void DestroyLayer(nn::vi::Layer* inLayer);
Result GetNativeWindow(void** outWindow, nn::vi::Layer* inLayer);

Result SetLayerScalingMode(nn::vi::Layer* layer, nn::vi::ScalingMode scalingMode);
Result SetLayerPosition(nn::vi::Layer* inLayer, float x, float y);
Result SetLayerSize(nn::vi::Layer* inLayer, s32 width, s32 height);
Result SetLayerZ(nn::vi::Layer* inLayer, s32 z);
Result GetLayerZ(s32* z, const nn::vi::Layer* inLayer);
Result SetLayerVisibility(nn::vi::Layer* inLayer, bool isVisible);
Result SetLayerAlpha(nn::vi::Layer* inLayer, float alpha);

Result AddToLayerStack(nn::vi::Layer* inLayer, nn::vi::LayerStack layerStackType);
Result RemoveFromLayerStack(nn::vi::Layer* inLayer, nn::vi::LayerStack layerStackType);
u64 GetLayerIdWithValidation(const nn::vi::Layer* inLayer);
}  // namespace vi
}  // namespace nn
