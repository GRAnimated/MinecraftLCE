#pragma once

#include <memory>

class Entity;

class Explosion {
public:
    std::shared_ptr<Entity> getDirectSource();
};
