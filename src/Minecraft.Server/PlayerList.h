#pragma once

class BlockPos;
class Dimension;

class PlayerList {
public:
    bool isTrackingBlock(BlockPos const&, Dimension const*);
};
