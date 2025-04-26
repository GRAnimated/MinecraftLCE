#pragma once

class C4JStorage {
    public:
    enum ESavingMessage {};
    enum ESaveIncompleteType {};
    enum eOptionsCallback {}; // why do you guys keep switching casing style

    class PROFILESETTINGS {};

    virtual void Tick() = 0;
#warning Last param may be incorrect. Xbox One Edition did change the signature though so this could be correct. It just doesn't make sense to pass a function/jump in place of a bool *.
    virtual void Init(unsigned int, const wchar_t *, const char *, int, int (*)(void *, C4JStorage::ESavingMessage, int), void *, const char *, void *) = 0;
    virtual void SetGameSaveFolderTitle(const wchar_t *title) = 0;
    virtual void SetSaveCacheFolderTitle(const wchar_t *title) = 0;
    virtual void SetOptionsFolderTitle(const wchar_t *title) = 0;
    virtual void SetCorruptSaveName(const wchar_t *name) = 0;
    virtual void SetGameSaveFolderPrefix(const char *prefix) = 0;
    virtual void SetMaxSaves(int max) = 0;
    virtual void SetDefaultImages(unsigned char *, unsigned int, unsigned char *, unsigned int, unsigned char *, unsigned int) = 0;
    virtual void SetIncompleteSaveCallback(void (*)(void *, ESaveIncompleteType), void *) = 0;
    virtual void SetSaveDisabled(bool disabled) = 0;
    virtual bool GetSaveDisabled() = 0;
    virtual void ResetSaveData() = 0;
    virtual void DoesSaveExist(bool *) = 0;
    virtual bool EnoughSpaceForAMinSaveGame() = 0; // guessed type
    virtual void GetSaveState() = 0;
    virtual void GetSavesInfo(int, int (*)(void *, struct SAVE_DETAILS *, bool), void *, const char *) = 0; // TODO: what is SAVE_DETAILS?
    virtual void ReturnSavesInfo() = 0;
    virtual void ClearSavesInfo() = 0;
    virtual void LoadSaveDataThumbnail(struct SAVE_INFO *, int (*)(void *, unsigned char *, unsigned int), void *) = 0; // TODO: what is SAVE_INFO? Probably that tEXt chunk
    virtual void LoadSaveData(struct SAVE_INFO *, int (*)(void *, bool, bool), void *) = 0; // TODO: what is SAVE_INFO?
    virtual void GetSaveSize() = 0;
    virtual void GetSaveData(void *, unsigned int *) = 0;
    virtual void field_B8() = 0;
    virtual void field_C0() = 0;
    virtual void field_C8() = 0;
    virtual void field_D0() = 0;
    virtual void SetSaveTitle(const wchar_t *) = 0;
    virtual void field_E0() = 0;
    virtual void field_E8() = 0;
    virtual void field_F0() = 0;
    virtual void field_F8() = 0;
    virtual void field_100() = 0;
    virtual void field_108() = 0;
    virtual void field_110() = 0;
    virtual void field_118() = 0;
    virtual void field_120() = 0;
    virtual void field_128() = 0;
    virtual void field_130() = 0;
    virtual void nullsub_1024() = 0;
    virtual void nullsub_1023() = 0;
    virtual void InitialiseProfileData(unsigned short, unsigned int, unsigned int, unsigned int *, int, unsigned int *) = 0;
    virtual void SetDefaultOptionsCallback(int (*)(void *, C4JStorage::PROFILESETTINGS *, int), void *) = 0;
    virtual void SetOptionsDataCallback(int (*)(void *, int, unsigned short, C4JStorage::eOptionsCallback), void *) = 0;
    virtual void SetOldProfileVersionCallback(int (*)(void *, unsigned char *, unsigned short, int), void *) = 0;
    virtual void field_168() = 0;
    virtual void field_170() = 0;
    virtual void ReadFromProfile(int, int) = 0;
    virtual void field_180() = 0;
    virtual void nullsub_1022() = 0;
    virtual void field_190() = 0;
    virtual void field_198() = 0;
    virtual void field_1A0() = 0;
    virtual void field_1A8() = 0;
    virtual void nullsub_1025() = 0;
    virtual void nullsub_1019() = 0;
    virtual void field_1C0() = 0;
    virtual void nullsub_1020() = 0;
    virtual void field_1D0() = 0;
    virtual void field_1D8() = 0;
    virtual void field_1E0() = 0;
    virtual void field_1E8() = 0;
    virtual void SetOpenDirFn(int (*)(const char *, int *)) = 0;
    virtual void SetReadDirFn(int (*)(int *, struct FSDirEntry *)) = 0; // TODO: what is FSDirEntry?
    virtual void SetCloseDirFn(int (*)(int *)) = 0;
    virtual void SetDLCPackageRoot(const char *) = 0;
    virtual void field_210() = 0;
    virtual void field_218() = 0;
    virtual void field_220() = 0;
    virtual void field_228() = 0;
    virtual void field_230() = 0;
    virtual void field_238() = 0;
    virtual void field_240() = 0;
    virtual void field_24() = 0; // TODO: seems to be templated
    virtual void field_250() = 0; // TODO: seems to be templated
    virtual void field_258() = 0;
    virtual void field_260() = 0;
    virtual void field_268() = 0;
    virtual void field_270() = 0;
    virtual void field_278() = 0;
    virtual void field_280() = 0;
    virtual void field_288() = 0;
    virtual void field_290() = 0;
    virtual void field_298() = 0;
};
