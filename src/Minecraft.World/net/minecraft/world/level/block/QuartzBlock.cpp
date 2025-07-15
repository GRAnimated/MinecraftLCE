#include "net/minecraft/world/level/block/QuartzBlock.h"

#include "net/minecraft/client/renderer/texture/IconRegister.h"

std::wstring QuartzBlock::TEXTURE_NAME_TOP = L"top";
std::wstring QuartzBlock::TEXTURE_NAME_CHISELED_TOP = L"chiseled_top";
std::wstring QuartzBlock::TEXTURE_NAME_LINES_TOP = L"lines_top";
std::wstring QuartzBlock::TEXTURE_NAME_BOTTOM = L"bottom";
std::wstring QuartzBlock::TEXTURE_NAMES[5] = {L"side", L"chiseled", L"lines", L"", L""};

// NON_MATCHING: Every registerIcon needs two extra strings to be created, why??
void QuartzBlock::registerIcons(IconRegister* iconRegister) {
    for (int i = 0; i < 5; i++) {
        if (!TEXTURE_NAMES[i].empty()) {
            mTextures[i] = iconRegister->registerIcon(getIconName().append(L"_").append(TEXTURE_NAMES[i]));
        } else {
            mTextures[i] = mTextures[i - 1];
        }
    }

    mTextureTop = iconRegister->registerIcon(getIconName().append(L"_").append(TEXTURE_NAME_TOP));
    mTextureChiseledTop
        = iconRegister->registerIcon(getIconName().append(L"_").append(TEXTURE_NAME_CHISELED_TOP));
    mTextureLinesTop = iconRegister->registerIcon(getIconName().append(L"_").append(TEXTURE_NAME_LINES_TOP));
    mTextureBottom = iconRegister->registerIcon(getIconName().append(L"_").append(TEXTURE_NAME_BOTTOM));
}
