#pragma once

#include "C4JStorage.h"

class CStorage : public C4JStorage {
public:
    void Tick() override;
    void Init(unsigned int, const wchar_t*, const char*, int, int (*)(void*, C4JStorage::ESavingMessage, int),
              void*, const char*, void*) override;
    void SetGameSaveFolderTitle(const wchar_t* title) override;
    void SetSaveCacheFolderTitle(const wchar_t* title) override;
    void SetOptionsFolderTitle(const wchar_t* title) override;
    void SetCorruptSaveName(const wchar_t* name) override;
    void SetGameSaveFolderPrefix(const char* prefix) override;
    void SetMaxSaves(int max) override;
    void SetDefaultImages(unsigned char*, unsigned int, unsigned char*, unsigned int, unsigned char*,
                          unsigned int) override;
    void SetIncompleteSaveCallback(void (*)(void*, ESaveIncompleteType), void*) override;
    void SetSaveDisabled(bool disabled) override;
    bool GetSaveDisabled() override;
    void ResetSaveData() override;
    void DoesSaveExist(bool*) override;
    bool EnoughSpaceForAMinSaveGame() override;  // guessed type
    void GetSaveState() override;
    void GetSavesInfo(int, int (*)(void*, struct SAVE_DETAILS*, bool), void*,
                      const char*) override;  // TODO: what is SAVE_DETAILS?
    void ReturnSavesInfo() override;
    void ClearSavesInfo() override;
    void LoadSaveDataThumbnail(struct SAVE_INFO*, int (*)(void*, unsigned char*, unsigned int),
                               void*) override;  // TODO: what is SAVE_INFO? Probably that tEXt chunk
    void LoadSaveData(struct SAVE_INFO*, int (*)(void*, bool, bool),
                      void*) override;  // TODO: what is SAVE_INFO?
    void GetSaveSize() override;
    void GetSaveData(void*, unsigned int*) override;
    void field_B8() override;
    void field_C0() override;
    void field_C8() override;
    void field_D0() override;
    void SetSaveTitle(const wchar_t*) override;
    void field_E0() override;
    void field_E8() override;
    void field_F0() override;
    void field_F8() override;
    void field_100() override;
    void field_108() override;
    void field_110() override;
    void field_118() override;
    void field_120() override;
    void field_128() override;
    void field_130() override;
    void nullsub_1024() override;
    void nullsub_1023() override;
    void InitialiseProfileData(unsigned short, unsigned int, unsigned int, unsigned int*, int,
                               unsigned int*) override;
    void SetDefaultOptionsCallback(int (*)(void*, C4JStorage::PROFILESETTINGS*, int), void*) override;
    void SetOptionsDataCallback(int (*)(void*, int, unsigned short, C4JStorage::eOptionsCallback),
                                void*) override;
    void SetOldProfileVersionCallback(int (*)(void*, unsigned char*, unsigned short, int), void*) override;
    void field_168() override;
    void field_170() override;
    void ReadFromProfile(int, int) override;
    void field_180() override;
    void nullsub_1022() override;
    void field_190() override;
    void field_198() override;
    void field_1A0() override;
    void field_1A8() override;
    void nullsub_1025() override;
    void nullsub_1019() override;
    void field_1C0() override;
    void nullsub_1020() override;
    void field_1D0() override;
    void field_1D8() override;
    void field_1E0() override;
    void field_1E8() override;
    void SetOpenDirFn(int (*)(const char*, int*)) override;
    void SetReadDirFn(int (*)(int*, struct FSDirEntry*)) override;  // TODO: what is FSDirEntry?
    void SetCloseDirFn(int (*)(int*)) override;
    void SetDLCPackageRoot(const char*) override;
    void field_210() override;
    void field_218() override;
    void field_220() override;
    void field_228() override;
    void field_230() override;
    void field_238() override;
    void field_240() override;
    void field_24() override;   // TODO: seems to be templated
    void field_250() override;  // TODO: seems to be templated
    void field_258() override;
    void field_260() override;
    void field_268() override;
    void field_270() override;
    void field_278() override;
    void field_280() override;
    void field_288() override;
    void field_290() override;
    void field_298() override;

    static CStorage* sInstance;  // apparently there are 2 of these????
    char padding[0x18C8];
};
