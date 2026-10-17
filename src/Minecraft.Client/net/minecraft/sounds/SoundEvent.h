#pragma once

#include "net/minecraft/resources/ResourceLocation.h"
#include <string>

class SoundEvent {
public:
    static const SoundEvent* UI_PRESS;
    static const SoundEvent* ITEM_PICKUP;
    static const SoundEvent* ENTER_THERMAL;
    static const SoundEvent* ENTER_BOOST;

    static MappedRegistry<ResourceLocation, const SoundEvent*> Registry;
    static int NEXT_ID;
    static SoundEvent* registerEvent(SoundEvent*);

    // The default overload takes its string by value: registerSound copies the
    // caller's string before entering the original constructor.
    SoundEvent(std::wstring name, float range);
    SoundEvent(std::wstring name, float range, int flags);
    std::wstring getName();
    float getRange();
    bool isUISound();
    void setId(int id);

    std::wstring m_name;
    int m_id;
    float m_range;
    int m_flags;
};
