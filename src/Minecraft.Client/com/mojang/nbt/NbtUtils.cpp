#include "com/mojang/nbt/NbtUtils.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "net/minecraft/world/level/block/Blocks.h"
#include "net/minecraft/world/level/block/state/BlockStateDefinition.h"

// name guessed
const BlockState* NbtUtils::readBlockState(CompoundTag* tag) {
    if (!tag->contains(L"Name", Tag::TAG_String))
        return Blocks::AIR->defaultBlockState();

    Block* block = Blocks::byString(tag->getString(L"Name"));
    const BlockState* state = block->defaultBlockState();
    if (tag->contains(L"Properties", Tag::TAG_Compound)) {
        CompoundTag* propertyTag = tag->getCompound(L"Properties");
        BlockStateDefinition* definition = block->getBlockStateDefinition();
        std::vector<std::wstring>* keys = propertyTag->getAllKeys();
        auto properties = definition->getProperties();
        for (auto keyIt = keys->begin(); keyIt != keys->end(); ++keyIt) {
            auto key = *keyIt;
            for (auto propertyIt = properties.begin(); propertyIt != properties.end(); ++propertyIt) {
                const Property* property = *propertyIt;
                if (key == property->getName()) {
                    Boxed* value = property->getValue(propertyTag->getString(key));
                    state = state->setBoxedValue(property, value);
                    delete value;
                }
            }
        }
        // getAllKeys transfers ownership of the vector to the caller.
        keys->~vector();
        ::operator delete(keys);
    }
    return state;
}
