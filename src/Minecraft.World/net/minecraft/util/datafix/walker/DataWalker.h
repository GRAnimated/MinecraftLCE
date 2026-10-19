#pragma once

class DataFixer;
class CompoundTag;

class DataWalker {
public:
    DataWalker();
    virtual ~DataWalker();
    virtual CompoundTag* walk(DataFixer*, CompoundTag*, int version) = 0;
};
