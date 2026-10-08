#include "fui/node/document/menu/FJ_Panorama.h"

std::string FJ_Panorama::sName = "Panorama";

int FJ_Panorama::GetCurrentFrame() {
    FJ_FuiNode *dayPanorama = reinterpret_cast<FJ_FuiNode*>(this->getChildByName("Panorama_Day"));

    if (dayPanorama) {
        FJ_FuiNode *child = reinterpret_cast<FJ_FuiNode*>(dayPanorama->getChildAt(0));

        if (child) {
            return child->currentFrame();
        }
    }

    return 0;
}
