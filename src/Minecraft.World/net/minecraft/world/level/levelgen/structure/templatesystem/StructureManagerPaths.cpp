#include "net/minecraft/util/StringUtils.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"
#include <utility>
const wchar_t* const StructureManager::s_resourceNames[RESOURCE_COUNT] = {
#include "StructureNames.inc"

};
std::wstring StructureManager::getArchivePath(int id) {
    const std::wstring name(s_resourceNames[id]);
    return std::move(replaceAll(name, L"/", L"\\").insert(0, L"Structures\\"));
}
