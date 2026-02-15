#pragma once

class Level;
class Random;
class BlockPos;
class BlockState;

class Feature {
public:
    Feature(bool isUpdate);
    virtual ~Feature();
    virtual bool place(Level* level, Random& random, const BlockPos& pos) = 0;
    virtual void init();
    virtual void setBlock(Level* level, const BlockPos& pos, const BlockState* blockState);

private:
    bool m_isUpdate;
};
