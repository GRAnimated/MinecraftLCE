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

    Mob* m_mob;
    std::vector<std::weak_ptr<Entity>> m_seen;
    std::vector<std::weak_ptr<Entity>> m_unseen;
};
