#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"

#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureTemplate.h"

void StructureManager::staticCtor() {}
StructureManager::StructureManager(DataFixerUpper* fixer) : m_fixerUpper(fixer) {}
StructureManager::~StructureManager() {
    for (const auto& entry : m_templates)
        delete entry.second;
}
