#pragma once
#include <cstdarg>
class ItemInstance;

class Recipes{
public:
    Recipes();
    void addShapedRecipe(ItemInstance*, ...);
    void buildRecipeIngredientsArray();
};