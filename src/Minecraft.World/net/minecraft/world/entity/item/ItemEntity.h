#pragma once

#include "net/minecraft/world/entity/Entity.h"
#include <string>

class ItemEntity : public Entity {
public:
    void setNoPickUpDelay();
    void setOwner(const std::wstring&);
    void makeFakeItem();
};