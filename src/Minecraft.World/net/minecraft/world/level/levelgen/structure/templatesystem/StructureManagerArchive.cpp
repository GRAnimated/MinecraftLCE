#include "java/io/ByteArrayInputStream.h"
#include "net/minecraft/client/CMinecraftApp.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"

bool StructureManager::loadArchive(int id) {
    const auto path = getArchivePath(id);
    if (!CConsoleMinecraftApp::sInstance.hasArchiveFile(path, false))
        return false;
    const auto data = CConsoleMinecraftApp::sInstance.getArchiveFile(path, false);
    if (!data.m_length || !data.m_data) {
        return false;
    }
    ByteArrayInputStream input(data);
    loadFromStream(id, &input);
    input.reset();
    delete[] data.m_data;
    return true;
}
