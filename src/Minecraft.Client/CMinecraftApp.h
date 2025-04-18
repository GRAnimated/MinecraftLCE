#pragma once
#include "Minecraft.World/level/levelgen/LevelGenerationOptions.h"

#include "Minecraft.World/level/gamemode/GameType.h"
#include "eGameHostOption.h"

enum eTMSAction {};
enum eFileExtensionType {};
enum eTMSFileType {};
enum eTPDFileType {};
class LevelChunk;
class PlayerUID;

class CMinecraftApp {
public:
    CMinecraftApp();
    virtual ~CMinecraftApp();
    virtual void CaptureScreenshot(int);
    virtual void SetRichPresenceContext(int, int) = 0;
    virtual void FatalLoadError(wchar_t const*, ...);
    virtual void StoreLaunchData();
    virtual void ExitGame();
    virtual void RunFrame();
    virtual void CaptureSaveThumbnail() = 0;
    virtual void GetSaveThumbnail(unsigned char**, unsigned int*) = 0;
    virtual void ReleaseSaveThumbnail() = 0;
    virtual void GetScreenshot(int, unsigned char**, unsigned int*) = 0;
    virtual void ReadBannedList(int, eTMSAction, bool) = 0;
    virtual void LoadLocalTMSFile(wchar_t*) = 0;
    virtual void LoadLocalTMSFile(wchar_t*, eFileExtensionType) = 0;
    virtual void FreeLocalTMSFiles(eTMSFileType) = 0;
    virtual void GetLocalTMSFileIndex(wchar_t*, bool, eFileExtensionType) = 0;
    virtual void GetTMSGlobalFileListRead();
    virtual void GetTMSDLCInfoRead();
    virtual void GetTMSXUIDsFileRead();
    virtual void GetFileFromTPD(eTPDFileType, unsigned char*, unsigned int, unsigned char**, unsigned int*);

    int GetGameHostOption(unsigned int, eGameHostOption option);
    bool GetChangingSessionType();
    bool GetGameStarted();
    static void* getSkinIdFromPath(const std::wstring& path);
    bool isXuidNotch(PlayerUID* id);
    static void StaticCtor();
    void loadDefaultGameRules();  // is this virtual?
    void processSchematics(LevelChunk*);
    LevelGenerationOptions* getLevelGenerationOptions();
    void loadMediaArchive();
    void initTime();

    // note to self: vftable pushes everything over by 8 inside decompiler view
    unsigned char padding[312];
    int mAutosaveTimerTime;
    unsigned char padding2[144];
    bool mGameStarted;
    char padding3;
    char padding4;
    bool mChangingSessionType;
};

class CConsoleMinecraftApp : public CMinecraftApp {
public:
    static CConsoleMinecraftApp sInstance;

    CConsoleMinecraftApp();
    virtual ~CConsoleMinecraftApp();
    void SetRichPresenceContext(int, int) override;
    void FatalLoadError(wchar_t const*, ...) override;
    void StoreLaunchData() override;
    void ExitGame() override;
    void CaptureSaveThumbnail() override;
    void GetSaveThumbnail(unsigned char**, unsigned int*) override;
    void ReleaseSaveThumbnail() override;
    void GetScreenshot(int, unsigned char**, unsigned int*) override;
    void ReadBannedList(int, eTMSAction, bool) override;
    void LoadLocalTMSFile(wchar_t*) override;
    void LoadLocalTMSFile(wchar_t*, eFileExtensionType) override;
    void FreeLocalTMSFiles(eTMSFileType) override;
    void GetLocalTMSFileIndex(wchar_t*, bool, eFileExtensionType) override;
    virtual void TemporaryCreateGameStart();

    void InitialiseDLCInfo();
    bool ReadProductCodes();
    void CommerceInit();
    int GetLocalPlayerCount();

    static int RequestSignInUIChoices(int);
};