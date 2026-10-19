#pragma once

class BlockState;

class FlatLayerInfo {
public:
    int getStart() const;
    int getHeight() const;
    const BlockState* getBlockState() const;

private:
    char m_field0[8];
    const BlockState* m_blockState;
    int m_start;
    int m_height;
};

static_assert(sizeof(FlatLayerInfo) == 0x18, "FlatLayerInfo ABI");
