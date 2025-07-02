#pragma once

#include "types.h"

#include "net/minecraft/client/eGameHostOption.h"
#include "net/minecraft/core/profile/CProfile.h"
#include "net/minecraft/core/storage/C4JStorage.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/levelgen/LevelGenerationOptions.h"
#include <string>

enum eTMSAction {};
enum eFileExtensionType {};
enum eTMSFileType {};
enum eTPDFileType {};
enum eXuiAction {};
class GameRuleDefinition;
class LevelChunk;
class PlayerUID;

class CMinecraftApp {
public:
    CMinecraftApp();
    virtual ~CMinecraftApp();
    virtual void CaptureScreenshot(int);
    virtual void SetRichPresenceContext(int, int) = 0;
    virtual void FatalLoadError(const wchar_t*, ...);
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
    int GetGameHostOption(eGameHostOption option);
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
    arrayWithLength<uchar> getArchiveFile(const std::wstring&, bool);
    bool hasArchiveFile(const std::wstring&, bool);
    void InitialiseTips();
    void InitGameSettings();
    LevelRuleset* getGameRuleDefinitions();
    EMiniGameId GetFirstMiniGameType();
    bool IsAppPaused();
    void SetAction(int, eXuiAction, void*);

    static int DefaultOptionsCallback(void*, C4JStorage::PROFILESETTINGS*, int);
    static int OptionsDataCallback(void*, int, unsigned short, C4JStorage::eOptionsCallback);
    static void SignInChangeCallback(void*, bool, unsigned int);
    static void ProfileReadErrorCallback(void*);
    static void UpsellReturnedCallback(void*, eUpsellType, eUpsellResponse, int);

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
    void FatalLoadError(const wchar_t*, ...) override;
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
    static int DisplaySavingMessageNX(void*, C4JStorage::ESavingMessage, int);
    static void Callback_SaveGameIncomplete(void*, C4JStorage::ESaveIncompleteType);

    void InitialiseDLCInfo();
    bool ReadProductCodes();
    void CommerceInit();
    int GetLocalPlayerCount();

    static int RequestSignInUIChoices(int);
};