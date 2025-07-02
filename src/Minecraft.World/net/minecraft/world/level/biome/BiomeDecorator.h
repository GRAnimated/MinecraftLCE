#pragma once

class Level;
class Random;
class Biome;
class BlockPos;
class Feature;
class ClayFeature;

class BiomeDecorator {
public:
    BiomeDecorator();
    virtual ~BiomeDecorator();
    virtual void decorate(Level*, Random&, Biome*, const BlockPos&);
    virtual void decorate(Biome*, Level*, Random&);
    virtual void decorateOres(Level*, Random&);

private:
    char byte_8;
    void* qword_c;
    void* qword_18;
    ClayFeature* field_20;
    void* qword_28;
    void* qword_30;
    void* qword_38;
    void* qword_40;
    void* qword_48;
    void* qword_50;
    void* qword_58;
    void* qword_60;
    void* qword_68;
    void* qword_70;
    void* qword_78;
    void* qword_80;
    void* qword_88;
    Feature* field_90;
    void* field_98;
    void* field_a0;
    void* field_a8;
    void* field_b0;
    void* field_b8;
    void* qword_c0;
    void* qword_c8;
    int dword_d0;
    int dword_d4;
    void* qword_d8;
    void* qword_e0;
    int dword_e8;
    int dword_ec;
    int dword_f0;
    int dword_f4;
    int dword_f8;
    char byte_fc;
};
