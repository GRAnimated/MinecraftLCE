#include "net/minecraft/world/level/storage/block/CompressedBlockStorage.h"

#include "java/io/DataInputStream.h"

#include "java/io/DataOutputStream.h"
#include "net/minecraft/core/System.h"

void CompressedBlockStorage::staticCtor() {
    InitializeCriticalSectionAndSpinCount(&sMutex, 0x1400);

    sStack[0].doSomething();
    sStack[1].doSomething();
    sStack[2].doSomething();
}

void CompressedBlockStorage::write(DataOutputStream* out) {
    out->writeInt(this->mLength);
    if (this->mData) {
        const arrayWithLength<unsigned char> a = arrayWithLength<unsigned char>(this->mData, this->mLength);
        out->write(a);
    }
}

void CompressedBlockStorage::read(DataInputStream* s) {
    const int i = s->readInt();

    if (i <= 0)
        return;

    if (this->mData)
        free(this->mData, this->mLength);

    this->mData = create(i, 0);
    const arrayWithLength<unsigned char> arr = arrayWithLength<unsigned char>(this->mData, i);
    this->mLength = i;

    s->readBytes(arr);
    this->compress(-1);
}

void CompressedBlockStorage::compress(int i) {
    get(i, i, i);  // STUB!
}

int CompressedBlockStorage::get(int x, int y, int z) {
    if (!this->mData)
        return 0;

    unsigned char* data = this->mData + 1024;
    unsigned short* unk = (unsigned short*)this->mData;

    int block;
    int blockData;

    getIndexes(&block, &blockData, x, y, z);

    int type = (unk[block] & 3);

    if (type == 3) {
        if (unk[block] & 4)
            return (unk[block] >> 8) & 255;
        else {
            unsigned char* un = data + ((unk[block] >> 1) & 0x7FFE);
            return un[blockData];
        }
    } else {
        int elementSize = 1 << type;
        int shiftIndex = 3 - type;
        int indexMask = (1 << elementSize) - 1;
        int indexBits = 7 >> type;
        int indexBytes = 0x3E >> shiftIndex;

        unsigned char* types = data + ((unk[block] >> 1) & 0x7FFE);
        unsigned char* unk2 = types + (1 << elementSize);

        int bitShift = (blockData >> shiftIndex) & indexBytes;
        int extractedBits = (blockData & indexBits) * elementSize;

        return types[(unk2[bitShift] >> extractedBits) & indexMask];
    }
}

// NON_MATCHING | Score: 1830 (lower is better)
void CompressedBlockStorage::tick() {
    unsigned int idx = (sStackLength + 1) % 3;
    XLockFreeStack<unsigned char>* stack = &sStack[idx];

    while (true) {
        unsigned char* p = stack->Pop();
        if (!p)
            break;

        free(p, 0);
    }

    sStackLength = idx;
}

bool CompressedBlockStorage::isCompressed() {
    return this->mLength != 0x8400;
}
