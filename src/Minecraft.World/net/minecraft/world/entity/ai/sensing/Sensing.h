#pragma once

#include <memory>
#include <vector>

class Mob;
class Entity;

class Sensing {
public:
    Sensing(Mob*);

    void tick();
    bool canSee(std::shared_ptr<Entity>);

    Mob* mMob;
    std::vector<std::weak_ptr<Entity>> mSeen;
    std::vector<std::weak_ptr<Entity>> mUnseen;
};
