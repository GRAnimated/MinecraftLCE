#include "net/minecraft/network/protocol/FlexiblePacket.h"

#include "java/io/DataOutputStream.h"
#include <string>

void FlexiblePacket::read(DataInputStream* input) {
    const int i = input->readInt();

    const int s = (i & 0x03) + ((i & 0xFC) >> 2) * 4;
    const int iv = (i >> 8) & 0xFFF;
    const int b = (i >> 20) & 0xFF;
    const int f = (i >> 28) & 0x0F;

    for (int i1 = 0; i1 < s; i1++) {
        mStrings.push_back(std::move(readUtf(input, 0x7B)));
    }

    for (int i1 = 0; i1 < iv; i1++) {
        mVarints.push_back(input->readVarInt());
    }

    if (b) {
        const unsigned char bb = input->readByte();
        for (int i1 = 0; i1 < b; i1++) {
            mBools.push_back((bb & (1 << i1)) != 0);
        }
    }

    for (int i1 = 0; i1 < f; i1++) {
        mFloats.push_back(input->readFloat());
    }
}

void FlexiblePacket::write(DataOutputStream* output) {
    const int p = (mStrings.size() & 0xFF) | (mVarints.size() & 0xFFF) << 8 | (mBools.size() & 0xFF) << 20
                  | mFloats.size() << 28;

    output->writeInt(p);

    for (int i = 0; i < mStrings.size(); i++)
        writeUtf(mStrings[i], output);

    for (int i = 0; i < mVarints.size(); i++)
        output->writeVarInt(mVarints[i]);

    if (mBools.size()) {
        char b = 0;
        for (int i = 0; i < mBools.size(); i++) {
            if (mBools[i])
                b |= (1 << i);
        }

        output->writeByte(b);
    }

    for (int i = 0; i < mFloats.size(); i++)
        output->writeFloat(mFloats[i]);
}

int FlexiblePacket::getEstimatedSize() {
    int strings = 0;

    for (int i = 0; i < mStrings.size(); i++) {
        strings += (int)mStrings[i].length();
    }

    return sizeof(int)                            // 4 byte packed header
           + (sizeof(int) * mVarints.size()       // varints
              + strings                           // strings (why not size * 2 + 2?)
              + (!mBools.empty())                 // bool
              + sizeof(float) * mFloats.size());  // floats
}
