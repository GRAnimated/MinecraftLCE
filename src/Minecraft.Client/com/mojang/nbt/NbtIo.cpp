#include "com/mojang/nbt/NbtIo.h"

#include "com/mojang/nbt/CompoundTag.h"
#include "com/mojang/nbt/EndTag.h"
#include "java/io/DataInput.h"
#include "java/io/DataOutput.h"
#include <memory>
#include <stdexcept>

Tag* NbtIo::readUnnamedTag(DataInput* input, int unk) {
    u8 ch = Tag::readType(input);
    if (ch == 0)
        return new EndTag();

    if (ch == 255)
        return new EndTag();

    input->readUTF();

    std::unique_ptr<Tag> tag(Tag::newTag(ch));
    tag->load(input, unk);
    return tag.release();
}

CompoundTag* NbtIo::read(DataInput* input) {
    Tag* tag = readUnnamedTag(input, 0);
    if (tag->getId() == Tag::TAG_Compound)
        return (CompoundTag*)tag;

    if (tag != nullptr)
        delete tag;

    return nullptr;
}

void NbtIo::writeUnnamedTag(Tag* tag, DataOutput* output) {
    output->writeByte(tag->getId());
    if (tag->getId() == 0)
        return;

    output->writeUTF(L"");
    tag->write(output);
}

void NbtIo::write(CompoundTag* tag, DataOutput* output) {
    return writeUnnamedTag(tag, output);
}
