#include "net/minecraft/util/datafix/DataFixerUpper.h"

#include "com/mojang/nbt/CompoundTag.h"

#include "net/minecraft/util/datafix/DataFix.h"
#include "net/minecraft/util/datafix/walker/DataWalker.h"

// name guessed
DataFixer::DataFixer() {}

DataFixerUpper::DataFixerUpper(int version) {
    m_version = version;
}

// name guessed
std::vector<DataWalker*>* DataFixerUpper::getOrCreateWalker(DataFixTypes::EDataFixTypes type) {
    auto* walkers = m_walkers[type];
    // The original replaces even an existing empty vector without deleting it.
    if (!walkers || walkers->empty()) {
        walkers = new std::vector<DataWalker*>();
        m_walkers[type] = walkers;
    }
    return walkers;
}

// name guessed
std::vector<DataFix*>* DataFixerUpper::getOrCreateFix(DataFixTypes::EDataFixTypes type) {
    auto* fixes = m_fixes[type];
    if (!fixes || fixes->empty()) {
        fixes = new std::vector<DataFix*>();
        m_fixes[type] = fixes;
    }
    return fixes;
}

// name guessed
void DataFixerUpper::addWalker(DataFixTypes::EDataFixTypes type, DataWalker* walker) {
    auto* walkers = getOrCreateWalker(type);
    walkers->push_back(walker);
}

// name guessed
// NON_MATCHING | score: 25 (lower is better)
void DataFixerUpper::addFixer(DataFixTypes::EDataFixTypes type, DataFix* fix) {
    auto* fixes = getOrCreateFix(type);
    int version = fix->getVersion();
    if (version > m_version)
        return;
    auto end = fixes->end();
    if (fixes->begin() != end) {
        int lastVersion = (*(end - 1))->getVersion();
        end = fixes->end();
        if (lastVersion > version) {
            // The Switch routine appends after this scan rather than inserting in order.
            for (auto it = fixes->begin(); it != end; ++it) {
                if ((*it)->getVersion() > version) {
                    fixes->push_back(fix);
                    return;
                }
            }
            return;
        }
    }
    fixes->push_back(fix);
}

const std::wstring DataFixerUpper::DATA_VERSION_KEY = L"DataVersion";  // name guessed

// name guessed
CompoundTag* DataFixerUpper::updateData(DataFixTypes::EDataFixTypes type, CompoundTag* tag) {
    int version = -1;
    if (tag->contains(DATA_VERSION_KEY, 99)) {
        version = tag->getInt(DATA_VERSION_KEY);
        if (version > 921)
            return tag;
    }
    return update(type, tag, version);
}

// name guessed
CompoundTag* DataFixerUpper::update(DataFixTypes::EDataFixTypes type, CompoundTag* tag, int version) {
    if (version < m_version) {
        tag = applyFixes(type, tag, version);
        tag = applyWalkers(type, tag, version);
    }
    return tag;
}

// name guessed
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

// name guessed
CompoundTag* DataFixerUpper::applyWalkers(DataFixTypes::EDataFixTypes type, CompoundTag* tag, int version) {
    auto found = m_walkers.find(type);
    if (found != m_walkers.end()) {
        for (auto* walker : *found->second)
            tag = walker->walk(this, tag, version);
    }
    return tag;
}
