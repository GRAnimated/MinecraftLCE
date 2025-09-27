#include "net/minecraft/client/model/models/BedModel.h"

#include "net/minecraft/client/model/geom/ModelPartSkin.h"

BedModel::BedModel(const ModelDefinition& def) : Model() {
    if (def.DoesOverrideModel()) {
        this->mBedPart = new ModelPartSkin(this, L"bed", def, nullptr, 0.0f, nullptr);
        this->mLegPart = new ModelPartSkin(this, L"leg1", def, nullptr, 0.0f, nullptr);
    } else {
        this->mTexWidth = 64;
        this->mTexHeight = 128;

        this->mBedPart = new ModelPartSkin(this, 0, 0);
        this->mLegPart = new ModelPartSkin(this, 0, 22);
        this->mLegPart->texOffs(0, 44);
        this->mBedPart->addBox(0.0f, 0.0f, 0.0f, 16, 32, 6, 0.0f);
        this->mBedPart->addBoxMapTex(3.0f, 31.0f, 6.0f, 10, 1, 3, 38, 2, 0.0f);
        this->mBedPart->addBoxMapTex(3.0f, 0.0f, 6.0f, 10, 1, 3, 38, 38, 0.0f);
        this->mBedPart->addBoxMapTex(15.0f, 3.0f, 6.0f, 1, 26, 3, 52, 6, 0.0f);
        this->mBedPart->addBoxMapTex(0.0f, 3.0f, 6.0f, 1, 26, 3, 44, 6, 0.0f);
        this->mLegPart->addBoxMapTex(0.0f, 0.0f, 6.0f, 3, 3, 3, 0, 38, 0.0f);
        this->mLegPart->addBoxMapTex(13.0f, 0.0f, 6.0f, 3, 3, 3, 12, 38, 0.0f);
        this->mLegPart->addBoxMapTex(0.0f, 29.0f, 6.0f, 3, 3, 3, 0, 44, 0.0f);
        this->mLegPart->addBoxMapTex(13.0f, 29.0f, 6.0f, 3, 3, 3, 12, 44, 0.0f);
    }

    this->compileSkinnedDrawlist();
}

void BedModel::render(bool shouldCallList) {
    this->mBedPart->render(0.0625f, shouldCallList, false);
    this->mLegPart->render(0.0625f, shouldCallList, false);
    this->callSkinnedDrawlist();
}

std::wstring BedModel::getName() {
    return L"bed";
}
