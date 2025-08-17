#include "net/minecraft/client/renderer/texture/Textures.h"

void Textures::stitch() {
    this->atlas->stitch();
    this->atlas2->stitch();
}
