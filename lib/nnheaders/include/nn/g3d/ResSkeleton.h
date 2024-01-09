#pragma once

#include <nn/nn_BitTypes.h>
#include <nn/util/util_BinTypes.h>
#include <nn/util/util_BinaryFormat.h>
#include <nn/util/util_ResDic.h>
#include "nn/gfx/gfx_ResUserData.h"
#include "nn/util/MathTypes.h"

namespace nn::g3d {

struct ResBoneData {
    nn::util::BinPtrToString pName;
    nn::util::BinTPtr<nn::gfx::ResUserData> pUserDataArray;
    nn::util::BinTPtr<nn::util::ResDic> pUserDataDic;
#ifndef UKING_NX_V150
    // This array is present in Pokémon Sword and Shield's version of nnSdk but not in BotW 1.5.0.
    uint8_t reserved[16];
#endif
    uint16_t index;
    uint16_t parentIndex;
    int16_t smoothMtxIndex;
    int16_t rigidMtxIndex;
    uint16_t billboardIndex;
    uint16_t userDataCount;
    nn::Bit32 flag;
    nn::util::Float3 scale;
    union {
        nn::util::Float4 quat;
        nn::util::Float3 euler;
    } rotate;
    nn::util::Float3 translate;
};

class ResBone : public nn::util::AccessorBase<ResBoneData> {
public:
    enum Shift {
        Shift_Hierarchy = 4,
        Shift_Rot = 12,
        Shift_Billboard = 16,
        Shift_MirroringState = 20,
        Shift_Transform = 23,
    };

    enum Flag {
        Flag_Visibility = 0x1 << 0,

        Flag_BillboardNone = 0x0 << Shift_Billboard,
        Flag_BillboardChild = 0x1 << Shift_Billboard,
        Flag_BillboardWorldViewVector = 0x2 << Shift_Billboard,
        Flag_BillboardWorldViewPoint = 0x3 << Shift_Billboard,
        Flag_BillboardScreenViewVector = 0x4 << Shift_Billboard,
        Flag_BillboardScreenViewPoint = 0x5 << Shift_Billboard,
        Flag_BillboardYaxisViewVector = 0x6 << Shift_Billboard,
        Flag_BillboardYaxisViewPoint = 0x7 << Shift_Billboard,
        Flag_BillboardMax = Flag_BillboardYaxisViewPoint,

        Flag_SegmentScaleCompensate = 0x1 << Shift_Transform,
        Flag_ScaleUniform = 0x2 << Shift_Transform,
        Flag_ScaleVolumeOne = 0x4 << Shift_Transform,
        Flag_RotateZero = 0x8 << Shift_Transform,
        Flag_TranslateZero = 0x10 << Shift_Transform,
        Flag_ScaleOne = Flag_ScaleVolumeOne | Flag_ScaleUniform,
        Flag_RotTransZero = Flag_RotateZero | Flag_TranslateZero,
        Flag_Identity = Flag_ScaleOne | Flag_RotateZero | Flag_TranslateZero,
        Flag_HiScaleUniform = Flag_ScaleUniform << Shift_Hierarchy,
        Flag_HiScaleVolumeOne = Flag_ScaleVolumeOne << Shift_Hierarchy,
        Flag_HiRotateZero = Flag_RotateZero << Shift_Hierarchy,
        Flag_HiTranslateZero = Flag_TranslateZero << Shift_Hierarchy,
        Flag_HiScaleOne = Flag_ScaleOne << Shift_Hierarchy,
        Flag_HiRotTransZero = Flag_RotTransZero << Shift_Hierarchy,
        Flag_HiIdentity = Flag_Identity << Shift_Hierarchy,
        Flag_BillboardIndexNone = 0xFFFF,
    };

    enum Mask {
        Mask_Rot = 0x7 << Shift_Rot,
        Mask_Billboard = 0x7 << Shift_Billboard,
        Mask_MirroringState = 0x7 << Shift_MirroringState,
        Mask_Transform = Flag_SegmentScaleCompensate | Flag_Identity
    };

    static constexpr int InvalidBoneIndex = 0xffff;

    ResBone(const ResBone&) = delete;
    auto operator=(const nn::g3d::ResBone&) = delete;

    int GetIndex() const { return index; }
    const char* GetName() const { return pName.Get()->GetData(); }
    int GetSmoothMtxIndex() const { return smoothMtxIndex; }
    int GetRigidMtxIndex() const { return rigidMtxIndex; }
    int GetParentIndex() const { return parentIndex; }
    nn::Bit32 GetRotateMode() const { return flag & Mask_Rot; }
    nn::Bit32 GetBillboardMode() const { return flag & Mask_Billboard; }
    nn::Bit32 GetMirroringState() const { return flag & Mask_MirroringState; }
    bool IsVisible() const { return (flag & Flag_Visibility) != 0; }
    nn::util::Float3& GetScale() { return scale; }
    const nn::util::Float3& GetScale() const { return scale; }
    nn::util::Float3& GetTranslate() { return translate; }
    const nn::util::Float3& GetTranslate() const { return translate; }
    nn::util::Float3& GetRotateEuler() { return rotate.euler; }
    const nn::util::Float3& GetRotateEuler() const { return rotate.euler; }
    nn::util::Float4& GetRotateQuat() { return rotate.quat; }
    const nn::util::Float4& GetRotateQuat() const { return rotate.quat; }
    int GetUserDataCount() const { return userDataCount; }

    nn::gfx::ResUserData* FindUserData(const char* key) {
        int index = FindUserDataIndex(key);
        if (index == util::ResDic::Npos)
            return nullptr;
        return GetUserData(index);
    }

    const nn::gfx::ResUserData* FindUserData(const char* key) const {
        int index = FindUserDataIndex(key);
        if (index == util::ResDic::Npos)
            return nullptr;
        return GetUserData(index);
    }

    int FindUserDataIndex(const char* key) const {
        const util::ResDic* dict = pUserDataDic.Get();
        if (dict == nullptr)
            return util::ResDic::Npos;
        return dict->FindIndex(key);
    }

    const char* GetUserDataName(int index) const {
        const util::ResDic* dict = pUserDataDic.Get();
        if (dict == nullptr)
            return nullptr;
        return dict->GetKey(index).data();
    }

    nn::gfx::ResUserData* GetUserData(int index) { return &pUserDataArray.Get()[index]; }

    const nn::gfx::ResUserData* GetUserData(int index) const {
        return &pUserDataArray.Get()[index];
    }
};

struct ResSkeletonData {
    nn::util::BinaryBlockHeader blockHeader;
    nn::util::BinTPtr<nn::util::ResDic> pBoneDic;
    nn::util::BinTPtr<nn::g3d::ResBone> pBoneArray;
    nn::util::BinTPtr<short> pMtxToBoneTable;
    nn::util::BinTPtr<nn::util::FloatColumnMajor4x3> pInvModelMatrixArray;
    nn::util::BinPtr pUserPtr;
    nn::util::BinTPtr<short> pMirroringBoneTable;
    uint8_t reserved1[8];
    nn::Bit32 flag;
    uint16_t boneCount;
    uint16_t smoothMtxCount;
    uint16_t rigidMtxCount;
    uint8_t reserved2[6];
};

class ResSkeleton : public nn::util::AccessorBase<nn::g3d::ResSkeletonData> {
public:
    static constexpr uint32_t Signature = util::MakeSignature('F', 'S', 'K', 'L');

    enum Shift {
        Shift_MirroringMode = 6,
        Shift_Scale = 8,
        Shift_Rot = 12,
    };

    enum Mask {
        Mask_MirroringMode = 0x3 << Shift_MirroringMode,
        Mask_Scale = 0x3 << Shift_Scale,
        Mask_Rot = ResBone::Mask_Rot,
        Mask_TransForm = Mask_Scale | Mask_Rot
    };

    enum ResetGuardFlag {
        ResetGuardFlag_None = 0,
        ResetGuardFlag_UserPtr = 1,
    };

    ResSkeleton(const ResSkeleton&) = delete;
    auto operator=(const ResSkeleton&) = delete;

    void Reset();
    void Reset(nn::Bit32);

    int GetSmoothMtxCount() const { return smoothMtxCount; }
    int GetRigidMtxCount() const { return rigidMtxCount; }
    int GetMtxCount() const { return GetSmoothMtxCount() + GetRigidMtxCount(); }
    nn::Bit32 GetScaleMode() const { return flag & Mask_Scale; }
    nn::Bit32 GetRotateMode() const { return flag & Mask_Rot; }
    nn::Bit32 GetMirroringMode() const { return flag & Mask_MirroringMode; }
    bool HasMirroringInfo() const { return pMirroringBoneTable.Get() != nullptr; }
    int GetBranchEndIndex(int) const;
    void SetUserPtr(void* ptr) { pUserPtr.Set(ptr); }
    void* GetUserPtr() { return pUserPtr.Get(); }
    const void* GetUserPtr() const { return pUserPtr.Get(); }
    void UpdateBillboardMode();

    int GetBoneCount() const { return boneCount; }

    nn::g3d::ResBone* FindBone(const char* name) {
        int index = FindBoneIndex(name);
        if (index == util::ResDic::Npos)
            return nullptr;
        return GetBone(index);
    }

    const nn::g3d::ResBone* FindBone(const char* name) const {
        int index = FindBoneIndex(name);
        if (index == util::ResDic::Npos)
            return nullptr;
        return GetBone(index);
    }

    int FindBoneIndex(const char* name) const {
        auto* dict = pBoneDic.Get();
        if (dict == nullptr)
            return util::ResDic::Npos;
        return dict->FindIndex(name);
    }

    const char* GetBoneName(int index) const {
        auto* dict = pBoneDic.Get();
        if (dict == nullptr)
            return nullptr;
        return dict->GetKey(index).data();
    }

    nn::g3d::ResBone* GetBone(int index) { return &pBoneArray.Get()[index]; }
    const nn::g3d::ResBone* GetBone(int index) const { return &pBoneArray.Get()[index]; }

    int GetMirroredBoneIndex(int index) const { return pMirroringBoneTable.Get()[index]; }
};

}  // namespace nn::g3d
