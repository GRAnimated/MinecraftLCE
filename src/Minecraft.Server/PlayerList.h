#pragma once

class BlockPos;
class Dimension;

class PlayerList {
public:
    bool isTrackingBlock(const BlockPos&, Dimension const*);
};
