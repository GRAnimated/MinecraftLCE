/**
 * @file hid.h
 * @brief Functions that help process gamepad inputs.
 */

#pragma once

#include <nn/types.h>
#include <nn/util.h>
#include <nn/util/MathTypes.h>
#include <nn/util/util_BitFlagSet.h>

namespace nn {
namespace hid {
struct NpadHandheldState;
struct NpadStyleTag;

// todo: does something like this exist in nn?
typedef util::Color4u8Type Color4u8;

struct ControllerSupportArg {
    u8 mMinPlayerCount;
    u8 mMaxPlayerCount;
    u8 mTakeOverConnection;
    bool mLeftJustify;
    bool mPermitJoyconDual;
    bool mSingleMode;
    bool mUseColors;
    Color4u8 mColors[4];
    u8 mUsingControllerNames;
    char mControllerNames[4][0x81];
};

struct ControllerSupportResultInfo {
    int mPlayerCount;
    int mSelectedId;
};

struct AnalogStickState {
    int32_t x, y;
};

struct NpadButton;
struct NpadAttribute;
struct NpadId;

typedef nn::util::BitFlagSet<32, NpadAttribute> NpadAttributesSet;
typedef nn::util::BitFlagSet<64, NpadButton> NpadButtonSet;
typedef nn::util::BitFlagSet<32, NpadStyleTag> NpadStyleSet;
typedef uint32_t NpadIdType;

struct NpadBaseState {
    int64_t samplingNumber;
    NpadButtonSet buttons;
    AnalogStickState analogStickL;
    AnalogStickState analogStickR;
    NpadAttributesSet attributes;
};

struct NpadHandheldState : NpadBaseState {};
struct NpadJoyDualState : NpadBaseState {};
struct NpadFullKeyState : NpadBaseState {};
struct NpadJoyLeftState : NpadBaseState {};
struct NpadJoyRightState : NpadBaseState {};

void InitializeNpad();
void SetSupportedNpadIdType(const u32*, u64);
void SetSupportedNpadStyleSet(NpadStyleSet);
void GetNpadStyleSet(const u32&);
static int ShowControllerSupport(ControllerSupportResultInfo*, const ControllerSupportArg&);

void GetNpadStates(NpadHandheldState*, int, const u32&);
void GetNpadStates(NpadJoyDualState*, int, const u32&);
void GetNpadStates(NpadFullKeyState*, int, const u32&);
void GetNpadStates(NpadJoyLeftState*, int, const u32&);
void GetNpadStates(NpadJoyRightState*, int, const u32&);

}  // namespace hid
}  // namespace nn
