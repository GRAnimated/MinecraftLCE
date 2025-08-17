#pragma once

#include "types.h"

#include <nn/os/os_MutexTypes.h>

#include "java/io/File.h"
#include "net/minecraft/util/FrameTimer.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"

#include <list>
#include <memory>
#include <string>

class DataFixerUpper;
class MultiPlayerGameMode;
class LocalPlayer;
class Entity;
class SoundEngine;
class File;
class ClientMasterGameMode;
class GhostController;
class MultiplayerLocalPlayer;
class BlockRenderer;
class MiniGameDef;
class BlockRenderDispatcher;
class ColourTable;
class Connection;
class EntityRenderDispatcher;
class ItemInHandRenderer;
class ItemRenderer;
class Screen;
class EntityBlockRenderer;
class Timer;
class Level;
class LevelRenderer;
class ParticleEngine;
class User;
class Textures;
class Font;
class ProgressRenderer;
class GameRenderer;
class BlockColors;
class ItemColors;
class TextureAtlas;
class Gui;
class Options;
class TexturePackRepository;
class McRegionLevelStorageSource;
class StatsCounter;
class FrameTimer;
class HitResult;
class Mob;
class Component;
class Canvas;
class MinecraftApplet;

class Minecraft {
public:
    static Minecraft* sInstance;
    static Minecraft* GetInstance();

    static int sAverageFps;
    static bool sUnk;
    static EntityBlockRenderer* sEntityBlockRenderer;
    static File sUnkFile;
    static nn::os::MutexType unk_71017C65F0;  // TODO: Find what class this should be in

    Minecraft(Component*, Canvas*, MinecraftApplet*, int width, int height, bool);

    void run();
    void init();
    static void main();

    static inline void currentTimeMillis();
    static void start(const std::wstring& str1, const std::wstring& str2);
    static void startAndConnectTo(const std::wstring& name, const std::wstring& session,
                                  const std::wstring& arg3);

    static void _71006D7E4C() { return; }

    static bool InMiniGame(EMiniGameId, bool);
    static int getAverageFps();
    static bool useFancyGraphics();

    BlockRenderDispatcher* getBlockRenderer();
    std::shared_ptr<Entity> getCameraEntity();
    ColourTable* getColourTable();
    Connection* getConnection(int);
    EntityRenderDispatcher* getEntityRenderDispatcher();
    DataFixerUpper* getFixerUpper();
    ItemInHandRenderer* getItemInHandRenderer();
    ItemRenderer* getItemRenderer();
    ClientMasterGameMode* GetClientMasterGameMode();
    MiniGameDef* GetMiniGame();
    bool isUsingDefaultSkin();
    bool isTutorial();
    void setScreen(Screen* screen);
    void SetGhostController(GhostController*);

    void SetupMiniGameInstance(MiniGameDef &def, int i);

    DataFixerUpper* mFixerUpper;
    MultiPlayerGameMode* mMultiPlayerGameMode;
    bool mIsFullscreen;
    bool bool_11;
    void* qword_18;
    int mWidth;
    int mHeight;
    int mDisplayWidth;
    int mDisplayHeight;
    Timer* mTimer;
    bool byte_38;
    void* qword_40;
    Level* mLevel;
    LevelRenderer* mLevelRenderer;
    std::shared_ptr<MultiplayerLocalPlayer> mLocalPlayer;
    arrayWithLength<void*> array_68;  // unknown array type
    std::shared_ptr<MultiplayerLocalPlayer> mLocalPlayers[4];
    MultiPlayerGameMode* mGameModes[4];
    int dword_d8;
    void* array_E0[4];
    int array_100[4];
    bool array_110[4];
    char gap_114[20];
    void* arr_128[4];
    int dword_148;
    std::shared_ptr<Entity> ptr_150;
    std::shared_ptr<Mob> ptr_160;  // TODO: This shared ptr is not an Entity, but it's used as one. Mob?
    ParticleEngine* mParticleEngine;
    User* mUser;
    std::wstring mServerDomain;
    Canvas* mParent;
    bool mIsAppletMode;
    bool mIsPaused;
    Textures* mTextures;
    Font* mFont;
    Font* mAltFont;
    Screen* mScreen;
    ProgressRenderer* mProgressRenderer;
    GameRenderer* mGameRenderer;
    EntityRenderDispatcher* mEntityRenderDispatcher;
    ItemInHandRenderer* mItemInHandRenderer;
    BlockColors* mBlockColors;
    ItemColors* mItemColors;
    TextureAtlas* mBlockAtlas;
    ItemRenderer* mItemRenderer;
    BlockRenderDispatcher* mBlockRenderDispatcher;
    void* qword_210;
    void* qword_218;
    int mOrigHeight;
    Gui* mGui;
    bool mIsNoRender;
    HitResult* mHitResult;
    Options* mOptions;
    MinecraftApplet* mMinecraftApplet;  // always null?
    SoundEngine* mSoundEngine;
    void* qword_258;
    TexturePackRepository* mTexturePackRepository;
    File mWorkingDirectory;
    McRegionLevelStorageSource* mLevelStorageSource;
    StatsCounter* mStatsCounters[4];
    std::wstring mConnectToIp;
    int mConnectToPort;
    bool mIsRunning;
    std::wstring mWorkDir;
    long long mLastTimer;
    int dword_2e8;
    FrameTimer* mFrameTimer = new FrameTimer();
    void* qword_2F8;
    nn::os::MutexType mCriticalSection;
    char mTutorialFlags;
    void* qword_328;
    std::vector<void*> qword_330;
    std::vector<void*> qword_348;
    MiniGameDef *mLobbyGameMode;
    ClientMasterGameMode* mClientMasterGameMode;
    void* qword_370;
    GhostController* mGhostController;
    std::list<GhostController*> mGhostControllers;
};

ASSERT_SIZEOF(Minecraft, 0x398)
