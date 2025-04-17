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

// NON_MATCHING
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
    
    // what the fuck is this
    // Wii U Edition says it's countLeadingZeros
    // although it looks like it's checking a flag left in a wstring pointer????
    std::wstring *ul2b0;
    bool ul2a8 = ((unsigned long long)wstring_2a8 & 1);

    if (ul2a8)
        ul2b0 = this->wstring_2b0; // ???
    else
        ul2b0 = (std::wstring*)((unsigned long long)this->wstring_2a8 >> 1); // idfk anymore LMFAO

    if (!(this->wstring_2a8->c_str() == L"")) {
        this->setScreen(new TitleScreen());
    }

    this->mProgressRenderer = new ProgressRenderer(this);
    Renderer::sInstance->CBuffLockStaticCreations();
}

// NOT_MATCHING
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
    CMinecraftApp::StaticCtor();
    MiniGameDef::StaticCtor();
    Minecraft::GetInstance()->mLobbyGameMode = MiniGameDef::GetCustomGameModeById(LOBBY, true);
    ClientPacketListener::staticCtor();
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

bool Minecraft::isUsingDefaultSkin()
{
    return GetInstance()->mTexturePackRepository->getSelected();
}

bool Minecraft::isTutorial()
{
    return this->byte_320 != 0;
}

bool Minecraft::useFancyGraphics() {
    return Minecraft::sInstance && Minecraft::sInstance->mOptions->mIsFancyGraphics;
}

void Minecraft::run() {
    this->mIsRunning = true;
    init();
};
