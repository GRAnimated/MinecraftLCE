#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureTemplate.h"

StructureTemplate* StructureManager::getOrCreate(int id) {
    auto* result = get(id);
    if (!result) {
        result = new StructureTemplate;
        m_templates[id] = result;
    }
    return result;
}
StructureTemplate* StructureManager::get(int id) {
    if (m_templates.find(id) == m_templates.end()) {
        loadArchive(id);
        if (m_templates.find(id) == m_templates.end())
            return new StructureTemplate;  // Original failure fallback is not cached.
    }
    return m_templates.find(id)->second;
}
