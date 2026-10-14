#include "net/minecraft/util/datafix/DataFix.h"
#include "net/minecraft/util/datafix/DataFixerUpper.h"
#include "net/minecraft/util/datafix/walker/DataWalker.h"

DataFixer::DataFixer() {}

DataFixerUpper::DataFixerUpper(int version) {
    m_version = version;
}

std::vector<DataWalker*>* DataFixerUpper::getOrCreateWalker(DataFixTypes::EDataFixTypes type) {
    auto* walkers = m_walkers[type];
    // The original replaces even an existing empty vector without deleting it.
    if (!walkers || walkers->empty()) {
        walkers = new std::vector<DataWalker*>();
        m_walkers[type] = walkers;
    }
    return walkers;
}

std::vector<DataFix*>* DataFixerUpper::getOrCreateFix(DataFixTypes::EDataFixTypes type) {
    auto* fixes = m_fixes[type];
    if (!fixes || fixes->empty()) {
        fixes = new std::vector<DataFix*>();
        m_fixes[type] = fixes;
    }
    return fixes;
}

void DataFixerUpper::addWalker(DataFixTypes::EDataFixTypes type, DataWalker* walker) {
    auto* walkers = getOrCreateWalker(type);
    walkers->push_back(walker);
}

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
