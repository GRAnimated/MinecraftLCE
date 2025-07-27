#pragma once

#pragma once

#include "net/minecraft/world/entity/Entity.h"
#include <memory>

class FireworksRocketEntity : public Entity {
public:
    std::shared_ptr<Player> getOwner() const;
};
