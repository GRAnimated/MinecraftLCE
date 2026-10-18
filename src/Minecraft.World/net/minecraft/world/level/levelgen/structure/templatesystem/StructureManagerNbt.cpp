#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/NbtIo.h"
#include "net/minecraft/util/datafix/DataFixerUpper.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureManager.h"
#include "net/minecraft/world/level/levelgen/structure/templatesystem/StructureTemplate.h"

void StructureManager::loadFromStream(int id, InputStream* input) {
    CompoundTag* tag = NbtIo::readCompressed(input);
    if (!tag->contains(DataFixerUpper::DATA_VERSION_KEY, 99))
        tag->putInt(DataFixerUpper::DATA_VERSION_KEY, 500);
    StructureTemplate* structure = new StructureTemplate();
    CompoundTag* updated = m_fixerUpper->updateData(DataFixTypes::STRUCTURE, tag);
    structure->loadTag(updated);
    delete tag;
    int key = id;
    m_templates[key] = structure;
}
