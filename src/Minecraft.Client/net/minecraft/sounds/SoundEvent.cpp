#include "net/minecraft/sounds/SoundEvent.h"

const SoundEvent* SoundEvent::UI_PRESS;
const SoundEvent* SoundEvent::ITEM_PICKUP;  // name guessed
const SoundEvent* SoundEvent::ENTER_THERMAL;
const SoundEvent* SoundEvent::ENTER_BOOST;
MappedRegistry<ResourceLocation, const SoundEvent*> SoundEvent::Registry;  // name guessed
int SoundEvent::NEXT_ID;

// name guessed
SoundEvent::SoundEvent(std::wstring name, float range) {
    m_id = -1;
    m_flags = 0;
    m_name = name;
    m_range = range;
}

// name guessed
// NON_MATCHING | score: 20 (lower is better)
SoundEvent::SoundEvent(std::wstring name, float range, int flags) {
    m_id = -1;
    m_name = name;
    m_flags = flags;
    m_range = range;
}

// name guessed
std::wstring SoundEvent::getName() {
    return m_name;
}
// name guessed
float SoundEvent::getRange() {
    return m_range;
}
// name guessed
bool SoundEvent::isUISound() {
    return m_flags == 1;
}
// name guessed
void SoundEvent::setId(int id) {
    m_id = id;
}

// name guessed
SoundEvent* SoundEvent::registerEvent(SoundEvent* event) {
    event->setId(NEXT_ID);
    ResourceLocation location(event->getName());
    Registry.registerMapping(NEXT_ID, location, event);
    ++NEXT_ID;
    return event;
}

static_assert(sizeof(SoundEvent) == 0x28, "Switch sound event ABI");
static_assert(offsetof(SoundEvent, m_id) == 0x18, "Switch sound ID offset");
static_assert(offsetof(SoundEvent, m_range) == 0x1c, "Switch sound range offset");
static_assert(offsetof(SoundEvent, m_flags) == 0x20, "Switch sound flags offset");
