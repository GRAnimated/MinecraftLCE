#include "Minecraft.Client/CMinecraftApp.h"
#include "Minecraft.Client/DataFixers.h"
#include "Minecraft.Client/GhostController.h"
#include "Minecraft.Client/Minecraft.h"
#include "Minecraft.Client/Options.h"
#include "Minecraft.Client/ParticleEngine.h"
#include "Minecraft.Client/StatsCounter.h"
#include "Minecraft.Client/Timer.h"
#include "Minecraft.Client/Tooltips.h"
#include "Minecraft.Client/User.h"
#include "Minecraft.Client/color/ColourTable.h"
#include "Minecraft.Client/gui/Font.h"
#include "Minecraft.Client/gui/Gui.h"
#include "Minecraft.Client/gui/screens/TitleScreen.h"
#include "Minecraft.Client/multiplayer/ClientPacketListener.h"
#include "Minecraft.Client/renderer/BlockRenderDispatcher.h"
#include "Minecraft.Client/renderer/GameRenderer.h"
#include "Minecraft.Client/renderer/LevelRenderer.h"
#include "Minecraft.Client/renderer/ProgressRenderer.h"
#include "Minecraft.Client/renderer/Renderer.h"
#include "Minecraft.Client/renderer/entity/EntityBlockRenderer.h"
#include "Minecraft.Client/renderer/entity/EntityRenderDispatcher.h"
#include "Minecraft.Client/renderer/item/ItemInHandRenderer.h"
#include "Minecraft.Client/renderer/item/ItemRenderer.h"
#include "Minecraft.Client/renderer/texture/TextureManager.h"
#include "Minecraft.Client/renderer/texture/Textures.h"
#include "Minecraft.Client/resources/TexturePackRepository.h"
#include "Minecraft.Client/sounds/SoundEngine.h"
#include "Minecraft.World/ArrayWithLength.h"
#include "Minecraft.World/MinecraftWorld.h"
#include "Minecraft.World/StructureManager.h"
#include "Minecraft.World/Tutorial.h"
#include "Minecraft.World/level/block/BlockColors.h"
#include "Minecraft.World/level/block/FoliageColor.h"
#include "Minecraft.World/level/block/GrassColor.h"
#include "Minecraft.World/level/block/ItemColors.h"
#include "Minecraft.World/level/gamemode/ClientMasterGameMode.h"
#include "Minecraft.World/level/gamemode/MasterGameMode.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameDef.h"
#include "Minecraft.World/level/gamemode/minigames/MiniGameMedals.h"
#include "Minecraft.World/level/storage/McRegionLevelStorageSource.h"
#include "Minecraft.World/stats/Stats.h"
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
    mWorkingDirectory = File(L"");

    mLevelStorageSource = new McRegionLevelStorageSource(File(mWorkingDirectory, L"saves"), getFixerUpper());

    mOptions = new Options(this, mWorkingDirectory);

    mTexturePackRepository = new TexturePackRepository(File(mWorkingDirectory), this);
    mTexturePackRepository->addDebugPacks();

    mTextures = new Textures(mTexturePackRepository, mOptions);

    mFont = new Font(mOptions, L"font/Default", mTextures, 0, &Font::sDefaultFontRsrc, 23, 28, 16, 16,
                     Font::sDefaultText);
    mAltFont = new Font(mOptions, L"font/alternate", mTextures, 0, &Font::sAlternateFontRsrc, 16, 16, 8, 8,
                        nullptr);

    GrassColor::init(mTextures->loadTexturePixels(_TEXTURE_NAME::GRASS_COLOR, L"misc/grasscolor"));
    FoliageColor::init(mTextures->loadTexturePixels(_TEXTURE_NAME::FOLIAGE_COLOR, L"misc/foliagecolor"));

    Biome::generateColoursDebugOutput();

    mBlockAtlas = new TextureAtlas(0, L"terrain", L"textures/blocks/", 0, true);

    mBlockColors = BlockColors::createDefault();
    mItemColors = ItemColors::createDefault(mBlockColors);

    mItemRenderer = new ItemRenderer(mEntityRenderDispatcher, mTextures, mItemColors);
    mEntityRenderDispatcher = new EntityRenderDispatcher(mTextures, mItemRenderer);

    GlStateManager::enableLighting();
    mItemInHandRenderer = new ItemInHandRenderer(this);
    GlStateManager::disableLighting();

    mGameRenderer = new GameRenderer(this, 0);
    mBlockRenderDispatcher = new BlockRenderDispatcher(mBlockColors);
    // static shit
    BlockEntityRenderDispatcher::sInstance->mTextures = mTextures;
    sEntityBlockRenderer = new EntityBlockRenderer();

    mStatsCounters[0] = new StatsCounter();
    mStatsCounters[1] = new StatsCounter();
    mStatsCounters[2] = new StatsCounter();
    mStatsCounters[3] = new StatsCounter();

    _71006D7E4C();

    // this is cursed why would you do this
    MemSect(31);
    {
        std::wstring status(L"Pre startup");
    }
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
    {
        std::wstring status(L"Startup");
    }
    MemSect(0);

    mLevelRenderer = new LevelRenderer(this, mTextures);

    mTextures->stitch();

    mParticleEngine = new ParticleEngine(mLevel, mTextures);

    MemSect(31);
    {
        std::wstring status(L"Post startup");
    }
    MemSect(0);

    mGui = new Gui(this);

    if (mConnectToIp == L"") {
        setScreen(new TitleScreen());
    }

    mProgressRenderer = new ProgressRenderer(this);
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

Minecraft::Minecraft(Component* component, Canvas* canvas, MinecraftApplet* minecraftApplet, int width,
                     int height, bool fullscreen) {
    mFixerUpper = DataFixers::createFixerUpper();
    mMultiPlayerGameMode = nullptr;
    bool_11 = false;
    mTimer = new Timer(20.0f);
    qword_40 = nullptr;
    mLevel = nullptr;
    array_68 = arrayWithLength<void*>(3, true);
    mLevelRenderer = nullptr;
    mLocalPlayer = nullptr;
    ptr_150 = nullptr;
    mParticleEngine = nullptr;
    mUser = nullptr;
    mIsPaused = false;
    mScreen = nullptr;
    dword_d8 = 0;
    mTextures = nullptr;
    mFont = nullptr;
    InitializeCriticalSection(&unk_71017C65F0);
    InitializeCriticalSection(&mCriticalSection);
    mProgressRenderer = nullptr;
    mGameRenderer = nullptr;
    qword_210 = nullptr;
    qword_218 = nullptr;
    mOrigHeight = 0;
    mGui = nullptr;
    mIsNoRender = false;
    mHitResult = nullptr;
    mOptions = nullptr;
    mSoundEngine = new SoundEngine();
    qword_258 = nullptr;
    mTexturePackRepository = nullptr;
    mWorkingDirectory = File(L"");
    mLevelStorageSource = nullptr;

    for (int i = 0; i < 4; i++) {
        mStatsCounters[i] = nullptr;
    }

    mConnectToPort = 0;
    sUnkFile = File(L"");
    mLastTimer = -1;
    dword_2e8 = 0;
    mIsRunning = true;
    dword_148 = -1;
    Stats::init();
    mOrigHeight = height;
    mIsFullscreen = fullscreen;
    mMinecraftApplet = nullptr;
    mParent = nullptr;
    mBlockColors = nullptr;
    mItemColors = nullptr;

    bool isWidescreen = Renderer::sInstance->IsWidescreen();
    int curWidth = width;
    if (!isWidescreen)
        curWidth = 3 * width / 4;
    mWidth = curWidth;
    mHeight = height;
    mDisplayWidth = width;
    mDisplayHeight = height;

    mIsFullscreen = fullscreen;  // this is set twice
    mIsAppletMode = false;

    sInstance = this;

    TextureManager::createInstance();

    for (int i = 0; i < 4; i++) {
        array_110[i] = 0;
        arr_128[i] = nullptr;
        mGameModes[i] = nullptr;
    }

    qword_328 = nullptr;
    mTutorialFlags = 0;
    byte_38 = false;
    mSoundEngine->init(nullptr);
    mClientMasterGameMode = new ClientMasterGameMode();
    mGhostController = nullptr;
    mLobbyGameMode = nullptr;
}

void Minecraft::startAndConnectTo(const std::wstring& name, const std::wstring& session,
                                  const std::wstring& arg3) {
    std::wstring copy_name = name;  // why? you literally could make it not pass ptr to string
    Minecraft* mc = new Minecraft(nullptr, nullptr, nullptr, 1280, 720, false);
    mc->mServerDomain = L"www.minecraft.net";

    if (copy_name != L"" && session != L"") {
        mc->mUser = new User(copy_name, session);
    } else {
        mc->mUser
            = new User(L"Player" + std::to_wstring((int)(System::processTimeInMilliSecs() % 1000)), L"");
    }

    mc->run();
}

BlockRenderDispatcher* Minecraft::getBlockRenderer() {
    return mBlockRenderDispatcher;
}

EntityRenderDispatcher* Minecraft::getEntityRenderDispatcher() {
    return mEntityRenderDispatcher;
}

DataFixerUpper* Minecraft::getFixerUpper() {
    return mFixerUpper;
}

ItemInHandRenderer* Minecraft::getItemInHandRenderer() {
    return mItemInHandRenderer;
}

ItemRenderer* Minecraft::getItemRenderer() {
    return mItemRenderer;
}

int Minecraft::getAverageFps() {
    return sAverageFps;
}

bool Minecraft::isUsingDefaultSkin() {
    return GetInstance()->mTexturePackRepository->getSelected();
}

bool Minecraft::isTutorial() {
    return mTutorialFlags != 0;
}

bool Minecraft::useFancyGraphics() {
    return Minecraft::sInstance && Minecraft::sInstance->mOptions->mIsFancyGraphics;
}

void Minecraft::run() {
    mIsRunning = true;
    init();
}

void Minecraft::SetGhostController(GhostController* ghostController) {
    if (mGhostController) {
        mGhostController->setDone();
        mGhostControllers.push_back(mGhostController);
    }
    mGhostController = ghostController;
}
