#include "Minecraft.h"
#include "Minecraft.Core/io/File.h"
#include "platform/NX/Platform.h"
#include "Minecraft.World/ArrayWithLength.h"

Minecraft* Minecraft::GetInstance() {
    return sInstance;
}

// NON_MATCHING
void Minecraft::run() {
    File *saves = new File(L"");
    this->mSaves = *saves;
    delete saves;

    File *sourceFile = new File(this->mSaves, L"saves");
    this->mMcRegionLevelStorageSource = new McRegionLevelStorageSource(*sourceFile, getFixerUpper());
    delete sourceFile;

    // I don't think mSaves should be used here directly...
    // name probably also shouldn't be here too but I need to destroy the file, and needed a name to create it.
    File *optionsFile = new File(this->mSaves, L"options.txt");
    this->mOptions = new Options(this, *optionsFile);
    delete optionsFile;

    // same deal
    // these calls are actually trying to create what looks to be a new wstring... but that doesn't seem right to me... why pass entire save folder to this? (never even makes a "resourcepacks" folder)
    File *texturesFolder = new File(this->mSaves, L"");
    this->mTexturePackRepository = new TexturePackRepository(*texturesFolder, this);
    delete texturesFolder;

    this->mTexturePackRepository->addDebugPacks();

    this->mTextures = new Textures(this->mTexturePackRepository, this->mOptions);

    // nullptr values are temp.
    this->mDefaultFont = new Font(this->mOptions, L"font/Default", this->mTextures, 0, nullptr, 23, 28, 16, 16, nullptr);

    // first nullptr value is temp, second is meant to be nullptr
    this->mAlternateFont = new Font(this->mOptions, L"font/Alternate", this->mTextures, 0, nullptr, 16, 16, 8, 8, nullptr);

    arrayWithLength<int> grassColorTexture = this->mTextures->loadTexturePixels(_TEXTURE_NAME::GRASS_COLOR, L"misc/grasscolor");
    GrassColor::init(grassColorTexture);

    arrayWithLength<int> foliageColorTexture = this->mTextures->loadTexturePixels(_TEXTURE_NAME::FOLIAGE_COLOR, L"misc/foliagecolor");
    FoliageColor::init(foliageColorTexture);

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
    GlStateManager::shadeModel(0LL);
    GlStateManager::clearDepth(1.0);
    GlStateManager::enableDepthTest();
    GlStateManager::depthFunc(4u);
    GlStateManager::enableAlphaTest();
    GlStateManager::alphaFunc(5u, 0.1);
    GlStateManager::cullFace(1);
    GlStateManager::matrixMode(1);
    GlStateManager::loadIdentity();
    GlStateManager::matrixMode(0);

    MemSect(31);
    status = L"Startup";
    MemSect(0);

    this->mLevelRenderer = new LevelRenderer(this, this->mTextures);
    this->mParticleEngine = new ParticleEngine(this->mLevel, this->mTextures);

    MemSect(31);
    status = L"Post startup";
    MemSect(0);

    this->mGui = new Gui(this);
    
    std::wstring *ul2b0;
    bool ul2a8 = ((unsigned long long)wstring_2a8 & 1);

    // idk what this is for, ~~maybe qword_2a8 is meant to be a bool?~~
    // nvm it's used for a string
    // I think we literally just check if the first byte is empty
    if (ul2a8)
        ul2b0 = this->wstring_2b0; // ???
    else
        ul2b0 = (std::wstring*)((unsigned long long)this->wstring_2a8 >> 1); // idfk anymore LMFAO

    // not matching statement
    if (!this->wstring_2a8->compare(0, -1, L""/*, ul2b0*/)) {
        TitleScreen *titleScreen = new TitleScreen();
        this->setScreen(titleScreen);
    }

    this->mProgressRenderer = new ProgressRenderer(this);
    Renderer::sInstance->CBuffLockStaticCreations();
}

DataFixerUpper* Minecraft::getFixerUpper() {
    return this->mFixerUpper;
}
