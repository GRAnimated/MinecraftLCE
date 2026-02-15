#include "net/minecraft/client/model/models/BedModel.h"

#include "net/minecraft/client/model/geom/ModelPartSkin.h"

BedModel::BedModel(const ModelDefinition& def) : Model() {
    if (def.DoesOverrideModel()) {
        this->m_bedPart = new ModelPartSkin(this, L"bed", def, nullptr, 0.0f, nullptr);
        this->m_legPart = new ModelPartSkin(this, L"leg1", def, nullptr, 0.0f, nullptr);
    } else {
        this->m_texWidth = 64;
        this->m_texHeight = 128;

        this->m_bedPart = new ModelPartSkin(this, 0, 0);
        this->m_legPart = new ModelPartSkin(this, 0, 22);
        this->m_legPart->texOffs(0, 44);
        this->m_bedPart->addBox(0.0f, 0.0f, 0.0f, 16, 32, 6, 0.0f);
        this->m_bedPart->addBoxMapTex(3.0f, 31.0f, 6.0f, 10, 1, 3, 38, 2, 0.0f);
        this->m_bedPart->addBoxMapTex(3.0f, 0.0f, 6.0f, 10, 1, 3, 38, 38, 0.0f);
        this->m_bedPart->addBoxMapTex(15.0f, 3.0f, 6.0f, 1, 26, 3, 52, 6, 0.0f);
        this->m_bedPart->addBoxMapTex(0.0f, 3.0f, 6.0f, 1, 26, 3, 44, 6, 0.0f);
        this->m_legPart->addBoxMapTex(0.0f, 0.0f, 6.0f, 3, 3, 3, 0, 38, 0.0f);
        this->m_legPart->addBoxMapTex(13.0f, 0.0f, 6.0f, 3, 3, 3, 12, 38, 0.0f);
        this->m_legPart->addBoxMapTex(0.0f, 29.0f, 6.0f, 3, 3, 3, 0, 44, 0.0f);
        this->m_legPart->addBoxMapTex(13.0f, 29.0f, 6.0f, 3, 3, 3, 12, 44, 0.0f);
    }

    this->compileSkinnedDrawlist();
}

void BedModel::render(bool shouldCallList) {
    this->m_bedPart->render(0.0625f, shouldCallList, false);
    this->m_legPart->render(0.0625f, shouldCallList, false);
    this->callSkinnedDrawlist();
}

std::wstring BedModel::getName() {
    return L"bed";
}
