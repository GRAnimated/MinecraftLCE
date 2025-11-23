#include "net/minecraft/world/level/block/StoneBrickBlock.h"

#include "net/minecraft/client/ui/StringIDs.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"
#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"
#include "net/minecraft/world/level/block/Block.h"
#include "net/minecraft/world/level/material/Material.h"
#include <cstring>
#include <string>

StoneBrickBlock::Variant* StoneBrickBlock::Variant::DEFAULT
    = new StoneBrickBlock::Variant(0, L"stonebrick", StringIDs::StoneBricks);
StoneBrickBlock::Variant* StoneBrickBlock::Variant::MOSSY
    = new StoneBrickBlock::Variant(1, L"mossy_stonebrick", StringIDs::MossyStoneBricks);
StoneBrickBlock::Variant* StoneBrickBlock::Variant::CRACKED
    = new StoneBrickBlock::Variant(2, L"cracked_stonebrick", StringIDs::CrackedStoneBricks);
StoneBrickBlock::Variant* StoneBrickBlock::Variant::CHISELED
    = new StoneBrickBlock::Variant(3, L"chiseled_stonebrick", StringIDs::ChiseledStoneBricks);

std::wstring StoneBrickBlock::TEXTURE_NAMES[4] = {L"", L"mossy", L"cracked", L"carved"};
int StoneBrickBlock::DEFAULT_DATA = -1;
int StoneBrickBlock::MOSSY_DATA = -1;
int StoneBrickBlock::CRACKED_DATA = -1;
int StoneBrickBlock::CHISELED_DATA = -1;

StoneBrickBlock::Variant* StoneBrickBlock::Variant::VARIANTS[4]
    = {Variant::DEFAULT, Variant::MOSSY, Variant::CRACKED, Variant::CHISELED};

StoneBrickBlock::StoneBrickBlock() : Block(Material::STONE) {
    this->DerivedInit();
    this->registerDefaultState(this->mBlockStateDefinition->any()->setValue(VARIANT, Variant::DEFAULT));
    memset(this->mVariantsTextures, 0, sizeof(this->mVariantsTextures));
}

void StoneBrickBlock::blockStaticCtor() {
    VARIANT = EnumProperty<Variant*>::create(L"variant", typeid(Variant), Variant::VARIANTS, PREDICATE);

    DEFAULT_DATA = Variant::DEFAULT->getData();
    MOSSY_DATA = Variant::MOSSY->getData();
    CRACKED_DATA = Variant::CRACKED->getData();
    CHISELED_DATA = Variant::CHISELED->getData();
}

const BlockState* StoneBrickBlock::getBlockState(int data) {
    return this->defaultBlockState()->setValue(VARIANT, Variant::byData(data));
}

int StoneBrickBlock::convertBlockStateToLegacyData(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

int StoneBrickBlock::getSpawnResourcesAuxValue(const BlockState* state) {
    return state->getValue<Variant*>(VARIANT)->getData();
}

unsigned int StoneBrickBlock::getDescriptionId(int data) {
    return this->getBlockState(data)->getValue<Variant*>(VARIANT)->getTranslationKey();
}

void StoneBrickBlock::registerIcons(IconRegister* iconReg) {
    for (int i = 0; i < sizeof(mVariantsTextures) / sizeof(TextureAtlasSprite*); ++i) {
        std::wstring texName = this->getIconName();

        if (!TEXTURE_NAMES[i].empty()) {
            texName += L"_" + TEXTURE_NAMES[i];
        }

        this->mVariantsTextures[i] = iconReg->registerIcon(texName);
    }
}

TextureAtlasSprite* StoneBrickBlock::getTexture(const Direction*, const BlockState* state) {
    return this->mVariantsTextures[state->getValue<Variant*>(VARIANT)->getData()];
}

// NON_MATCHING: static array handling is generated differently
BlockStateDefinition* StoneBrickBlock::createBlockStateDefinition() {
    static const Property* properties[1]{VARIANT};
    return new BlockStateDefinition(this, properties);
}
