#include "java/io/DataInputStream.h"

#include "net/minecraft/core/BlockPos.h"
#include "net/minecraft/world/item/Item.h"
#include "net/minecraft/world/item/ItemInstance.h"

#include "com/mojang/nbt/NbtIo.h"
#include "net/minecraft/client/Compression.h"

#include <cstdint>
#include <cstring>

#define READ_PRIMITIVE_BYTE() m_inputStream->read()

DataInputStream::DataInputStream(InputStream* stream) : m_inputStream(stream) {}
DataInputStream::~DataInputStream() = default;

/** Destruction of the wrapper does not destroy its child. The binary exposes
 * this explicit operation for callers that transferred ownership.
 */
void DataInputStream::deleteChildStream() {
    delete m_inputStream;
}

int DataInputStream::read() {
    return m_inputStream->read();
}
int DataInputStream::read(arrayWithLength<unsigned char> array) {
    return read(array, 0, array.m_length);
}
int DataInputStream::read(arrayWithLength<unsigned char> array, unsigned int start, unsigned int length) {
    return m_inputStream->read(array, start, length);
}
void DataInputStream::close() {
    m_inputStream->close();
}
long long DataInputStream::skip(long long amount) {
    return m_inputStream->skip(amount);
}
void DataInputStream::skipBytes(long long amount) {
    skip(amount);
}

bool DataInputStream::readBoolean() {
    return READ_PRIMITIVE_BYTE() != 0;
}
unsigned char DataInputStream::readByte() {
    return READ_PRIMITIVE_BYTE();
}
unsigned char DataInputStream::readUnsignedByte() {
    return READ_PRIMITIVE_BYTE();
}
wchar_t DataInputStream::readChar() {
    const std::uint32_t high = READ_PRIMITIVE_BYTE();
    const std::uint32_t low = READ_PRIMITIVE_BYTE();
    return (high << 8) | (low & 0xff);
}
bool DataInputStream::readFully(arrayWithLength<unsigned char> array) {
    for (unsigned int i = 0; i < array.m_length; ++i) {
        const int value = m_inputStream->read();
        if (value == -1) {
            return false;
        }
        array[i] = value;
    }
    return true;
}
// NON_MATCHING | score: 1615 (lower is better)
bool DataInputStream::readFully(arrayWithLength<char> array) {
    return readFully(
        arrayWithLength<unsigned char>(reinterpret_cast<unsigned char*>(array.m_data), array.m_length));
}
bool DataInputStream::readBytes(arrayWithLength<unsigned char> array) {
    for (unsigned int i = 0; i < array.m_length; ++i) {
        const int value = m_inputStream->read();
        if (value == -1) {
            return false;
        }
        array[i] = value;
    }
    return true;
}
int DataInputStream::readInt() {
    const std::uint32_t b0 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b1 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b2 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b3 = READ_PRIMITIVE_BYTE();
    return (b0 << 24) | ((b1 & 0xff) << 16) | ((b2 & 0xff) << 8) | (b3 & 0xff);
}
long DataInputStream::readLong() {
    const std::uint64_t b0 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b1 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b2 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b3 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b4 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b5 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b6 = READ_PRIMITIVE_BYTE();
    const std::uint32_t b7 = READ_PRIMITIVE_BYTE();
    return (b0 << 56) | (std::uint64_t(b1 & 0xff) << 48) | (std::uint64_t(b2 & 0xff) << 40)
           | (std::uint64_t(b3 & 0xff) << 32) | (b4 << 24) | ((b5 & 0xff) << 16) | ((b6 & 0xff) << 8)
           | (b7 & 0xff);
}
short DataInputStream::readShort() {
    const std::uint32_t high = READ_PRIMITIVE_BYTE();
    const std::uint32_t low = READ_PRIMITIVE_BYTE();
    return (high << 8) | (low & 0xff);
}
int DataInputStream::readUnsignedShort() {
    const std::uint32_t high = READ_PRIMITIVE_BYTE();
    const std::uint32_t low = READ_PRIMITIVE_BYTE();
    return (high << 8) | (low & 0xff);
}
// NON_MATCHING | score: 1210 (lower is better)
double DataInputStream::readDouble() {
    const long bits = readLong();
    double result;
    std::memcpy(&result, &bits, sizeof(result));
    return result;
}
// NON_MATCHING | score: 1210 (lower is better)
float DataInputStream::readFloat() {
    const int bits = readInt();
    float result;
    std::memcpy(&result, &bits, sizeof(result));
    return result;
}

// NON_MATCHING | score: 3810 (lower is better)
std::wstring DataInputStream::readUTF() {
    std::wstring result;
    auto invalid = [&result]() -> std::wstring { return result; };
    const unsigned short length = readUnsignedShort();
    unsigned short consumed = 0;
    while (consumed < length) {
        const int first = m_inputStream->read();
        if (first == -1 || (first & 0xc0) == 0x80 || (first & 0xf0) == 0xf0)
            return invalid();
        ++consumed;
        if ((first & 0x80) == 0) {
            result.push_back(first);
        } else if ((first & 0xe0) == 0xc0) {
            if (consumed >= length)
                return invalid();
            const int second = m_inputStream->read();
            if (second == -1 || (second & 0xc0) != 0x80)
                return invalid();
            ++consumed;
            result.push_back(((first & 0x1f) << 6) | (second & 0x3f));
        } else if ((first & 0xf0) == 0xe0) {
            if (consumed >= length)
                return invalid();
            const int second = m_inputStream->read();
            ++consumed;
            if (consumed >= length || second == -1)
                return invalid();
            const int third = m_inputStream->read();
            if (third == -1 || (second & 0xc0) != 0x80 || (third & 0xc0) != 0x80)
                return invalid();
            ++consumed;
            result.push_back(((first & 0xf) << 12) | ((second & 0x3f) << 6) | (third & 0x3f));
        }
    }
    return result;
}
// NON_MATCHING | score: 470 (lower is better)
int DataInputStream::readUTFChar() {
    const int first = m_inputStream->read();
    if (first == -1 || (first & 0xc0) == 0x80 || (first & 0xf0) == 0xf0)
        return -1;
    if ((first & 0x80) == 0)
        return first;
    if ((first & 0xe0) == 0xc0) {
        const int second = m_inputStream->read();
        if (second == -1 || (second & 0xc0) != 0x80)
            return -1;
        return ((first & 0x1f) << 6) | (second & 0x3f);
    }
    if ((first & 0xf0) == 0xe0) {
        const int second = m_inputStream->read();
        if (second == -1)
            return -1;
        const int third = m_inputStream->read();
        if (third == -1 || (second & 0xc0) != 0x80 || (third & 0xc0) != 0x80)
            return -1;
        return ((first & 0xf) << 12) | ((second & 0x3f) << 6) | (third & 0x3f);
    }
    return -1;
}
PlayerUID DataInputStream::readPlayerUID() {
    static_assert(sizeof(PlayerUID) == 32, "The original PlayerUID wire format is 32 bytes");
    PlayerUID result;
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&result);
    for (unsigned int i = 0; i < 32; ++i)
        bytes[i] = readByte();
    return result;
}
// NON_MATCHING | score: 585 (lower is better)
int DataInputStream::readVarInt() {
    std::uint32_t result = 0;
    unsigned int shift = 0;
    int count = -1;
    unsigned char byte;
    do {
        byte = readByte();
        if (++count > 4)
            return -1;
        result |= std::uint32_t(byte & 0x7f) << shift;
        shift += 7;
    } while (byte & 0x80);
    return result;
}
// NON_MATCHING | score: 585 (lower is better)
long DataInputStream::readVarLong() {
    std::uint64_t result = 0;
    unsigned int shift = 0;
    long count = -1;
    unsigned char byte;
    do {
        byte = readByte();
        if (++count > 9)
            return -1;
        result |= std::uint64_t(byte & 0x7f) << shift;
        shift += 7;
    } while (byte & 0x80);
    return result;
}

// NON_MATCHING | score: 5 (lower is better)
CompoundTag* DataInputStream::readCompressedNbt() {
    const short length = readShort();
    if (length < 0)
        return nullptr;
    const short compressedLength = readShort();
    if (compressedLength < 0)
        return nullptr;
    arrayWithLength<unsigned char> compressed(compressedLength, true);
    readFully(compressed);
    arrayWithLength<unsigned char> bytes(length, true);
    unsigned int actualLength = length;
    Compression::getCompression()->Decompress(bytes.m_data, &actualLength, compressed.m_data,
                                              compressed.m_length);
    CompoundTag* result = NbtIo::decompress(bytes);
    delete[] bytes.m_data;
    delete[] compressed.m_data;
    return result;
}

// NON_MATCHING | score: 5 (lower is better)
CompoundTag* DataInputStream::readNbt() {
    const short length = readShort();
    if (length < 0)
        return nullptr;
    arrayWithLength<unsigned char> bytes(length, true);
    readFully(bytes);
    CompoundTag* result = NbtIo::decompress(bytes);
    delete[] bytes.m_data;
    return result;
}

BlockPos DataInputStream::readBlockPos() {
    return BlockPos::decompressBlockPos(readLong());
}

// NON_MATCHING | score: 3036 (lower is better)
BlockPos* DataInputStream::readBlockPosPointer() {
    const BlockPos pos = BlockPos::decompressBlockPos(readLong());
    return new BlockPos(pos.getX(), pos.getY(), pos.getZ());
}

// NON_MATCHING | score: 810 (lower is better)
not_null_ptr<ItemInstance> DataInputStream::readItem() {
    not_null_ptr<ItemInstance> result = ItemInstance::EMPTY;
    const short id = readShort();
    if (id >= 0) {
        const unsigned char count = readByte();
        const short auxiliary = readShort();
        result = not_null_ptr<ItemInstance>(new ItemInstance(Item::byId(id), count, auxiliary));
        result->setTag(readNbt());
    }
    return result;
}
