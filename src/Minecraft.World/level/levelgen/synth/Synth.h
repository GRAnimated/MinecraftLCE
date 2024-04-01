#pragma once

class Synth {
public:
    Synth();
    virtual ~Synth();
    virtual double getValue(double, double) = 0;
};