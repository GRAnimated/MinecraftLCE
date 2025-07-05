#pragma once

class Difficulty {
public:
    static const Difficulty* PEACEFUL;
    static const Difficulty* EASY;
    static const Difficulty* NORMAL;
    static const Difficulty* HARD;

    static Difficulty* byId(int id);
    int getId() const;
};
