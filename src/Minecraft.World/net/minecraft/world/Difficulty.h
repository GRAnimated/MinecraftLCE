#pragma once

class Difficulty {
public:
    static const Difficulty* PEACEFUL;
    static const Difficulty* EASY;
    static const Difficulty* NORMAL;
    static const Difficulty* HARD;
    static Difficulty* DIFFICULTIES[4];

    static Difficulty* byId(int id);
    int getId() const;

private:
    int m_id;
};

static_assert(sizeof(Difficulty) == 4, "Difficulty ID layout");
