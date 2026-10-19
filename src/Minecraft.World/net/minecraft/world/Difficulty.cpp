#include "net/minecraft/world/Difficulty.h"

Difficulty* Difficulty::byId(int id) {
    return DIFFICULTIES[id % 4];
}

int Difficulty::getId() const {
    return m_id;
}
