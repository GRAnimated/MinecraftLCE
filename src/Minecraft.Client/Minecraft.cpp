#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Core/System.h"
#include "Minecraft.h"
#include "Minecraft.Core/io/File.h"
#include "platform/NX/Platform.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "renderer/GlStateManager.h"
#include "renderer/entity/BlockEntityRenderDispatcher.h"
#include <string>
#include "Minecraft.World/MinecraftWorld.h"
#include "User.h"
#include "Minecraft.World/Tutorial.h"
#include "Minecraft.World/StructureManager.h"
#include "Tooltips.h"
#include "ui/scene/scenes/UIScene_CreativeMenu.h"
#include "ui/scene/scenes/UIScene_LeaderboardsMenu.h"
#include "ParticleType.h"
#include "Minecraft.World/level/gamemode/MasterGameMode.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameMedals.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameDef.h"
#include "multiplayer/ClientPacketListener.h"

Minecraft* Minecraft::GetInstance() {
    return sInstance;
}

// NON_MATCHING: score 8813
void Minecraft::init() {
    this->mSaves = File(L"");

    this->mMcRegionLevelStorageSource = new McRegionLevelStorageSource(File(this->mSaves, L"saves"), getFixerUpper());

    this->mOptions = new Options(this, File(this->mSaves));

    this->mTexturePackRepository = new TexturePackRepository(File(this->mSaves), this);
    this->mTexturePackRepository->addDebugPacks();

    this->mTextures = new Textures(this->mTexturePackRepository, this->mOptions);

    // nullptr values are temp.
    // first one is a ResourceLocation* initialized in __sti___17_UnityClient13_cpp_useLomp
    this->mDefaultFont = new Font(this->mOptions, L"font/Default", this->mTextures, 0, nullptr, 23, 28, 16, 16, nullptr);
    // first nullptr value is temp, second is meant to be nullptr
    this->mAlternateFont = new Font(this->mOptions, L"font/Alternate", this->mTextures, 0, nullptr, 16, 16, 8, 8, nullptr);

    arrayWithLength<int> grassColorTexture = this->mTextures->loadTexturePixels(_TEXTURE_NAME::GRASS_COLOR, L"misc/grasscolor");
    GrassColor::init(grassColorTexture);

    arrayWithLength<int> foliageColorTexture = this->mTextures->loadTexturePixels(_TEXTURE_NAME::FOLIAGE_COLOR, L"misc/foliagecolor");
    FoliageColor::init(foliageColorTexture);

    Biome::generateColoursDebugOutput();

    this->mBlockAtlas = new TextureAtlas(0, L"terrain", L"textures/blocks/", 0, true);

    // TODO: get class size
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
    setStatsCounter(this->mStatsCounter4);

    MemSect(31);
    std::wstring status = L"Pre startup";
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
    status = L"Startup";
    MemSect(0);

    this->mLevelRenderer = new LevelRenderer(this, this->mTextures);
    
    this->mTextures->stitch();

    this->mParticleEngine = new ParticleEngine(this->mLevel, this->mTextures);

    MemSect(31);
    status = L"Post startup";
    MemSect(0);

    this->mGui = new Gui(this);

    if (!this->wstring_2a8->empty()) {
        this->setScreen(new TitleScreen());
    }

    this->mProgressRenderer = new ProgressRenderer(this);
    Renderer::sInstance->CBuffLockStaticCreations();
}

// NON_MATCHING: score 4620
void Minecraft::main() {
    sUnk = true;
    MinecraftWorld_RunStaticCtors();
    User::staticCtor();
    Tutorial::staticCtor();
    ColourTable::staticCtor();
    StructureManager::staticCtor();
    Tooltips::staticCtor();
    GlStateManager::staticCtor();
    CConsoleMinecraftApp::sInstance->loadDefaultGameRules();

    long ms = System::processTimeInMilliSecs();    
    std::wstring playerName = L"Player" + _toString(ms % 1000);

    UIScene_CreativeMenu::staticCtor();
    UIScene_LeaderboardsMenu::staticCtor();
    BlockEntityRenderDispatcher::staticCtor();

    start(playerName, L"-");
    
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

void Minecraft::start(const std::wstring& str1, const std::wstring& str2)
{
    startAndConnectTo(str1, str2, L"");
}

// NON_MATCHING: score 16007
Minecraft::Minecraft(class Component*, class Canvas*, class MinecraftApplet*, int width, int height, bool)
{
    this->mLocalPlayer = nullptr;
    this->qword_60 = nullptr;
    // this->qword_68 = ?? 
    this->website = nullptr; // we should be setting like size or some shit to 0 here
    mLocalPlayers[0] = nullptr;
    mLocalPlayers[1] = nullptr;
    mLocalPlayers[2] = nullptr;
    mLocalPlayers[3] = nullptr;
    this->qword_150 = nullptr;
    this->qword_158 = nullptr;
    this->qword_160 = nullptr;
    this->qword_168 = nullptr;
    this->website = nullptr; // we should be setting like size or some shit to 0 here
    File(this->mSaves);
    this->wstring_2a8 = nullptr;
    this->wstring_2b0 = nullptr;
    this->qword_2b8 = nullptr;
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
    this->qword_380 = &this->qword_380; // ?
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

// NON_MATCHING: score 5636
void Minecraft::startAndConnectTo(const std::wstring &name, const std::wstring &session, const std::wstring &arg3)
{
    Minecraft *mc = new Minecraft(nullptr, nullptr, nullptr, 1280, 720, false);
    mc->website = L"www.minecraft.net";

    if (!name.empty() && !session.empty()) {
        mc->user = new User(name, session);
    } else {
        mc->user = new User(L"Player" + std::to_wstring(System::processTimeInMilliSecs() % 1000), L"");
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
};
