#include "Minecraft.World/level/storage/block/CompressedBlockStorage.h"

void CompressedBlockStorage::write(DataOutputStream* out) {
    out->writeInt(this->storage.length);
    if (this->storage.data) {
        arrayWithLength<unsigned char> a = arrayWithLength<unsigned char>(this->storage.data, this->storage.length);
        out->write(a);
    }
}