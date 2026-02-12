#include "net/minecraft/client/Minecraft.h"

#include "NX/Platform.h"
#include "NX/Render/RendererCore.h"
#include "java/io/File.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/client/GhostController.h"
#include "net/minecraft/client/Options.h"
#include "net/minecraft/client/Timer.h"
#include "net/minecraft/client/Tooltips.h"
#include "net/minecraft/client/User.h"
#include "net/minecraft/client/color/ColourTable.h"
#include "net/minecraft/client/color/block/BlockColors.h"
#include "net/minecraft/client/color/item/ItemColors.h"
#include "net/minecraft/client/gui/Font.h"
#include "net/minecraft/client/gui/Gui.h"
#include "net/minecraft/client/gui/screens/TitleScreen.h"
#include "net/minecraft/client/multiplayer/ClientPacketListener.h"
#include "net/minecraft/client/particle/ParticleEngine.h"
#include "net/minecraft/client/particle/ParticleType.h"
#include "net/minecraft/client/renderer/GameRenderer.h"
#include "net/minecraft/client/renderer/LevelRenderer.h"
#include "net/minecraft/client/renderer/ProgressRenderer.h"
#include "net/minecraft/client/renderer/block/BlockRenderDispatcher.h"
#include "net/minecraft/client/renderer/blockentity/BlockEntityRenderDispatcher.h"
#include "net/minecraft/client/renderer/entity/EntityBlockRenderer.h"
#include "net/minecraft/client/renderer/entity/EntityRenderDispatcher.h"
#include "net/minecraft/client/renderer/entity/ItemRenderer.h"
#include "net/minecraft/client/renderer/item/ItemInHandRenderer.h"
#include "net/minecraft/client/renderer/platform/GlStateManager.h"
#include "net/minecraft/client/renderer/texture/TextureManager.h"
#include "net/minecraft/client/renderer/texture/Textures.h"
#include "net/minecraft/client/resources/TexturePackRepository.h"
#include "net/minecraft/client/sounds/SoundEngine.h"
#include "net/minecraft/client/tutorial/Tutorial.h"
#include "net/minecraft/client/ui/scene/scenes/UIScene_CreativeMenu.h"
#include "net/minecraft/client/ui/scene/scenes/UIScene_LeaderboardsMenu.h"
#include "net/minecraft/core/System.h"
#include "net/minecraft/stats/Stats.h"
#include "net/minecraft/stats/StatsCounter.h"
#include "net/minecraft/util/datafix/DataFixers.h"
#include "net/minecraft/world/ArrayWithLength.h"
#include "net/minecraft/world/MinecraftWorld.h"
#include "net/minecraft/world/level/FoliageColor.h"
#include "net/minecraft/world/level/GrassColor.h"
#include "net/minecraft/world/level/gamemode/ClientMasterGameMode.h"
#include "net/minecraft/world/level/gamemode/MasterGameMode.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameDef.h"
#include "net/minecraft/world/level/gamemode/minigames/MiniGameMedals.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"
#include "net/minecraft/world/level/storage/McRegionLevelStorageSource.h"
#include <string>

Minecraft* Minecraft::sInstance;

int Minecraft::sAverageFps;
bool Minecraft::sUnk;
EntityBlockRenderer* Minecraft::sEntityBlockRenderer;
File Minecraft::sUnkFile;
nn::os::MutexType Minecraft::unk_71017C65F0;

Minecraft* Minecraft::GetInstance() {
    return sInstance;
}

void Minecraft::init() {
    m_workingDirectory = File(L"");

    m_levelStorageSource
        = new McRegionLevelStorageSource(File(m_workingDirectory, L"saves"), getFixerUpper());

    m_options = new Options(this, m_workingDirectory);

    m_texturePackRepository = new TexturePackRepository(File(m_workingDirectory), this);
    m_texturePackRepository->addDebugPacks();

    m_textures = new Textures(m_texturePackRepository, m_options);

    m_font = new Font(m_options, L"font/Default", m_textures, 0, &Font::sDefaultFontRsrc, 23, 28, 16, 16,
                      Font::sDefaultText);
    m_altFont = new Font(m_options, L"font/alternate", m_textures, 0, &Font::sAlternateFontRsrc, 16, 16, 8, 8,
                         nullptr);

    GrassColor::init(
        m_textures->loadTexturePixels(_TEXTURE_NAME::eTextureName_GRASSCOLOR, L"misc/grasscolor"));
    FoliageColor::init(
        m_textures->loadTexturePixels(_TEXTURE_NAME::eTextureName_FOLIAGECOLOR, L"misc/foliagecolor"));

    Biome::generateColoursDebugOutput();

    m_blockAtlas = new TextureAtlas(0, L"terrain", L"textures/blocks/", 0, true);

    m_blockColors = BlockColors::createDefault();
    m_itemColors = ItemColors::createDefault(m_blockColors);

    m_itemRenderer = new ItemRenderer(m_entityRenderDispatcher, m_textures, m_itemColors);
    m_entityRenderDispatcher = new EntityRenderDispatcher(m_textures, m_itemRenderer);

    GlStateManager::enableLighting();
    m_itemInHandRenderer = new ItemInHandRenderer(this);
    GlStateManager::disableLighting();

    m_gameRenderer = new GameRenderer(this, 0);
    m_blockRenderDispatcher = new BlockRenderDispatcher(m_blockColors);
    // static shit
    BlockEntityRenderDispatcher::sInstance->m_textures = m_textures;
    sEntityBlockRenderer = new EntityBlockRenderer();

    m_statsCounters[0] = new StatsCounter();
    m_statsCounters[1] = new StatsCounter();
    m_statsCounters[2] = new StatsCounter();
    m_statsCounters[3] = new StatsCounter();

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

    m_levelRenderer = new LevelRenderer(this, m_textures);

    m_textures->stitch();

    m_particleEngine = new ParticleEngine(m_level, m_textures);

    MemSect(31);
    {
        std::wstring status(L"Post startup");
    }
    MemSect(0);

    m_gui = new Gui(this);

    if (m_connectToIp == L"") {
        setScreen(new TitleScreen());
    }

    m_progressRenderer = new ProgressRenderer(this);
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
    Minecraft::GetInstance()->m_lobbyGameMode = &MiniGameDef::GetCustomGameModeById(LOBBY, true);
    ClientPacketListener::staticCtor();
}

void Minecraft::start(const std::wstring& str1, const std::wstring& str2) {
    startAndConnectTo(str1, str2, L"");
}

Minecraft::Minecraft(Component* component, Canvas* canvas, MinecraftApplet* minecraftApplet, int width,
                     int height, bool fullscreen) {
    m_fixerUpper = DataFixers::createFixerUpper();
    m_multiPlayerGameMode = nullptr;
    m_bool11 = false;
    m_timer = new Timer(20.0f);
    m_qword40 = nullptr;
    m_level = nullptr;
    m_array68 = arrayWithLength<void*>(3, true);
    m_levelRenderer = nullptr;
    m_localPlayer = nullptr;
    m_ptr150 = nullptr;
    m_particleEngine = nullptr;
    m_user = nullptr;
    m_isPaused = false;
    m_screen = nullptr;
    m_dwordD8 = 0;
    m_textures = nullptr;
    m_font = nullptr;
    InitializeCriticalSection(&unk_71017C65F0);
    InitializeCriticalSection(&m_criticalSection);
    m_progressRenderer = nullptr;
    m_gameRenderer = nullptr;
    m_qword210 = nullptr;
    m_qword218 = nullptr;
    m_origHeight = 0;
    m_gui = nullptr;
    m_isNoRender = false;
    m_hitResult = nullptr;
    m_options = nullptr;
    m_soundEngine = new SoundEngine();
    m_qword258 = nullptr;
    m_texturePackRepository = nullptr;
    m_workingDirectory = File(L"");
    m_levelStorageSource = nullptr;

    for (int i = 0; i < 4; i++) {
        m_statsCounters[i] = nullptr;
    }

    m_connectToPort = 0;
    sUnkFile = File(L"");
    m_lastTimer = -1;
    m_dword2e8 = 0;
    m_isRunning = true;
    m_dword148 = -1;
    Stats::init();
    m_origHeight = height;
    m_isFullscreen = fullscreen;
    m_minecraftApplet = nullptr;
    m_parent = nullptr;
    m_blockColors = nullptr;
    m_itemColors = nullptr;

    bool isWidescreen = Renderer::sInstance->IsWidescreen();
    int curWidth = width;
    if (!isWidescreen)
        curWidth = 3 * width / 4;
    m_width = curWidth;
    m_height = height;
    m_displayWidth = width;
    m_displayHeight = height;

    m_isFullscreen = fullscreen;  // this is set twice
    m_isAppletMode = false;

    sInstance = this;

    TextureManager::createInstance();

    for (int i = 0; i < 4; i++) {
        m_array110[i] = 0;
        m_arr128[i] = nullptr;
        m_gameModes[i] = nullptr;
    }

    m_qword328 = nullptr;
    m_tutorialFlags = 0;
    m_byte38 = false;
    m_soundEngine->init(nullptr);
    m_clientMasterGameMode = new ClientMasterGameMode();
    m_ghostController = nullptr;
    m_lobbyGameMode = nullptr;
}

void Minecraft::startAndConnectTo(const std::wstring& name, const std::wstring& session,
                                  const std::wstring& arg3) {
    std::wstring copy_name = name;  // why? you literally could make it not pass ptr to string
    Minecraft* mc = new Minecraft(nullptr, nullptr, nullptr, 1280, 720, false);
    mc->m_serverDomain = L"www.minecraft.net";

    if (copy_name != L"" && session != L"") {
        mc->m_user = new User(copy_name, session);
    } else {
        mc->m_user
            = new User(L"Player" + std::to_wstring((int)(System::processTimeInMilliSecs() % 1000)), L"");
    }

    mc->run();
}

BlockRenderDispatcher* Minecraft::getBlockRenderer() {
    return m_blockRenderDispatcher;
}

EntityRenderDispatcher* Minecraft::getEntityRenderDispatcher() {
    return m_entityRenderDispatcher;
}

DataFixerUpper* Minecraft::getFixerUpper() {
    return m_fixerUpper;
}

ItemInHandRenderer* Minecraft::getItemInHandRenderer() {
    return m_itemInHandRenderer;
}

ItemRenderer* Minecraft::getItemRenderer() {
    return m_itemRenderer;
}

int Minecraft::getAverageFps() {
    return sAverageFps;
}

bool Minecraft::isUsingDefaultSkin() {
    return GetInstance()->m_texturePackRepository->getSelected();
}

bool Minecraft::isTutorial() {
    return m_tutorialFlags != 0;
}

bool Minecraft::useFancyGraphics() {
    return Minecraft::sInstance && Minecraft::sInstance->m_options->m_isFancyGraphics;
}

void Minecraft::run() {
    m_isRunning = true;
    init();
}

void Minecraft::SetGhostController(GhostController* ghostController) {
    if (m_ghostController) {
        m_ghostController->setDone();
        m_ghostControllers.push_back(m_ghostController);
    }
    m_ghostController = ghostController;
}
