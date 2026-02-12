#pragma once

#include "types.h"

#include <nn/os/os_MutexTypes.h>

#include "java/io/File.h"
#include "net/minecraft/stats/StatsCounter.h"
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
    void run_middle();
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

    void tickAllConnections();

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

    void SetupMiniGameInstance(MiniGameDef& def, int i);

    DataFixerUpper* m_fixerUpper;
    MultiPlayerGameMode* m_multiPlayerGameMode;
    bool m_isFullscreen;
    bool m_bool11;
    void* m_qword18;
    int m_width;
    int m_height;
    int m_displayWidth;
    int m_displayHeight;
    Timer* m_timer;
    bool m_byte38;
    void* m_qword40;
    Level* m_level;
    LevelRenderer* m_levelRenderer;
    std::shared_ptr<MultiplayerLocalPlayer> m_localPlayer;
    arrayWithLength<void*> m_array68;  // unknown array type
    std::shared_ptr<MultiplayerLocalPlayer> m_localPlayers[4];
    MultiPlayerGameMode* m_gameModes[4];
    int m_dwordD8;
    void* m_arrayE0[4];
    int m_array100[4];
    bool m_array110[4];
    char m_gap114[20];
    void* m_arr128[4];
    int m_dword148;
    std::shared_ptr<Entity> m_ptr150;
    std::shared_ptr<Mob> m_ptr160;  // TODO: This shared ptr is not an Entity, but it's used as one. Mob?
    ParticleEngine* m_particleEngine;
    User* m_user;
    std::wstring m_serverDomain;
    Canvas* m_parent;
    bool m_isAppletMode;
    bool m_isPaused;
    Textures* m_textures;
    Font* m_font;
    Font* m_altFont;
    Screen* m_screen;
    ProgressRenderer* m_progressRenderer;
    GameRenderer* m_gameRenderer;
    EntityRenderDispatcher* m_entityRenderDispatcher;
    ItemInHandRenderer* m_itemInHandRenderer;
    BlockColors* m_blockColors;
    ItemColors* m_itemColors;
    TextureAtlas* m_blockAtlas;
    ItemRenderer* m_itemRenderer;
    BlockRenderDispatcher* m_blockRenderDispatcher;
    void* m_qword210;
    void* m_qword218;
    int m_origHeight;
    Gui* m_gui;
    bool m_isNoRender;
    HitResult* m_hitResult;
    Options* m_options;
    MinecraftApplet* m_minecraftApplet;  // always null?
    SoundEngine* m_soundEngine;
    void* m_qword258;
    TexturePackRepository* m_texturePackRepository;
    File m_workingDirectory;
    McRegionLevelStorageSource* m_levelStorageSource;
    StatsCounter* m_statsCounters[4];
    std::wstring m_connectToIp;
    int m_connectToPort;
    bool m_isRunning;
    std::wstring m_workDir;
    long long m_lastTimer;
    int m_dword2e8;
    FrameTimer* m_frameTimer = new FrameTimer();
    void* m_qword2F8;
    nn::os::MutexType m_criticalSection;
    char m_tutorialFlags;
    void* m_qword328;
    std::vector<void*> m_qword330;
    std::vector<void*> m_qword348;
    MiniGameDef* m_lobbyGameMode;
    ClientMasterGameMode* m_clientMasterGameMode;
    void* m_qword370;
    GhostController* m_ghostController;
    std::list<GhostController*> m_ghostControllers;
};

ASSERT_SIZEOF(Minecraft, 0x398)
