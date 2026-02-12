#pragma once

class BufferBuilder;

class Tesselator {
public:
    static Tesselator* getInstance();

    static int sThreadStorageIndex;
    static void CreateNewThreadStorage(int);

    Tesselator(int);  // this int is likely some buffer size, as it is passed to the builder

    BufferBuilder* getBuilder() const;
    void end();

private:
    BufferBuilder* m_builder;
    void* m_padding;  // to match class size, may be an int
};
