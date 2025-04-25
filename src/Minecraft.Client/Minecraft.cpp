#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/Tooltips.h"
#include "Minecraft.Client/User.h"
#include "Minecraft.Client/multiplayer/ClientPacketListener.h"
#include "Minecraft.Client/resources/StringTable.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/MinecraftWorld.h"
#include "Minecraft.World/StructureManager.h"
#include "Minecraft.World/Tutorial.h"
#include "Minecraft.World/level/gamemode/MasterGameMode.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameDef.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameMedals.h"
#include "Minecraft.Core/ParticleType.h"
#include "Minecraft.Core/System.h"
#include "Minecraft.Core/io/File.h"
#include "platform/NX/Platform.h"
#include "renderer/GlStateManager.h"
#include "renderer/entity/BlockEntityRenderDispatcher.h"
#include "ui/scene/scenes/UIScene_CreativeMenu.h"
#include "ui/scene/scenes/UIScene_LeaderboardsMenu.h"
#include <string>

Minecraft* Minecraft::GetInstance() {
    return sInstance;
}

void Minecraft::init() {
    this->mSaves = File(L"");

    this->mMcRegionLevelStorageSource
        = new McRegionLevelStorageSource(File(this->mSaves, L"saves"), getFixerUpper());

    this->mOptions = new Options(this, this->mSaves);

    this->mTexturePackRepository = new TexturePackRepository(File(this->mSaves), this);
    this->mTexturePackRepository->addDebugPacks();

    this->mTextures = new Textures(this->mTexturePackRepository, this->mOptions);

    this->mDefaultFont = new Font(this->mOptions, L"font/Default", this->mTextures, 0,
                                  &Font::sDefaultFontRsrc, 23, 28, 16, 16, Font::sDefaultText);
    this->mAlternateFont = new Font(this->mOptions, L"font/alternate", this->mTextures, 0,
                                    &Font::sAlternateFontRsrc, 16, 16, 8, 8, nullptr);

    GrassColor::init(this->mTextures->loadTexturePixels(_TEXTURE_NAME::GRASS_COLOR, L"misc/grasscolor"));
    FoliageColor::init(
        this->mTextures->loadTexturePixels(_TEXTURE_NAME::FOLIAGE_COLOR, L"misc/foliagecolor"));

    Biome::generateColoursDebugOutput();

    this->mBlockAtlas = new TextureAtlas(0, L"terrain", L"textures/blocks/", 0, true);

    this->mBlockColors = BlockColors::createDefault();
    this->mItemColors = ItemColors::createDefault(this->mBlockColors);

    this->mItemRenderer = new ItemRenderer(this->mEntityRenderDispatcher, this->mTextures, this->mItemColors);
    this->mEntityRenderDispatcher = new EntityRenderDispatcher(this->mTextures, this->mItemRenderer);

    GlStateManager::enableLighting();
    this->mItemInHandRenderer = new ItemInHandRenderer(this);
    GlStateManager::disableLighting();

    this->mGameRenderer = new GameRenderer(this, 0);
    this->mBlockRenderDispatcher = new BlockRenderDispatcher(this->mBlockColors);
    // static shit
    BlockEntityRenderDispatcher::sInstance->mTextures = this->mTextures;
    this->sEntityBlockRenderer = new EntityBlockRenderer();

    this->mStatsCounter1 = new StatsCounter();
    this->mStatsCounter2 = new StatsCounter();
    this->mStatsCounter3 = new StatsCounter();
    this->mStatsCounter4 = new StatsCounter();
    setupStatsCounter();

    // this is cursed why would you do this
    MemSect(31);
    { std::wstring status(L"Pre startup"); }
    MemSect(0);

    GlStateManager::enableTexture();
    GlStateManager::shadeModel(0);
    GlStateManager::clearDepth(1.0);
    GlStateManager::enableDepthTest();
    GlStateManager::depthFunc(4);
    GlStateManager::enableAlphaTest();
    GlStateManager::alphaFunc(5, 0.1);
    GlStateManager::cullFace(1);
    GlStateManager::matrixMode(1);
    GlStateManager::loadIdentity();
    GlStateManager::matrixMode(0);

    MemSect(31);
    { std::wstring status(L"Startup"); }
    MemSect(0);

    this->mLevelRenderer = new LevelRenderer(this, this->mTextures);

    this->mTextures->stitch();

    this->mParticleEngine = new ParticleEngine(this->mLevel, this->mTextures);

    MemSect(31);
    { std::wstring status(L"Post startup"); }
    MemSect(0);

    this->mGui = new Gui(this);

    if (this->wstring_2a8 == L"") {
        this->setScreen(new TitleScreen());
    }

    this->mProgressRenderer = new ProgressRenderer(this);
    Renderer::sInstance->CBuffLockStaticCreations();
}

void Minecraft::main() {
    std::wstring playerName;
    std::wstring session;

    sUnk = true;
    MinecraftWorld_RunStaticCtors();
    User::staticCtor();
    Tutorial::staticCtor();
    ColourTable::staticCtor();
    StructureManager::staticCtor();
    Tooltips::staticCtor();
    GlStateManager::staticCtor();
    CConsoleMinecraftApp::sInstance.loadDefaultGameRules();

    long ms = System::processTimeInMilliSecs();
    playerName = L"Player" + _toString(ms % 1000);
    session = L"-";

    UIScene_CreativeMenu::staticCtor();
    UIScene_LeaderboardsMenu::staticCtor();
    BlockEntityRenderDispatcher::staticCtor();

    start(playerName, session);

    ParticleType::staticCtor();
    // who was in charge of naming this one
    MasterGameMode::StaticCtor();
    MiniGameMedals::staticCtor();
    // and these
    CMinecraftApp::StaticCtor();
    MiniGameDef::StaticCtor();
    Minecraft::GetInstance()->mLobbyGameMode = MiniGameDef::GetCustomGameModeById(LOBBY, true);
    ClientPacketListener::staticCtor();
}

void Minecraft::start(const std::wstring& str1, const std::wstring& str2) {
    startAndConnectTo(str1, str2, L"");
}

// NON_MATCHING: score 16007
Minecraft::Minecraft(class Component*, class Canvas*, class MinecraftApplet*, int width, int height, bool) {
    this->mLocalPlayer = nullptr;
    this->qword_60 = nullptr;
    // this->qword_68 = ??
    this->website = nullptr;  // we should be setting like size or some shit to 0 here
    mLocalPlayers[0] = nullptr;
    mLocalPlayers[1] = nullptr;
    mLocalPlayers[2] = nullptr;
    mLocalPlayers[3] = nullptr;
    this->qword_150 = nullptr;
    this->qword_158 = nullptr;
    this->qword_160 = nullptr;
    this->qword_168 = nullptr;
    this->website = nullptr;  // we should be setting like size or some shit to 0 here
    File(this->mSaves);
    this->wstring_2a8 = nullptr;
    this->qword_2c8 = nullptr;
    this->qword_2d0 = nullptr;
    this->qword_2d8 = nullptr;
    this->mFrameTimer = new FrameTimer();
    this->qword_330 = nullptr;
    this->qword_338 = nullptr;
    this->qword_340 = nullptr;
    this->qword_348 = nullptr;
    this->qword_350 = nullptr;
    this->qword_358 = nullptr;
    this->qword_380 = &this->qword_380;  // ?
    this->qword_388 = &this->qword_380;
    this->qword_390 = nullptr;
    this->mFixerUpper = DataFixers::createFixerUpper();
    this->mMultiPlayerGameMode = nullptr;
    this->byte_11 = 0;
    this->mTimer = new Timer(20.0);
    this->qword_40 = nullptr;
    this->mLevel = nullptr;
    // sub_71006D770C((__int64)&v24, 3u, 1);
    // LODWORD(this->qword_70) = v24.qword8;
    // this->qword_68 = (void *)v24.qword0;
    this->mLevelRenderer = nullptr;
    // TODO: continue
}

// NON_MATCHING: score 3141
void Minecraft::startAndConnectTo(const std::wstring& name, const std::wstring& session,
                                  const std::wstring& arg3) {
    Minecraft* mc = new Minecraft(nullptr, nullptr, nullptr, 1280, 720, false);
    mc->website = L"www.minecraft.net";

    if (name != L"" && session != L"") {
        mc->user = new User(name, session);
    } else {
        mc->user = new User(L"Player" + _toString<long>(System::processTimeInMilliSecs() % 1000), L"");
    }

    mc->run();
}

BlockRenderDispatcher* Minecraft::getBlockRenderer() {
    return this->mBlockRenderDispatcher;
}

EntityRenderDispatcher* Minecraft::getEntityRenderDispatcher() {
    return this->mEntityRenderDispatcher;
}

DataFixerUpper* Minecraft::getFixerUpper() {
    return this->mFixerUpper;
}

ItemInHandRenderer* Minecraft::getItemInHandRenderer() {
    return this->mItemInHandRenderer;
}

ItemRenderer* Minecraft::getItemRenderer() {
    return this->mItemRenderer;
}

int Minecraft::getAverageFps() {
    return sAverageFps;
}

bool Minecraft::isUsingDefaultSkin() {
    return GetInstance()->mTexturePackRepository->getSelected();
}

bool Minecraft::isTutorial() {
    return this->byte_320 != 0;
}

bool Minecraft::useFancyGraphics() {
    return Minecraft::sInstance && Minecraft::sInstance->mOptions->mIsFancyGraphics;
}

void Minecraft::run() {
    this->mIsRunning = true;
    init();
}