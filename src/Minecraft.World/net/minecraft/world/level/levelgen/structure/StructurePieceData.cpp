#include "net/minecraft/world/level/levelgen/structure/StructurePiece.h"

#include "java/io/DataInputStream.h"
#include "java/io/DataOutputStream.h"
#include "net/minecraft/util/StringUtils.h"

void StructurePiece::addStructurePieceSaveData(DataOutputStream* output, std::vector<bool> flags0,
                                               std::vector<bool> flags1, std::vector<int> values0,
                                               std::vector<int> values1) {
    addBoolSaveData(output, flags0);
    addBoolSaveData(output, flags1);
    addIntSaveData(output, values0);
    addIntSaveData(output, values1);
}

void StructurePiece::readStructurePieceSaveData(DataInputStream* input, std::vector<bool>& flags0,
                                                std::vector<bool>& flags1, std::vector<int>& values0,
                                                std::vector<int>& values1) {
    flags0 = readBoolSaveData(input);
    flags1 = readBoolSaveData(input);
    values0 = readIntSaveData(input);
    values1 = readIntSaveData(input);
}

void StructurePiece::addBoolSaveData(DataOutputStream* output, std::vector<bool> values) {
    std::wstring text = L"";
    for (std::size_t i = 0; i < values.size(); ++i) {
        text += std::to_wstring(values[i]);
        if (i < values.size() - 1)
            text += L",";
    }
    output->writeUTF(text);
}

std::vector<bool> StructurePiece::readBoolSaveData(DataInputStream* input) {
    std::vector<bool> values;
    std::wstring text = input->readUTF();
    if (!text.empty()) {
        std::vector<std::wstring> tokens;
        tokens = split(text, L',');
        for (std::size_t i = 0; i < tokens.size(); ++i)
            values.push_back(_fromString<bool>(tokens[i]));
    }
    return values;
}

void StructurePiece::addIntSaveData(DataOutputStream* output, std::vector<int> values) {
    std::wstring text = L"";
    for (std::size_t i = 0; i < values.size(); ++i) {
        text += std::to_wstring(values[i]);
        if (i < values.size() - 1)
            text += L",";
    }
    output->writeUTF(text);
}

std::vector<int> StructurePiece::readIntSaveData(DataInputStream* input) {
    std::vector<int> values;
    std::wstring text = input->readUTF();
    if (!text.empty()) {
        std::vector<std::wstring> tokens;
        tokens = split(text, L',');
        for (std::size_t i = 0; i < tokens.size(); ++i)
            values.push_back(_fromString<int>(tokens[i]));
    }
    return values;
}
