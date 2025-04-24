#pragma once

class Difficulty {
public:
    static Difficulty* byId(int id);
    int getId() const;
};
