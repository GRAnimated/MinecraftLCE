#pragma once

#include "Minecraft.Client/User.h"
#include "Minecraft.World/level/biome/Biome.h"
#include "Minecraft.World/level/block/BlockColors.h"
#include "Minecraft.World/level/block/FoliageColor.h"
#include "Minecraft.World/level/block/GrassColor.h"
#include "Minecraft.World/level/block/ItemColors.h"
#include "Minecraft.World/level/storage/McRegionLevelStorageSource.h"
#include "DataFixers.h"
#include "FrameTimer.h"
#include "Minecraft.Network/Connection.h"
#include "Options.h"
#include "ParticleEngine.h"
#include "StatsCounter.h"
#include "Timer.h"
#include "color/ColourTable.h"
#include "gui/Font.h"
#include "gui/Gui.h"
#include "renderer/BlockRenderDispatcher.h"
#include "renderer/GameRenderer.h"
#include "renderer/GlStateManager.h"
#include "renderer/LevelRenderer.h"
#include "renderer/ProgressRenderer.h"
#include "renderer/Renderer.h"
#include "renderer/entity/EntityBlockRenderer.h"
#include "renderer/entity/EntityRenderDispatcher.h"
#include "renderer/item/ItemInHandRenderer.h"
#include "renderer/item/ItemRenderer.h"
#include "renderer/texture/TextureAtlas.h"
#include "renderer/texture/Textures.h"
#include "resources/TexturePackRepository.h"
#include "ui/screen/TitleScreen.h"
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

class Minecraft {
public:
    static Minecraft* sInstance;
    static Minecraft* GetInstance();

    Minecraft(class Component*, class Canvas*, class MinecraftApplet*, int width, int height, bool);

    void run();
    void init();
    static void main();

    static inline void currentTimeMillis();
    static void start(const std::wstring& str1, const std::wstring& str2);
    static void startAndConnectTo(const std::wstring& name, const std::wstring& session,
                                  const std::wstring& arg3);

    // called after all 4 StatsCounters are created in init
    static void setupStatsCounter() { return; }

    // feel like this is meant to be BlockRenderer, not BlockRenderDispatcher... but maybe it is just a
    // container for BlockRenderer although wouldn't getEntityRenderDispatcher also be called
    // getEntityRenderer?
    BlockRenderDispatcher* getBlockRenderer();
    std::shared_ptr<Entity> getCameraEntity();
    ColourTable* getColourTable();
    Connection* getConnection(int);
    EntityRenderDispatcher* getEntityRenderDispatcher();
    DataFixerUpper* getFixerUpper();
    ItemInHandRenderer* getItemInHandRenderer();
    ItemRenderer* getItemRenderer();

    ClientMasterGameMode* GetClientMasterGameMode();  // PascalCase
    MiniGameDef* GetMiniGame();

    bool isUsingDefaultSkin();
    bool isTutorial();
    static int getAverageFps();
    static bool useFancyGraphics();

    void setScreen(Screen* screen);

    static int sAverageFps;  // or would it be const (I think const does the same thing as static where it
                             // shoves it into the executable)
    static bool sUnk;
    static EntityBlockRenderer* sEntityBlockRenderer;
    DataFixerUpper* mFixerUpper;
    MultiPlayerGameMode* mMultiPlayerGameMode;
    bool byte_10;
    bool byte_11;
    void* qword_18;
    int dword_20;
    int dword_24;
    int dword_28;
    int dword_2c;
    Timer* mTimer;
    char byte_38;
    void* qword_40;
    Level* mLevel;
    LevelRenderer* mLevelRenderer;
    LocalPlayer* mLocalPlayer;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    std::shared_ptr<MultiplayerLocalPlayer> mLocalPlayers[4];
    void* qword_b8;
    void* qword_c0;
    void* qword_c8;
    void* qword_d0;
    int dword_d8;
    char gap_DC[52];
    short word_110;
    short word_112;
    char gap_114[20];
    void* qword_128;
    void* qword_130;
    void* qword_138;
    void* qword_140;
    int dword_148;
    void* qword_150;
    void* qword_158;
    void* qword_160;
    void* qword_168;
    ParticleEngine* mParticleEngine;
    User* user;
    std::wstring website;
    // void* qword_188;
    // char gap_190[8];
    void* qword_198;
    char byte_1a0;
    bool mHasRenderedTick;
    Textures* mTextures;
    Font* mDefaultFont;
    Font* mAlternateFont;
    void* qword_1c0;
    ProgressRenderer* mProgressRenderer;
    GameRenderer* mGameRenderer;
    EntityRenderDispatcher* mEntityRenderDispatcher;
    ItemInHandRenderer* mItemInHandRenderer;
    BlockColors* mBlockColors;
    ItemColors* mItemColors;
    TextureAtlas* mBlockAtlas;
    ItemRenderer* mItemRenderer;
    BlockRenderDispatcher* mBlockRenderDispatcher;  // meant to be BlockRenderer???
    void* qword_210;
    void* qword_218;
    int dword_220;
    Gui* mGui;
    char byte_230;
    void* qword_238;
    Options* mOptions;
    void* qword_248;
    SoundEngine* mSoundEngine;
    void* qword_258;
    TexturePackRepository* mTexturePackRepository;
    File mSaves;
    McRegionLevelStorageSource* mMcRegionLevelStorageSource;
    StatsCounter* mStatsCounter1;
    StatsCounter* mStatsCounter2;
    StatsCounter* mStatsCounter3;
    StatsCounter* mStatsCounter4;
    std::wstring wstring_2a8;
    int dword_2c0;
    bool mIsRunning;
    char gap_2C5[3];
    void* qword_2c8;
    void* qword_2d0;
    void* qword_2d8;
    void* qword_2e0;
    int dword_2e8;
    FrameTimer* mFrameTimer;
    char gap_2F8[8];
    void* qword_300;
    char gap_308[24];
    char byte_320;
    void* qword_328;
    void* qword_330;
    void* qword_338;
    void* qword_340;
    void* qword_348;
    void* qword_350;
    void* qword_358;
    void* mLobbyGameMode;  // check MiniGameDef.h
    ClientMasterGameMode* mClientMasterGameMode;
    char gap_370[8];
    GhostController* mGhostController;
    void* qword_380;
    void* qword_388;
    void* qword_390;
};
