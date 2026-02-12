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
        m_strings.push_back(std::move(readUtf(input, 0x7B)));
    }

    for (int i1 = 0; i1 < iv; i1++) {
        m_varints.push_back(input->readVarInt());
    }

    if (b) {
        const unsigned char bb = input->readByte();
        for (int i1 = 0; i1 < b; i1++) {
            m_bools.push_back((bb & (1 << i1)) != 0);
        }
    }

    for (int i1 = 0; i1 < f; i1++) {
        m_floats.push_back(input->readFloat());
    }
}

void FlexiblePacket::write(DataOutputStream* output) {
    const int p = (m_strings.size() & 0xFF) | (m_varints.size() & 0xFFF) << 8 | (m_bools.size() & 0xFF) << 20
                  | m_floats.size() << 28;

    output->writeInt(p);

    for (int i = 0; i < m_strings.size(); i++)
        writeUtf(m_strings[i], output);

    for (int i = 0; i < m_varints.size(); i++)
        output->writeVarInt(m_varints[i]);

    if (m_bools.size()) {
        char b = 0;
        for (int i = 0; i < m_bools.size(); i++) {
            if (m_bools[i])
                b |= (1 << i);
        }

        output->writeByte(b);
    }

    for (int i = 0; i < m_floats.size(); i++)
        output->writeFloat(m_floats[i]);
}

int FlexiblePacket::getEstimatedSize() {
    int strings = 0;

    for (int i = 0; i < m_strings.size(); i++) {
        strings += (int)m_strings[i].length();
    }

    return sizeof(int)                             // 4 byte packed header
           + (sizeof(int) * m_varints.size()       // varints
              + strings                            // strings (why not size * 2 + 2?)
              + (!m_bools.empty())                 // bool
              + sizeof(float) * m_floats.size());  // floats
}
