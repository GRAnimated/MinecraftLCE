#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/util/datafix/DataFix.h"
#include "net/minecraft/util/datafix/DataFixerUpper.h"
#include "net/minecraft/util/datafix/walker/DataWalker.h"

const std::wstring DataFixerUpper::DATA_VERSION_KEY = L"DataVersion";

CompoundTag* DataFixerUpper::updateData(DataFixTypes::EDataFixTypes type, CompoundTag* tag) {
    int version = -1;
    if (tag->contains(DATA_VERSION_KEY, 99)) {
        version = tag->getInt(DATA_VERSION_KEY);
        if (version > 921)
            return tag;
    }
    return update(type, tag, version);
}

CompoundTag* DataFixerUpper::update(DataFixTypes::EDataFixTypes type, CompoundTag* tag, int version) {
    if (version < m_version) {
        tag = applyFixes(type, tag, version);
        tag = applyWalkers(type, tag, version);
    }
    return tag;
}

CompoundTag* DataFixerUpper::applyFixes(DataFixTypes::EDataFixTypes type, CompoundTag* tag, int version) {
    if (m_fixes.find(type) != m_fixes.end()) {
        auto* fixes = m_fixes[type];
        for (auto it = fixes->begin(), end = fixes->end(); it != end; ++it) {
            if (version < (*it)->getVersion())
                tag = (*it)->fix(tag);
        }
    }
    return tag;
}

CompoundTag* DataFixerUpper::applyWalkers(DataFixTypes::EDataFixTypes type, CompoundTag* tag, int version) {
    auto found = m_walkers.find(type);
    if (found != m_walkers.end()) {
        for (auto* walker : *found->second)
            tag = walker->walk(this, tag, version);
    }
    return tag;
}
