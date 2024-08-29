#pragma once

class BufferBuilder;

class Tesselator {
public:
    static Tesselator* getInstance();

    Tesselator(int);

    BufferBuilder* getBuilder() const;

private:
    BufferBuilder* builder;
};