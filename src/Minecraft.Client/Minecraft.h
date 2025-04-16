#pragma once

#include <memory>
#include <string>
#include "Minecraft.World/level/storage/McRegionLevelStorageSource.h"
#include "Options.h"
#include "resources/TexturePackRepository.h"
#include "Textures.h"
#include "gui/Font.h"
#include "Minecraft.World/level/block/GrassColor.h"
#include "Minecraft.World/level/block/FoliageColor.h"
#include "Minecraft.World/level/biome/Biome.h"
#include "renderer/texture/TextureAtlas.h"
#include "Minecraft.World/level/block/BlockColors.h"
#include "Minecraft.World/level/block/ItemColors.h"
#include "renderer/item/ItemRenderer.h"
#include "renderer/entity/EntityRenderDispatcher.h"
#include "renderer/entity/EntityBlockRenderer.h"
#include "renderer/BlockRenderDispatcher.h"
#include "renderer/GlStateManager.h"
#include "renderer/item/ItemInHandRenderer.h"
#include "renderer/GameRenderer.h"
#include "StatsCounter.h"
#include "renderer/LevelRenderer.h"
#include "ParticleEngine.h"
#include "renderer/Renderer.h"
#include "gui/Gui.h"
#include "ui/screen/TitleScreen.h"
#include "renderer/ProgressRenderer.h"

class DataFixerUpper;
class MultiPlayerGameMode;
class LocalPlayer;
class Entity;
class SoundEngine;
class File;
class FrameTimer;
class ClientMasterGameMode;
class GhostController;
class ColourTable;
class MultiplayerLocalPlayer;

class Minecraft {
public:
    static Minecraft* sInstance;
    static Minecraft* GetInstance();

    Minecraft(class Component*, class Canvas*, class MinecraftApplet*, int width, int height, bool);
    void run();

    inline void init() {
        this->byte_2c4 = 1;
        run();
    };

    static inline void currentTimeMillis();
    static void start(const std::wstring& str1, const std::wstring& str2);
    static void startAndConnectTo(const std::wstring& arg1, const std::wstring& arg2,
                                  const std::wstring& arg3);

    DataFixerUpper *getFixerUpper();

    std::shared_ptr<Entity> getCameraEntity();

    ColourTable* getColourTable();

    bool isUsingDefaultSkin();

    // replaced with direct access on Wii U Edition but does nothing on Switch Edition.
    static void setStatsCounter(StatsCounter *counter) { return; };

    void setScreen(Screen *screen);

    static EntityBlockRenderer *sEntityBlockRenderer;
    DataFixerUpper* mFixerUpper;
    MultiPlayerGameMode* mMultiPlayerGameMode;
    bool byte_10;
    bool byte_11;
    void* qword_18;
    int dword_20;
    int dword_24;
    int dword_28;
    int dword_2c;
    void* qword_30;
    char byte_38;
    void* qword_40;
    Level *mLevel;
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
    char gap_160[16];
    ParticleEngine* mParticleEngine;
    void* qword_178;
    void* qword_180;
    void* qword_188;
    char gap_190[8];
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
    BlockRenderDispatcher* mBlockRenderDispatcher;
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
    std::wstring *wstring_2a8;
    std::wstring *wstring_2b0;
    void* qword_2b8;
    int dword_2c0;
    char byte_2c4;
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
    void* qword_360;
    ClientMasterGameMode* mClientMasterGameMode;
    char gap_370[8];
    GhostController* mGhostController;
    void* qword_380;
    void* qword_388;
    void* qword_390;
};
