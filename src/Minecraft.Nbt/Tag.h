#pragma once

#include <string>
#include "nn/types.h"

class DataOutput;
class DataInput;

class Tag {
public:
    Tag();

    virtual void write(DataOutput*) = 0;
    virtual void load(DataInput*, int) = 0;
    virtual void toString() = 0;
    virtual u8 getId() = 0;
    virtual void print(const std::wstring&, char*, std::wostream&);
    virtual ~Tag();
    virtual void equals(Tag*);
    virtual void copy() = 0;
    virtual void stripEmptyChildren();
    virtual bool isEmpty() const;
    virtual void getAsString();
};