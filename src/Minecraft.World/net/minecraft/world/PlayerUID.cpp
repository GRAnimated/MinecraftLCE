#include "net/minecraft/world/PlayerUID.h"

#include <cstring>

PlayerUID::PlayerUID(int uid) {
    memset(this, 0, sizeof(PlayerUID));
}
// name guessed
// NON_MATCHING | score: 3335 (lower is better)
bool PlayerUID::operator==(const PlayerUID& other) const {
    if (m_leastSigBits == 0 || other.m_leastSigBits == 0) {
        if (m_gap0 != other.m_gap0 || m_mostSigBits != other.m_mostSigBits)
            return false;
    } else if (m_leastSigBits != other.m_leastSigBits) {
        return false;
    }
    if ((m_byte18 & 2) != (other.m_byte18 & 2))
        return false;
    return !(m_byte18 & 2) || ((m_byte18 ^ other.m_byte18) & 12) == 0;
}
// name guessed
bool PlayerUID::operator!=(const PlayerUID& other) const {
    return !(*this == other);
}
