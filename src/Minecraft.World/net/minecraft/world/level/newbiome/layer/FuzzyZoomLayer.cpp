#include "net/minecraft/world/level/newbiome/layer/FuzzyZoomLayer.h"

FuzzyZoomLayer::FuzzyZoomLayer(long long seed, std::shared_ptr<Layer> parent) : ZoomLayer(seed, parent) {
    mParent = parent;
}

int FuzzyZoomLayer::modeOrRandom(int x, int y, int width, int height) {
    return Layer::random(x, y, width, height);
}
