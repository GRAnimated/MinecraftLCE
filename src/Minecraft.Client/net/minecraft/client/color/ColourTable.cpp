#include "net/minecraft/client/color/ColourTable.h"

#include "NX/Platform.h"
#include "java/io/ByteArrayInputStream.h"
#include "java/io/DataInputStream.h"

const wchar_t* const ColourTable::s_colourNames[ColourTable::COLOUR_COUNT] = {
#include "ColourNames.inc"

};
std::unordered_map<std::wstring, int> ColourTable::s_nameToColour;

void ColourTable::staticCtor() {
    for (int i = 0; i < COLOUR_COUNT; ++i)
        s_nameToColour.insert(std::make_pair(s_colourNames[i], i));
}

ColourTable::ColourTable(unsigned char* data, unsigned int size) {
    read(data, size);
}

ColourTable::ColourTable(const ColourTable& original, unsigned char* data, unsigned int size) {
    XMemCpy(this, &original, sizeof(ColourTable));
    read(data, size);
}

void ColourTable::read(unsigned char* data, unsigned int size) {
    ByteArrayInputStream bytes(arrayWithLength<unsigned char>(data, size));
    DataInputStream input(&bytes);
    input.readInt();  // The original format header is read but not validated.
    int count = input.readInt();
    while (count > 0) {
        const auto name = input.readUTF();
        const auto value = static_cast<unsigned int>(input.readInt());
        setColour(name, value);
        --count;
    }
    bytes.reset();
}

void ColourTable::setColour(const std::wstring& name, unsigned int value) {
    const auto found = s_nameToColour.find(name);
    if (found != s_nameToColour.end())
        m_colours[found->second] = value;
}

unsigned int ColourTable::getColour(eMinecraftColour colour) {
    return m_colours[static_cast<int>(colour)];
}
