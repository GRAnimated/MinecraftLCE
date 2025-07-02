#pragma once

// can't be bothered to find correct base class (if there even is one)
class FireworksRecipe {
public:
    static void CreateNewThreadStorage();

    class ThreadStorage {};
};