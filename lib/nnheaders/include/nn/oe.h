/**
 * @file oe.h
 * @brief Extenstions to OS functions.
 */

#pragma once

#include <nn/settings.h>
#include <nn/types.h>

namespace nn::oe {

enum OperationMode {
    OperationMode_Handheld,
    OperationMode_Docked,
};

enum PerformanceMode {
    PerformanceMode_Normal = 0,
    PerformanceMode_Boost = 1,
    PerformanceMode_Invalid = -1,
};

typedef s32 FocusHandlingMode;

struct DisplayVersion {
    char name[16];
};

void Initialize();
void SetPerformanceConfiguration(nn::oe::PerformanceMode, s32);
OperationMode GetOperationMode();
PerformanceMode GetPerformanceMode();
void SetResumeNotificationEnabled(bool);
void SetOperationModeChangedNotificationEnabled(bool);
void SetPerformanceModeChangedNotificationEnabled(bool);
void SetFocusHandlingMode(nn::oe::FocusHandlingMode);
bool TryPopNotificationMessage(u32*);
s32 GetCurrentFocusState();
void EnableGamePlayRecording(void*, u64);
bool IsUserInactivityDetectionTimeExtended();
void SetUserInactivityDetectionTimeExtended(bool);
void FinishStartupLogo();
nn::settings::LanguageCode GetDesiredLanguage();
void GetDisplayVersion(DisplayVersion*);
bool TryPopLaunchParameter(size_t*, void*, size_t);

}  // namespace nn::oe
