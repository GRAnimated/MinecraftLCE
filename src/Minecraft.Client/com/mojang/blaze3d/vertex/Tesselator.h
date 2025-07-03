#pragma once

class BufferBuilder;

class Tesselator {
public:
    static Tesselator* getInstance();

    static void CreateNewThreadStorage(int);

    Tesselator(int);

    BufferBuilder* getBuilder() const;

private:
    BufferBuilder* builder;
};
