#pragma once

#include <nn/util/util_BinTypes.h>

namespace nn::util {

struct RelocationTable;
struct BinaryBlockHeader;

enum ByteOrderMark { ByteOrderMark_Normal = 65279, ByteOrderMark_Reverse = 65534 };

struct BinaryFileHeader {
    BinFileSignature signature;
    BinVersion version;
    uint16_t _byteOrderMark;
    uint8_t _alignmentShift;
    uint8_t _targetAddressSize;
    uint32_t _offsetToFileName;
    uint16_t _flag;
    uint16_t _offsetToFirstBlock;
    uint32_t _offsetToRelTable;
    uint32_t _fileSize;

    bool IsValid(int64_t, int, int, int) const;
    bool IsSignatureValid(int64_t) const;
    bool IsVersionValid(int, int, int) const;
    bool IsEndianValid() const;
    bool IsEndianReverse() const;
    bool IsAlignmentValid() const;
    bool IsRelocated() const;
    size_t GetFileSize() const;
    size_t GetAlignment() const;
    string_view GetFileName() const;
    RelocationTable* GetRelocationTable();
    BinaryBlockHeader* GetFirstBlock();
    const BinaryBlockHeader* GetFirstBlock() const;
    BinaryBlockHeader* FindFirstBlock(int);
    const BinaryBlockHeader* FindFirstBlock(int) const;
    void SetByteOrderMark(ByteOrderMark);
    void SetAddressSize();
    void SetAlignment(size_t);
    void SetFileSize(size_t);
    void SetFileName(const string_view&);
    void SetFirstBlock(BinaryBlockHeader*);
    void SetRelocated(bool);
    void SetRelocationTable(RelocationTable*);
};

struct BinaryBlockHeader {
    BinaryBlockHeader* GetNextBlock();
    const BinaryBlockHeader* GetNextBlock() const;
    BinaryBlockHeader* FindNextBlock(int signature);
    const BinaryBlockHeader* FindNextBlock(int signature) const;
    size_t GetBlockSize() const;
    void SetNextBlock(BinaryBlockHeader* block);
    void SetBlockSize(size_t size);

    BinBlockSignature signature;
    uint32_t _offsetToNextBlock;
    uint32_t _blockSize;
    uint32_t _reserved;
};

struct RelocationTable {
    typedef uint64_t AddrType;

    struct Section {
        union {
            AddrType _padding;
            void* _ptr;
        };
        uint32_t _position;
        uint32_t _size;
        int32_t _entryIndex;
        int32_t _entryCount;

        void SetPtr(void*);
        void* GetPtr() const;
        void* GetPtrInFile(void*) const;
        void* GetBasePtr(void*) const;
        size_t GetSize() const;
    };

    static const int PackedSignature;
    BinBlockSignature _signature;
    uint32_t _position;
    int32_t _sectionCount;
    Section _sections[1];

    static AddrType CalculateSize(int, int);
    void Relocate();
    void Unrelocate();
    Section* GetSection(int);
    const Section* GetSection(int) const;
    void SetSignature();
};

}  // namespace nn::util