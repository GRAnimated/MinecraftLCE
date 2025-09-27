#pragma once

class BufferBuilder;

class Tesselator {
public:
    static Tesselator* getInstance();

    static int sThreadStorageIndex;
    static void CreateNewThreadStorage(int);

    Tesselator(int);

    BufferBuilder* getBuilder() const;
    void end();

private:
    BufferBuilder* builder;
    void* padding;  // to match class size, may be an int
};
