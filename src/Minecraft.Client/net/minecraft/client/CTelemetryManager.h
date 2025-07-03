#pragma once

#include "net/minecraft/client/ui/scene/UIScene.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

enum ESen_FriendOrMatch {};
enum ESen_CompeteOrCoop {};
enum ESen_LevelExitStatus {};
enum ESen_MediaDestination {};
enum ESen_MediaType {};
enum ESen_UpsellID {};
enum ESen_UpsellOutcome {};
enum ETelemetryChallenges {};
enum TelemetryJoinMethod {};

class LaunchMoreOptionsMenuInitData;
class SAVE_DETAILS;

class CTelemetryManager {
public:
    virtual ~CTelemetryManager();
    virtual void Init();
    virtual void Tick();
    virtual void Flush();
    virtual void RecordPlayerSessionStart(int);
    virtual void RecordPlayerSessionExit(int, int);
    virtual void RecordHeartBeat(int);
    virtual void RecordLevelStart(int, ESen_FriendOrMatch, ESen_CompeteOrCoop, int, int, int);
    virtual void RecordLevelExit(int, ESen_LevelExitStatus);
    virtual void RecordLevelSaveOrCheckpoint(int, int, int);
    virtual void RecordLevelResume(int, ESen_FriendOrMatch, ESen_CompeteOrCoop, int, int, int, int);
    virtual void RecordPauseOrInactive(int);
    virtual void RecordUnpauseOrActive(int);
    virtual void RecordMenuShown(int, EUIScene, int);
    virtual void RecordAchievementUnlocked(int, int, int);
    virtual void RecordMediaShareUpload(int, ESen_MediaDestination, ESen_MediaType);
    virtual void RecordUpsellPresented(int, ESen_UpsellID, int);
    virtual void RecordUpsellResponded(int, ESen_UpsellID, int, ESen_UpsellOutcome);
    virtual void RecordPlayerDiedOrFailed(int, int, int, int, int, int, int, ETelemetryChallenges);
    virtual void RecordEnemyKilledOrOvercome(int, int, int, int, int, int, int, ETelemetryChallenges);
    virtual void RecordTexturePackLoaded(int, int, bool);
    virtual void RecordSkinChanged(int, int);
    virtual void RecordBanLevel(int);
    virtual void RecordUnBanLevel(int);
    virtual void PrepareMiniGameHostOptions(int, const LaunchMoreOptionsMenuInitData*, TelemetryJoinMethod);
    virtual void RecordMiniGameHostOptions(int, EMiniGameId);
    virtual void RecordPlayerSettings(int);
    virtual void sub_2CA1730();
    virtual void sub_2CA1738();
    virtual void sub_2CA1740();
    virtual void sub_2CA1748();
    virtual void RecordGameModeRoundStart(const std::wstring&, const std::wstring&);
    virtual void RecordGameModeRoundFinished();
    virtual void RecordSavesInformation(int, SAVE_DETAILS const*, unsigned int);
    virtual void GetMultiplayerInstanceID();
    virtual void GenerateMultiplayerInstanceId();
    virtual void SetMultiplayerInstanceId(int);

    static CTelemetryManager* sInstance;
};
