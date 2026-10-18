#pragma once

#include <string>

class DataInputStream;
class ByteArrayTag;
class Level;
class StructurePiece;
class StructureStart;

class StructureFeatureIO {
public:
    static void staticCtor();
    static std::wstring getEncodeId(StructureStart*);
    static std::wstring getEncodeId(StructurePiece*);
    static StructurePiece* loadStaticPiece(DataInputStream*, Level*);
    static StructureStart* loadStaticStart(ByteArrayTag*, Level*);
};
